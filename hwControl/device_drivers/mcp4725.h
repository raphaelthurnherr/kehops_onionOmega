/**
 * \file mcp4725.h
 * \brief MCP4725 Digital analog converter with eeprom memory driver
 *  I2C default address: 0x60 (7 bit)
 * \author Raphael Thurnherr
 * \version 0.1
 * \date 24.04.2019
 *
 * Library to setup and drive the DAC converter MCP4725
 * 
 */

#ifndef MCP4725_H
#define MCP4725_H

/**
 * \struct mcp4725 [mcp4725.h] Configuration structure definition
 */

typedef struct mcp4725{
    char deviceName[25];                        // Device Name of IC
    unsigned char deviceAddress;                // Bus device address
    unsigned int vref_mv;                       // VoltageReference value in mV (2.7..5.5)
} device_mcp4725;

/**
 * \brief MCP4725 driver initialization
 * \param pointer on the configuration structure
 * \return code error
 */
extern int mcp4725_init(device_mcp4725 *mcp4725config);        // MCP4725 driver initialization

/**
 * \brief MCP4725 set output voltage in mV
 * \param pointer on the configuration structure
 * \return code error
 */
extern int mcp4725_setDACOutput_mV(device_mcp4725 *mcp4725config, int value_mv);

/**
 * \brief MCP4725 set output voltage by 12 bit value
 * \param pointer on the configuration structure
 * \return code error
 */
extern int mcp4725_setDAC_12bitValue(device_mcp4725 *mcp4725config, int value);


#endif /* MCP4725_H */
