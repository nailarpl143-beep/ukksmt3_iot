#include "config.h"
#include "dht_sensor.h"
#include "oled_display.h"
#include "wifi_manager.h"
#include "async_server.h"

// --- DEFINISI NYATA VARIABEL GLOBAL (Wajib ada di file utama) ---
float currentTemp = 0.0;
float currentHum = 0.0;
unsigned long bootMillis = 0;
static unsigned long lastSensorMillis = 0;

void setup() {
    Serial.begin(SERIAL_BAUD);
    delay(1000);
    bootMillis = millis();

    Serial.println();
    Serial.println("=================================================");
    Serial.println("  PROYEK 4 : DHT11 ASYNC WEB DASHBOARD (LITTLEFS)");
    Serial.println("=================================================");

    initOLED();
    showConnectingWifi(WIFI_SSID);

    initDHT();
    initLittleFS();

    bool connected = connectedWIFI();

    if (connected) {
        initAsyncWebServer();
    }
     
    readDHT(currentTemp, currentHum);
    drawDashboardOled(currentTemp, currentHum, connected, localIPAddress);
}

void loop() {
    unsigned long now = millis();

    if (now - lastSensorMillis >= SENSOR_READ_INTERVAL) {
        lastSensorMillis = now;

        if (readDHT(currentTemp, currentHum)) {
            Serial.print("[ASYNC NODE] Suhu: ");
            Serial.print(currentTemp, 1);
            Serial.print(" C | Hum: ");
            Serial.print(currentHum, 1);
            Serial.println("%");

            drawDashboardOled(currentTemp, currentHum, wifiConnected, localIPAddress);
        }
    }
}