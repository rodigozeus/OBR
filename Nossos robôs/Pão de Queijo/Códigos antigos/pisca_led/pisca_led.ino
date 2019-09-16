/*
Programa simples que pisca um led ligado ao Arduíno
*/

//define a palavra "led" como sendo o mesmo que 13
#define led1 10 
#define led2 2
#define led3 3
#define tempo 1000
void setup() {
  //inicializa o pino do led como porta de saída
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

//Essa é a função mais importante, ela se repete até que o Arduíno seja desligado.
void loop() {
  digitalWrite(led1, HIGH);   // liga o led
  delay(5*tempo);               // espera 1000 milissegundos = 1 segundo 
  digitalWrite(led1, LOW);    // desliga o led
  digitalWrite(led2, HIGH);
  delay(2*tempo);               // espera 1000 milissegundos = 1 segundo
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH);
  delay(5*tempo);
  digitalWrite(led3, LOW);
  
  
  //depois disso a função volta do início, ou seja, liga o led de novo...
}
