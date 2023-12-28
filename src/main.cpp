#include <Arduino.h>
#include "ph_sensor.h"

void setup() {
    Serial.begin(9600);
    delay(2000);
}

void loop() {
    Serial.println(getPhValue());
}