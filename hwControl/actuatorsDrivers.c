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
                //printf("\n\n Configuring PCA9629\n----------------------------------\n")
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
                strcpy(dev_pca9629[pca9629_count].deviceName, boardDevice[i].name);
                dev_pca9629[pca9629_count].deviceAddress = boardDevice[i].address;
                err += pca9629_init(&dev_pca9629[pca9629_count]);
                printDeviceData(i, &boardDevice[i]);
                pca9629_count++;
            }
             
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
    
    if(ptrDev>=0){
        printf("SET LED POWER FROM NEW DRIVERS:  NAME:%s   I2C add: 0x%2x    dout_id: %d     channel: %d     power: %d     frequency: %d\n",kehopsActuators.dout[dout_id].hw_driver.name,  dev_pca9685[ptrDev].deviceAddress, dout_id, channel, power, dev_pca9685[ptrDev].frequency);         
        pca9685_setPWMdutyCycle(&dev_pca9685[ptrDev], channel, power);
    }else printf ("#! Function [actuator_setLedPower] -> Unknown driver name: %s\n", kehopsActuators.dout[dout_id].hw_driver.name);
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
    if(ptrDev>=0){
        printf("SET PWM POWER FROM NEW DRIVERS:  NAME:%s   I2C add: 0x%2x    dout_id: %d     channel: %d     power: %d     frequency: %d\n",kehopsActuators.dout[dout_id].hw_driver.name,  dev_pca9685[ptrDev].deviceAddress, dout_id, channel, power, dev_pca9685[ptrDev].frequency);        
        pca9685_setPWMdutyCycle(&dev_pca9685[ptrDev], channel, power);
    }else printf ("#! Function [actuator_setPwmPower] -> Unknown driver name: %s\n", kehopsActuators.dout[dout_id].hw_driver.name);
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
    
    if(ptrDev>=0){
        printf("SET SERVO POSITION FROM NEW DRIVERS: NAME: %s   I2Cadd: 0x%2x    dout_id: %d     channel: %d     position: %d     time: %.2f\n",kehopsActuators.dout[dout_id].hw_driver.name, dev_pca9685[ptrDev].deviceAddress, dout_id, channel, position, time_ms);    
        pca9685_setPulseWidthTime(&dev_pca9685[ptrDev], channel, time_ms);
    }else printf ("#! Function [actuator_setServoPosition] -> Unknown driver name: %s\n", kehopsActuators.dout[dout_id].hw_driver.name);
}


/**
 * \fn char actuator_setStepperStepAction()
 * \brief Get the STEPPER hardware id of and setup direction and step count to do
 *
 * \param motorNumber, direction, stepCount
 * \return -
 */

int actuator_setStepperStepAction(int motorNumber, int direction, int stepCount){
    int ptrDev;
    unsigned char ctrlData = 0;
    unsigned char PMAmode = 0;
        

        // Check if motor inversion requiered and modify if necessary
    if(kehops.stepperWheel[motorNumber].config.motor.inverted)
        direction *= -1;

    switch(direction){
            case BUGGY_FORWARD :	ctrlData = 0x80; break;
            case BUGGY_BACK :           ctrlData = 0x81; break;

            case BUGGY_STOP : 		ctrlData = 0x20; break;
            default :		     	break;
    }
        
    if(stepCount<=0)
        // Configuration du driver pour une rotation continue
       PMAmode = 0x00;
    else
        // Configuration du driver pour une action unique
        PMAmode = 0x01;
    
    
    
    int stepper_id = kehops.stepperWheel[motorNumber].config.motor.stepper_motor_id; 
    ptrDev = getPCA9629config_ptr(kehopsActuators.stepper_motors[stepper_id].hw_driver.name);
    
    if(ptrDev>=0){
        printf("SET STEPPER STEP ACTION FROM NEW DRIVERS: NAME: %s   I2Cadd: 0x%2x    stepper_id: %d     STEPS: %d \n", kehopsActuators.stepper_motors[stepper_id].hw_driver.name, dev_pca9685[ptrDev].deviceAddress, stepper_id, stepCount);    
        // Reset le registre de contronle
        // (Indispensable pour une nouvelle action après une action infinie)
        PCA9629_StepperMotorControl(&dev_pca9629[ptrDev], 0x00);

        // Assignation du mode action continu ou unique
        PCA9629_StepperMotorMode(&dev_pca9629[ptrDev], PMAmode);
        PCA9629_StepperMotorSetStep(&dev_pca9629[ptrDev], stepCount);
        PCA9629_StepperMotorControl(&dev_pca9629[ptrDev], ctrlData);
    }else printf ("#! Function [actuator_setStepperStepAction] -> Unknown driver name: %s\n", kehopsActuators.stepper_motors[stepper_id].hw_driver.name);
    
    return (0);
} 

/*
 * \fn char actuator_setStepperSpeed()
 * \brief Get the STEPPER hardware id of and setup the speed
 *
 * \param motorNumber, direction, stepCount
 * \return -
 */

int actuator_setStepperSpeed(int motorNumber, int speed){
        int regData;
        int ptrDev;
    
    	// V�rification ratio max et min comprise entre 0..100%
	if(speed > 100)
		speed = 100;
	if (speed<0)
		speed = 1;

        // Periode minimum (2mS) + vitesse en % (max 22.5mS)
        regData = 0x029A + ((100-speed) * 75);
       
    int stepper_id = kehops.stepperWheel[motorNumber].config.motor.stepper_motor_id; 
    ptrDev = getPCA9629config_ptr(kehopsActuators.stepper_motors[stepper_id].hw_driver.name);
    
    if(ptrDev>=0){
        printf("SET STEPPER STEP SPEED FROM NEW DRIVERS: NAME: %s   I2Cadd: 0x%2x    stepper_id: %d     SPEED: %d \n", kehopsActuators.stepper_motors[stepper_id].hw_driver.name, dev_pca9685[ptrDev].deviceAddress, stepper_id, speed);    
        PCA9629_StepperMotorPulseWidth(&dev_pca9629[ptrDev], regData);
    }else printf ("#! Function [actuator_setStepperSpeed] -> Unknown driver name: %s\n", kehopsActuators.stepper_motors[stepper_id].hw_driver.name);
         
    return (1);
}

/*
 * \fn char actuator_getStepperState()
 * \brief Get the STEPPER state register
 *
 * \param motorNumber
 * \return -
 */

int actuator_getStepperState(int motorNumber){
    int state;
    
    state = PCA9629_ReadMotorState(&dev_pca9629[0]);
    //printf("ACTUATOR GETSTEPPERSTATE: address = 0x%2x     value: 0x%2x\n",dev_pca9629[0].deviceAddress, state);
    return state;
}



//-----------------------------------------------------------------------
int getPCA9685config_ptr(char * name){
    int i, refFound=-1;
    
    for(i=0; refFound<0 && i<pca9685_count ;i++){
        if(!strcmp(dev_pca9685[i].deviceName, name)){
            refFound = i;
        }
    }       
    return refFound;
}

int getPCA9629config_ptr(char * name){
    int i, refFound=-1;
    
    for(i=0; refFound<0 && i<pca9629_count ;i++){
        if(!strcmp(dev_pca9629[i].deviceName, name)){
            refFound = i;
        }
    }       
    return refFound;
}



