//----------------------------------------------------------------------------------------------------------------------
// Class Tracer.
// Joel - MajorLee- Soranzo
// le 10/07/2016
// VoLAB by VoRoBoTics
//----------------------------------------------------------------------------------------------------------------------
// class pour robot de desin, source Instructable


#include "Tracer.h"

int freeRam () {
    extern int __heap_start, *__brkval; 
    int v; 
    return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

//----------------------------------------------------------------------------------------------------------------------
//Constructor
Tracer::Tracer():
    _L_stepperPins( { (int)LSTEPPERPIN0, (int)LSTEPPERPIN1,\
                            (int)LSTEPPERPIN2, (int)LSTEPPERPIN3 })
{
    // 2 syntaxes possibles : dans la liste d'init ou  dans le corps
    _R_stepperPins[0] = (int)RSTEPPERPIN0;
    _R_stepperPins[1] = (int)RSTEPPERPIN1;
    _R_stepperPins[2] = (int)RSTEPPERPIN2;
    _R_stepperPins[3] = (int)RSTEPPERPIN3;

}

//----------------------------------------------------------------------------------------------------------------------
// void Tracer::tracerBegin(){
void Tracer::begin(){
    for(int pin=0; pin<4; pin++){
        pinMode(_L_stepperPins[pin], OUTPUT);
        digitalWrite(_L_stepperPins[pin], LOW);
        pinMode(_R_stepperPins[pin], OUTPUT);
        digitalWrite(_R_stepperPins[pin], LOW);
    }
    _penServo.write(PENUP);
    _upDownServopin = UDSERVOPIN; //quel est l'utilite de ce membre ?
    _penServo.attach(_upDownServopin);
    penup();
}


void Tracer::tracerDebug(){
#ifdef DEBUG
/*
    spl("into the tracer class");
    for (int i = 0; i < 4; i++){
        dsp( F("L_stepper_pin")); dsp(i);dsp(" = ");dspl(_L_stepperPins[i]);
    }
    for (int i = 0; i < 4; i++){
        dsp( F("R_stepper_pin")); dsp(i);dsp(" = ");dspl(_R_stepperPins[i]);
    }
    dsp(F("steps for 10 mm = "));dspl( step(10));
    */
#endif
}

//----------------------------------------------------------------------------------------------------------------------
// Méthodes de bas niveaux pour le pilotage des moteurs pas à pas
void Tracer::penup(){
    _penServo.attach(_upDownServopin);
    delay(20);
    _penServo.write(PENUP);
    delay(250);
    _penServo.detach();
}

void Tracer::pendown(){
    _penServo.attach(_upDownServopin);
    delay(20);  
    _penServo.write(PENDOWN);
    delay(250);
    _penServo.detach();
}

int Tracer::step(float distance){
    int steps = distance * STEPREV / (WHEELDIA * 3.1412); //24.61
    return steps;  
}

void Tracer::forward(float distance){
    int steps = step(distance);
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
        //correction déviation droite déterminée de manière empirique
        offsetRcpt += param;
        if (offsetRcpt >= 180 ){
            offsetRcpt = 0;
            param +=2;
        }
        right( (float) param );
        break;    
        case TL:
        left( (float) param );
        break;          
    }
}

//----------------------------------------------------------------------------------------------------------------------
// methode : filenameContructor
// cree le nom de fichier pour acceder a la lettre
// le lettre est convertie en majuscules
// pas de verification !
String Tracer::fileNameConstructor( String sousDir, String fileNameBase ){
    fileNameBase.toUpperCase();
    return String(sousDir)+"/"+fileNameBase+String(".hex");
}

//----------------------------------------------------------------------------------------------------------------------
// methode : pour debug
void Tracer::printBufferCmd(){
    dsp(F("Contenu du buffer de commandes :")); dspl( _nbrCommandes );
    for (int i = 0; i< _nbrCommandes; i++){
        sp( F("cmd : ") );sp( _bufferCommandes[i][0] );
        sp( F(", ") );spl(_bufferCommandes[i][1]);
    }
}


void Tracer::traceBuffer(){
        for(int x=0; x < _nbrCommandes; x++){
        trace( _bufferCommandes[x][0], _bufferCommandes[x][1] );
    }
}

//----------------------------------------------------------------------------------------------------------------------
// methode readBufferFromSD
// in:
//  sous-repertoire, base du nom de fichier
// out:
// 0: echec
// ou nombre de commandes
// renseigne le membre prive : _bufferCommandes[30][2];
int Tracer::readBufferFromSD( String sousDir, String fileNameBase ){
    String fileName = fileNameConstructor( sousDir, fileNameBase );
    dspl( fileName );
    _myFile = SD.open(fileName, FILE_READ);
    _nbrCommandes = 0;
    while (_myFile.available()) {
        _bufferCommandes[_nbrCommandes][0] = _myFile.read();
        _bufferCommandes[_nbrCommandes][1] = _myFile.read();
        _nbrCommandes++ ;
    }
    _myFile.close();
    dspl( freeRam() );
    if ( _nbrCommandes <= NBRCMDMAX )return _nbrCommandes;
    else return 0;
}

// That's all folks