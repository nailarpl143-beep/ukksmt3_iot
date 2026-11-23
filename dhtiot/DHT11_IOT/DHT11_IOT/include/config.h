#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

#define WIFI_SSID     "RPL SMK MVP"
#define WIFI_PASS     "*#Mufa161073*#"

#define DHT_PIN       4
#define DHT_TYPE      DHT11

#define OLED_SDA        21
#define OLED_SCL        22
#define OLED_I2C_ADDR   0X32
#define SCREEN_WIDTH    128
#define SCREEN_HEIGHT   64
#define OLED_RESET      -1

#define SERIAL_BAUD   115200
#define SENSOR_READ_INTERVAL 2000

#endif