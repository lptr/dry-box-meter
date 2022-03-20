#pragma once

#include <gfxfont.h>

#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSansBold18pt7b.h>
#include <GxEPD2_BW.h>
#include <Wire.h>

#include <Task.hpp>

#include "Environment.hpp"

#define GxEPD2_DISPLAY_CLASS GxEPD2_BW
#define GxEPD2_DRIVER_CLASS GxEPD2_213_B74    // GDEM0213B74 128x250, SSD1680

#define MAX_DISPLAY_BUFFER_SIZE 65536ul
#define MAX_HEIGHT(EPD) (EPD::HEIGHT <= MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8) ? EPD::HEIGHT : MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8))
GxEPD2_DISPLAY_CLASS<GxEPD2_DRIVER_CLASS, MAX_HEIGHT(GxEPD2_DRIVER_CLASS)> display(GxEPD2_DRIVER_CLASS(/*CS=5*/ SS, /*DC=*/17, /*RST=*/16, /*BUSY=*/4));

using namespace farmhub::client;

class Display : BaseTask {
public:
    Display(TaskContainer& tasks, Environment& environment)
        : BaseTask(tasks, "Display")
        , environment(environment) {
    }

    void begin() {
        display.init();
        Serial.printf("Initialzed display %dx%d\n", display.width(), display.height());
    }

protected:
    const Schedule loop(const Timing& timing) override {
        updateIfNecessary();
        return sleepIndefinitely();
    }

private:
    void updateIfNecessary() {
        String temp = String(environment.getTemperature(), 1) + " C";
        String humidity = String(environment.getHumidity(), 1) + "%";

        if (temp == lastTemperature && humidity == lastHumidity) {
            return;
        }

        display.firstPage();
        display.setTextColor(GxEPD_BLACK);

        do {
            display.setCursor(0, 36);

            display.setFont(&FreeSans9pt7b);
            display.println("Temperature");
            display.println();
            display.setFont(&FreeSansBold18pt7b);
            display.println(temp);

            display.setFont(&FreeSans9pt7b);
            display.println("Humidity");
            display.println();
            display.setFont(&FreeSansBold18pt7b);
            display.println(humidity);
        } while (display.nextPage());

        lastTemperature = temp;
        lastHumidity = humidity;
    }

    Environment& environment;
    String lastTemperature;
    String lastHumidity;
};
