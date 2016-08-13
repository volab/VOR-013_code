//----------------------------------------------------------------------------------------------------------------------
// Projet VOR-013 Vor Marley the drawing Robots
// Major Lee
// CC-0
// Juillet 2016
//----------------------------------------------------------------------------------------------------------------------
// entete classe chargee des comm bluetooth
//----------------------------------------------------------------------------------------------------------------------
#ifndef V13BT_H
#define V13BT_H

#define DELAYSEND_STATUS 5000 //ms
#define DELAYTIMEOUTCONNEXION 20 //en seconde
#include <Arduino.h>
#include <SoftwareSerial.h>
#include "debugSerialPort.h"

class V13BT{

    private:
    //SoftwareSerial *_bluetoothSerial; // RX, TX
    SoftwareSerial _bluetoothSerial; // RX, TX
    boolean _flagRec;
    String _bufRec;
    long _delaySendStatus;
    long _prevDelaySendStatus;
    char _prevChar;
    long _trameNum;
    boolean _flagBTconnecte;
    long _timeoutConnexion;
    
    public:
    V13BT();
    void begin(int speed);
    void update( String trameEtat ); //update : emet et recoit
    boolean getFlagRec();
    boolean getRec(String& buffRecu ); //si chaine recu alors vrai
    void echoTrame(String trame);
};

#endif