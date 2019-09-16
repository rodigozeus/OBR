
#define direito 4
#define esquerdo 12
#define direito_Invertido 7
#define esquerdo_Invertido 13
#define vel_direito 3
#define vel_esquerdo 11 



#define velocReto 120
#define reverso 120

#define compensa -1
#define tempo_curva 200
#define tempo 500

#define tempo_reta 4000



 
void setup() {

  pinMode(direito, OUTPUT);
  pinMode(direito_Invertido, OUTPUT);
  pinMode(esquerdo, OUTPUT);
  pinMode(esquerdo_Invertido, OUTPUT);
  pinMode(vel_direito, OUTPUT);
  pinMode(vel_esquerdo, OUTPUT);
  
}
 
void loop() {

    //pra direita
    
 digitalWrite(direito, LOW);
 digitalWrite(esquerdo_Invertido, LOW);
 
 analogWrite(vel_direito, velocReto);
 analogWrite(vel_esquerdo, velocReto+compensa);

 digitalWrite(direito_Invertido, HIGH);
 digitalWrite(esquerdo, HIGH);
 delay(tempo_curva);
 
 //pra frente

 digitalWrite(direito_Invertido, LOW);
 digitalWrite(esquerdo_Invertido, LOW);
 
 analogWrite(vel_direito, velocReto);
 analogWrite(vel_esquerdo, velocReto+compensa);

 digitalWrite(direito, HIGH);
 digitalWrite(esquerdo, HIGH);
 delay(5000);
 

}
