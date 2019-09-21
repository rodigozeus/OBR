
#include <VarSpeedServo.h> 

VarSpeedServo servo1; //nome do servo, igual na outra biblioteca



void setup() {
  servo1.attach(8); //pino do servo, igual na outra.

}

void loop() {
 

  servo1.write(180, 20, true); //os parâmetros são (ângulo, velocidade de a 1 a 255 e o "true" serve pro código esperar
                               // até que o movimento do servo seja concluido antes de seguir pra próxima linha.
  delay(1000);
  servo1.write(0, 255); //aqui ele vai pro ângulo 0 em velocidade máxima
  delay(1000);

}


//descrição em ingles do comando .write

/*
write(value)     - Sets the servo angle in degrees.  (invalid angle that is valid as pulse in microseconds is treated as microseconds)
write(value, speed) - speed varies the speed of the move to new position 0=full speed, 1-255 slower to faster
write(value, speed, wait) - wait is a boolean that, if true, causes the function call to block until move is complete
 */
