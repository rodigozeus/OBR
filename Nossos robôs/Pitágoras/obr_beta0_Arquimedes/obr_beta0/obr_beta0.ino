/*
==============================================================================================================
BIBLIOTECAS:
==============================================================================================================*/

#include <MPU6050_tockn.h>
#include <Wire.h>

/*
==============================================================================================================
MAPEAMENTO DE HARDWARE:
==============================================================================================================*/
//Motor do lado direito
#define direito 5                                                                                                 
#define direito_Invertido 7
#define vel_direito 6 //Precisa ser PWM

//Motor do lado esquerdo
#define esquerdo 4
#define esquerdo_Invertido 2
#define vel_esquerdo 3 //Precisa ser PWM

//Sensores de linha
#define sensor_extrema_direita A0
#define sensor_direito A1
#define sensor_meio A2
#define sensor_esquerdo A3
#define sensor_extrema_esquerda A4

//Sensor de toque
#define botao A5

//Sensores de cor
#define s2 10
#define s3 11
#define out_E 9
#define out_D 8


/*
==============================================================================================================
CONSTANTES:
==============================================================================================================*/

#define compensa_direito 0 //Valor somado a velocidade do motor direito
#define compensa_esquerdo 0 //Valor somado a velocidade do motor esquerdo

//Velocidades
#define veloc_Frente 100
#define veloc_Reverso 100

//cortes dos sensores de linha
#define corteD 80
#define corteE 80
#define corte_meio 70
#define corteED 220
#define corteEE 420


/*
==============================================================================================================
VARIÁVEIS:
==============================================================================================================*/

//Variaveis cores
int red_E = 0;
int green_E = 0;
int blue_E = 0;
int red_D = 0;
int green_D = 0;
int blue_D = 0;



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

  
  //Pinos dos sensores
  pinMode(sensor_direito, INPUT);
  pinMode(sensor_esquerdo, INPUT);
  pinMode(sensor_extrema_direita, INPUT);
  pinMode(sensor_extrema_esquerda, INPUT);
  pinMode(sensor_meio, INPUT);
  pinMode(botao, INPUT_PULLUP);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out_D, INPUT);
  pinMode(out_E, INPUT);
  
  Serial.begin(9600);
}


/*
==============================================================================================================
PROGRAMA PRINCIPAL:
==============================================================================================================*/
void loop() {

//Frente se os dois estiverem no branco
if(analogRead(sensor_direito) < corteD and analogRead(sensor_esquerdo) < corteE){
    obstaculo();
    frente();
 
}//fecha frente
  

//virar pra esquerda se o sensor da esquerda perceber a linha
if(analogRead(sensor_direito) < corteD and analogRead(sensor_esquerdo) > corteE) {
   obstaculo();       
   esquerda();
      
}//fecha esquerda


////virar pra direita se o sensor da direita perceber a linha
if(analogRead(sensor_direito) > corteD and analogRead(sensor_esquerdo) < corteE){
  obstaculo(); 
  direita();

}//fecha direita


//Sensor da extrema esquerda
if(analogRead(sensor_extrema_direita) < corteED and analogRead(sensor_extrema_esquerda) > corteEE){
                    
    //Anda pra frente até que o sensor deixe de perceber a linha
    while(true) {
       obstaculo();
       if (analogRead(sensor_esquerdo)<corteE) {
          break;
          }
          else {
             frente();
             }
        }//fecha while
                
     //Girar pra esquerda até o sensor do meio perceber a linha
     while(true){ 
        obstaculo();
        girar_esquerda();
        /
        if (analogRead(sensor_meio)>corte_meio){
           break;
           }
                    
        //Caso o sensor da direita perceba a linha, volta um pouco e tenta centralizar de novo
        if (analogRead(sensor_direito)>corteD) {
           girar_direita();
           delay(500);
           }
        } //fecha while 
} //fecha extrema esquerda


//Sensor da extrema direita
if(analogRead(sensor_extrema_direita) > corteED and analogRead(sensor_extrema_esquerda) < corteEE){
                    
    //Anda pra frente até que o sensor deixe de perceber a linha
    while(true) {
       obstaculo();
       if (analogRead(sensor_direito)<corteD) {
          break;
          }
          else {
             frente();
             }
        }//fecha while
                
     //Girar pra direita até o sensor do meio perceber a linha
     while(true){ 
        obstaculo();
        girar_direita();
        
        if (analogRead(sensor_meio)>corte_meio){
           break;
           }
                    
        //Caso o sensor da esquerda perceba a linha, volta um pouco e tenta centralizar de novo
        if (analogRead(sensor_esquerdo)>corteE) {
           girar_esquerda();
           delay(500);
           }
        } //fecha while 
} //fecha extrema direita

                      
//Quando esquerda e direita estiverem na linha, ponto de decisão  
if (analogRead(sensor_direito) > corteD and analogRead(sensor_esquerdo) > corteE){
     //to be continued
   
}//fecha ponto de decisão

} //fecha loop



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

     digitalWrite(direito_Invertido, LOW);
     digitalWrite(esquerdo_Invertido, LOW);
     
     analogWrite(vel_direito, veloc_Frente+compensa_direito);
     analogWrite(vel_esquerdo, veloc_Frente+compensa_esquerdo);
    
     digitalWrite(direito, LOW);
     digitalWrite(esquerdo, HIGH);

}

void esquerda(){

     digitalWrite(direito_Invertido, LOW);
     digitalWrite(esquerdo_Invertido, LOW);
     
     analogWrite(vel_direito, veloc_Frente+compensa_direito);
     analogWrite(vel_esquerdo, veloc_Frente+compensa_esquerdo);
    
     digitalWrite(direito, HIGH);
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
     analogWrite(vel_esquerdo, veloc_Reverso+compensa_esquerdo);
    
     digitalWrite(direito_Invertido, LOW);
     digitalWrite(esquerdo_Invertido, HIGH);
 }

 void detecta_cor()
{
      //Rotina que le o valor das cores
      digitalWrite(s2, LOW);
      digitalWrite(s3, LOW);
      //count OUT, pRed, RED
      red_E = pulseIn(out_E, digitalRead(out_E) == HIGH ? LOW : HIGH);
      red_D = pulseIn(out_D, digitalRead(out_D) == HIGH ? LOW : HIGH);
      digitalWrite(s3, HIGH);
      //count OUT, pBLUE, BLUE
      blue_E = pulseIn(out_E, digitalRead(out_E) == HIGH ? LOW : HIGH);
      blue_D = pulseIn(out_D, digitalRead(out_D) == HIGH ? LOW : HIGH);
      digitalWrite(s2, HIGH);
      //count OUT, pGreen, GREEN
      green_E = pulseIn(out_E, digitalRead(out_E) == HIGH ? LOW : HIGH);
      green_D = pulseIn(out_D, digitalRead(out_D) == HIGH ? LOW : HIGH);
}

void obstaculo() {
      if (digitalRead(botao) == LOW) {
      while(true) {
        para();
        //to be continued
  }
  }
}
