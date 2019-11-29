#include <Arduino.h>
#include "heater.h"

Heater::Heater() { }

Heater::Heater(int onn, int power) {
    onPin = onn;
    powerPin = power;
    isOn = false;
}

void Heater::init() {
    pinMode(onPin, OUTPUT);
    pinMode(powerPin, OUTPUT);
}

void Heater::turnOn() {
    if (!isOn) {
        triggerButton(onPin);
        isOn = true;
    }
}

void Heater::turnOff() {
    if (isOn) {
        triggerButton(onPin);
        isOn = false;
    }   
}
  
void Heater::increasePower(int steps) {
    for (int i = 0 ; i < steps ; i++) {
        triggerButton(powerPin);
    }
}

void Heater::turnMax() {
    turnOn();
    increasePower(4);
}

void triggerButton(int pin) {
    digitalWrite(pin, HIGH);
    delay(50);
    digitalWrite(pin, LOW);
}
