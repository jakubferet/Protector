#include <Homie.h>

void setup() {
  Serial.begin(115200);
  Serial << endl << endl;

  Homie_setFirmware("bare-minimum", "1.0.0"); // The underscore is not a typo! See Magic bytes
  Homie.setup();
}

void loop() {
  Homie.loop();
}
