/**
 * \file deviceMapping.h
 * \brief  Interconnect the user parts (like LEDs components) to the hardware
 *  driver IC output (like PCA9685 driver) or generic driver.
 *      
 * \author Raphael Thurnherr
 * \version 0.1
 * \date 09.03.2019
 *
 *  With reading the partsDescriptor config file, these functions will create dynamically
 *  the connections between the user components parts (leds, motors, etc..) and the terminals
 *  of the driver IC. 
 * 
 */

#ifndef DEVICEMAPPING_H
#define DEVICEMAPPING_H

#define MAX_DRIVERS_PER_TYPE 25

/**
 * \struct attributes [driversDescriptor.h]
 *  Sub structure for devices.
 * -> include deviceInit structure for set the device registers
 */
struct deviceAttributes{
    struct deviceInit{
        unsigned char regAddr;
        unsigned char regData;
    } deviceInit[16];
};

/**
 * \struct devicesList [driversDescriptor.h]
 * structure to list the device settings
 * -> include attributes structure of device
 */
typedef struct devicesList{
    int   device_id;
    char type[15];
    unsigned char address;
    struct deviceAttributes attributes;
}devices_list;


/*
 * ****************************************************************************
 * ****************************************************************************
 */

struct driverAttribute{
    int device_channel;
};
    

/**
 * \struct device_subdriver [driversDescriptor.h]
 *  device_subdriver is used for reccursive drive if a device need 
 *  other driver to work:
 * 
 * For exemple:
 *  An I2C GPIO extender is not on the primary bus, but on a secondary I2Cbus
 *  via an I2C multiplexor IC.
 * 
 * For this exemple we need to "connect" the secondary bus to the primary via de I2C mux.
 * The I2C multiplexor IC need be setup before de final IC;
 * 
 */


struct device_subdrivers{
    int device_id;
    char device_type[15];
    struct driverAttribute attributes;
};


typedef struct device_drivers{
    int device_id;
    char device_type[15];
    struct driverAttribute attributes;
    struct device_subdrivers sub_driver;
} deviceDriver;

/**
 * \struct device_driver [driversDescriptor.h]
 *  Sub structure for devices.
 * -> include part_Driver structure
 */
struct device{
    int id;
    char interface[25];
    struct device_drivers driver;
};

/**
 * \struct dcMotor_attribute [driversDescriptor.h]
 *  Sub structure for parts.
 * -> include specific sub attribute Structure
 */
struct generic_motor_driver{
    struct device enable;
    struct device speed;
    struct device cw;
    struct device ccw;
};

/**
 * \struct partsList [driversDescriptor.h]
 * structure to list the parts of the robot
 */
typedef struct parts_list{
    int part_id;
    char type[15];
    struct generic_motor_driver dc_motor[MAX_DRIVERS_PER_TYPE];
    struct device stepper_motors[MAX_DRIVERS_PER_TYPE];
    struct device dout[MAX_DRIVERS_PER_TYPE];
    struct device din[MAX_DRIVERS_PER_TYPE];
    struct device ain[MAX_DRIVERS_PER_TYPE];
    struct device counter[MAX_DRIVERS_PER_TYPE];
    struct device rgbSensor[MAX_DRIVERS_PER_TYPE];
    struct device distanceSensor[MAX_DRIVERS_PER_TYPE];
    
}kehopsParts;


/**
 * \brief Open and load drivers descriptor configuration
 * \return code error
 */  
extern char LoadDriversDescriptor(char * fileName);


/**
 * \brief Open and load electronic devices descriptor configuration
 * \return code error
 */  
extern char LoadDevicesDescriptor(char * fileName);

#endif /* DEVICEMAPPING_H */

