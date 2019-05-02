/**
 * \file ads101x.h
 * \brief ADS101x 12bit Analog to digital converter (2 or 4 channels)
 *  I2C default address: 0x48 when ADR connected to GND
 *                       0x49 when ADR connected to VDD
 *                       0x4A when ADR connected to SDA
 *                       0x4B when ADR connected to SCL
 * \author Raphael Thurnherr
 * \version 0.1
 * \date 30.04.2019
 *
 * Library to setup and drive the 12 bit ADC converter ADS101x 
 * 
 */

#ifndef ADS101X_H
#define ADS101X_H

/**
 * \struct ads101x [ads101x.h] Configuration structure definition
 */

typedef struct ads101x{
    char deviceName[25];                        // Device Name of IC
    unsigned char deviceAddress;                // Bus device address
} device_ads101x;

/**
 * \brief ADS101x driver initialization
 * \param pointer on the configuration structure
 * \return code error
 */
extern int ads101x_init(device_ads101x *ads101xconfig);        // ADS1215 driver initialization

/**
 * \brief ADS101x read convertion data register
 * \param pointer on the configuration structure
 * \return code error
 */
extern int ads101x_getVoltage_mv(device_ads101x *ads101xconfig, unsigned char channel);



#endif /* ADS101X_H */
