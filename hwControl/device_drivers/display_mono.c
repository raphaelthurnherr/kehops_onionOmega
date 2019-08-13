/**
 * \file display.h
 * \brief display chipset graphic display
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

#include "api/gfx_u8g/u8g2.h"
#include "api/gfx_u8g/U8g2lib.h"

#include "display_mono.h"
#include "gfx_xbm_pics.h"

void display_welcomeMessage(u8g2_t *display, device_display * config);

/**
 * \fn char display_init(device_ssd1306 *ssd1306config)
 * \brief display driver initialization
 *
 * \param handler to SSD1306 configuration structure
 * \return Error
 */

int display_init(device_display *displayMonoConfig){
    int err =0;    
    unsigned char deviceAddress = displayMonoConfig->deviceAddress;
    
     u8g2_t * u8g2 = &displayMonoConfig->u8g2Conf;               // a structure which will contain all the data for one display

     err=1;
     
     switch (displayMonoConfig->controllerType){
         case CTRL_SSD1306 : 
                                if(displayMonoConfig->width == 128 && displayMonoConfig->height==64){
                                    err=0;
                                    u8g2_Setup_ssd1306_i2c_128x64_noname_f(u8g2, U8G2_R0, u8x8_byte_arm_linux_hw_i2c, u8x8_arm_linux_gpio_and_delay);
                                    break;
                                };
                                if(displayMonoConfig->width == 128 && displayMonoConfig->height==32){
                                    err=0;
                                    u8g2_Setup_ssd1306_i2c_128x32_univision_f(u8g2, U8G2_R0, u8x8_byte_arm_linux_hw_i2c, u8x8_arm_linux_gpio_and_delay);
                                    break;  // init u8g2 structure; break;

                                };                                    
                                    
         case CTRL_SH1106 :     if(displayMonoConfig->width == 128 && displayMonoConfig->height==64){
                                    err=0;
                                    u8g2_Setup_sh1106_i2c_128x64_noname_f(u8g2, U8G2_R0, u8x8_byte_arm_linux_hw_i2c, u8x8_arm_linux_gpio_and_delay);
                                    break;   // init u8g2 structure; break;
                                };
         
         case CTRL_SSD1305 :    if(displayMonoConfig->width == 128 && displayMonoConfig->height==64){
                                    err=0;
                                    u8g2_Setup_ssd1305_128x64_adafruit_f(u8g2, U8G2_R0, u8x8_byte_arm_linux_hw_i2c, u8x8_arm_linux_gpio_and_delay);
                                    break;  // init u8g2 structure; break;
                                };                                    
         default: break;
     }
    
    if(!err){
        u8g2_InitDisplay(u8g2); // send init sequence to the display, display is in sleep mode after this,
        u8g2_ClearDisplay(u8g2);
        u8g2_SetPowerSave(u8g2, 0); // wake up display
        
        display_welcomeMessage(u8g2, displayMonoConfig);
    }
        //printf("Kehops I2C SSD1306 graphical device initialization with %d error\n", err);

    usleep(25000);       // Display problem for this sh1106 ifnot wait
    return err;
}


#endif

/**
 * \fn char display_welcomeMessage(u8g2_t * display, char * name)
 * \brief Display the welcome logo on the display
 *
 * \param handler to u8g2_t configuration structure
 * \return Error
 */

//void display_welcomeMessage(u8g2_t * display, char * name){
    void display_welcomeMessage(u8g2_t * display, device_display * config){
    
    char * myString[32];

    // Clear buffer
    u8g2_ClearBuffer(display);

    if(config->width >= 128 && config->height<= 32){
        
        // Set logo to buffer
        u8g2_DrawXBM(display, 0, 0, logo_name_128x32_width, logo_name_128x32_height, logo_name_128x32_bits);
    
        // Add text
        u8g2_SetFont(display, u8g2_font_10x20_tf);    
        sprintf(myString, "<%s>", config->deviceName);
        u8g2_DrawStr(display, 80, 30, myString);
        u8g2_SendBuffer(display);
    }
    
    if(config->width >= 128 && config->height>= 64){
        // Set logo to beffer
        u8g2_DrawXBM(display, 0, 0, kehops_logo_width, kehops_logo_height, kehops_logo);
    
        // Add text
        u8g2_SetFont(display, u8g2_font_10x20_tf);    
        sprintf(myString, "<%s>", config->deviceName);
        u8g2_DrawStr(display, 80, 35, myString);
        u8g2_SendBuffer(display);
    }  
}

