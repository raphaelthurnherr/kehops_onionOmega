/**
 * \file partsDescriptor.h
 * \brief  Interconnect the user parts (like LEDs components) to the hardware
 *  driver IC output (like PCA9685 driver) or generic driver.
 *      
 * \author Raphael Thurnherr
 * \version 0.1
 * \date 09.03.2019
 *
 *  With reading the partsDescriptor config file, these functions will create dynamically
 *  the connections between the user components parts (leds, motors, etc..) and the terminals
 *  of the driver IC. 
 * 
 */

#ifndef DRIVERSDESCRIPTOR_H
#define DRIVERSDESCRIPTOR_H

struct attributes{
    struct deviceInit{
        unsigned char regAddr;
        unsigned char regData;
    } deviceInit[16];
};

typedef struct devicesList{
    char type[15];
    unsigned char address;
    struct attributes attributes;
    
}devices_list;
    
/**
 * \brief Open and load drivers descriptor configuration
 * \return code error
 */  
extern char LoadDriversDescriptor(char * fileName);


/**
 * \brief Open and load electronic devices descriptor configuration
 * \return code error
 */  
extern char LoadDevicesDescriptor(char * fileName);

#endif /* DRIVERSDESCRIPTOR_H */

