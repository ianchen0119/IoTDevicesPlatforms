const int redPin = 3;
const int greenPin = 5;
const int bluePin = 6;
int NOTE_C4 =400;
int NOTE_C3 =300;
int NOTE_C2 =200;
void setup() {
  // initialize serial:
  Serial.begin(9600);
  // make the pins outputs:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(8, INPUT);
  pinMode(7, OUTPUT);

}
int noteDurations1[] = {
  1, 1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 
};
int noteDurations2[] = {
  1, 1 ,1 
};
int noteDurations3[] = {
  1, 1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 
};
int melody1[] = {
  NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4
};
int melody2[] = {
  NOTE_C3, NOTE_C3, NOTE_C3
};
int melody3[] = {
  NOTE_C2, NOTE_C2, NOTE_C2, NOTE_C2, NOTE_C2, NOTE_C2, NOTE_C2, NOTE_C2, NOTE_C2, NOTE_C2
};
void loop() {
  analogWrite(redPin, 255);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
  for (int thisNote = 0; thisNote < 10; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations1[thisNote];
    tone(8, melody1[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }  
  analogWrite(redPin, 255);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 0);
  for (int thisNote = 0; thisNote < 3; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations1[thisNote];
    tone(8, melody2[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
  analogWrite(redPin, 0);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 0);
  for (int thisNote = 0; thisNote < 10; thisNote++) {
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations3[thisNote];
    tone(8, melody3[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}
