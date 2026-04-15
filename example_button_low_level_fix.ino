#include <Wire.h>
#include "PCF8575.h"

PCF8575 pcf8575(0x20);

void setup() {
  Serial.begin(115200);

  // Configure before begin() or after begin(); both now work correctly.
  pcf8575.pinMode(P0, INPUT);
  // Alternative: pcf8575.pinMode(P0, INPUT_PULLUP);

  if (!pcf8575.begin()) {
    Serial.println("PCF8575 init failed");
    while (1) {}
  }
}

void loop() {
  Serial.println(pcf8575.digitalRead(P0));
  delay(50);
}
