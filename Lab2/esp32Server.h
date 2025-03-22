#ifndef HANDLE_H
#define HANDLE_H

#include <WebServer.h>
#include "html.h"
#include "info.h"

extern void setInterval();
WebServer server(80);

void handleRoot() 
{
  server.send(200, "text/html", html);
}
  
void handleWebClickFirst()
{
  setInterval();
  server.send(200, "text/html", "Click");
}

void handleWebClickSecond()
{
  Serial.println("C");
}

void sendSetInterval()
{
  server.send(200, "text/plain", "Set interval");
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
  server.on("/interval", sendSetInterval);
  server.begin();
}

#endif // HANDLE_H
