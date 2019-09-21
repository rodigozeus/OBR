#include <SoftwareSerial.h> //Inclui a biblioteca para comunicação com o módulo bluetooth
#include "pitches.h"
/*
==============================================================================================================
MAPEAMENTO DE HARDWARE:
==============================================================================================================*/
//Motor do lado direito
#define direito 13                                                                                             
#define direito_Invertido 12
#define vel_direito 11 //Precisa ser PWM

//Motor do lado esquerdo
#define esquerdo 8
#define esquerdo_Invertido 3
#define vel_esquerdo 9 //Precisa ser PWM

//Módulo Bluetooth
#define pinoRX 2
SoftwareSerial bluetooth(pinoRX, 3);

#define re A3
#define blue A5
#define red A4
#define setaR A1
#define setaL A2
#define freio A0
#define buzzer 7



/*
==============================================================================================================
CONSTANTES:
==============================================================================================================*/

#define compensa_direito 0 //Valor somado a velocidade do motor direito
#define compensa_esquerdo 0 //Valor somado a velocidade do motor esquerdo


/*
==============================================================================================================
VARIÁVEIS:
==============================================================================================================*/
 
int veloc_Frente = 130;
int veloc_Reverso = 130;
char letra;
bool estado_led_sirene = HIGH;
bool estado_led_setaL = LOW;
bool estado_led_setaR = LOW;
unsigned long tempoL = 0;
unsigned long tempoR = 0;
unsigned long tempo_buzina = 0;
unsigned long tempo_sirene = 0;



