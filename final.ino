int pirPin = 3; //the digital pin connected to the PIR sensor's output
bool force = false;
bool motion = false;
int output = 4;
int count=0;
char data =0;
bool flag=true;
#include <Wire.h>
#include "DHT.h"
#include<SoftwareSerial.h>
SoftwareSerial BTSerial(10, 11); // RX, TX for HC-05 Bluetooth module

#define DHTPIN 8
#define DHTTYPE DHT22
int flamePin = 7;
int buzzer = 12
;
int red = 12;
int motor = 9;
int swt = 4;
int count1=0;
DHT dht(DHTPIN, DHTTYPE);

void setup(void) {
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
//  digitalWrite(pirPin, LOW);
  pinMode(5, OUTPUT);
  //Bluetooth.begin(9600);
  pinMode(flamePin, INPUT);
  pinMode(swt, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(red, OUTPUT);
  Serial.begin(9600);
  pinMode(motor, OUTPUT);
 // pinMode(10, INPUT);
 // pinMode(11, OUTPUT);
  // Serial.println(F("DHTxx test!"));
  dht.begin();
  }

void loop(void) {
    int sensorValue = analogRead(A0);
    int pir = digitalRead(pirPin);         
    int switc = digitalRead(2);
    data=Serial.read();
    // Serial.println(pir+"pir kaj ");
    // Serial.println(pir);
    // Serial.println(sensorValue+"force kaj");
    // Serial.println(sensorValue);
    if (data=='1'){
      flag=false;
    }
    else{
      flag=true;
    }
    
    if (sensorValue > 50 && force == false){ 
    force = true;
    
    }
    if (motion == false && pir == 1){
      motion = true;
    }
    if(switc == 0 and flag){
      Serial.print('entry');
      if(force == true || motion == true){
        if (count>2){
          // Serial.println("Invasion");
          sendNotification("Burglar alert. Press 1 to turn it off");
        }
        count=count+1;
        digitalWrite(5,1);
        delay(1000);
  //      Bluetooth.print("Invasion!");
  //      Bluetooth.print(";");
     
      }
      
    }
    else{
        force = false;
        motion = false;
        count=0;
        digitalWrite(5,0);
        delay( 1000);
  //      Bluetooth.print("All good!");
  //  Bluetooth.print(";");
      }
  
  
  float t = dht.readTemperature();
  int flame = digitalRead(flamePin);
  int swi = digitalRead(swt);
  // Serial.println("Flame: ");
  // Serial.println(flame);
  // Serial.println("Temp: ");
  // Serial.println(t);
  // Serial.println("Count: ");
  // Serial.println(count1);
  
  if (swi == 0 and flag){
    // Serial.print('fire entry');
  if (flame == 0){
    if (count1>2){
      // Serial.println("Fire");
      sendNotification("Fire alert. Press 1 to turn it off");
    }
    //float t = dht.readTemperature();
    if (t>26.50){
    analogWrite(buzzer, HIGH);
    digitalWrite(motor, LOW);
    digitalWrite(red, HIGH);
    delay(3000);
    
    
    }
  
    else if (t>26){
    analogWrite(buzzer, HIGH);
    digitalWrite(motor, LOW);
    digitalWrite(red, HIGH);
    delay(2000);
    
      
    }else{
    analogWrite(buzzer, HIGH);
    digitalWrite(motor, LOW);
    digitalWrite(red, HIGH);
    delay(1000);
    }
  //  digitalWrite(motor, LOW);
  //  delay(1000);
    digitalWrite(motor, HIGH);
    
    delay(1000);
    count1=count1+1;
  }
  else{
    analogWrite(buzzer, LOW);
    digitalWrite(red, LOW);
    digitalWrite(motor, HIGH);
    delay(1000);
    count1=0;
    
    
  }
  }
  else{
    analogWrite(buzzer, LOW);
    digitalWrite(red, LOW);
    digitalWrite(motor, HIGH);
    delay(1000);
    count1=0;
  
  }
    // Serial.println("Force Sensor: ");
    // Serial.println(sensorValue);
    // Serial.println("Force flag: ");
    // Serial.println(force);
    // Serial.println("-----------");
    // Serial.println("PIR: ");
    // Serial.println(pir);
    // Serial.println("PIR flag: ");
    // Serial.println(motion);
    // Serial.println("-----------");
    // Serial.println("Burglar switch: ");
    // Serial.println(switc);
    delay(1000);
    
      
}

void sendNotification(String message) {
  BTSerial.println(message); // Send message via Bluetooth
  Serial.println("Sent: " + message); 
  delay(1000); // Delay to avoid flooding the Bluetooth serial
}