#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "config.h"

static Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET );
static bool oledAvaiable = false;

inline bool initOLED() {
    Wire.begin(OLED_SDA, OLED_SCL);
    if (!oled.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDR)) {
        Serial.println("[OLED ERROR] ");
        oledAvaiable = false;
        return false;
    }
    oledAvaiable = true;
    oled.clearDisplay();
    oled.setTextColor(SSD1306_WHITE);
    return true;
}

inline void showConnectingWifi(const char* ssid) {
    if (!oledAvaiable) return;
    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setCursor(0, 10);
    oled.println("Menyambung Wi-Fi...");
    oled.println("-------");
    oled.println("SSID: ");
    oled.println(ssid); 
    oled.display();
}

inline void drawDashboardOled(float temp, float hum, bool connected, String ip) {
    if (!oledAvaiable) return;

    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setCursor(0, 0);

    oled.println("DHT11 DASHBOARD");
    oled.println("----------------");

    oled.print("Suhu      : ");
    oled.print(temp);
    oled.println(" C");

    oled.print("Humidity  : ");
    oled.print(hum);
    oled.println(" %");

    oled.println("----------------");

    if (connected) {
        oled.println("WiFi: Connected");
        oled.print("IP: ");
        oled.println(ip);
    } else {
        oled.println("WiFi: Disconnected");
    }

    oled.display();
}
#endif