#include <Servo.h> // include la Libreria Servo.h

Servo myservo;  // create Servo object
int pos = 0;  
#define TRIG_PIN 4
#define ECHO_PIN 5
#define MOTOR 49
long distance;
long duration;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);   // set trigger pin to OUTPUT
  pinMode(ECHO_PIN, INPUT);    // set echo pin to INPUT
 // myservo.attach(8);  // set servo pin
  //myservo.write(0);
  delay (1000);
}


void loop() {
  // Clears the trigPin
    myservo.attach(MOTOR);  // set servo pin

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

      myservo.write(180);              
    delay(1700);

      myservo.write(90);
    delay(50000);

  }
    myservo.detach();

  delay (500);
}
