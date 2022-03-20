#include <Arduino.h>

#include <Application.hpp>
#include <Task.hpp>
#include <Telemetry.hpp>
#include <wifi/WiFiManagerProvider.hpp>

#include "Display.hpp"
#include "Environment.hpp"

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
        telemetryPublisher.registerProvider(environment);
    }

protected:
    void beginApp() override {
        display.begin();
        environment.begin(GPIO_NUM_21, GPIO_NUM_22);
    }

private:
    DryBoxDeviceConfig deviceConfig;
    DryBoxAppConfig appConfig;
    NonBlockingWiFiManagerProvider wifiProvider { tasks };
    Environment environment;
    Display display { tasks, environment };
};

DryBoxApp app;

void setup() {
    app.begin();
}

void loop() {
    app.loop();
}
