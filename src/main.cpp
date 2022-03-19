#include <Arduino.h>

#include <Application.hpp>
#include <Task.hpp>
#include <Telemetry.hpp>
#include <wifi/WiFiManagerProvider.hpp>

#include "Display.hpp"

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
        display.begin();
    }

private:
    DryBoxDeviceConfig deviceConfig;
    DryBoxAppConfig appConfig;
    NonBlockingWiFiManagerProvider wifiProvider { tasks };
    Display display { tasks };
};

DryBoxApp app;

void setup() {
    app.begin();
}

void loop() {
    app.loop();
}
