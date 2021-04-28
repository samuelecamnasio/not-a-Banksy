#include <Servo.h> // include la Libreria Servo.h

Servo myservo;  // create Servo object
int pos = 0;  
#define TRIG_PIN 4
#define ECHO_PIN 5
#define MOTOR 13
long distance;
long duration;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);   // set trigger pin to OUTPUT
  pinMode(ECHO_PIN, INPUT);    // set echo pin to INPUT
  myservo.attach(MOTOR);
  delay(100);
 // myservo.write(0);
 for (pos = 178; pos > 0; pos -= 1)
    {
      myservo.write(pos);
      delay(20);

    }                          
    delay(100);
    myservo.detach();  // set servo pin
  //delay(20);
  //myservo.detach();
  delay (1000);
}


void loop() {
  // Clears the trigPin
    //myservo.attach(MOTOR);  // set servo pin

  //INSIDE

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
  //Serial.println(distance);  
  //Serial.println(pos);

  if(distance<10)
  { 
    //raise head
    //sneeze on the wall 
    //low head
    //rotate 
    //Serial.print("in! ");
     delay(100);
           myservo.attach(MOTOR);  // set 8 as servo pin
           delay(30);
    for (pos = 0; pos < 180; pos += 1) 
    {
      myservo.write(pos);   
      //Serial.print("aaaaa ");           
      delay(20);      
                 
    }

    myservo.detach();  // set 8 as servo pin



     delay(5000);
      //raise head
    //show picture
    //delay
       myservo.attach(MOTOR);  // set servo pin
    delay(30);
    for (pos = 178; pos > 0; pos -= 1)
    {
      myservo.write(pos);
      delay(20);

    }                          
    delay(100);
    myservo.detach();  // set servo pin
  }
  delay (500);

  //OUTSIDE
  //play music
  //rotate
  //raise head
  //show picture
  //low head
  //sneeze on QRcode
  //raise head
  //turn back

}
