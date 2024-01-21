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
int servoMin[] = {5760, 5248, 3968, 6272, 3968, 3968, 3200, 1792};
int servoMax[] = {6400, 5824, 8000, 7552, 8000, 8000, 8832, 10176};
int servoInitial[] = {6080, 5520, 5984, 6912, 5984, 5984, 6016, 5984};

//  setSpeed takes channel number you want to limit and the
//  speed limit in units of (1/4 microseconds)/(10 milliseconds).
int servoSpeed[] = {0, 0, 0, 0, 0, 0, 0, 0}; // Adjust as needed

//  setAcceleration takes channel number you want to limit and
//  the acceleration limit value from 0 to 255 in units of (1/4
//  microseconds)/(10 milliseconds) / (80 milliseconds).
int servoAcceleration[] = {20, 0, 40, 6, 10, 5, 100, 10}; // Adjust as needed

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
  //play 3 clips and then a song
  for (int i=1;i<=1;i++){
    playclip();
    delay(10000);

    //reset accel speeds for bounce
    resetservos();
  }
  //playsong();
}

void bounce(float tempo) {
  maestro.setTarget(NECKLIFT, 5000);
  maestro.setTarget(NECK, servoMin[NECK]);
  maestro.setTarget(VISOR, 6000);
  maestro.setTarget(WRIST, servoMin[WRIST]);
  randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
  maestro.setTarget(TOP_RING, randNumber);
  randNumber = random(servoMin[NECK_ROTATE],servoMax[NECK_ROTATE]);
  maestro.setTarget(NECK_ROTATE, randNumber);
   
  delay((30/tempo)*1000);

  maestro.setTarget(NECKLIFT, 6500);
  maestro.setTarget(NECK, servoMax[NECK]);
  maestro.setTarget(VISOR, 6150);
 
  delay((30/tempo)*1000);

  maestro.setTarget(NECKLIFT, 5000);
  maestro.setTarget(NECK, servoMin[NECK]);
  maestro.setTarget(VISOR, 6000);
   maestro.setTarget(WRIST, servoMax[WRIST]);
  randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
  maestro.setTarget(TOP_RING, randNumber);
  randNumber = random(servoMin[ELBOW],servoMax[ELBOW]);
  maestro.setTarget(ELBOW, randNumber);
  randNumber = random(servoMin[NECK_ROTATE],servoMax[NECK_ROTATE]);
  maestro.setTarget(NECK_ROTATE, randNumber);
   
  delay((30/tempo)*1000);

  maestro.setTarget(NECKLIFT, 6500);
  maestro.setTarget(NECK, servoMax[NECK]);
  maestro.setTarget(VISOR, 6150);

  delay((30/tempo)*1000);

  maestro.setTarget(NECKLIFT, 5000);
  maestro.setTarget(NECK, servoMin[NECK]);
  maestro.setTarget(VISOR, 6000);
  maestro.setTarget(WRIST, servoMin[WRIST]);
  randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
  maestro.setTarget(TOP_RING, randNumber);
  randNumber = random(servoMin[NECK_ROTATE],servoMax[NECK_ROTATE]);
  maestro.setTarget(NECK_ROTATE, randNumber);
   
  delay((30/tempo)*1000);

  maestro.setTarget(NECKLIFT, 6500);
  maestro.setTarget(NECK, servoMax[NECK]);
  maestro.setTarget(VISOR, 6150);

  delay((30/tempo)*1000);

  maestro.setTarget(NECKLIFT, 5000);
  maestro.setTarget(NECK, servoMin[NECK]);
  maestro.setTarget(VISOR, 6000);
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

  maestro.setTarget(NECKLIFT, 6500);
  maestro.setTarget(NECK, servoMax[NECK]);
  maestro.setTarget(VISOR, 6150);

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
    delay(1000);
    float bounceDuration = float(clipLength[song])/((60/float(clipTempo[song]))*4);
    // had to decrease bounceDuration as was playing too long - need to figure out why as think calc was correct
    for (float i=1;i<=int(bounceDuration*.9);i++) {
      bounce(clipTempo[song]);
      Serial.println(i);
      Serial.println(int(bounceDuration));
    }
}

