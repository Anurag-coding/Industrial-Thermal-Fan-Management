#include "Logger.h"

#include <fstream>
#include <iomanip>
#include <ctime>
#include <sys/stat.h>

Logger::Logger()
{
    // Create logs directory if it doesn't exist
    mkdir("logs", 0755);

    // Check whether CSV already exists
    std::ifstream checkFile("logs/thermal_data.csv");

    bool fileExists = checkFile.good();

    checkFile.close();

    // Create CSV header for a new file
    if (!fileExists)
    {
        std::ofstream file(
            "logs/thermal_data.csv"
        );

        if (file.is_open())
        {
            file << "Timestamp,"
                 << "Reading,"
                 << "Load(%),"
                 << "Temperature(C),"
                 << "Fan_PWM(%),"
                 << "Fan_RPM,"
                 << "Status,"
                 << "Runtime(sec)"
                 << std::endl;

            file.close();
        }
    }
}


void Logger::logData(
    int reading,
    int load,
    int temperature,
    int fanSpeed,
    int fanRPM,
    const std::string& status,
    double runtime
)
{
    std::ofstream file(
        "logs/thermal_data.csv",
        std::ios::app
    );

    if (!file.is_open())
    {
        return;
    }


    // Get current system time
    std::time_t currentTime =
        std::time(nullptr);

    std::tm* localTime =
        std::localtime(&currentTime);


    // Format timestamp
    char timestamp[32];

    std::strftime(
        timestamp,
        sizeof(timestamp),
        "%Y-%m-%d %H:%M:%S",
        localTime
    );


    // Write CSV row
    file << timestamp
         << ","
         << reading
         << ","
         << load
         << ","
         << temperature
         << ","
         << fanSpeed
         << ","
         << fanRPM
         << ","
         << status
         << ","
         << std::fixed
         << std::setprecision(1)
         << runtime
         << std::endl;


    file.close();
}
