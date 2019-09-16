//Programa: Sensor TCS3200 e led RGB
//Autor: FILIPEFLOP

// Mais informações: https://www.filipeflop.com/blog/sensor-de-cor-tcs3200-rgb-arduino/ 
 
//Pinos de conexao do modulo

const int s2 = 2;
const int s3 = 4;
const int out = A3;
 
//Pinos do led RGB

 
//Variaveis cores
int red = 0;
int green = 0;
int blue = 0;
 
void setup()
{

  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);

  Serial.begin(115200);

}
 
void loop()
{
  //Detecta a cor
  color();
  //Mostra valores no serial monitor
  Serial.print("Vermelho :");
  Serial.print(red, DEC);
  Serial.print(" Verde : ");
  Serial.print(green, DEC);
  Serial.print(" Azul : ");
  Serial.print(blue, DEC);
  Serial.println();
 
  //Verifica se a cor vermelha foi detectada
  if (red < blue && red < green && red < 500)
  {
    Serial.println("Vermelho");

  }
 
  //Verifica se a cor azul foi detectada
  else if (blue < red && blue < green && blue < 1000)
  {
    Serial.println("Azul");

  }
 
  //Verifica se a cor verde foi detectada
  else if (green < red && green < blue)
  {
    Serial.println("Verde");

  }
  Serial.println();
 

  delay(50);

}
 
void color()
{
  //Rotina que le o valor das cores
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  //count OUT, pRed, RED
  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s3, HIGH);
  //count OUT, pBLUE, BLUE
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s2, HIGH);
  //count OUT, pGreen, GREEN
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
}
