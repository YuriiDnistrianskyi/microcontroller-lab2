#ifndef SERAIL_READ_H
#define SERAIL_READ_H

#include <Arduino.h>

extern void setInterval();

void readSerialMonitor()
{
  if (Serial2.available() > 0)
  {
    String command = Serial2.readString();
    if (command == "C")
    {
      setInterval();
      // Serial2.println("C");
    } else {
      Serial2.print("Unknow command: ");
      Serial2.println(command);
    }
  }
}


#endif // SERIAL_READ_H