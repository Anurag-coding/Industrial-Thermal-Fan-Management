#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger {
public:
    Logger();

    void logData(
        int reading,
        int load,
        int temperature,
        int fanSpeed,
        int fanRPM,
        const std::string& status,
        double runtime
    );
};

#endif
