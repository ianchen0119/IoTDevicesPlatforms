#include <Servo.h>

Servo myservo;

// Sensor pins
#define sensorPower 7
#define sensorPin A0
// Value for storing water level
int val = 0;
int pos = 0;

void setup() { // Set D7 as an OUTPUT
  pinMode(sensorPower, OUTPUT);
  // Set to LOW so no power flows through the sensor digitalWrite(sensorPower, LOW);
  Serial.begin(9600);

  myservo.attach(9); 
}

void loop() { //get the reading from the function below and print it
  int level = readSensor();
  int map_level = map(level, 0, 500, 0, 100);
  Serial.print("Water level: ");
  Serial.println(level);
  Serial.print("Water mapped level: ");
  Serial.println(map_level);
  
  if(map_level < 75){
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  }
  delay(100);
}

//This is a function used to get the reading
int readSensor() {
  digitalWrite(sensorPower, HIGH); // Turn the sensor ON
  delay(10); // wait 10 milliseconds
  val = analogRead(sensorPin); // Read the analog value form sensor
  digitalWrite(sensorPower, LOW); // Turn the sensor OFF
  return val; // send current reading
}