/*
==============================================================================================================
CONFIGURAÇÃO:
==============================================================================================================*/
void setup() {

  //Pinos dos motores como saída
  pinMode(direito, OUTPUT);
  pinMode(direito_Invertido, OUTPUT);
  pinMode(esquerdo, OUTPUT);
  pinMode(esquerdo_Invertido, OUTPUT);
  pinMode(vel_direito, OUTPUT);
  pinMode(vel_esquerdo, OUTPUT);
  pinMode(re, OUTPUT);
  pinMode(setaR, OUTPUT);
  pinMode(setaL, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(freio, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  Serial.begin(9600);
  bluetooth.begin(9600);
}


/*
==============================================================================================================
PROGRAMA PRINCIPAL:
==============================================================================================================*/
void loop() {

sirene();

    if (bluetooth.available() > 0) {

          //lê o que o bluetooth mandou e armazena na variável letra
          letra = bluetooth.read();
          
          //informa ao computador o que foi recebido
          Serial.print("Recebi: ");
          Serial.println(letra);


    }

    //define a velocidade em cada caso de 0 a 9 para 0 a 90% e  para 100%.
    if (letra == '0') {
      veloc_Frente = 0;
      veloc_Reverso = 0;
    }
    if (letra == '1') {
      veloc_Frente = 60;
      veloc_Reverso = 60;
      
    }
    if (letra == '2') {
      veloc_Frente = 80;
      veloc_Reverso = 80;
    }
    if (letra == '3') {
      veloc_Frente = 100;
      veloc_Reverso = 100;
    }
    if (letra == '4') {
      veloc_Frente = 120;
      veloc_Reverso = 120;
    }
    if (letra == '5') {
      veloc_Frente = 140;
      veloc_Reverso = 140;
    }
    if (letra == '6') {
      veloc_Frente = 160;
      veloc_Reverso = 160;
    }
    if (letra == '7') {
      veloc_Frente = 180;
      veloc_Reverso = 180;
    }
    if (letra == '8') {
      veloc_Frente = 200;
      veloc_Reverso = 200;
    }
    if (letra == '9') {
      veloc_Frente = 230;
      veloc_Reverso = 230;
    }
    if (letra == 'p' or letra == 'q') {
      veloc_Frente = 255;
      veloc_Reverso = 255;
    }



    //se a letra for F, ele ativa o motor pra frente.
    if (letra == 'F') {
      frente();
      digitalWrite(re, LOW);
          }

    //se a letra for B, ele ativa o motor pra tras.
    if (letra == 'B') {
      tras();
      //buzina();
      digitalWrite(re, HIGH);
    }



    //Esquerda (L)
    if (letra == 'L') {
      girar_esquerda();
      digitalWrite(re, LOW);

    }
    //frente esquerda (G)
    else if (letra == 'G') {
      girar_esquerda();
      digitalWrite(re, LOW);
    }

    //tras esquerda (H)
    else if (letra == 'H') {
      tras_esquerda();
      digitalWrite(re, HIGH);
    }
    else {
      digitalWrite(setaL, LOW);
    }

    //Direita (R)
    if (letra == 'R') {
      girar_direita();
      digitalWrite(re, LOW);

    }

    //frente direita (I)
    else if (letra == 'I') {
      girar_direita();
      digitalWrite(re, LOW);
    }
    //tras direita (J)
    else if (letra == 'J') {
      tras_direita();
      digitalWrite(re, HIGH);
    }
    else {
      digitalWrite(setaR, LOW);
    }

    //para todos os motores (S)
    if (letra == 'S' or letra=='D') {
      para();
      digitalWrite(freio, HIGH);
      
    }
    else {
      digitalWrite(freio, LOW);
    }


  }





/*
==============================================================================================================
DEFININDO CADA FUNÇÃO:
==============================================================================================================*/
void buzina(){
  if ((millis()-tempo_buzina)>800) {
    tone(buzzer,NOTE_A7,400);
    tempo_buzina=millis();
  }
}


void seta_esquerda() {
  if ((millis()-tempoL)>250) {
    estado_led_setaL=!estado_led_setaL;
    digitalWrite(setaL, estado_led_setaL);
    tempoL=millis();
  }
}

void seta_direita() {
  if ((millis()-tempoR)>250) {
    estado_led_setaR=!estado_led_setaR;
    digitalWrite(setaR, estado_led_setaR);
    tempoR=millis();
  }
}

void sirene() {
  if ((millis()-tempo_sirene)>300) {
    estado_led_sirene=!estado_led_sirene;
    digitalWrite(red, estado_led_sirene);
    digitalWrite(blue, (!estado_led_sirene));
    tempo_sirene=millis();
  }
}

void frente(){

     digitalWrite(direito_Invertido, LOW);
     digitalWrite(esquerdo_Invertido, LOW);
     
     analogWrite(vel_direito, veloc_Frente+compensa_direito);
     analogWrite(vel_esquerdo, veloc_Frente+compensa_esquerdo);
    
     digitalWrite(direito, HIGH);
     digitalWrite(esquerdo, HIGH);
 
}

void tras(){

 digitalWrite(direito, LOW);
 digitalWrite(esquerdo, LOW);

 analogWrite(vel_direito, veloc_Reverso+compensa_direito);
 analogWrite(vel_esquerdo, veloc_Reverso+compensa_esquerdo);

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

void direita(){

     digitalWrite(direito_Invertido, HIGH);
     digitalWrite(esquerdo_Invertido, LOW);
     
     analogWrite(vel_direito, veloc_Frente+compensa_direito);
     analogWrite(vel_esquerdo, veloc_Frente+compensa_esquerdo);
    
     digitalWrite(direito, LOW);
     digitalWrite(esquerdo, LOW);
     seta_direita();

}

void esquerda(){

     digitalWrite(direito_Invertido, LOW);
     digitalWrite(esquerdo_Invertido, HIGH);
     
     analogWrite(vel_direito, veloc_Frente+compensa_direito);
     analogWrite(vel_esquerdo, veloc_Frente+compensa_esquerdo);
    
     digitalWrite(direito, LOW);
     digitalWrite(esquerdo, LOW);
     seta_esquerda();

}

void girar_direita(){

 digitalWrite(direito, LOW);
 digitalWrite(esquerdo_Invertido, LOW);
 
 analogWrite(vel_direito, veloc_Reverso+compensa_direito);
 analogWrite(vel_esquerdo, veloc_Frente+compensa_esquerdo);

 digitalWrite(direito_Invertido, HIGH);
 digitalWrite(esquerdo, HIGH);
 seta_direita();

}

void girar_esquerda(){

 digitalWrite(direito_Invertido, LOW);
 digitalWrite(esquerdo, LOW);  
 
 analogWrite(vel_direito, veloc_Frente+compensa_direito);
 analogWrite(vel_esquerdo, veloc_Reverso+compensa_esquerdo);

 digitalWrite(direito, HIGH);
 digitalWrite(esquerdo_Invertido, HIGH);
 seta_esquerda();

}

void tras_direita(){

 digitalWrite(direito, HIGH);
 digitalWrite(esquerdo, LOW);

 analogWrite(vel_direito, veloc_Reverso+compensa_direito);
 analogWrite(vel_esquerdo, veloc_Reverso+compensa_esquerdo);

 digitalWrite(direito_Invertido, LOW);
 digitalWrite(esquerdo_Invertido, HIGH);
 seta_direita();

}

void tras_esquerda(){
 digitalWrite(direito, HIGH);
 digitalWrite(esquerdo, LOW);

 analogWrite(vel_direito, veloc_Reverso+compensa_direito);
 analogWrite(vel_esquerdo, veloc_Reverso);

 digitalWrite(direito_Invertido, LOW);
 digitalWrite(esquerdo_Invertido, HIGH);
 seta_esquerda();
 }
