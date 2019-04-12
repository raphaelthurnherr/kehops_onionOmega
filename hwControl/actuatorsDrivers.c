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
#include <ctype.h>

#include "actuatorsDrivers.h"
#include "../configManager.h"
#include "../config/deviceMapping.h"
#include "../kehops_main.h"

// Device drivers libraries declaration
#include "pca9685.h"
#include "pca9629.h"
#include "efm8_mcu_kehops.h"
#include "mcp23008.h"
#include "bh1745.h"

// Device variable déclaration
#define MAX_PCA9685_DEVICE 8
#define MAX_PCA9629_DEVICE 8
#define MAX_EFM8BB_DEVICE 8
#define MAX_MCP23008_DEVICE 8
#define MAX_BH1745_DEVICE 8

device_pca9685 dev_pca9685[MAX_PCA9685_DEVICE];
device_pca9629 dev_pca9629[MAX_PCA9629_DEVICE];
device_efm8McuKehops dev_efm8bb[MAX_EFM8BB_DEVICE];
device_mcp23008 dev_mcp23008[MAX_MCP23008_DEVICE];
device_bh1745 dev_bh1745[MAX_BH1745_DEVICE];

unsigned char pca9685_count=0;
unsigned char pca9629_count=0;
unsigned char efm8bb_count=0;
unsigned char mcp23008_count=0;
unsigned char bh1745_count=0;

//int getDriverTypeByName(char * name); // Get the device type from the name and convert it to local definition

int getPCA9685config_ptr(char * name);
int getPCA9629config_ptr(char * name);
int getEFM8BBconfig_ptr(char * name);
int getMCP23008config_ptr(char * name);
int getBH1745config_ptr(char * name);

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
    //usleep(100000);

    for(i=0; boardDevice[i].address >= 0 && i<MAX_BOARD_DEVICE; i++){
        // DEVICES TYPE PCA9585 PWM DRIVER CONFIGURATION
            if(!strcmp(boardDevice[i].type, "pca9685")){              
                // Setting up the pca9685 device
                printf("\n\n Configuring PCA9629  [%s]\n----------------------------------\n",boardDevice[i].name);
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
            
        // DEVICES TYPE PCA9529 STEPPER MOTOR DRIVER CONFIGURATION
            if(!strcmp(boardDevice[i].type, "pca9629")){              
                // Setting up the pca9629 device               
                printf("\n\n Configuring PCA9629  [%s]\n----------------------------------\n", boardDevice[i].name);
                strcpy(dev_pca9629[pca9629_count].deviceName, boardDevice[i].name);
                dev_pca9629[pca9629_count].deviceAddress = boardDevice[i].address;
                err += pca9629_init(&dev_pca9629[pca9629_count]);
                //printDeviceData(i, &boardDevice[i]);
                pca9629_count++;
            }
            
            // DEVICES TYPE EFM8 MICROCONTROLER KEHOPS FIRMWARE CONFIGURATION
            if(!strcmp(boardDevice[i].type, "efm8bb")){              
                // Setting up the efm8bb MCU device               
                printf("\n\n Configuring EFM8BB  [%s]\n----------------------------------\n",boardDevice[i].name);
                strcpy(dev_efm8bb[efm8bb_count].deviceName, boardDevice[i].name);
                dev_efm8bb[efm8bb_count].deviceAddress = boardDevice[i].address;
                EFM8BB_init(&dev_efm8bb[efm8bb_count]);
                //printDeviceData(i, &boardDevice[i]);
                efm8bb_count++;
            }
            
            // DEVICES TYPE MCP23008 GPIO EXTENDER CONFIGURATION
            if(!strcmp(boardDevice[i].type, "mcp23008")){              
                // Setting up the mcp23008 GPIO extender              
                printf("\n\n Configuring MCP23008  [%s]\n----------------------------------\n",boardDevice[i].name);
                strcpy(dev_mcp23008[mcp23008_count].deviceName, boardDevice[i].name);
                dev_mcp23008[mcp23008_count].deviceAddress = boardDevice[i].address;
                dev_mcp23008[mcp23008_count].pullupEnable  = 0xff;                   // NEED TO BE DEFINE VIA CONFIG DEVICE.CFG
                dev_mcp23008[mcp23008_count].gpioDirection = 0x60;                  // NEED TO BE DEFINE VIA CONFIG DEVICE.CFG
                mcp23008_init(&dev_mcp23008[mcp23008_count]);
                printDeviceData(i, &boardDevice[i]);
                mcp23008_count++;
            }     
            
            // DEVICES TYPE BH1745 RGB SENSOR CONFIGURATION
            if(!strcmp(boardDevice[i].type, "bh1745")){              
                // Setting up the bh1745 rgb sensor
                printf("\n\n Configuring BH1745  [%s]\n----------------------------------\n",boardDevice[i].name);
                strcpy(dev_bh1745[bh1745_count].deviceName, boardDevice[i].name);
                dev_bh1745[bh1745_count].deviceAddress = boardDevice[i].address;
                bh1745nuc_init(&dev_bh1745[bh1745_count]);
                printDeviceData(i, &boardDevice[i]);
                bh1745_count++;
            }             
    }
    return err;
}

