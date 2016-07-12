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


#define LED 3
#define SWITCH 2

int freeRam () {
    extern int __heap_start, *__brkval; 
    int v; 
    return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

Lettres lettreur; //ie traceur de lettre

//----------------------------------------------------------------------------------------------------------------------
void setup() {
    Serial.begin(9600);
    randomSeed(analogRead(1));  

    dspl("setup : " __DATE__ " @ " __TIME__);

    pinMode( SWITCH, INPUT_PULLUP);
    pinMode( LED, OUTPUT );
    //penup();
    
    //------------------------------------------------------------------------------------------------------------------
    // sabordage en cas d'échec ! avec LED clignotante
    if (!SD.begin(10)) {
        Serial.println(F("initialization failed!"));
        return;
        while (1){
            digitalWrite( LED, !digitalRead(LED));
            delay(200);
        }
    }
    dsp( F("memoire dispo avant A : "));dspl( freeRam() );
    lettreur.begin();
    lettreur.setLettre( 'a' );
    lettreur.traceLettre();
    //mytracer.tracerDebug();
    
    dsp( F("memoire dispo avant B : "));dspl( freeRam() );
    // Lettres( 'b' );
    lettreur.setLettre( 'b' );
    lettreur.traceLettre();
    dsp( F("memoire dispo apres B : "));dspl( freeRam() );
    Serial.println(F("fin_2020") );
    delay(1000);
}

String aEcrire="VOLAB";


//----------------------------------------------------------------------------------------------------------------------
void loop(){ 
    // attente appui sur le bouton poussoir
    while( digitalRead( SWITCH )){
        digitalWrite( LED, !digitalRead(LED));
        delay(200);
    }
    digitalWrite( LED, LOW );
    delay(1000);
    
    //Ecriture du texte
    for (int i = 0; i< aEcrire.length(); i++){
        Serial.println(  aEcrire.charAt(i) );
        //    traceLetter( aEcrire.charAt(i) );
    }

    //done();      // releases stepper motor
    while(1);    // wait for reset
}

// ----- TRACER FUNCTIONS -----------
/*


void traceLetter(char c){

}
*/
// ----- HELPER FUNCTIONS -----------







