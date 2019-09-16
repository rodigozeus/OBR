// MultiStepper
// -*- mode: C++ -*-
//
// Control both Stepper motors at the same time with different speeds
// and accelerations. 
// Requires the AFMotor library (https://github.com/adafruit/Adafruit-Motor-Shield-library)
// And AccelStepper with AFMotor support (https://github.com/adafruit/AccelStepper)
// Public domain!

#include <AccelStepper.h>
#include <AFMotor.h>

#define velocidade 600

// two stepper motors one on each port
AF_Stepper motor1(200, 1);
AF_Stepper motor2(200, 2);

// you can change these to DOUBLE or INTERLEAVE or MICROSTEP!
// wrappers for the first motor!
void forwardstep1() {  
  motor1.onestep(FORWARD, MICROSTEP);
}
void backwardstep1() {  
  motor1.onestep(BACKWARD, MICROSTEP);
}
// wrappers for the second motor!
void forwardstep2() {  
  motor2.onestep(FORWARD, MICROSTEP);
}
void backwardstep2() {  
  motor2.onestep(BACKWARD, MICROSTEP);
}

// Motor shield has two motor ports, now we'll wrap them in an AccelStepper object
AccelStepper stepper1(forwardstep1, backwardstep1);
AccelStepper stepper2(forwardstep2, backwardstep2);

void setup()
{  
    stepper1.setMaxSpeed(velocidade);
    stepper1.setSpeed(velocidade);  


    
    stepper2.setMaxSpeed(-velocidade);
    stepper2.setSpeed(-velocidade); 
    
}

void loop()
{
    stepper1.runSpeed();
    stepper2.runSpeed();

}
