//----------------------------------------------------------------------------------------------------------------------
// Projet VOR-013 Vor Marley the drawing Robots
// Major Lee
// CC-0
// Juillet 2016
//----------------------------------------------------------------------------------------------------------------------
// 
// add bp and led to start
// majorLee 5/3
// Ajoute d'un tableau de lettres
// Changement de broche du L_stepper validé 8/7/16
// reprise intégration SD carte
// Programmation orientée objet


//#include <Servo.h>
//#include "letters.h"
//#define TABLETTERMAXLIGN 25
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
//#include "bluetooth.h"
//#include <SPI.h>
//#include <SD.h>
//#include "Tracer.h"


#include "Lettres.h"
#include "Flasher.h"
#include "VOR13.h"

#include "bluetooth.h"


#define LED 3
#define SWITCH 2



Lettres lettreur; //ie traceur de lettre
Flasher led;
V13BT bluetoothChanel ;
#define RESERVEMEM 5
uint8_t reserveMemoire[RESERVEMEM];

//----------------------------------------------------------------------------------------------------------------------
void setup() {
    Serial.begin(9600);
    randomSeed(analogRead(1));  

    dspl("setup : " __DATE__ " @ " __TIME__);

    pinMode( SWITCH, INPUT_PULLUP);
    for (int i = 0 ; i< RESERVEMEM; i++){
        reserveMemoire[i] = i;
    }

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
    bluetoothChanel.begin(9600);
/*    
#ifdef DEBUG    
    while(1);
#endif
*/
    delay(1000);
    
}

String aEcrire="VOLAB";
//String aEcrire="ABCD";
int mode = MODE_ECRIT; // mode par defaut
int etat = ETAT_ATTENTE;
int recState = NOREC;
long toto;

//----------------------------------------------------------------------------------------------------------------------
void loop(){ 
    String recTrame ="";
    
    // attente appui sur le bouton poussoir
    led.begin( LED, 200, 200);
    while( digitalRead( SWITCH )){
        led.update();
        
        //bluetoothChanel.update(mode, etat, recState);
/*        
        if ( bluetoothChanel.getRec( recTrame )){
            //bluetoothChanel.echoTrame( recTrame );
            //sp("quelques chose a dire ? "); spl( recTrame);
            //recState = NOREC;
            //toto = 3;
        } 
        */
    }
    led.stop();
    //bluetoothChanel.end();
    //delete( &bluetoothChanel );
    delay(1000);
    
    //Ecriture du texte
    for (int i = 0; i< aEcrire.length(); i++){
        Serial.println(  aEcrire.charAt(i) );
        lettreur.traceLettre( aEcrire.charAt(i) );
    }

    //done();      // releases stepper motor
    while(1);    // wait for reset
}







