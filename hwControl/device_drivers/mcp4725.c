/**
 * \file mcp4725.h
 * \brief MCP4725 Digital analog converter with eeprom memory driver
 * \author Raphael Thurnherr
 * \version 0.1
 * \date 24.04.2019
 *
 * Library to setup and drive the DAC converter MCP4725
 * 
 */

#ifndef I2CSIMU

// user Definitions
#define RESOLUTION  4096



#include "mcp4725.h"
#include <onion-i2c.h>
#include "stdio.h"

/**
 * \brief MCP4725 driver initialization
 * \param pointer on the configuration structure
 * \return code error
 */
int mcp4725_init(device_mcp4725 *mcp4725config){
    int err =0;    
    unsigned char mcp4725_regData[32];
    unsigned char deviceAddress = mcp4725config->deviceAddress;

    // Get the DAC register setting (8 bit), DAC Register data (16 bit), EEPROM DATA(16 bit)   
    err += i2c_readRaw(0, deviceAddress, mcp4725_regData , 5);

    if(err){
        printf("Kehops I2C MCP4725 device initialization with %d error\n", err);
    }
    return err;
}


/**
 * \brief MCP4725 set DAC output voltage in mV
 * \param pointer on the configuration structure
 * \param channel, specify the channel to set state
 * \param value_mv, mV value for output
 * \return code error
 */

int mcp4725_setDACOutput_mV(device_mcp4725 *mcp4725config, int value_mv){
    unsigned char err =0;
    unsigned char deviceAddress = mcp4725config->deviceAddress;
    unsigned int vref = mcp4725config->vref_mv;
    unsigned int regData;
    
    regData = (vref / RESOLUTION) * value_mv;
    
    unsigned char data[32];
    
    // Write only DAC Register: (C2, C1, C0) = (0,1,0) and  POWERDOWN =0;
    data[0] = 0x40;
    
    data[1] = (regData & 0xff00) >> 8;
    data[2] = regData & 0x00f0;
    err += i2c_writeBufferRaw(0,deviceAddress, data, 3);
    
    err++;
    return err;
}

/**
 * \brief MCP4725 set DAC output 12bit value
 * \param pointer on the configuration structure
 * \param channel, specify the channel to set state
 * \param value (12bit), mV value for output
 * \return code error
 */

int mcp4725_setDAC_12bitValue(device_mcp4725 *mcp4725config, int value){
    unsigned char err =0;
    unsigned char deviceAddress = mcp4725config->deviceAddress;
    unsigned char data[32];
    
    // Write only DAC Register: (C2, C1, C0) = (0,1,0) and  POWERDOWN =0;
    data[0] = 0x40;
    
    // Loading buffer with 12bit register value
    data[1] = (value & 0xff00) >> 8;
    data[2] = (value & 0x00f0);
    
    err += i2c_writeBufferRaw(0, deviceAddress, data, 3);
    
    err++;
    return err;
}

#endif