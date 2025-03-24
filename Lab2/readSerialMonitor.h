#ifndef SERAIL_READ_H
#define SERAIL_READ_H

#include <Arduino.h>

extern void setInterval();

void readSerialMonitor()
{
  if (Serial2.available() > 0)
  {
    char command = Serial2.read();
    if (command == 'C')
    {
      setInterval();
      Serial2.println('R');
      Serial.println("send response");
    }
    else if (command == 'R') {
      setInterval();
      Serial.println("set Interval");
    }
    // else if (command == )
    // else {
    //   Serial.print("Unknow command: ");
    //   Serial.println(command);
    // }
  }
}


#endif // SERIAL_READ_H