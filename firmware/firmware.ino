
#include <Servo.h> // include Servo.h library
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

const int  switchOnePin = 2;    // digital pin 2 (pin the switch one is attached to)
// Use pins 10 and 11 to communicate with DFPlayer Mini
static const uint8_t PIN_MP3_TX = 10; // Connects to module's RX
static const uint8_t PIN_MP3_RX = 11; // Connects to module's TX
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);
// Create the Player object
DFRobotDFPlayerMini player;

Servo slidingServo;  // create Servo object
Servo basementServo;  // create Servo object
Servo headServo;  // create Servo object

int slidingPos = 0;  //servo position
int headPos = 0;  //servo position
int basementPos = 0;  //servo position
int relay = 51; // relay to control the pump 

#define TRIG_PIN_BACK 4
#define ECHO_PIN_BACK 5
#define TRIG_PIN_FRONT 6
#define ECHO_PIN_FRONT 7
#define HEAD_MOTOR 12
#define BASEMENT_MOTOR 13
#define SLIDING_MOTOR 49
long distance;
long duration;

int switchOneState = 0;         // current state of the switch
int lastSwitchOneState = 0;     // previous state of the switch

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
    // Init serial port for DFPlayer Mini
  softwareSerial.begin(9600);
  pinMode(TRIG_PIN_BACK, OUTPUT);   // set trigger pin to OUTPUT
  pinMode(ECHO_PIN_BACK, INPUT);    // set echo pin to INPUT
   pinMode(TRIG_PIN_FRONT, OUTPUT);   // set trigger pin to OUTPUT
  pinMode(ECHO_PIN_FRONT, INPUT);    // set echo pin to INPUT
  delay(50);

  pinMode(switchOnePin, INPUT);
  pinMode(relay, OUTPUT); 
  delay(50);
  // read the switch input pins:
  switchOneState   = digitalRead(switchOnePin);
  delay(100);
  lastSwitchOneState = switchOneState;
  delay(50);
 if (switchOneState == HIGH) {  //outside, set the robot in the correct position
    basementServo.attach(BASEMENT_MOTOR);  
    delay(100);
    basementServo.write(180); //facing the people
    delay(4000);
    basementServo.detach();
  }
 else{  //inside, set the robot in the correct position
    basementServo.attach(BASEMENT_MOTOR);  
    delay(100);
    basementServo.write(0); //facing the wall
    delay(4000);
    basementServo.detach();
 }

 headServo.attach(HEAD_MOTOR);  
 headServo.write(80);              //head down
 delay(2000);                   
 headServo.detach();
 
  delay(500);
 
}


