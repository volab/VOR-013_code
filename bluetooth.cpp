//----------------------------------------------------------------------------------------------------------------------
// Projet VOR-013 Vor Marley the drawing Robots
// Major Lee
// CC-0
// Juillet 2016
//----------------------------------------------------------------------------------------------------------------------
// classe chargee des comm bluetooth
//----------------------------------------------------------------------------------------------------------------------
#include "bluetooth.h"
//#include "VOR13.h"


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
    _flagBTconnecte = false;
    _timeoutConnexion = 0;  
}

//----------------------------------------------------------------------------------------------------------------------
// cette methode est unpeu la bonne a tout faire
// elle emet la trame et la recoit
//void V13BT::update(int mode, int etat, int lastRec){
void V13BT::update( String trame ){
    //*********************EMISSION*************************************************************************************
    if  ( _flagBTconnecte && ( millis() - _prevDelaySendStatus > _delaySendStatus ) ){
        _prevDelaySendStatus = millis();
        trame += ", " + String( _trameNum );
        //_bluetoothSerial->println( trame);
        _bluetoothSerial.println( trame );
        _trameNum++;
    }
    //*********************FILTRE CR, LF********************************************************************************
    if (_prevChar == 0xD || _prevChar == 0xA ){
        _flagRec = true;
        while ( _bluetoothSerial.available() ) _bluetoothSerial.read(); //flush buffer
        _prevChar = 0;
    }

    //*********************test Mode Connecte***************************************************************************
    if ( _flagRec && _bufRec == "syncVOR13" ){
        _flagBTconnecte = true;
        _flagRec = false;
        _timeoutConnexion = millis();
        dspl("Mode Con");
        _bufRec = "";
    }
    //*********************RECEPTION************************************************************************************
    if ( !_flagRec && _bluetoothSerial.available() ){
        
        char c = _bluetoothSerial.read();
        //sp("char = ");SERIALDEBUG.println( c, HEX );
        if ( c !=  0xD && c != 0xA ){
            _bufRec += String(c);
        }
        _prevChar = c;
        _timeoutConnexion = millis();
    }
    
    if ( _flagBTconnecte && (millis() - _timeoutConnexion) >= (DELAYTIMEOUTCONNEXION * 1000) ){
        _flagBTconnecte = false ; // disconnected
        dspl("Mode dec");
    }
}

boolean V13BT::getFlagRec(){
    return _flagRec;
}

boolean V13BT::getRec(String& buffRecu ){
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