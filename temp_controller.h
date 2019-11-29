#ifndef TEMP_H
#define TEMP_H

#include <ArduinoSTL.h>

#include "temp_provider.h"
#include "heater.h"
#include "recipe_step.h"

class TempController {
  TempProvider provider;
  Heater heater;
  std::vector<RecipeStep> recipe;
  unsigned long timeInitiated;
  bool isPowered;
  int offset = 1;
  int currentStep;
  bool ended;

public:
  TempController();
  TempController(const TempProvider& tempProvider, const Heater& heaterController);
  void init();
  void addRecipeStep(int temp, int minutes);
  void perform();
};

#endif
