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
#define MAX_BOARD_DEVICE 50




struct driverAttribute{
    int device_channel;
};

struct device_subdrivers{
    char name[15];
    struct driverAttribute attributes;
};


struct driver_subdrivers{
    char name[15];
    int address;
    char device_type[15];
    struct driverAttribute attributes;
};


/**
 * \struct attributes [driversDescriptor.h]
 *  Sub structure for devices.
 * -> include deviceInit structure for set the device registers
 */

struct addrReg {
    int regAddr;
    int regData;
};
    
struct deviceAttributes{
    struct addrReg deviceInit[32];
    int frequency;
};

/**
 * \struct devicesList [driversDescriptor.h]
 * structure to list the device settings
 * -> include attributes structure of device
 */
typedef struct devicesList{
    char name[15];
    char type[15];
    int address;
    struct deviceAttributes attributes;
    struct device_subdrivers sub_driver;    
}devices_list;


/*
 * ****************************************************************************
 * ****************************************************************************
 */

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

typedef struct device_drivers{
    char name[15];
    struct driverAttribute attributes;
} hwDeviceDriver;

typedef struct generic_drivers{
    int device_id;
    char interface[MAX_DRIVERS_PER_TYPE];
    hwDeviceDriver hw_driver;
} genericDriver;


struct sw_dcMotor{
    genericDriver enable;
    genericDriver speed;
    genericDriver cw;
    genericDriver ccw;
};


typedef struct sw_DeviceDriver{
    struct sw_dcMotor dc_motor;
}swDeviceDriver;

 

/**
 * \struct device_driver [driversDescriptor.h]
 *  Sub structure for devices.
 * -> include part_Driver structure
 */
struct device{
    int id;
    char interface[MAX_DRIVERS_PER_TYPE];
    hwDeviceDriver hw_driver;
    swDeviceDriver sw_driver;
};

/**
 * \struct partsList [driversDescriptor.h]
 * structure to list the parts of the robot
 */
typedef struct parts_list{
    int part_id;
    char type[15];
    struct device dc_motor[MAX_DRIVERS_PER_TYPE];
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
extern char LoadDevicesDescriptor(char * srcDataBuffer, devices_list * boardDevice);


/**
 * \brief Open and load electronic devices descriptor configuration
 * \return code error
 */  
extern char LoadBoardDescriptor(char * srcDataBuffer, kehopsParts * kparts, devices_list * boardDevice);

/**
 * \fn unsigned char printDeviceData(int partsNb, struct device * device)
 * \brief Print a structured view of a device settings
 *
 * \param int partsNb, number of the field in the array driver
 * \param struct device * device, The driver to print
 *
 * \return -
 * 
 * output format:
 * 
 * deviceArray[partsNb] 
 * |__ ID: 5
 *   |__ Type: _tca9546
 *   |__ Address: 0xe0
  *  |__ Attributes:{Not implemented}
 * 
 * 
 */

extern unsigned char printDeviceData(int deviceNb, devices_list * device);


/**
 * \fn unsigned char printBoardData(int partsNb, struct device * device)
 * \brief Print a structured view of a device settings
 *
 * \param int partsNb, number of the field in the array driver
 * \param struct device * device, The driver to print
 *
 * \return -
 * 
 * output format:
 * 
 *  driverArray[partsNb] 
 *  |__ ID: 1
 *  |__ Interface: i2c
 *  |__ Driver
 *     |__ deviceId: 2
 *     |__ type: 
 *     |__ attributes
 *        |__ channel: 5
 * 
 * 
 */

extern unsigned char printBoardData(int partsNb, struct device * device);

// Create the structure for hardware description
//and get the setting from configs file

devices_list boardDevice[MAX_BOARD_DEVICE];
kehopsParts kehopsActuators;

#endif /* DEVICEMAPPING_H */

