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
#include "api/ssd1306/SSD1306_OLED.h"

/* draw rectangles */
void testdrawrect();

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

    /* Run SDD1306 Initialization Sequence */
    display_Init_seq();

    /* Clear display */
    clearDisplay();
    Display();
    
    
    setTextSize(1);
    setTextColor(WHITE);
    setCursor(10,0);
    print_str("HELLO FELLAS!");
    println();
    printFloat_ln(3.141592, 4); //Print 4 No's after the decimal Pt.
    printNumber_L_ln(-1234, DEC);
    printNumber_UC_ln(170, BIN);
    setTextSize(2);
    setTextColor(WHITE);
    print_str("0x");
    printNumber_UL_ln(0xDEADBEEF, HEX);
    

    if(err)
        printf("Kehops I2C SSD1306 graphical device initialization with %d error\n", err);

    return err;
}


/* draw rectangles */
void testdrawrect() 
{
    short i = 0;
    for (i=0; i<SSD1306_LCDHEIGHT/2; i+=2)
    {
        drawRect(i, i,SSD1306_LCDWIDTH-2*i, SSD1306_LCDHEIGHT-2*i, WHITE);
        Display();
        usleep(1000);
    }
}
#endif