#ifndef ASYNC_SERVER_H
#define ASYNC_SERVER_H

#include <WiFi.h>
#include <LittleFS.h>
#include "ESPAsyncWebServer.h"
#include <ArduinoJson.h>
#include "config.h"

// Objek server asinkron pada port 80
static AsyncWebServer asyncServer(80);

// Referensi variabel global (HANYA EXTERN, TANPA NILAI AWAL)
extern float currentTemp;
extern float currentHum;
extern bool wifiConnected;
extern unsigned long bootMillis;

// Inisialisasi flash file system littleFS
inline bool initLittleFS() {
    if (!LittleFS.begin(true)) {
        Serial.println("[LittleFS ERROR] Gagal mount file system flash!");
        return false;
    }
    Serial.println("[LittleFS] File system berhasil dimuat");
    return true;
}

// Mendapatkan rute web dan API asinkron
inline void initAsyncWebServer() {
    asyncServer.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");

    asyncServer.on("/api/now", HTTP_GET, [](AsyncWebServerRequest *request){
        JsonDocument doc;

        if (isnan(currentTemp) || isnan(currentHum)){
            doc["temp"] = nullptr;
            doc["hum"] = nullptr;
        } else {
            doc["temp"] = round(currentTemp * 10) / 10.0;
            doc["hum"] = round(currentHum * 10) / 10.0;
        }

        doc["online"] = wifiConnected;
        doc["rssi"] = WiFi.RSSI();
        doc["uptime"] = (millis() - bootMillis) / 1000;
        doc["ip"] = WiFi.localIP().toString();
        doc["ssid"] = WiFi.SSID();

        String response;
        serializeJson(doc, response);
        request->send(200, "application/json", response);  
    });

    asyncServer.onNotFound([](AsyncWebServerRequest *request){
        request->send(404, "text/plain", "404 not found pada esp32 async web server");
    });

    asyncServer.begin();
    Serial.println("[ASYNC HTTP] Server aktif dan siap melayani request di background");
}

#endif