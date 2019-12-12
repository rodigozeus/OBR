/*
==============================================================================================================
MAPEAMENTO DE HARDWARE:
==============================================================================================================*/
//Motor do Lado Direito
#define direito 2                                                                                                 
#define direito_Invertido 7
#define vel_direito 10//Precisa ser PWM

//Motor do Lado Esquerdo
#define esquerdo 4
#define esquerdo_Invertido 8
#define vel_esquerdo 11 //Precisa ser PWM

#define sensor_frente A0
#define sensor_tras A1


/*
==============================================================================================================
CONSTANTES e VARIÁVEIS:
==============================================================================================================*/

#define corte_frente 100
#define corte_tras 100

//Compensadores de velocidade, para caso o robô esteja com um lado mais rápido que outro
#define compensa_direito 0 //Valor somado a velocidade do motor direito
#define compensa_esquerdo 0 //Valor somado a velocidade do motor esquerdo

bool direcao = true;
int velocidade = 170;

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
  pinMode(sensor_frente, INPUT);
  pinMode(sensor_tras, INPUT);
  Serial.begin(9600);
 

}


/*
==============================================================================================================
PROGRAMA PRINCIPAL:
==============================================================================================================*/
void loop() {

if (direcao) {
  frente(170);
}

else {
  tras(170);
}

ler_sensores();

}


/*==============================================================================================================
DEFININDO CADA FUNÇÃO:
==============================================================================================================*/

void ler_sensores() {
  int leitura_frente = analogRead(sensor_frente);
  int leitura_tras = analogRead(sensor_tras);

  Serial.print("Frente: ");
  Serial.print(leitura_frente);
  Serial.print("       Tras: ");
  Serial.println(leitura_tras);

  //Frente saindo - Voltar
  if (leitura_frente<corte_frente and leitura_tras>corte_tras) {
    if (direcao) {
    direcao = false;
    velocidade = 0;
    para();
    delay(100);
    while (velocidade < 170) {
      velocidade = velocidade + 10;
      tras(velocidade);
      delay(50);
    }
    }
    else {
      tras(255);
      delay(3000);
    }
  }
  //Traseira saindo - Voltar
  if (leitura_frente>corte_frente and leitura_tras<corte_tras) {
    
    if(direcao) {
      frente(255);
      delay(3000);
    }
    else {
    direcao = true;
    velocidade = 0;
    para();
    delay(100);
    while (velocidade < 170) {
      velocidade = velocidade + 10;
      frente(velocidade);
      delay(50);
    }
    }
  }
  }


void frente(int velocidade){

     digitalWrite(direito_Invertido, LOW);
     digitalWrite(esquerdo_Invertido, LOW);
     
     analogWrite(vel_direito, velocidade+compensa_direito);
     analogWrite(vel_esquerdo, velocidade+compensa_esquerdo);
    
     digitalWrite(direito, HIGH);
     digitalWrite(esquerdo, HIGH);
 
}

void tras(int velocidade){
    
     digitalWrite(direito, LOW);
     digitalWrite(esquerdo, LOW);
    
     analogWrite(vel_direito, velocidade+compensa_direito);
     analogWrite(vel_esquerdo, velocidade+compensa_esquerdo);
    
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
