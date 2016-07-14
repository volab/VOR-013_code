#include "Flasher.h"
#include <Arduino.h>
#include "debugSerialPort.h"


void Flasher::begin( int pin, unsigned long ton, unsigned long toff){
    _pin = pin;
    _ton = ton;
    _toff = toff;
    pinMode( _pin, OUTPUT);
    _ledState = 0;
    _previousMillis = 0;
    _changeStateCpt = 0;
    digitalWrite( _pin, _ledState );
    
}

void Flasher::update(){
    if ( (millis()-_previousMillis  > _ton) && (_ledState == 1) ){
        _ledState = 0;
        _previousMillis = millis();
        digitalWrite( _pin, _ledState );
        _changeStateCpt++;
    } else if ( (millis()-_previousMillis  > _toff) && (_ledState == 0) ){
        _ledState = 1 ;
        _previousMillis = millis();
        digitalWrite( _pin, _ledState );
        _changeStateCpt++;
    }  
}

void Flasher::stop(){
    digitalWrite( _pin, 0 );
    _ledState = 0;
    pinMode( _pin, INPUT );
    _changeStateCpt = 0;
}