/**
 * \file bh1745.h
 * \brief bh1745 NUC Color Sensor driver
 * \author Raphael Thurnherr
 * \version 0.1
 * \date 18.03.2019
 *
 * Setup and drive the 16 bit RGB color sensor
 */

#ifndef BH1745_H
#define BH1745_H

/**
 * \struct device_bh1745 [bh1745.h] Configuration structure definition
 */

typedef struct bh1745{
    char deviceName[25];                        // Device Name of IC
    unsigned char deviceAddress;                // Bus device address
} device_bh1745;


/**
 * \brief Initial configuration for bh1745nuc_init RGB sensor
 * \return code error
 */

extern unsigned char bh1745nuc_init(device_bh1745 *bh1745Config);


/**
 * \brief bh1745_getChannelRGBvalue, get color value for the specified channel 
 * \param device_bh1745 bh1745Config, pointer on the configuration structure
 * \param int channel, specify the channel (0 = RED, 1 = GREEN, 2 = BLUE, 3 = CLEAR)
 * \return code error
 */

extern int bh1745nuc_getChannelRGBvalue(device_bh1745 *bh1745Config, int channel);
#endif /* BH1745_H */
