// 
// add bp and led to start
// majorLee 5/3
// Ajoute d'un tableau de lettres
// Changement de broche du L_stepper validé 8/7/16
// reprise intégration SD carte


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

Tracer tracer;

//File myFile;
int nbrCommandes = 0;
byte cmdBuffer[30][2];

// setup servo
//int servoPin = A0;
int servoPin = 8;
int PEN_DOWN = 20; // angle of servo when pen is down
int PEN_UP = 80;   // angle of servo when pen is up
Servo penServo;

float wheel_dia=63; //    # mm (increase = spiral out)
float wheel_base=112; //    # mm (increase = spiral in, ccw) 
//int steps_rev=128; //        # 512 for 64x gearbox, 128 for 16x gearbox
int steps_rev=512;
int delay_time=2; //         # time between steps in ms

#define LED 3
#define SWITCH 2
// Stepper sequence org->pink->blue->yel
//int L_stepper_pins[] = {12, 10, 9, 11};
int L_stepper_pins[] = { A5, A3, A2, A4 };
int R_stepper_pins[] = { 4, 6, 7, 5 };

int fwd_mask[][4] =  {{1, 0, 1, 0},
    {0, 1, 1, 0},
    {0, 1, 0, 1},
    {1, 0, 0, 1}};

int rev_mask[][4] =  {{1, 0, 0, 1},
    {0, 1, 0, 1},
    {0, 1, 1, 0},
    {1, 0, 1, 0}};
//

/*
int figure[][2]={ {FW,50}, {TL,60},
                {FW,50}, {TL,60},
                {FW,50}, {TL,60},
                {FW,50}, {TL,60},
                {FW,50}, {TL,60},
                {FW,50}, {TL,60} };                  
*/





/*
int readLettre( char caractere ){

}
*/


void setup() {
    Serial.begin(9600);
    randomSeed(analogRead(1));  
    for(int pin=0; pin<4; pin++){
        pinMode(L_stepper_pins[pin], OUTPUT);
        digitalWrite(L_stepper_pins[pin], LOW);
        pinMode(R_stepper_pins[pin], OUTPUT);
        digitalWrite(R_stepper_pins[pin], LOW);
    }
    penServo.write(PEN_UP);
    penServo.attach(servoPin);
    //sp(F("setup : "));sp(__DATE__); spl(__TIME__);
    spl("setup : " __DATE__ " @ " __TIME__);
    
    //sp("file name : ");spl( fileNameConstructor ('a'));
    pinMode( SWITCH, INPUT_PULLUP);
    pinMode( LED, OUTPUT );
    //penup();
    
    //--------------------------------------------------------------------------
    // sabordage en cas d'échec ! avec LED clignotante
    if (!SD.begin(10)) {
        Serial.println("initialization failed!");
        return;
        while (1){
            digitalWrite( LED, !digitalRead(LED));
            delay(200);
        }
    }
    Lettres( 'a' );
    
    Serial.println("fin_2020");
    delay(1000);
}

String aEcrire="VOLAB";

void loop(){ // draw a calibration box 4 times
    while( digitalRead( SWITCH )){
        digitalWrite( LED, !digitalRead(LED));
        delay(200);
    }
    digitalWrite( LED, LOW );
    delay(1000);
    for (int i = 0; i< aEcrire.length(); i++){
        Serial.println(  aEcrire.charAt(i) );
        //    traceLetter( aEcrire.charAt(i) );
    }



    done();      // releases stepper motor
    while(1);    // wait for reset
}

