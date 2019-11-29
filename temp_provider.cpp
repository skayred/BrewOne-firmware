#include "temp_controller.h"
#include "config.h"

TempProvider::TempProvider() { }

TempProvider::TempProvider(int hltPin, int bltPin) {
    hltDS = OneWire(hltPin);
    bltDS = OneWire(bltPin);
}

void TempProvider::init() {
    lastTempTime = -1;
}

float TempProvider::getHLTTemp() {
    return getTemp(hltDS);
}

float TempProvider::getBLTTemp() {
    float bltTemp = getTemp(bltDS);
    if ((lastTempTime < 0) || ((millis() - lastTempTime) >= TEMP_TIME_STEP)) {
        lastTemps.push(bltTemp);

        if (lastTemps.item_count() > TEMPS_SIZE) {
            lastTemps.pop();
        }
    }

    return bltTemp;
}

bool TempProvider::isStable() {
    int count = lastTemps.item_count();
    std::vector<double> xs;
    std::vector<double> ys;
    
    double xSums = 0;
    double ySums = 0;
    double xSquares = 0;

    for (int i = 0 ; i < lastTemps.item_count() ; i++) {
        xs.push_back(i+1);
        ys.push_back(lastTemps.at(i));
        
        xSums += (i+1);
        ySums += lastTemps.at(i);
        xSquares += (i+1)*(i+1);
    }

    double a = 0;
    double b;
    double c;
    double d;

    for (int i = 0 ; i < lastTemps.item_count() ; i++) {
        a += (i+1)*lastTemps.at(i);
    }
    a = count * a;
    b = xSums*ySums;
    c = count*xSquares;
    d = xSums*xSums;
    
    double slope = (a-b)/(c-d);

    return (abs(slope) < STABLE_SLOPE_LIMIT);
}

float TempProvider::getTemp(OneWire ds){
  byte data[12];
  byte addr[8];

  if ( !ds.search(addr)) {
      //no more sensors on chain, reset search
      ds.reset_search();
      return -1000;
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return -1000;
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28) {
      Serial.print("Device is not recognized");
      return -1000;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1); // start conversion, with parasite power on at the end

  byte present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE); // Read Scratchpad

  for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = ds.read();
  }

  ds.reset_search();

  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB); //using two's compliment
  float TemperatureSum = tempRead / 16;
  return TemperatureSum;
}
