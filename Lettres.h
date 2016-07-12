#ifndef LETTRES_CLASS_H
#define LETTRES_CLASS_H

#include <SD.h>
#include "Tracer.h"

#include "debugSerialPort.h"

#define NBRCMDMAX 30

#include "cmdEnum.h"


// heritage public : ref :
// http://www.bruno-garcia.net/www/Cours/heritage.html#syntaxe
class Lettres : public Tracer {
    public:
    Lettres( );
    void setLettre( char c ){ _carac = c; };
    void traceLettre( char c );
 
    private:
    char _carac;
    int _nbrCommandes ;
    byte _bufferCommandes[NBRCMDMAX][2];
    int readLettre();
    File _myFile;
    String fileNameConstructor( );
    int fromEnumCommande( String commande);
    
    void printBufferCmd();
};

#endif