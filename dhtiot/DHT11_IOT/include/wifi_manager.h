#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>
#include "config.h"

static bool wifiConnected = false;
static String localIPAddress = "0.0.0.0";

inline bool connectedWIFI() {
    Serial.println();
    Serial.println("[WIFI] Menghubungkan ke: ");
    Serial.println(WIFI_SSID);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 40) {
        delay(500);
        Serial.print(".");
        attempts++;
    }
    Serial.println();

    if (WiFi.status() == WL_CONNECTED) {
        wifiConnected = true;
        localIPAddress = WiFi.localIP().toString();
        Serial.println("[WIFI] Berhasil terhubung!");
        Serial.print("[WIFI] Alamat dashboard: http://");
        Serial.println(localIPAddress);
        return true;
    } else {
        wifiConnected = false;
        localIPAddress = "Disconnected";
        Serial.println("[WIFI ERROR] Gagal terhubung ke wifi.");
        return false;
    }
}

inline bool checkWIFIStatus() {
    wifiConnected = (WiFi.status() == WL_CONNECTED);
    if (wifiConnected) {
        localIPAddress = WiFi.localIP().toString();
    }
    return wifiConnected;
}

#endif