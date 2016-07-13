#ifndef TRACER_H
#define TRACER_H

#include <Arduino.h>
#include <Servo.h>
#include <SD.h>
#include "cmdEnum.h"
#include "debugSerialPort.h"

#define WHEELDIA 63 //mm
#define WHEELBASE 112 //ecartement en mm
#define STEPREV 512 //nbr de pas par tour
#define UDSERVOPIN 8 //angle du servo pour monter le crayon
#define PENDOWN 20 //angle du servo pour abaisser le crayon
#define PENUP 80

#define DELAYTIME 2 //ms

#define LSTEPPERPIN0 A5
#define LSTEPPERPIN1 A3
#define LSTEPPERPIN2 A2
#define LSTEPPERPIN3 A4

#define RSTEPPERPIN0 4
#define RSTEPPERPIN1 6
#define RSTEPPERPIN2 7
#define RSTEPPERPIN3 5

#define NBRCMDMAX 30

class Tracer{
    public:
    Tracer();
    // void tracerBegin();
    void begin();
    void tracerDebug();
    void printBufferCmd();
    
    protected:
    void trace(int cmd, int param);
    int readBufferFromSD( String sousDir, String fileNameBase );
    void traceBuffer();
    
    private:
    int _upDownServopin; //quel est l'utilite de ce membre ?
    Servo _penServo;
    int _L_stepperPins[4];
    int _R_stepperPins[4];
    int _nbrCommandes ;
    byte _bufferCommandes[NBRCMDMAX][2];
    File _myFile;
    
    const int _fwd_mask[4][4] =  {{1, 0, 1, 0},
                                {0, 1, 1, 0},
                                {0, 1, 0, 1},
                                {1, 0, 0, 1}};
    const int _rev_mask[4][4] =   {{1, 0, 0, 1},
                                {0, 1, 0, 1},
                                {0, 1, 1, 0},
                                {1, 0, 1, 0}};
    
    //methodes privees
    void penup();
    void pendown();    
    int step(float distance);
    void forward(float distance);
    void backward(float distance);
    void right(float degrees);
    void left(float degrees);
    void done();

    int readBufferFromSD();

    //String fileNameConstructor( );
    String fileNameConstructor( String sousDir, String fileNameBase );
    int fromEnumCommande( String commande);
    
    
    
    
};

// extern Tracer mytracer;
#endif