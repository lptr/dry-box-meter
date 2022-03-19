#include <Arduino.h>

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
    display.init();
    // comment out next line to have no or minimal Adafruit_GFX code
    display.setTextColor(GxEPD_BLACK);
    display.firstPage();
    do {
        display.fillScreen(GxEPD_WHITE);
        // comment out next line to have no or minimal Adafruit_GFX code
        display.print("Hello World!");
    } while (display.nextPage());

    app.begin();
}

void loop() {
    app.loop();
}
