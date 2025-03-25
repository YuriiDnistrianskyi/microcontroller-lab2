#ifndef SERAIL_READ_H
#define SERAIL_READ_H

#include <Arduino.h>
#include "../info/commandsUART.h"

extern void setInterval();

void readSerialMonitor()
{
  if (Serial2.available() > 0)
  {
    char command = Serial2.read();
    command = command & 0x7F;
    if (command == 'C')
    {
      setInterval();
      Serial2.println(sendResponseUART);
      Serial.println("send response");
    }
    else if (command == 'R') {
      setInterval();
      Serial.println("set Interval");
    }
  }
}

#endif // SERIAL_READ_H