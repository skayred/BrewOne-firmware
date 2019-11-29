#include "temp_controller.h"
#include "temp_provider.h"
#include "heater.h"
#include "config.h"

TempController::TempController() { }

TempController::TempController(const TempProvider& tempProvider, const Heater& heaterController) {
    timeInitiated = -1;
    provider = tempProvider;
    heater = heaterController;
    currentStep = 0;
    started = false;
    ended = false;
}

void TempController::init() { }

void TempController::addRecipeStep(int temp, int minutes) {
    if (!started) {
        started = true;
    }
    recipe.push_back(RecipeStep(temp, minutes));
}

void TempController::perform() {
    if (!started) {
        return;
    }
    float hltTemp = provider.getHLTTemp();
    float bltTemp = provider.getBLTTemp();

    if ((millis()/(1000*60)) >= (timeInitiated + recipe.at(currentStep).minutes)) {
        if (currentStep < (recipe.size() - 1)) {
            currentStep++;
        } else {
            ended = true;
        }
    }

    int desiredTemp = recipe.at(currentStep).temperature + HLT_OFFSET;

    if ((!isPowered) && (hltTemp < (desiredTemp - offset))) {
        if (timeInitiated < 0) {
            heater.turnMax();
        } else {
            heater.turnOn();
        }
    }

    if (isPowered && (hltTemp > (desiredTemp - offset)) && (hltTemp < (desiredTemp + offset))) {
        if (timeInitiated < 0) {
            timeInitiated = millis();
        }
    }

    if (isPowered && (hltTemp > (desiredTemp + offset))) {
        heater.turnOff();
    }
}
