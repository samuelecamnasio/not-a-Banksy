#include <Servo.h> // include la Libreria Servo.h
//OUTSIDE MODE

#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

// Use pins 2 and 3 to communicate with DFPlayer Mini
static const uint8_t PIN_MP3_TX = 10; // Connects to module's RX 
static const uint8_t PIN_MP3_RX = 11; // Connects to module's TX 
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);

// Create the Player object
DFRobotDFPlayerMini player;

Servo headServo;  // create Servo object
Servo slidingServo;  // create Servo object
Servo basementServo;  // create Servo object
int relay = 51; // Out for light 

int pos = 0;  
#define TRIG_PIN 4
#define ECHO_PIN 5
#define BASEMENT_MOTOR 13
#define SLIDING_MOTOR 49
#define HEAD_MOTOR 12
long distance;
long duration;

void setup() {
Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);   // set trigger pin to OUTPUT
  pinMode(ECHO_PIN, INPUT);    // set echo pin to INPUT
  pinMode(relay, OUTPUT); 
  softwareSerial.begin(9600);
  
  headServo.attach(HEAD_MOTOR);  // set 8 as servo pin
  delay(50);
  headServo.write(20);              
  delay(100);            
  headServo.detach();
/*
  basementServo.attach(BASEMENT_MOTOR);  // set 8 as servo pin
  basementServo.write(0);
    delay(1000);           
  basementServo.detach();
  */

  delay (1000);

}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);  

  if(distance<10)
  {  Serial.print("i'm in! ");
  
  //delay(5000);

         //basementServo.attach(BASEMENT_MOTOR);  // set 8 as servo pin
           //delay(30);
    //for (pos = 0; pos < 60; pos += 2) 
    //{
      //basementServo.write(pos);              
      //delay(60);      
                 
    //}

    //basementServo.detach();  // set 8 as servo pin



  
     //down head
     
       headServo.attach(HEAD_MOTOR);  // set 8 as servo pin

     for (pos = 20; pos < 81; pos += 1) 
      {
        headServo.write(pos);              
        delay(10);//faster ?                      
      }
    delay(100);
         headServo.detach();
    delay(10);
    if (player.begin(softwareSerial)) {
    Serial.println("OK");

    // Set volume to maximum (0 to 30).
    player.volume(30);
    // Play the first MP3 file on the SD card
    player.play(1);
  }
  else{
    Serial.println("non si sente");
  }
  delay(500);
  
      // Let's turn on the relay...
      digitalWrite(relay,HIGH);
      Serial.println("Relay On");
      Serial.println("CIAOOO");
      delay(100);
  
      // Let's turn off the relay...
      digitalWrite(relay, LOW);
      Serial.println("Relay OFF");
      delay(2000);

 // rotate body
 
 /*  basementServo.attach(BASEMENT_MOTOR);  // set 8 as servo pin
      for (pos = 0; pos < 180; pos += 1) 
      {
        basementServo.write(pos);              
        delay(30);                
      }
      basementServo.detach();  // set 8 as servo pin, maybe not detach, TRY IT
delay(10000);*/
//turn body
     // basementServo.attach(BASEMENT_MOTOR);  // set servo pin
   
      //for (pos = 58; pos > 0; pos -= 2)
      //{
        //basementServo.write(pos);
        //delay(60);
      //}                          
      //basementServo.detach();  // set servo pin
    
  //
  }
  delay(1000); // Waiting for a while

}
