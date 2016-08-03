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
    //_bluetoothSerial =  new SoftwareSerial( A1, A0 );
    //_bluetoothSerial->begin( speed );
    _bluetoothSerial.begin( speed );
    
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
        }
        //_bluetoothSerial->println( trame);
        _bluetoothSerial.println( trame);
        // ne faire que si _bufRec a ete vide
        //if ( _bluetoothSerial->available() ){
        if ( _bluetoothSerial.available() ){
            //char c = _bluetoothSerial->read();
            char c = _bluetoothSerial.read();
            if ( c !=  '\n' && c != 0xA ){
                _bufRec += String(c);
            } else {
                _flagRec = true;
            }
            // last char rec pour tester les CR, LF
            // CR ou LF seul
        }
    }
}




boolean V13BT::getFlagRec(){
    
}

boolean V13BT::getRec(String& buffRecu ){
    _flagRec = false ; // reset flag rec
    _bufRec = "";
}