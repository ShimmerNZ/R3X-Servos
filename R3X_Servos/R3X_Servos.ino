#include <SoftwareSerial.h>
#include <PololuMaestro.h>
#include "Communication.h"

// Define the servo channels
#define VISOR 0
#define NECK 1
#define WRIST 2
#define ELBOW 3
#define TOP_RING 4
#define BOTTOM_RING 5
#define NECKLIFT 6
#define NECK_ROTATE 7
#define OTHER_ARDUINO 10
#define MY_ADDRESS 25

SoftwareSerial maestroSerial(10, 11);
MicroMaestro maestro(maestroSerial);
static Communication Comm(MY_ADDRESS);

// Define servo movement parameters
// work out these values via control centre translate to a number from 0 to 16383.
int servoMin[] = {7000, 7000, 7000, 7000, 7000, 7000, 7000, 7000};
int servoMax[] = {9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000};
int servoInitial[] = {9000, 9000, 7000, 7000, 7000, 7000, 7000, 9000};

//  setSpeed takes channel number you want to limit and the
//  speed limit in units of (1/4 microseconds)/(10 milliseconds).
int servoSpeed[] = {50, 50, 50, 50, 50, 50, 50, 50}; // Adjust as needed

//  setAcceleration takes channel number you want to limit and
//  the acceleration limit value from 0 to 255 in units of (1/4
//  microseconds)/(10 milliseconds) / (80 milliseconds).
int servoAcceleration[] = {10, 10, 10, 10, 10, 10, 10, 10}; // Adjust as needed

void setup() {
  maestroSerial.begin(9600);
  Serial.begin(115200);
  for (int i = 0; i <= 8; i++) {
    maestro.setSpeed(i,servoSpeed[i]);
    maestro.setAcceleration(i,servoAcceleration[i]);
    maestro.setTarget(i,servoInitial[i]);
  }
    randomSeed(analogRead(0));
}

long randNumber;

void loop() {
  delay(6000); // Adjust delay as needed
  bounce(800);
  int randNum = random(22);
  Comm.Transmit(OTHER_ARDUINO, randNum);
}


void bounce(int tempo) {
  maestro.setTarget(NECK, servoMax[NECK]);
  maestro.setTarget(VISOR, servoMax[VISOR]);
  delay(tempo/120);
}