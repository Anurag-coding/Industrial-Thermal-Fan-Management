#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/ioctl.h>

#include "../include/thermal_ioctl.h"

#define DEVICE_NAME "thermal_controller"
#define CLASS_NAME  "industrial_thermal"

static dev_t device_number;
static struct cdev thermal_cdev;
static struct class *thermal_class;

/* Simulated hardware values */
static int temperature = 40;
static int fan_speed = 0;
static int fan_rpm = 0;
static int load = 50;
static int emergency_shutdown = 0;


/*
 * Open device
 */
static int thermal_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "thermal_driver: device opened\n");

    return 0;
}


/*
 * Close device
 */
static int thermal_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "thermal_driver: device closed\n");

    return 0;
}


/*
 * IOCTL communication
 */
static long thermal_ioctl(
    struct file *file,
    unsigned int command,
    unsigned long argument)
{
    int value;

    switch (command)
    {

        case THERMAL_SET_TEMPERATURE:

            if (copy_from_user(
                    &value,
                    (int __user *)argument,
                    sizeof(int)))
            {
                return -EFAULT;
            }

            temperature = value;

            printk(
                KERN_INFO
                "thermal_driver: temperature set to %d C\n",
                temperature
            );

            break;


        case THERMAL_GET_TEMPERATURE:

            value = temperature;

            if (copy_to_user(
                    (int __user *)argument,
                    &value,
                    sizeof(int)))
            {
                return -EFAULT;
            }

            break;


        case THERMAL_SET_FAN_SPEED:

            if (copy_from_user(
                    &value,
                    (int __user *)argument,
                    sizeof(int)))
            {
                return -EFAULT;
            }

            if (value < 0)
                value = 0;

            if (value > 100)
                value = 100;

            fan_speed = value;

            printk(
                KERN_INFO
                "thermal_driver: fan speed set to %d%%\n",
                fan_speed
            );

            break;


        case THERMAL_GET_FAN_SPEED:

            value = fan_speed;

            if (copy_to_user(
                    (int __user *)argument,
                    &value,
                    sizeof(int)))
            {
                return -EFAULT;
            }

            break;


        case THERMAL_SET_LOAD:

            if (copy_from_user(
                    &value,
                    (int __user *)argument,
                    sizeof(int)))
            {
                return -EFAULT;
            }

            if (value < 0)
                value = 0;

            if (value > 100)
                value = 100;

            load = value;

            printk(
                KERN_INFO
                "thermal_driver: industrial load set to %d%%\n",
                load
            );

            break;


        case THERMAL_GET_LOAD:

            value = load;

            if (copy_to_user(
                    (int __user *)argument,
                    &value,
                    sizeof(int)))
            {
                return -EFAULT;
            }

            break;
            
        case THERMAL_GET_FAN_RPM:

             fan_rpm = (fan_speed * 1500) / 100;

             value = fan_rpm;

             if (copy_to_user(
                    (int __user *)argument,
                    &value,
                    sizeof(int)))
             {
                  return -EFAULT;
             }

             printk(
                   KERN_INFO
                  "thermal_driver: fan RPM = %d\n",
                  fan_rpm
             );

             break;


        case THERMAL_EMERGENCY_SHUTDOWN:

            emergency_shutdown = 1;
            fan_speed = 100;

            printk(
                KERN_ALERT
                "thermal_driver: EMERGENCY SHUTDOWN ACTIVATED!\n"
            );

            break;


        default:

            return -EINVAL;
    }

    return 0;
}


/*
 * File operations
 */
static struct file_operations thermal_fops =
{
    .owner          = THIS_MODULE,
    .open           = thermal_open,
    .release        = thermal_release,
    .unlocked_ioctl = thermal_ioctl
};


/*
 * Driver initialization
 */
static int __init thermal_driver_init(void)
{
    int result;

    printk(
        KERN_INFO
        "thermal_driver: initializing virtual thermal driver\n"
    );


    /*
     * Allocate device number
     */
    result = alloc_chrdev_region(
        &device_number,
        0,
        1,
        DEVICE_NAME
    );

    if (result < 0)
    {
        printk(
            KERN_ERR
            "thermal_driver: failed to allocate device number\n"
        );

        return result;
    }


    /*
     * Initialize character device
     */
    cdev_init(
        &thermal_cdev,
        &thermal_fops
    );

    thermal_cdev.owner = THIS_MODULE;


    /*
     * Add character device
     */
    result = cdev_add(
        &thermal_cdev,
        device_number,
        1
    );

    if (result < 0)
    {
        unregister_chrdev_region(
            device_number,
            1
        );

        return result;
    }


    /*
     * Create device class
     */
    thermal_class = class_create(
        CLASS_NAME
    );

    if (IS_ERR(thermal_class))
    {
        cdev_del(&thermal_cdev);

        unregister_chrdev_region(
            device_number,
            1
        );

        return PTR_ERR(thermal_class);
    }


    /*
     * Create /dev/thermal_controller
     */
    if (IS_ERR(device_create(
        thermal_class,
        NULL,
        device_number,
        NULL,
        DEVICE_NAME)))
    {
        class_destroy(thermal_class);

        cdev_del(&thermal_cdev);

        unregister_chrdev_region(
            device_number,
            1
        );

        return -1;
    }


    printk(
        KERN_INFO
        "thermal_driver: driver loaded successfully\n"
    );

    printk(
        KERN_INFO
        "thermal_driver: device created at /dev/%s\n",
        DEVICE_NAME
    );

    return 0;
}


/*
 * Driver cleanup
 */
static void __exit thermal_driver_exit(void)
{
    device_destroy(
        thermal_class,
        device_number
    );

    class_destroy(
        thermal_class
    );

    cdev_del(
        &thermal_cdev
    );

    unregister_chrdev_region(
        device_number,
        1
    );

    printk(
        KERN_INFO
        "thermal_driver: driver unloaded\n"
    );
}


module_init(thermal_driver_init);
module_exit(thermal_driver_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Industrial Thermal Management Project");
MODULE_DESCRIPTION(
    "Virtual Industrial Thermal Management Driver"
);
MODULE_VERSION("1.0");
