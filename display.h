#ifndef DISPLAY_H
#define DISPLAY_H

#include <OneWire.h>
#include <SerLCD.h>

#include "temp_provider.h"

class Display {
    int displayPin;
    OneWire hltDS;
    OneWire bltDS;
    int hltTemp;
    int bltTemp;
    SerLCD lcd;
    TempProvider tempProvider;

public:
  Display(int dispPin, const TempProvider& provider);
  void render();
  void init();
};

#endif
