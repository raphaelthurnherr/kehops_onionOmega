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
#include "pca9629.h"

// Device variable déclaration
#define MAX_PCA9685_DEVICE 8
#define MAX_PCA9629_DEVICE 8

device_pca9685 dev_pca9685[MAX_PCA9685_DEVICE];
device_pca9629 dev_pca9629[MAX_PCA9629_DEVICE];

unsigned char pca9685_count=0;
unsigned char pca9629_count=0;

int getPCA9685config_ptr(char * name);


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
    usleep(1000000);

    for(i=0; boardDevice[i].address >= 0 && i<MAX_BOARD_DEVICE; i++){
        // DEVICES TYPE PCA9585 CONFIGURATION
            if(!strcmp(boardDevice[i].type, "pca9685")){              
                // Setting up the pca9685 device
                strcpy(dev_pca9685[pca9685_count].deviceName, boardDevice[i].name);
                if(boardDevice[i].attributes.frequency <= 0)
                    dev_pca9685[pca9685_count].frequency =200;
                else
                    dev_pca9685[pca9685_count].frequency = boardDevice[i].attributes.frequency;     
                dev_pca9685[pca9685_count].totemPoleOutput=1;                 
                dev_pca9685[pca9685_count].deviceAddress = boardDevice[i].address;                
                err += pca9685_init(&dev_pca9685[pca9685_count]);
                //printDeviceData(i, &boardDevice[i]);
                pca9685_count++;
            }
            
        // DEVICES TYPE PCA9529 CONFIGURATION
            if(!strcmp(boardDevice[i].type, "pca9629")){              
                // Setting up the pca9629 device
               
                printf("\n\n Configuring PCA9629\n----------------------------------\n");
                dev_pca9629[pca9629_count].deviceAddress = boardDevice[i].address;
                err += pca9629_init(&dev_pca9629[pca9629_count]);
                printDeviceData(i, &boardDevice[i]);
                pca9629_count++;
            }
             
    }
    

    for(i=0; boardDevice[i].address >= 0 && i<MAX_BOARD_DEVICE; i++){

    }
  
    return err;
}

/**
 * \fn char actuator_setLedPower()
 * \brief Get the DOUT hardware id of the LED from config and apply the PWM settings
 *
 * \param ledID, power
 * \return -
 */

char actuator_setLedPower(int ledID, int power){
    int ptrDev;
    int dout_id = kehops.led[ledID].config.dout_id;  
    int channel = kehopsActuators.dout[dout_id].hw_driver.attributes.device_channel;
    
    ptrDev = getPCA9685config_ptr(kehopsActuators.dout[dout_id].hw_driver.name);
       
    printf("SET LED POWER FROM NEW DRIVERS:  NAME:%s   I2C add: 0x%2x    dout_id: %d     channel: %d     power: %d     frequency: %d\n",kehopsActuators.dout[dout_id].hw_driver.name,  dev_pca9685[ptrDev].deviceAddress, dout_id, channel, power, dev_pca9685[ptrDev].frequency);         
    pca9685_setPWMdutyCycle(&dev_pca9685[ptrDev], channel, power);
}


/**
 * \fn char actuator_setPwmPower()
 * \brief Get the DOUT hardware id of the LED from config and apply the PWM settings
 *
 * \param pwmID, power
 * \return -
 */

char actuator_setPwmPower(int pwmID, int power){
    
    int dout_id = kehops.pwm[pwmID].config.dout_id;  
    int channel = kehopsActuators.dout[dout_id].hw_driver.attributes.device_channel;
    int ptrDev; 

    ptrDev = getPCA9685config_ptr(kehopsActuators.dout[dout_id].hw_driver.name);

    printf("SET PWM POWER FROM NEW DRIVERS:  NAME:%s   I2C add: 0x%2x    dout_id: %d     channel: %d     power: %d     frequency: %d\n",kehopsActuators.dout[dout_id].hw_driver.name,  dev_pca9685[ptrDev].deviceAddress, dout_id, channel, power, dev_pca9685[ptrDev].frequency);        
    pca9685_setPWMdutyCycle(&dev_pca9685[ptrDev], channel, power);
}

/**
 * \fn char actuator_setsetServoPosition()
 * \brief Get the DOUT hardware id of the SERVO from config and apply the PWM settings
 *
 * \param pwmID, position
 * \return -
 */

char actuator_setServoPosition(int pwmID, int position){
    float time_ms;
    int ptrDev;
    
    int dout_id = kehops.pwm[pwmID].config.dout_id;  
    int channel = kehopsActuators.dout[dout_id].hw_driver.attributes.device_channel;
    
    // Calculation of OFF Value for PCA
    if(position>100)
        position=100;

    if(position >= 0)
        time_ms = 0.8 + ((2.2-0.8)/100)*position;
    else
        time_ms = 0.0;                    // Turn off the servomotor (no refresh)   
    
    ptrDev = getPCA9685config_ptr(kehopsActuators.dout[dout_id].hw_driver.name);
    
    printf("SET SERVO POSITION FROM NEW DRIVERS: NAME: %s   I2Cadd: 0x%2x    dout_id: %d     channel: %d     position: %d     time: %.2f\n",kehopsActuators.dout[dout_id].hw_driver.name, dev_pca9685[ptrDev].deviceAddress, dout_id, channel, position, time_ms);
        
    pca9685_setPulseWidthTime(&dev_pca9685[ptrDev], channel, time_ms);
}



int getPCA9685config_ptr(char * name){
    int i, refFound=-1;
    
    for(i=0; refFound<0 && i<pca9685_count ;i++){
        if(!strcmp(dev_pca9685[i].deviceName, name)){
            refFound = i;
        }
    }
        
    return refFound;
}
