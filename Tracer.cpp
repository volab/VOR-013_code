//----------------------------------------------------------------------------------------------------------------------
// myTracer pré-instancié en fin de fichier.
// Joel - MajorLee- Soranzo
// le 10/07/2016
// VoLAB by VoRoBoTics
//----------------------------------------------------------------------------------------------------------------------
// class pour robot de desin, source thingiverse


#include "Tracer.h"



//----------------------------------------------------------------------------------------------------------------------
//Constructor
Tracer::Tracer():
    _L_stepperPins( { (int)LSTEPPERPIN0, (int)LSTEPPERPIN1,\
                            (int)LSTEPPERPIN2, (int)LSTEPPERPIN3 })
{
    _penServo.write(PENUP);
    _upDownServopin = UDSERVOPIN; //quel est l'utilite de ce membre ?
    _penServo.attach(_upDownServopin);
    // _L_stepperPins[4] =  { (int)LSTEPPERPIN0, (int)LSTEPPERPIN1,
                            // (int)LSTEPPERPIN2, (int)LSTEPPERPIN3 };
    //_R_stepperPins[4] = { RSTEPPERPIN0, RSTEPPERPIN1, RSTEPPERPIN2, RSTEPPERPIN3 };
    _R_stepperPins[0] = (int)RSTEPPERPIN0;
    _R_stepperPins[1] = (int)RSTEPPERPIN1;
    _R_stepperPins[2] = (int)RSTEPPERPIN2;
    _R_stepperPins[3] = (int)RSTEPPERPIN3;
    for(int pin=0; pin<4; pin++){
        pinMode(_L_stepperPins[pin], OUTPUT);
        digitalWrite(_L_stepperPins[pin], LOW);
        pinMode(_R_stepperPins[pin], OUTPUT);
        digitalWrite(_R_stepperPins[pin], LOW);
    }
    penup();
}

//----------------------------------------------------------------------------------------------------------------------

void Tracer::tracerDebug(){
#ifdef DEBUG
    spl("into the tracer class");
    for (int i = 0; i < 4; i++){
        dsp( "L_stepper_pin"); dsp(i);dsp(" = ");dspl(_L_stepperPins[i]);
    }
    for (int i = 0; i < 4; i++){
        dsp( "R_stepper_pin"); dsp(i);dsp(" = ");dspl(_R_stepperPins[i]);
    }
    dsp("steps for 10 mm = ");dspl( step(10));
#endif
}

//----------------------------------------------------------------------------------------------------------------------
void Tracer::penup(){
    delay(250);
    _penServo.write(PENUP);
    delay(250);
}

void Tracer::pendown(){
    delay(250);  
    _penServo.write(PENDOWN);
    delay(250);
}

int Tracer::step(float distance){
    //int steps = distance * steps_rev / (wheel_dia * 3.1412); //24.61
    int steps = distance * STEPREV / (WHEELDIA * 3.1412); //24.61
    /*
Serial.print(distance);
Serial.print(" ");
Serial.print(steps_rev);
Serial.print(" ");  
Serial.print(wheel_dia);
Serial.print(" ");  
Serial.println(steps);
delay(1000);*/
    return steps;  
}


void Tracer::forward(float distance){
    int steps = step(distance);
    //Serial.print("forward : ");Serial.println(distance);
    for(int step=0; step<steps; step++){
        for(int mask=0; mask<4; mask++){
            for(int pin=0; pin<4; pin++){
                digitalWrite(_L_stepperPins[pin], _rev_mask[mask][pin]);
                digitalWrite(_R_stepperPins[pin], _fwd_mask[mask][pin]);
            }
            delay(DELAYTIME);
        } 
    }
}

void Tracer::backward(float distance){
    int steps = step(distance);
    for(int step=0; step<steps; step++){
        for(int mask=0; mask<4; mask++){
            for(int pin=0; pin<4; pin++){
                digitalWrite(_L_stepperPins[pin], _fwd_mask[mask][pin]);
                digitalWrite(_R_stepperPins[pin], _rev_mask[mask][pin]);
            }
            delay(DELAYTIME);
        } 
    }
}


void Tracer::right(float degrees){
    float rotation = degrees / 360.0;
    //Serial.print("right : ");Serial.println(degrees);
    // float distance = wheel_base * 3.1412 * rotation;
    float distance = WHEELBASE * 3.1412 * rotation;
    int steps = step(distance);
    for(int step=0; step<steps; step++){
        for(int mask=0; mask<4; mask++){
            for(int pin=0; pin<4; pin++){
                digitalWrite(_R_stepperPins[pin], _rev_mask[mask][pin]);
                digitalWrite(_L_stepperPins[pin], _rev_mask[mask][pin]);
            }
            delay(DELAYTIME);
        } 
    }   
}


void Tracer::left(float degrees){
    float rotation = degrees / 360.0;
    //Serial.print("left : ");Serial.println(degrees);
    //float distance = wheel_base * 3.1412 * rotation;
    float distance = WHEELBASE * 3.1412 * rotation;
    int steps = step(distance);
    for(int step=0; step<steps; step++){
        for(int mask=0; mask<4; mask++){
            for(int pin=0; pin<4; pin++){
                digitalWrite(_R_stepperPins[pin], _fwd_mask[mask][pin]);
                digitalWrite(_L_stepperPins[pin], _fwd_mask[mask][pin]);
            }
            delay(DELAYTIME);
        } 
    }   
}

void Tracer::done(){ // unlock stepper to save battery
    for(int mask=0; mask<4; mask++){
        for(int pin=0; pin<4; pin++){
            digitalWrite(_R_stepperPins[pin], LOW);
            digitalWrite(_L_stepperPins[pin], LOW);
        }
        delay(DELAYTIME);
    }
}

//----------------------------------------------------------------------------------------------------------------------
//protected
void Tracer::trace(int cmd, int param){
    //Serial.print(F("cmd = "));Serial.print( cmd );
    //Serial.print(" / ");Serial.println( param );
    static int offsetRcpt = 0;
    switch (cmd){
        default: // PU:
        penup();
        break;
        case PD:
        pendown();
        break;
        case FW:
        forward( (float) param );
        break;
        case TR:
        //correction déviation droite
        offsetRcpt += param;
        //Serial.print(F("TR cumul : ")); Serial.println( offsetRcpt );
        if (offsetRcpt >= 180 ){
            offsetRcpt = 0;
            param +=2;
            //Serial.print(F("Param corrige : ")); Serial.println( param );
        }
        right( (float) param );
        break;    
        case TL:
        left( (float) param );
        break;          
    }
}

Tracer mytracer;