/**
 * \fn char actuator_setDoutValue()
 * \brief Get the DOUT hardware id of the output from config and apply the
 *  PWM settings if available, else boolean value is apply
 * \param pwmID, power
 * \return -
 */

char actuator_setDoutValue(int doutID, int value){
    
    int channel = kehopsActuators.dout[doutID].hw_driver.attributes.device_channel;
    int ptrDev; 

    // USE DRIVER FOR PCA9685
    if(!strcmp(kehopsActuators.dout[doutID].hw_driver.type, DRIVER_PCA9685)){
        ptrDev = getPCA9685config_ptr(kehopsActuators.dout[doutID].hw_driver.name);
        if(ptrDev>=0){
            printf("SET DOUT VALUE FROM <%s> DRIVERS:  NAME:%s TYPE:%s I2C add: 0x%2x    dout_id: %d     channel: %d     power: %d     frequency: %d\n",DRIVER_PCA9685, kehopsActuators.dout[doutID].hw_driver.name, kehopsActuators.dout[doutID].hw_driver.type, dev_pca9685[ptrDev].deviceAddress, doutID, channel, value, dev_pca9685[ptrDev].frequency);        
            pca9685_setPWMdutyCycle(&dev_pca9685[ptrDev], channel, value);
        }else 
            printf ("#! Function [actuator_setDoutValue] -> Unknown driver name: %s\n", kehopsActuators.dout[doutID].hw_driver.name);
        printf ("#! NOW USING  DRIVER 'PCA9685' for DOUT #%d\n", doutID);
    }
    
    // USE DRIVER FOR MCP23008
    if(!strcmp(kehopsActuators.dout[doutID].hw_driver.type, DRIVER_MCP23008)){
        ptrDev = getMCP23008config_ptr(kehopsActuators.dout[doutID].hw_driver.name);
        if(ptrDev>=0){
            printf("SET DOUT VALUE FROM <%s> DRIVERS:  NAME:%s TYPE:%s I2C add: 0x%2x    dout_id: %d     channel: %d     power: %d\n",DRIVER_MCP23008, kehopsActuators.dout[doutID].hw_driver.name, kehopsActuators.dout[doutID].hw_driver.type, dev_mcp23008[ptrDev].deviceAddress, doutID, channel, value);        
            mcp23008_setChannel(&dev_mcp23008[ptrDev], channel, value);
        }else 
            printf ("#! Function [actuator_setDoutValue] -> Unknown driver name: %s\n", kehopsActuators.dout[doutID].hw_driver.name);
        
            printf ("#! NOW USING  DRIVER 'MCP23008' for DOUT #%d\n", doutID);
    }
    
}

/**
 * \fn char actuator_setsetServoPosition()
 * \brief Get the DOUT hardware id of the SERVO from config and apply the PWM settings
 *
 * \param pwmID, position
 * \return -
 */

