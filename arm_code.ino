#include <Servo.h>

//TODO: tweak constants for bounds of finger ranges

Servo palm;
Servo thumb;
Servo index;
Servo middle;
Servo ring;
Servo pinky;
//Servo pronator;
//Servo wristRight;
//Servo wristLeft;

int thumbIn = 0; //A0 pin for thumb flex sensor
int indexIn = 1; //etc
int middleIn = 2; 
int ringIn = 3;
int pinkyIn = 4; 

int currentThumb = analogRead(thumbIn); //current positions of fingers
int currentIndex = analogRead(indexIn);
int currentMiddle = analogRead(middleIn);
int currentRing = analogRead(ringIn);
int currentPinky = analogRead(pinkyIn);

//flag for exiting before doing anything. 0=false, nonzero is true
#define EXITONSTART 1
//flag for how long to delay after setup but before starting main loop
#define DELAYBEFOREMAIN 500

//FINGER INDEX CONSTANTS (for code): 
#define PALM 0
#define THUMB 1
#define INDEX 2
#define MIDDLE 3
#define RING 4
#define PINKY 5
//#define PRONATOR 6
//#define WRISTRIGHT 7
//#define WRISTLEFT 8

//FINGER PINS (which arduino out to plug into)
//PALM: 2
//THUMB: 3
//INDEX: 4
//MIDDLE: 5
//RING: 6
//PINKY: 7
//PRONATOR: 8
//WRISTRIGHT: 9
//WRISTLEFT: 10
void setup() 
{
  Serial.begin(9600);
  Serial.println("Starting setup");
  if(EXITONSTART) exit(0); //quit before doing anything if EXIT flag is set

  palm.attach(2); //map palm to write to pin 2
  thumb.attach(3); //etc
  index.attach(4);
  middle.attach(5);
  ring.attach(6);
  pinky.attach(7);
  //pronator.attach(8);
  //wristRight.attach(9);
  //wristLeft.attach(10);
  
  closeHand();
  
//  pronate(0);
//  delay(750);
//  pronate(180);
//  delay(750);
//  pronate(82); //note that 82 is dead-center for some reason
//  delay(750);
  
  delay(DELAYBEFOREMAIN);
}


//just see if each finger moves
void testServos()
{
  for(int i = 0; i < 6; i++)
  {
    if((i==PALM)||(i==INDEX))
    {
      moveFingerRange(i, 180, 180);
    }
    if((i==MIDDLE)||(i==THUMB)||(i==RING)||(i==PINKY))
    {
      moveFingerRange(i, 0, 0);
    }
    delay(750);
  } 
  
  for(int i = 0; i < 6; i++)
  {
    if((i==PALM)||(i==INDEX))
    {
      moveFingerRange(i, 0, 0);
    }
    if((i==MIDDLE)||(i==THUMB)||(i==RING)||(i==PINKY))
    {
      moveFingerRange(i, 180, 180);
    }
    delay(750);
  } 
  
//  pronate(0);
//  delay(750);
//  pronate(180);
//  delay(750);
//  pronate(82);
//  delay(750);
//  
//  moveWristRight(0);
//  moveWristLeft(0);
//  delay(750);
//  moveWristRight(180);
//  moveWristLeft(180);
//  delay(750);
//  moveWristRight(90);
//  moveWristLeft(90);
//  delay(2000);
  
}

//set the servos to the closed hand position
//called during setup
void closeHand()
{
  movePalm(0);
  moveThumb(180);
  moveIndex(0);
  moveMiddle(180);
  moveRing(180);
  movePinky(180);
}

//set the servos to the open hand position
void openHand()
{
  movePalm(180);
  moveThumb(0);
  moveIndex(180);
  moveMiddle(0);
  moveRing(0);
  movePinky(0);
}

//the most important function of all
void flipOff()
{
  closeHand();
  middle.write(60); //outside middle's bounds but useful here
  delay(1000);
  moveMiddle(180);
}

//ROCK AND ROLL
void signOfHorns()
{
  closeHand();
  moveIndex(180);
  movePinky(0);
}

////hi there
//void waveHello()
//{
//  openHand();
//  delay(250);
//  moveWristRight(180);
//  moveWristLeft(180);
//  delay(750);
//  moveWristRight(0);  
//  moveWristLeft(0);
//  delay(750);
//  moveWristRight(180);
//  moveWristLeft(180);
//  delay(750);
//  moveWristRight(90);
//  moveWristLeft(90);
//}

//move the palm joint to the given position with bounds
void movePalm(int pos)
{
   Serial.println("Call to movePalm\n");
   pos = constrain(pos, 60, 130);

   palm.write(pos);
}

//move the thumb to the given position with bounds
void moveThumb(int pos)
{
   //Serial.println("Call to moveThumb\n");
   pos = constrain(pos, 135, 180);

   thumb.write(pos);
}

//move the index finger to the given position with bounds
void moveIndex(int pos)
{
   //Serial.print("Call to moveIndex\n");
   pos = constrain(pos, 46, 115);
  
   index.write(pos);
}

//move the middle finger to the given position with bounds
void moveMiddle(int pos)
{
  //Serial.print("Call to moveMiddle\n");
  pos = constrain(pos, 65, 150);
  
  middle.write(pos);
}

