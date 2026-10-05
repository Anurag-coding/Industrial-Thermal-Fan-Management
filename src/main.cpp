#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>
#include <string>

#include "TemperatureSensor.h"
#include "FanController.h"
#include "ThermalMonitor.h"
#include "Logger.h"

using namespace std;

int main()
{
    TemperatureSensor sensor;
    FanController fan;
    ThermalMonitor monitor;
    Logger logger;

    int temperature = 35;
    int load = 20;

    const int MAX_READINGS = 30;

    int minTemperature = 1000;
    int maxTemperature = 0;

    double totalTemperature = 0.0;

    int minLoad = 1000;
    int maxLoad = 0;

    double totalLoad = 0.0;

    int readings = 0;

    bool emergencyCooling = false;

    auto startTime =
        chrono::steady_clock::now();


    cout << endl;

    cout << "==================================================" << endl;
    cout << "       INDUSTRIAL THERMAL MANAGEMENT SYSTEM" << endl;
    cout << "==================================================" << endl;

    cout << "System Started..." << endl;
    cout << "Linux Thermal Driver Connected." << endl;
    cout << "Thermal Monitoring Activated." << endl;
    cout << "Total Readings : "
         << MAX_READINGS << endl;

    cout << "==================================================" << endl;


    for (int i = 1; i <= MAX_READINGS; i++)
    {

        // -----------------------------------------
        // INDUSTRIAL LOAD
        // -----------------------------------------

        if (i <= 8)
        {
            load = 90;
        }
        else if (i <= 14)
        {
            load = 100;
        }
        else if (i <= 22)
        {
            load = 25;
        }
        else
        {
            load = 5;
        }


        // -----------------------------------------
        // EXTREMELY HIGH TEMPERATURE
        // EMERGENCY COOLING STARTS ONLY AT 90°C
        // -----------------------------------------

        if (temperature >= 90)
        {
            emergencyCooling = true;
        }


        // -----------------------------------------
        // STOP EMERGENCY COOLING AFTER
        // TEMPERATURE FALLS BELOW 60°C
        // -----------------------------------------

        if (temperature <= 60)
        {
            emergencyCooling = false;
        }


        // -----------------------------------------
        // FAN CONTROL
        // -----------------------------------------

        int fanSpeed;

        if (emergencyCooling)
        {
            fanSpeed =
                fan.setFanSpeed(100);
        }
        else
        {
            fanSpeed =
                fan.calculateFanSpeed(
                    temperature
                );
        }


        // -----------------------------------------
        // GET RPM FROM LINUX DRIVER
        // -----------------------------------------

        int fanRPM =
            fan.getFanRPM();


        // -----------------------------------------
        // STATUS
        // -----------------------------------------

        const char* status =
            monitor.getStatus(
                temperature
            );


        // -----------------------------------------
        // RUNTIME
        // -----------------------------------------

        auto currentTime =
            chrono::steady_clock::now();

        double runtime =
            chrono::duration<double>(
                currentTime - startTime
            ).count();


        // -----------------------------------------
        // STATISTICS
        // -----------------------------------------

        if (temperature < minTemperature)
        {
            minTemperature = temperature;
        }

        if (temperature > maxTemperature)
        {
            maxTemperature = temperature;
        }

        totalTemperature += temperature;


        if (load < minLoad)
        {
            minLoad = load;
        }

        if (load > maxLoad)
        {
            maxLoad = load;
        }

        totalLoad += load;

        readings++;


        // -----------------------------------------
        // DISPLAY
        // -----------------------------------------

        cout << endl;

        cout << "--------------------------------------------------"
             << endl;

        cout << "Reading     : "
             << i << "/"
             << MAX_READINGS
             << endl;

        cout << "Runtime     : "
             << fixed
             << setprecision(1)
             << runtime
             << " sec"
             << endl;

        cout << "Load        : "
             << load
             << "%"
             << endl;

        cout << "Temperature : "
             << temperature
             << " °C"
             << endl;

        cout << "Fan Speed   : "
             << fanSpeed
             << "%"
             << endl;

        cout << "Fan RPM     : "
             << fanRPM
             << " RPM"
             << endl;

        cout << "Status      : "
             << status
             << endl;


        // -----------------------------------------
        // CRITICAL
        // -----------------------------------------

        if (temperature >= 70 &&
            temperature < 90)
        {
            cout << endl;

            cout << "WARNING: CRITICAL TEMPERATURE!"
                 << endl;

            cout << "Temperature approaching"
                 << " emergency level."
                 << endl;
        }


        // -----------------------------------------
        // EXTREMELY HIGH
        // -----------------------------------------

        if (temperature >= 90)
        {
            cout << endl;

            cout << "!!! EXTREMELY HIGH TEMPERATURE !!!"
                 << endl;

            cout << "EMERGENCY COOLING ACTIVATED!"
                 << endl;

            cout << "Emergency Fan Speed : "
                 << fanSpeed
                 << "%"
                 << endl;

            cout << "Emergency Fan RPM   : "
                 << fanRPM
                 << " RPM"
                 << endl;

            cout << "Temperature recovery in progress..."
                 << endl;
        }


        // -----------------------------------------
        // RECOVERY
        // -----------------------------------------

        if (emergencyCooling &&
            temperature < 90)
        {
            cout << endl;

            cout << "Cooling successful."
                 << endl;

            cout << "Temperature recovering..."
                 << endl;
        }


        // -----------------------------------------
        // NORMAL
        // -----------------------------------------

        if (temperature <= 40)
        {
            cout << endl;

            cout << "Temperature returned to NORMAL."
                 << endl;
        }


        // -----------------------------------------
        // LOG
        // -----------------------------------------

        string logStatus;

        if (emergencyCooling)
        {
            logStatus =
                "EMERGENCY COOLING";
        }
        else
        {
            logStatus =
                string(status);
        }

        logger.logData(
            i,
            load,
            temperature,
            fanSpeed,
            fanRPM,
            logStatus,
            runtime
        );


        // -----------------------------------------
        // NEXT TEMPERATURE
        // -----------------------------------------

        temperature =
            sensor.readTemperature(
                fanSpeed,
                load
            );


        this_thread::sleep_for(
            chrono::seconds(2)
        );
    }


    // -----------------------------------------
    // FINAL STATISTICS
    // -----------------------------------------

    double averageTemperature = 0.0;

    if (readings > 0)
    {
        averageTemperature =
            totalTemperature /
            readings;
    }


    double averageLoad = 0.0;

    if (readings > 0)
    {
        averageLoad =
            totalLoad /
            readings;
    }


    auto endTime =
        chrono::steady_clock::now();

    double totalRuntime =
        chrono::duration<double>(
            endTime - startTime
        ).count();


    cout << endl << endl;

    cout << "==================================================" << endl;
    cout << "              THERMAL STATISTICS" << endl;
    cout << "==================================================" << endl;

    cout << "Total Readings      : "
         << readings << endl;

    cout << "Minimum Temperature : "
         << minTemperature
         << " °C" << endl;

    cout << "Maximum Temperature : "
         << maxTemperature
         << " °C" << endl;

    cout << "Average Temperature : "
         << fixed
         << setprecision(2)
         << averageTemperature
         << " °C" << endl;

    cout << "Minimum Load        : "
         << minLoad
         << "%" << endl;

    cout << "Maximum Load        : "
         << maxLoad
         << "%" << endl;

    cout << "Average Load        : "
         << fixed
         << setprecision(2)
         << averageLoad
         << "%" << endl;

    cout << "Total Runtime       : "
         << fixed
         << setprecision(1)
         << totalRuntime
         << " sec" << endl;

    cout << "==================================================" << endl;

    cout << "Monitoring Completed." << endl;

    cout << "==================================================" << endl;

    return 0;
}