void loop() {

  // read the switch input pins:
  switchOneState   = digitalRead(switchOnePin);
  delay(50);

 if (switchOneState == HIGH) {  //outside
  if(switchOneState != lastSwitchOneState)  //set position for the outside state
  { 
      basementServo.attach(BASEMENT_MOTOR);  // set servo pin
        for (basementPos = 0; basementPos < 180; basementPos += 1) 
      {
        basementServo.write(basementPos);              
        delay(30);                
      }   
        basementServo.detach();  // set servo pin
        delay(100);
  
  }
    digitalWrite(TRIG_PIN_FRONT, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(TRIG_PIN_FRONT, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN_FRONT, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(ECHO_PIN_FRONT, HIGH);
    // Calculating the distance
    distance= duration*0.034/2;
    // Prints the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.println(distance);  
    Serial.println(headPos);

    if(distance<200)
    {
      if (player.begin(softwareSerial))
      {
        Serial.println("OK");
        // Set volume to maximum (0 to 30).
        player.volume(30);
        // Play MP3 file on the SD card
        player.play(5);
        delay(10000);
        headServo.attach(HEAD_MOTOR);  // set servo pin
        delay(100);
        for (headPos = 80; headPos > 20; headPos -= 1)  //raise head
        {
          headServo.write(headPos);
          delay(35);
        }
        headServo.detach();
  
        delay(5000);
        delay(100);
        slidingServo.attach(SLIDING_MOTOR);  
        delay(100);
        //raise board
        slidingServo.write(180);              
        delay(1700);
        slidingServo.write(90);
        delay(100);
        slidingServo.detach(); 
        delay(5000);
        player.pause();  //pause the mp3
        delay(2000);
         
        //turn body
        basementServo.attach(BASEMENT_MOTOR);  // set servo pin
        delay(100);
        for (basementPos = 178; basementPos > 135; basementPos -= 1)
        {
          basementServo.write(basementPos);
          delay(30);
        }       
        delay(100);                   
        basementServo.detach();  // set servo pin
        delay(100);
        //down head
        headServo.attach(HEAD_MOTOR);  // set servo pin
        for (headPos = 20; headPos < 81; headPos += 1) 
        {
          headServo.write(headPos);              
          delay(10);                   
        }
        delay(100);
        headServo.detach();
        //delay(100);
         //sneeze
        player.volume(30);
        player.play(1);//sneeze sound
        delay(1000);
        Serial.println("Relay On");
        digitalWrite(relay,HIGH);
        // Let's turn on the relay...
        delay(1000);
  
        // Let's turn off the relay...
        digitalWrite(relay, LOW);
        Serial.println("Relay OFF");
        delay(2000); 

        //restart music
        player.volume(30);
        player.play(5);
        delay(5000);
        //raise head
        headServo.attach(HEAD_MOTOR);  // set servo pin
        delay(100);
        for (headPos = 80; headPos > 20; headPos -= 1)
        {
          headServo.write(headPos);
          delay(35);
        }
        delay(100);
        headServo.detach();

        //turn body
        basementServo.attach(BASEMENT_MOTOR);  // set servo pin
        delay(100);
        for (basementPos = 135; basementPos < 180; basementPos += 1) 
        {
          basementServo.write(basementPos);              
          delay(30);                 
        }
        basementServo.detach();

        //down board
        slidingServo.attach(SLIDING_MOTOR);  // set servo pin
        delay(100);
        slidingServo.write(0);
        delay(1900);
        slidingServo.write(90);
        delay(100);
        slidingServo.detach();
        delay(100);

        //down head
        headServo.attach(HEAD_MOTOR);  // set servo pin
        delay(100);
        for (headPos = 20; headPos < 81; headPos += 1) 
        {
          headServo.write(headPos);              
          delay(45);                       
        }
        headServo.detach();
        //music off
       delay(5000);
        player.pause();  //pause the mp3
       delay(100);
       delay(5000);

    }
    else 
    {
      Serial.println("Connecting to DFPlayer Mini failed!");
    }
 }
 }
  else  //inside
  {
    if(switchOneState != lastSwitchOneState)  //set position for the inside state
    {
      basementServo.attach(BASEMENT_MOTOR);  // set servo pin
      for (basementPos = 178; basementPos > 0; basementPos -= 1)  //turn facing the wall
      {
        basementServo.write(basementPos);
        delay(30);
      } 
      basementServo.detach();  // set servo pin
      delay(100);
    }
   digitalWrite(TRIG_PIN_BACK, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(TRIG_PIN_BACK, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN_BACK, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(ECHO_PIN_BACK, HIGH);
    // Calculating the distance
    delay(50);
    distance= duration*0.034/2;
    // Prints the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.println(distance);  
    Serial.println(headPos);

    if(distance<200)
    { 
      if (player.begin(softwareSerial)) {

        //turn body
          basementServo.attach(BASEMENT_MOTOR);  
          delay(100);
          for (basementPos = 0; basementPos < 30; basementPos += 1) 
          {
            basementServo.write(basementPos);              
            delay(30);                
          }
          basementServo.detach(); 
         //sneeze   
        player.volume(30);
        player.play(1);//sneeze sound
        delay(1000);
    
        digitalWrite(relay,HIGH);
        Serial.println("Relay On");
        // Let's turn on the relay...
        delay(1000);
      
        // Let's turn off the relay...
        digitalWrite(relay, LOW);
        Serial.println("Relay OFF");
        delay(100);
  
        //raise head 
        headServo.attach(HEAD_MOTOR);  // set servo pin
        delay(100);
        for (headPos = 80; headPos > 20; headPos -= 1) 
          {
            headServo.write(headPos);              
            delay(45);                       
          }
         headServo.detach();
         delay(100);

          //start music
          // Set volume to maximum (0 to 30).
          player.volume(30);
          // Play MP3 file on the SD card
          player.play(5);
          delay(10000);
          //turn body
          basementServo.attach(BASEMENT_MOTOR);  
          delay(100);
          for (basementPos = 30; basementPos < 180; basementPos += 1) 
          {
            basementServo.write(basementPos);              
            delay(30);                
          }
          basementServo.detach();        

          delay(3000);
        delay(100);
        //raise board
        slidingServo.attach(SLIDING_MOTOR);  // set servo pin
        delay(50);
        slidingServo.write(180);              
        delay(1700);
        slidingServo.write(90);
        delay(100);
        slidingServo.detach();  
        delay(100);
        //down head
        headServo.attach(HEAD_MOTOR);  // set servo pin
        delay(100);
        for (headPos = 20; headPos < 80; headPos += 1) 
        {
          headServo.write(headPos);              
          delay(45);                       
        }
        headServo.detach();
        delay(100);
        //down board
        slidingServo.attach(SLIDING_MOTOR);  // set servo pin
        delay(50);
        slidingServo.write(0);
        delay(1900);
        slidingServo.write(90);
        delay(100);
        slidingServo.detach();
        delay(100);

        //turn body
        basementServo.attach(BASEMENT_MOTOR);  // set servo pin
        delay(100);
        for (basementPos = 178; basementPos > 0; basementPos -= 1)
        {
          basementServo.write(basementPos);
          delay(30);
        }                          
        basementServo.detach();  // set servo pin
        delay(100);
        
        delay(10000);
        player.pause();  //pause the mp3   

    }
     delay(5000);
  }
  }      
  // Delay a little bit to avoid bouncing
    delay(500);
  // save the current state as the last state,
  //for next time through the loop
  lastSwitchOneState   = switchOneState;
  delay(100);
}
