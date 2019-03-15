#include "Arduino.h"
#include "heltec.h"
#include "images.h"
#include<SPI.h>
#include<Wire.h>  //responsible for i2c communication

void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, true /*Serial Enable*/);

  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_10);
}

void loop() {
  Heltec.display->clear();

  Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER);
  Heltec.display->drawString(64, 22, "Hello World!");
  Heltec.display->display();
}
