# Industrial Thermal Management & Dynamic Fan Controller

A Linux-based software simulation of an industrial thermal management system developed in **C++ on Ubuntu**. The project simulates temperature variation under changing industrial loads, automatically controls fan speed, communicates with a custom Linux kernel driver using `ioctl()`, monitors fan RPM, records thermal data, and activates emergency cooling during critical conditions.

---

## 1. Project Overview

Industrial systems such as servers, machines, embedded equipment, and computing systems can generate significant heat under high workloads. Continuous temperature monitoring and automatic cooling are important for preventing overheating and maintaining safe operation.

This project implements a complete software-based thermal management pipeline:

```text
Industrial Load
      |
      v
Temperature Sensor Simulation
      |
      v
Thermal Monitor
      |
      v
Fan Controller
      |
    ioctl()
      |
      v
Linux Kernel Thermal Driver
      |
      v
Virtual Fan / Simulated Hardware
      |
      v
Fan Speed + RPM
      |
      v
Temperature Recovery
```

---

## 2. Objectives

The main objectives of the project are:

- Simulate an industrial thermal environment.
- Monitor temperature continuously.
- Simulate changing industrial workloads.
- Automatically adjust fan speed according to temperature.
- Demonstrate user-space and kernel-space communication.
- Implement a custom Linux thermal device driver.
- Control a virtual fan through `ioctl()`.
- Monitor simulated fan RPM.
- Detect high and critical temperatures.
- Activate emergency cooling automatically.
- Store thermal readings in CSV format.
- Generate final thermal statistics after monitoring.

---

## 3. Key Features

- Real-time simulated temperature monitoring
- Variable industrial load simulation
- Automatic fan-speed control
- Linux character-device thermal driver
- User-space/kernel-space communication using `ioctl()`
- Virtual fan PWM control
- Fan RPM monitoring
- Thermal status monitoring
- Critical-temperature detection
- Emergency cooling
- Temperature recovery
- Runtime statistics
- CSV data logging
- 30-reading monitoring cycle
- Fully software-based simulation
- No physical hardware required

---

## 4. System Architecture

The system is divided into two major layers:

### 4.1 User Space

```text
+--------------------------------------+
|       C++ Thermal Management App     |
+--------------------------------------+
| TemperatureSensor                    |
| ThermalMonitor                       |
| FanController                        |
| Logger                               |
+--------------------------------------+
                 |
                 | ioctl()
                 v
        /dev/thermal_controller
```

### 4.2 Kernel Space

```text
+--------------------------------------+
|       Linux Kernel Thermal Driver    |
+--------------------------------------+
| Temperature Handling                 |
| Fan Speed Control                    |
| Industrial Load Handling             |
| Fan RPM Simulation                   |
+--------------------------------------+
                 |
                 v
        Virtual / Simulated Hardware
```

---

## 5. Project Workflow

Each monitoring cycle follows this process:

```text
1. Generate industrial load
          |
          v
2. Calculate / read temperature
          |
          v
3. Determine thermal status
          |
          v
4. Calculate required fan speed
          |
          v
5. Send fan speed using ioctl()
          |
          v
6. Read fan RPM from driver
          |
          v
7. Display thermal information
          |
          v
8. Store reading in CSV file
          |
          v
9. Update simulated temperature
          |
          v
10. Repeat monitoring cycle
```

---

## 6. Temperature Monitoring and Control

The thermal status is determined according to the simulated temperature.

```text
Temperature       Status                  Fan Action
------------------------------------------------------------
< 40°C            NORMAL                  Fan OFF / Low
40–59°C           WARM                    Low Cooling
60–69°C           HIGH TEMPERATURE        Moderate Cooling
70–89°C           CRITICAL                High Cooling
≥ 90°C            EXTREMELY HIGH          Emergency Cooling
```

The system continuously adjusts the fan according to the current temperature.

---

## 7. Emergency Cooling

When the temperature becomes extremely high, the system activates maximum cooling.

```text
EXTREMELY HIGH TEMPERATURE
          |
          v
EMERGENCY COOLING ACTIVATED
          |
          v
Fan PWM = 100%
          |
          v
Fan RPM = 1500 RPM
          |
          v
Temperature Decreases
          |
          v
CRITICAL
          |
          v
HIGH TEMPERATURE
          |
          v
WARM
          |
          v
NORMAL
```

The application does not terminate when an emergency condition occurs. Instead, it continues monitoring while the cooling system attempts to reduce the temperature.

---

## 8. Fan Control

The fan controller uses temperature-based proportional control.

```text
Temperature Range      Fan PWM
--------------------------------
< 40°C                 0%
40–44°C                20%
45–49°C                30%
50–54°C                40%
55–59°C                50%
60–64°C                60%
65–69°C                70%
70–74°C                80%
75–79°C                90%
≥ 80°C                 100%
```

