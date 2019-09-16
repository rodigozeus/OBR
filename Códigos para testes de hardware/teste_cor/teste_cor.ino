
//Pinos de conexao do modulo
const int s2 = 10;
const int s3 = 11;
const int out_E = 9;
const int out_D = 8;
 

//Variaveis cores
int red_E = 0;
int green_E = 0;
int blue_E = 0;
int red_D = 0;
int green_D = 0;
int blue_D = 0;
 
void setup()
{
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out_D, INPUT);
  pinMode(out_E, INPUT);

  Serial.begin(9600);
}
 
void loop()
{
  //Detecta a cor
  color();
  
  /*
  //Mostra valores no serial monitor (esquerda)
  Serial.print("Vermelho :");
  Serial.print(red_E, DEC);
  Serial.print(" Verde : ");
  Serial.print(green_E, DEC);
  Serial.print(" Azul : ");
  Serial.print(blue_E, DEC);
  Serial.println();
  */
  
  /*
  //Mostra valores no serial monitor (direita)
  Serial.print("Vermelho :");
  Serial.print(red_D, DEC);
  Serial.print(" Verde : ");
  Serial.print(green_D, DEC);
  Serial.print(" Azul : ");
  Serial.print(blue_D, DEC);
  Serial.println();
  */
  
 
  //Verifica se a cor verde foi detectada
  if (green_D < red_D and green_D < blue_D and green_E < red_E and green_E < blue_E)
  {
    Serial.println("Verde em ambos!");
  }

  else if (green_D < red_D and green_D < blue_D)
  {
    Serial.println("Verde na direita!");
  }

  else if (green_E < red_E and green_E < blue_E)
  {
    Serial.println("Verde na esquerda!");
  }
  else {
    Serial.println("Nada!");
  }
 
}
 
void color()
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
