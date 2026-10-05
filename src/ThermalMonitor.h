#ifndef THERMAL_MONITOR_H
#define THERMAL_MONITOR_H

class ThermalMonitor {
public:
    ThermalMonitor();

    const char* getStatus(int temperature);
    bool isCritical(int temperature);
};

#endif
