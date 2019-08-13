/**
 * \file display.h
 * \brief display chipset graphic display
 * \author Raphael Thurnherr
 * \version 0.1
 * \date 24.04.2019
 *
 * Library to setup and drive the graphical display based on SSD1306 driver
 * 
 */


#ifndef display_H
#define display_H

#include "api/gfx_u8g/u8g2.h"


/**
 * \enum Grafic cotroller list
 */
typedef enum gfx_controller_list{
    CTRL_SSD1305,
    CTRL_SSD1306,
    CTRL_SH1106
} gfx_list;

/**
 * \struct display [display.h] Configuration structure definition
 */

typedef struct display{
    char deviceName[25];                        // Device Name of IC
    int controllerType;                         // Device controller of the display
    int width;                         // Device controller of the display
    int height;                         // Device controller of the display
    unsigned char deviceAddress;                // Bus device address
    u8g2_t u8g2Conf;               // a structure which will contain all the data for one display    
    
    
} device_display;

/**
 * \fn char display_init(device_ssd1306 *ssd1306config)
 * \brief display driver initialization
 *
 * \param handler to display configuration structure
 * \return Error
 */

extern int display_init(device_display *displayMonoConfig);

extern void display_clearScreen(device_display *displayMonoConfig);
extern void display_clearBuffer(device_display *displayMonoConfig);

extern void display_addXBM(device_display *displayMonoConfig, unsigned char x, unsigned char y, unsigned char width, unsigned char height, const unsigned char * picture);
extern void display_addText(device_display *displayMonoConfig, unsigned char x, unsigned char y, unsigned char size, char * text);
extern void display_addIcon(device_display *displayMonoConfig, unsigned char x, unsigned char y, unsigned char type, char * text);
extern void display_addCircle(device_display *displayMonoConfig, unsigned char x, unsigned char y, unsigned char radius, unsigned char filled);

extern void display_updateScreen(device_display *displayMonoConfig);
#endif /* display */
