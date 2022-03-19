#include <Arduino.h>

#include <gfxfont.h>

#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSansBold24pt7b.h>
#include <GxEPD2_BW.h>
#include <Wire.h>

#include <Application.hpp>
#include <Task.hpp>
#include <Telemetry.hpp>
#include <wifi/WiFiManagerProvider.hpp>

#include "GxEPD2_display_selection_new_style.h"

using namespace farmhub::client;

class DryBoxDeviceConfig : public Application::DeviceConfiguration {
public:
    DryBoxDeviceConfig()
        : Application::DeviceConfiguration("dry-box", "mk1") {
    }
};

class DryBoxAppConfig : public Application::AppConfiguration {
public:
    DryBoxAppConfig()
        : Application::AppConfiguration(seconds { 5 }) {
    }
};

class DryBoxApp : public Application {
public:
    DryBoxApp()
        : Application("SimpleApp", "UNKNOWN", deviceConfig, appConfig, wifiProvider) {
    }

protected:
    void beginApp() override {
    }

private:
    DryBoxDeviceConfig deviceConfig;
    DryBoxAppConfig appConfig;
    NonBlockingWiFiManagerProvider wifiProvider { tasks };
};

DryBoxApp app;

void setup() {
    Serial.begin(115200);

    display.init();
    Serial.printf("Initialzed display %dx%d\n", display.width(), display.height());

    display.setTextColor(GxEPD_BLACK);
    display.firstPage();

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

    app.begin();
}

void loop() {
    app.loop();
}
