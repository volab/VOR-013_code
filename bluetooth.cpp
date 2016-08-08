//----------------------------------------------------------------------------------------------------------------------
// Projet VOR-013 Vor Marley the drawing Robots
// Major Lee
// CC-0
// Juillet 2016
//----------------------------------------------------------------------------------------------------------------------
// classe chargee des comm bluetooth
//----------------------------------------------------------------------------------------------------------------------
#include "bluetooth.h"
#include "VOR13.h"

V13BT::V13BT(): _bluetoothSerial( A1, A0 ){
//V13BT::V13BT() {
    _flagRec = false;
    _bufRec = "";
    _delaySendStatus = DELAYSEND_STATUS;
    _prevDelaySendStatus = 0 ;
    //comme cela, ca marche pas:
    //SoftwareSerial _bluetoothSerial( A1, A0 ); //
    
}


void V13BT::begin(int speed){
    //Syntaxe possible en utilisant les pointeurs et pas l'init dans la
    // liste d'intialisation du constructeur
    //_bluetoothSerial =  new SoftwareSerial( A1, A0 );
    //_bluetoothSerial->begin( speed );
    _bluetoothSerial.begin( speed );
    _prevChar = 0;
    _trameNum=0;
    
}

void V13BT::update(int mode, int etat, int lastRec){
    String trame;
    if ( millis() - _prevDelaySendStatus > _delaySendStatus ){
        _prevDelaySendStatus = millis();
        //send status mais V13BT ne connais pas l'etat de M. VOR Marlay
        switch (mode){
            case MODE_ECRIT:
            trame = "Mode ecrit,";
            break;
            case MODE_DESSINE:
            trame = "Mode dessin,";
            break;
        }
        switch (etat){
            case ETAT_ATTENTE:
            trame += "en attente, ";
            break;
            case ETAT_WORK:
            trame += "en cours, ";
            break;
            case ETAT_FINI:
            trame += "fini, ";
            break;
        }
        switch (lastRec){
            case NOREC:
            trame += "rien recu";
            break;
            case LASTREC_GO:
            trame += "recu GO";
            break;
            case LASTREC_DESSINE:
            trame += "recu dessine";
            break;
            case LASTREC_TEXTE:
            trame += "recu texte";
            break;
            case LASTREC_MODEDESSIN:
            trame += "recu mode dessin";
            break;
            case LASTREC_MODETEXTE:
            trame += "recu mode texte";
            break;
            case LASTREC_UNKNOW:
            trame += "commande inconnue";
            break;
        }
        trame += ", " + String( _trameNum );
        //_bluetoothSerial->println( trame);
        _bluetoothSerial.println( trame);
        _trameNum++;
    }
        // ne faire que si _bufRec a ete vide
        // ou flagRec = false;

    //if ( _bluetoothSerial->available() ){
    if ( !_flagRec && _bluetoothSerial.available() ){
        //char c = _bluetoothSerial->read();
        
        char c = _bluetoothSerial.read();
        if ( c !=  '\n' && c != 0xA ){
            _bufRec += String(c);
            //sp( "char recu : "); spl( _bufRec );
        } else {
            if (_prevChar != '\n' && _prevChar != 0xA ) _flagRec = true;
            //sp("flagrec = "); spl( _flagRec);
        }
        _prevChar = c;
        // last char rec pour tester les CR, LF
        // CR ou LF seul
    }    
}




boolean V13BT::getFlagRec(){
    return _flagRec;
}

//boolean V13BT::getRec(String& buffRecu ){
boolean V13BT::getRec(String buffRecu ){
    if ( ! _flagRec ) return false;
    //sp( "bufrec = ");spl( _bufRec );
    buffRecu = _bufRec;
    _bufRec = "";
    _flagRec = false ; // reset flag rec
    return true;
}

void V13BT::echoTrame(String trame){
    _bluetoothSerial.println( trame);
}