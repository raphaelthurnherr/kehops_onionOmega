/**
 * \file ads111x.h
 * \brief ADS111x 12bit Analog to digital converter (2 or 4 channels)
 *  I2C default address: 0x48 when ADR connected to GND
 *                       0x49 when ADR connected to VDD
 *                       0x4A when ADR connected to SDA
 *                       0x4B when ADR connected to SCL
 * \author Raphael Thurnherr
 * \version 0.1
 * \date 03.05.2019
 *
 * Library to setup and drive the 12 bit ADC converter ADS111x 
 * 
 */

#ifndef I2CSIMU

// Register Definitions
#define CVRTREG 0x00                    // Conversion register
#define CONFREG 0x01                    // Config register
#define THRESHOLD_L 0x02		// Threshold low register
#define THRESHOLD_L 0x03		// Threshold low register

#include "ads111x.h"
#include <onion-i2c.h>
#include "stdio.h"
#include "math.h"


/**
 * \brief ADS111x driver initialization
 * \param pointer on the configuration structure
 * \return code error
 */
int ads111x_init(device_ads111x *ads111xconfig){
    char err=0;
    
    unsigned char deviceAddr = ads111xconfig->deviceAddress;
    unsigned char defaultMuxChannel = 0;

    unsigned char data[32];
    
    // Set default channel, FSR to 6.144V, Continuous conversion
    data[0] = (((defaultMuxChannel & 0x07) << 4) & 0xF0) | 0x00;
    
    // Set DR to 128 SPS, TRADITIONNAL comparator active HIGH with NONlatching and DISABLE.
    data[1] = 0x8B;
    
    // Write CONFIG Register
    err+= i2c_writeBuffer(0, deviceAddr, CONFREG, data, 2);

    return err;
}

/**
 * \brief ADS111x read convertion data register
 * \param pointer on the configuration structure
 * \return code error
 */
int ads111x_getVoltage_mv(device_ads111x *ads111xconfig, unsigned char channel){
    char err=0;
    unsigned char deviceAddr = ads111xconfig->deviceAddress;
    unsigned char data[32];
    int result=0;
    unsigned char confReg[32];
    
    channel += 4;           // Using MUX Ref to GND
    
    // Get the configuration register data
    err += i2c_read(0, deviceAddr, CONFREG, confReg, 2);
    
    // Change mutiplexer channel 
    confReg[0] = (confReg[0] & 0x8F) | ((channel & 0x07) << 4);

    // Write CONFIG Register for new channel
    err+= i2c_writeBuffer(0, deviceAddr, CONFREG, confReg, 2);    
    
    // Read Conversion register for selected channel... !!! Convertion time unknown !!!
    err += i2c_read(0, deviceAddr, CVRTREG, data, 2);
    
    if(!err){
        result = round((float) (((data[0] << 8) & 0Xff00) | data[1]) * 0.1875);  // Register value * 3mV Resolution for FSR = 0 (Max 6.144V)
        //printf("JE VIENS LIRE CES VALEURS:    address: 0x%2x    REG: 0x%2x    CHANNEL: %d RESULT: %d\n", deviceAddr, CVRTREG, channel,result);
        return result;
    }
    else 
        return -1; 
}

#endif