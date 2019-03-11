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

#define FILE_KEY_DRIVERS_MOTOR "{'drivers'{'dout'"
#define FILE_KEY_DRIVERS_MOTOR_ID "{'drivers'{'dout'[*{'id'"
#define FILE_KEY_DRIVERS_MOTOR_DRIVER_DEVICE "{'drivers'{'dout'[*{'driver'{'device_id'"
#define FILE_KEY_DRIVERS_MOTOR_DRIVER_TYPE "{'drivers'{'dout'[*{'driver'{'type'"
#define FILE_KEY_DRIVERS_MOTOR_DRIVER_ATTRIBUTES "{'drivers'{'dout'[*{'driver'{'attributes'"
#define FILE_KEY_DRIVERS_MOTOR_DRIVER_ATTRIBUTES_EN "{'drivers'{'dout'[*{'driver'{'attributes'{'enable'"
#define FILE_KEY_DRIVERS_MOTOR_DRIVER_ATTRIBUTES_SPEED "{'drivers'{'dout'[*{'driver'{'attributes'{'speed'"
#define FILE_KEY_DRIVERS_MOTOR_DRIVER_ATTRIBUTES_CW "{'drivers'{'dout'[*{'driver'{'attributes'{'cw'"
#define FILE_KEY_DRIVERS_MOTOR_DRIVER_ATTRIBUTES_CCW "{'drivers'{'dout'[*{'driver'{'attributes'{'ccw'"

#define FILE_KEY_DRIVERS_STEPPER_ID "{'drivers'{'stepper_motors'[*{'id'"
#define FILE_KEY_DRIVERS_STEPPER_DRIVER_DEVICE "{'drivers'{'stepper_motors'[*{'driver'{'device_id'"
#define FILE_KEY_DRIVERS_STEPPER_DRIVER_DTYPE "{'drivers'{'stepper_motors'[*{'driver'{'type'"
#define FILE_KEY_DRIVERS_STEPPER_DRIVER_ATTRIBUTES "{'drivers'{'stepper_motors'[*{'driver'{'attributes'"

#define FILE_KEY_DRIVERS_DOUT "{'drivers'{'dout'"
#define FILE_KEY_DRIVERS_DOUT_ID "{'drivers'{'dout'[*{'id'"
#define FILE_KEY_DRIVERS_DOUT_DRIVER_DEVICE "{'drivers'{'dout'[*{'driver'{'device_id'"
#define FILE_KEY_DRIVERS_DOUT_DRIVER_TYPE "{'drivers'{'dout'[*{'driver'{'type'"
#define FILE_KEY_DRIVERS_DOUT_DRIVER_ATTRIBUTES "{'drivers'{'dout'[*{'driver'{'attributes'"
#define FILE_KEY_DRIVERS_DOUT_DRIVER_ATTRIBUTES_CHANNEL "{'drivers'{'dout'[*{'driver'{'attributes'{'channel'"

#define FILE_KEY_DRIVERS_DIN "{'drivers'{'din'"
#define FILE_KEY_DRIVERS_DIN_ID "{'drivers'{'din'[*{'id'"
#define FILE_KEY_DRIVERS_DIN_DRIVER_DEVICE "{'drivers'{'din'[*{'driver'{'device_id'"
#define FILE_KEY_DRIVERS_DIN_DRIVER_TYPE "{'drivers'{'din'[*{'driver'{'type'"
#define FILE_KEY_DRIVERS_DIN_DRIVER_ATTRIBUTES "{'drivers'{'din'[*{'driver'{'attributes'"
#define FILE_KEY_DRIVERS_DIN_DRIVER_ATTRIBUTES_CHANNEL "{'drivers'{'din'[*{'driver'{'attributes'{'channel'"

