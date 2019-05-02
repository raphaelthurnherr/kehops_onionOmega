/**
 * \file k_vl53l0x.c
 * \brief bh1745 NUC Color Sensor driver
 * \author Raphael Thurnherr
 * \version 0.1
 * \date 23.04.2019
 *
 * Setup and drive the Time of Flight distance sensor
 * Note that this driver use the Texas API libraries
 */

#ifndef I2CSIMU

#include "k_vl53l0x.h"
#include "stdio.h"

// Manufacturer API libraries
/*
#include "api/vl53l0x/vl53l0x_api.h"
#include "api/vl53l0x/vl53l0x_platform.h"
#include "api/vl53l0x/vl53l0x_i2c_platform.h"

static VL53L0X_Dev_t MyDevice; // device descriptor from manufacturer
*/

/**
 * \brief vl53l0x_init, device initialisation
 * \param device_vl53l0x vl53l0xConfig, pointer on the configuration structure
 * \return code error
 */
unsigned char vl53l0x_init(device_vl53l0x *vl53l0xConfig){
    unsigned char err=0;
    unsigned char deviceAddress = vl53l0xConfig->deviceAddress;

    /*
    VL53L0X_Error err_code;
    uint8_t vhvCalibrationValue;
    uint8_t phaseCalibrationValue;
    uint32_t refSpadCount;
    uint8_t isApertureSpads;

    //Initialize Comms 
    MyDevice.I2cDevAddr      =  deviceAddress;
    MyDevice.comms_type      =  1;
    MyDevice.comms_speed_khz =  400;

    err_code = VL53L0X_comms_initialise(I2C, MyDevice.comms_speed_khz);
    if(err_code!=VL53L0X_ERROR_NONE) {
      printf("ERROR: VL53L0X_comms_initialise(): %d\r\n", err_code);
      err++;
    }

    
    err_code = VL53L0X_DataInit(&MyDevice);
    if(err_code != VL53L0X_ERROR_NONE) {
      printf("ERROR: DataInit(): %d\r\n", err_code);
      err++;
    }

    
    err_code = VL53L0X_StaticInit(&MyDevice);
    if(err_code != VL53L0X_ERROR_NONE) {
      printf("ERROR: StaticInit: %d\r\n", err_code);
      err++;
    }

    VL53L0X_PerformRefSpadManagement(&MyDevice, &refSpadCount, &isApertureSpads);
    if(err_code!=VL53L0X_ERROR_NONE) {
      printf("ERROR: SpadCal: %d\r\n", err_code);
      err++;
    }

    err_code = VL53L0X_PerformRefCalibration(&MyDevice, &vhvCalibrationValue, &phaseCalibrationValue);
    if(err_code!=VL53L0X_ERROR_NONE) {
      printf("ERROR: VL53L0X_PerformRefCalibration(): %d\r\n", err_code);
      err++;
    }

    err_code = VL53L0X_SetDeviceMode(&MyDevice, VL53L0X_DEVICEMODE_SINGLE_RANGING);
    if(err_code != VL53L0X_ERROR_NONE) {
      printf("ERROR: VL53L0X_SetDeviceMode(): %d\r\n", err_code);
      err++;
    }

    // Enable/Disable Sigma and Signal check
    err_code = VL53L0X_SetLimitCheckEnable(&MyDevice, VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, 1 );
    if(err_code != VL53L0X_ERROR_NONE) {
      printf("ERROR: VL53L0X_SetLimitCheckEnable(): %d\r\n", err_code);
      err++;
    }

    err_code = VL53L0X_SetLimitCheckEnable(&MyDevice, VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, 1 );
    if(err_code != VL53L0X_ERROR_NONE) {
      printf("ERROR: VL53L0X_SetLimitCheckEnable(): %d\r\n", err_code);
      err++;
    }

    err_code = VL53L0X_SetLimitCheckEnable(&MyDevice, VL53L0X_CHECKENABLE_RANGE_IGNORE_THRESHOLD, 1 );
    if(err_code != VL53L0X_ERROR_NONE) {
      printf("ERROR: VL53L0X_SetLimitCheckEnable(): %d\r\n", err_code);
      err++;
    }

    err_code = VL53L0X_SetLimitCheckValue(&MyDevice, VL53L0X_CHECKENABLE_RANGE_IGNORE_THRESHOLD, (FixPoint1616_t)( 1.5 * 0.023 * 65536 ) );
    if(err_code != VL53L0X_ERROR_NONE) {
      printf("ERROR: VL53L0X_SetLimitCheckValue(): %d\r\n", err_code);
      err++;
    }  
    */
    err++;
    
    if(err){
<<<<<<< HEAD
        printf("Kehops I2C TOF VL53l0x device initialization with %d error\n", err);
=======
        //printf("Kehops I2C TOF VL53l0x device initialization with %d error\n", err);
>>>>>>> 413101f3277cdf793fdbb7f9e91ceb8e8f51a1d9
    }
    return err;    
}


/**
 * \brief vl53l0x_getChannel_distance_mm, get distance in mm
 * \param device_vl53l0x vl53l0xConfig, pointer on the configuration structure
 * \param int channel, specify the channel ( TO COMPLETE)
 * \return code error
 */

int vl53l0x_getChannel_distance_mm(device_vl53l0x * vl53l0xConfig, int channel){
	char err;
        unsigned char deviceAddress = vl53l0xConfig->deviceAddress;
        int value=-1;   
        
	if(!err){
		return value;
	}else{
            printf("vl53l0x_getChannel_distance_mm() -> Read error\n");
            return -1;
        }
}

#endif