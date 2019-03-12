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

#define FILE_KEY_DRIVERS_MOTOR "{'drivers'{'dc_motors'"
#define FILE_KEY_DRIVERS_STEPPER "{'drivers'{'stepper_motors'"
#define FILE_KEY_DRIVERS_DOUT "{'drivers'{'dout'"
#define FILE_KEY_DRIVERS_DIN "{'drivers'{'din'"
#define FILE_KEY_DRIVERS_AIN "{'drivers'{'ain'"
#define FILE_KEY_DRIVERS_CNT "{'drivers'{'counter'"
#define FILE_KEY_DRIVERS_RGB "{'drivers'{'rgbSensor'"
#define FILE_KEY_DRIVERS_DISTANCE "{'drivers'{'distanceSensor'"

#define FILE_KEY_DRIVER_ID "[*{'id'"
#define FILE_KEY_DRIVER_INTERFACE "[*{'interface'"
#define FILE_KEY_DRIVER_DEVICE "[*{'driver'{'device_id'"
#define FILE_KEY_DRIVER_TYPE "[*{'driver'{'type'"
#define FILE_KEY_DRIVER_ATTRIBUTES "[*{'driver'{'attributes'"

#define FILE_KEY_DRIVER_ATTRIBUTES_CHANNEL "[*{'driver'{'attributes'{'channel'"
#define FILE_KEY_DRIVER_ATTRIBUTES_EN "[*{'driver'{'attributes'{'enable'"
#define FILE_KEY_DRIVER_ATTRIBUTES_SPEED "[*{'driver'{'attributes'{'speed'"
#define FILE_KEY_DRIVER_ATTRIBUTES_CW "[*{'driver'{'attributes'{'cw'"
#define FILE_KEY_DRIVER_ATTRIBUTES_CCW "[*{'driver'{'attributes'{'ccw'"

#define FILE_KEY_DRIVER_ATTRIBUTES_SUBD "[*{'driver'{'sub-driver'"
#define FILE_KEY_DRIVER_ATTRIBUTES_SUBD_DEVICE "[*{'driver'{'sub-driver'{'device_id'"
#define FILE_KEY_DRIVER_ATTRIBUTES_SUBD_TYPE "[*{'driver'{'sub-driver'{'type'"
#define FILE_KEY_DRIVER_ATTRIBUTES_SUBD_ATTRIBUTES "[*{'driver'{'sub-driver'{'attributes'"
#define FILE_KEY_DRIVER_ATTRIBUTES_SUBD_ATTRIBUTES_CHANNEL "[*{'driver'{'sub-driver'{'attributes'{'channel'"
/*
      {
        "id": 1,
        "driver": {
          "device_id": "8",
          "type": "vl53l1x",
          "attributes": {},
          "sub-driver": {
              "device_id": "6",
              "type": "tca9546",
              "attributes": {
                "channel": 0
              }
          }
        }
      }
 */
#endif /* DRIVERDESCRIPTOR_JSONKEYS_H */

