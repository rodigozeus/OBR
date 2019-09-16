#include <HCSR04.h>

//define onde o sensor está ligado
#define Echo 11
#define Trig 10
#define ledVermelho 3
#define ledhulk 10
#define ledhomer 2
int distancia;

UltraSonicDistanceSensor sensor(Trig, Echo);  //Inicializa o sensor usando os pinos

void setup () {
    Serial.begin(9600); //inicia a comunicação com o computador
    pinMode(ledVermelho, OUTPUT);
    pinMode(ledhulk, OUTPUT);
    pinMode(ledhomer, OUTPUT);
}
void loop () {
    
    distancia=sensor.measureDistanceCm();
    Serial.print(distancia);
    Serial.println("cm de distância");
    delay(100);

    if (distancia<=15) {

      digitalWrite(ledVermelho, HIGH);
      digitalWrite(ledhulk, LOW);
      digitalWrite(ledhomer, LOW);
    }

    if (distancia>=16) {

      digitalWrite(ledhomer, HIGH);
      digitalWrite(ledhulk, LOW);
    }
    
    
    if (distancia>15) {

      digitalWrite(ledVermelho, LOW);
    
    }

    if (distancia>=30) {

      digitalWrite(ledhomer, LOW);
      digitalWrite(ledhulk, HIGH);
    }
    }
