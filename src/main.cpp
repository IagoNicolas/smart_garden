#include <Arduino.h>
#include "SensorReader.h"
#include <utility>

void setup() {
    Serial.begin(9600);
    Serial3.begin(300);  // baixa velocidade para evitar corromper dados
    delay(2000);
}

void loop() {
    std::pair<float, int> result = getTempTdsValue();
    Serial.print("PH reading: ");
    Serial.println(getPhValue());
    Serial.print("Temperature reading (ºC): ");
    Serial.println(result.first);
    Serial.print("TDS reading: ");
    Serial.println(result.second);
    delay(2000);
}