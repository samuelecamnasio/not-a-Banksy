#include <Servo.h> // include la Libreria Servo.h

Servo myservo;  // create Servo object
int pos = 0;  
#define TRIG_PIN 4
#define ECHO_PIN 5
#define MOTOR 12
long distance;
long duration;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);   // set trigger pin to OUTPUT
  pinMode(ECHO_PIN, INPUT);    // set echo pin to INPUT
  myservo.attach(MOTOR);  // set servo pin
  delay(90);
  
  myservo.write(20);
  delay (1000);
  myservo.detach();
}


void loop() {
  // Clears the trigPin

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
    myservo.attach(MOTOR);  // set servo pin
    delay(100);
for (pos = 20; pos < 80; pos += 1) 
    {
      myservo.write(pos);              
      delay(35);                       
    }

    delay(5000);
  
    

  for (pos = 80; pos > 20; pos -= 1)
    {
      myservo.write(pos);
      delay(35);
    }
    
  }
    myservo.detach();  // set servo pin

  delay (500);
}
