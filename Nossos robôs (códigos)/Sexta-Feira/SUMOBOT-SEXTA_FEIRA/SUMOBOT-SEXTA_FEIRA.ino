/*
======================================================================================
SUMOBOT-SEXTA_FEIRA
====================================================================================== 
BIBLIOTECAS:
====================================================================================== */
#include <HCSR04.h>
   
/*
======================================================================================
MAPEAMENTO DE HARDWARE:
====================================================================================== */
//Motor do Lado Direito
#define Direito 4                                                                                                 
#define Direito_Invertido 2
#define Vel_Direito 3 //Precisa ser PWM

//Motor do Lado Esquerdo
#define Esquerdo 5
#define Esquerdo_Invertido 7
#define Vel_Esquerdo 6 //Precisa ser PWM

//Sensor de Linha
#define Extrema_Direita A0
#define Extrema_Esquerda A2
#define Meio A1

//Sensor Ultrassônico
UltraSonicDistanceSensor distanceSensor (8,9);

/*
======================================================================================
CONSTANTES:
====================================================================================== */
//Velocidade Compensa
#define Compensa_Direito 0
#define Compensa_Esquerdo 0

//Delay de Curva
#define Tempo_Curva 0

//Velocidades
#define Velocidade_Frente 150
#define Velocidade_Reverso 150

//Corte dos Sensor de Linha
#define Corte_Direito 200
#define Corte_Esquerdo 200
#define Corte_Meio 0

/*
======================================================================================
VARIÁVEIS:
====================================================================================== */
int distancia;

/*
======================================================================================
CONFIGURAÇÃO:
====================================================================================== */
void setup() {
  
//Pinos dos Motores 
pinMode(Direito,OUTPUT);
pinMode(Direito_Invertido,OUTPUT);
pinMode(Vel_Direito,OUTPUT);
pinMode(Esquerdo,OUTPUT);
pinMode(Esquerdo_Invertido,OUTPUT);
pinMode(Vel_Esquerdo,OUTPUT);

//Pinos dos Sensor de Linha
pinMode(Extrema_Direita,INPUT);
pinMode(Extrema_Esquerda,INPUT);

Serial.begin(9600);

}

/*
======================================================================================
PROGRAMAÇÃO:
====================================================================================== */
void loop() {  
  
distancia = distanceSensor.measureDistanceCm();
//dentro do parênteses precisa colocar a velocidade desejada de 0 a 25
  if (distancia < 30 and distancia >= 0) {
while(true){
frente(255);
} 
}
}


/*
======================================================================================
DIREÇÕES:
====================================================================================== */
//FRENTE
void frente(int velocidade){
if (velocidade>255) {
  velocidade = 255; }
if ((velocidade+Compensa_Direito)>255) {
  velocidade = 255-Compensa_Direito; }
if ((velocidade+Compensa_Esquerdo>255)) {
  velocidade = 255-Compensa_Esquerdo; }
digitalWrite(Direito,HIGH);
digitalWrite(Esquerdo,HIGH);
analogWrite(Vel_Direito,velocidade+Compensa_Direito);
analogWrite(Vel_Esquerdo,velocidade+Compensa_Esquerdo);
digitalWrite(Direito_Invertido,LOW);
digitalWrite(Esquerdo_Invertido,LOW); }

//RÉ
void tras(int velocidade){
if (velocidade>255) {
  velocidade = 255; }
if ((velocidade+Compensa_Direito)>255) {
  velocidade = 255-Compensa_Direito; }
if ((velocidade+Compensa_Esquerdo>255)) {
  velocidade = 255-Compensa_Esquerdo; }
digitalWrite(Direito,LOW);
digitalWrite(Esquerdo,LOW);
analogWrite(Vel_Direito,velocidade+Compensa_Direito);
analogWrite(Vel_Esquerdo,velocidade+Compensa_Esquerdo);
digitalWrite(Direito_Invertido,HIGH);
digitalWrite(Esquerdo_Invertido,HIGH); }
 
//PARA
void para(){
digitalWrite(Direito,LOW);
digitalWrite(Esquerdo,LOW);
analogWrite(Vel_Direito,0);
analogWrite(Vel_Esquerdo,0);
digitalWrite(Direito_Invertido,LOW);
digitalWrite(Esquerdo_Invertido,LOW); }

//DIREITA
void direita(){
digitalWrite(Direito,LOW);
digitalWrite(Esquerdo,LOW);  
analogWrite(Vel_Direito,Velocidade_Frente+Compensa_Direito);
analogWrite(Vel_Esquerdo,Velocidade_Frente+Compensa_Esquerdo);
digitalWrite(Direito_Invertido,HIGH);
digitalWrite(Esquerdo_Invertido,LOW); }

//ESQUERDA
void esquerda(){
digitalWrite(Direito,LOW);
digitalWrite(Esquerdo,LOW);  
analogWrite(Vel_Direito,Velocidade_Frente+Compensa_Direito);
analogWrite(Vel_Esquerdo,Velocidade_Frente+Compensa_Esquerdo);
digitalWrite(Direito_Invertido,LOW);
digitalWrite(Esquerdo_Invertido,HIGH); }

//GIRAR_DIREITA
void girar_direita(){
digitalWrite(Direito,LOW);
digitalWrite(Esquerdo,HIGH);  
analogWrite(Vel_Direito,Velocidade_Frente+Compensa_Direito);
analogWrite(Vel_Esquerdo,Velocidade_Frente+Compensa_Esquerdo);
digitalWrite(Direito_Invertido,HIGH);
digitalWrite(Esquerdo_Invertido,LOW); }

//GIRAR_ESQUERDA
void girar_esquerda(){
digitalWrite(Direito,HIGH);
digitalWrite(Esquerdo,LOW);  
analogWrite(Vel_Direito,Velocidade_Frente+Compensa_Direito);
analogWrite(Vel_Esquerdo,Velocidade_Frente+Compensa_Esquerdo);
digitalWrite(Direito_Invertido,LOW);
digitalWrite(Esquerdo_Invertido,HIGH); }

//RÉ_DIREITA
void tras_direita(){
digitalWrite(Direito,HIGH);
digitalWrite(Esquerdo,LOW);
analogWrite(Vel_Direito,Velocidade_Reverso+Compensa_Direito);
analogWrite(Vel_Esquerdo,Velocidade_Reverso+Compensa_Esquerdo);
digitalWrite(Direito_Invertido,LOW);
digitalWrite(Esquerdo_Invertido,HIGH); }

//RÉ_ESQUERDA
void tras_esquerda(){
digitalWrite(Direito,LOW);
digitalWrite(Esquerdo,HIGH);
analogWrite(Vel_Direito,Velocidade_Reverso+Compensa_Direito);
analogWrite(Vel_Esquerdo,Velocidade_Reverso+Compensa_Esquerdo);
digitalWrite(Direito_Invertido,HIGH);
digitalWrite(Esquerdo_Invertido,LOW); }
