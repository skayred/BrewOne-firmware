#include "temp.h"

TempController::TempController() {
}

void TempController::init() {
    timeInitiated = -1;
}

void getHLTOffset() {
    return 6;
}

void TempController::addRecipeStep(int temp, int minutes) {
    recipe.pushBack(RecipeStep(temp, minutes));
}

void TempController::perform() {
    float hltTemp = getTemperature(hlt);
    float bltTemp = getTemperature(blt);

    if ((millis()/(1000*60)) >= (timeInitiated + recipe.at(currentStep).minutes)) {
        if (currentStep < (recipe.size() - 1)) {
            currentStep++;
        } else {
            ended = true;
        }
    }

    int desiredTemp = recipe.at(currentStep).temp + getHLTOffset();

    if ((!isPowered) && (hltTemp < (desiredTemp - offset))) {
        if (timeInitiated < 0) {
            maxPower();
        } else {
            maintainPower();
        }
    }

    if (isPowered && (hltTemp > (desiredTemp - offset)) && (hltTemp < (desiredTemp + offset))) {
        if (timeInitiated < 0) {
            timeInitiated = millis();
        }
    }

    if (isPowered && (hltTemp > (desiredTemp + offset))) {
        switchOn();
    }
}