/*
==============================================================================================================
MAPEAMENTO DE HARDWARE:
==============================================================================================================*/
//Motor do lado direito
#define direito 13                                                                                             
#define direito_Invertido 12
#define vel_direito 11 //Precisa ser PWM

//Motor do lado esquerdo
#define esquerdo 8
#define esquerdo_Invertido 3
#define vel_esquerdo 9 //Precisa ser PWM

//Sensores
#define extrema_Direita A0
#define extrema_Esquerda A1
#define meio A4

//Sensores de cor
#define pinS2_R 6
#define pinS3_R 7
#define pinOut_R A2
#define pinS2_L 2
#define pinS3_L 4
#define pinOut_L A3

unsigned int valorBrancoR = 0;
unsigned int valorVerdeR = 0;
unsigned int valorBrancoL = 0;
unsigned int valorVerdeL = 0;


/*
==============================================================================================================
CONSTANTES:
==============================================================================================================*/

#define compensa_direito 30 //Valor somado a velocidade do motor direito
#define compensa_esquerdo 0 //Valor somado a velocidade do motor esquerdo
#define compensa_curva 0


#define tempo_curva 50

#define media 2

//cortes
#define corte_fora_da_linha 9
#define corte_na_linha 10
#define corte_no_verde 15
#define corte 100

/*
==============================================================================================================
VARIÁVEIS:
==============================================================================================================*/
 
int mediaD;
int mediaE;


int veloc_Frente = 130;
int veloc_Reverso = 130;

int tentativa;


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
  
//  Pinos dos sensores como entrada
  pinMode(extrema_Direita, INPUT);
  pinMode(extrema_Esquerda, INPUT);
  pinMode(meio, INPUT);

  
  Serial.begin(9600);
}


/*
==============================================================================================================
PROGRAMA PRINCIPAL:
==============================================================================================================*/
void loop() {


ler_sensores();
    

//sensor de cor
 if(mediaD < corte and mediaE < corte){
    frente();
    Serial.println("frente");
  } 
  
 //virar pra esquerda
 if(mediaD < corte and mediaE > corte){
  frente();
  delay(tempo_curva);
    while(true){
      girar_esquerda();
      Serial.println("esquerda");
      if (analogRead(meio)>corte){
        para();
        Serial.println("Meio");
        break;
      }
    }
   
    
  }
//virar pra direita
if(mediaD > corte and mediaE < corte){
  frente();
  delay(tempo_curva);
    while(true){
      girar_direita();
      Serial.println("direita");
      if (analogRead(meio)>corte){
        para();
        Serial.println("Meio");
        break;
      }
    }
  }


  
if(mediaD > corte and mediaE > corte){
  para();

}

}
  
  /*
  tentativa=0;
  tras();
  delay(100);
while(true){
  tentativa=tentativa+1;
  Serial.println(tentativa);
  if (tentativa>10){
    break;
  }
  Serial.println("While ativo");
tras();
delay(50);
para();
delay(200);
detectaCor();

Serial.print("Valor esquerdo: ");
Serial.println(valorVerdeL);
Serial.print("Valor direito: ");
Serial.println(valorVerdeR);

   if(valorVerdeR >= corte_no_verde and valorVerdeL < corte_no_verde){
  girar_direita();
  Serial.println("verde na direita");
  delay(tempo_curva*5);
  break;
  }
  
if(valorVerdeL >= corte_no_verde and valorVerdeR < corte_no_verde){
  girar_esquerda();
  Serial.println("verde na esquerda");
  delay(tempo_curva*5);
  break;
  }
else {
  frente();
  delay(50);
}
  }
}
}




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
 
 analogWrite(vel_direito, veloc_Reverso+compensa_curva+compensa_direito);
 analogWrite(vel_esquerdo, veloc_Frente+compensa_esquerdo);

 digitalWrite(direito_Invertido, HIGH);
 digitalWrite(esquerdo, HIGH);

}

void girar_esquerda(){

 digitalWrite(direito_Invertido, LOW);
 digitalWrite(esquerdo, LOW);  
 
 analogWrite(vel_direito, veloc_Frente+compensa_direito);
 analogWrite(vel_esquerdo, veloc_Reverso+compensa_curva+compensa_esquerdo);

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
 analogWrite(vel_esquerdo, veloc_Reverso);

 digitalWrite(direito_Invertido, LOW);
 digitalWrite(esquerdo_Invertido, HIGH);
 }


 // *********** Função de leitura do sensor de cor ********************
void detectaCor(){

  //Sem filtro
  digitalWrite(pinS3_R, LOW);
  digitalWrite(pinS2_R, HIGH);
  valorBrancoR = pulseIn(pinOut_R, digitalRead(pinOut_R) == HIGH ? LOW : HIGH);

  //Verde
  digitalWrite(pinS3_R, HIGH);
  digitalWrite(pinS2_R, HIGH);
  valorVerdeR = pulseIn(pinOut_R, digitalRead(pinOut_R) == HIGH ? LOW : HIGH);
  
//Sem filtro2
  digitalWrite(pinS3_L, LOW);
  digitalWrite(pinS2_L, HIGH);
  valorBrancoL = pulseIn(pinOut_L, digitalRead(pinOut_L) == HIGH ? LOW : HIGH);

    //Verde2
  digitalWrite(pinS3_L, HIGH);
  digitalWrite(pinS2_L, HIGH);
  valorVerdeL = pulseIn(pinOut_L, digitalRead(pinOut_L) == HIGH ? LOW : HIGH);
}



//ler sensores
void ler_sensores(){
int contador = 0;
int totalD = 0;
int totalE = 0;

while(contador < media){
  totalD = totalD + analogRead(extrema_Direita);
  totalE = totalE +analogRead(extrema_Esquerda);
  contador = contador + 1; 
  }
 mediaD = totalD / media;
 mediaE = totalE / media;
 
//Serial.print("mediaD:");
//Serial.println(mediaD);
//Serial.print("mediaE:");
//Serial.println(mediaE);
 
}
