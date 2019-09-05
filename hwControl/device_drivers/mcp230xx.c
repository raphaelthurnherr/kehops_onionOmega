/**
 * \file mcp230xx.c
 * \brief MCP230xx GPIO Extender drivers
 * \author Raphael Thurnherr
 * \version 0.1
 * \date 18.03.2019
 *
 * Library to setup and use the 8 channel MCP230xx GPIO extender I2C device
 * 
 * MCP23017 Use two bank register (IOCON.BANK =1)
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


#include "mcp230xx.h"
#include <onion-i2c.h>

/**
 * \brief MCP23008 driver initialization
 * \param pointer on the configuration structure
 * \return code error
 */
int mcp23008_init(device_mcp230xx *mcp230xxconfig){
    int err =0;
    
    // Get the use configuratiom, ignore the 8 MSB if 16bit configuration
    unsigned char deviceAddress = mcp230xxconfig->deviceAddress;
    unsigned char gpioDirection = mcp230xxconfig->gpioDirection & 0x00FF;
    unsigned char invertedInput = mcp230xxconfig->invertedInput & 0x00FF;
    unsigned char pullupEnable = mcp230xxconfig->pullupEnable & 0x00FF;
    
    // Disable auto-incrementationS
    err+= i2c_write(0, deviceAddress, IOCON, 0x20);

    // Set GPIO in output or input mode
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
 * \brief MCP23017 driver initialization
 * \param pointer on the configuration structure
 * \return code error
 */
int mcp23017_init(device_mcp230xx *mcp230xxconfig){
    int err =0;    
    unsigned char deviceAddress = mcp230xxconfig->deviceAddress;
    unsigned int gpioDirection = mcp230xxconfig->gpioDirection;
    unsigned int invertedInput = mcp230xxconfig->invertedInput;
    unsigned int pullupEnable = mcp230xxconfig->pullupEnable;
    
    // Disable auto-incrementation, use if possible two separate bank
    err+= i2c_write(0, deviceAddress, IOCON, 0xA0);

 //BANK 1 CONFIGURATION (GPIO-A)
    // Set GPIO in output or input mode)
    if(!err) 
        err+= i2c_write(0, deviceAddress, IODIR, gpioDirection & 0x00FF);

    // Pull up enable         
    if(!err) 
        err+= i2c_write(0, deviceAddress, GPPU, pullupEnable & 0x00FF);

    // Set input inverted logic    
    if(!err) 
        err+= i2c_write(0, deviceAddress, IPOL, invertedInput & 0x00FF);

 //BANK 2 CONFIGURATION (GPIO-B)
    // Set GPIO in output or input mode)
    if(!err) 
        err+= i2c_write(0, deviceAddress, IODIR | 0x10, (gpioDirection & 0xFF00)) >> 8;

    // Pull up enable         
    if(!err) 
        err+= i2c_write(0, deviceAddress, GPPU | 0x10, (pullupEnable & 0xFF00)) >> 8;

    // Set input inverted logic    
    if(!err) 
        err+= i2c_write(0, deviceAddress, IPOL | 0x10, (invertedInput & 0xFF00)) >> 8;
    
    if(err)
        printf("Kehops I2C MCP23017 device initialization with %d error\n", err);

    return err;
}


/**
 * \brief MCP230xx read input state on specified input channel
 * \param pointer on the configuration structure
 * \param channel, specify the channel to get state
 * \return code error
 */
int mcp230xx_getChannel(device_mcp230xx *mcp230xxconfig, unsigned char channel){
    unsigned char err =0;
    unsigned char deviceAddress = mcp230xxconfig->deviceAddress;
    int MCP230xx_GPIO_STATE = 0;
    int MCP230xx_GPIOB_STATE = 0;
    unsigned char value=0;
      
    // Get the PORT A Value
    err += i2c_readByte(0, deviceAddress, GPIO, &MCP230xx_GPIO_STATE);
    
    // Get the PORT B Value (Read "0" on MCP 23008)
    err += i2c_readByte(0, deviceAddress, GPIO | 0x10, &MCP230xx_GPIOB_STATE);
    MCP230xx_GPIO_STATE |= MCP230xx_GPIOB_STATE << 8;
    
    if(MCP230xx_GPIO_STATE & (0x01<<channel))
        value = 0;
    else 
        value = 1;

    if(!err)
        return value;
    else 
        return -1;    
}

/**
 * \brief MCP230xx set output state on specified input channel, the function read port state before rewrite
 * \param pointer on the configuration structure
 * \param channel, specify the channel to set state
 * \param state, state to apply on output
 * \return code error
 */
int mcp230xx_setChannel(device_mcp230xx *mcp230xxconfig, unsigned char channel, unsigned char state){
    unsigned char err =0;
    int MCP230xx_GPIO_STATE;
    unsigned char GPIOBREG = 0x00;       // By default, PORT A Selected (Reg adresse 0x00..0x0A
    
    unsigned char deviceAddress = mcp230xxconfig->deviceAddress;
   
    // Modify address register (0x10 .. 0x1A) if channel 8..15 are used according the bank register of MCP23017 
    if(channel >= 8){
        GPIOBREG = 0x10;
        channel -= 8;       // Convert 16 port to 2x 8 bit port. (Channel 16 will be channel 7 on PORT B)
    }
    
    // Get the PORT x Value    
    err += i2c_readByte(0, deviceAddress, GPIO | GPIOBREG, &MCP230xx_GPIO_STATE);
    
    if(state)
        MCP230xx_GPIO_STATE |= (0x01<<channel);
    else
        MCP230xx_GPIO_STATE &= (0xFF-(0x01 << channel));
    
    err += i2c_write(0, deviceAddress, OLAT | GPIOBREG, MCP230xx_GPIO_STATE);
    
    return err;
}

/**
 * \brief MCP230xx set output values on all GPIO port bits
 * \param pointer on the configuration structure
 * \param value, value to apply on outputs
 * \return code error
 */
int mcp230xx_setPort(device_mcp230xx *mcp230xxconfig, unsigned char value){
    unsigned char err =0;
    unsigned char deviceAddress = mcp230xxconfig->deviceAddress;
    
    err += i2c_write(0, deviceAddress, OLAT, value);
    return err;
}

/**
 * \brief MCP230xx get input value on GPIO port
 * \param pointer on the configuration structure
 * \return code error
 */
int mcp230xx_getPort(device_mcp230xx *mcp230xxconfig){
    unsigned char err =0;
    unsigned char deviceAddress = mcp230xxconfig->deviceAddress;
    int MCP230xx_GPIO_STATE;

    err += i2c_readByte(0, deviceAddress, GPIO, &MCP230xx_GPIO_STATE);

    if(!err)
        return MCP230xx_GPIO_STATE;
    else 
        return -1;      
}

#endif