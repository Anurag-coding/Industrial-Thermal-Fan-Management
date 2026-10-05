#ifndef THERMAL_IOCTL_H
#define THERMAL_IOCTL_H

#include <linux/ioctl.h>

/*
 * Magic number used to identify our thermal driver
 */
#define THERMAL_MAGIC 'T'

/*
 * Set simulated temperature
 */
#define THERMAL_SET_TEMPERATURE \
    _IOW(THERMAL_MAGIC, 1, int)

/*
 * Get current simulated temperature
 */
#define THERMAL_GET_TEMPERATURE \
    _IOR(THERMAL_MAGIC, 2, int)

/*
 * Set fan speed (PWM percentage)
 */
#define THERMAL_SET_FAN_SPEED \
    _IOW(THERMAL_MAGIC, 3, int)

/*
 * Get current fan speed
 */
#define THERMAL_GET_FAN_SPEED \
    _IOR(THERMAL_MAGIC, 4, int)

/*
 * Set industrial load percentage
 */
#define THERMAL_SET_LOAD \
    _IOW(THERMAL_MAGIC, 5, int)

/*
 * Get industrial load
 */
#define THERMAL_GET_LOAD \
    _IOR(THERMAL_MAGIC, 6, int)

/*
 * Emergency shutdown
 */
#define THERMAL_EMERGENCY_SHUTDOWN \
    _IO(THERMAL_MAGIC, 7)
/*
 * Get current fan RPM
 */
#define THERMAL_GET_FAN_RPM \
    _IOR(THERMAL_MAGIC, 8, int)
#endif