The selected PWM value is sent to the Linux thermal driver through `ioctl()`.

---

## 9. Fan RPM Model

The simulated fan RPM is calculated by the kernel driver.

```text
RPM = (Fan PWM × 1500) / 100
```

Example:

```text
PWM       RPM
----------------
0%        0 RPM
20%       300 RPM
30%       450 RPM
40%       600 RPM
50%       750 RPM
60%       900 RPM
70%       1050 RPM
80%       1200 RPM
90%       1350 RPM
100%      1500 RPM
```

---

## 10. Linux Kernel Driver

The project contains a custom Linux thermal kernel driver.

The driver creates the device:

```text
/dev/thermal_controller
```

The C++ application communicates with this device using Linux `ioctl()` calls.

The driver provides operations for:

- Getting temperature
- Setting temperature
- Getting fan speed
- Setting fan speed
- Getting industrial load
- Setting industrial load
- Getting fan RPM

---

## 11. Project Structure

```text
Industrial-Thermal-Management/
|
+-- src/
|   +-- main.cpp
|   +-- TemperatureSensor.cpp
|   +-- TemperatureSensor.h
|   +-- FanController.cpp
|   +-- FanController.h
|   +-- ThermalMonitor.cpp
|   +-- ThermalMonitor.h
|   +-- Logger.cpp
|   +-- Logger.h
|
+-- driver/
|   +-- thermal_driver.c
|   +-- Makefile
|   +-- ...
|
+-- include/
|   +-- thermal_ioctl.h
|
+-- logs/
|   +-- thermal_data.csv
|
+-- driver_test.cpp
+-- README.md
```

---

## 12. Module Description

### 12.1 `main.cpp`

Responsible for:

- Starting the thermal management system.
- Running the monitoring loop.
- Generating industrial load.
- Coordinating all modules.
- Displaying readings.
- Calculating final statistics.

### 12.2 `TemperatureSensor.cpp`

Responsible for:

- Simulating temperature changes.
- Modeling heat generation.
- Modeling fan cooling.
- Modeling natural cooling.
- Supporting temperature recovery.

### 12.3 `FanController.cpp`

Responsible for:

- Calculating fan PWM.
- Communicating with `/dev/thermal_controller`.
- Sending fan-speed commands using `ioctl()`.
- Reading fan speed.
- Reading fan RPM.

### 12.4 `ThermalMonitor.cpp`

Responsible for:

- Determining thermal status.
- Detecting critical temperature.
- Providing system thermal-state information.

### 12.5 `Logger.cpp`

Responsible for:

- Creating the log directory.
- Creating the CSV file.
- Recording timestamped thermal readings.
- Storing temperature, load, PWM, RPM, status, and runtime.

### 12.6 `thermal_driver.c`

Responsible for:

- Implementing the Linux kernel thermal driver.
- Creating `/dev/thermal_controller`.
- Handling IOCTL commands.
- Maintaining simulated thermal values.
- Maintaining fan speed and RPM values.

### 12.7 `thermal_ioctl.h`

Contains the common IOCTL definitions shared between the user-space application and kernel driver.

### 12.8 `driver_test.cpp`

A standalone test program used to verify communication between user space and the Linux thermal driver.

---

## 13. Data Logging

Thermal readings are stored in:

```text
logs/thermal_data.csv
```

The CSV file contains:

```text
Timestamp
Reading
Load(%)
Temperature(C)
Fan_PWM(%)
Fan_RPM
Status
Runtime(sec)
```

Example:

```text
Timestamp,Reading,Load(%),Temperature(C),Fan_PWM(%),Fan_RPM,Status,Runtime(sec)

2026-10-05 05:23:01,1,90,35,0,0,NORMAL,0.0
2026-10-05 05:23:03,2,90,46,30,450,WARM,2.0
2026-10-05 05:23:07,4,90,63,60,900,HIGH TEMPERATURE,6.0
2026-10-05 05:23:09,5,90,71,80,1200,CRITICAL,8.0
2026-10-05 05:23:18,9,100,93,100,1500,EMERGENCY COOLING,16.2
```

The CSV can be opened using spreadsheet software such as LibreOffice Calc or Microsoft Excel.

---

## 14. Thermal Statistics

After the monitoring cycle is completed, the application calculates:

- Total readings
- Minimum temperature
- Maximum temperature
- Average temperature
- Minimum load
- Maximum load
- Average load
- Total runtime

Example:

```text
==================================================
              THERMAL STATISTICS
==================================================
Total Readings      : 30
Minimum Temperature : XX °C
Maximum Temperature : XX °C
Average Temperature : XX.XX °C
Minimum Load        : XX%
Maximum Load        : XX%
Average Load        : XX.XX%
Total Runtime       : XX.X sec
==================================================
Monitoring Completed.
==================================================
```

