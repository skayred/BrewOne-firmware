#ifndef RECIPE_STEP_H
#define RECIPE_STEP_H

class RecipeStep {
public:
  int temperature;
  int minutes;
  RecipeStep();
  RecipeStep(int tempIn, int minutesIn);
};

#endif
