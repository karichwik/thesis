#include<SoftwareSerial.h>

#define trigPin 9

#define echoPin 10

int counter ; 
int WaterLevelValue;

SoftwareSerial mySerial(2, 3);

int normalDistance;

boolean triggered = false;

long duration, distance;

void setup()

{

mySerial.begin(9600);

Serial.begin (9600);

delay(100);

pinMode(trigPin, OUTPUT);

pinMode(echoPin, INPUT);

long duration, distance;


}

void loop(){

  digitalWrite(trigPin, LOW);
  
  delay(1000);
  
  digitalWrite(trigPin, HIGH);
  
  delay(1000);
  
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  
  distance= duration*0.034/2;
  
  Serial.print("Distance: ");
  
  Serial.println(distance);
  
  Serial.print("Water level: ");
  WaterLevelValue = analogRead(A0); 
  Serial.println(WaterLevelValue);
  
  delay(100);

  if (distance <= 20){
  
  triggered = true;
  
  counter ++;

  
  
  }
  else{

    triggered = false;

    counter = 0;


  }
  if(WaterLevelValue >= 300){
    //triggered = true;

    counter ++;
  }
  else{
    //triggered = false;

    counter = 0;
  }


  Serial.print("Counter value: ");
  Serial.println(counter);
  

  if (triggered && counter == 10 && WaterLevelValue >= 300 ){
    Serial.println("sending sms");
    mySerial.println("AT+CMGF=1");
    
    //Sets the GSM Module in Text Mode
    
    delay(500);
    
    // Delay of 1000 milli seconds or 1 second
    
    mySerial.println("AT+CMGS=\"+639093222770\"\r");
    
    // Replace x with mobile number
    
    delay(500);
    
    mySerial.println("ALERT! The Water level reached it's limit!.");
    
    // The SMS text you want to send 
    delay(100);
    
    mySerial.println((char)26);
    
    // ASCII code of CTRL+Z
    
    delay(1000);

  counter = 0;
    
    } 


}
