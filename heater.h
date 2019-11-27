#ifndef HEATER_H
#define HEATER_H

#include <vector>

class Heater {
  bool isOn;
  int onPin;
  int powerPin;

private:
    void triggerButton(int pin);

public:
  Heater();
  void init(int on, int power);
  void turnOn();
  void turnOff();
  void increasePower(int steps);
  void turnMax();
};

#endif