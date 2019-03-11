/**
 * \file partsDescriptor.h
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

#ifndef DRIVERSDESCRIPTOR_H
#define DRIVERSDESCRIPTOR_H

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
}device_attribute;
    

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

struct device_subdriver{
    int device_id;
    char device_type[15];
    struct driverAttribute attributes;
    struct device_subdriver sub_driver;
};

struct device_settings{
    int device_id;
    char device_type[15];
    struct device_subdriver sub_driver;
    struct driverAttribute attributes;
};

/**
 * \struct dcMotor_attribute [driversDescriptor.h]
 *  Sub structure for parts.
 * -> include specific sub attribute Structure
 */
struct generic_motor_driver_attribute{
    struct device_settings enable;
    struct device_settings speed;
    struct device_settings cw;
    struct device_settings ccw;
};


/**
 * \struct device_driver [driversDescriptor.h]
 *  Sub structure for devices.
 * -> include part_Driver structure
 */
struct device_driver{
    int id;
    struct device_settings driver;
};

/**
 * \struct partsList [driversDescriptor.h]
 * structure to list the parts of the robot
 */
typedef struct partsList{
    int device_id;
    char type[15];
    struct generic_motor_driver_attribute dc_motor[5];
    struct device_driver distanceSensor[2];
}parts_list;

parts_list partsList;

partsList.dc_motor[0].id =99;
partsList.dc_motor[0].driver.device_id =0;
partsList.dc_motor[0].driver.type;
partsList.dc_motor[0].driver.generic_motor_attributes.enable.device_id;
partsList.distanceSensor[0].id;
partsList.distanceSensor[0].driver.device_id
partsList.distanceSensor[0].driver.device_id =0;
partsList.distanceSensor[0].driver.device_type="efm8bb"
partsList.distanceSensor[0].driver.attributes.device_channel = 0
partsList.distanceSensor[0].driver.sub_driver.device_id=9;
partsList.distanceSensor[0].driver.sub_driver.device_type="i2cmux"
partsList.distanceSensor[0].driver.sub_driver.sub_driver.device_id=88;
partsList.distanceSensor[0].driver.sub_driver.sub_driver.device_type="i2cmux";
partsList.distanceSensor[0].driver.sub_driver.sub_driver.sub_driver.sub_driver;


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

#endif /* DRIVERSDESCRIPTOR_H */

