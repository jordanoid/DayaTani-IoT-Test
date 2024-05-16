#include <ArduinoJson.h>

const int battPin = A1;
float minVolt = 3.0;
float maxVolt = 4.2;
float battPercentage;
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
  if (prevTime == 0 || millis() - prevTime >= 1000){
    adc = analogRead(A1);
    battVoltage = adc * 5 / 1023;
    battPercentage = map(battVoltage * 1000, minVolt * 1000, maxVolt * 1000, 0, 100);
    battPercentage = constrain(battPercentage, 0, 100);
    doc.clear(); 
    doc["percentage"] = battPercentage;
    serializeJson(doc, jsonString);

    Serial.println(jsonString);
    prevTime = millis();
  }
}