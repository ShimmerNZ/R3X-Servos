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

bool playing = false;
long randNumber;

SoftwareSerial maestroSerial(10, 11);
MicroMaestro maestro(maestroSerial);
static Communication Comm(MY_ADDRESS);

// Define servo movement parameters
// work out these values via control centre translate to a number 4 x us value.
int servoMin[] = {5760, 5432, 3968, 6272, 3968, 3968, 3200, 1792};
int servoMax[] = {6400, 5644, 8000, 7552, 8000, 8000, 8832, 10176};
int servoInitial[] = {6080, 5520, 5984, 6912, 5984, 5984, 6016, 5984};

//  setSpeed takes channel number you want to limit and the
//  speed limit in units of (1/4 microseconds)/(10 milliseconds).
int servoSpeed[] = {0, 0, 0, 0, 0, 0, 0, 0}; // Adjust as needed

//  setAcceleration takes channel number you want to limit and
//  the acceleration limit value from 0 to 255 in units of (1/4
//  microseconds)/(10 milliseconds) / (80 milliseconds).
int servoAcceleration[] = {40, 40, 40, 6, 10, 5, 20, 10}; // Adjust as needed

int clipLength[] = {0,3,6,9,5,7,9,2,7,8,4,15,2,6,8,9,13,8,4,3,4,2,4,190,160,173,147,130,141,178,140,179,165,98,170,176,172,163,157,60,187};
int clipTempo[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,142,120,130,115,132,120,126,91,116,117,124,92,105,120,105,96,123,112};

void setup() {
  maestroSerial.begin(9600);
  Serial.begin(115200);
  for (int i = 0; i <= 8; i++) {
    maestro.setSpeed(i,servoSpeed[i]);
    maestro.setAcceleration(i,servoAcceleration[i]);
    maestro.setTarget(i,servoInitial[i]);
  }
    randomSeed(analogRead(0));
    delay(6000);
}


void loop() {
  for (int i=1;i<=3;i++){
    playclip();
  }
  playsong();
}

void bounce(float tempo) {
  maestro.setAcceleration(6,40);
  maestro.setTarget(NECKLIFT, 5000);
  maestro.setTarget(NECK, servoMin[NECK]);
  //maestro.setTarget(VISOR, servoMin[VISOR]);
  maestro.setTarget(VISOR, 5960);
  maestro.setTarget(WRIST, servoMin[WRIST]);
  randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
  maestro.setTarget(TOP_RING, randNumber);
  randNumber = random(servoMin[NECK_ROTATE],servoMax[NECK_ROTATE]);
  maestro.setTarget(NECK_ROTATE, randNumber);
  
  delay((30/tempo)*1000);

  maestro.setTarget(NECK, servoMax[NECK]);
  maestro.setTarget(VISOR, 6200);

  delay((30/tempo)*1000);
  
  maestro.setTarget(NECKLIFT, 7000);
  maestro.setTarget(NECK, servoMin[NECK]);
  maestro.setTarget(VISOR, 5960);
  maestro.setTarget(WRIST, servoMax[WRIST]);
  randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
  maestro.setTarget(TOP_RING, randNumber);
  randNumber = random(servoMin[ELBOW],servoMax[ELBOW]);
  maestro.setTarget(ELBOW, randNumber);
  randNumber = random(servoMin[NECK_ROTATE],servoMax[NECK_ROTATE]);
  maestro.setTarget(NECK_ROTATE, randNumber);
  
   delay((30/tempo)*1000);

  maestro.setTarget(NECK, servoMin[NECK]);
  maestro.setTarget(VISOR, 6200);

  delay((30/tempo)*1000);
  
  maestro.setTarget(NECKLIFT, 5000);
  maestro.setTarget(NECK, servoMin[NECK]);
  //maestro.setTarget(VISOR, servoMin[VISOR]);
  maestro.setTarget(VISOR, 5960);
  maestro.setTarget(WRIST, servoMin[WRIST]);
  randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
  maestro.setTarget(TOP_RING, randNumber);
  randNumber = random(servoMin[NECK_ROTATE],servoMax[NECK_ROTATE]);
  maestro.setTarget(NECK_ROTATE, randNumber);
  
  delay((30/tempo)*1000);

  maestro.setTarget(NECK, servoMax[NECK]);
  maestro.setTarget(VISOR, 6200);

  delay((30/tempo)*1000);

  maestro.setTarget(NECKLIFT, 7000);
  maestro.setTarget(NECK, servoMax[NECK]);
  maestro.setTarget(VISOR, 5960);
  maestro.setTarget(WRIST, servoMax[WRIST]);
  randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
  maestro.setTarget(TOP_RING, randNumber);
  randNumber = random(servoMin[ELBOW],servoMax[ELBOW]);
  maestro.setTarget(ELBOW, randNumber);
  randNumber = random(servoMin[NECK_ROTATE],servoMax[NECK_ROTATE]);
  maestro.setTarget(NECK_ROTATE, randNumber);
  randNumber = random(servoMin[BOTTOM_RING],servoMax[BOTTOM_RING]);
  maestro.setTarget(BOTTOM_RING, randNumber);
  
     delay((30/tempo)*1000);

  maestro.setTarget(NECK, servoMin[NECK]);
  maestro.setTarget(VISOR, 6200);

  delay((30/tempo)*1000);
}

void playsong() {
  randNumber = random(23,40);
  // Create a temporary buffer to hold the combined string
  char buffer[20];  // Adjust the size based on your needs
  // Format the string "Song,10" into the buffer (options - Song,Mode,Volume)
  snprintf(buffer, sizeof(buffer), "Song,%d",randNumber);
  int song = randNumber;
  Comm.Transmit(OTHER_ARDUINO,buffer);
  //Comm.Transmit(OTHER_ARDUINO,"Mode,10");
    Serial.print("song: ");
    Serial.print(randNumber);
    Serial.print("   length: ");
    Serial.println(clipLength[randNumber]);
    //delay(clipLength[randNumber]*1000);
    float bounceDuration = float(clipLength[song])/((60/float(clipTempo[song]))*4);
    for (float i=1;i<=int(bounceDuration);i++) {
      bounce(clipTempo[song]);
      Serial.println(i);
      Serial.println(int(bounceDuration));
    }
}

void playclip() {
  randNumber = random(1,11);
  // Create a temporary buffer to hold the combined string
  char buffer[20];  // Adjust the size based on your needs
  // Format the string "Song,10" into the buffer (options - Song,Mode,Volume)
  snprintf(buffer, sizeof(buffer), "Song,%d",randNumber);
  Comm.Transmit(OTHER_ARDUINO,buffer);
  Comm.Transmit(OTHER_ARDUINO,"Mode,4");
    Serial.print("clip: ");
    Serial.print(randNumber);
    Serial.print("   length: ");
    Serial.println(clipLength[randNumber]);
    delay(clipLength[randNumber]*1000);
  switch (randNumber){
    case 1:
      // do some movement       
      break;
    case 2:
      // do some movement       
      break;
    default:
      break;
    }
}