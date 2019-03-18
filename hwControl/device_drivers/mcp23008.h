/**
 * \file mcp23008.h
 * \brief MCP23008 GPIO Extender drivers
 * \author Raphael Thurnherr
 * \version 0.1
 * \date 18.03.2019
 *
 * Library to setup and use the 8 channel MCP23008 GPIO extender I2C device
 * 
 */

#ifndef MCP23008_H
#define MCP23008_H

/**
 * \struct mcp23008 [mcp23008.h] Configuration structure definition
 */

typedef struct mcp23008{
    unsigned char deviceAddress;                // Bus device address
    unsigned char gpioDirection;                // Specify the GPIO's port dirtection, 1 input, 0 output
    unsigned char invertedInput;               // >0, invert the output logic level
    unsigned char pullupEnable;                 // The internal pullup 100k resistor configuration, 1 enable, 0 disable.
} device_mcp23008;

/**
 * \brief MCP23008 driver initialization
 * \param pointer on the configuration structure
 * \return code error
 */
extern int mcp23008_init(device_mcp23008 *mcp23008config);        // PCA9685 driver initialization



/**
 * \brief MCP23008 read input state on specified input channel
 * \param pointer on the configuration structure
 * \return code error
 */
extern int mcp23008_getChannel(device_mcp23008 *mcp23008config, unsigned char channel);


/**
 * \brief MCP23008 set output state on specified input channel, the function read port state before rewrite
 * \param pointer on the configuration structure
 * \return code error
 */
extern int mcp23008_setChannel(device_mcp23008 *mcp23008config, unsigned char channel, unsigned char state);

/**
 * \brief MCP23008 set output values on all GPIO port bits
 * \param pointer on the configuration structure
 * \param value, value to apply on outputs
 * \return code error
 */
extern int mcp23008_setPort(device_mcp23008 *mcp23008config, unsigned char value);

/**
 * \brief MCP23008 get input value on GPIO port
 * \param pointer on the configuration structure
 * \return code error
 */
extern int mcp23008_getPort(device_mcp23008 *mcp23008config);

#endif /* MCP23008_H */
