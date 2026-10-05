#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "include/thermal_ioctl.h"

using namespace std;

int main()
{
    int fd;

    cout << "======================================" << endl;
    cout << "   THERMAL DRIVER TEST" << endl;
    cout << "======================================" << endl;

    // Open virtual thermal device
    fd = open("/dev/thermal_controller", O_RDWR);

    if (fd < 0)
    {
        perror("Failed to open thermal controller");
        return 1;
    }

    cout << "Driver device opened successfully." << endl;


    // ----------------------------------
    // Set temperature
    // ----------------------------------

    int temperature = 65;

    if (ioctl(fd, THERMAL_SET_TEMPERATURE, &temperature) < 0)
    {
        perror("Failed to set temperature");
        close(fd);
        return 1;
    }

    cout << "Temperature set to: "
         << temperature << " C" << endl;


    // ----------------------------------
    // Read temperature
    // ----------------------------------

    temperature = 0;

    if (ioctl(fd, THERMAL_GET_TEMPERATURE, &temperature) < 0)
    {
        perror("Failed to get temperature");
        close(fd);
        return 1;
    }

    cout << "Temperature from driver: "
         << temperature << " C" << endl;


    // ----------------------------------
    // Set fan speed
    // ----------------------------------

    int fanSpeed = 75;

    if (ioctl(fd, THERMAL_SET_FAN_SPEED, &fanSpeed) < 0)
    {
        perror("Failed to set fan speed");
        close(fd);
        return 1;
    }

    cout << "Fan speed set to: "
         << fanSpeed << "%" << endl;


    // ----------------------------------
    // Read fan speed
    // ----------------------------------

    fanSpeed = 0;

    if (ioctl(fd, THERMAL_GET_FAN_SPEED, &fanSpeed) < 0)
    {
        perror("Failed to get fan speed");
        close(fd);
        return 1;
    }

    cout << "Fan speed from driver: "
         << fanSpeed << "%" << endl;


    // ----------------------------------
    // Set industrial load
    // ----------------------------------

    int load = 80;

    if (ioctl(fd, THERMAL_SET_LOAD, &load) < 0)
    {
        perror("Failed to set load");
        close(fd);
        return 1;
    }

    cout << "Industrial load set to: "
         << load << "%" << endl;


    // ----------------------------------
    // Read industrial load
    // ----------------------------------

    load = 0;

    if (ioctl(fd, THERMAL_GET_LOAD, &load) < 0)
    {
        perror("Failed to get load");
        close(fd);
        return 1;
    }

    cout << "Industrial load from driver: "
         << load << "%" << endl;


    // Close device
    close(fd);

    cout << "Driver communication successful!" << endl;
    cout << "======================================" << endl;

    return 0;
}