char actuator_setServoPosition(int doutID, int position){
    float time_ms;
    int ptrDev;
    
//    int dout_id = kehops.pwm[pwmID].config.dout_id;  
    int channel = kehopsActuators.dout[doutID].hw_driver.attributes.device_channel;
        
    // Calculation of OFF Value for PCA
    if(position>100)
        position=100;

    if(position >= 0)
        time_ms = 0.8 + ((2.2-0.8)/100)*position;
    else
        time_ms = 0.0;                    // Turn off the servomotor (no refresh)   
        
    // USE DRIVER FOR PCA9685
    if(!strcmp(kehopsActuators.dout[doutID].hw_driver.type, DRIVER_PCA9685)){
        ptrDev = getPCA9685config_ptr(kehopsActuators.dout[doutID].hw_driver.name);

        if(ptrDev>=0){
            printf("SET SERVO POSITION FROM NEW DRIVERS: NAME: %s TYPE:%s  I2Cadd: 0x%2x    dout_id: %d     channel: %d     position: %d     time: %.2f\n",kehopsActuators.dout[doutID].hw_driver.name,kehopsActuators.dout[doutID].hw_driver.type, dev_pca9685[ptrDev].deviceAddress, doutID, channel, position, time_ms);    
            pca9685_setPulseWidthTime(&dev_pca9685[ptrDev], channel, time_ms);
        }else printf ("#! Function [actuator_setServoPosition] -> Unknown driver name: %s\n", kehopsActuators.dout[doutID].hw_driver.name);
        printf ("#! NOW USING  DRIVER 'PCA9685' for Servomotor #%d\n", doutID);
    }
}


/**
 * \fn char actuator_setStepperStepAction()
 * \brief Get the STEPPER hardware id of and setup direction and step count to do
 *
 * \param motorNumber, direction, stepCount
 * \return -
 */

int actuator_setStepperStepAction(int stepperID, int direction, int stepCount){
    int ptrDev;
     
   
    // USE DRIVER FOR PCA9629
     if(!strcmp(kehopsActuators.stepper_motors[stepperID].hw_driver.type, DRIVER_PCA9629)){
        unsigned char ctrlData = 0;
        unsigned char PMAmode = 0;
        switch(direction){
            case BUGGY_FORWARD :	ctrlData = 0x80; break;
            case BUGGY_BACK :       ctrlData = 0x81; break;
            case BUGGY_STOP : 	ctrlData = 0x20; break;
            default :		     	break;
        }

        if(stepCount<=0)
            // Configuration du driver pour une rotation continue
           PMAmode = 0x00;
        else
            // Configuration du driver pour une action unique
            PMAmode = 0x01;

        ptrDev = getPCA9629config_ptr(kehopsActuators.stepper_motors[stepperID].hw_driver.name);

        if(ptrDev>=0){
            printf("SET STEPPER STEP ACTION FROM NEW DRIVERS: NAME: %s TYPE:%s  I2Cadd: 0x%2x    stepper_id: %d     STEPS: %d \n", kehopsActuators.stepper_motors[stepperID].hw_driver.name,kehopsActuators.stepper_motors[stepperID].hw_driver.type,  dev_pca9685[ptrDev].deviceAddress, stepperID, stepCount);    
            // Reset le registre de contronle
            // (Indispensable pour une nouvelle action après une action infinie)
            PCA9629_StepperMotorControl(&dev_pca9629[ptrDev], 0x00);

            // Assignation du mode action continu ou unique
            PCA9629_StepperMotorMode(&dev_pca9629[ptrDev], PMAmode);
            PCA9629_StepperMotorSetStep(&dev_pca9629[ptrDev], stepCount);
            PCA9629_StepperMotorControl(&dev_pca9629[ptrDev], ctrlData);
        }else printf ("#! Function [actuator_setStepperStepAction] -> Unknown driver name: %s\n", kehopsActuators.stepper_motors[stepperID].hw_driver.name);
        printf ("#! NOW USING  DRIVER 'PCA9629' for Stepper motor #%d\n", stepperID);
 }
    
    return (0);
} 

/*
 * \fn char actuator_setStepperSpeed()
 * \brief Get the STEPPER hardware id of and setup the speed
 *
 * \param motorNumber, direction, stepCount
 * \return -
 */


int actuator_setStepperSpeed(int stepperID, int speed){
   
        // V�rification ratio max et min comprise entre 0..100%
	if(speed > 100)
		speed = 100;
	if (speed<0)
		speed = 1;
    // USE DRIVER FOR PCA9629
     if(!strcmp(kehopsActuators.stepper_motors[stepperID].hw_driver.type, DRIVER_PCA9629)){    
        int regData;
        int ptrDev;

        // Periode minimum (2mS) + vitesse en % (max 22.5mS)
        regData = 0x029A + ((100-speed) * 75);

        ptrDev = getPCA9629config_ptr(kehopsActuators.stepper_motors[stepperID].hw_driver.name);

        if(ptrDev>=0){
            printf("SET STEPPER STEP SPEED FROM NEW DRIVERS: NAME: %s TYPE:%s  I2Cadd: 0x%2x    stepper_id: %d     SPEED: %d \n", kehopsActuators.stepper_motors[stepperID].hw_driver.name,kehopsActuators.stepper_motors[stepperID].hw_driver.type, dev_pca9685[ptrDev].deviceAddress, stepperID, speed);    
            PCA9629_StepperMotorPulseWidth(&dev_pca9629[ptrDev], regData);
        }else printf ("#! Function [actuator_setStepperSpeed] -> Unknown driver name: %s\n", kehopsActuators.stepper_motors[stepperID].hw_driver.name);
        printf ("#! NOW USING  DRIVER 'PCA9629' for Stepper motor #%d\n", stepperID);
     }
         
    return (1);
}

