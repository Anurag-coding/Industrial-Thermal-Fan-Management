#include "TemperatureSensor.h"

#include <cstdlib>
#include <ctime>

TemperatureSensor::TemperatureSensor()
{
    temperature = 35;
    ambientTemperature = 30;

    srand(static_cast<unsigned int>(time(nullptr)));
}

int TemperatureSensor::readTemperature(
    int fanSpeed,
    int load
)
{
    const double AMBIENT = 30.0;

    // -----------------------------------------
    // HEAT GENERATION
    // -----------------------------------------

    double heatGeneration =
        0.8 + (load * 0.12);


    // -----------------------------------------
    // FAN COOLING
    // -----------------------------------------

    double fanCooling =
        fanSpeed * 0.08;


    // -----------------------------------------
    // EMERGENCY COOLING
    // ONLY STARTS AT 90°C
    // -----------------------------------------

    if (temperature >= 90)
    {
        fanCooling += 8.0;
    }


    // -----------------------------------------
    // NATURAL COOLING
    // -----------------------------------------

    double naturalCooling = 0;

    if (temperature > AMBIENT)
    {
        naturalCooling =
            (temperature - AMBIENT) * 0.04;
    }


    // -----------------------------------------
    // TEMPERATURE CHANGE
    // -----------------------------------------

    double change =
        heatGeneration
        - fanCooling
        - naturalCooling;


    // Small random fluctuation
    int noise =
        (rand() % 3) - 1;


    temperature +=
        static_cast<int>(change)
        + noise;


    // -----------------------------------------
    // LIMITS
    // -----------------------------------------

    if (temperature < 30)
    {
        temperature = 30;
    }

    if (temperature > 100)
    {
        temperature = 100;
    }

    return temperature;
}
