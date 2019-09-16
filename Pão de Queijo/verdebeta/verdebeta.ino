#include <HCSR04.h>

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

//Sensores de linha
#define extrema_Direita A0
#define extrema_Esquerda A1
#define meio A4

//Sensores de cor
#define pinS2_R 6
#define pinS3_R 7
#define pinOut_R A2
#define pinS2_L 2
#define pinS3_L 4
#define pinOut_L A3

//Sensor ultrassônico
UltraSonicDistanceSensor distanceSensor(5, 10);



/*
==============================================================================================================
CONSTANTES:
==============================================================================================================*/

#define compensa_direito 40 //Valor somado a velocidade do motor direito
#define compensa_esquerdo 0 //Valor somado a velocidade do motor esquerdo

//Delays
#define tempo_curva 150

//Velocidades
#define veloc_Frente 160
#define veloc_Reverso 160

//cortes dos sensores de linha
#define corteD 150
#define corteE 150
#define corte_meio 350

/*
==============================================================================================================
VARIÁVEIS:
==============================================================================================================*/

int tentativa;

int red_L = 0;
int green_L = 0;
int blue_L = 0;
int red_R = 0;
int green_R = 0;
int blue_R = 0;
bool esquerda_verde = false;
bool direita_verde = false;
int sensor_esquerdo;
int sensor_direito;


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
  pinMode(pinS2_L, OUTPUT);
  pinMode(pinS3_L, OUTPUT);
  pinMode(pinOut_L, INPUT);
  
//  Pinos dos sensores
  pinMode(extrema_Direita, INPUT);
  pinMode(extrema_Esquerda, INPUT);
  pinMode(pinS2_L, OUTPUT);
  pinMode(pinS3_L, OUTPUT);
  pinMode(pinOut_L, INPUT);
  pinMode(pinS2_R, OUTPUT);
  pinMode(pinS3_R, OUTPUT);
  pinMode(pinOut_R, INPUT);

  
  Serial.begin(9600);
}