void playclip() {
  //randNumber = random(1,22);
  randNumber = 10;
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
    //delay(clipLength[randNumber]*1000);
  switch (randNumber){
    case 1:
      maestro.setAcceleration(6,15);
      maestro.setAcceleration(1,5);
      maestro.setAcceleration(0,10);
      maestro.setTarget(NECK, servoInitial[NECK]);
      maestro.setTarget(NECKLIFT, servoInitial[NECKLIFT]);
      delay(350);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      delay(500);
      randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
      maestro.setTarget(TOP_RING, randNumber);
      randNumber = random(servoMin[ELBOW],servoMax[ELBOW]);
      maestro.setTarget(ELBOW, randNumber);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      delay(450);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      delay(460);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
      maestro.setTarget(TOP_RING, randNumber);
      randNumber = random(servoMin[ELBOW],servoMax[ELBOW]);
      maestro.setTarget(ELBOW, randNumber);
      delay(500);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      delay(600);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, servoInitial[VISOR]);
      maestro.setTarget(NECK, servoInitial[NECK]);
      delay(1000);       
      break;
    case 2:
      maestro.setAcceleration(6,15);
      maestro.setAcceleration(1,5);
      maestro.setAcceleration(0,10);
      maestro.setTarget(NECK, servoInitial[NECK]);
      maestro.setTarget(NECKLIFT, servoInitial[NECKLIFT]);
      delay(550);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      randNumber = random(servoMin[NECK_ROTATE],servoMax[NECK_ROTATE]);
      maestro.setTarget(NECK_ROTATE, randNumber);
      delay(500);
      randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
      maestro.setTarget(TOP_RING, randNumber);
      randNumber = random(servoMin[ELBOW],servoMax[ELBOW]);
      maestro.setTarget(ELBOW, randNumber);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      delay(450);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      randNumber = random(servoMin[NECK_ROTATE],servoMax[NECK_ROTATE]);
      maestro.setTarget(NECK_ROTATE, randNumber);
      delay(460);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
      maestro.setTarget(TOP_RING, randNumber);
      randNumber = random(servoMin[ELBOW],servoMax[ELBOW]);
      maestro.setTarget(ELBOW, randNumber);
      delay(500);
      randNumber = random(servoMin[NECK_ROTATE],servoMax[NECK_ROTATE]);
      maestro.setTarget(NECK_ROTATE, randNumber);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      delay(600);
      randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
      maestro.setTarget(TOP_RING, randNumber);
      randNumber = random(servoMin[ELBOW],servoMax[ELBOW]);
      maestro.setTarget(ELBOW, randNumber);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      delay(450);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      delay(460);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      randNumber = random(servoMin[NECK_ROTATE],servoMax[NECK_ROTATE]);
      maestro.setTarget(NECK_ROTATE, randNumber);
      randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
      maestro.setTarget(TOP_RING, randNumber);
      randNumber = random(servoMin[ELBOW],servoMax[ELBOW]);
      maestro.setTarget(ELBOW, randNumber);
      delay(550);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      delay(560);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      delay(960);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, servoInitial[VISOR]);
      maestro.setTarget(NECK, servoInitial[NECK]);
      delay(1000);           
      break;
    case 3:
      maestro.setAcceleration(6,15);
      maestro.setAcceleration(1,5);
      maestro.setAcceleration(0,10);
      maestro.setTarget(NECK, servoInitial[NECK]);
      maestro.setTarget(NECKLIFT, servoInitial[NECKLIFT]);
      delay(550);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      randNumber = random(servoMin[NECK_ROTATE],servoMax[NECK_ROTATE]);
      maestro.setTarget(NECK_ROTATE, randNumber);
      delay(500);
      randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
      maestro.setTarget(TOP_RING, randNumber);
      randNumber = random(servoMin[ELBOW],servoMax[ELBOW]);
      maestro.setTarget(ELBOW, randNumber);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      delay(450);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      randNumber = random(servoMin[NECK_ROTATE],servoMax[NECK_ROTATE]);
      maestro.setTarget(NECK_ROTATE, randNumber);
      delay(460);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
      maestro.setTarget(TOP_RING, randNumber);
      randNumber = random(servoMin[ELBOW],servoMax[ELBOW]);
      maestro.setTarget(ELBOW, randNumber);
      delay(500);
      randNumber = random(servoMin[NECK_ROTATE],servoMax[NECK_ROTATE]);
      maestro.setTarget(NECK_ROTATE, randNumber);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      delay(600);
      randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
      maestro.setTarget(TOP_RING, randNumber);
      randNumber = random(servoMin[ELBOW],servoMax[ELBOW]);
      maestro.setTarget(ELBOW, randNumber);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      delay(450);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      delay(460);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      randNumber = random(servoMin[NECK_ROTATE],servoMax[NECK_ROTATE]);
      maestro.setTarget(NECK_ROTATE, randNumber);
      randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
      maestro.setTarget(TOP_RING, randNumber);
      randNumber = random(servoMin[ELBOW],servoMax[ELBOW]);
      maestro.setTarget(ELBOW, randNumber);
      delay(550);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      delay(550);
      maestro.setAcceleration(6,1);
      maestro.setAcceleration(1,1);
      maestro.setSpeed(1,2);
      maestro.setSpeed(0,3);
      maestro.setAcceleration(0,1);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      delay(1200);
      maestro.setTarget(NECKLIFT, 3200);
      maestro.setTarget(VISOR, servoMin[VISOR]);
      maestro.setTarget(NECK, servoMin[NECK]);
      delay(2000);             
      break;
    case 4:
      maestro.setAcceleration(6,15);
      maestro.setAcceleration(1,5);
      maestro.setAcceleration(0,10);
      delay(350);
      maestro.setTarget(NECK, servoInitial[NECK]);
      maestro.setTarget(NECKLIFT, servoInitial[NECKLIFT]);
      delay(350);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      delay(500);
      randNumber = random(servoMin[NECK_ROTATE],servoMax[NECK_ROTATE]);
      maestro.setTarget(NECK_ROTATE, randNumber);
      randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
      maestro.setTarget(TOP_RING, randNumber);
      randNumber = random(servoMin[ELBOW],servoMax[ELBOW]);
      maestro.setTarget(ELBOW, randNumber);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      delay(450);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      delay(460);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
      maestro.setTarget(TOP_RING, randNumber);
      randNumber = random(servoMin[ELBOW],servoMax[ELBOW]);
      maestro.setTarget(ELBOW, randNumber);
      delay(500);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      delay(600);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      randNumber = random(servoMin[NECK_ROTATE],servoMax[NECK_ROTATE]);
      maestro.setTarget(NECK_ROTATE, randNumber);
      randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
      maestro.setTarget(TOP_RING, randNumber);
      randNumber = random(servoMin[ELBOW],servoMax[ELBOW]);
      maestro.setTarget(ELBOW, randNumber);
      delay(500);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      delay(500);
      maestro.setAcceleration(6,1);
      maestro.setAcceleration(1,1);
      maestro.setSpeed(1,2);
      maestro.setSpeed(0,3);
      maestro.setAcceleration(0,1);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, servoInitial[VISOR]);
      maestro.setTarget(NECK, servoInitial[NECK]);
      delay(1000);           
      break;
    case 5:
      maestro.setAcceleration(6,15);
      maestro.setAcceleration(1,5);
      maestro.setAcceleration(0,10);
      maestro.setTarget(NECK, servoInitial[NECK]);
      maestro.setTarget(NECKLIFT, servoInitial[NECKLIFT]);
      delay(550);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      randNumber = random(servoMin[NECK_ROTATE],servoMax[NECK_ROTATE]);
      maestro.setTarget(NECK_ROTATE, randNumber);
      delay(500);
      randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
      maestro.setTarget(TOP_RING, randNumber);
      randNumber = random(servoMin[ELBOW],servoMax[ELBOW]);
      maestro.setTarget(ELBOW, randNumber);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      delay(450);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      randNumber = random(servoMin[NECK_ROTATE],servoMax[NECK_ROTATE]);
      maestro.setTarget(NECK_ROTATE, randNumber);
      delay(460);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
      maestro.setTarget(TOP_RING, randNumber);
      randNumber = random(servoMin[ELBOW],servoMax[ELBOW]);
      maestro.setTarget(ELBOW, randNumber);
      delay(500);
      randNumber = random(servoMin[NECK_ROTATE],servoMax[NECK_ROTATE]);
      maestro.setTarget(NECK_ROTATE, randNumber);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      delay(600);
      randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
      maestro.setTarget(TOP_RING, randNumber);
      randNumber = random(servoMin[ELBOW],servoMax[ELBOW]);
      maestro.setTarget(ELBOW, randNumber);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      delay(450);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      delay(560);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      randNumber = random(servoMin[NECK_ROTATE],servoMax[NECK_ROTATE]);
      maestro.setTarget(NECK_ROTATE, randNumber);
      randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
      maestro.setTarget(TOP_RING, randNumber);
      randNumber = random(servoMin[ELBOW],servoMax[ELBOW]);
      maestro.setTarget(ELBOW, randNumber);
      delay(550);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      delay(660);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      delay(1560);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, servoInitial[VISOR]);
      maestro.setTarget(NECK, servoInitial[NECK]);
      delay(1000);                
      break;
    case 6:
      maestro.setAcceleration(6,15);
      maestro.setAcceleration(1,5);
      maestro.setAcceleration(0,10);
      maestro.setTarget(NECK, servoInitial[NECK]);
      maestro.setTarget(NECKLIFT, servoInitial[NECKLIFT]);
      delay(550);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      randNumber = random(servoMin[NECK_ROTATE],servoMax[NECK_ROTATE]);
      maestro.setTarget(NECK_ROTATE, randNumber);
      delay(500);
      randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
      maestro.setTarget(TOP_RING, randNumber);
      randNumber = random(servoMin[ELBOW],servoMax[ELBOW]);
      maestro.setTarget(ELBOW, randNumber);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      delay(450);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      randNumber = random(servoMin[NECK_ROTATE],servoMax[NECK_ROTATE]);
      maestro.setTarget(NECK_ROTATE, randNumber);
      delay(460);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
      maestro.setTarget(TOP_RING, randNumber);
      randNumber = random(servoMin[ELBOW],servoMax[ELBOW]);
      maestro.setTarget(ELBOW, randNumber);
      delay(500);
      randNumber = random(servoMin[NECK_ROTATE],servoMax[NECK_ROTATE]);
      maestro.setTarget(NECK_ROTATE, randNumber);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      delay(600);
      randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
      maestro.setTarget(TOP_RING, randNumber);
      randNumber = random(servoMin[ELBOW],servoMax[ELBOW]);
      maestro.setTarget(ELBOW, randNumber);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      delay(450);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      delay(460);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      randNumber = random(servoMin[NECK_ROTATE],servoMax[NECK_ROTATE]);
      maestro.setTarget(NECK_ROTATE, randNumber);
      randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
      maestro.setTarget(TOP_RING, randNumber);
      randNumber = random(servoMin[ELBOW],servoMax[ELBOW]);
      maestro.setTarget(ELBOW, randNumber);
      delay(550);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      delay(750);
      maestro.setAcceleration(6,1);
      maestro.setAcceleration(1,1);
      maestro.setSpeed(1,2);
      maestro.setSpeed(0,3);
      maestro.setAcceleration(0,1);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      delay(1200);
      maestro.setTarget(NECKLIFT, 3200);
      maestro.setTarget(VISOR, servoMin[VISOR]);
      maestro.setTarget(NECK, servoMin[NECK]);
      delay(2000);                 
      break;
    case 7:
      maestro.setAcceleration(6,15);
      maestro.setAcceleration(1,5);
      maestro.setAcceleration(0,10);
      maestro.setTarget(NECK, servoInitial[NECK]);
      maestro.setTarget(NECKLIFT, servoInitial[NECKLIFT]);
      delay(350);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      delay(500);
      randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
      maestro.setTarget(TOP_RING, randNumber);
      randNumber = random(servoMin[ELBOW],servoMax[ELBOW]);
      maestro.setTarget(ELBOW, randNumber);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      delay(450);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      delay(460);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
      maestro.setTarget(TOP_RING, randNumber);
      randNumber = random(servoMin[ELBOW],servoMax[ELBOW]);
      maestro.setTarget(ELBOW, randNumber);
      delay(500);      
      break;
    case 8:
      maestro.setAcceleration(6,15);
      maestro.setAcceleration(1,5);
      maestro.setAcceleration(0,10);
      delay(250);
      maestro.setTarget(NECK, servoInitial[NECK]);
      maestro.setTarget(NECKLIFT, servoInitial[NECKLIFT]);
      delay(550);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      randNumber = random(servoMin[NECK_ROTATE],servoMax[NECK_ROTATE]);
      maestro.setTarget(NECK_ROTATE, randNumber);
      delay(500);
      randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
      maestro.setTarget(TOP_RING, randNumber);
      randNumber = random(servoMin[ELBOW],servoMax[ELBOW]);
      maestro.setTarget(ELBOW, randNumber);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      delay(450);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      randNumber = random(servoMin[NECK_ROTATE],servoMax[NECK_ROTATE]);
      maestro.setTarget(NECK_ROTATE, randNumber);
      delay(460);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
      maestro.setTarget(TOP_RING, randNumber);
      randNumber = random(servoMin[ELBOW],servoMax[ELBOW]);
      maestro.setTarget(ELBOW, randNumber);
      delay(500);
      randNumber = random(servoMin[NECK_ROTATE],servoMax[NECK_ROTATE]);
      maestro.setTarget(NECK_ROTATE, randNumber);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      delay(600);
      randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
      maestro.setTarget(TOP_RING, randNumber);
      randNumber = random(servoMin[ELBOW],servoMax[ELBOW]);
      maestro.setTarget(ELBOW, randNumber);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      delay(450);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      delay(460);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      randNumber = random(servoMin[NECK_ROTATE],servoMax[NECK_ROTATE]);
      maestro.setTarget(NECK_ROTATE, randNumber);
      randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
      maestro.setTarget(TOP_RING, randNumber);
      randNumber = random(servoMin[ELBOW],servoMax[ELBOW]);
      maestro.setTarget(ELBOW, randNumber);
      delay(650);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      delay(660);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      delay(960);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, servoInitial[VISOR]);
      maestro.setTarget(NECK, servoInitial[NECK]);
      delay(1000);                
      break;
    case 9:
            maestro.setAcceleration(6,15);
      maestro.setAcceleration(1,5);
      maestro.setAcceleration(0,10);
      delay(250);
      maestro.setTarget(NECK, servoInitial[NECK]);
      maestro.setTarget(NECKLIFT, servoInitial[NECKLIFT]);
      delay(550);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      randNumber = random(servoMin[NECK_ROTATE],servoMax[NECK_ROTATE]);
      maestro.setTarget(NECK_ROTATE, randNumber);
      delay(500);
      randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
      maestro.setTarget(TOP_RING, randNumber);
      randNumber = random(servoMin[ELBOW],servoMax[ELBOW]);
      maestro.setTarget(ELBOW, randNumber);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      delay(450);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      randNumber = random(servoMin[NECK_ROTATE],servoMax[NECK_ROTATE]);
      maestro.setTarget(NECK_ROTATE, randNumber);
      delay(460);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
      maestro.setTarget(TOP_RING, randNumber);
      randNumber = random(servoMin[ELBOW],servoMax[ELBOW]);
      maestro.setTarget(ELBOW, randNumber);
      delay(500);
      randNumber = random(servoMin[NECK_ROTATE],servoMax[NECK_ROTATE]);
      maestro.setTarget(NECK_ROTATE, randNumber);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      delay(600);
      randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
      maestro.setTarget(TOP_RING, randNumber);
      randNumber = random(servoMin[ELBOW],servoMax[ELBOW]);
      maestro.setTarget(ELBOW, randNumber);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      delay(450);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      delay(460);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      randNumber = random(servoMin[NECK_ROTATE],servoMax[NECK_ROTATE]);
      maestro.setTarget(NECK_ROTATE, randNumber);
      randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
      maestro.setTarget(TOP_RING, randNumber);
      randNumber = random(servoMin[ELBOW],servoMax[ELBOW]);
      maestro.setTarget(ELBOW, randNumber);
      delay(650);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      delay(760);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      maestro.setAcceleration(6,1);
      maestro.setAcceleration(1,1);
      maestro.setSpeed(1,2);
      maestro.setSpeed(0,3);
      maestro.setAcceleration(0,1);
      delay(1060);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, servoInitial[VISOR]);
      maestro.setTarget(NECK, servoInitial[NECK]);
      delay(1000);    
      break;
    case 10:
      maestro.setAcceleration(6,15);
      maestro.setAcceleration(1,5);
      maestro.setAcceleration(0,10);
      maestro.setTarget(NECK, servoInitial[NECK]);
      maestro.setTarget(NECKLIFT, servoInitial[NECKLIFT]);
      delay(550);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      randNumber = random(servoMin[NECK_ROTATE],servoMax[NECK_ROTATE]);
      maestro.setTarget(NECK_ROTATE, randNumber);
      delay(500);
      randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
      maestro.setTarget(TOP_RING, randNumber);
      randNumber = random(servoMin[ELBOW],servoMax[ELBOW]);
      maestro.setTarget(ELBOW, randNumber);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      delay(450);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      randNumber = random(servoMin[NECK_ROTATE],servoMax[NECK_ROTATE]);
      maestro.setTarget(NECK_ROTATE, randNumber);
      delay(460);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
      maestro.setTarget(TOP_RING, randNumber);
      randNumber = random(servoMin[ELBOW],servoMax[ELBOW]);
      maestro.setTarget(ELBOW, randNumber);
      delay(500);
      randNumber = random(servoMin[NECK_ROTATE],servoMax[NECK_ROTATE]);
      maestro.setTarget(NECK_ROTATE, randNumber);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      delay(600);
      randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
      maestro.setTarget(TOP_RING, randNumber);
      randNumber = random(servoMin[ELBOW],servoMax[ELBOW]);
      maestro.setTarget(ELBOW, randNumber);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      delay(450);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      delay(460);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      randNumber = random(servoMin[NECK_ROTATE],servoMax[NECK_ROTATE]);
      maestro.setTarget(NECK_ROTATE, randNumber);
      randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
      maestro.setTarget(TOP_RING, randNumber);
      randNumber = random(servoMin[ELBOW],servoMax[ELBOW]);
      maestro.setTarget(ELBOW, randNumber);
      delay(350);
      maestro.setTarget(NECK, servoInitial[NECK]);
      maestro.setTarget(NECKLIFT, servoInitial[NECKLIFT]);
      maestro.setTarget(VISOR, servoInitial[VISOR]);
      delay(200);     
      break;
    case 11:
      // do some movement       
      break;
    case 12:
      // do some movement       
      break;
    case 13:
      // do some movement       
      break;
    case 14:
      // do some movement       
      break;
    case 15:
      // do some movement       
      break;
    case 16:
      // do some movement       
      break;
    case 17:
      // do some movement       
      break;
    case 18:
      maestro.setAcceleration(6,15);
      maestro.setAcceleration(1,5);
      maestro.setAcceleration(0,10);
      maestro.setTarget(NECK, servoInitial[NECK]);
      maestro.setTarget(NECKLIFT, servoInitial[NECKLIFT]);
      delay(700);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      delay(400);
      randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
      maestro.setTarget(TOP_RING, randNumber);
      randNumber = random(servoMin[ELBOW],servoMax[ELBOW]);
      maestro.setTarget(ELBOW, randNumber);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      delay(450);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      delay(560);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, 6200);
      maestro.setTarget(NECK, 5700);
      randNumber = random(servoMin[TOP_RING],servoMax[TOP_RING]);
      maestro.setTarget(TOP_RING, randNumber);
      randNumber = random(servoMin[ELBOW],servoMax[ELBOW]);
      maestro.setTarget(ELBOW, randNumber);
      delay(600);
      maestro.setTarget(NECKLIFT, 6500);
      maestro.setTarget(VISOR, 6400);
      maestro.setTarget(NECK, servoMax[NECK]);
      delay(1000);
      maestro.setTarget(NECKLIFT, 5000);
      maestro.setTarget(VISOR, servoInitial[VISOR]);
      maestro.setTarget(NECK, servoInitial[NECK]);
      delay(1000);     
      break;
    case 19:
      // do some movement       
      break;
    case 20:
      // do some movement       
      break;
    case 21:
      // do some movement       
      break;
    case 22:
      // do some movement       
      break;
    default:
      break;
    }
}

void resetservos()
{
        for (int i = 0; i <= 8; i++) {
        maestro.setSpeed(i,servoSpeed[i]);
        maestro.setAcceleration(i,servoAcceleration[i]);
        maestro.setTarget(i,servoInitial[i]);
      }
}