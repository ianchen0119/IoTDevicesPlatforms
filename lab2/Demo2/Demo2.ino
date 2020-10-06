int melody[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
int noteIndex = 0;
unsigned long lastDebounceTime = 0;
bool press_50 = false, press_5000 = false;
int buttonState = LOW;
void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
}

void loop() {
  int sensorValue = analogRead(A0);
  sensorValue = map(sensorValue, 0, 1023, 260, 520);

  int reading = digitalRead(2);
  if(reading != buttonState){
    buttonState = reading;
    Serial.println(reading);
    lastDebounceTime = millis();
  }
  
  if(millis() - lastDebounceTime >= 2000 && buttonState == LOW){
    Serial.println(millis() - lastDebounceTime);
    press_5000 = true;
  }

  if(millis() - lastDebounceTime >= 50 && buttonState == LOW){
    press_50 = true;
  }

  if(millis() - lastDebounceTime >= 50 && buttonState == HIGH){
    if(press_5000){
      for(int thisNote = 0; thisNote < 10; thisNote++) {
        tone(8, melody[thisNote], 250);
        delay(250);
        noTone(8);
      }
    }
    else if(press_50){
      melody[noteIndex] = sensorValue;
      noteIndex = (noteIndex + 1) % 10;
    }
    press_5000 = false;
    press_50 = false;
  }
  buttonState = reading;
}
