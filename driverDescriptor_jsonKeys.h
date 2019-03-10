/**
 * \file driverDescriptor_jsonKeys.h
 * \brief  Interconnect the user parts (like LEDs components) to the hardware
 *  driver IC output (like PCA9685 driver) or generic driver.
 *      
 * \author Raphael Thurnherr
 * \version 0.1
 * \date 10.03.2019
 *
 * Definition of all the JSON keys used for get the data in the configuration files:
 *  - drivers.cfg    -- Déclaration of drivers structure
 *  - devices.cfg    -- Declaration of electronic device of the board
 */ 
      

#ifndef DRIVERDESCRIPTOR_JSONKEYS_H
#define DRIVERDESCRIPTOR_JSONKEYS_H

/**
 * \def JSON keys for electronic device definition
*/
#define FILE_KEY_DEVICES "{'devices'"
#define FILE_KEY_DEVICES_ID "{'devices'[*{'id'"
#define FILE_KEY_DEVICES_TYPE "{'devices'[*{'type'"
#define FILE_KEY_DEVICES_ADDRESS "{'devices'[*{'address'"
#define FILE_KEY_DEVICES_ATTRIBUTES_DEVINIT "{'devices'[*{'attributes'{deviceInit"
#define DEVICES_ATTRIBUTES_DEVINIT "{deviceInit"
#define DEVICES_ATTRIBUTES_DEVINIT_INIT_ADDR "{'deviceInit'[*{'regAddr'"
#define DEVICES_ATTRIBUTES_DEVINIT_INIT_DATA "{'deviceInit'[*{'regData'"

/**
 * \def JSON keys for DOUT driver definition
*/
#define FILE_KEY_DRIVERS "{'drivers'"
#define FILE_KEY_DRIVERS_DOUT "{'drivers'{'dout'"
#define FILE_KEY_DRIVERS_DOUT_ID "{'drivers'{'dout'[*{'id'"
#define FILE_KEY_DRIVERS_DOUT_DRIVER_DEVICE "{'drivers'{'dout'[*{'driver'{'device_id'"
#define FILE_KEY_DRIVERS_DOUT_DRIVER_TYPE "{'drivers'{'dout'[*{'driver'{'type'"
#define FILE_KEY_DRIVERS_DOUT_DRIVER_ATTRIBUTES "{'drivers'{'dout'[*{'driver'{'attributes'"

#endif /* DRIVERDESCRIPTOR_JSONKEYS_H */

