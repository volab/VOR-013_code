#ifndef LETTRES_CLASS_H
#define LETTRES_CLASS_H

#include <SD.h>

#include "debugSerialPort.h"

#define NBRCMDMAX 30

#include "cmdEnum.h"

class Lettres : Tracer {
    public:
    Lettres( char c );


 
    private:
    char _carac;
    int _nbrCommandes ;
    byte _bufferCommandes[NBRCMDMAX][2];
    int readLettre();
    File _myFile;
    String fileNameConstructor( );
    int fromEnumCommande( String commande);
    void traceLettre();
    void printBufferCmd();
};

#endif