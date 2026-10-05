#include "FanController.h"

#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "../include/thermal_ioctl.h"

using namespace std;


// ==========================================
// CONSTRUCTOR
// ==========================================

FanController::FanController()
{
    fanSpeed = 0;

    device = open(
        "/dev/thermal_controller",
        O_RDWR
    );

    if (device < 0)
    {
        perror(
            "FanController: failed to open thermal driver"
        );
    }
    else
    {
        cout << "FanController: thermal driver connected."
             << endl;
    }
}


// ==========================================
// DESTRUCTOR
// ==========================================

FanController::~FanController()
{
    if (device >= 0)
    {
        close(device);
    }
}


// ==========================================
// AUTOMATIC FAN CONTROL
// ==========================================

int FanController::calculateFanSpeed(int temperature)
{
    /*
        Temperature ranges:

        Below 40°C  -> 0% fan
        40-49°C     -> 20% fan
        50-59°C     -> 30% fan
        60-69°C     -> 30% fan
        70-79°C     -> 40% fan
        80-89°C     -> 50% fan
        90°C+       -> 100% fan
    */

    if (temperature < 40)
    {
        fanSpeed = 0;
    }
    else if (temperature < 50)
    {
        fanSpeed = 20;
    }
    else if (temperature < 60)
    {
        fanSpeed = 30;
    }
    else if (temperature < 70)
    {
        fanSpeed = 30;
    }
    else if (temperature < 80)
    {
        fanSpeed = 40;
    }
    else if (temperature < 90)
    {
        fanSpeed = 50;
    }
    else
    {
        // Extremely high temperature
        // Maximum cooling
        fanSpeed = 100;
    }


    // Send fan speed to Linux thermal driver
    setFanSpeed(fanSpeed);

    return fanSpeed;
}


// ==========================================
// DIRECT FAN SPEED CONTROL
// ==========================================

int FanController::setFanSpeed(int speed)
{
    // Limit speed between 0 and 100
    if (speed < 0)
    {
        speed = 0;
    }

    if (speed > 100)
    {
        speed = 100;
    }

    fanSpeed = speed;


    // Send PWM value to kernel driver
    if (device >= 0)
    {
        if (
            ioctl(
                device,
                THERMAL_SET_FAN_SPEED,
                &fanSpeed
            ) < 0
        )
        {
            perror(
                "FanController: failed to set fan speed"
            );
        }
    }


    return fanSpeed;
}


// ==========================================
// GET FAN SPEED
// ==========================================

int FanController::getFanSpeed()
{
    if (device >= 0)
    {
        int driverFanSpeed = 0;

        if (
            ioctl(
                device,
                THERMAL_GET_FAN_SPEED,
                &driverFanSpeed
            ) == 0
        )
        {
            fanSpeed = driverFanSpeed;
        }
    }


    return fanSpeed;
}


// ==========================================
// GET FAN RPM
// ==========================================

int FanController::getFanRPM()
{
    int rpm = 0;


    if (device < 0)
    {
        return -1;
    }


    if (
        ioctl(
            device,
            THERMAL_GET_FAN_RPM,
            &rpm
        ) < 0
    )
    {
        perror(
            "FanController: failed to read fan RPM"
        );

        return -1;
    }


    return rpm;
}
