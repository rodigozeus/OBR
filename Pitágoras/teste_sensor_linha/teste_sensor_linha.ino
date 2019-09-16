
#define extrema_direita A0
#define direita A1
#define meio A2
#define esquerda A3
#define extrema_esquerda A4

int sensor_ED = 0;
int sensor_D = 0;
int sensor_Meio = 0;
int sensor_E = 0;
int sensor_EE = 0;

void setup() {

  pinMode(extrema_direita, INPUT);
  pinMode(direita, INPUT);
  pinMode(meio, INPUT);
  pinMode(esquerda, INPUT);
  pinMode(extrema_esquerda, INPUT);
  Serial.begin(9600); 
}

void loop() {

sensor_ED = analogRead(extrema_direita);
sensor_D = analogRead(direita);
sensor_Meio = analogRead(meio);
sensor_E = analogRead(esquerda);
sensor_EE = analogRead(extrema_esquerda);

  
  Serial.print("Ext. Esquerda: ");
  Serial.print(sensor_EE);
  
  Serial.print(" / Esquerda:");
  Serial.print(sensor_E);
  
  Serial.print(" / Meio:");
  Serial.print(sensor_Meio);
  
  Serial.print(" / Direita:");
  Serial.print(sensor_D);

  Serial.print(" / Ext. Direita:");
  Serial.println(sensor_ED);


}