//move the ring finger to the given position with bounds
void moveRing(int pos)
{
  //Serial.print("Call to moveRing\n");
  pos = constrain(pos, 95, 175);
  
  ring.write(pos);
}

//move the pinky finger to the given position with bounds
void movePinky(int pos)
{
  //Serial.print("Call to movePinky\n");
  pos = constrain(pos, 95, 155);
  
  pinky.write(pos);
}

////rotate the arm to the given position within bounds
//void pronate(int pos)
//{
//  Serial.print("Call to pronate\n");
//  if(pos < 40) pos=40;
//  if(pos > 135) pos=135;
//  
//  pronator.write(pos);
//}
//
////move the right wrist servo to the given position,
////within bounds
//void moveWristRight(int pos)
//{
//  Serial.print("Call to wristRight\n");
//  wristLeft.detach();
//  if(pos<45) pos=45;
//  if(pos>110) pos=110;
// 
//  wristRight.write(pos); 
//  wristLeft.attach(10);
//}
//
////move the left wrist servo to the given position,
////within bounds
//void moveWristLeft(int pos)
//{
//  Serial.print("Call to wristLeftt\n");
//  wristRight.detach();
//
//  if(pos<55) //slow the downward motion a bit
//  {
//    wristLeft.write(60);
//    delay(35);
//    pos=55;
//  } 
//  if(pos>100) pos=100;
// 
//  wristLeft.write(pos); 
//  wristRight.attach(9);
//}

//call the appropriate move wrapper to move the finger from startIndex
//to endIndex, minding their boundaries of activation. pause for delayVal
//number of milliseconds for each degree turned
void moveFingerRange(int index, int startIndex, int endIndex, int delayVal)
{
   switch(index)
   {
     case PALM: 
       for(int i = startIndex; i <= endIndex; i++)
       {
         movePalm(i);
         delay(delayVal);
       }
       break;
       
     case THUMB:
       for(int i = startIndex; i <= endIndex; i++)
       {
         moveThumb(i);
         delay(delayVal);
       }
       break;
       
     case INDEX:
       for(int i = startIndex; i <= endIndex; i++)
       {
         moveIndex(i);
         delay(delayVal);
       }
       break;
       
     case MIDDLE: 
       for(int i = startIndex; i <= endIndex; i++)
       {
         moveMiddle(i);
         delay(delayVal);
       }
       break;
       
     case RING:
       for(int i = startIndex; i <= endIndex; i++)
       {
         moveRing(i);
         delay(delayVal);
       }
       break;
     
     case PINKY:
       for(int i = startIndex; i <= endIndex; i++)
       {
         movePinky(i);
         delay(delayVal);
       }
       break;

     default:
       Serial.println("Error in moveFingerRange (bad index, use constants)");
   }
  
}

//overloaded version of moveFingerRange, intended to just call moveFingerRange
//above with a default delayVal of 10 ms
void moveFingerRange(int index, int startIndex, int endIndex)
{
   moveFingerRange(index, startIndex, endIndex, 10); 
}


//read the value of the thumb flex sensor, map it to the thumb motor range,
//then write the appropriate value out to the thumb
void readThumb()
{
  int thumbPos = analogRead(thumbIn);
  thumbPos = constrain(thumbPos, 720, 800); //control some sensor noise/bondary issues
  int newThumb = map(thumbPos, 720, 800, 135, 180);
  
  int differential = abs(newThumb-currentThumb); //some smoothing when at rest or moving slowly
  if(differential >= 3)
  {
    
    moveThumb(newThumb);
    currentThumb = newThumb;
  }
}

//same for index
void readIndex()
{
  int indexPos = analogRead(indexIn);
  indexPos = constrain(indexPos, 750, 830);
  int newIndex = map(indexPos, 750, 830, 115, 46);
  
  int differential = abs(newIndex-currentIndex);
  if(differential >= 3)
  {
    moveIndex(newIndex);
    currentIndex = newIndex;
  }
}

//same for middle
void readMiddle()
{
  int middlePos = analogRead(middleIn);
  middlePos = constrain(middlePos, 750, 850); 
  int newMiddle = map(middlePos, 750, 850, 65, 150);

  int differential = abs(newMiddle-currentMiddle);
  if(differential >= 3)
  {
    moveMiddle(newMiddle);
    currentMiddle = newMiddle;
  }

}

//same for ring
void readRing()
{
  int ringPos = analogRead(ringIn);
  ringPos = constrain(ringPos, 750, 850);
  int newRing = map(ringPos, 750, 850, 95, 175);
  
  
  int differential = abs(newRing-currentRing);
  if(differential >= 3)
  {
    moveRing(newRing);
    currentRing = newRing;
  }
}

//same for pinky
void readPinky()
{
  int pinkyPos = analogRead(pinkyIn);
  Serial.println(pinkyPos);
  pinkyPos = constrain(pinkyPos, 730, 775);
  int newPinky = map(pinkyPos, 730, 775, 95, 155); 
  
  int differential = abs(newPinky-currentPinky);
  if(differential >= 3)
  {
     movePinky(newPinky);
     currentPinky = newPinky;
  }
}


//main loop
void loop() 
{  
  
  readThumb();
  readIndex();
  readMiddle();
  readRing();
  readPinky();
  
  delay(25);
}
