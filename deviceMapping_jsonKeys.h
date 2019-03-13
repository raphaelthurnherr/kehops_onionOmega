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
#define FILE_KEY_DEVICES_ATTRIBUTES_DEVINIT "{'devices'[*{'attributes'{deviceInit"
#define DEVICES_ATTRIBUTES_DEVINIT "{deviceInit"
#define DEVICES_ATTRIBUTES_DEVINIT_INIT_ADDR "{'deviceInit'[*{'regAddr'"
#define DEVICES_ATTRIBUTES_DEVINIT_INIT_DATA "{'deviceInit'[*{'regData'"

/**
 * \def JSON keys for driver definition
*/
#define FILE_KEY_DRIVERS "{'drivers'"

#define FILE_KEY_DRIVERS_MOTOR "{'drivers'{'dc_motors'"
#define FILE_KEY_DRIVERS_STEPPER "{'drivers'{'stepper_motors'"
#define FILE_KEY_DRIVERS_DOUT "{'drivers'{'dout'"
#define FILE_KEY_DRIVERS_DIN "{'drivers'{'din'"
#define FILE_KEY_DRIVERS_AIN "{'drivers'{'ain'"
#define FILE_KEY_DRIVERS_CNT "{'drivers'{'counter'"
#define FILE_KEY_DRIVERS_RGB "{'drivers'{'rgbSensor'"
#define FILE_KEY_DRIVERS_DISTANCE "{'drivers'{'distanceSensor'"

/**
 * \def Common definition
*/

// For search in array
#define FILE_KEY_DRIVER_ID "[*{'id'"
#define FILE_KEY_DRIVER_INTERFACE "[*{'interface'"
#define FILE_KEY_DRIVER_DEVICE "[*{'driver'{'device_id'"
#define FILE_KEY_DRIVER_TYPE "[*{'driver'{'type'"
#define FILE_KEY_DRIVER_ATTRIBUTES "[*{'driver'{'attributes'"


// For search in object
#define KEY_DEVICE "{driver{'device_id'"
#define KEY_TYPE "{{driver'type'"
#define KEY_INTERFACE "{'interface'"
#define KEY_ATTRIBUTES "{'attributes'"

#define KEY_DRIVER_DEVICE "{'device_id'"

#define FILE_KEY_DRIVER_ATTRIBUTES_CHANNEL "[*{{'attributes'{'channel'"
#define KEY_ATTRIBUTES_EN "[*{'attributes'{'enable'"
#define KEY_ATTRIBUTES_SPEED "[*{'attributes'{'speed'"
#define KEY_ATTRIBUTES_CW "[*{'attributes'{'cw'"
#define KEY_ATTRIBUTES_CCW "[*{'attributes'{'ccw'"

#define FILE_KEY_DRIVER_ATTRIBUTES_SUBD "[*{'driver'{'sub-driver'"
#define FILE_KEY_DRIVER_ATTRIBUTES_SUBD_DEVICE "[*{'driver'{'sub-driver'{'device_id'"
#define FILE_KEY_DRIVER_ATTRIBUTES_SUBD_TYPE "[*{'driver'{'sub-driver'{'type'"
#define FILE_KEY_DRIVER_ATTRIBUTES_SUBD_ATTRIBUTES "[*{'driver'{'sub-driver'{'attributes'"
#define FILE_KEY_DRIVER_ATTRIBUTES_SUBD_ATTRIBUTES_CHANNEL "[*{'driver'{'sub-driver'{'attributes'{'channel'"

#endif /* DEVICEMAPPING_JSONKEYS_H */

