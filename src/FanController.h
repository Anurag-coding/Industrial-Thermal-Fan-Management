#ifndef FAN_CONTROLLER_H
#define FAN_CONTROLLER_H

class FanController
{
private:
    int device;
    int fanSpeed;

public:
    FanController();
    ~FanController();

    int calculateFanSpeed(int temperature);

    // Directly set fan speed
    int setFanSpeed(int speed);

    int getFanSpeed();
    int getFanRPM();
};

#endif
