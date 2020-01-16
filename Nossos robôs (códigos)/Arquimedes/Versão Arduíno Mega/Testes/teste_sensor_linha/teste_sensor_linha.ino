/*
 
  Código criado para testar leituras analógicas de sensores de linha (reflexividade baseados em infravermelho)
  Especificamente para 5 sensores posicionados em linha.
 
 */

//Define os pinos em que os 5 sensores estão conectados
#define extrema_direita A0
#define direita A1
#define meio A2
#define esquerda A3
#define extrema_esquerda A4

//Cria as variáveis para armazenamento das leituras
int sensor_ED;
int sensor_D;
int sensor_Meio;
int sensor_E;
int sensor_EE;

void setup() {

  //inicializa todos os sensores como input
  pinMode(extrema_direita, INPUT);
  pinMode(direita, INPUT);
  pinMode(meio, INPUT);
  pinMode(esquerda, INPUT);
  pinMode(extrema_esquerda, INPUT);
  
  //inicializa comunicação com o computador
  Serial.begin(9600); 
}

void loop() {

//Lê e armazena as leituras dos 5 sensores
sensor_ED = analogRead(extrema_direita);
sensor_D = analogRead(direita);
sensor_Meio = analogRead(meio);
sensor_E = analogRead(esquerda);
sensor_EE = analogRead(extrema_esquerda);


//Informa ao computador via serial a leitura de cada um

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
