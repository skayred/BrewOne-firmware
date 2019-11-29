#include <OneWire.h>
#include <SoftwareSerial.h>
#include <SerLCD.h>
#include <ArduinoJson.h>

#include "display.h"
#include "temp_provider.h"
#include "temp_controller.h"

char tmpstring[10];

SoftwareSerial esp(3, 2);

TempProvider tempProvider(A2, A3);
Heater heater(12,13);
Display disp(6, tempProvider);
TempController tempController(tempProvider, heater);

StaticJsonDocument<400> doc;

void initESP() {
  Serial.write("Initializing ESP...\n");
  delay(500);
  String espTmp;

  while (!esp.available()) {
    delay(100);
  }

  while (!espTmp.startsWith("{\"status\":\"ready\"}")) {
    Serial.write("---\n");
    Serial.write(espTmp.c_str());
    delay(500);
    esp.write("OK\n");
    while (!esp.available()) {
      delay(100);
    }
    espTmp = esp.readString();
  }
}

void setup(void) {
  Serial.begin(9600);
  esp.begin(9600);
  initESP();

  disp.init();

  Serial.write("ESP connected\n");
}

void loop(void) {
  if (esp.available()) {
    DeserializationError error = deserializeJson(doc, esp.readString());

    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return;
    } else {
      Serial.println(doc["status"].as<const char*>());
    }
  }

  disp.render();
  tempController.perform();

  delay(200);
}
