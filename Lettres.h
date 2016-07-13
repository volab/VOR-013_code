#ifndef LETTRES_CLASS_H
#define LETTRES_CLASS_H


#include "Tracer.h"

#include "debugSerialPort.h"



#include "cmdEnum.h"


// heritage public : ref :
// http://www.bruno-garcia.net/www/Cours/heritage.html#syntaxe
class Lettres : public Tracer {
    public:
    Lettres( );
    //void setLettre( char c ){ _carac = c; };
    void traceLettre( char c );
 
    private:
    char _carac;

};

#endif