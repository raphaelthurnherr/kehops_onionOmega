/**
 * \file tca9548a.h
 * \brief MCP4725 Digital analog converter with eeprom memory driver
 *  I2C default address: 0xE0 (7 bit)
 * \author Raphael Thurnherr
 * \version 0.1
 * \date 25.04.2019
 *
 * Library to setup and drive the 8 channel I2C switch
 *
 */

#ifndef I2CSIMU

#include "tca9548a.h"
#include <onion-i2c.h>
#include "stdio.h"

/**
 * \brief TCA9548A driver initialization
 * \param pointer on the configuration structure
 * \return code error
 */
int tca9548a_init(device_tca9548a *tca9548aconfig){
    int err =0;    
    unsigned char regData[32];
    unsigned char data[32];
    unsigned char deviceAddress = tca9548aconfig->deviceAddress;
 
    // Prepare register for  all channel default OFF
    data[0] = 0x00;
    
    // Test read
    err += i2c_readRaw(0, deviceAddress, regData, 1);   
    
    // Test write and Set all channels off
    err += i2c_writeBufferRaw(0, deviceAddress, data, 1);

    if(err){
        printf("Kehops I2C TCA9548A device initialization with %d error\n", err);
    }
    return err;
}


/**
 * \brief TCA9548A set channel state
 * \param pointer on the configuration structure
 * \param channel selection
 * \param channel state (ON/OFF/XON)
 * \return code error
 */

int tca9548a_setChannelState(device_tca9548a *tca9548aconfig, unsigned char channel, int state){
    char err =0;
    unsigned char deviceAddress = tca9548aconfig->deviceAddress;
    
    unsigned char controlRegisterValue[32];
    
    // Get the actual control register value for TCA9548A
    err += i2c_readRaw(0, deviceAddress, controlRegisterValue, 1);
    
    switch(state){
        case STATE_ON :  controlRegisterValue[0] |= (1 << channel); break;
        case STATE_OFF : controlRegisterValue[0] &= ~(1 << channel); break;
        default: break;
    }
   
    err += i2c_writeBufferRaw(0, deviceAddress, controlRegisterValue, 1);
    
        // Test read
    err += i2c_readRaw(0, deviceAddress, controlRegisterValue, 1);
    
    return err;
}

#endif