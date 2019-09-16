/*
==============================================================================================================
MAPEAMENTO DE HARDWARE:
==============================================================================================================*/
//Motor do lado direito
#define direito 4
#define direito_Invertido 7
#define vel_direito 3 //Precisa ser PWM

//Motor do lado esquerdo
#define esquerdo 12
#define esquerdo_Invertido 13
#define vel_esquerdo 11 //Precisa ser PWM

//Sensores
#define pin_sensor_Direito 2
#define pin_sensor_Esquerdo 8
 
/*
==============================================================================================================
CONSTANTES:
==============================================================================================================*/

#define veloc_Frente 100 //Velocidade normal (0 a 255)
#define velo_Reverso 100 //Velocidade reversa (0 a 255)

#define compensa_direito 20 //Valor somado a velocidade do motor direito
#define compensa_esquerdo 0 //Valor somado a velocidade do motor esquerdo
 

/*
==============================================================================================================
VARIÁVEIS:
==============================================================================================================*/
 
bool sensor_Direito, sensor_Esquerdo;

/*
==============================================================================================================
FUNÇÕES:
==============================================================================================================*/

void frente(), para(), esquerda(), direita(), girar_direita(), girar_esquerda();

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
  
  //Pinos dos sensores como entrada
  pinMode(pin_sensor_Direito, INPUT);
  pinMode(pin_sensor_Esquerdo, INPUT);
  
}


/*
==============================================================================================================
PROGRAMA PRINCIPAL:
==============================================================================================================*/
void loop() {
 
//Leituras dos Sensores
sensor_Direito = !digitalRead(pin_sensor_Direito);
sensor_Esquerdo = !digitalRead(pin_sensor_Esquerdo);
 
 
 //Nenhum sensor vê a linha
 if(sensor_Direito == false and sensor_Esquerdo == false){
    
    frente();
  } 
 
 //O sensor esquerdo vê a linha
 else if(sensor_Direito == false and sensor_Esquerdo == true){

    girar_direita();
  }

 //O sensor direito vê a linha
 else if(sensor_Direito == true and sensor_Esquerdo == false){

    girar_esquerda();
  }

 //Os dois sensores vêem a linha
 else if(sensor_Direito == true and sensor_Esquerdo == true){

    para();
 }

}


/*
==============================================================================================================
DEFININDO CADA FUNÇÃO:
==============================================================================================================*/
 
void frente() {

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

 analogWrite(vel_direito, velo_Reverso+compensa_direito);
 analogWrite(vel_esquerdo, velo_Reverso+compensa_esquerdo);

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

 digitalWrite(direito, LOW);
 digitalWrite(esquerdo_Invertido, LOW);
 digitalWrite(direito_Invertido, LOW);
 
 analogWrite(vel_direito, 0);
 analogWrite(vel_esquerdo, veloc_Frente+compensa_esquerdo);

 digitalWrite(esquerdo, HIGH);

}

void esquerda(){

 digitalWrite(direito_Invertido, LOW);
 digitalWrite(esquerdo, LOW);
 digitalWrite(esquerdo_Invertido, LOW); 
 
 analogWrite(vel_direito, veloc_Frente+compensa_direito);
 analogWrite(vel_esquerdo, 0);

 digitalWrite(direito, HIGH);


}

void girar_direita(){

 digitalWrite(direito, LOW);
 digitalWrite(esquerdo_Invertido, LOW);
 
 analogWrite(vel_direito, velo_Reverso+compensa_direito);
 analogWrite(vel_esquerdo, veloc_Frente+compensa_esquerdo);

 digitalWrite(direito_Invertido, HIGH);
 digitalWrite(esquerdo, HIGH);

}

void girar_esquerda(){

 digitalWrite(direito_Invertido, LOW);
 digitalWrite(esquerdo, LOW);  
 
 analogWrite(vel_direito, veloc_Frente+compensa_direito);
 analogWrite(vel_esquerdo, velo_Reverso+compensa_esquerdo);

 digitalWrite(direito, HIGH);
 digitalWrite(esquerdo_Invertido, HIGH);

}
