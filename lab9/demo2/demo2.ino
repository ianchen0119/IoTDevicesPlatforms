#define PIROUT 2
void setup(){
  Serial.begin(9600);
  pinMode(PIROUT, INPUT);
  pinMode(8, OUTPUT);
}

void loop(){
  int sensorReading = analogRead(A0);
  Serial.println(sensorReading);
  if (digitalRead(PIROUT)==HIGH && sensorReading < 30){
    Serial.println("Some body is here");
    digitalWrite(8, HIGH);
  }
  else{
    Serial.println("Nothing Detected by PIR Sensor");
    digitalWrite(8, LOW);
  }
  delay(1000);
}
