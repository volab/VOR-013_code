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
// integration bluetooth débordement de la pile !!!!
// a nécessité de changer de philo.


#include <Servo.h>

#define TABLETTERMAXLIGN 25
#include "Lettres.h"
#include "Flasher.h"
#include "VOR13.h"
#include "bluetooth.h"

#define LED 3
#define SWITCH 2

VOR13 robot; //to keep the robot state (ben oui un peu d'anglais !)
Lettres lettreur; //ie traceur de lettre
Flasher led;
V13BT bluetoothChanel ;

//----------------------------------------------------------------------------------------------------------------------
void setup() {
    Serial.begin(9600);
    randomSeed(analogRead(1));  
    robot.begin();
    dspl("setup : " __DATE__ " @ " __TIME__);

    pinMode( SWITCH, INPUT_PULLUP);
    bluetoothChanel.begin(9600);

    /* sample code à concerver pour la beautee
    led1.begin( 13, 10, 500 );
    for ( ; led.getChangeStateCpt() < 100; ){
        led.update();
    }
    */

    //------------------------------------------------------------------------------------------------------------------
    // sabordage en cas d'échec ! avec LED flash rapide
    if (!SD.begin(10)) {
        Serial.println(F("initialization failed!"));
        led.begin( LED, 20, 100 );
        while (1){
            led.update();
        }
    }
    lettreur.begin();   
}

//----------------------------------------------------------------------------------------------------------------------
void loop(){ 
    String recTrame ="";
    
    // attente appui sur le bouton poussoir
    led.begin( LED, 300, 300);
    boolean go = false;
    while(!go ){
        led.update();
        bluetoothChanel.update( robot.buildStateTrame() );
        if ( bluetoothChanel.getRec( recTrame )){
            //bluetoothChanel.echoTrame( recTrame );
            robot.interpreteTrame( recTrame );
        }
        go = !digitalRead( SWITCH ) | robot.go();
    }
    led.stop();
    delay(500);
    robot.setState( ETAT_WORK );
    //Ecriture du texte
    if ( robot.getMode() == MODE_ECRIT ){
        for (int i = 0; i< robot.get_aEcrire().length(); i++){
            lettreur.traceLettre( robot.get_aEcrire().charAt(i) );
            bluetoothChanel.update( robot.buildStateTrame() );
        }
        //dégagement
        lettreur.degage(90, 110);
    } else { //mode dessin
        lettreur.dessine( robot.get_aDessiner() );
        //dégagement
        lettreur.degage(90, 160);
    }

    
    robot.setState( ETAT_FINI );
    //done();      // releases stepper motor
    while(1) bluetoothChanel.update( robot.buildStateTrame() );    // wait for reset
}







