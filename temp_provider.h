#ifndef TEMP_PROVIDER_H
#define TEMP_PROVIDER_H

#include <vector>

class TempProvider {
  std::vector<float> lastTemps;

public:
  TempProvider();
  void init(int hltPin, int bltPin);
  float getHLTTemp();
  float getBLTTemp();
  bool isStable();
};

#endif