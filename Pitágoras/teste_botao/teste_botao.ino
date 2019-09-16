
#define botao A5


void setup() {

  pinMode(botao, INPUT_PULLUP);
  Serial.begin(9600); 
}

void loop() {

if (digitalRead(botao) == LOW) {
  Serial.println("Apertado");
  }

else {
  Serial.println("solto");
}
  


}
