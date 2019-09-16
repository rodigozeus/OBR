/* 
 Código para teste de ponte-H (trabalhamos com a L298)
 
/*
==============================================================================================================
MAPEAMENTO DE HARDWARE:
==============================================================================================================*/
//Motor do lado direito
#define direito 5                                                                                                 
#define direito_Invertido 7
#define vel_direito 6 //Precisa ser PWM

//Motor do lado esquerdo
#define esquerdo 4
#define esquerdo_Invertido 2
#define vel_esquerdo 3 //Precisa ser PWM


/*
==============================================================================================================
CONSTANTES:
==============================================================================================================*/

//Velocidades (valores para o pulso PWM: 0 - 255)
#define veloc_Frente 80
#define veloc_Reverso 80

//Compensadores de velocidade, para caso o robô esteja com um lado mais rápido que outro
#define compensa_direito 0 //Valor somado a velocidade do motor direito
#define compensa_esquerdo 0 //Valor somado a velocidade do motor esquerdo

/*
==============================================================================================================
CONFIGURAÇÃO:
==============================================================================================================*/
void setup() {

  //Pinos dos motores como saída
  pinMode(direito, OUTPUT);
  pinMode(direito_Invertido, OUTPUT);
  pinMode(esquerdo, OUTPUT);
  pinMode(esquerdo_Invertido, OUTPUT);
  pinMode(vel_direito, OUTPUT);
  pinMode(vel_esquerdo, OUTPUT);
 

}


/*
==============================================================================================================
PROGRAMA PRINCIPAL:
==============================================================================================================*/
void loop() {

//anda pra frente, anda pra tras, gira pra direita, depois gira esquerda, faz cada operação por 5 segundos e para.

frente();
delay(5000);

tras();
delay(5000);

girar_direita();
delay(5000);

girar_esquerda();
delay(5000);

while(true) {
  para();
}

}


/*==============================================================================================================
DEFININDO CADA FUNÇÃO:
==============================================================================================================*/

void frente(){

     digitalWrite(direito_Invertido, LOW);
     digitalWrite(esquerdo_Invertido, LOW);
     
     analogWrite(vel_direito, veloc_Frente+compensa_direito);
     analogWrite(vel_esquerdo, veloc_Frente+compensa_esquerdo);
    
     digitalWrite(direito, HIGH);
     digitalWrite(esquerdo, HIGH);
 
}

void tras(){
    
     digitalWrite(direito, LOW);
     digitalWrite(esquerdo, LOW);
    
     analogWrite(vel_direito, veloc_Reverso+compensa_direito);
     analogWrite(vel_esquerdo, veloc_Reverso+compensa_esquerdo);
    
     digitalWrite(direito_Invertido, HIGH);
     digitalWrite(esquerdo_Invertido, HIGH);
 
}


void para(){
    
     digitalWrite(direito_Invertido, LOW);
     digitalWrite(esquerdo_Invertido, LOW);
     
     analogWrite(vel_direito, 0);
     analogWrite(vel_esquerdo, 0);
    
     digitalWrite(direito, LOW);
     digitalWrite(esquerdo, LOW);

}

void direita(){

     digitalWrite(direito_Invertido, LOW);
     digitalWrite(esquerdo_Invertido, LOW);
     
     analogWrite(vel_direito, veloc_Frente+compensa_direito);
     analogWrite(vel_esquerdo, veloc_Frente+compensa_esquerdo);
    
     digitalWrite(direito, LOW);
     digitalWrite(esquerdo, HIGH);

}

void esquerda(){

     digitalWrite(direito_Invertido, LOW);
     digitalWrite(esquerdo_Invertido, LOW);
     
     analogWrite(vel_direito, veloc_Frente+compensa_direito);
     analogWrite(vel_esquerdo, veloc_Frente+compensa_esquerdo);
    
     digitalWrite(direito, HIGH);
     digitalWrite(esquerdo, LOW);

}

void girar_direita(){

     digitalWrite(direito, LOW);
     digitalWrite(esquerdo_Invertido, LOW);
     
     analogWrite(vel_direito, veloc_Reverso+compensa_direito);
     analogWrite(vel_esquerdo, veloc_Frente+compensa_esquerdo);
    
     digitalWrite(direito_Invertido, HIGH);
     digitalWrite(esquerdo, HIGH);

}

void girar_esquerda(){

     digitalWrite(direito_Invertido, LOW);
     digitalWrite(esquerdo, LOW);  
     
     analogWrite(vel_direito, veloc_Frente+compensa_direito);
     analogWrite(vel_esquerdo, veloc_Reverso+compensa_esquerdo);
    
     digitalWrite(direito, HIGH);
     digitalWrite(esquerdo_Invertido, HIGH);

}

void tras_direita(){

     digitalWrite(direito, HIGH);
     digitalWrite(esquerdo, LOW);
    
     analogWrite(vel_direito, veloc_Reverso+compensa_direito);
     analogWrite(vel_esquerdo, veloc_Reverso+compensa_esquerdo);
    
     digitalWrite(direito_Invertido, LOW);
     digitalWrite(esquerdo_Invertido, HIGH);

}

void tras_esquerda(){
     digitalWrite(direito, HIGH);
     digitalWrite(esquerdo, LOW);
    
     analogWrite(vel_direito, veloc_Reverso+compensa_direito);
     analogWrite(vel_esquerdo, veloc_Reverso+compensa_esquerdo);
    
     digitalWrite(direito_Invertido, LOW);
     digitalWrite(esquerdo_Invertido, HIGH);

}
