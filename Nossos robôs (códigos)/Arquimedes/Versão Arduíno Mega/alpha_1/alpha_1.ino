/*
==============================================================================================================
BIBLIOTECAS:
==============================================================================================================*/

#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);

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
#define veloc_Frente 110
#define veloc_Reverso 110

//cortes dos sensores de linha
#define corteD 150
#define corteE 150
#define corte_meio 150
#define corteED 350
#define corteEE 150


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

int angulo;
int referencia;

/*
==============================================================================================================
CONFIGURAÇÃO:
==============================================================================================================*/
void setup() {
  
  //inicializa giroscopio
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

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

}


/*
==============================================================================================================
PROGRAMA PRINCIPAL:
==============================================================================================================*/
void loop() {
//Serial.println("normal");
//Frente se os dois estiverem no branco
if(analogRead(sensor_direito) < corteD and analogRead(sensor_esquerdo) < corteE){
   obstaculo();
   frente();
 
}//fecha frente
//Sensor da extrema esquerda
if(analogRead(sensor_extrema_esquerda) > corteEE){
                    
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
        left:
        girar_esquerda();
        
        if (analogRead(sensor_meio)>corte_meio){
           meio:
           break;
           }
                    
        //Caso o sensor da direita perceba a linha, volta um pouco e tenta centralizar de novo
        if (analogRead(sensor_extrema_direita)>corteED) {
           while(true) {
              obstaculo();
              girar_direita();
              if (analogRead(sensor_meio)>corte_meio){
                goto meio;
                }
              if (analogRead(sensor_extrema_esquerda)>corteEE) {
                 goto left;
                 }
              }
           }
           
        } //fecha while 
} //fecha extrema esquerda  

//virar pra esquerda se o sensor da esquerda perceber a linha
else if(analogRead(sensor_esquerdo) > corteE) {
   obstaculo();       
   esquerda();
      
}//fecha esquerda

//Sensor da extrema direita
if(analogRead(sensor_extrema_direita) > corteED){
                    
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


////virar pra direita se o sensor da direita perceber a linha
else if(analogRead(sensor_direito) > corteD){
   obstaculo(); 
   direita();

}//fecha direita







                      
//Quando esquerda e direita estiverem na linha, ponto de decisão  
if (analogRead(sensor_direito) > corteD and analogRead(sensor_esquerdo) > corteE){
    
   
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
          para();
          //Serial.println("Obstaculo");
          desvia();
      }
}

void ler_giro() {
    mpu6050.update();
    angulo = mpu6050.getAngleZ();
}

void direita_giro(int curva) {
    para();
    delay(100);
    ler_giro();
    referencia=angulo;
    
    while(angulo>(referencia-curva)) {
      ler_giro();
      girar_direita();
      }
    para();
}

void esquerda_giro(int curva) {
    para();
    delay(100);
    ler_giro();
    referencia=angulo;
    
    while(angulo<(referencia+curva)) {
      ler_giro();
      girar_esquerda();
      }
    para();
}

void frente_reto(int tempo) {
  unsigned long tempo_inicial;
  ler_giro();
  referencia = angulo;
  tempo_inicial=millis();
  while (tempo>(millis()-tempo_inicial)) {
    ler_giro();
    if (angulo>(referencia+2)) {
      girar_direita();
      }
    else if (angulo<(referencia-2)) {
      girar_esquerda();
      }

    else {
      frente();
      }
  }
}
void tras_reto(int tempo) {
  unsigned long tempo_inicial;
  ler_giro();
  referencia = angulo;
  tempo_inicial=millis();
  while (tempo>(millis()-tempo_inicial)) {
    ler_giro();
    if (angulo>(referencia+2)) {
      girar_direita();
      }
    else if (angulo<(referencia-2)) {
      girar_esquerda();
      }

    else {
      tras();
      }
  }
}

void desvia() {
    tras_reto(500);
    esquerda_giro(90);
    frente_reto(1500);
    direita_giro(85);
    frente_reto(3200);
    direita_giro(70);
    frente_reto(1700);
    esquerda_giro(70);
}