/*
 * \fn char actuator_getStepperState()
 * \brief Get the STEPPER state register
 *
 * \param motorNumber
 * \return -
 */

int actuator_getStepperState(int stepperID){
    int state;    
    
     // USE DRIVER FOR PCA9629
     if(!strcmp(kehopsActuators.stepper_motors[stepperID].hw_driver.type, DRIVER_PCA9629)){    
        int ptrDev = getPCA9629config_ptr(kehopsActuators.stepper_motors[stepperID].hw_driver.name);
        if(ptrDev>=0){
            state = PCA9629_ReadMotorState(&dev_pca9629[ptrDev]);
        }else{
            printf ("#! Function [actuator_getStepperState] -> Unknown driver name: %s\n", kehopsActuators.stepper_motors[stepperID].hw_driver.name);
            state = 0;
        }
        //printf ("#! NOW USING  DRIVER 'PCA9629' for Stepper motor #%d\n", stepperID);
     }
    return state;
}

// ------------------------------------------------------------------------------------
//EFM8
// ------------------------------------------------------------------------------------
int actuator_getCounterPulses(unsigned char wheelID){
    int counterPulses;
    int ptrDev;
    
    int counter_id = kehops.dcWheel[wheelID].config.encoder.pulseCounter_id; 
    
    ptrDev = getEFM8BBconfig_ptr(kehopsActuators.pulsesCounter[counter_id].hw_driver.name);
    if(ptrDev>=0){
        //printf("GET COUNTER FROM NEW DRIVERS: NAME: %s   I2Cadd: 0x%2x    counter_id: %d\n", kehopsActuators.pulsesCounter[counter_id].hw_driver.name, dev_efm8bb[ptrDev].deviceAddress, counter_id);    
        counterPulses = EFM8BB_getChannel(&dev_efm8bb[ptrDev], kehopsActuators.pulsesCounter[counter_id].hw_driver.attributes.device_channel);
    }else printf ("#! Function [actuator_getCounterPulses] -> Unknown driver name: %s\n", kehopsActuators.pulsesCounter[counter_id].hw_driver.name);
    return counterPulses;
}



int actuator_getCounterFrequency(unsigned char wheelID){
    int frequency;
    int ptrDev;
    
    int freq_id = kehops.dcWheel[wheelID].config.encoder.freqCounter_id;
        
    ptrDev = getEFM8BBconfig_ptr(kehopsActuators.freqCounter[freq_id].hw_driver.name);
    if(ptrDev>=0){
        //printf("GET FREQ FROM NEW DRIVERS: NAME: %s   I2Cadd: 0x%2x    counter_id: %d\n", kehopsActuators.freqCounter[freq_id].hw_driver.name, dev_efm8bb[ptrDev].deviceAddress, freq_id);    
        frequency = EFM8BB_getChannel(&dev_efm8bb[ptrDev], kehopsActuators.freqCounter[freq_id].hw_driver.attributes.device_channel);
    }else printf ("#! Function [actuator_getCounterFrequency] -> Unknown driver name: %s\n", kehopsActuators.freqCounter[freq_id].hw_driver.name);
    
    return frequency;
}

