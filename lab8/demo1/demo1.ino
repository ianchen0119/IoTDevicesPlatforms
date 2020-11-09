int sensorPin = A0; // select the input pin for the potentiometer
int ledPin = 13; // select the pin for the LED
int sensorValue = 0; // variable to store the value coming from the sensor
void setup ()
{
  pinMode (ledPin, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  Serial.begin (9600);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
}
void loop ()
{
  sensorValue = analogRead (sensorPin);
  if(sensorValue < 20){
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
  }
  else if(sensorValue >= 20 && sensorValue < 40){
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW); 
  }
  else if(sensorValue >= 40 && sensorValue < 60){
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW); 
  }
  else if(sensorValue >= 60){
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH); 
  }
  Serial.println (sensorValue, DEC);
  delay(50);
}
