#ifndef LETTRES_CLASS_H
#define LETTRES_CLASS_H

#include <SD.h>

#define sp(X) Serial.print(X)
#define spl(X) Serial.println(X)

//global enum
enum{ PD, PU, FW, TR, TL };

class Lettres{
 


 
    private:
    char _carac;
    int _nbrCommandes ;
    byte _bufferCommandes[30][2];
    int readLettre();
    File _myFile;
    String fileNameConstructor( );
    int fromEnumCommande( String commande);
};

#endif