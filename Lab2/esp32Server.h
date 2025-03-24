#ifndef HANDLE_H
#define HANDLE_H

#include <WebServer.h>
#include "html.h"
#include "info.h"

extern void setInterval();
extern bool stateLeds[3]; 
extern bool stateOther[3];
extern uint8_t listId;
WebServer server(80);

void handleRoot() 
{
  server.send(200, "text/html", html);
}
  
void handleWebClickFirst()
{
  setInterval();
  listId = 0;
  server.send(200, "text/html", "Click");
}

void handleWebClickSecond()
{
  Serial2.println('C');
  Serial.println("Send on ESP32");
  listId = 1;
}

void sendStateLeds()
{
  bool stateList[3];

  if (listId == 0)
  {
    String stateStr = "{\"stateLed1\":" + String(stateLeds[0]) + 
                    ",\"stateLed2\":" + String(stateLeds[1]) +
                    ",\"stateLed3\":" + String(stateLeds[2]) + "}";
  } 
  else if (listId == 1)
  {
    String stateStr = "{\"stateLed1\":" + String(stateOther[0]) + 
                    ",\"stateLed2\":" + String(stateOther[1]) +
                    ",\"stateLed3\":" + String(stateOther[2]) + "}";
  }

  server.send(200, "application/json", stateStr);
}

void initWifi()
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/click_f", handleWebClickFirst);
  server.on("/click_s", handleWebClickSecond);
  server.on("/interval", sendStateLeds);
  server.begin();
}

#endif // HANDLE_H
