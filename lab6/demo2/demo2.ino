/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int potpin = 0;  // analog pin used to connect the potentiometer
int val, last = 0;    // variable to read the value from the analog pin
int direct = 1, degree = 0;

void setup() {
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  Serial.println(val);
  if (val < last){
    direct ^= 1;
  }
  last = val;
  if(direct == 1) degree += 1;
  else degree -= 1;
  if(degree < 0) degree = 0;
  else if (degree > 180) degree = 180;
  Serial.println(degree);
  myservo.write(degree);                  // sets the servo position according to the scaled value
  delay(100);                           // waits for the servo to get there
}