// ----- TRACER FUNCTIONS -----------
/*
void trace(int cmd, int param){
Serial.print(F("cmd = "));Serial.print( cmd );
Serial.print(" / ");Serial.println( param );
static int offsetRcpt = 0;
switch (cmd){
    default: // PU:
    penup();
    break;
    case PD:
    pendown();
    break;
    case FW:
    forward( (float) param );
    break;
    case TR:
    //correction déviation droite
    offsetRcpt += param;
    Serial.print(F("TR cumul : ")); Serial.println( offsetRcpt );
    if (offsetRcpt >= 180 ){
        offsetRcpt = 0;
        param +=2;
        Serial.print(F("Param corrige : ")); Serial.println( param );
    }
    right( (float) param );
    break;    
    case TL:
    left( (float) param );
    break;          
}
}

void traceLetter(char c){
byte *letterTable;
int nbrCmd;
switch (c){
    case 'A':
    letterTable = &letter_A[0][0];
    nbrCmd = sizeof(letter_A) / sizeof( *letter_A );
    break;
    case 'B':
    letterTable = &letter_B[0][0];
    nbrCmd = sizeof(letter_B) / sizeof( *letter_B );
    break;
    case 'C':
    letterTable = &letter_C[0][0];
    nbrCmd = sizeof(letter_C) / sizeof( *letter_C );
    break;
    case 'D':
    letterTable = &letter_D[0][0];
    nbrCmd = sizeof(letter_D) / sizeof( *letter_D );
    break;
    case 'E':
    letterTable = &letter_E[0][0];
    nbrCmd = sizeof(letter_E) / sizeof( *letter_E );
    break;
    case 'F':
    letterTable = &letter_F[0][0];
    nbrCmd = sizeof(letter_F) / sizeof( *letter_F );
    break;
    case 'G':
    letterTable = &letter_G[0][0];
    nbrCmd = sizeof(letter_G) / sizeof( *letter_G );
    break;
    case 'H':
    letterTable = &letter_H[0][0];
    nbrCmd = sizeof(letter_H) / sizeof( *letter_H );
    break;
    case 'I':
    letterTable = &letter_I[0][0];
    nbrCmd = sizeof(letter_I) / sizeof( *letter_I );
    break;
    case 'J':
    letterTable = &letter_J[0][0];
    nbrCmd = sizeof(letter_J) / sizeof( *letter_J );
    break;
    case 'K':
    letterTable = &letter_K[0][0];
    nbrCmd = sizeof(letter_K) / sizeof( *letter_K );
    break;
    case 'L':
    letterTable = &letter_L[0][0];
    nbrCmd = sizeof(letter_L) / sizeof( *letter_L );
    break;
    case 'M':
    letterTable = &letter_M[0][0];
    nbrCmd = sizeof(letter_M) / sizeof( *letter_M );
    break;
    case 'N':
    letterTable = &letter_N[0][0];
    nbrCmd = sizeof(letter_N) / sizeof( *letter_N );
    break;
    case 'O':
    letterTable = &letter_O[0][0];
    nbrCmd = sizeof(letter_O) / sizeof( *letter_O );
    break;
    case 'P':
    letterTable = &letter_P[0][0];
    nbrCmd = sizeof(letter_P) / sizeof( *letter_P );
    break;
    case 'Q':
    letterTable = &letter_Q[0][0];
    nbrCmd = sizeof(letter_Q) / sizeof( *letter_Q );
    break;
    case 'R':
    letterTable = &letter_R[0][0];
    nbrCmd = sizeof(letter_R) / sizeof( *letter_R );
    break;
    case 'S':
    letterTable = &letter_S[0][0];
    nbrCmd = sizeof(letter_S) / sizeof( *letter_S );
    break;
    case 'T':
    letterTable = &letter_T[0][0];
    nbrCmd = sizeof(letter_T) / sizeof( *letter_T );
    break;
    case 'U':
    letterTable = &letter_U[0][0];
    nbrCmd = sizeof(letter_U) / sizeof( *letter_U );
    break;
    case 'V':
    letterTable = &letter_V[0][0];
    nbrCmd = sizeof(letter_V) / sizeof( *letter_V );
    break;
    case 'W':
    letterTable = &letter_W[0][0];
    nbrCmd = sizeof(letter_W) / sizeof( *letter_W );
    break;
    case 'X':
    letterTable = &letter_X[0][0];
    nbrCmd = sizeof(letter_X) / sizeof( *letter_X );
    break;
    case 'Y':
    letterTable = &letter_Y[0][0];
    nbrCmd = sizeof(letter_Y) / sizeof( *letter_Y );
    break;
    case 'Z':
    letterTable = &letter_Z[0][0];
    nbrCmd = sizeof(letter_Z) / sizeof( *letter_Z );
    break;
}
Serial.print(F("nb cme : "));Serial.println(nbrCmd);
for(int x=0; x< nbrCmd; x++){
    trace( *(letterTable+x*2), *(letterTable+x*2+1));
}
}
*/
// ----- HELPER FUNCTIONS -----------
int step(float distance){
    int steps = distance * steps_rev / (wheel_dia * 3.1412); //24.61
    /*
Serial.print(distance);
Serial.print(" ");
Serial.print(steps_rev);
Serial.print(" ");  
Serial.print(wheel_dia);
Serial.print(" ");  
Serial.println(steps);
delay(1000);*/
    return steps;  
}


void forward(float distance){
    int steps = step(distance);
    //Serial.print("forward : ");Serial.println(distance);
    for(int step=0; step<steps; step++){
        for(int mask=0; mask<4; mask++){
            for(int pin=0; pin<4; pin++){
                digitalWrite(L_stepper_pins[pin], rev_mask[mask][pin]);
                digitalWrite(R_stepper_pins[pin], fwd_mask[mask][pin]);
            }
            delay(delay_time);
        } 
    }
}


void backward(float distance){
    int steps = step(distance);
    for(int step=0; step<steps; step++){
        for(int mask=0; mask<4; mask++){
            for(int pin=0; pin<4; pin++){
                digitalWrite(L_stepper_pins[pin], fwd_mask[mask][pin]);
                digitalWrite(R_stepper_pins[pin], rev_mask[mask][pin]);
            }
            delay(delay_time);
        } 
    }
}


void right(float degrees){
    float rotation = degrees / 360.0;
    //Serial.print("right : ");Serial.println(degrees);
    float distance = wheel_base * 3.1412 * rotation;
    int steps = step(distance);
    for(int step=0; step<steps; step++){
        for(int mask=0; mask<4; mask++){
            for(int pin=0; pin<4; pin++){
                digitalWrite(R_stepper_pins[pin], rev_mask[mask][pin]);
                digitalWrite(L_stepper_pins[pin], rev_mask[mask][pin]);
            }
            delay(delay_time);
        } 
    }   
}


void left(float degrees){
    float rotation = degrees / 360.0;
    //Serial.print("left : ");Serial.println(degrees);
    float distance = wheel_base * 3.1412 * rotation;
    int steps = step(distance);
    for(int step=0; step<steps; step++){
        for(int mask=0; mask<4; mask++){
            for(int pin=0; pin<4; pin++){
                digitalWrite(R_stepper_pins[pin], fwd_mask[mask][pin]);
                digitalWrite(L_stepper_pins[pin], fwd_mask[mask][pin]);
            }
            delay(delay_time);
        } 
    }   
}


void done(){ // unlock stepper to save battery
    for(int mask=0; mask<4; mask++){
        for(int pin=0; pin<4; pin++){
            digitalWrite(R_stepper_pins[pin], LOW);
            digitalWrite(L_stepper_pins[pin], LOW);
        }
        delay(delay_time);
    }
}


void penup(){
    delay(250);
    //Serial.println("PEN_UP()");
    penServo.write(PEN_UP);
    delay(250);
}


void pendown(){
    delay(250);  
    //Serial.println("PEN_DOWN()");
    penServo.write(PEN_DOWN);
    delay(250);
}

