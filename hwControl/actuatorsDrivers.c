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

//#define INFO_DEBUG

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "actuatorsDrivers.h"
#include "../configManager.h"
#include "../config/deviceMapping.h"
#include "../kehops_main.h"

// Device drivers libraries declaration
#include "pca9685.h"

// Device variable déclaration
device_pca9685 dev_pca9685;

/**
 * \fn char boardHWinit()
 * \brief Initialize the devices IC of the board and the 
 *
 * \param filename to open
 * \return -
 */

int boardHWinit(void){
    int err = 0;
    int i;

    // DEVICES TYPE PCA9585 CONFIGURATION
    for(i=0; boardDevice[i].address >= 0 && i<MAX_BOARD_DEVICE; i++){
            if(!strcmp(boardDevice[i].type, "_pca9685")){
                // Setting up the pca9685 device
                dev_pca9685.frequency=50;
                dev_pca9685.totemPoleOutput=1;                 
                dev_pca9685.deviceAddress = boardDevice[i].address;
                err += pca9685_init(&dev_pca9685);
                #ifdef INFO_DEBUG
                    printf("\n__________ID [%d] , TYPE: %s  ADDRESS: %d  [0x%02x]\n",i, boardDevice[i].type, boardDevice[i].address, boardDevice[i].address);
                #endif                
            }
    }

    /*
    for(i=0;i<MAX_DRIVERS_PER_TYPE;i++){
        if(kehopsActuators.dout[i].id >= 0){
            
            #ifdef INFO_DEBUG
                printf("\n__________MAIN DOUT : PART ID: %d, DEVICE ADDRESS: 0x%2x, TYPE: %s  CHANNEL: %d\n", kehopsActuators.dout[i].id, kehopsActuators.dout[i].hw_driver.address, 
                kehopsActuators.dout[i].hw_driver.device_type, kehopsActuators.dout[i].hw_driver.attributes.device_channel);
            #endif
        }
    }        
      */     
    return err;
}

/**
 * \fn char actuator_setLedPower()
 * \brief Apply on the DOUT the requiere PWM
 *
 * \param ledID, powerr
 * \return -
 */

char actuator_setLedPower(int ledID, int power){
    
    int dout_id = kehops.led[ledID].config.dout_id;  
    int channel = kehopsActuators.dout[dout_id].hw_driver.attributes.device_channel;
    
    printf("SET LED POWER FROM NEW DRIVERS:    dout_id: %d     channel: %d     power: %d\n", dout_id, channel, power);
    
    dev_pca9685.deviceAddress = kehopsActuators.dout[dout_id].hw_driver.address;
    pca9685_setPWMdutyCycle(&dev_pca9685, channel, power);
}


