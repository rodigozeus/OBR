#include <Servo.h>

Servo daniel;
Servo rodrigo;

void setup() {  
  daniel.attach(9);
  rodrigo.attach(10);
  
}

void loop() {
  
   daniel.write(100);
   rodrigo.write(80);
   
  delay(2000);
  
 


}
