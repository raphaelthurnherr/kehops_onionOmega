/**
 * \file mcp4728.h
 * \brief MCP4728 4 channels Digital analog converter with eeprom memory driver
 *  I2C default address: 0x60 when ADR connected to GND
 *  I2C default address: 0x61 when ADR connected to VCC
 * \author Raphael Thurnherr
 * \version 0.1
 * \date 05.09.2019
 *
 * Library to setup and drive the DAC converter MCP4728
 * 
 */

#ifndef I2CSIMU

// user Definitions
#define RESOLUTION  4095



#include "mcp4728.h"
#include <onion-i2c.h>
#include "stdio.h"
#include "math.h"

/**
 * \brief MCP4728 driver initialization
 * \param pointer on the configuration structure
 * \return code error
 */
int mcp4728_init(device_mcp4728 *mcp4728config){
    int err =0;    
    unsigned char mcp4728_regData[32];
    unsigned char deviceAddress = mcp4728config->deviceAddress;

    // Get the DAC register setting (8 bit), DAC Register data (16 bit), EEPROM DATA(16 bit)   
    err += i2c_readRaw(0, deviceAddress, mcp4728_regData , 5);

    if(err){
        printf("Kehops I2C MCP4728 device initialization with %d error\n", err);
    }
    return err;
}


/**
 * \brief MCP4728 set DAC output voltage in mV
 * \param pointer on the configuration structure
 * \param channel, specify the channel to set state
 * \param value_mv, mV value for output
 * \return code error
 */

int mcp4728_setDACOutput_mV(device_mcp4728 *mcp4728config, unsigned char channel, int value_mv){
    unsigned char err =0;
    unsigned char deviceAddress = mcp4728config->deviceAddress;
    unsigned int vref = mcp4728config->vref_mv;
    unsigned int regData =0;
    float resolution_mv;
    
    resolution_mv = (float)vref / RESOLUTION;
    
    regData = round((float)value_mv / resolution_mv);

    unsigned char data[32];
    
    // Write only DAC Register: (C2, C1, C0) (W1, W0)= (0,1,0) (1,1) and  POWERDOWN =0;
    data[0] = 0x58;

    // Select DAC Register
    data[0] |= (channel<<1);
    
    // Force UDAC to 0
    data[0] &= 0xFE;
            
    
    // Loading buffer with 12bit register value and VREF (0=VCC), POWER DOWN (0=normal), Gain (0=1x)
    data[1] = (regData & 0x0f00) >> 8;               // MSB
    data[2] = (regData & 0x00ff);                  // LSB
        
    err += i2c_writeBufferRaw(0, deviceAddress, data, 3);
    
    printf("Write I2C mcp4728_setDACOutput_mV:     valueMV: %d     Address:   0x%2x", value_mv,  deviceAddress );
    err++;
    return err;
}

/**
 * \brief MCP4728 set DAC output 12bit value
 * \param pointer on the configuration structure
 * \param channel, specify the channel to set state
 * \param value (12bit), mV value for output
 * \return code error
 */

int mcp4728_setDAC_12bitValue(device_mcp4728 *mcp4728config,  unsigned char channel, int value){
    unsigned char err =0;
    unsigned char deviceAddress = mcp4728config->deviceAddress;
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