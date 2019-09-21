#include <SoftwareSerial.h> //Inclui a biblioteca para comunicação com o módulo bluetooth

/*
==============================================================================================================
MAPEAMENTO DE HARDWARE:
==============================================================================================================*/
//Motor do Lado Direito
#define direito 4                                                                                                 
#define direito_Invertido 2
#define vel_direito 3 //Precisa ser PWM

//Motor do Lado Esquerdo
#define esquerdo 5
#define esquerdo_Invertido 7
#define vel_esquerdo 6 //Precisa ser PWM

//Módulo Bluetooth
#define pinoRX 12
SoftwareSerial bluetooth(pinoRX, 13);


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
 
int veloc_Frente = 0;
int veloc_Reverso = 0;
char letra;



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

  Serial.begin(9600);
  bluetooth.begin(9600);
}


/*
==============================================================================================================
PROGRAMA PRINCIPAL:
==============================================================================================================*/
void loop() {


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
    if (letra == 'q') {
      veloc_Frente = 255;
      veloc_Reverso = 255;
    }



    //se a letra for F, ele ativa o motor pra frente.
    if (letra == 'F') {
      frente();
    }

    //se a letra for B, ele ativa o motor pra tras.
    if (letra == 'B') {
      tras();
    }


    //Esquerda (L)
    if (letra == 'L') {
      girar_esquerda();

    }

    //Direita (R)
    if (letra == 'R') {
      girar_direita();

    }

    //frente direita (I)
    if (letra == 'I') {
      girar_direita();
    }

    //frente esquerda (G)
    if (letra == 'G') {
      girar_esquerda();
    }

    //tras esquerda (H)
    if (letra == 'H') {
      tras_esquerda();
    }

    //tras direita (J)
    if (letra == 'J') {
      tras_direita();
    }

    //para todos os motores (S)
    if (letra == 'S' or letra=='D') {
      para();
    }

  }





/*
==============================================================================================================
DEFININDO CADA FUNÇÃO:
==============================================================================================================*/
 
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

}

void esquerda(){

     digitalWrite(direito_Invertido, LOW);
     digitalWrite(esquerdo_Invertido, HIGH);
     
     analogWrite(vel_direito, veloc_Frente+compensa_direito);
     analogWrite(vel_esquerdo, veloc_Frente+compensa_esquerdo);
    
     digitalWrite(direito, LOW);
     digitalWrite(esquerdo, LOW);

}

void girar_direita(){

 digitalWrite(direito, LOW);
 digitalWrite(esquerdo_Invertido, LOW);
 
 analogWrite(vel_direito, veloc_Reverso+compensa_direito);
 analogWrite(vel_esquerdo, veloc_Frente+compensa_esquerdo);

 digitalWrite(direito_Invertido, HIGH);
 digitalWrite(esquerdo, HIGH);

}

void girar_esquerda(){

 digitalWrite(direito_Invertido, LOW);
 digitalWrite(esquerdo, LOW);  
 
 analogWrite(vel_direito, veloc_Frente+compensa_direito);
 analogWrite(vel_esquerdo, veloc_Reverso+compensa_esquerdo);

 digitalWrite(direito, HIGH);
 digitalWrite(esquerdo_Invertido, HIGH);

}

void tras_direita(){

 digitalWrite(direito, HIGH);
 digitalWrite(esquerdo, LOW);

 analogWrite(vel_direito, veloc_Reverso+compensa_direito);
 analogWrite(vel_esquerdo, veloc_Reverso+compensa_esquerdo);

 digitalWrite(direito_Invertido, LOW);
 digitalWrite(esquerdo_Invertido, HIGH);

}

void tras_esquerda(){
 digitalWrite(direito, HIGH);
 digitalWrite(esquerdo, LOW);

 analogWrite(vel_direito, veloc_Reverso+compensa_direito);
 analogWrite(vel_esquerdo, veloc_Reverso);

 digitalWrite(direito_Invertido, LOW);
 digitalWrite(esquerdo_Invertido, HIGH);
 }
