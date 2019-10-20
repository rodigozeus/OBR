#include <AFMotor.h>
/*
==============================================================================================================
MAPEAMENTO DE HARDWARE:
==============================================================================================================*/
#define curva A5
#define acelerador A4

AF_DCMotor motor_esquerdo(4);
AF_DCMotor motor_direito(1);

/*
==============================================================================================================
CONSTANTES:
==============================================================================================================*/
#define centro_curva -18
#define centro_acelerador 17
#define correcao 1 //maior que 1 se estiver puxando pra direita e vice versa
#define fator_giro 2 //ajusta a velocidade de giro parado

/*
==============================================================================================================
VARIÁVEIS:
==============================================================================================================*/
long leitura_curva = 0;
long leitura_acelerador = 0;


/*
==============================================================================================================
CONFIGURAÇÃO:
==============================================================================================================*/
void setup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  motor_esquerdo.run(RELEASE);
  motor_direito.run(RELEASE);
  Serial.begin(9600);

}


/*
==============================================================================================================
PROGRAMA PRINCIPAL:
==============================================================================================================*/
void loop() {
  
leitura_curva = (pulseIn(curva, HIGH, 30000));
leitura_acelerador = (pulseIn(acelerador, HIGH, 30000));

leitura_curva = map(leitura_curva, 977, 2060, -255, 255);
leitura_acelerador = map(leitura_acelerador, 890, 2030, -255, 255);
imprime_valores();

//acelerador solto
if (abs(leitura_acelerador-centro_acelerador)<10) {
  gira_parado(leitura_curva/fator_giro);
}
else if (leitura_acelerador>centro_acelerador) {
  frente(leitura_acelerador);
}
else if (leitura_acelerador<centro_acelerador) {
  tras(leitura_acelerador);
}
}


/*
==============================================================================================================
DEFININDO CADA FUNÇÃO:
==============================================================================================================*/
void imprime_valores() {
  Serial.print("Curva: ");
  Serial.print(leitura_curva);
  Serial.print("        Acelerador: ");
  Serial.println(leitura_acelerador);
}

void gira_parado(int velocidade) {
  if (velocidade < (centro_curva-30)) {
      Serial.print("Esquerda_tras e Direita_frente: ");
      Serial.println(abs(velocidade));
      motor_esquerdo.setSpeed(abs(velocidade));
      motor_direito.setSpeed(abs(velocidade));
      motor_esquerdo.run(BACKWARD);
      motor_direito.run(FORWARD);
  }
  else if (velocidade > (centro_curva+30)) {
      Serial.print("Esquerda_frente e Direita_tras: ");
      Serial.println(abs(velocidade));
      motor_esquerdo.setSpeed(abs(velocidade));
      motor_direito.setSpeed(abs(velocidade));
      motor_esquerdo.run(FORWARD);
      motor_direito.run(BACKWARD);
  }
  else {
      motor_esquerdo.run(RELEASE);
      motor_direito.run(RELEASE);
  }
}

void frente(int velocidade) {
  if (leitura_curva < (centro_curva-30)) {
      if (leitura_curva<=velocidade) {
        motor_esquerdo.setSpeed(0);
      }
      else {
        motor_esquerdo.setSpeed(abs(velocidade)-abs(leitura_curva));
      }
      motor_direito.setSpeed(abs(velocidade));
      motor_esquerdo.run(FORWARD);
      motor_direito.run(FORWARD);
  }
  else if (leitura_curva > (centro_curva+30)) {
      if (leitura_curva>=velocidade) {
        motor_direito.setSpeed(0);
      }
      else {
        motor_direito.setSpeed(abs(velocidade)-abs(leitura_curva));
      }
      motor_esquerdo.setSpeed(abs(velocidade));
      motor_esquerdo.run(FORWARD);
      motor_direito.run(FORWARD);
  }
  else {
      motor_esquerdo.setSpeed(abs(velocidade)/correcao);
      motor_direito.setSpeed(abs(velocidade));
      motor_esquerdo.run(FORWARD);
      motor_direito.run(FORWARD);
  }
}

void tras(int velocidade) {
  if (leitura_curva < (centro_curva-30)) {
      if (leitura_curva<=velocidade) {
        motor_esquerdo.setSpeed(0);
      }
      else {
        motor_esquerdo.setSpeed(abs(velocidade)-abs(leitura_curva));
      }
      motor_direito.setSpeed(abs(velocidade));
      motor_esquerdo.run(BACKWARD);
      motor_direito.run(BACKWARD);
  }
  else if (leitura_curva > (centro_curva+30)) {
      if (leitura_curva>=velocidade) {
        motor_direito.setSpeed(0);
      }
      else {
        motor_direito.setSpeed(abs(velocidade)-abs(leitura_curva));
      }
      motor_esquerdo.setSpeed(abs(velocidade));
      motor_esquerdo.run(BACKWARD);
      motor_direito.run(BACKWARD);
  }
  else {
      motor_esquerdo.setSpeed(abs(velocidade)/correcao);
      motor_direito.setSpeed(abs(velocidade));
      motor_esquerdo.run(BACKWARD);
      motor_direito.run(BACKWARD);
  }
}
