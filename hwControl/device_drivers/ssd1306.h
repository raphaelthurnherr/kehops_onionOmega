/**
 * \file ssd1306.h
 * \brief ssd1306 chipset graphic display
 * \author Raphael Thurnherr
 * \version 0.1
 * \date 24.04.2019
 *
 * Library to setup and drive the graphical display based on SSD1306 driver
 * 
 */


#ifndef SSD1306_H
#define SSD1306_H

/**
 * \struct ssd1306 [ssd1306.h] Configuration structure definition
 */

typedef struct ssd1306{
    char deviceName[25];                        // Device Name of IC
    unsigned char deviceAddress;                // Bus device address
} device_ssd1306;

/**
 * \fn char ssd1306_init(device_ssd1306 *ssd1306config)
 * \brief SSD1306 driver initialization
 *
 * \param handler to SSD1306 configuration structure
 * \return Error
 */

extern int ssd1306_init(device_ssd1306 *ssd1306config);

#endif /* SSD1306_H */
