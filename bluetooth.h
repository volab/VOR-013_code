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
#include <Arduino.h>
#include <SoftwareSerial.h>


class V13BT{

    private:
    //SoftwareSerial *_bluetoothSerial; // RX, TX
    SoftwareSerial _bluetoothSerial; // RX, TX
    boolean _flagRec;
    String _bufRec;
    long _delaySendStatus;
    long _prevDelaySendStatus;
    

    public:
    V13BT();
    void begin(int speed);
    void update(int mode, int etat, int lastRec);
    boolean getFlagRec();
    boolean getRec(String& buffRecu ); //si chaine recu alors vrai

    
};

#endif