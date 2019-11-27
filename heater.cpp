#include "heater.h"

Heater::Heater() {
}

void Heater::init(int on, int power) {
    onPin = on;
    powerPin = power;
    isOn = false;
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
