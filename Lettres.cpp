#include "Lettres.h"


int Lettres::fromEnumCommande( String commande){
    if (commande == "PD") return PD;
    if (commande == "PU") return PU;
    if (commande == "FW") return FW;
    if (commande == "TR") return TR;
    if (commande == "TL") return TL;  
}


//----------------------------------------------------------------------------------------------------------------------
// fonction : filenameContructor
// cree le nom de fichier pour acceder a la lettre
// le lettre est convertie en majuscules
// pas de verification !
String Lettres::fileNameConstructor( ){
    _carac = toupper( _carac );
    return String("letters/")+_carac+String(".txt");
}


//----------------------------------------------------------------------------------------------------------------------
// Fonction readLetter
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
    while (pos1 != -1){
        //lettre est conserve intacte
        //parcours de lettre avec offset1 et 2
        int pos2 = lettre.indexOf('}', offset2);
        String sousChaine = lettre.substring(pos1+1, pos2);
        spl( sousChaine );
        offset1 = pos1+2;
        offset2 = pos2+1;
        // recherche de la sous-chaine commande
        int posVirgule = sousChaine.indexOf(',');
        String commande = sousChaine.substring(0, posVirgule );
        sp("Commande : "); sp( commande );
        //cmdBuffer[nbrCommandes][0] = (byte)sousChaine.substring(0, sousChaine.indexOf(','))
        _bufferCommandes[_nbrCommandes][0] = fromEnumCommande(commande);
        byte parametre = (byte)sousChaine.substring( posVirgule + 1 ).toInt();
        sp(" - Parametre = ");spl(parametre);
        _bufferCommandes[_nbrCommandes][1] = parametre;
        pos1 = lettre.indexOf('{', offset1);
        _nbrCommandes += 1 ;
    }
    Serial.print("Nombre de commande = "); Serial.println(_nbrCommandes);
    return _nbrCommandes;
}
