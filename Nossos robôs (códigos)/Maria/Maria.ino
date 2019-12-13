/*
 * Olá Maria,
 * Abaixo segue um esboço de código para controlar o _________
 * 
 * Lhe proponho uma serie de desafios:
 *    1 - Fazer com que o robô gire tanto pra direita quanto pra esquerda
 *    2 - Construir uma pista de linha com curvas arredondadas (baixa angulação)
 *    3 - Instalar dois sensores de linha no ________
 *    4 - Realizar testes com os sensores de linha e definir os valores de corte
 *    5 - Tornar o _________ capaz de seguir a linha.
 *    
 * Não são desafios fáceis. (não mesmo rsrs)
 * Mas, tenho certeza de que você consegue!!! :)
 */



//Biblioteca do Shield Ponte-H (esta plaquinha em cima do arduíno)
#include <AFMotor.h>

/*
==============================================================================================================
MAPEAMENTO DE HARDWARE:
==============================================================================================================*/

AF_DCMotor motor_esquerdo(1); //motor 1
AF_DCMotor motor_direito(4);  //motor 4

/*
==============================================================================================================
CONSTANTES e VARIÁVEIS:
==============================================================================================================*/

  //nada por enquanto

/*
==============================================================================================================
CONFIGURAÇÃO:
==============================================================================================================*/
void setup() {

esperar_botao();
    
}


/*
==============================================================================================================
PROGRAMA PRINCIPAL:
==============================================================================================================*/
void loop() {

//vai pra frente com 100 de velocidade (máximo é 255)
frente(100);
delay(500);


para();
delay(500);

//vai pra tras com 100 de velocidade (máximo é 255)
tras(100);
delay(500);

}


/*==============================================================================================================
DEFININDO CADA FUNÇÃO:
==============================================================================================================*/

void frente(int velocidade){
  
  //define a velocidade de cada motor
  motor_esquerdo.setSpeed(velocidade);
  motor_direito.setSpeed(velocidade);
  
  //manda o motor girar pra frente (FORWARD)
  motor_esquerdo.run(FORWARD);
  motor_direito.run(FORWARD);
 
}

void tras(int velocidade){

  //define a velocidade de cada motor
  motor_esquerdo.setSpeed(velocidade);
  motor_direito.setSpeed(velocidade);
  
  //manda o motor girar pra tras (BACKWARD)
  motor_esquerdo.run(BACKWARD);
  motor_direito.run(BACKWARD);

}


void para(){

  //manda os motores pararem (RELEASE)
  motor_esquerdo.run(RELEASE);
  motor_direito.run(RELEASE);
  
}

void esperar_botao() {
  pinMode(10, INPUT_PULLUP);
  while (true) {
    if (!digitalRead(10)) {break;}
  }
}
