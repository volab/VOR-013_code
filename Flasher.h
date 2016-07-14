#ifndef LEDFLASHER_H
#define LEDFLASHER_H



class Flasher {
    public:
    void stop();
    Flasher(){};
    void begin( int pin, unsigned long ton, unsigned long toff );
    void update();
    int getChangeStateCpt(){ return _changeStateCpt; }
    
    private:
    unsigned long _ton;
    unsigned long _toff;
    int _pin;
    unsigned long _previousMillis;
    int _ledState ;
    unsigned long _changeStateCpt;
    
};

#endif