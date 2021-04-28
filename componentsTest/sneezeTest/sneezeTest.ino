
#define echopin 5 // echo pin
#define trigpin 4 // Trigger pin

long dis_cm;
long ultra_time;
int set_cm = 10;

int relay = 51; // Out for light 

void setup(){
Serial.begin(9600);// initialize serial communication at 9600 bits per second:

pinMode (trigpin, OUTPUT);
pinMode (echopin, INPUT);

pinMode(relay, OUTPUT); 

delay(1000); // Waiting for a while
}

void loop(){ 
//*************************
ultra_read();
//*************************

Serial.print("Dis :");Serial.println(dis_cm); 


if(dis_cm<set_cm){
 
  digitalWrite(relay,HIGH);
  Serial.println("Relay On");
  // Let's turn on the relay...
  Serial.println("CIAOOO");
    delay(1000);

  // Let's turn off the relay...
  digitalWrite(relay, LOW);
    Serial.println("Relay OFF");

}

delay(100); 
}

//**********************ultra_read****************************
void ultra_read(){
digitalWrite(trigpin, LOW);
delayMicroseconds(2);
digitalWrite(trigpin, HIGH);
delayMicroseconds(10);
  digitalWrite(trigpin, LOW);

ultra_time = pulseIn (echopin, HIGH);
dis_cm =  ultra_time / 29 / 2; 
}
