#pragma once

#include <gfxfont.h>

#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSansBold24pt7b.h>
#include <GxEPD2_BW.h>
#include <Wire.h>

#include <Task.hpp>

#define GxEPD2_DISPLAY_CLASS GxEPD2_BW
#define GxEPD2_DRIVER_CLASS GxEPD2_213_B74    // GDEM0213B74 128x250, SSD1680

#define MAX_DISPLAY_BUFFER_SIZE 65536ul
#define MAX_HEIGHT(EPD) (EPD::HEIGHT <= MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8) ? EPD::HEIGHT : MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8))
GxEPD2_DISPLAY_CLASS<GxEPD2_DRIVER_CLASS, MAX_HEIGHT(GxEPD2_DRIVER_CLASS)> display(GxEPD2_DRIVER_CLASS(/*CS=5*/ SS, /*DC=*/17, /*RST=*/16, /*BUSY=*/4));

using namespace farmhub::client;

class Display : BaseTask {
public:
    Display(TaskContainer& tasks)
        : BaseTask(tasks, "Display") {
    }

    void begin() {
        display.init();
        Serial.printf("Initialzed display %dx%d\n", display.width(), display.height());
    }

protected:
    const Schedule loop(const Timing& timing) override {
        display.firstPage();
        display.setTextColor(GxEPD_BLACK);

        do {
            display.setCursor(0, 36);

            display.setFont(&FreeSans9pt7b);
            display.println("Temperature");
            display.println();
            display.setFont(&FreeSansBold24pt7b);
            display.println("24 °C");

            display.setFont(&FreeSans9pt7b);
            display.println("Humidity");
            display.println();
            display.setFont(&FreeSansBold24pt7b);
            display.println("20%");
        } while (display.nextPage());

        return sleepIndefinitely();
    }
};
