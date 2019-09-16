
#define extrema_Direita A0
#define extrema_Esquerda A2
#define meio A1

int sensorD = 0;
int sensorE = 0;
int sensorMeio = 0;

void setup() {

  Serial.begin(9600); 
}

void loop() {

  sensorD = analogRead(extrema_Direita);
  sensorE = analogRead(extrema_Esquerda);
  sensorMeio = analogRead(meio);
  
  Serial.print("Esquerda: ");
  Serial.print(sensorE);
  Serial.print("  /  Direita:");
  Serial.print(sensorD);
  Serial.print("  /  Meio:");
  Serial.println(sensorMeio);


}
