int answer;
int buttonState = 0;
int lastButtonState = 0; 

void setup() {
  // initialize the serial communication:
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(9, OUTPUT);
}

void loop() {
  // send the value of analog input 0:
  while (Serial.available() > 0) {
    int guess = Serial.parseInt();
    if (Serial.read() == '\n') {
      Serial.println(guess);
      if (guess == answer){
        digitalWrite(9, HIGH);
        Serial.println("correct");    
      }
      else{
        digitalWrite(9, LOW);
        Serial.println("wrong");
      }
    }
  }
  buttonState = digitalRead(2);
  if (buttonState != lastButtonState && buttonState == HIGH) {
    answer = map(constrain(analogRead(A0), 400, 700), 1, 1000, 1, 10);
    Serial.println(answer);
    delay(50); 
  }
  lastButtonState = buttonState;
  delay(2);
}
