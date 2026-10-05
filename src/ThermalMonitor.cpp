#include "ThermalMonitor.h"

ThermalMonitor::ThermalMonitor()
{
}

const char* ThermalMonitor::getStatus(int temperature)
{
    if (temperature < 40)
    {
        return "NORMAL";
    }
    else if (temperature < 60)
    {
        return "WARM";
    }
    else if (temperature < 70)
    {
        return "HIGH TEMPERATURE";
    }
    else if (temperature < 90)
    {
        return "CRITICAL";
    }
    else
    {
        return "EXTREMELY HIGH";
    }
}

bool ThermalMonitor::isCritical(int temperature)
{
    return temperature >= 70;
}
