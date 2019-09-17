/*
Testa os sensores de cor esquerdo e direito
Para diminuir a quantidade de portas usadas no Arduíno, os pinos s2 e s3 dos dois sensores foram unificados,
então, s2 e s3 são o mesmo para o sensor direito e esquerdo, sendo necessário um cabo Y.
*/

//Pinos de conexao dos modulos
const int s2 = 10; //s2 direito e esquerdo
const int s3 = 11; //s3 direito e esquerdo

const int out_E = 9; //Out esquerdo
const int out_D = 8; //Out direito
 

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
  ler_cor();
  
  //Verifica se a cor verde foi detectada e informa qual o lado ou se foi em ambos.
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
    Serial.println("Verde não detectado");
  }
 
}
 
void ler_cor()
{
  //Rotina que le o valor das cores
 
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  //Testa a cor vermelha nos dois sensores
  red_E = pulseIn(out_E, digitalRead(out_E) == HIGH ? LOW : HIGH);
  red_D = pulseIn(out_D, digitalRead(out_D) == HIGH ? LOW : HIGH);
  digitalWrite(s3, HIGH);
  //Testa a cor azul nos dois sensores
  blue_E = pulseIn(out_E, digitalRead(out_E) == HIGH ? LOW : HIGH);
  blue_D = pulseIn(out_D, digitalRead(out_D) == HIGH ? LOW : HIGH);
  digitalWrite(s2, HIGH);
  //Testa a cor verde nos dois sensores
  green_E = pulseIn(out_E, digitalRead(out_E) == HIGH ? LOW : HIGH);
  green_D = pulseIn(out_D, digitalRead(out_D) == HIGH ? LOW : HIGH);
}