int actuator_getDigitalInput(unsigned char dinID){
    char value;
    int ptrDev;    
    //int din_id = kehops.proximity[dinID].config.din_id; 
        
    // USE DRIVER FOR EFM8BB
    if(!strcmp(kehopsActuators.din[dinID].hw_driver.type, DRIVER_EFM8BB)){
        ptrDev = getEFM8BBconfig_ptr(kehopsActuators.din[dinID].hw_driver.name);
        if(ptrDev>=0){
            value = EFM8BB_getChannel(&dev_efm8bb[ptrDev], kehopsActuators.din[dinID].hw_driver.attributes.device_channel);
        }else{
                printf ("#! Function [actuator_getDigitalInput] -> Unknown driver name: %s\n", kehopsActuators.din[dinID].hw_driver.name);
                value = -1;
        }
        //printf ("#! NOW USING  DRIVER 'EFM8BB' for DIN #%d\n", dinID);
    }

    // USE DRIVER FOR MCP23008
    if(!strcmp(kehopsActuators.din[dinID].hw_driver.type, DRIVER_MCP23008)){
        ptrDev = getMCP23008config_ptr(kehopsActuators.din[dinID].hw_driver.name);
        if(ptrDev>=0){
            value = mcp23008_getChannel(&dev_mcp23008[ptrDev], kehopsActuators.din[dinID].hw_driver.attributes.device_channel);
        }else{
                printf ("#! Function [actuator_getDigitalInput] -> Unknown driver name: %s\n", kehopsActuators.din[dinID].hw_driver.name);
                value = -1;
        }
        //printf ("#! NOW USING  DRIVER 'MCP23008' for DIN #%d\n", dinID);
    }
    
    // USE DRIVER FOR TARTEMPION TEST
    if(!strcmp(kehopsActuators.din[dinID].hw_driver.type, DRIVER_TARTEMPION)){
         //printf ("#! NOW USING OTHER DRIVER 'TARTEMPION' for DIN #%d\n", dinID);
         value = -1;
    }
    
    return value;
}

int actuator_getDistance(unsigned char distanceSensorID){
    int distance_mm =-1;
    int ptrDev;    
    int dist_id = kehops.sonar[distanceSensorID].config.distanceSensor_id; 
        
    ptrDev = getEFM8BBconfig_ptr(kehopsActuators.distanceSensor[dist_id].hw_driver.name);
    if(ptrDev>=0){
        distance_mm = EFM8BB_getChannel(&dev_efm8bb[ptrDev], kehopsActuators.distanceSensor[dist_id].hw_driver.attributes.device_channel);
    }else{
            printf ("#! Function [actuator_getDistance] -> Unknown driver name: %s\n", kehopsActuators.distanceSensor[dist_id].hw_driver.name);
            distance_mm = -1;
    }
    return distance_mm;
}

int actuator_getVoltage(unsigned char ainID){
    int voltage_mv;
    int ptrDev;    
    int ain_id = kehops.battery[ainID].config.ain_id; 
                
    ptrDev = getEFM8BBconfig_ptr(kehopsActuators.ain[ain_id].hw_driver.name);
    
    if(ptrDev>=0){
        voltage_mv = EFM8BB_getChannel(&dev_efm8bb[ptrDev], kehopsActuators.ain[ain_id].hw_driver.attributes.device_channel);
    }else{
            printf ("#! Function [actuator_getVoltage] -> Unknown driver name: %s\n", kehopsActuators.ain[ain_id].hw_driver.name);
            voltage_mv = -1;
    }
    return voltage_mv;
}

int actuator_getRGBColor(unsigned char rgbID, RGB_COLOR * rgbColor){
    int ptrDev;    
    int rgb_id = kehops.rgb[rgbID].config.rgbID; 
    
    ptrDev = getBH1745config_ptr(kehopsActuators.rgbSensor[rgb_id].hw_driver.name);
    if(ptrDev>=0){
        rgbColor->red = bh1745nuc_getChannelRGBvalue(&dev_bh1745[ptrDev], RED);
        rgbColor->green = bh1745nuc_getChannelRGBvalue(&dev_bh1745[ptrDev], GREEN);
        rgbColor->blue = bh1745nuc_getChannelRGBvalue(&dev_bh1745[ptrDev], BLUE);
        rgbColor->clear = bh1745nuc_getChannelRGBvalue(&dev_bh1745[ptrDev], CLEAR);
    }else{
            printf ("#! Function [actuator_getColor] -> Unknown driver name: %s\n", kehopsActuators.rgbSensor[rgb_id].hw_driver.name);
    }
    
    if(rgbColor->red >= 0 && rgbColor->green >= 0 && rgbColor->blue >= 0 && rgbColor->clear >= 0)
        return 0;
    else
        return -1;
}


/**
 * \brief int actuator_getFirmwareVersion(void), FUNCTION TO COMPLETE
 *  ! NOT IMPLEMENTED
 * \param ! NOT IMPLEMENTED
 * \return ! NOT IMPLEMENTED
 */  

