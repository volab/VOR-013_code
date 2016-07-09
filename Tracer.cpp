

#include "Tracer.h"



//----------------------------------------------------------------------------------------------------------------------
//Constructor
Tracer::Tracer(){
    _penServo.write(PENUP);
    _upDownServopin = UDSERVOPIN;
    _penServo.attach(_upDownServopin);
}

//----------------------------------------------------------------------------------------------------------------------
void Tracer::penup(){
    delay(250);
    //Serial.println("PEN_UP()");
    _penServo.write(PENUP);
    delay(250);
}

void Tracer::pendown(){
    delay(250);  
    //Serial.println("PEN_DOWN()");
    _penServo.write(PENDOWN);
    delay(250);
}



