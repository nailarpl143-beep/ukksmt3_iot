"#ifndef DHT_SENSOR_H
#define DHT_SENSOR_H

#include <DHT.h>
#include "config.h""

static DHT dhtSensor(DHT_PIN, DHT_TYPE);

inline void initDHT() {
    dhtSensor.begin();
    Serial.println("[DHT11] Driver sensor berhasil dinisialisai pada GPI0" + String(DHT_PIN));
}

inline bool readDHT(float &temp, float &hum) {
    float t = dhtSensor.readTemperature();
    float h = dhtSensor.readHumidity();

    if (isnan(t) || isnan(h)) {
        Serial.println("[DHT11 ERROR] Gagal membaca sensor!");
        return false;
    }
    temp = t;
    hum = h;
    return true;
}
#endif