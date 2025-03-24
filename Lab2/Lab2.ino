#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

#include "pins.h"
#include "esp32Server.h"
#include "ledLighting.h"
#include "esp32serialRead.h"

#define DEBOUNCE_TIME 200UL
#define SERIAL_SPEED 115200
#define SERIAL_SPEED_FOR_UART 115200 // 57600

bool stateButton = LOW;
volatile uint32_t prevDebounceTime = 0;
volatile uint8_t indexArray = 0;
uint32_t intervalArray[] = {2000, 1000, 500, 200};
uint32_t interval = intervalArray[indexArray];
uint8_t numberOfIntervals = sizeof(intervalArray) / sizeof(intervalArray[0]);
uint8_t listId = 0;

void IRAM_ATTR handleOnClick()
{
  uint32_t currentTime = millis();
  if ((currentTime - prevDebounceTime) > DEBOUNCE_TIME) 
  {
    listId = 0;
    setInterval();
    sendStateLeds();
    prevDebounceTime = currentTime;
  }
}

void setInterval()
{
  indexArray = (indexArray + 1) % numberOfIntervals;
}

void pinModeSetup()
{
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void setup()
{
  Serial.begin(SERIAL_SPEED);
  Serial2.begin(SERIAL_SPEED_FOR_UART, SERIAL_8N1, 16, 17);
  pinModeSetup();
  initWifi();
  attachInterrupt(digitalPinToInterrupt(buttonPin), handleOnClick, RISING);
}

void loop()
{
  server.handleClient();
  readSerialMonitor();
  interval = intervalArray[indexArray];
  ledLighting(interval);
}
