/**
 * \file actuatorsDrivers.h
 * \brief  Set or Get action on an actuator of Kehops
 *      
 * \author Raphael Thurnherr
 * \version 0.1
 * \date 21.03.2019
 *
 * Using the configManager with devices_list (IC) and parts list (LED, Motor, etc...), these functions will
 * interconnect the hi level commands (motors, led, etc...) to the hardware output or inputs devices
 * 
 * Note: Per definition, a generic "drivers" can use more one IC drivers for create an action on an actuator
 */


#ifndef ACTUATORSDRIVERS_H
#define ACTUATORSDRIVERS_H

/**
 * \brief Initialize the devices IC of the board
 * \param -
 * \return -
 */  

extern int boardHWinit();

/**
 * \brief Apply on the DOUT the requiere PWM
 * \param -
 * \return -
 */  
extern char actuator_setLedPower(int ledID, int power);

        
#endif /* ACTUATORSDRIVERS_H */
