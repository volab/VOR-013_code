// 
// Cette version est dédiée au test du servo moteur

#include <Servo.h>

// setup servo
int servoPin = 8;
int PEN_DOWN = 20; // angle of servo when pen is down
int PEN_UP = 110;   // angle of servo when pen is up
Servo penServo;


boolean flagPen = false;
boolean flagDoit = false;


void setup() {
  randomSeed(analogRead(1)); 
  Serial.begin(9600);

  penServo.attach(servoPin);
  Serial.println("setup");

}

void loop(){ // draw a calibration box 4 times
  if (flagDoit){
    if (flagPen) pendown(); else penup();
    flagDoit = false;
  }
  Serial.print("Waiting - flagpen = ");Serial.println( flagPen);
  delay(600);
  
}

void serialEvent(){
  while( Serial.available() != 0) Serial.read();
  flagPen = !flagPen;
  flagDoit = true;
}

void penup(){
  delay(250);
  Serial.println("PEN_UP()");
  penServo.write(PEN_UP);
  delay(250);
}


void pendown(){
  delay(250);  
  Serial.println("PEN_DOWN()");
  penServo.write(PEN_DOWN);
  delay(250);
}