/*
==============================================================================================================
PROGRAMA PRINCIPAL:
==============================================================================================================*/
void loop() {

if (distanceSensor.measureDistanceCm()<7) {

  para();
  delay(500);
  int contador = 0;
  for (int x=0; x < 10; x++) {
    
    if (distanceSensor.measureDistanceCm()<7) {
       contador = contador+1;
  }
  }

  if (contador>7) {
        Serial.println("obstaculo");
        
        girar_direita();
        delay(1300);
        frente();
        delay(500);
        girar_esquerda();
        delay(1500);
        frente();
        delay(500);
        girar_esquerda();
        delay(1300);
        frente();
        
  
  }
    
  

}


 
 else {
Serial.println("Livre");
 

//Ler os sensores de linha:
sensor_esquerdo = analogRead(extrema_Esquerda);
sensor_direito = analogRead(extrema_Direita);


//Frente se os dois estiverem no branco
if(sensor_direito < corteD and sensor_esquerdo < corteE){
    frente();
    //Serial.println("frente");
  } 
  

//virar pra esquerda se o sensor da esquerda perceber a linha
if(sensor_direito < corteD and sensor_esquerdo > corteE){
    
    para();
    delay(300);
    
    //Anda pra frente até que o sensor deixe de perceber a linha
    while(true) {
      sensor_esquerdo = analogRead(extrema_Esquerda);
      if (sensor_esquerdo<corteE) {
        break;
      }
      else {
        frente();
      }
    }

    //Girar pra esquerda até o sensor do meio perceber a linha
    while(true){ 
          girar_esquerda();
          //Serial.println("esquerda");
          if (analogRead(meio)>corte_meio and analogRead(extrema_Esquerda)<corteE){
            para();
            delay(tempo_curva/2);
            //Serial.println("Meio");
            break;
          }
    
          //Caso o sensor da direita perceba a linha, volta um pouco e tenta centralizar de novo
          if (analogRead(extrema_Direita)>corteD) {
            girar_direita();
            delay(500);
          }
    }  
}

////virar pra esquerda se o sensor da direita perceber a linha
if(sensor_direito > corteD and sensor_esquerdo < corteE){
    
    para();
    delay(300);
    
    //Anda pra frente até que o sensor deixe de perceber a linha
    while(true) {
        sensor_direito = analogRead(extrema_Direita);
        if (sensor_direito<corteD) {
          break;
        }
        else {
          frente();
        }
    }
    
    //Girar pra direita até o sensor do meio perceber a linha
    while(true){ 
        girar_direita();
        //Serial.println("direita");
        if (analogRead(meio)>corte_meio and analogRead(extrema_Direita)<corteD){
          para();
          delay(200);
          //Serial.println("Meio");
          break;
        }
        
        //Caso o sensor da esquerda perceba a linha, volta um pouco e tenta centralizar de novo
        if (analogRead(extrema_Esquerda)>corteE) {
          girar_esquerda();
          delay(500);
        }
    } 
 }
  


//Quando os dois sensores estiverem na linha, ponto de decisão  
if (sensor_direito > corteD and sensor_esquerdo > corteE){
     para();
     //Serial.println("parou!!!");
     delay(tempo_curva);
     tras();
     delay(tempo_curva);
     para();
      
      while(true) {    
        detectaCor();
        if (esquerda_verde) {
            frente();
            delay(tempo_curva*2);
            while(true){ 
              girar_esquerda();
              //Serial.println("esquerda no verde");
              if (analogRead(meio)>corte_meio){
                para();
                //Serial.println("Virei no verde");
                break;
              }
             
              }
              break;
        }
        else {
          //Serial.println("Outro");
          
                  }
      
      }
      
    }

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
 analogWrite(vel_esquerdo, veloc_Reverso+compensa_esquerdo);

 digitalWrite(direito_Invertido, LOW);
 digitalWrite(esquerdo_Invertido, HIGH);
 }


 // *********** Função de leitura do sensor de cor ********************
void detectaCor(){
  
  //Rotina que le o valor das cores
  esquerda_verde = false;
  direita_verde = false;
  
  int conta_esquerda_verde = 0;
  int conta_direita_verde = 0;
  
  //Lê 10 vezes cada sensor de cor
  
  for (int x=0; x<10; x++) {
      
      //Sensor esquerdo:
      digitalWrite(pinS2_L, LOW);
      digitalWrite(pinS3_L, LOW);
      //count OUT, pRed, RED
      red_L = pulseIn(pinOut_L, digitalRead(pinOut_L) == HIGH ? LOW : HIGH);
      digitalWrite(pinS3_L, HIGH);
      //count OUT, pBLUE, BLUE
      blue_L = pulseIn(pinOut_L, digitalRead(pinOut_L) == HIGH ? LOW : HIGH);
      digitalWrite(pinS2_L, HIGH);
      //count OUT, pGreen, GREEN
      green_L = pulseIn(pinOut_L, digitalRead(pinOut_L) == HIGH ? LOW : HIGH);
    
      if (green_L < red_L && green_L < blue_L)
      {
        conta_esquerda_verde = conta_esquerda_verde+1;
      }
      
      //Sensor direito:
      digitalWrite(pinS2_R, LOW);
      digitalWrite(pinS3_R, LOW);
      //count OUT, pRed, RED
      red_R = pulseIn(pinOut_R, digitalRead(pinOut_R) == HIGH ? LOW : HIGH);
      digitalWrite(pinS3_R, HIGH);
      //count OUT, pBLUE, BLUE
      blue_R = pulseIn(pinOut_R, digitalRead(pinOut_R) == HIGH ? LOW : HIGH);
      digitalWrite(pinS2_R, HIGH);
      //count OUT, pGreen, GREEN
      green_R = pulseIn(pinOut_R, digitalRead(pinOut_R) == HIGH ? LOW : HIGH);
    
      if (green_R < red_R && green_R < blue_R)
      {
        conta_direita_verde = conta_direita_verde+1;
      }

  }

//Se mais que 6 leituras derem verde, considera verde
if ((conta_esquerda_verde>6)) {
  esquerda_verde = true;
}
else {
  esquerda_verde = false;
}

if ((conta_direita_verde>6)) {
  direita_verde = true;
}
else {
  direita_verde = false;
}


}
