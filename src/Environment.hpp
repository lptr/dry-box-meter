#pragma once

#include <SHT2x.h>
#include <Wire.h>

#include <Telemetry.hpp>

using namespace farmhub::client;

class Environment
    : public TelemetryProvider {
public:
    Environment()
        : TelemetryProvider() {
    }

    void begin(gpio_num_t sda, gpio_num_t scl) {
        sensor.begin(sda, scl);
        Serial.printf("Initialed HTU21D sensor on SDA = %d, SCL = %d, status = 0x%x\n", sda, scl, sensor.getStatus());
    }

protected:
    void populateTelemetry(JsonObject& json) override {
        sensor.read();
        auto temp = sensor.getTemperature();
        auto humidity = sensor.getHumidity();
        Serial.printf("Temperature: %f, humidity: %f\n", temp, humidity);
        json["temperature"] = temp;
        json["humidity"] = humidity;
    }

private:
    SHT2x sensor;
};
