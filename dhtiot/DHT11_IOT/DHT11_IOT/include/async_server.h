#ifndef ASYNC_SERVER_H
#define ASYNC_SERVER_H

#include <LittleFS.h>
#include "ESPAsyncWebServer.h"
#include <ArduinoJson.h>
#include "config.h"

// Objek server asinkron pada port 80
static AsyncWebServer asycServer(80);

// Referensi variabel global
extern float currentTemp;
extern float currentHum
extern bool wifiConnected;
extern unsigned long bootMillis;

// Inisialisasi flash file system littleFS
inline bool initLittleFS() {
    if (!LittleFS.begin(true)) {
        Serial.println("[LittleFS ERROR] Gagal mount file system flash!");
    }
    Serial.println("[LittleFS ERROR] file system berhasil dimuat");
    return true;

// Mendapatkan rute web dan API asinkron
inline void initAsyncWebServer() {
    // 1. Layani file statis (index.html, style.css) langsung dari LittleFS
    asyncServer.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");

    // 2. Endpoint REST API Realtime: Get/api/now
    asyncServer.on("/api/now", HTTS_GET, [](AsyncWebServerRequest *request){
        JsonDocument doc;

        if (isnan(currentTemp) || isnan(currentHum)){
            doc["temp"] = nullptr;
            doc["hum"] = nullptr;
        } else {
            doc["temp"] = round(currentTemp *10) / 10.0;
            doc["hum"] = round(currentHum *10) / 10.0;
        }

        dosc["online"] = wifiConnected;
        dosc["rssi"] = WiFi.RSSI();
        dosc["uptime"] = (millis() - bootMillis) / 1000;
        dosc["ip"] = WiFi.localIP().toString();
        dosc["ssid"] = WiFi.SSID();

        String response;
        serializeJson(doc, response);
        request->send(200, "application/json", response);  
    });
    // 2. Endpoint REST API Realtime: Get/api/now
    asyncServer.onNotFound([](AsyncWebServerRequest *request){
        request->send(404, "text/plain, "404" not found pada esp32 async web server");
    });

    asyncServer.begin();
    Serial.println("[ASYNC HTTP] Server aktif dan siap melayani request di background");
}

#endif