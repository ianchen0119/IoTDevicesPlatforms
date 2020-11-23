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

  Serial.print("a/g:\t");
  Serial.print(ax); Serial.print("\t");
  Serial.print(ay); Serial.print("\t");
  Serial.print(az); Serial.print("\t");
  Serial.print(gx); Serial.print("\t");
  Serial.print(gy); Serial.print("\t");
  Serial.println(gz); Serial.print("\t");

  Serial.print("T/P/A\t");
  Serial.print(temperature); Serial.print("\t");
  Serial.print(pressure); Serial.print("\t");
  Serial.println(altitude);

  blinkState = !blinkState;
  digitalWrite(LED_PIN, blinkState);
  delay(100);
}
