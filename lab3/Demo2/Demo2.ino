const int numReadings = 10;
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average


// These constants won't change:
const int sensorPin = A0;    // pin that the sensor is attached to
const int ledPin = 9;        // pin that the LED is attached to

// variables:
int sensorValue = 0;         // the sensor value
int sensorMin = 1023;        // minimum sensor value
int sensorMax = 0;           // maximum sensor value


void setup() {
  // turn on LED to signal the start of the calibration period:
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  Serial.begin(9600);

  // calibrate during the first five seconds
  while (millis() < 5000) {
    sensorValue = analogRead(sensorPin);

    // record the maximum sensor value
    if (sensorValue > sensorMax) {
      sensorMax = sensorValue;
    }

    // record the minimum sensor value
    if (sensorValue < sensorMin) {
      sensorMin = sensorValue;
    }
  }
  Serial.println(sensorMax);
  Serial.println();
  Serial.println(sensorMin);
  // signal the end of the calibration period
  digitalWrite(13, LOW);
}

int smoothing(){
  total -= readings[readIndex];
  readings[readIndex] = sensorValue;
  total += sensorValue;
  readIndex = (readIndex + 1) % 10;
  return total / numReadings;
}

int calibration(){
  sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 255);
  sensorValue = constrain(sensorValue, 0, 255);
  return sensorValue;
}

void loop() {
  // read the sensor:
  sensorValue = analogRead(sensorPin);
  calibration();
  int smooth = smoothing();
  //Serial.print(sensorValue);
  //Serial.println(smooth);
  analogWrite(ledPin, sensorMax - smooth);
  delay(100);
}
