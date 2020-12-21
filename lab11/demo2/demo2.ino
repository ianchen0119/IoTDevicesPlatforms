#include <SoftwareSerial.h>
#include "dht.h"
#define dht_dpin A0 

dht DHT;

unsigned long BAUD_RATE = 9600;
const int BLUETOOTH_TX = 8;
const int BLUETOOTH_RX = 7;
const int READ_TIME = 500; //ms
unsigned long prevMillis;

bool trans = false;

SoftwareSerial bluetooth(BLUETOOTH_TX, BLUETOOTH_RX);

void setup() {
  // Start serial communications.
  // The baud rate must be the same for both the serial and the bluetooth.
  Serial.begin(BAUD_RATE);
  bluetooth.begin(BAUD_RATE);
  Serial.println("Setup Complete");

  delay(1000);
}

void loop() {
  DHT.read11(dht_dpin);
  //Serial.println(DHT.humidity);
  delay(50);
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    String str = "";
    Serial.print("Input: ");
    
    prevMillis = millis();
    while (millis() - prevMillis < READ_TIME) {
      if (Serial.available()) {
        char c = Serial.read();
        if (c != 10 && c != 13) { // Don't send line end characters to HM10.
          str += c;
        }
      }
    }
    
    bluetooth.print(str);
    Serial.println(str);
  }

  if(trans){
    trans = false;
    Serial.print("Temperature / Humidity: ");
    Serial.print(DHT.temperature);
    Serial.print(" / ");
    Serial.println(DHT.humidity);

    bluetooth.print("From MASTER_0616018 Temperature / Humidity: ");
    bluetooth.print(DHT.temperature);
    bluetooth.print(" / ");
    bluetooth.println(DHT.humidity);
  }

  if (bluetooth.available()) {
    String str = "";
    Serial.print("HM10: ");
    
    prevMillis = millis();
    while (millis() - prevMillis < READ_TIME) {
      if (bluetooth.available()) {
        str += (char) bluetooth.read();
      }
    }
    Serial.println(str);

    if(str.indexOf("SLAVE_002") != -1) trans = true;
  }
}
