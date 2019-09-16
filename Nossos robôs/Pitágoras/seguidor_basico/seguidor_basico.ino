/*
==============================================================================================================
MAPEAMENTO DE HARDWARE:
==============================================================================================================*/
//Motor do lado direito
#define direito 7                                                                                                 
#define direito_Invertido 5
#define vel_direito 6 //Precisa ser PWM

//Motor do lado esquerdo
#define esquerdo 2
#define esquerdo_Invertido 4
#define vel_esquerdo 3 //Precisa ser PWM

//Sensores de linha
#define sensor_direito A1
#define sensor_esquerdo A3
#define sensor_meio A2

//Sensor de toque
#define botao A5


/*
==============================================================================================================
CONSTANTES:
==============================================================================================================*/

#define compensa_direito 0 //Valor somado a velocidade do motor direito
#define compensa_esquerdo 0 //Valor somado a velocidade do motor esquerdo

//Velocidades
#define veloc_Frente 120
#define veloc_Reverso 120

//cortes dos sensores de linha
#define corteD 60
#define corteE 60
#define corte_meio 180

/*
==============================================================================================================
VARIÁVEIS:
==============================================================================================================*/





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

  
  //Pinos dos sensores
  pinMode(sensor_direito, INPUT);
  pinMode(sensor_esquerdo, INPUT);
  pinMode(sensor_meio, INPUT);
  pinMode(botao, INPUT_PULLUP);
  
  Serial.begin(9600);
}


/*
==============================================================================================================
PROGRAMA PRINCIPAL:
==============================================================================================================*/
void loop() {
//com obstáculo:
if (digitalRead(botao) == LOW) {
  para();
  }

else {
//Frente se os dois estiverem no branco
if(analogRead(sensor_direito) < corteD and analogRead(sensor_esquerdo) < corteE){
    frente();
    //Serial.println("frente");
  } 
  

//virar pra esquerda se o sensor da esquerda perceber a linha
if(analogRead(sensor_direito) < corteD and analogRead(sensor_esquerdo) > corteE){
    
    
    //Anda pra frente até que o sensor deixe de perceber a linha
    while(true) {
      if (analogRead(sensor_esquerdo)<corteE) {
        break;
      }
      else {
        frente();
      }
    }

    //Girar pra esquerda até o sensor do meio perceber a linha
    while(true){ 
          girar_esquerda();
          //Serial.println("esquerda");
          if (analogRead(sensor_meio)>corte_meio and analogRead(sensor_esquerdo)<corteE){
            break;
          }
    
          //Caso o sensor da direita perceba a linha, volta um pouco e tenta centralizar de novo
          if (analogRead(sensor_direito)>corteD) {
            girar_direita();
            delay(500);
          }
    }  
}

////virar pra esquerda se o sensor da direita perceber a linha
if(analogRead(sensor_direito) > corteD and analogRead(sensor_esquerdo) < corteE){
        
    //Anda pra frente até que o sensor deixe de perceber a linha
    while(true) {
        if (analogRead(sensor_direito)<corteD) {
          break;
        }
        else {
          frente();
        }
    }
    
    //Girar pra direita até o sensor do meio perceber a linha
    while(true){ 
        girar_direita();
        //Serial.println("direita");
        if (analogRead(sensor_meio)>corte_meio and analogRead(sensor_direito)<corteD){
          //Serial.println("Meio");
          break;
        }
        
        //Caso o sensor da esquerda perceba a linha, volta um pouco e tenta centralizar de novo
        if (analogRead(sensor_esquerdo)>corteE) {
          girar_esquerda();
          delay(500);
        }
    } 
 }
  


//Quando os dois sensores estiverem na linha, ponto de decisão  
if (analogRead(sensor_direito) > corteD and analogRead(sensor_esquerdo) > corteE){
     para();
     //Serial.println("Parado");
   
    }
} //sem obstáculo
} //loop



/*
==============================================================================================================
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

     digitalWrite(direito_Invertido, HIGH);
     digitalWrite(esquerdo_Invertido, LOW);
     
     analogWrite(vel_direito, veloc_Frente+compensa_direito);
     analogWrite(vel_esquerdo, veloc_Frente+compensa_esquerdo);
    
     digitalWrite(direito, LOW);
     digitalWrite(esquerdo, LOW);

}

void esquerda(){

     digitalWrite(direito_Invertido, LOW);
     digitalWrite(esquerdo_Invertido, HIGH);
     
     analogWrite(vel_direito, veloc_Frente+compensa_direito);
     analogWrite(vel_esquerdo, veloc_Frente+compensa_esquerdo);
    
     digitalWrite(direito, LOW);
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
