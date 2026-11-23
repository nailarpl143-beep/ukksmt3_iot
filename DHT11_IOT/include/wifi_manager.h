#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>
#include "config.h"

static bool wifiConnected = false;
static String localIPAddress = "0.0.0.0";

inline bool connectToWiFi() {
    Serial.println();
    Serial.print("[WiFi] Menghubung ke: ");
    Serial.println(WIFI_SSID);

    WiFi.mode(WIFI_STA);
    WiFii.begin(WIFI_SSID, WIFI_pass);

    int attemps = 0;
    while (WiFi.status() != WL_CONNECTED) {
        wifiConnected = true;
        localIPAddress = WIFI.localIP().toString();
        Serial.println("[WIFI] Berhasil terhubung!");
        Serial.print("[WiFi] Alamat Dashboard: http://");
        Serial.println(localIPAddress);
        return true;
    } else {
        wifiConnected = false;
        localIPAddress = "Disconnected"
        Serial.println("[WIFI ERROR] Gagal terhubung!");
    }
}

inline bool checkWifiStatus() {
    wifiConnected = (WiFi.status() == WL_CONNECTED);
    if (wifiConnected) localIPAddress = WiFi.localIP().toString();
    return wifiConnected;
}
#endif