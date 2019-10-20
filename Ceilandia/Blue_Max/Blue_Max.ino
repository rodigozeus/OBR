/*
==============================================================================================================
MAPEAMENTO DE HARDWARE:
==============================================================================================================*/
#define sensor_frente A0
#define sensor_tras A5

#include <AFMotor.h>

AF_DCMotor motor_esquerdo(3);
AF_DCMotor motor_direito(4);


/*
==============================================================================================================
CONSTANTES e VARIÁVEIS:
==============================================================================================================*/

#define corte_frente 100
#define corte_tras 100

bool direcao = true;
int velocidade = 250;

/*
==============================================================================================================
CONFIGURAÇÃO:
==============================================================================================================*/
void setup() {
  
  pinMode(sensor_frente, INPUT);
  pinMode(sensor_tras, INPUT);
  Serial.begin(9600);
    // turn on motor
  motor_esquerdo.setSpeed(velocidade);
  motor_direito.setSpeed(velocidade);
 
  motor_esquerdo.run(RELEASE);
  motor_direito.run(RELEASE);
 

}


/*
==============================================================================================================
PROGRAMA PRINCIPAL:
==============================================================================================================*/
void loop() {

if (direcao) {
  frente(250);
}

else {
  tras(250);
}

ler_sensores();

}


/*==============================================================================================================
DEFININDO CADA FUNÇÃO:
==============================================================================================================*/

void ler_sensores() {
  int leitura_frente = analogRead(sensor_frente);
  int leitura_tras = analogRead(sensor_tras);

  Serial.print("Frente: ");
  Serial.print(leitura_frente);
  Serial.print("       Tras: ");
  Serial.println(leitura_tras);

  //Frente saindo - Voltar
  if (leitura_frente<corte_frente and leitura_tras>corte_tras) {
    direcao = false;
    velocidade = 0;
    para();
    delay(100);
    while (velocidade < 250) {
      velocidade = velocidade + 10;
      tras(velocidade);
      delay(30);
    }
  }
  //Traseira saindo - Voltar
  if (leitura_frente>corte_frente and leitura_tras<corte_tras) {
    direcao = true;
    velocidade = 0;
    para();
    delay(100);
    while (velocidade < 250) {
      velocidade = velocidade + 10;
      frente(velocidade);
      delay(30);
    }
  }
  }


void frente(int velocidade){
  
  motor_esquerdo.setSpeed(velocidade);
  motor_direito.setSpeed(velocidade);
  motor_esquerdo.run(FORWARD);
  motor_direito.run(FORWARD);
 
}

void tras(int velocidade){

  motor_esquerdo.setSpeed(velocidade);
  motor_direito.setSpeed(velocidade);
  motor_esquerdo.run(BACKWARD);
  motor_direito.run(BACKWARD);

}


void para(){
  
  motor_esquerdo.run(RELEASE);
  motor_direito.run(RELEASE);
  
}
