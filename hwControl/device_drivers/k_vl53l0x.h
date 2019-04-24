/**
 * \file k_vl53l0x.h
 * \brief vl53l0x TOF distance sensor
 * \author Raphael Thurnherr
 * \version 0.1
 * \date 23.04.2019
 *
 * Setup and drive the Time of Flight distance sensor
 */

#ifndef K_VL53L0X_H
#define K_VL53L0X_H

/**
 * \struct device_k_vl53l0x [k_vl53l0x.h] Configuration structure definition
 */

typedef struct k_vl53l0x{
    char deviceName[25];                        // Device Name of IC
    unsigned char deviceAddress;                // I2C Bus device address
} device_vl53l0x;


/**
 * \brief Initial configuration for vl53l0x TOF sensor
 * \return code error
 */

extern unsigned char vl53l0x_init(device_vl53l0x *vl53l0xConfig);


/**
 * \brief vl53l0x_getChannel_distance_mm, get distance in mm
 * \param device_vl53l0x vl53l0xConfig, pointer on the configuration structure
 * \param int channel, specify the channel ( TO COMPLETE)
 * \return code error
 */

extern int vl53l0x_getChannel_distance_mm(device_vl53l0x *vl53l0xConfig, int channel);

#endif /* K_VL53L0X_H */
