/**
 * \file mcp4725.h
 * \brief MCP4725 Digital analog converter with eeprom memory driver
 *  I2C default address: 0x60 when ADR connected to GND
 *  I2C default address: 0x61 when ADR connected to VCC
 * \author Raphael Thurnherr
 * \version 0.1
 * \date 24.04.2019
 *
 * Library to setup and drive the DAC converter MCP4725
 * 
 */

#ifndef I2CSIMU

// user Definitions
#define RESOLUTION  4095



#include "mcp4725.h"
#include <onion-i2c.h>
#include "stdio.h"
#include "math.h"

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
    unsigned int regData =0;
    float resolution_mv;
    
    resolution_mv = (float)vref / RESOLUTION;
    
    regData = round((float)value_mv / resolution_mv);

    unsigned char data[32];
    
    // Write only DAC Register: (C2, C1, C0) = (0,1,0) and  POWERDOWN =0;
    data[0] = 0x40;
    
    // Loading buffer with 12bit register value
    data[1] = (regData & 0x0ff0) >> 4;        // MSB
    data[2] = (regData & 0x000f) << 4;        // LSB
    
    err += i2c_writeBufferRaw(0, deviceAddress, data, 3);
    
    printf("Write I2C mcp4725_setDACOutput_mV:     valueMV: %d     Address:   0x%2x", value_mv,  deviceAddress );
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
    data[1] = (value & 0x0ff0) >> 4;        // MSB
    data[2] = (value & 0x000f) << 4;        // LSB

    err += i2c_writeBufferRaw(0, deviceAddress, data, 3);
    
    err++;
    return err;
}

#endif