int actuator_getFirmwareVersion(void){
    /*
    ptrDev = getEFM8BBconfig_ptr(kehops.battery[0].config.ain_id);
    voltage_mv = EFM8BB_getChannel(&dev_efm8bb[ptrDev]);
     */
}

/**
 * \brief int actuator_getBoardId(void), FUNCTION TO COMPLETE
 *  ! NOT IMPLEMENTED
 * \param ! NOT IMPLEMENTED
 * \return ! NOT IMPLEMENTED
 */  

int actuator_getBoardId(void){
    int ptrDev;  
/*    
    ptrDev = getEFM8BBconfig_ptr(kehops.battery[0].config.ain_id);
    EFM8BB_getBoardType();
*/
}

/**
 * \brief actuator_clearWheel(unsigned char Id), FUNCTION TO COMPLETE
 *  ! NOT IMPLEMENTED
 * \param ! NOT IMPLEMENTED
 * \return ! NOT IMPLEMENTED
 */  

void actuator_clearWheel(unsigned char Id){
    int ptrDev;  
    //ptrDev = getEFM8BBconfig_ptr(kehops.dcWheel[Id].config.encoder.pulseCounter_id);
    //EFM8BB_clearWheelDistance(&dev_efm8bb[ptrDev], Id);
}


/**
 * \brief int getPCA9685config_ptr(char * name), Search in the device table
 * list of PCA9685 PWM driver the configuration structure correspondant to the
 * device name (Like IC3) and return a pointer of this structure.
 * \param char * name , name of the device (like IC3, U5, etc...)
 * \return pointer of the correspondant configuration stucture
 */  

int getPCA9685config_ptr(char * name){
    int i, refFound=-1;
    
    for(i=0; refFound<0 && i<pca9685_count ;i++){
        if(!strcmp(dev_pca9685[i].deviceName, name)){
            refFound = i;
        }
    }       
    return refFound;
}

/**
 * \brief int getPCA9629config_ptr(char * name), Search in the device table
 * list of PCA9629 STEPPER MOTOR DRIVER the configuration structure correspondant
 * to the device name (Like IC3) and return a pointer of this structure.
 * \param char * name , name of the device (like IC3, U5, etc...)
 * \return pointer of the correspondant configuration stucture
 */   
int getPCA9629config_ptr(char * name){
    int i, refFound=-1;
    
    for(i=0; refFound<0 && i<pca9629_count ;i++){
        if(!strcmp(dev_pca9629[i].deviceName, name)){
            refFound = i;
        }
    }       
    return refFound;
}

/**
 * \brief int getEFM8BBconfig_ptr(char * name), Search in the device table
 * list of EFM8BB microcontroller the configuration structure correspondant
 * to the device name (Like IC3) and return a pointer of this structure.
 * \param char * name , name of the device (like IC3, U5, etc...)
 * \return pointer of the correspondant configuration stucture
 */ 
int getEFM8BBconfig_ptr(char * name){
    int i, refFound=-1;
    
    for(i=0; refFound<0 && i<efm8bb_count ;i++){
        if(!strcmp(dev_efm8bb[i].deviceName, name)){
            refFound = i;
        }
    }       
    return refFound;
}

/**
 * \brief int getMCP23008config_ptr(char * name), Search in the device table
 * list of MCP23008 GPIO Extender the configuration structure correspondant
 * to the device name (Like IC3) and return a pointer of this structure.
 * \param char * name , name of the device (like IC3, U5, etc...)
 * \return pointer of the correspondant configuration stucture
 */ 
int getMCP23008config_ptr(char * name){
    int i, refFound=-1;
    
    for(i=0; refFound<0 && i<mcp23008_count ;i++){
        if(!strcmp(dev_mcp23008[i].deviceName, name)){
            refFound = i;
        }
    }       
    return refFound;
}

/**
 * \brief int getMCP23008config_ptr(char * name), Search in the device table
 * list of MCP23008 GPIO Extender the configuration structure correspondant
 * to the device name (Like IC3) and return a pointer of this structure.
 * \param char * name , name of the device (like IC3, U5, etc...)
 * \return pointer of the correspondant configuration stucture
 */ 
int getBH1745config_ptr(char * name){
    int i, refFound=-1;
    
    for(i=0; refFound<0 && i<bh1745_count ;i++){
        if(!strcmp(dev_bh1745[i].deviceName, name)){
            refFound = i;
        }
    }       
    return refFound;
}