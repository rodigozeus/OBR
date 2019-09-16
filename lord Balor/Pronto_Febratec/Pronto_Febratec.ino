#include <SoftwareSerial.h> //Inclui a biblioteca para comunicação com o módulo bluetooth
#include <HCSR04.h>

const int pinoRX = 2; //Define o pino que recebe os dados do módulo

UltraSonicDistanceSensor distanceSensor(9,8);
SoftwareSerial bluetooth(pinoRX, 3); //configura a comunicação com p módulo



char letra = 'S';
int velocidade_tras = 200;
int velocidade = 200; //velocidade inicial
int distancia;
int curva = 130; //o quanto de potência aplicar aos motores que viram
int U=200;

//pinos para contrololar a ponte H
int frente = 6;
int tras = 5;
int direita = 11;
int esquerda = 10;




void setup() {
  Serial.begin(9600);
  pinMode(frente, OUTPUT);
  pinMode(tras, OUTPUT);




  //inicia a comunicação com o computador
  
  bluetooth.begin(9600); //inicia a comunicação com o bluetooth

  //define os pinos da ponte H como saída
  pinMode(frente, OUTPUT);
  pinMode(tras, OUTPUT);
  pinMode(esquerda, OUTPUT);
  pinMode(direita, OUTPUT);

  //para todos os motores por segurança
  analogWrite(frente, 0);
  analogWrite(tras, 0);
  analogWrite(esquerda, 0);
  analogWrite(direita, 0);
}



//inicia a parte do código que será repetida infinitamente
void loop() {

    distancia=distanceSensor.measureDistanceCm();
    Serial.print("Distancia: ");
    Serial.println(distancia);

 
 if (distancia<=10 and distancia>0) {
    
      analogWrite(frente, 0);
      analogWrite(tras, velocidade_tras);
      analogWrite(direita, 0);
      analogWrite(esquerda, 0);
      
 }
    
 if (distancia>=20) {
    analogWrite(tras, 0);
    analogWrite(frente, 100);
    analogWrite(direita, 0);
    analogWrite(esquerda, 0);
   
 }
 if (distancia >10 and distancia <20){
    analogWrite(frente, 0);
    analogWrite(tras, 0);
    analogWrite(direita, 0);
    analogWrite(esquerda, 0);
 }

 } 
 

    

 
