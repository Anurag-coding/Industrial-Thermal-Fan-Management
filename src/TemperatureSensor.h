#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

class TemperatureSensor {
private:
    double temperature;
    double ambientTemperature;

public:
    TemperatureSensor();

    int readTemperature(int fanSpeed, int load);

    double getTemperature();
    double getAmbientTemperature();
};

#endif
