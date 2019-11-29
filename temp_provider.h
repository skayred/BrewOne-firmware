#ifndef TEMP_PROVIDER_H
#define TEMP_PROVIDER_H

#include <OneWire.h>
#include "Queue.h"

class TempProvider {
    unsigned long lastTempTime;
    OneWire hltDS;
    OneWire bltDS;
    DataQueue<float> lastTemps;
private:
    float getTemp(OneWire ds);

public:
    TempProvider();
    TempProvider(int hltPin, int bltPin);
    void init();
    float getHLTTemp();
    float getBLTTemp();
    bool isStable();
};

#endif
