const int  switchOnePin = 2;    // digital in 2 (pin the switch one is attached to)

#include <Servo.h> // include la Libreria Servo.h

#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

// Use pins 2 and 3 to communicate with DFPlayer Mini
static const uint8_t PIN_MP3_TX = 10; // Connects to module's RX
static const uint8_t PIN_MP3_RX = 11; // Connects to module's TX
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);
// Create the Player object
DFRobotDFPlayerMini player;

Servo slidingServo;  // create Servo object
int pos = 0;  
#define TRIG_PIN 4
#define ECHO_PIN 5
#define SLIDINGMOTOR 49
long distance;
long duration;

int switchOneState = 0;         // current state of the switch
int lastSwitchOneState = 0;     // previous state of the switch

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
    // Init serial port for DFPlayer Mini
  softwareSerial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);   // set trigger pin to OUTPUT
  pinMode(ECHO_PIN, INPUT);    // set echo pin to INPUT
  int switchOneState = 0;         // current state of the switch
  int lastSwitchOneState = 0;     // previous state of the switch switch pins as an input
  pinMode(switchOnePin, INPUT);
  delay(500);
}


void loop() {

  // read the switch input pins:
  switchOneState   = digitalRead(switchOnePin);
  delay(50);


   digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(ECHO_PIN, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);  
  Serial.println(pos);

  if(distance<10)
  {  Serial.print("i'm in! ");
        if (switchOneState == HIGH) {
        // if the current state is HIGH then the button
        // went from off to on:
                slidingServo.attach(SLIDINGMOTOR);  // set 8 as servo pin
            delay(100);
            Serial.println("Switch one is on");
            slidingServo.write(180);              
            delay(1800);

            slidingServo.write(90);

            delay(5000);
    
            slidingServo.write(0);

            delay(1900);
            slidingServo.write(90);
            delay(100);
            slidingServo.detach();  // set servo pin

        } else {
          if (player.begin(softwareSerial)) {
              Serial.println("OK");
          
              // Set volume to maximum (0 to 30).
              player.volume(30);
              // Play the first MP3 file on the SD card
              player.play(5);
            } else {
              Serial.println("Connecting to DFPlayer Mini failed!");
            }
            // if the current state is LOW then the button
            // went from on to off:
            Serial.println("Switch one is off");
        }
      

  }

  delay (500);

  // compare the switchState to its previous state
        
  // Delay a little bit to avoid bouncing
  delay(50);  
  // save the current state as the last state,
  //for next time through the loop
  lastSwitchOneState   = switchOneState;
}
