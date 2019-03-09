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

#ifndef PARTSDESCRIPTOR_H
#define PARTSDESCRIPTOR_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Open and load parts descriptor configuration
 * \return code error
 */  
extern char LoadDescriptor(char * fileName);


#ifdef __cplusplus
}
#endif

#endif /* PARTSDESCRIPTOR_H */