#define FILE_KEY_DRIVERS_AIN "{'drivers'{'ain'"
#define FILE_KEY_DRIVERS_AIN_ID "{'drivers'{'ain'[*{'id'"
#define FILE_KEY_DRIVERS_AIN_DRIVER_DEVICE "{'drivers'{'ain'[*{'driver'{'device_id'"
#define FILE_KEY_DRIVERS_AIN_DRIVER_TYPE "{'drivers'{'ain'[*{'driver'{'type'"
#define FILE_KEY_DRIVERS_AIN_DRIVER_ATTRIBUTES "{'drivers'{'ain'[*{'driver'{'attributes'"
#define FILE_KEY_DRIVERS_AIN_DRIVER_ATTRIBUTES_CHANNEL "{'drivers'{'ain'[*{'driver'{'attributes'{'channel'"

#define FILE_KEY_DRIVERS_CNT "{'drivers'{'counter'"
#define FILE_KEY_DRIVERS_CNT_ID "{'drivers'{'counter'[*{'id'"
#define FILE_KEY_DRIVERS_CNT_DRIVER_DEVICE "{'drivers'{'counter'[*{'driver'{'device_id'"
#define FILE_KEY_DRIVERS_CNT_DRIVER_TYPE "{'drivers'{'counter'[*{'driver'{'type'"
#define FILE_KEY_DRIVERS_CNT_DRIVER_ATTRIBUTES "{'drivers'{'counter'[*{'driver'{'attributes'"
#define FILE_KEY_DRIVERS_CNT_DRIVER_ATTRIBUTES_CHANNEL "{'drivers'{'counter'[*{'driver'{'attributes'{'channel'"

#define FILE_KEY_DRIVERS_RGB "{'drivers'{'rgbSensor'"
#define FILE_KEY_DRIVERS_RGB_ID "{'drivers'{'rgbSensor'[*{'id'"
#define FILE_KEY_DRIVERS_RGB_DRIVER_DEVICE "{'drivers'{'rgbSensor'[*{'driver'{'device_id'"
#define FILE_KEY_DRIVERS_RGB_DRIVER_TYPE "{'drivers'{'rgbSensor'[*{'driver'{'type'"
#define FILE_KEY_DRIVERS_RGB_DRIVER_ATTRIBUTES "{'drivers'{'rgbSensor'[*{'driver'{'attributes'"

#define FILE_KEY_DRIVERS_DISTANCE "{'drivers'{'distanceSensor'"
#define FILE_KEY_DRIVERS_DISTANCE_ID "{'drivers'{'distanceSensor'[*{'id'"
#define FILE_KEY_DRIVERS_DISTANCE_DRIVER_DEVICE "{'drivers'{'distanceSensor'[*{'driver'{'device_id'"
#define FILE_KEY_DRIVERS_DISTANCE_DRIVER_TYPE "{'drivers'{'distanceSensor'[*{'driver'{'type'"
#define FILE_KEY_DRIVERS_DISTANCE_DRIVER_ATTRIBUTES "{'drivers'{'distanceSensor'[*{'driver'{'attributes'"
#define FILE_KEY_DRIVERS_DISTANCE_DRIVER_ATTRIBUTES_SUBD "{'drivers'{'counter'[*{'driver'{'attributes'{'sub-driver'"
#define FILE_KEY_DRIVERS_DISTANCE_DRIVER_ATTRIBUTES_SUBD_DEVICE "{'drivers'{'counter'[*{'driver'{'attributes'{'sub-driver'{'device_id'"
#define FILE_KEY_DRIVERS_DISTANCE_DRIVER_ATTRIBUTES_SUBD_TYPE "{'drivers'{'counter'[*{'driver'{'attributes'{'sub-driver'{'type'"
#define FILE_KEY_DRIVERS_DISTANCE_DRIVER_ATTRIBUTES_SUBD_ATTRIBUTES "{'drivers'{'counter'[*{'driver'{'attributes'{'sub-driver'{'attributes'"
#define FILE_KEY_DRIVERS_DISTANCE_DRIVER_ATTRIBUTES_SUBD_ATTRIBUTES_CHANNEL "{'drivers'{'counter'[*{'driver'{'attributes'{'sub-driver'{'attributes'{'channel'"

#endif /* DRIVERDESCRIPTOR_JSONKEYS_H */

