#include <ArduinoJson.h>

#include "main.h"

void setup()
{
    Serial.begin(115200);
    Wire.begin(I2C_SDA, I2C_SCL);
    oled = new Display(&_display, SCREEN_ADDRESS);
}

void loop()
{
    uint32_t time = millis();

    if(Serial.available())
    {
        StaticJsonDocument<200> doc;
        DeserializationError error = deserializeMsgPack(doc, Serial);
        if(!error)
        {
            JsonVariant gt = doc["GT"].as<JsonVariant>();
            JsonVariant gu = doc["GU"].as<JsonVariant>();
            JsonVariant ct = doc["CT"].as<JsonVariant>();
            JsonVariant cu = doc["CU"].as<JsonVariant>();
            JsonVariant fr = doc["FR"].as<JsonVariant>();

            if(!gu.isNull())
            {
                gpuUsage = gu.as<uint8_t>();
                oled->addGPUUsage(gpuUsage);
            }
            if(!gt.isNull())
            {
                gpuTemperature = gt.as<uint8_t>();
            }
            if(!cu.isNull())
            {
                cpuUsage = cu.as<uint8_t>();
                oled->addCPUUsage(cpuUsage);
            }
            if(!ct.isNull())
            {
                cpuTemperature = ct.as<uint8_t>();
            }
            if(!fr.isNull())
            {
                framerate = fr.as<uint8_t>();
                oled->addFPS(framerate);
            }
        }
    }

    if(time - lastUpdate > 3000) {
        mode++;
        if(mode == 3)
            mode = 0;
        lastUpdate = millis();
    }
    if(mode == 0)
        oled->drawCPU(cpuUsage, cpuTemperature);
    else if(mode == 1)
        oled->drawGPU(gpuUsage, gpuTemperature);
    else if(mode == 2)
        oled->drawFPS(framerate);

    delay(10);
}