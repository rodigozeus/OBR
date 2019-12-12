/*
==============================================================================================================
MAPEAMENTO DE HARDWARE:
==============================================================================================================*/
//Receptor
#define curva A5
#define acelerador A4

//Motor do lado direito
#define direito 13                                                                                             
#define direito_Invertido 12
#define vel_direito 11 //Precisa ser PWM

//Motor do lado esquerdo
#define esquerdo 8
#define esquerdo_Invertido 3
#define vel_esquerdo 9 //Precisa ser PWM

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
  //Pinos do receptor como entrada
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  //Pinos dos motores como saída
  pinMode(direito, OUTPUT);
  pinMode(direito_Invertido, OUTPUT);
  pinMode(esquerdo, OUTPUT);
  pinMode(esquerdo_Invertido, OUTPUT);
  pinMode(vel_direito, OUTPUT);
  pinMode(vel_esquerdo, OUTPUT);
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
}
//Ir pra frente
else if (leitura_acelerador>centro_acelerador) {
  acelerar(leitura_acelerador);
}

//ir pra tras
else if (leitura_acelerador<centro_acelerador) {
  voltar(leitura_acelerador);
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
      girar_esquerda(abs(velocidade));
  }
  else if (velocidade > (centro_curva+30)) {
      girar_direita(abs(velocidade))
  }
  else {
      para();
  }
}

void acelerar(int velocidade) {
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

void voltar(int velocidade) {
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




void frente(int velocidade){

     digitalWrite(direito_Invertido, LOW);
     digitalWrite(esquerdo_Invertido, LOW);
     
     analogWrite(vel_direito, velocidade);
     analogWrite(vel_esquerdo, velocidade);
    
     digitalWrite(direito, HIGH);
     digitalWrite(esquerdo, HIGH);
 
}

void tras(int velocidade){

     digitalWrite(direito, LOW);
     digitalWrite(esquerdo, LOW);
    
     analogWrite(vel_direito, velocidade);
     analogWrite(vel_esquerdo, velocidade);
    
     digitalWrite(direito_Invertido, HIGH);
     digitalWrite(esquerdo_Invertido, HIGH);
 
}


void para(){

     digitalWrite(direito_Invertido, LOW);
     digitalWrite(esquerdo_Invertido, LOW);
     
     analogWrite(vel_direito, 0);
     analogWrite(vel_esquerdo, 0);
    
     digitalWrite(direito, LOW);
     digitalWrite(esquerdo, LOW);

}

void direita(int velocidade){

     digitalWrite(direito_Invertido, LOW);
     digitalWrite(esquerdo_Invertido, LOW);
     
     analogWrite(vel_direito, velocidade-abs(leitura_curva));
     analogWrite(vel_esquerdo, velocidade);
    
     digitalWrite(direito, HIGH);
     digitalWrite(esquerdo, HIGH);
     }

void esquerda(int velocidade){

     digitalWrite(direito_Invertido, LOW);
     digitalWrite(esquerdo_Invertido, LOW);
     
     analogWrite(vel_direito, velocidade);
     analogWrite(vel_esquerdo, velocidade-abs(leitura_curva));
    
     digitalWrite(direito, HIGH);
     digitalWrite(esquerdo, HIGH);
     }

void girar_direita(int velocidade){

     digitalWrite(direito, LOW);
     digitalWrite(esquerdo_Invertido, LOW);
     
     analogWrite(vel_direito, velocidade);
     analogWrite(vel_esquerdo, velocidade);
    
     digitalWrite(direito_Invertido, HIGH);
     digitalWrite(esquerdo, HIGH);
     }

void girar_esquerda(int velocidade){
    
     digitalWrite(direito_Invertido, LOW);
     digitalWrite(esquerdo, LOW);  
     
     analogWrite(vel_direito, velocidade);
     analogWrite(vel_esquerdo, velocidade);
    
     digitalWrite(direito, HIGH);
     digitalWrite(esquerdo_Invertido, HIGH);
     }

void tras_direita(int velocidade){

     digitalWrite(direito, LOW);
     digitalWrite(esquerdo, LOW);
    
     analogWrite(vel_direito, velocidade);
     analogWrite(vel_esquerdo, velocidade-abs(leitura_curva));
    
     digitalWrite(direito_Invertido, HIGH);
     digitalWrite(esquerdo_Invertido, HIGH);
     }

void tras_esquerda(int velocidade){
     digitalWrite(direito, LOW);
     digitalWrite(esquerdo, LOW);
    
     analogWrite(vel_direito, velocidade-abs(leitura_curva));
     analogWrite(vel_esquerdo, velocidade);
    
     digitalWrite(direito_Invertido, HIGH);
     digitalWrite(esquerdo_Invertido, HIGH);
     }
