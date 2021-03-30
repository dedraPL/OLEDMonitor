#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#include "display.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET 16
#define SCREEN_ADDRESS 0x3C

#define I2C_SDA 4
#define I2C_SCL 15

Adafruit_SSD1306 _display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Display* oled;

uint32_t lastUpdate = 0;
uint8_t mode = 0;

uint8_t cpuUsage = 0, cpuTemperature = 0, gpuUsage = 0, gpuTemperature = 0, framerate = 0;

#endif