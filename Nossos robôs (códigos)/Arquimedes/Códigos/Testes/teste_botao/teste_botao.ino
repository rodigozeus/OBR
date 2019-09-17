
#define botao A5

long conta=0;


void setup() {

  pinMode(botao, INPUT_PULLUP);
  Serial.begin(9600); 
}

void loop() {

if (digitalRead(botao) == LOW) {
  conta=conta+1;
  Serial.println(conta);
  }

else {
  //Serial.println("solto");
}
  


}
