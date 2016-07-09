#ifndef TRACER_H
#define TRACER_H

#include <Arduino.h>
#include <Servo.h>


#define WHEELDIA 63 //mm
#define WHEELBASE 112 //ecartement en mm
#define STEPREV 512
#define UDSERVOPIN 8
#define PENDOWN 20
#define PENUP 80

class Tracer{
    public:
    Tracer();
    
    private:
    int _upDownServopin;
    Servo _penServo;
    int _L_stepperPins[4];
    int _R_stepperPins[4];
    void penup();
    void pendown();
    
};

extern Tracer tracer;
#endif