#define trigPin 8
#define echoPin 7
long duration, distance;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
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
  distance = duration/58.2;
  Serial.println(distance);
  if(distance < 100 && distance > 30){
    beep(500);
  }
  else if(distance <= 30){
    beep(250);
  }
  delay(50);
}
