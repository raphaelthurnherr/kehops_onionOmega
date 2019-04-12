/**
 * \file mcp23008.c
 * \brief MCP23008 GPIO Extender drivers
 * \author Raphael Thurnherr
 * \version 0.1
 * \date 18.03.2019
 *
 * Library to setup and use the 8 channel MCP23008 GPIO extender I2C device
 * 
 */

#ifndef I2CSIMU

// Register Definitions
#define IODIR   0x00		// IO direction register, 0 output, 1 input
#define IPOL    0x01		// Input polarity register, 0 same logic state of pin, 1 opposite logic state
#define GPINTEN 0x02		// Interrupt on change pins, 0 disable interrupt, 1 enable interrupt
#define IDEFVAL 0x03		// Default value register for comparison to cause an interrupt
#define INTCON  0x04		// Interrupt on change control register
#define IOCON   0x05		// IO configuration register
#define GPPU    0x06		// Pull-up resistor register, 0 pull-up disable, 1 pull-up enable
#define INTF    0x07		// Interrupt flags register, 0 no interrupt pending, 1 interrupt is pending
#define INTCAP  0x08		// Interrupt captured value for port register
#define GPIO    0x09		// General purpose IO port register
#define OLAT    0x0A		// Output latch register, (Use to modify the outputs)

#endif

#include "mcp23008.h"
#include <onion-i2c.h>

/**
 * \brief MCP23008 driver initialization
 * \param pointer on the configuration structure
 * \return code error
 */
int mcp23008_init(device_mcp23008 *mcp23008config){
    int err =0;    
    unsigned char deviceAddress = mcp23008config->deviceAddress;
    unsigned char gpioDirection = mcp23008config->gpioDirection;
    unsigned char invertedInput = mcp23008config->invertedInput;
    unsigned char pullupEnable = mcp23008config->pullupEnable;
    
    char dataReg = 
    
    // Disable auto-incrementation
    err+= i2c_write(0, deviceAddress, IOCON, 0x20);

    // Set GPIO 0..4 in output, GPIO 5..6 in input mode
    if(!err) 
        err+= i2c_write(0, deviceAddress, IODIR, gpioDirection);

    // Pull up enable         
    if(!err) 
        err+= i2c_write(0, deviceAddress, GPPU, pullupEnable);

    // Set input inverted logic    
    if(!err) 
        err+= i2c_write(0, deviceAddress, IPOL, invertedInput);
    
    if(err)
        printf("Kehops I2C MCP23008 device initialization with %d error\n", err);

    return err;
}


/**
 * \brief MCP23008 read input state on specified input channel
 * \param pointer on the configuration structure
 * \param channel, specify the channel to get state
 * \return code error
 */
int mcp23008_getChannel(device_mcp23008 *mcp23008config, unsigned char channel){
    unsigned char err =0;
    unsigned char deviceAddress = mcp23008config->deviceAddress;
    int MCP2308_GPIO_STATE;
    unsigned char value=0;
    
    err += i2c_readByte(0, deviceAddress, GPIO, &MCP2308_GPIO_STATE);
    
    if(MCP2308_GPIO_STATE & (0x01<<channel))
        value = 0;
    else 
        value = 1;

    if(!err)
        return value;
    else 
        return -1;    
}

/**
 * \brief MCP23008 set output state on specified input channel, the function read port state before rewrite
 * \param pointer on the configuration structure
 * \param channel, specify the channel to set state
 * \param state, state to apply on output
 * \return code error
 */
int mcp23008_setChannel(device_mcp23008 *mcp23008config, unsigned char channel, unsigned char state){
    unsigned char err =0;
    int MCP2308_GPIO_STATE;
    unsigned char deviceAddress = mcp23008config->deviceAddress;
    
    // Sélection du chip d'entrée/sortie qui pilote le pont en H
    i2c_readByte(0, deviceAddress, GPIO, &MCP2308_GPIO_STATE);
    
    if(state)
        MCP2308_GPIO_STATE |= (0x01<<channel);
    else
        MCP2308_GPIO_STATE &= (0xFF-(0x01<<channel));
    
    err += i2c_write(0, deviceAddress, OLAT, MCP2308_GPIO_STATE);
    
    return err;
}

/**
 * \brief MCP23008 set output values on all GPIO port bits
 * \param pointer on the configuration structure
 * \param value, value to apply on outputs
 * \return code error
 */
int mcp23008_setPort(device_mcp23008 *mcp23008config, unsigned char value){
    unsigned char err =0;
    unsigned char deviceAddress = mcp23008config->deviceAddress;
    
    err += i2c_write(0, deviceAddress, OLAT, value);
    return err;
}

/**
 * \brief MCP23008 get input value on GPIO port
 * \param pointer on the configuration structure
 * \return code error
 */
int mcp23008_getPort(device_mcp23008 *mcp23008config){
    unsigned char err =0;
    unsigned char deviceAddress = mcp23008config->deviceAddress;
    int MCP2308_GPIO_STATE;

    err += i2c_readByte(0, deviceAddress, GPIO, &MCP2308_GPIO_STATE);

    if(!err)
        return MCP2308_GPIO_STATE;
    else 
        return -1;      
}