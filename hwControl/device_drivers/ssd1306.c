/**
 * \file ssd1306.h
 * \brief ssd1306 chipset graphic display
 * \author Raphael Thurnherr
 * \version 0.1
 * \date 24.04.2019
 *
 * Library to setup and drive the graphical display based on SSD1306 driver
 * using API.
 * 
 */

#ifndef I2CSIMU

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "ssd1306.h"

/**
 * \fn char ssd1306_init(device_ssd1306 *ssd1306config)
 * \brief SSD1306 driver initialization
 *
 * \param handler to SSD1306 configuration structure
 * \return Error
 */

int ssd1306_init(device_ssd1306 *ssd1306config){
    int err =0;    
    unsigned char deviceAddress = ssd1306config->deviceAddress;

    err++;
    if(err)
        //printf("Kehops I2C SSD1306 graphical device initialization with %d error\n", err);

    return err;
}


#endif