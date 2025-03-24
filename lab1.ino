#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID "YALOH"
#define STAPSK "123123123"
#endif

#define BUTTON  D8  // GPIO15
#define L1  D4
#define L2  D3
#define L3  D7

const char* ssid = STASSID; 
const char* password = STAPSK;

ESP8266WebServer server(80);

volatile uint16_t click_count = 0;
const uint32_t debounce_timeout = 50;
volatile bool double_clicked = false;
volatile uint8_t step = 5;
volatile uint32_t-= last_update = 0;

const uint8_t scenario[] = { L3, L2, L1, L2, L3 };

const char PROGMEM page[] = R"html(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Button Click</title>
    <style>
        body {
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            background-color: #f4f4f4;
            font-family: Arial, sans-serif;
        }
        button {
            padding: 10px 20px;
            font-size: 16px;
            background-color: #007bff;
            color: white;
            border: none;
            border-radius: 5px;
            cursor: pointer;
            transition: background 0.3s;
        }
        button:hover {
            background-color: #0056b3;
        }
    </style>
    <script>
        function sendRequest() {
            fetch('/clicked', { method: 'GET' })
                .then(response => response.text())
                .then(data => console.log(data))
                .catch(error => console.error('Error:', error));
        }
    </script>
</head>
<body>
    <button ondblclick="sendRequest()">DOUBLE CLICK BUTTON</button>
</body>
</html>
)html";

void IRAM_ATTR isr() {
    static uint32_t last_press_time = 0;
    uint32_t current_time = micros() / 1000;
    
    if (current_time - last_press_time < debounce_timeout) {
        return;
    }

    if (click_count == 0 || current_time - last_press_time > 250) {
        last_press_time = current_time;
        click_count = 1;
        return;
    }

    click_count = 0;
    last_press_time = current_time;
    double_clicked = true;
}

void handleRoot() {
    server.send(200, "text/html", page);
}

void handleClick() {
    server.send(200);
    double_clicked = true;
}

void setupHardware() {
    pinMode(L1, OUTPUT);
    pinMode(L2, OUTPUT);
    pinMode(L3, OUTPUT);
    pinMode(BUTTON, INPUT);
    attachInterrupt(BUTTON, isr, FALLING);
    interrupts();
}

void setupWiFi() {
    WiFi.mode(WIFI_AP); 
    WiFi.softAP(ssid, password); 

    Serial.println("WiFi Access Point started");
    Serial.print("IP Address: ");
    Serial.println(WiFi.softAPIP()); 
}

void setupServer() {
    server.on("/", handleRoot);
    server.on("/clicked", handleClick);
    server.begin();
    Serial.println("HTTP server started");
}

void updateLEDs() {
    if (double_clicked) {
        double_clicked = false;
        digitalWrite(scenario[step - 1], LOW);
        step = 0;
        last_update = 0;
    }
    
    unsigned long current_time = millis();
    if (step <= 5 && current_time - last_update > 500) {
        last_update = current_time;
        if (step > 0) {
            digitalWrite(scenario[step - 1], LOW);
        }
        if (step != 5) {
            digitalWrite(scenario[step], HIGH);
        }
        step++;
    }
}

void setup() {
    Serial.begin(9600);
    setupHardware();
    setupWiFi();
    setupServer();
}

void loop() {
    server.handleClient();
    updateLEDs();
}
