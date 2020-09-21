/*
  Fade

  This example shows how to fade an LED on pin 9 using the analogWrite()
  function.

  The analogWrite() function uses PWM, so if you want to change the pin you're
  using, be sure to use another PWM capable pin. On most Arduino, the PWM pins
  are identified with a "~" sign, like ~3, ~5, ~6, ~9, ~10 and ~11.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Fade
*/

int led = 9;           // the PWM pin the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 30;    // how many points to fade the LED by

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(led, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  int sensorValue = analogRead(A0);
  brightness = sensorValue * (255 / 1023.0);
  for(int i=0; i<3; i++){
    analogWrite(led, brightness);
    delay(300);
    analogWrite(led, LOW);
    delay(300);
  }
  delay(900);
  for(int i=0; i<3; i++){
    analogWrite(led, brightness);
    delay(600);
    analogWrite(led, LOW);
    delay(300);
  }
  delay(900);
  for(int i=0; i<3; i++){
    analogWrite(led, brightness);
    delay(300);
    analogWrite(led, LOW);
    delay(300);
  }
  delay(900);
}
