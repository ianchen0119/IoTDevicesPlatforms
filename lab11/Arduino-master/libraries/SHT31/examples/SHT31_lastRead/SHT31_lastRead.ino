//
//    FILE: SHT31_lastRead.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.0.2
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/SHT31

#include "Wire.h"
#include "SHT31.h"

uint32_t start;
uint32_t stop;

SHT31 sht;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("SHT31_LIB_VERSION: \t");
  Serial.println(SHT31_LIB_VERSION);

  Wire.begin();
  sht.begin(0x44);
  Wire.setClock(100000);

  uint16_t stat = sht.readStatus();
  Serial.print(stat, HEX);
  Serial.println();
}

void loop()
{
  sht.read();         // default = true/fast       slow = false
  Serial.print("\t");
  Serial.print(sht.lastRead());
  Serial.print("\t");
  Serial.print(sht.getTemperature(), 1);
  Serial.print("\t");
  Serial.println(sht.getHumidity(), 1);
  delay(100);
}

// -- END OF FILE --