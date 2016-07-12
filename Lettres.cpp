#include "Lettres.h"

// 11/7 : decision de fonctionner avec begin dans Traceur 
// plutot que dans le constructeur
Lettres::Lettres( ){
    // _carac = toupper (c);
    // traceLettre();
}

void Lettres::traceLettre(char c){
    _carac = c ;
    sp(F("Trace lettre : ")); spl(_carac);
    readLettre();
    sp(F("nbr cmd = "));spl(_nbrCommandes);
    //spl("nbr cmd = " String(_nbrCommandes) );
    //printBufferCmd();
    //tracerDebug();
    //--------------------------------------------------------------------------

// byte _bufferCommandes[NBRCMDMAX][2];
// void trace(int cmd, int param);
    for(int x=0; x < _nbrCommandes; x++){
        trace( _bufferCommandes[x][0], _bufferCommandes[x][1] );
    }
   
    //--------------------------------------------------------------------------
}



void Lettres::printBufferCmd(){
    for (int i = 0; i< _nbrCommandes; i++){
        sp( "cmd : ");sp( _bufferCommandes[i][0] );
        sp( ", ");spl(_bufferCommandes[i][1]);
    }
}

int Lettres::fromEnumCommande( String commande){
    if (commande == "PD") return PD;
    if (commande == "PU") return PU;
    if (commande == "FW") return FW;
    if (commande == "TR") return TR;
    if (commande == "TL") return TL;  
}


//----------------------------------------------------------------------------------------------------------------------
// methode : filenameContructor
// cree le nom de fichier pour acceder a la lettre
// le lettre est convertie en majuscules
// pas de verification !
String Lettres::fileNameConstructor( ){
    _carac = toupper( _carac );
    return String("letters/")+_carac+String(".txt");
}


//----------------------------------------------------------------------------------------------------------------------
// methode readLetter
// in:
//  char lettre
// out:
// 0: echec
// ou nombre de commandes
// renseigne le membre prive : _bufferCommandes[30][2];
int Lettres::readLettre(){
    String fileName = fileNameConstructor( );
    String lettre = ""; //chaine des commandes
    //--------------------------------------------------------------------------
    // debut debug function read lettre et surtout conversion ASCII to enum
    _myFile = SD.open(fileName, FILE_READ);
    byte octetlu;
    while (_myFile.available()) {
        octetlu = _myFile.read();
        lettre.concat((char)octetlu);
        //Serial.println(octetlu);
    }
    _myFile.close();
    Serial.println( lettre ) ;
    int offset1 = 0;
    int offset2 = 0;
    int pos1 = lettre.indexOf('{', offset1);
    _nbrCommandes = 0;
    while (pos1 != -1 && _nbrCommandes <= NBRCMDMAX){
        //lettre est conserve intacte
        //parcours de lettre avec offset1 et 2
        int pos2 = lettre.indexOf('}', offset2);
        String sousChaine = lettre.substring(pos1+1, pos2);
        //spl( sousChaine );
        offset1 = pos1+2;
        offset2 = pos2+1;
        // recherche de la sous-chaine commande
        int posVirgule = sousChaine.indexOf(',');
        String commande = sousChaine.substring(0, posVirgule );
        //sp(F("Commande : ")); sp( commande );
        //cmdBuffer[nbrCommandes][0] = (byte)sousChaine.substring(0, sousChaine.indexOf(','))
        _bufferCommandes[_nbrCommandes][0] = fromEnumCommande(commande);
        byte parametre = (byte)sousChaine.substring( posVirgule + 1 ).toInt();
        //sp(F(" - Parametre = "));spl(parametre);
        _bufferCommandes[_nbrCommandes][1] = parametre;
        pos1 = lettre.indexOf('{', offset1);
        _nbrCommandes += 1 ;
    }

    if ( _nbrCommandes <= NBRCMDMAX )return _nbrCommandes;
    else return 0;
}
