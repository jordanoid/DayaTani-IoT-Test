#include <Arduino.h>
#include <ArduinoJson.h>

const uint8_t battPin = A1;
const float minVolt = 3.0;
const float maxVolt = 4.2;
int battPercentage;
float battVoltage;
float adc;
int prevTime = 0;

String jsonString;
JsonDocument doc;

void setup(){
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(battPin, INPUT);
}

void loop(){
  // put your main code here, to run repeatedly:
  if (prevTime == 0 || millis() - prevTime > 1000){
    adc = analogRead(A1);
    battVoltage = adc * 5 / 1023;
    battPercentage = map(battVoltage, minVolt, maxVolt, 0, 100);
    battPercentage = constrain(battPercentage, 0, 100);

    doc["percentage"] = battPercentage;
    serializeJson(doc, jsonString);

    Serial.println(jsonString);
    prevTime = millis();
  }
}