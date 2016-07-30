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

V13BT::V13BT(){
    _flagRec = false;
    _bufRec = "";
    _delaySendStatus = DELAYSEND_STATUS;
    _prevDelaySendStatus = 0 ;
    _bluetoothSerial =  new SoftwareSerial( A1, A0 );
}


void V13BT::begin(int speed){
    _bluetoothSerial->begin( speed );
    
}

void V13BT::update(boolean mode, int etat, int lastRec){
    if ( millis() - _prevDelaySendStatus > _delaySendStatus ){
        _prevDelaySendStatus = millis();
        //send status mais V13BT ne connais pas l'etat de M. VOR Marlay
    }
}

boolean V13BT::getFlagRec(){
    
}

boolean V13BT::getRec(String& buffRecu ){
    
}