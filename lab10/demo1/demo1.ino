#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include "BMP085.h"

MPU6050 accelgyro;
BMP085 barometer;

int16_t ax, ay, az;
int16_t gx, gy, gz;

float temperature;
float pressure;
float seaLevelPressure = 101830;
float altitude;
int32_t lastMicros;
#define LED_PIN 13
bool blinkState = false;

bool complete = true;
int16_t pgx, pgy, pgz;
int r;

int melody[] = {
  293
};
int noteDurations[] = {
  4
};

void setup(){
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Initial I2C");
  accelgyro.initialize();
  barometer.initialize();

  Serial.println("Test device connection");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  Serial.println(barometer.testConnection() ? "BMP085 connection successful" : "BMP085 connection failed");

  pinMode(LED_PIN, OUTPUT);
  pinMode(8, OUTPUT);
}

void loop(){
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  barometer.setControl(BMP085_MODE_TEMPERATURE);
  lastMicros = micros();
  while(micros() - lastMicros < barometer.getMeasureDelayMicroseconds());
  temperature = barometer.getTemperatureC();
  barometer.setControl(BMP085_MODE_PRESSURE_3);
  while(micros() - lastMicros < barometer.getMeasureDelayMicroseconds());

  pressure = barometer.getPressure();
  altitude = barometer.getAltitude(pressure, seaLevelPressure);

  /*Serial.print("a/g:\t");
  Serial.print(ax); Serial.print("\t");
  Serial.print(ay); Serial.print("\t");
  Serial.print(az); Serial.print("\t");
  Serial.print(gx); Serial.print("\t");
  Serial.print(gy); Serial.print("\t");
  Serial.println(gz); Serial.print("\t");

  Serial.print("T/P/A\t");
  Serial.print(temperature); Serial.print("\t");
  Serial.print(pressure); Serial.print("\t");
  Serial.println(altitude);*/

  if(complete){
    complete = false;
    r = random(1, 3);
    if(r == 1) Serial.println("Shaking in z");
    else Serial.println("Rotate more than 90 degrees");
    pgx = gx;
    pgy = gy;
    pgz = gz;
    digitalWrite(7, HIGH);
  }
  else if((r == 1 && az < 10000) || (r == 2 && (gx - pgx > 90 || gy - pgy > 90 || gz - pgz > 90))){
    complete = true;
    Serial.println("Mission Complete");
    digitalWrite(7, LOW);
    delay(2000);
  }
  else{
    for (int thisNote = 0; thisNote < 9; thisNote++) {
      int noteDuration = 1000 / noteDurations[thisNote];
      tone(8, melody[thisNote], noteDuration);
      int pauseBetweenNotes = noteDuration * 1.3;
      delay(pauseBetweenNotes);
      noTone(8);
    }
  }
  delay(100);
}
