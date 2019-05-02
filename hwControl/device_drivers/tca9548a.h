/**
 * \file tca9548a.h
 * \brief TCA9548A I2C Switch driver
 *  I2C default address: 0xE0 (7 bit)
 * \author Raphael Thurnherr
 * \version 0.1
 * \date 25.04.2019
 *
 * Library to setup and drive the 8 channel I2C switch
 * 
 */


#ifndef TCA9548A_H
#define TCA9548A_H

#define STATE_OFF  0            // OFF state
#define STATE_ON  !STATE_OFF    // ON state

/**
 * \struct tca9548a [tca9548a.h] Configuration structure definition
 */

typedef struct tca9548a{
    char deviceName[25];                        // Device Name of IC
    unsigned char deviceAddress;                // Bus device address
} device_tca9548a;

/**
 * \brief TCA9548A driver initialization
 * \param pointer on the configuration structure
 * \return code error
 */
extern int tca9548a_init(device_tca9548a *tca9548aconfig);        // TCA9548A driver initialization

/**
 * \brief TCA9548A set channel state
 * \param pointer on the configuration structure
 * \param channel selection
 * \param channel state (ON/OFF/XON)
 * \return code error
 */
extern int tca9548a_setChannelState(device_tca9548a *tca9548aconfig, unsigned char channel, int state);

#endif /* TCA9548A_H */
