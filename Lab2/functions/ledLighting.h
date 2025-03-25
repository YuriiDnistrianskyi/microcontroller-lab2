#ifndef LEDLIGHTING_H
#define LEDLIGHTING_H

#include "../info/pins.h"
bool stateLeds[3] = {};
bool stateOther[3] = {};
uint8_t numberOfLeds = sizeof(stateLeds) / sizeof(stateLeds[0]);
bool flagChangeLeds = false;
uint8_t currentLed = 0;
uint32_t prevLedTime = 0;

void ledLighting(uint32_t delayTime)
{
  uint32_t nowTime = millis();
  if ((nowTime - prevLedTime) >= delayTime) 
  {
    prevLedTime = nowTime;
    currentLed = (currentLed + 1) % numberOfLeds;

    for (int i = 0; i < numberOfLeds; i++) {
      if (i == currentLed)
      {
        stateLeds[i] = HIGH;
      }
      else
      {
        stateLeds[i] = LOW;
      }
    }
    flagChangeLeds = true;
  }

  if (flagChangeLeds)
  {
    digitalWrite(ledPin1, stateLeds[0]);
    digitalWrite(ledPin2, stateLeds[1]);
    digitalWrite(ledPin3, stateLeds[2]);
    flagChangeLeds = false;
  }
}

#endif // LEDLIGHTING_H