---

## 15. Technologies Used

```text
Technology              Purpose
------------------------------------------------------------
C++                     User-space thermal application
C                       Linux kernel thermal driver
Linux Kernel             Kernel-level device interface
IOCTL                   User/kernel communication
Character Device        /dev/thermal_controller
G++                     C++ compilation
Make                    Kernel driver build
CSV                     Thermal data storage
Ubuntu Linux            Development environment
VirtualBox              Virtual Linux environment
```

---

## 16. Requirements

### Operating System

- Ubuntu Linux
- VirtualBox (optional)

### Software

- GCC / G++
- GNU Make
- Linux kernel headers
- Bash
- Standard C/C++ libraries


---

## 17. Driver Compilation and Installation

Navigate to the project:

```bash
cd ~/Industrial-Thermal-Management
```

Enter the driver directory:

```bash
cd driver
```

Build the driver:

```bash
make
```

Load the kernel module:

```bash
sudo insmod thermal_driver.ko
```

Verify the module:

```bash
lsmod | grep thermal_driver
```

Check the device:

```bash
ls -l /dev/thermal_controller
```

Return to the project directory:

```bash
cd ..
```

---

## 18. Driver Testing

Compile the driver test:

```bash
g++ driver_test.cpp -o driver_test
```

Run the test:

```bash
sudo ./driver_test
```

The test verifies:

```text
Temperature Set/Get
Fan Speed Set/Get
Industrial Load Set/Get
Fan RPM
Driver Communication
```

A successful test should display:

```text
Driver communication successful!
```

---

## 19. Application Compilation

From the project root:

```bash
cd ~/Industrial-Thermal-Management
```

Compile the C++ application:

```bash
g++ src/main.cpp \
src/TemperatureSensor.cpp \
src/FanController.cpp \
src/ThermalMonitor.cpp \
src/Logger.cpp \
-Iinclude \
-o thermal
```

---

## 20. Running the Application

The C++ application uses the `Makefile` located inside the `src/` directory.

Navigate to the source directory:

```bash
cd ~/Industrial-Thermal-Management/src
```

Build the application:

```bash
make
```

Run the application:

```bash
make run
```

The `make run` command starts the application without requiring `sudo`.

If the application has not been built yet, `make run` will build it automatically before running.

To remove compiled files:

```bash
make clean
```

To clean and rebuild the application:

```bash
make rebuild
```

To display the available Makefile commands:

```bash
make help
```

The application displays:

```text
Reading
Runtime
Load
Temperature
Fan Speed
Fan RPM
Status
```

The monitoring system runs for 30 readings and then displays the final thermal statistics.

---

## 21. Expected System Behavior

A normal thermal cycle may follow this pattern:

```text
NORMAL
   |
   v
WARM
   |
   v
HIGH TEMPERATURE
   |
   v
CRITICAL
   |
   v
EMERGENCY COOLING
   |
   v
Temperature decreases
   |
   v
HIGH TEMPERATURE
   |
   v
WARM
   |
   v
NORMAL
```

This demonstrates a closed-loop thermal management system.

---

## 22. Advantages

- Fully software-based simulation.
- No physical thermal hardware required.
- Demonstrates Linux system programming.
- Demonstrates kernel module development.
- Demonstrates user-space/kernel-space communication.
- Uses a real Linux character device.
- Demonstrates `ioctl()` communication.
- Provides automatic cooling control.
- Provides emergency thermal protection.
- Stores historical thermal data.
- Produces useful thermal statistics.
- Suitable for OS and systems-programming projects.

---

## 23. Limitations

This project is a software simulation.

The temperature sensor, industrial workload, and fan are simulated models rather than physical devices.

The fan RPM represents a calculated driver value and does not come from a physical fan sensor.

---

## 24. Future Enhancements

Possible future improvements include:

- Real-time graphical dashboard
- Live temperature graphs
- Configurable temperature thresholds
- Multiple thermal zones
- Multiple virtual fans
- PID-based fan control
- Database-based logging
- Web-based monitoring dashboard
- Remote monitoring
- Alert and notification system
- Integration with real temperature sensors
- Integration with real PWM fan hardware

---

## 25. Conclusion

The **Industrial Thermal Management & Dynamic Fan Controller** demonstrates an end-to-end Linux-based thermal control system.

The project combines:

```text
C++
  +
Linux System Programming
  +
Linux Kernel Module
  +
Character Device Driver
  +
IOCTL Communication
  +
Thermal Simulation
  +
Automatic Fan Control
  +
Emergency Cooling
  +
Data Logging
```

into a single software-based industrial thermal management system.

The project provides practical exposure to both **user-space C++ programming** and **Linux kernel-level system programming**, making it suitable for an academic systems-programming project and technical demonstration.

---


