/**
 * \file deviceMapping_jsonKeys.h
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
      

#ifndef DEVICEMAPPING_JSONKEYS_H
#define DEVICEMAPPING_JSONKEYS_H

/**
 * \def JSON keys for electronic device definition
*/
#define FILE_KEY_DEVICES "{'devices'"
#define FILE_KEY_DEVICES_ID "{'devices'[*{'id'"
#define FILE_KEY_DEVICES_TYPE "{'devices'[*{'type'"
#define FILE_KEY_DEVICES_ADDRESS "{'devices'[*{'address'"


/**
 * \def JSON keys for driver definition
*/
#define FILE_KEY_DRIVERS "{'drivers'"

#define KEY_ARRAY_MOTOR "{'drivers'{'dc_motors'"
#define KEY_ARRAY_STEPPER "{'drivers'{'stepper_motors'"
#define KEY_ARRAY_DOUT "{'drivers'{'dout'"
#define KEY_ARRAY_DIN "{'drivers'{'din'"
#define KEY_ARRAY_AIN "{'drivers'{'ain'"
#define KEY_ARRAY_CNT "{'drivers'{'counter'"
#define KEY_ARRAY_RGB "{'drivers'{'rgbSensor'"
#define KEY_ARRAY_DISTANCE "{'drivers'{'distanceSensor'"


#define KEY_OBJ_X_DEVICE "[*"


/**
 * \def Common definition
*/

// DEVICES OBJECTS COMPONENTS
#define KEY_DEVICE_STR_ID "{'id'"
#define KEY_DEVICE_STR_INTERFACE "{'interface'"
#define KEY_DEVICE_OBJ_DRIVER "{'driver'"
#define KEY_DEVICE_OBJ_ATTRIBUTES "{'attributes'"

// DRIVERS OBJECT KEY SETTINGS
#define KEY_DRIVER_STR_ID "{'device_id'"
#define KEY_DRIVER_STR_TYPE "{'type'"
#define KEY_DRIVER_OBJ_ATTRIBUTES "{'attributes'"
#define KEY_DRIVER_OBJ_SUBDRIVER "{'sub-driver'"

// ATTRIBUTES SETTINGS DRIVERS IC
#define KEY_DRIVER_STR_CHANNEL "{'channel'"


/*************************************************************/

#define KEY_ATTRIBUTES_EN "[*{'attributes'{'enable'"
#define KEY_ATTRIBUTES_SPEED "[*{'attributes'{'speed'"
#define KEY_ATTRIBUTES_CW "[*{'attributes'{'cw'"
#define KEY_ATTRIBUTES_CCW "[*{'attributes'{'ccw'"

#endif /* DEVICEMAPPING_JSONKEYS_H */

