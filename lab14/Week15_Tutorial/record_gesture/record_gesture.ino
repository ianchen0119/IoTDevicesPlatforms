#include <Wire.h>
#include "MPU6050.h"

MPU6050 IMU;
//ax, ay, az
#define NUM_AXES 3
// sometimes you may get "spikes" in the readings
// set a sensible value to turncate too large value
#define TRUNCATE_AT 20
// set a threshold to enable detection of motiion
#define ACCEL_THRESHOLD 5
// hom many samples you would like to record for a gesture
#define NUM_SAMPLES 30
// one-dimensional array for calibration
double baseline[NUM_AXES];
// one-dimensional array for features
float features[NUM_SAMPLES * NUM_AXES];

void setup() {
  // serial to display data
  Serial.begin(115200);
  while(!IMU.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
  delay(500);
  }
  recordBaseline();
}
void imu_read(float *ax, float *ay, float *az) {
  Vector normAccel = IMU.readNormalizeAccel();
    
  *ax = normAccel.XAxis;
  *ay = normAccel.YAxis;
  *az = normAccel.ZAxis;
}
void recordBaseline() {
    float ax, ay, az;

    for (int i = 0; i < 10; i++) {
        imu_read(&ax, &ay, &az);
        delay(100);
    }

    baseline[0] = ax;
    baseline[1] = ay;
    baseline[2] = az;
}

bool motionDetected(float ax, float ay, float az) {
    return (abs(ax) + abs(ay) + abs(az)) > ACCEL_THRESHOLD;
}

void recordIMU() {
    float ax, ay, az;

    for (int i = 0; i < NUM_SAMPLES; i++) {
        imu_read(&ax, &ay, &az);

        ax = constrain(ax - baseline[0], -TRUNCATE_AT, TRUNCATE_AT);
        ay = constrain(ay - baseline[1], -TRUNCATE_AT, TRUNCATE_AT);
        az = constrain(az - baseline[2], -TRUNCATE_AT, TRUNCATE_AT);

        features[i * NUM_AXES + 0] = ax;
        features[i * NUM_AXES + 1] = ay;
        features[i * NUM_AXES + 2] = az;

        delay(30);
    }
}

void printFeatures() {
    const uint16_t numFeatures = sizeof(features) / sizeof(double);
    
    for (int i = 0; i < numFeatures; i++) {
        Serial.print(features[i]);
        Serial.print(i == numFeatures - 1 ? ' ' : ',');
    }
    Serial.println(' ');
}

void loop() {
  // display the data
    float ax, ay, az;

    imu_read(&ax, &ay, &az);
    ax = constrain(ax - baseline[0], -TRUNCATE_AT, TRUNCATE_AT);
    ay = constrain(ay - baseline[1], -TRUNCATE_AT, TRUNCATE_AT);
    az = constrain(az - baseline[2], -TRUNCATE_AT, TRUNCATE_AT);
    if (!motionDetected(ax, ay, az)) {
        delay(10);
        return;
    }

    recordIMU();
    printFeatures();

    delay(2000);
} 
