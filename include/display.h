#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "fifo.h"

#include "fps.h"
#include "cpu.h"
#include "gpu.h"
#include "font.h"

#define USAGE_X 68
#define USAGE_Y 28

#define TEMP_X 68
#define TEMP_Y 58

#define GRAPH_HEIGHT 25

#define CPU_GRAPH_WIDTH 60
#define GPU_GRAPH_WIDTH 60
#define FPS_GRAPH_WIDTH 125

class Display
{
public:
    Display(Adafruit_SSD1306 *oled, uint8_t address)
    {
        _oled = oled;

        if (!_oled->begin(SSD1306_SWITCHCAPVCC, address))
        {
            Serial.println(F("SSD1306 allocation failed"));
            for (;;)
                ; // Don't proceed, loop forever
        }

        fpsBuffer.trackValues = true;
        cpuBuffer.max = 100;
        gpuBuffer.max = 100;
    }

    void drawFPS(uint8_t fps)
    {
        _oled->clearDisplay();

        _oled->drawBitmap(0, 0, image_data_fps, 128, 64, 1);

        this->drawNumbers(fps, USAGE_X, USAGE_Y);

        this->drawGraph<uint8_t, FPS_GRAPH_WIDTH>(&fpsBuffer, 2, 56);

        _oled->display();
    }

    void drawCPU(uint8_t cpu, uint8_t temp)
    {
        _oled->clearDisplay();

        _oled->drawBitmap(0, 0, image_data_cpu, 128, 64, 1);

        this->drawNumbers(cpu, USAGE_X, USAGE_Y);
        if (temp > 99)
            temp = 99;
        this->drawNumbers(temp, TEMP_X, TEMP_Y);

        this->drawGraph<uint8_t, CPU_GRAPH_WIDTH>(&cpuBuffer, 2, 56);

        _oled->display();
    }

    void drawGPU(uint8_t gpu, uint8_t temp)
    {
        _oled->clearDisplay();

        _oled->drawBitmap(0, 0, image_data_gpu, 128, 64, 1);

        this->drawNumbers(gpu, USAGE_X, USAGE_Y);
        if (temp > 99)
            temp = 99;
        this->drawNumbers(temp, TEMP_X, TEMP_Y);

        this->drawGraph<uint8_t, GPU_GRAPH_WIDTH>(&gpuBuffer, 2, 56);

        _oled->display();
    }

    void addGPUUsage(uint8_t usage) {
        this->gpuBuffer.add(usage);
    }

    void addCPUUsage(uint8_t usage) {
        this->cpuBuffer.add(usage);
    }

    void addFPS(uint8_t fps) {
        this->fpsBuffer.add(fps);
    }

private:
    FIFO<uint8_t, CPU_GRAPH_WIDTH> cpuBuffer;
    FIFO<uint8_t, GPU_GRAPH_WIDTH> gpuBuffer;
    FIFO<uint8_t, FPS_GRAPH_WIDTH> fpsBuffer;

    Adafruit_SSD1306 *_oled;

    void drawNumbers(uint8_t num, uint8_t x, uint8_t y)
    {
        _oled->setFont(&Dialog_plain_30);
        _oled->setTextSize(1);
        _oled->setTextColor(WHITE);
        _oled->setCursor(x, y);
        _oled->print(num);
    }

    template <typename T, size_t N>
    void drawGraph(FIFO<T, N> *buffer, uint8_t x, uint8_t y)
    {
        float scale = (GRAPH_HEIGHT - 1) / (float) buffer->max;
        for (uint8_t i = 0; i < N; i++)
        {
            T value = buffer->get(i) > buffer->max ? buffer->max : (buffer->get(i) < buffer->min ? buffer->min : buffer->get(i));
            value = (uint8_t)(value * scale);
            _oled->drawPixel(x + i, y - value, WHITE);
        }
    }
};

#endif