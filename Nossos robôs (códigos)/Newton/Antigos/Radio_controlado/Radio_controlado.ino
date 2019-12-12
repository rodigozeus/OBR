#include <AFMotor.h>
#include <Servo.h> 
/*
==============================================================================================================
MAPEAMENTO DE HARDWARE:
==============================================================================================================*/
#define curva A5
#define acelerador A4

AF_DCMotor motor_esquerdo(4);
AF_DCMotor motor_direito(1);

Servo helice;

/*
==============================================================================================================
CONSTANTES:
==============================================================================================================*/
#define centro_curva -18
#define centro_acelerador 17
#define fator_giro 1 //ajusta a velocidade de giro parado

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
  helice.attach(9);
  helice.write(20);
  delay(2000);
}


/*
==============================================================================================================
PROGRAMA PRINCIPAL:
==============================================================================================================*/
void loop() {
  
leitura_curva = (pulseIn(curva, HIGH, 30000));
leitura_acelerador = (pulseIn(acelerador, HIGH, 30000));

leitura_curva = map(leitura_curva, 977, 2060, -250, 250);
leitura_acelerador = map(leitura_acelerador, 890, 2030, -250, 250);
imprime_valores();

//acelerador solto
if (abs(leitura_acelerador-centro_acelerador)<10) {
  gira_parado(leitura_curva/fator_giro);
  helice.write(20);
}
else if (leitura_acelerador>centro_acelerador) {
  frente(leitura_acelerador);
  //helice.write(leitura_acelerador-120);
}
else if (leitura_acelerador<centro_acelerador) {
  tras(leitura_acelerador);
  helice.write(20);
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
      motor_esquerdo.setSpeed(abs(velocidade));
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
      motor_esquerdo.setSpeed(abs(velocidade));
      motor_direito.setSpeed(abs(velocidade));
      motor_esquerdo.run(BACKWARD);
      motor_direito.run(BACKWARD);
  }
}
