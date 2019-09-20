
#include <MPU6050_tockn.h>
#include <Wire.h>
#include <SoftwareSerial.h>

#define pinoTX 2
SoftwareSerial uno(13,pinoTX);

int angulo;
int referencia;
#define controle 12

MPU6050 mpu6050(Wire);

void setup() {
  Serial.begin(9600);
  uno.begin(9600);
  pinMode(controle, INPUT);
  Wire.begin();
  mpu6050.begin();
  delay(1000);
  Serial.println("Nano ligado");
  mpu6050.calcGyroOffsets(true);
  finaliza();

}

void loop() {
  
  if (digitalRead(controle)==HIGH) {
    para();
    desvia();
    finaliza();
  }

}






void ler_giro() {
    mpu6050.update();
    angulo = mpu6050.getAngleZ();
}
void frente(){
  uno.print("F");
  }

void tras(){
  uno.print("B");
  }

void para(){
  uno.print("S");  
  }

void direita(){
  uno.print("I");
  }

void esquerda(){
  uno.print("G");
  }

void girar_direita(){
  uno.print("R");
  }

void girar_esquerda(){
  uno.print("L");
  }
void finaliza() {
  uno.print("P");
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
    //mpu6050.calcGyroOffsets(true);
    tras_reto(500);
    esquerda_giro(80);
    frente_reto(1500);
    direita_giro(90);
    frente_reto(3200);
    direita_giro(70);

}
