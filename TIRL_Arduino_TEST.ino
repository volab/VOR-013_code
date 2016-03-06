// 
// add bp and led to start
// majorLee 5/3
// Ajoute d'un tableau de lettres


#include <Servo.h>
#include "letters.h"
#define TABLETTERMAXLIGN 25

// setup servo
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
int L_stepper_pins[] = {12, 10, 9, 11};
int R_stepper_pins[] = {4, 6, 7, 5};

int fwd_mask[][4] =  {{1, 0, 1, 0},
                      {0, 1, 1, 0},
                      {0, 1, 0, 1},
                      {1, 0, 0, 1}};

int rev_mask[][4] =  {{1, 0, 0, 1},
                      {0, 1, 0, 1},
                      {0, 1, 1, 0},
                      {1, 0, 1, 0}};
//


int figure[][2]={ {FW,50}, {TL,60},
                  {FW,50}, {TL,60},
                  {FW,50}, {TL,60},
                  {FW,50}, {TL,60},
                  {FW,50}, {TL,60},
                  {FW,50}, {TL,60} };                  


void setup() {
  randomSeed(analogRead(1)); 
  Serial.begin(9600);
  for(int pin=0; pin<4; pin++){
    pinMode(L_stepper_pins[pin], OUTPUT);
    digitalWrite(L_stepper_pins[pin], LOW);
    pinMode(R_stepper_pins[pin], OUTPUT);
    digitalWrite(R_stepper_pins[pin], LOW);
  }
  penServo.attach(servoPin);
  Serial.println("setup");
  pinMode( SWITCH, INPUT_PULLUP);
  pinMode( LED, OUTPUT );
  penup();
  delay(1000);
}

String aEcrire="ABE";

void loop(){ // draw a calibration box 4 times
  while( digitalRead( SWITCH )){
    digitalWrite( LED, !digitalRead(LED));
    delay(200);
  }
  digitalWrite( LED, LOW );
  delay(1000);
  for (int i = 0; i< aEcrire.length(); i++){
    Serial.println(  aEcrire.charAt(i) );
    traceLetter( aEcrire.charAt(i) );
  }
  

  
  done();      // releases stepper motor
  while(1);    // wait for reset
}

// ----- TRACER FUNCTIONS -----------
void trace(int cmd, int param){
  Serial.print("cmd = ");Serial.print( cmd );
  Serial.print(" / ");Serial.println( param );
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
      right( (float) param );
      break;    
    case TL:
      left( (float) param );
      break;          
  }
}

void traceLetter(char c){
  int *letterTable;
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
    case 'E':
      letterTable = &letter_E[0][0];
      nbrCmd = sizeof(letter_E) / sizeof( *letter_E );
      break;
  }
  for(int x=0; x< nbrCmd; x++){
    trace( *(letterTable+x*2), *(letterTable+x*2+1));
  }
}
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

