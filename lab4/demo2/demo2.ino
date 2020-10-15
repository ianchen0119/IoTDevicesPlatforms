#include "DHT.h"

DHT dht(A0, DHT11);
#define trigPin 8
#define echoPin 7
long duration, distance;
float h, t, f;
float s;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  delay(1000);
  dht.begin();
  h = dht.readHumidity();//讀取濕度
  t = dht.readTemperature();//讀取攝氏溫度
  f = dht.readTemperature(true);//讀取華氏溫度
  s = 1000000 / ((331.6 + 0.606 * t) * 100);
  Serial.println(h);
  Serial.println(t);
}

void beep(int l){
  tone(4, 293, l);
  delay(l);
  noTone(4);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration/s;
  //Serial.println(distance);
  if(distance < 100 && distance > 30){
    //beep(500);
  }
  else if(distance <= 30){
    //beep(250);
  }
  delay(50);

  h = dht.readHumidity();//讀取濕度
  t = dht.readTemperature();//讀取攝氏溫度
  f = dht.readTemperature(true);//讀取華氏溫度
  s = 1000000 / ((331.6 + 0.606 * t) * 100);
  Serial.println(h);
  Serial.println(t);
}
