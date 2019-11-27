#ifndef TEMP_H
#define TEMP_H

#include <vector>

class TempController {
  std::vector<RecipeStep> recipe;
  unsigned long timeInitiated;
  bool isPowered;
  int offset = 1;

private:
    void switchOn();
    void switchPower();
    void maxPower();
    void maintainPower();
    float getHLTOffset();

public:
  TempController();
  void init();
  void addRecipeStep(int temp, int minutes);
  void perform();
};

#endif