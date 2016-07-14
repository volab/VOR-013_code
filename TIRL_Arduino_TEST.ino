// 
// add bp and led to start
// majorLee 5/3
// Ajoute d'un tableau de lettres
// Changement de broche du L_stepper validé 8/7/16
// reprise intégration SD carte
// Programmation orientée objet


#include <Servo.h>
//#include "letters.h"
#define TABLETTERMAXLIGN 25
/*
** MOSI - pin 11
** MISO - pin 12
** CLK - pin 13
** CS - pin 10
** 9 
** 8 servoPen
** 4,5,6,7 steper right
** 3 LED
** 2 Switch
*/
#include <SPI.h>
#include <SD.h>
#include "Tracer.h"
#include "Lettres.h"
#include "Flasher.h"


#define LED 3
#define SWITCH 2

int freeRam () {
    extern int __heap_start, *__brkval; 
    int v; 
    return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

Lettres lettreur; //ie traceur de lettre
Flasher led;

//----------------------------------------------------------------------------------------------------------------------
void setup() {
    Serial.begin(9600);
    randomSeed(analogRead(1));  

    dspl("setup : " __DATE__ " @ " __TIME__);

    pinMode( SWITCH, INPUT_PULLUP);

    /* sample code à concerver
    led1.begin( 13, 10, 500 );
    for ( ; led.getChangeStateCpt() < 100; ){
        led.update();
    }
    */

    
    //------------------------------------------------------------------------------------------------------------------
    // sabordage en cas d'échec ! avec LED clignotante
    if (!SD.begin(10)) {
        Serial.println(F("initialization failed!"));
        led.begin( LED, 20, 200 );
        while (1){
            led.update();
        }
    }
    lettreur.begin();  
#ifdef DEBUG    
    while(1);
#endif
    delay(1000);
    
}

String aEcrire="VOLAB";


//----------------------------------------------------------------------------------------------------------------------
void loop(){ 
    // attente appui sur le bouton poussoir
    led.begin( LED, 200, 200);
    while( digitalRead( SWITCH )){
        led.update();
    }
    led.stop();
    delay(1000);
    
    //Ecriture du texte
    for (int i = 0; i< aEcrire.length(); i++){
        Serial.println(  aEcrire.charAt(i) );
        lettreur.traceLettre( aEcrire.charAt(i) );
    }

    //done();      // releases stepper motor
    while(1);    // wait for reset
}







