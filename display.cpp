#include "display.h"
#include "temp_provider.h"
#include <SoftwareSerial.h>
#include <SerLCD.h>

Display::Display(int dispPin, const TempProvider& provider) {
  displayPin = dispPin;

  tempProvider = provider;
}

void Display::render() {
  hltTemp = (int) tempProvider.getHLTTemp();
  bltTemp = (int) tempProvider.getBLTTemp();

  lcd.setCursor(0, 2);
  lcd.print("HLT:");
  lcd.print(hltTemp);
  lcd.print(" BLT:");
  lcd.print(bltTemp);
}

void Display::init() {
  SoftwareSerial display(displayPin, 5);
  display.begin(9600);
  lcd.begin(display);

  lcd.setBacklight(208, 240, 192);
  lcd.setContrast(10);

  lcd.clear();
  lcd.print("BrewOne");
}
