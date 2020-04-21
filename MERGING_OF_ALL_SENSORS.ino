#define IR 2 
int sensorPin = A0; // select the input pin for LDR
int sensorValue = 0; 
int detection = HIGH;    // no obstacle
const int trigPin = 9;
const int echoPin = 10;
long duration;
int distance;
#define Grove_Water_Sensor 8 // Attach Water sensor to Arduino Digital Pin 8
#define LED 13 // Attach an LED to Digital Pin 9 (or use onboard LED)
void setup() {
// ultr Serial.begin(9600);   
  pinMode(IR, INPUT); 
   pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
//WATER
 pinMode(Grove_Water_Sensor, INPUT); // The Water Sensor is an Input
   pinMode(LED, OUTPUT); // The LED is an Output
}
void loop() { 
 // ULTRA
 // ULTRA
 // ULTRA
 digitalWrite(trigPin,LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 duration=pulseIn(echoPin, HIGH);
 Serial.println(duration*0.00017);
 delay(10);
 
//LDR
//LDR
//LDR
sensorValue = analogRead(sensorPin); // read the value from the sensor
Serial.println(sensorValue); //prints the values coming from the sensor on the screen
delay(100);
//IR
//IR
//IR
  detection = digitalRead(IR);
  if(detection == LOW){
    Serial.print("There is an obstacle!\n");
  }
  else{ 
    Serial.print("No obstacle!\n");
  }
  delay(500);    // in ms
 //Water
 //Water
 //Water
  /* The water sensor will switch LOW when water is detected.
   Get the Arduino to illuminate the LED and activate the buzzer
   when water is detected, and switch both off when no water is present */
   if( digitalRead(Grove_Water_Sensor) == LOW) {
      digitalWrite(LED,HIGH);
      Serial.println("Not Present");
   }else {
      digitalWrite(LED,LOW);
      Serial.println("Present");
   }
   
}
