/**** OBR 2020 **** Plano Piloto **** 3 meses ****  pista + rampa ****
/*
========================================
Mapeamento de Hardware:
========================================*/
//Motor do lado direito
#define direito 7                                                                                                 
#define direito_Invertido 5
#define vel_direito 6 

//Motor do lado esquerdo
#define esquerdo 2
#define esquerdo_Invertido 4
#define vel_esquerdo 3 

//Sensores de linha
#define extrema_direita A0
#define direita A1
#define meio A2
#define esquerda A3
#define extrema_esquerda A4

//sensor de toque
#define botao A5

//Sensores de cor
const int s2 = 10;
const int s3 = 11;
const int out_E = 9;
const int out_D = 8;


/*
========================================
Constantes:
========================================*/
#define compensa_direito 0 
#define compensa_esquerdo 0 

//Velocidades
#define veloc_Frente 120
#define veloc_Reverso 120

//cortes dos sensores de linha
#define corte 200


/*
========================================
Variaveis:                           
========================================*/
//sensor de linha
int sensor_ED = 0;
int sensor_D = 0;
int sensor_Meio = 0;
int sensor_E = 0;
int sensor_EE = 0;

//Variaveis cores
int red_E = 0;
int green_E = 0;
int blue_E = 0;
int red_D = 0;
int green_D = 0;
int blue_D = 0;


/*======================================
Configuração:
========================================*/
void setup() {
//Pinos dos motores
  pinMode(direito, OUTPUT);
  pinMode(direito_Invertido, OUTPUT);
  pinMode(esquerdo, OUTPUT);
  pinMode(esquerdo_Invertido, OUTPUT);
  pinMode(vel_direito, OUTPUT);
  pinMode(vel_esquerdo, OUTPUT);

//pinos dos sensores de linha
  pinMode(extrema_direita, INPUT);
  pinMode(direita, INPUT);
  pinMode(meio, INPUT);
  pinMode(esquerda, INPUT);
  pinMode(extrema_esquerda, INPUT);

//pinos dos sensores de linha
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out_D, INPUT);
  pinMode(out_E, INPUT);

//pino do sensor de toque
pinMode(botao, INPUT_PULLUP);
Serial.begin(9600); 
}

/*======================================
Programação principal:
========================================*/
void loop() {
/*--------------------------------------
Seguir a linha:  
----------------------------------------*/



/*---------------------------------------
Identificar a cor verde:  
-----------------------------------------*/



/*---------------------------------------
 Desviar do objeto:  
-----------------------------------------*/

}


/*======================================
Voids:
========================================*/
/*---------------------------------------
 Direções:  
-----------------------------------------*/
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

void girar_direita(){

     digitalWrite(direito_Invertido, HIGH);
     digitalWrite(esquerdo_Invertido, LOW);
     
     analogWrite(vel_direito, veloc_Frente+compensa_direito);
     analogWrite(vel_esquerdo, veloc_Frente+compensa_esquerdo);
    
     digitalWrite(direito, LOW);
     digitalWrite(esquerdo, LOW);

}

void girar_esquerda(){

     digitalWrite(direito_Invertido, LOW);
     digitalWrite(esquerdo_Invertido, HIGH);
     
     analogWrite(vel_direito, veloc_Frente+compensa_direito);
     analogWrite(vel_esquerdo, veloc_Frente+compensa_esquerdo);
    
     digitalWrite(direito, LOW);
     digitalWrite(esquerdo, LOW);

}

void girar_direita_eixo(){

 digitalWrite(direito, LOW);
 digitalWrite(esquerdo_Invertido, LOW);
 
 analogWrite(vel_direito, veloc_Reverso+compensa_direito);
 analogWrite(vel_esquerdo, veloc_Frente+compensa_esquerdo);

 digitalWrite(direito_Invertido, HIGH);
 digitalWrite(esquerdo, HIGH);

}

void girar_esquerda_eixo(){

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

/*--------------------------------------
Detectar cor
----------------------------------------*/
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

 
