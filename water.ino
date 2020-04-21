#include <SoftwareSerial.h>       //Software Serial library
SoftwareSerial espSerial(3, 4);   //Pin 2 and 3 act as RX and TX. Connect them to TX and RX of ESP8266      
#define DEBUG true
String mySSID = "Harshit";       // WiFi SSID
String myPWD = "46d3fe489277"; // WiFi Password
String myAPI = "FXEAE0UX6LNJ1L0D ";   // API Key
String myHOST = "api.thingspeak.com";
String myPORT = "80";
String myFIELD = "field1"; 
int sendVal;
int BUTTON=6;
#define Grove_Water_Sensor 8 // Attach Water sensor to Arduino Digital Pin 8
#define IR 2   
int detection = HIGH; 
#define LED 13 // Attach an buzzer to Digital Pin 9 (or use onboard LED)
int i=0;
int sensorPin = A0; // select the input pin for LDR
int ldf=5;
int sensorValue = 0; // variable to store the value coming from the sensor
// ultrasonic
const int trigPin = 9;
const int echoPin = 10;
long duration;
int distance;


void setup() {
  //usonic
   pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  //ultraends
   pinMode(Grove_Water_Sensor, INPUT); // The Water Sensor is an Input
   pinMode(LED, OUTPUT); // The LED is an Output
   pinMode(ldf, OUTPUT); // The LED is an Output
   pinMode(IR, INPUT); 
  
  pinMode(BUTTON,INPUT);
  Serial.begin(9600);
  espSerial.begin(115200);
  
  espData("AT+RST", 1000, DEBUG);                      //Reset the ESP8266 module
  espData("AT+CWMODE=1", 1000, DEBUG);                 //Set the ESP mode as station mode
  espData("AT+CWJAP=\""+ mySSID +"\",\""+ myPWD +"\"", 1000, DEBUG);   //Connect to WiFi network
  /*while(!esp.find("OK")) 
  {          
      //Wait for connection
  }*/
  delay(1000);
}

void loop() {
  //wifi 
   if(digitalRead(BUTTON) == HIGH){
    sendVal =20; // Send a random number between 1 and 1000
    String sendData = "GET /update?api_key="+ myAPI +"&"+ myFIELD +"="+String(sendVal);
    espData("AT+CIPMUX=1", 1000, DEBUG);       //Allow multiple connections
    espData("AT+CIPSTART=0,\"TCP\",\""+ myHOST +"\","+ myPORT, 1000, DEBUG);
    espData("AT+CIPSEND=0," +String(sendData.length()+4),1000,DEBUG);  
    espSerial.find(">"); 
    espSerial.println(sendData);
    Serial.print("Value to be sent: ");
    Serial.println(sendVal);
     
    espData("AT+CIPCLOSE=0",1000,DEBUG);
    delay(10000);
  }
  //sonic 
digitalWrite(trigPin,LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 duration=pulseIn(echoPin, HIGH);
 
 if(duration*0.00017>0.6&&duration*0.00017<0.75)
{Serial.println("0.6 to 0.75");
digitalWrite(LED,HIGH);
    delay(500);
     digitalWrite(LED,LOW);
    delay(500);
     digitalWrite(LED,HIGH);
    delay(500);
   
}
if(duration*0.00017>0.3&&duration*0.00017<0.59)
{Serial.println("0.3 to 0.59");
digitalWrite(LED,HIGH);
    delay(50);
     digitalWrite(LED,LOW);
    delay(10);
     digitalWrite(LED,LOW);
    delay(10);
   
}
if(duration*0.00017<0.3)
{Serial.println("0.3 k eless");
for(i=0;i<3;i++)
{   digitalWrite(LED,HIGH);
    delay(50);
     digitalWrite(LED,LOW);
    delay(50);
     digitalWrite(LED,LOW);
    delay(50);
   
}
}
 delay(10);
//sonic


   /* The water sensor will switch LOW when water is detected.
   Get the Arduino to illuminate the LED and activate the buzzer
   when water is detected, and switch both off when no water is present */
   if( digitalRead(Grove_Water_Sensor) == LOW) {
      digitalWrite(LED,LOW);
      Serial.println("Not Present");
      
   }else {
      digitalWrite(LED,HIGH);
      Serial.println("present");
   }
   // water ka hai

  // ir ka hai
    detection = digitalRead(IR);
  if(detection == LOW){
    Serial.print(" obstacle!\n");
    
  }
  else{ 
    Serial.print("no obstacle!\n");
    digitalWrite(LED,HIGH);
    delay(100);
    digitalWrite(LED,LOW);
    delay(100);
    }
  // ldr 
  sensorValue = analogRead(sensorPin); // read the value from the sensor
Serial.println(sensorValue); //prints the values coming from the sensor on the screen
if(sensorValue >=500){
    digitalWrite(ldf,LOW);
  }
  else{  
    digitalWrite(ldf,HIGH);
  }
delay(100);

  delay(500);    // in msf
  
}


String espData(String command, const int timeout, boolean debug)
{
  Serial.print("AT Command ==> ");
  Serial.print(command);
  Serial.println("     ");
  
  String response = "";
  espSerial.println(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (espSerial.available())
    {
      char c = espSerial.read();
      response += c;
    }
  }
  if (debug)
  {
    //Serial.print(response);
  }
  return response;
}