/**
 * \fn char display_welcomeMessage(u8g2_t * display, char * name)
 * \brief Display the welcome logo on the display
 *
 * \param handler to u8g2_t configuration structure
 * \return Error
 */

void display_addXBM(device_display *displayMonoConfig, unsigned char x, unsigned char y, unsigned char width, unsigned char height, const unsigned char * picture){
    
    u8g2_t * u8g2 = &displayMonoConfig->u8g2Conf;               // a structure which will contain all the data for one display
    char * myString[32];

    // Set logo to beffer
    u8g2_DrawXBM(u8g2, x, y, width, height, picture);
}

/**
 * \fn char display_clearScreen(device_display *displayMonoConfig)
 * \brief Clear the screen
 *
 * \param handler to u8g2_t configuration structure
 * \return Error
 */

void display_clearScreen(device_display *displayMonoConfig){
    
    u8g2_t * u8g2 = &displayMonoConfig->u8g2Conf;               // a structure which will contain all the data for one display

    u8g2_ClearDisplay(u8g2);
}

/**
 * \fn char display_clearScreen(device_display *displayMonoConfig)
 * \brief Clear the screen
 *
 * \param handler to u8g2_t configuration structure
 * \return Error
 */

void display_clearBuffer(device_display *displayMonoConfig){
    u8g2_t * u8g2 = &displayMonoConfig->u8g2Conf;               // a structure which will contain all the data for one display
    
    // Clear buffer
    u8g2_ClearBuffer(u8g2);
}

/**
 * \fn char display_updateScreen(device_display *displayMonoConfig)
 * \brief Clear the screen
 *
 * \param handler to u8g2_t configuration structure
 * \return Error
 */

void display_updateScreen(device_display *displayMonoConfig){
    u8g2_t * u8g2 = &displayMonoConfig->u8g2Conf;               // a structure which will contain all the data for one display
    u8g2_SendBuffer(u8g2);
}

/**
 * \fn char display_addText(u8g2_t * display, char * name)
 * \brief Display the welcome logo on the display
 *
 * \param handler to u8g2_t configuration structure
 * \return Error
 */

void display_addText(device_display *displayMonoConfig, unsigned char x, unsigned char y, unsigned char size, char * text){
    
    u8g2_t * u8g2 = &displayMonoConfig->u8g2Conf;               // a structure which will contain all the data for one display

    // Add text
    switch(size){
        case 0 : u8g2_SetFont(u8g2, u8g2_font_6x12_mf); break;
        case 1 : u8g2_SetFont(u8g2, u8g2_font_6x13_mf); break;
        case 2 : u8g2_SetFont(u8g2, u8g2_font_7x13_tf); break;
        case 3 : u8g2_SetFont(u8g2, u8g2_font_10x20_tf); break;
        
        default: u8g2_SetFont(u8g2, u8g2_font_6x12_mf); break;
    }

    u8g2_DrawStr(u8g2, x, y, text);
}

/**
 * \fn char display_addIcon(device_display *displayMonoConfig, unsigned char x, unsigned char y, unsigned char type, char * text)
 * \brief Display a selected logo from font source
 *
 * \param handler to u8g2_t configuration structure
 * \return Error
 */

void display_addIcon(device_display *displayMonoConfig, unsigned char x, unsigned char y, unsigned char type, char * text){
    
    u8g2_t * u8g2 = &displayMonoConfig->u8g2Conf;               // a structure which will contain all the data for one display

    // Add text
    switch(type){
        case 0 : u8g2_SetFont(u8g2, u8g2_font_battery19_tn); break;
        
        default: u8g2_SetFont(u8g2, u8g2_font_battery19_tn); break;
    }
    
    u8g2_DrawStr(u8g2, x, y, text);
}

/**
 * \fn char display_addCircle(device_display *displayMonoConfig, unsigned char x, unsigned char y, unsigned char filled)
 * \brief Display a selected logo from font source
 *
 * \param handler to u8g2_t configuration structure
 * \return Error
 */

void display_addCircle(device_display *displayMonoConfig, unsigned char x, unsigned char y, unsigned char radius, unsigned char filled){
    
    u8g2_t * u8g2 = &displayMonoConfig->u8g2Conf;               // a structure which will contain all the data for one display

    if(!filled)
        u8g2_DrawCircle(u8g2, x, y, radius, U8G2_DRAW_ALL);
    else
        u8g2_DrawDisc(u8g2, x, y, radius, U8G2_DRAW_ALL);
}