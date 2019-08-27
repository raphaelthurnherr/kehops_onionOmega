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
//#define INFO_BUS_DEBUG

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "hardwareDrivers.h"
#include "../configManager.h"
#include "../config/deviceMapping.h"
#include "../kehops_main.h"

// Device drivers libraries declaration
#include "pca9685.h"
#include "pca9629.h"
#include "efm8_mcu_kehops.h"
#include "mcp230xx.h"
#include "bh1745.h"
#include "k_vl53l0x.h"
#include "mcp4725.h"
#include "tca9548a.h"
#include "display_mono.h"
#include "ads101x.h"
#include "ads111x.h"

#include "gfx_xbm_pics.h"

// Device variable déclaration
#define MAX_IC_DEVICE_PER_TYPE 8


device_pca9685 dev_pca9685[MAX_IC_DEVICE_PER_TYPE];
device_pca9629 dev_pca9629[MAX_IC_DEVICE_PER_TYPE];
device_efm8McuKehops dev_efm8bb[MAX_IC_DEVICE_PER_TYPE];
device_mcp230xx dev_mcp230xx[MAX_IC_DEVICE_PER_TYPE];
device_bh1745 dev_bh1745[MAX_IC_DEVICE_PER_TYPE];
device_vl53l0x dev_vl53l0x[MAX_IC_DEVICE_PER_TYPE];
device_mcp4725 dev_mcp4725[MAX_IC_DEVICE_PER_TYPE];
device_tca9548a dev_tca9548a[MAX_IC_DEVICE_PER_TYPE];

device_display dev_U8G2_display[MAX_IC_DEVICE_PER_TYPE];

device_ads101x dev_ads101x[MAX_IC_DEVICE_PER_TYPE];
device_ads111x dev_ads111x[MAX_IC_DEVICE_PER_TYPE];


unsigned char pca9685_count=0;
unsigned char pca9629_count=0;
unsigned char efm8bb_count=0;
unsigned char mcp230xx_count=0;
unsigned char bh1745_count=0;
unsigned char vl53l0x_count=0;
unsigned char mcp4725_count=0;
unsigned char tca9548a_count=0;
unsigned char ads101x_count=0;
unsigned char ads111x_count=0;
unsigned char display_U8G2_count=0;

int getDriverConfig_ptr(char * driverType, char * name);
int driverSelector_SetDOUT(char * driverType, char * driverName, int channel, int value);
int setDeviceChannelByName(char * deviceName, int channel, int value);
struct device_subdrivers getSubdriverSettingsByName(char * driverName);

int subDriver_onActivate(char * driverName);
int subDriver_onDeactivate(char * driverName);

/**
 * \fn char boardHWinit()
 * \brief Initialize the devices IC of the board and the 
 *
 * \param filename to open
 * \return -
 */

int boardHWinit(void){
    int err = 0;
    int warning = 0;
    int status = 0;
    int NoDriverFound=1;    
    int i;

    printf("#[HW DRIVER] Board devices drivers initialization: \n");
    
    usleep(10000);
    
    for(i=0; boardDevice[i].address >= 0 && i<MAX_BOARD_DEVICE; i++){
            
        NoDriverFound = 1;                          
        printf("\n              [%s - %s] :",boardDevice[i].name, boardDevice[i].type);
            
            
        // SUB-DRIVER PRE ACTION Find if sub-driver action is necessary and defined before working

        if(strcmp(boardDevice[i].sub_driver.name, "")){
            status = subDriver_onActivate(boardDevice[i].name);

            if(status != 0){
                printf(" (SUBDRIVER -> ERROR [%d])", status);
                warning++;
            }
            else
                printf(" (SUBDRIVER -> OK)");
        }
            
        // DEVICES TYPE PCA9585 PWM DRIVER CONFIGURATION
            
            if(!strcmp(boardDevice[i].type, DRIVER_PCA9685)){              
                // Setting up the pca9685 device
                strcpy(dev_pca9685[pca9685_count].deviceName, boardDevice[i].name);
                if(boardDevice[i].attributes.frequency <= 0)
                    dev_pca9685[pca9685_count].frequency =200;
                else
                    dev_pca9685[pca9685_count].frequency = boardDevice[i].attributes.frequency;     
                dev_pca9685[pca9685_count].totemPoleOutput=1;                 
                dev_pca9685[pca9685_count].deviceAddress = boardDevice[i].address;                
                if(pca9685_init(&dev_pca9685[pca9685_count]) != 0){
                    err++;
                    printf(" -> ERROR");
                    dev_pca9685[pca9685_count].deviceAddress = 0; // Set address to unvalid
                }else
                    printf(" -> OK");   
                
            #ifdef INFO_DEBUG
                    printDeviceData(i, &boardDevice[i]);
            #endif
                pca9685_count++;
                NoDriverFound=0;
            }
            
        // DEVICES TYPE PCA9529 STEPPER MOTOR DRIVER CONFIGURATION
            if(!strcmp(boardDevice[i].type, DRIVER_PCA9629)){              
                // Setting up the pca9629 device               
                strcpy(dev_pca9629[pca9629_count].deviceName, boardDevice[i].name);
                dev_pca9629[pca9629_count].deviceAddress = boardDevice[i].address;
                if(pca9629_init(&dev_pca9629[pca9629_count]) != 0){
                    err++;
                    printf(" -> ERROR");
                    dev_pca9629[pca9629_count].deviceAddress = 0; // Set address to unvalid
                }else
                    printf(" -> OK");                
            #ifdef INFO_DEBUG
                printDeviceData(i, &boardDevice[i]);
            #endif                
                pca9629_count++;
                NoDriverFound=0;
            }
            
            // DEVICES TYPE EFM8 MICROCONTROLER KEHOPS FIRMWARE CONFIGURATION
            if(!strcmp(boardDevice[i].type, DRIVER_EFM8BB)){              
                // Setting up the efm8bb MCU device               
                strcpy(dev_efm8bb[efm8bb_count].deviceName, boardDevice[i].name);
                dev_efm8bb[efm8bb_count].deviceAddress = boardDevice[i].address;
                if(EFM8BB_init(&dev_efm8bb[efm8bb_count]) != 0){
                    err++;
                    printf(" -> ERROR");
                    dev_efm8bb[efm8bb_count].deviceAddress = 0; // Set address to unvalid
                }else
                    printf(" -> OK");                  
            #ifdef INFO_DEBUG                
                printDeviceData(i, &boardDevice[i]);
            #endif                
                efm8bb_count++;
                NoDriverFound=0;                
            }
            
            // DEVICES TYPE MCP23008 GPIO EXTENDER CONFIGURATION
            if(!strcmp(boardDevice[i].type, DRIVER_MCP23008)){              
                // Setting up the mcp23008GPIO extender              
                strcpy(dev_mcp230xx[mcp230xx_count].deviceName, boardDevice[i].name);
                dev_mcp230xx[mcp230xx_count].deviceAddress = boardDevice[i].address;
                dev_mcp230xx[mcp230xx_count].pullupEnable  = 0xff;                   // NEED TO BE DEFINE VIA CONFIG DEVICE.CFG
                dev_mcp230xx[mcp230xx_count].gpioDirection = 0x60;                   // NEED TO BE DEFINE VIA CONFIG DEVICE.CFG
                if(mcp23008_init(&dev_mcp230xx[mcp230xx_count]) != 0){
                    err++;
                    printf(" -> ERROR");
                    dev_mcp230xx[mcp230xx_count].deviceAddress = 0; // Set address to unvalid
                }else
                    printf(" -> OK");                  
            #ifdef INFO_DEBUG                
                printDeviceData(i, &boardDevice[i]);
            #endif                
                mcp230xx_count++;
                NoDriverFound=0;                
            }
        
            // DEVICES TYPE MCP23017 GPIO EXTENDER CONFIGURATION
            if(!strcmp(boardDevice[i].type, DRIVER_MCP23017)){              
                // Setting up the mcp23017 GPIO extender              
                strcpy(dev_mcp230xx[mcp230xx_count].deviceName, boardDevice[i].name);
                dev_mcp230xx[mcp230xx_count].deviceAddress = boardDevice[i].address;
                dev_mcp230xx[mcp230xx_count].pullupEnable  = 0xff;                   // NEED TO BE DEFINE VIA CONFIG DEVICE.CFG
                dev_mcp230xx[mcp230xx_count].gpioDirection = 0x00;                   // NEED TO BE DEFINE VIA CONFIG DEVICE.CFG
                if(mcp23008_init(&dev_mcp230xx[mcp230xx_count]) != 0){
                    err++;
                    printf(" -> ERROR");
                    dev_mcp230xx[mcp230xx_count].deviceAddress = 0; // Set address to unvalid
                }else
                    printf(" -> OK");                  
            #ifdef INFO_DEBUG                
                printDeviceData(i, &boardDevice[i]);
            #endif                
                mcp230xx_count++;
                NoDriverFound=0;                
            }         
            
            // DEVICES TYPE BH1745 RGB SENSOR CONFIGURATION
            if(!strcmp(boardDevice[i].type, DRIVER_BH1745)){              
                // Setting up the bh1745 rgb sensor
                strcpy(dev_bh1745[bh1745_count].deviceName, boardDevice[i].name);
                dev_bh1745[bh1745_count].deviceAddress = boardDevice[i].address;
                if(bh1745nuc_init(&dev_bh1745[bh1745_count]) != 0){
                    err++;
                    printf(" -> ERROR");
                    dev_bh1745[bh1745_count].deviceAddress = 0; // Set address to unvalid
                }else
                    printf(" -> OK");                 
                
            #ifdef INFO_DEBUG                
                printDeviceData(i, &boardDevice[i]);
            #endif                
                bh1745_count++;
                NoDriverFound=0;                
            }
            
            // DEVICES TYPE VL53l0x TOF DISTANCE SENSOR
            if(!strcmp(boardDevice[i].type, DRIVER_VL53L0X)){              
                // Setting up the vl53l0x TOF distance sensor
                strcpy(dev_vl53l0x[vl53l0x_count].deviceName, boardDevice[i].name);
                dev_vl53l0x[vl53l0x_count].deviceAddress = boardDevice[i].address;
                if(vl53l0x_init(&dev_vl53l0x[vl53l0x_count]) != 0){
                    err++;
                    printf(" -> NOT YET IMPLEMENTED");
                    dev_vl53l0x[vl53l0x_count].deviceAddress = 0; // Set address to unvalid                    
                }else
                    printf(" -> OK");                 
                
            #ifdef INFO_DEBUG                
                printDeviceData(i, &boardDevice[i]);
            #endif                
                vl53l0x_count++;
                NoDriverFound=0;                
            }
            
            // DEVICES TYPE MCP4725 DIGITAL ANALOG CONVERTER CONFIGURATION
            if(!strcmp(boardDevice[i].type, DRIVER_MCP4725)){              
                // Setting up the mcp4725 Digital analog converter             
                strcpy(dev_mcp4725[mcp4725_count].deviceName, boardDevice[i].name);
                dev_mcp4725[mcp4725_count].deviceAddress = boardDevice[i].address;
                dev_mcp4725[mcp4725_count].vref_mv = 3300;
                
                if(mcp4725_init(&dev_mcp4725[mcp4725_count]) != 0){
                    err++;
                    printf(" -> ERROR");
                    dev_mcp4725[mcp4725_count].deviceAddress = 0;
                }else{
                    printf(" -> OK");                  
                }
            #ifdef INFO_DEBUG                
                printDeviceData(i, &boardDevice[i]);
            #endif                
                mcp4725_count++;
                NoDriverFound=0;                
            }
            
            // DEVICES TYPE TCA9548A 8 CHANNELS I2C  SWITCH
            if(!strcmp(boardDevice[i].type, DRIVER_TCA9548A)){              
                // Setting up the tca9548a I2C switch
                strcpy(dev_tca9548a[tca9548a_count].deviceName, boardDevice[i].name);
                dev_tca9548a[tca9548a_count].deviceAddress = boardDevice[i].address;
                
                if(tca9548a_init(&dev_tca9548a[tca9548a_count]) != 0){
                    err++;
                    printf(" -> ERROR");
                    dev_tca9548a[tca9548a_count].deviceAddress = 0; // Set address to unvalid
                }else{
                    printf(" -> OK");                  
                }
            #ifdef INFO_DEBUG                
                printDeviceData(i, &boardDevice[i]);
            #endif                
                tca9548a_count++;
                NoDriverFound=0;                
            }
            
            // DEVICES TYPE DRIVER_SSD1306 GRAPHICAL DISPLAY
            if(!strcmp(boardDevice[i].type, DRIVER_SSD1306)){              
                // Setting up the ssd1306 Graphic display
                strcpy(dev_U8G2_display[display_U8G2_count].deviceName, boardDevice[i].name);
                dev_U8G2_display[display_U8G2_count].deviceAddress = boardDevice[i].address;
                dev_U8G2_display[display_U8G2_count].controllerType = CTRL_SSD1306;
                dev_U8G2_display[display_U8G2_count].width = boardDevice[i].attributes.width;
                dev_U8G2_display[display_U8G2_count].height = boardDevice[i].attributes.height;
                if(display_init(&dev_U8G2_display[display_U8G2_count]) != 0){
                    err++;
                    printf(" -> ERROR");
                    dev_U8G2_display[display_U8G2_count].deviceAddress = 0; // Set address to unvalid
                }else{
                    printf(" -> OK");                  
                }
            #ifdef INFO_DEBUG                
                printDeviceData(i, &boardDevice[i]);
            #endif                
                display_U8G2_count++;
                NoDriverFound=0;                
            }
        
            // DEVICES TYPE DRIVER_SSD1305 GRAPHICAL DISPLAY
            if(!strcmp(boardDevice[i].type, DRIVER_SSD1305)){              
                // Setting up the ssd1305 Graphic display
                strcpy(dev_U8G2_display[display_U8G2_count].deviceName, boardDevice[i].name);
                dev_U8G2_display[display_U8G2_count].deviceAddress = boardDevice[i].address;
                dev_U8G2_display[display_U8G2_count].controllerType = CTRL_SSD1305;
                dev_U8G2_display[display_U8G2_count].width = boardDevice[i].attributes.width;
                dev_U8G2_display[display_U8G2_count].height = boardDevice[i].attributes.height;
                if(display_init(&dev_U8G2_display[display_U8G2_count]) != 0){
                    err++;
                    printf(" -> ERROR");
                    dev_U8G2_display[display_U8G2_count].deviceAddress = 0; // Set address to unvalid
                }else{
                    printf(" -> OK");                  
                }
            #ifdef INFO_DEBUG                
                printDeviceData(i, &boardDevice[i]);
            #endif                
                display_U8G2_count++;
                NoDriverFound=0;                
            }        
        
            // DEVICES TYPE DRIVER_SH1106 GRAPHICAL DISPLAY
            if(!strcmp(boardDevice[i].type, DRIVER_SH1106)){
                strcpy(dev_U8G2_display[display_U8G2_count].deviceName, boardDevice[i].name);
                dev_U8G2_display[display_U8G2_count].deviceAddress = boardDevice[i].address;
                dev_U8G2_display[display_U8G2_count].controllerType = CTRL_SH1106;
                dev_U8G2_display[display_U8G2_count].width = boardDevice[i].attributes.width;
                dev_U8G2_display[display_U8G2_count].height = boardDevice[i].attributes.height;
                if(display_init(&dev_U8G2_display[display_U8G2_count]) != 0){
                    err++;
                    printf(" -> ERROR");
                    dev_U8G2_display[display_U8G2_count].deviceAddress = 0; // Set address to unvalid
                }else{
                    printf(" -> OK");                  
                }
            #ifdef INFO_DEBUG                
                printDeviceData(i, &boardDevice[i]);
            #endif                
                display_U8G2_count++;
                NoDriverFound=0;                
            }
        
            
            // DEVICES TYPE DRIVER_ADS101X 12 BIT ANALOG DIGITAL CONVERTER
            if(!strcmp(boardDevice[i].type, DRIVER_ADS101X)){              
                // Setting up the ads101x AD Converter
                strcpy(dev_ads101x[ads101x_count].deviceName, boardDevice[i].name);
                dev_ads101x[ads101x_count].deviceAddress = boardDevice[i].address;
                if(ads101x_init(&dev_ads101x[ads101x_count]) != 0){
                    err++;
                    printf(" -> ERROR");
                    dev_ads101x[ads101x_count].deviceAddress = 0; // Set address to unvalid                    
                }else{
                    printf(" -> OK");                  
                }
            #ifdef INFO_DEBUG                
                printDeviceData(i, &boardDevice[i]);
            #endif                
                ads101x_count++;
                NoDriverFound=0;                
            }

            // DEVICES TYPE DRIVER_ADS111X 16 BIT ANALOG DIGITAL CONVERTER
            if(!strcmp(boardDevice[i].type, DRIVER_ADS111X)){              
                // Setting up the ads111x AD Converter
                strcpy(dev_ads111x[ads111x_count].deviceName, boardDevice[i].name);
                dev_ads111x[ads111x_count].deviceAddress = boardDevice[i].address;
                if(ads111x_init(&dev_ads111x[ads111x_count]) != 0){
                    err++;
                    printf(" -> ERROR");
                    dev_ads111x[ads111x_count].deviceAddress = 0; // Set address to unvalid                    
                }else{
                    printf(" -> OK");                  
                }
            #ifdef INFO_DEBUG                
                printDeviceData(i, &boardDevice[i]);
            #endif                
                ads111x_count++;
                NoDriverFound=0;                
            }        
            
            // - END OF DRIVER INITIALIZATION -
            
            // Check if driver was found for this part
            if(NoDriverFound > 0){
                warning++;    
            }
            
            // SUB-DRIVER POST ACTION Find if sub-driver action was necessary and finish action            
            subDriver_onDeactivate(boardDevice[i].name);
 
    }
     printf("\n");
     
     if(warning && !err)
         return -1;
         
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
    
    // SUBDRIVER ACTION Check if driver IC need a subdriver and make a pre-action if required
    subDriver_onActivate(kehopsActuators.dout[doutID].hw_driver.name);
    
    // USE DRIVER FOR PCA9685
    if(!strcmp(kehopsActuators.dout[doutID].hw_driver.type, DRIVER_PCA9685)){
        ptrDev = getDriverConfig_ptr(DRIVER_PCA9685, kehopsActuators.dout[doutID].hw_driver.name);
        if(ptrDev>=0){
    #ifdef INFO_DEBUG
            printf("SET DOUT VALUE FROM <%s> DRIVERS:  NAME:%s TYPE:%s I2C add: 0x%2x    dout_id: %d     channel: %d     ratio: %d\n",DRIVER_PCA9685, kehopsActuators.dout[doutID].hw_driver.name, kehopsActuators.dout[doutID].hw_driver.type, dev_pca9685[ptrDev].deviceAddress, doutID, channel, value);        
    #endif
            if(dev_pca9685[ptrDev].deviceAddress > 0)
                pca9685_setPWMdutyCycle(&dev_pca9685[ptrDev], channel, value);
            else
                {
                #ifdef INFO_BUS_DEBUG
                    printf("#! Function [actuator_setDoutValue] -> I2C Error: Bad address or device not connected\n");
                #endif      
            }
        }else 
            printf ("#! Function [actuator_setDoutValue] -> Unknown driver name: %s\n", kehopsActuators.dout[doutID].hw_driver.name);
    }
    
    // USE DRIVER FOR MCP23008
    if(!strcmp(kehopsActuators.dout[doutID].hw_driver.type, DRIVER_MCP23008)){
        ptrDev = getDriverConfig_ptr(DRIVER_MCP23008, kehopsActuators.dout[doutID].hw_driver.name);
        if(ptrDev>=0){
    #ifdef INFO_DEBUG            
            printf("SET DOUT VALUE FROM <%s> DRIVERS:  NAME:%s TYPE:%s I2C add: 0x%2x    dout_id: %d     channel: %d     state: %d\n",DRIVER_MCP230XX, kehopsActuators.dout[doutID].hw_driver.name, kehopsActuators.dout[doutID].hw_driver.type, dev_mcp230xx[ptrDev].deviceAddress, doutID, channel, value);        
    #endif            
            if(dev_mcp230xx[ptrDev].deviceAddress > 0)
                mcp230xx_setChannel(&dev_mcp230xx[ptrDev], channel, value);
            else
                {
                #ifdef INFO_BUS_DEBUG
                printf("#! Function [actuator_setDoutValue] -> I2C Error: Bad address or device not connected\n");
                #endif
        }
            
        }else 
            printf ("#! Function [actuator_setDoutValue] -> Unknown driver name: %s\n", kehopsActuators.dout[doutID].hw_driver.name);
    }
    
    // USE DRIVER FOR MCP23017
    if(!strcmp(kehopsActuators.dout[doutID].hw_driver.type, DRIVER_MCP23017)){
        ptrDev = getDriverConfig_ptr(DRIVER_MCP23008, kehopsActuators.dout[doutID].hw_driver.name);
        if(ptrDev>=0){
    #ifdef INFO_DEBUG            
            printf("SET DOUT VALUE FROM <%s> DRIVERS:  NAME:%s TYPE:%s I2C add: 0x%2x    dout_id: %d     channel: %d     state: %d\n",DRIVER_MCP230XX, kehopsActuators.dout[doutID].hw_driver.name, kehopsActuators.dout[doutID].hw_driver.type, dev_mcp230xx[ptrDev].deviceAddress, doutID, channel, value);        
    #endif            
            if(dev_mcp230xx[ptrDev].deviceAddress > 0)
                mcp230xx_setChannel(&dev_mcp230xx[ptrDev], channel, value);
            else
                {
                #ifdef INFO_BUS_DEBUG
                printf("#! Function [actuator_setDoutValue] -> I2C Error: Bad address or device not connected\n");
                #endif
        }
            
        }else 
            printf ("#! Function [actuator_setDoutValue] -> Unknown driver name: %s\n", kehopsActuators.dout[doutID].hw_driver.name);
    }    
    
    // SUBDRIVER ACTION Check if driver IC need a subdriver and make a post-action if required
    subDriver_onDeactivate(kehopsActuators.dout[doutID].hw_driver.name);
    
}

/**
 * \fn char actuator_setAnalogValue()
 * \brief Get the Analog hardware id of the output from config and apply the
 *  PWM settings if available, else boolean value is apply
 * \param pwmID, power
 * \return -
 */

char actuator_setAnalogValue(int aoutID, int value){
    int channel = kehopsActuators.aout[aoutID].hw_driver.attributes.device_channel;
    int ptrDev; 
        
    // SUBDRIVER ACTION Check if driver IC need a subdriver and make a pre-action if required
    subDriver_onActivate(kehopsActuators.aout[aoutID].hw_driver.name);
    
    // USE DRIVER FOR MCP4725
    if(!strcmp(kehopsActuators.aout[aoutID].hw_driver.type, DRIVER_MCP4725)){
        ptrDev = getDriverConfig_ptr(DRIVER_MCP4725, kehopsActuators.aout[aoutID].hw_driver.name);
        if(ptrDev>=0){
    #ifdef INFO_DEBUG
            printf("SET ANALOG VALUE FROM <%s> DRIVERS:  NAME:%s TYPE:%s I2C add: 0x%2x    aout_id: %d     channel: %d     value: %d\n",DRIVER_MCP4725, kehopsActuators.aout[aoutID].hw_driver.name, kehopsActuators.aout[aoutID].hw_driver.type, dev_mcp4725[ptrDev].deviceAddress, aoutID, channel, value);        
    #endif
            if(dev_mcp4725[ptrDev].deviceAddress > 0)
                mcp4725_setDACOutput_mV(&dev_mcp4725[ptrDev], value);
            else
                {
                #ifdef INFO_BUS_DEBUG                
                printf("#! Function [actuator_setAnalogValue] -> I2C Error: Bad address or device not connected\n");
                #endif
            }
            
        }else 
            printf ("#! Function [actuator_setAnalogValue] -> Unknown driver name: %s\n", kehopsActuators.aout[aoutID].hw_driver.name);
    }
    
    // SUBDRIVER ACTION Check if driver IC need a subdriver and make a post-action if required
    subDriver_onDeactivate(kehopsActuators.aout[aoutID].hw_driver.name);    
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
        
    // SUBDRIVER ACTION Check if driver IC need a subdriver and make a pre-action if required
    subDriver_onActivate(kehopsActuators.dout[doutID].hw_driver.name);
    
    // USE DRIVER FOR PCA9685
    if(!strcmp(kehopsActuators.dout[doutID].hw_driver.type, DRIVER_PCA9685)){
        ptrDev = getDriverConfig_ptr(DRIVER_PCA9685, kehopsActuators.dout[doutID].hw_driver.name);
        if(ptrDev>=0){
    #ifdef INFO_DEBUG            
            printf("SET SERVO POSITION FROM NEW DRIVERS: NAME: %s TYPE:%s  I2Cadd: 0x%2x    dout_id: %d     channel: %d     position: %d     time: %.2f\n",kehopsActuators.dout[doutID].hw_driver.name,kehopsActuators.dout[doutID].hw_driver.type, dev_pca9685[ptrDev].deviceAddress, doutID, channel, position, time_ms);
    #endif
            if(dev_pca9685[ptrDev].deviceAddress > 0)
                pca9685_setPulseWidthTime(&dev_pca9685[ptrDev], channel, time_ms);
            else
                {
                #ifdef INFO_BUS_DEBUG
                printf("#! Function [actuator_setServoPosition] -> I2C Error: Bad address or device not connected\n");
                #endif
            }                
            
        }else printf ("#! Function [actuator_setServoPosition] -> Unknown driver name: %s\n", kehopsActuators.dout[doutID].hw_driver.name);
    }
    
    // SUBDRIVER ACTION Check if driver IC need a subdriver and make a post-action if required
    subDriver_onDeactivate(kehopsActuators.dout[doutID].hw_driver.name);
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
     
    // SUBDRIVER ACTION Check if driver IC need a subdriver and make a pre-action if required
    subDriver_onActivate(kehopsActuators.stepper_motors[stepperID].hw_driver.name);
    
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

        ptrDev = getDriverConfig_ptr(DRIVER_PCA9629, kehopsActuators.stepper_motors[stepperID].hw_driver.name);
        
        if(ptrDev>=0){
    #ifdef INFO_DEBUG
            printf("SET STEPPER STEP ACTION FROM NEW DRIVERS: NAME: %s TYPE:%s  I2Cadd: 0x%2x    stepper_id: %d     STEPS: %d \n", kehopsActuators.stepper_motors[stepperID].hw_driver.name,kehopsActuators.stepper_motors[stepperID].hw_driver.type,  dev_pca9685[ptrDev].deviceAddress, stepperID, stepCount);    
    #endif
            if(dev_pca9629[ptrDev].deviceAddress > 0){
                // Reset le registre de contronle
                // (Indispensable pour une nouvelle action après une action infinie)
                PCA9629_StepperMotorControl(&dev_pca9629[ptrDev], 0x00);

                // Assignation du mode action continu ou unique
                PCA9629_StepperMotorMode(&dev_pca9629[ptrDev], PMAmode);
                PCA9629_StepperMotorSetStep(&dev_pca9629[ptrDev], stepCount);
                PCA9629_StepperMotorControl(&dev_pca9629[ptrDev], ctrlData);
            }
            else
                {
                #ifdef INFO_BUS_DEBUG                
                printf("#! Function [actuator_setStepperStepAction] -> I2C Error: Bad address or device not connected\n");
                #endif 
            }                
            

        }else printf ("#! Function [actuator_setStepperStepAction] -> Unknown driver name: %s\n", kehopsActuators.stepper_motors[stepperID].hw_driver.name);
 }
    
    // SUBDRIVER ACTION Check if driver IC need a subdriver and make a post-action if required
    subDriver_onDeactivate(kehopsActuators.stepper_motors[stepperID].hw_driver.name);    
    
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
        
    // SUBDRIVER ACTION Check if driver IC need a subdriver and make a pre-action if required
    subDriver_onActivate(kehopsActuators.stepper_motors[stepperID].hw_driver.name);
    
    // USE DRIVER FOR PCA9629
     if(!strcmp(kehopsActuators.stepper_motors[stepperID].hw_driver.type, DRIVER_PCA9629)){    
        int regData;
        int ptrDev;

        // Periode minimum (2mS) + vitesse en % (max 22.5mS)
        regData = 0x029A + ((100-speed) * 75);

        ptrDev = getDriverConfig_ptr(DRIVER_PCA9629, kehopsActuators.stepper_motors[stepperID].hw_driver.name);
        if(ptrDev>=0){
#ifdef INFO_DEBUG
            printf("SET STEPPER STEP SPEED FROM NEW DRIVERS: NAME: %s TYPE:%s  I2Cadd: 0x%2x    stepper_id: %d     SPEED: %d \n", kehopsActuators.stepper_motors[stepperID].hw_driver.name,kehopsActuators.stepper_motors[stepperID].hw_driver.type, dev_pca9685[ptrDev].deviceAddress, stepperID, speed);    
#endif            
            if(dev_pca9629[ptrDev].deviceAddress > 0)
            PCA9629_StepperMotorPulseWidth(&dev_pca9629[ptrDev], regData);
            else
                {
                #ifdef INFO_BUS_DEBUG                
                printf("#! Function [actuator_setStepperSpeed] -> I2C Error: Bad address or device not connected\n");
                #endif 
            }                
            
        }else printf ("#! Function [actuator_setStepperSpeed] -> Unknown driver name: %s\n", kehopsActuators.stepper_motors[stepperID].hw_driver.name);
     }

    // SUBDRIVER ACTION Check if driver IC need a subdriver and make a post-action if required
    subDriver_onDeactivate(kehopsActuators.stepper_motors[stepperID].hw_driver.name);
    
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
    int state=-1;    
    
    // SUBDRIVER ACTION Check if driver IC need a subdriver and make a pre-action if required
    subDriver_onActivate(kehopsActuators.stepper_motors[stepperID].hw_driver.name);
    
     // USE DRIVER FOR PCA9629
     if(!strcmp(kehopsActuators.stepper_motors[stepperID].hw_driver.type, DRIVER_PCA9629)){    
        int ptrDev = getDriverConfig_ptr(DRIVER_PCA9629, kehopsActuators.stepper_motors[stepperID].hw_driver.name);
        
        if(ptrDev>=0){
            if(dev_pca9629[ptrDev].deviceAddress > 0)
                state = PCA9629_ReadMotorState(&dev_pca9629[ptrDev]);
            else
                {
                #ifdef INFO_BUS_DEBUG                
                printf("#! Function [actuator_getStepperState] -> I2C Error: Bad address or device not connected\n");
                #endif 
            }                
        }else{
            printf ("#! Function [actuator_getStepperState] -> Unknown driver name: %s\n", kehopsActuators.stepper_motors[stepperID].hw_driver.name);
            state = 0;
        }
     }
    
    // SUBDRIVER ACTION Check if driver IC need a subdriver and make a post-action if required
    subDriver_onDeactivate(kehopsActuators.stepper_motors[stepperID].hw_driver.name);
    
    return state;
}

// ------------------------------------------------------------------------------------
//EFM8
// ------------------------------------------------------------------------------------
int actuator_getCounterPulses(unsigned char pulseCounterID){
    int counterPulses = -1;
    int ptrDev;
    
    // SUBDRIVER ACTION Check if driver IC need a subdriver and make a pre-action if required
    subDriver_onActivate(kehopsActuators.pulsesCounter[pulseCounterID].hw_driver.name);
    
    // USE DRIVER FOR EFM8BB
    if(!strcmp(kehopsActuators.pulsesCounter[pulseCounterID].hw_driver.type, DRIVER_EFM8BB)){
        ptrDev = getDriverConfig_ptr(DRIVER_EFM8BB, kehopsActuators.pulsesCounter[pulseCounterID].hw_driver.name);
        if(ptrDev>=0){
            //printf("GET COUNTER FROM NEW DRIVERS: NAME: %s   I2Cadd: 0x%2x    counter_id: %d\n", kehopsActuators.pulsesCounter[counter_id].hw_driver.name, dev_efm8bb[ptrDev].deviceAddress, counter_id);    
            if(dev_efm8bb[ptrDev].deviceAddress > 0)
                counterPulses = EFM8BB_getChannel(&dev_efm8bb[ptrDev], kehopsActuators.pulsesCounter[pulseCounterID].hw_driver.attributes.device_channel);
            else
                {
                #ifdef INFO_BUS_DEBUG                
                printf("#! Function [actuator_getCounterPulses] -> I2C Error: Bad address or device not connected\n");
                #endif 
            }                
        }else printf ("#! Function [actuator_getCounterPulses] -> Unknown driver name: %s\n", kehopsActuators.pulsesCounter[pulseCounterID].hw_driver.name);
    }
    
    // SUBDRIVER ACTION Check if driver IC need a subdriver and make a post-action if required
    subDriver_onDeactivate(kehopsActuators.pulsesCounter[pulseCounterID].hw_driver.name);
    
    return counterPulses;
}



int actuator_getCounterFrequency(unsigned char freqCounterID){
    int frequency = -1;
    int ptrDev;
    
    // SUBDRIVER ACTION Check if driver IC need a subdriver and make a pre-action if required
    subDriver_onActivate(kehopsActuators.freqCounter[freqCounterID].hw_driver.name);
    
    // USE DRIVER FOR EFM8BB
    if(!strcmp(kehopsActuators.freqCounter[freqCounterID].hw_driver.type, DRIVER_EFM8BB)){
        ptrDev = getDriverConfig_ptr(DRIVER_EFM8BB, kehopsActuators.freqCounter[freqCounterID].hw_driver.name);        
        if(ptrDev>=0){
            //printf("GET FREQ FROM NEW DRIVERS: NAME: %s   I2Cadd: 0x%2x    counter_id: %d\n", kehopsActuators.freqCounter[freq_id].hw_driver.name, dev_efm8bb[ptrDev].deviceAddress, freq_id);    
            if(dev_efm8bb[ptrDev].deviceAddress > 0)
                frequency = EFM8BB_getChannel(&dev_efm8bb[ptrDev], kehopsActuators.freqCounter[freqCounterID].hw_driver.attributes.device_channel);
            else
                {
                #ifdef INFO_BUS_DEBUG                
                printf("#! Function [actuator_getCounterFrequency] -> I2C Error: Bad address or device not connected\n");
                #endif 
            }        
        }else printf ("#! Function [actuator_getCounterFrequency] -> Unknown driver name: %s\n", kehopsActuators.freqCounter[freqCounterID].hw_driver.name);
    }
    
    // SUBDRIVER ACTION Check if driver IC need a subdriver and make a post-action if required
    subDriver_onDeactivate(kehopsActuators.freqCounter[freqCounterID].hw_driver.name);
    
    return frequency;
}

int actuator_getDigitalInput(unsigned char dinID){
    char value = -1;
    int ptrDev;    
        
    // SUBDRIVER ACTION Check if driver IC need a subdriver and make a pre-action if required
    subDriver_onActivate(kehopsActuators.din[dinID].hw_driver.name);
    
    // USE DRIVER FOR EFM8BB
    if(!strcmp(kehopsActuators.din[dinID].hw_driver.type, DRIVER_EFM8BB)){
        ptrDev = getDriverConfig_ptr(DRIVER_EFM8BB, kehopsActuators.din[dinID].hw_driver.name);                
        if(ptrDev>=0){
            if(dev_efm8bb[ptrDev].deviceAddress > 0)
                value = EFM8BB_getChannel(&dev_efm8bb[ptrDev], kehopsActuators.din[dinID].hw_driver.attributes.device_channel);
            else
                {
                #ifdef INFO_BUS_DEBUG                
                printf("#! Function [actuator_getDigitalInput] -> I2C Error: Bad address or device not connected\n");
                #endif             
            }                    
        }else{
                printf ("#! Function [actuator_getDigitalInput] -> Unknown driver name: %s\n", kehopsActuators.din[dinID].hw_driver.name);
                value = -1;
        }
        //printf ("#! NOW USING  DRIVER 'EFM8BB' for DIN #%d\n", dinID);
    }

    // USE DRIVER FOR MCP23008
    if(!strcmp(kehopsActuators.din[dinID].hw_driver.type, DRIVER_MCP23008)){
        ptrDev = getDriverConfig_ptr(DRIVER_MCP23008, kehopsActuators.din[dinID].hw_driver.name);                
        if(ptrDev>=0){
            if(dev_mcp230xx[ptrDev].deviceAddress > 0)
                value = mcp230xx_getChannel(&dev_mcp230xx[ptrDev], kehopsActuators.din[dinID].hw_driver.attributes.device_channel);
            else
                {
                #ifdef INFO_BUS_DEBUG                
                printf("#! Function [actuator_getDigitalInput] -> I2C Error: Bad address or device not connected\n");
                #endif             
            }              
        }else{
                printf ("#! Function [actuator_getDigitalInput] -> Unknown driver name: %s\n", kehopsActuators.din[dinID].hw_driver.name);
                value = -1;
        }
        //printf ("#! NOW USING  DRIVER 'MCP230xx' for DIN #%d\n", dinID);
    }
    
    // USE DRIVER FOR MCP23017
    if(!strcmp(kehopsActuators.din[dinID].hw_driver.type, DRIVER_MCP23017)){
        ptrDev = getDriverConfig_ptr(DRIVER_MCP23017, kehopsActuators.din[dinID].hw_driver.name);                
        if(ptrDev>=0){
            if(dev_mcp230xx[ptrDev].deviceAddress > 0)
                value = mcp230xx_getChannel(&dev_mcp230xx[ptrDev], kehopsActuators.din[dinID].hw_driver.attributes.device_channel);
            else
                {
                #ifdef INFO_BUS_DEBUG                
                printf("#! Function [actuator_getDigitalInput] -> I2C Error: Bad address or device not connected\n");
                #endif             
            }              
        }else{
                printf ("#! Function [actuator_getDigitalInput] -> Unknown driver name: %s\n", kehopsActuators.din[dinID].hw_driver.name);
                value = -1;
        }
        //printf ("#! NOW USING  DRIVER 'MCP230xx' for DIN #%d\n", dinID);
    }    
   
    // SUBDRIVER ACTION Check if driver IC need a subdriver and make a post-action if required
    subDriver_onDeactivate(kehopsActuators.din[dinID].hw_driver.name);
    
    return value;
}

int actuator_getDistance(unsigned char distanceSensorID){
    int distance_mm = -1;
    int ptrDev;    

    // SUBDRIVER ACTION Check if driver IC need a subdriver and make a pre-action if required
    subDriver_onActivate(kehopsActuators.distanceSensor[distanceSensorID].hw_driver.name);
    
    // USE DRIVER FOR EFM8BB
    if(!strcmp(kehopsActuators.distanceSensor[distanceSensorID].hw_driver.type, DRIVER_EFM8BB)){
        ptrDev = getDriverConfig_ptr(DRIVER_EFM8BB, kehopsActuators.distanceSensor[distanceSensorID].hw_driver.name);                        
        if(ptrDev>=0){
            if(dev_efm8bb[ptrDev].deviceAddress > 0)
                distance_mm = EFM8BB_getChannel(&dev_efm8bb[ptrDev], kehopsActuators.distanceSensor[distanceSensorID].hw_driver.attributes.device_channel);
            else
                {
                #ifdef INFO_BUS_DEBUG                
                printf("#! Function [actuator_getDistance] -> I2C Error: Bad address or device not connected\n");
                #endif             
            }               
        }else{
                printf ("#! Function [actuator_getDistance] -> Unknown driver name: %s\n", kehopsActuators.distanceSensor[distanceSensorID].hw_driver.name);
                distance_mm = -1;
        }
    }
    
    // SUBDRIVER ACTION Check if driver IC need a subdriver and make a pre-action if required
    subDriver_onDeactivate(kehopsActuators.distanceSensor[distanceSensorID].hw_driver.name);
    
    return distance_mm;
}

int actuator_getVoltage(unsigned char ainID){
    int voltage_mv = -1;
    int  ptrDev;    
    
    // Check if driver IC need a subdriver and make a pre-action if required
    subDriver_onActivate(kehopsActuators.ain[ainID].hw_driver.name);
              
    // USE DRIVER FOR EFM8BB
    if(!strcmp(kehopsActuators.ain[ainID].hw_driver.type, DRIVER_EFM8BB)){
        ptrDev = getDriverConfig_ptr(DRIVER_EFM8BB, kehopsActuators.ain[ainID].hw_driver.name);                        
        if(ptrDev>=0){
            if(dev_efm8bb[ptrDev].deviceAddress > 0)
                voltage_mv = EFM8BB_getChannel(&dev_efm8bb[ptrDev], kehopsActuators.ain[ainID].hw_driver.attributes.device_channel);
            else
                {
                #ifdef INFO_BUS_DEBUG                
                printf("#! Function [actuator_getVoltage] -> I2C Error: Bad address or device not connected\n");
                #endif             
            }                           

        }else{
                printf ("#! Function [actuator_getVoltage] -> Unknown driver name: %s\n", kehopsActuators.ain[ainID].hw_driver.name);
                voltage_mv = -1;
        }
    }
    
    // USE DRIVER FOR ADS101x ADC Converter
    if(!strcmp(kehopsActuators.ain[ainID].hw_driver.type, DRIVER_ADS101X)){
        ptrDev = getDriverConfig_ptr(DRIVER_ADS101X, kehopsActuators.ain[ainID].hw_driver.name);
        if(ptrDev>=0){
            if(dev_ads101x[ptrDev].deviceAddress > 0)
                voltage_mv = ads101x_getVoltage_mv(&dev_ads101x[ptrDev], kehopsActuators.ain[ainID].hw_driver.attributes.device_channel);
            else
                {
                #ifdef INFO_BUS_DEBUG                
                printf("#! Function [actuator_getVoltage] -> I2C Error: Bad address or device not connected\n");
                #endif             
            }                                       
        }else{
                printf ("#! Function [actuator_getVoltage] -> Unknown driver name: %s\n", kehopsActuators.ain[ainID].hw_driver.name);
                voltage_mv = -1;
        }
    }
    
    // USE DRIVER FOR ADS111x ADC Converter
    if(!strcmp(kehopsActuators.ain[ainID].hw_driver.type, DRIVER_ADS111X)){
        ptrDev = getDriverConfig_ptr(DRIVER_ADS111X, kehopsActuators.ain[ainID].hw_driver.name);
        if(ptrDev>=0){
            if(dev_ads111x[ptrDev].deviceAddress > 0)
                voltage_mv = ads111x_getVoltage_mv(&dev_ads111x[ptrDev], kehopsActuators.ain[ainID].hw_driver.attributes.device_channel);
            else
                {
                #ifdef INFO_BUS_DEBUG                
                printf("#! Function [actuator_getVoltage] -> I2C Error: Bad address or device not connected\n");
                #endif             
            }                                       
        }else{
                printf ("#! Function [actuator_getVoltage] -> Unknown driver name: %s\n", kehopsActuators.ain[ainID].hw_driver.name);
                voltage_mv = -1;
        }
    }    
    
    // Check if driver IC need a subdriver and make a post-action if required
    subDriver_onDeactivate(kehopsActuators.ain[ainID].hw_driver.name);
    
    return voltage_mv;
}

int actuator_getRGBColor(unsigned char rgbID, RGB_COLOR * rgbColor){
    int ptrDev;    
    
    ptrDev = getDriverConfig_ptr(DRIVER_BH1745, kehopsActuators.rgbSensor[rgbID].hw_driver.name);
    if(ptrDev>=0){
            if(dev_bh1745[ptrDev].deviceAddress > 0){
                rgbColor->red = bh1745nuc_getChannelRGBvalue(&dev_bh1745[ptrDev], RED);
                rgbColor->green = bh1745nuc_getChannelRGBvalue(&dev_bh1745[ptrDev], GREEN);
                rgbColor->blue = bh1745nuc_getChannelRGBvalue(&dev_bh1745[ptrDev], BLUE);
                rgbColor->clear = bh1745nuc_getChannelRGBvalue(&dev_bh1745[ptrDev], CLEAR);                
            }
            else
                {
                #ifdef INFO_BUS_DEBUG                
                printf("#! Function [actuator_getColor] -> I2C Error: Bad address or device not connected\n");
                #endif             
            }
#ifdef INFO_DEBUG
            printf("COLOR SENSOR #%d  Red: %d  Green: %d  Blue: %d  Clear: %d\n", ptrDev, rgbColor->red, rgbColor->green, rgbColor->blue, rgbColor->clear);
#endif
    }else{
            printf ("#! Function [actuator_getColor] -> Unknown driver name: %s\n", kehopsActuators.rgbSensor[rgbID].hw_driver.name);
    }
    
    if(rgbColor->red >= 0 && rgbColor->green >= 0 && rgbColor->blue >= 0 && rgbColor->clear >= 0)
        return 0;
    else
        return -1;
}

/**
 * \brief int actuator_setKehopsDisplay(unsigned char gfxID)
 * \param gfxID, ID of display in kehops.cfg
 * \return error code
 */ 

int actuator_setKehopsDisplay(unsigned char gfxID){
    int ptrDev=-1;
    char strTemp[25];
    char strVolt[10];
    char strDist[10];
   
    // Check if driver IC need a subdriver and make a pre-action if required
    subDriver_onActivate(kehopsActuators.gfxDisplay[gfxID].hw_driver.name);
    
    
    if(!strcmp(kehopsActuators.gfxDisplay[gfxID].hw_driver.type, DRIVER_SH1106) || !strcmp(kehopsActuators.gfxDisplay[gfxID].hw_driver.type, DRIVER_SSD1306)){
        usleep(50000);
        
        ptrDev = getDriverConfig_ptr(DRIVER_SH1106, kehopsActuators.gfxDisplay[gfxID].hw_driver.name);
        
        if(ptrDev>=0){
            if(dev_U8G2_display[ptrDev].deviceAddress > 0){
                if(dev_U8G2_display[ptrDev].width >= 128 && dev_U8G2_display[ptrDev].height >= 64){
                    
                    //display_clearScreen(&dev_display[ptrDev]);
                    // Build the screen
                    gcvt((float)kehops.analogInput[0].measure.voltage_mV/1000, 3, strTemp);
                    sprintf(strVolt, "%s V", strTemp);
                    sprintf(strDist, "%d [cm]", kehops.sonar[0].measure.distance_cm);

                    display_clearBuffer(&dev_U8G2_display[ptrDev]);
                    display_addXBM(&dev_U8G2_display[ptrDev], 0, 0, kehops_61x64_width, kehops_61x64_height, kehops_61x64_bits);

                    // Display the name in the logo
                    display_addText(&dev_U8G2_display[ptrDev],15,60, 0, sysApp.info.name);

                    // Display the sonar evaluation logo               
                    if(kehops.sonar[0].measure.distance_cm < 10)
                        display_addXBM(&dev_U8G2_display[ptrDev], 14, 0, kehops_us_33x17_0_width, kehops_us_33x17_0_height, kehops_us_33x17_0_bits);
                    if(kehops.sonar[0].measure.distance_cm >= 10 & kehops.sonar[0].measure.distance_cm < 20)
                        display_addXBM(&dev_U8G2_display[ptrDev], 14, 0, kehops_us_33x17_1_width, kehops_us_33x17_1_height, kehops_us_33x17_1_bits);                
                    if(kehops.sonar[0].measure.distance_cm >= 20 & kehops.sonar[0].measure.distance_cm <30)
                        display_addXBM(&dev_U8G2_display[ptrDev], 14, 0, kehops_us_33x17_2_width, kehops_us_33x17_2_height, kehops_us_33x17_2_bits);
                    if(kehops.sonar[0].measure.distance_cm >= 30)
                        display_addXBM(&dev_U8G2_display[ptrDev], 14, 0, kehops_us_33x17_3_width, kehops_us_33x17_3_height, kehops_us_33x17_3_bits);

                // PROXIMITY
                    // Display the left proximity sensor state
                    if(kehops.proximity[0].measure.state)
                        display_addXBM(&dev_U8G2_display[ptrDev], 2, 15, kehops_ir_l_10x7_1_width, kehops_ir_l_10x7_1_height, kehops_ir_l_10x7_1_bits);
                    else
                        display_addXBM(&dev_U8G2_display[ptrDev], 2, 15, kehops_ir_l_10x7_0_width, kehops_ir_l_10x7_0_height, kehops_ir_l_10x7_0_bits);                

                    // Display the right proximity sensor state               
                    if(kehops.proximity[1].measure.state)
                        display_addXBM(&dev_U8G2_display[ptrDev], 49, 15, kehops_ir_r_10x7_1_width, kehops_ir_r_10x7_1_height, kehops_ir_r_10x7_1_bits);
                    else
                        display_addXBM(&dev_U8G2_display[ptrDev], 49, 15, kehops_ir_r_10x7_0_width, kehops_ir_r_10x7_0_height, kehops_ir_r_10x7_0_bits);                

                // BUTTONS                
                    if(kehops.button[0].measure.state)
                        display_addCircle(&dev_U8G2_display[ptrDev], 21, 40, 3, 1);
                    else
                        display_addCircle(&dev_U8G2_display[ptrDev], 21, 40, 3, 0);

                    if(kehops.button[1].measure.state)
                        display_addCircle(&dev_U8G2_display[ptrDev], 39, 40, 3, 1);
                    else
                        display_addCircle(&dev_U8G2_display[ptrDev], 39, 40, 3, 0);                


                    display_addText(&dev_U8G2_display[ptrDev],60,10, 0, strDist);

                    // Display battery and voltage
                    sprintf(strTemp, "%d", (int)kehops.analogInput[0].measure.capacity / 20);
                    display_addIcon(&dev_U8G2_display[ptrDev], 120, 60, 0, strTemp);                

                    display_addText(&dev_U8G2_display[ptrDev],80,60, 0, strVolt);

                    sprintf(strTemp, "  %d %s", (int)kehops.analogInput[0].measure.capacity, "%");
                    display_addText(&dev_U8G2_display[ptrDev],80,50, 0, strTemp);

                    display_updateScreen(&dev_U8G2_display[ptrDev]);
                }
                
// DISPLAY FOR 32px
                if(dev_U8G2_display[ptrDev].width >= 128 && dev_U8G2_display[ptrDev].height <= 32){
                    //display_clearScreen(&dev_display[ptrDev]);
                    // Build the screen
                    gcvt((float)kehops.analogInput[0].measure.voltage_mV/1000, 3, strTemp);
                    sprintf(strVolt, "%s V", strTemp);
                    sprintf(strDist, "%d [cm]", kehops.sonar[0].measure.distance_cm);

                    display_clearBuffer(&dev_U8G2_display[ptrDev]);

                    // Display the sonar evaluation logo               
                    if(kehops.sonar[0].measure.distance_cm < 10)
                        display_addXBM(&dev_U8G2_display[ptrDev], 5, 8, kehops_us_33x17_0_width, kehops_us_33x17_0_height, kehops_us_33x17_0_bits);
                    if(kehops.sonar[0].measure.distance_cm >= 10 & kehops.sonar[0].measure.distance_cm < 20)
                        display_addXBM(&dev_U8G2_display[ptrDev], 5, 8, kehops_us_33x17_1_width, kehops_us_33x17_1_height, kehops_us_33x17_1_bits);                
                    if(kehops.sonar[0].measure.distance_cm >= 20 & kehops.sonar[0].measure.distance_cm <30)
                        display_addXBM(&dev_U8G2_display[ptrDev], 5, 8, kehops_us_33x17_2_width, kehops_us_33x17_2_height, kehops_us_33x17_2_bits);
                    if(kehops.sonar[0].measure.distance_cm >= 30)
                        display_addXBM(&dev_U8G2_display[ptrDev], 5, 8, kehops_us_33x17_3_width, kehops_us_33x17_3_height, kehops_us_33x17_3_bits);


                    display_addText(&dev_U8G2_display[ptrDev],45,16, 0, strDist);

                    // Display battery and voltage
                    sprintf(strTemp, "%d", (int)kehops.analogInput[0].measure.capacity / 20);
                    display_addIcon(&dev_U8G2_display[ptrDev], 120, 30, 0, strTemp);                

                    display_addText(&dev_U8G2_display[ptrDev],80,30, 0, strVolt);


                    display_updateScreen(&dev_U8G2_display[ptrDev]);
                }
            }
            else
                {
                #ifdef INFO_BUS_DEBUG                
                printf("#! Function [actuator_setKehopsDisplay] -> I2C Error: Bad address or device not connected\n");
                #endif             
            }                                       
        }else{
                printf ("#! Function [actuator_setKehopsDisplay] -> Unknown driver name: %s\n", kehopsActuators.gfxDisplay[gfxID].hw_driver.name);
        }
    }
    
    // SUBDRIVER ACTION Check if driver IC need a subdriver and make a pre-action if required
    subDriver_onDeactivate(kehopsActuators.gfxDisplay[gfxID].hw_driver.name);
}


/**
 * \brief int actuator_setDisplayText(unsigned char gfxID)
 * \param gfxID, ID of display in kehops.cfg
 * \return error code
 */ 

int actuator_setDisplayText(unsigned char gfxID, char * text, char *border, char *icon){
    int ptrDev=-1;
   
    // Check if driver IC need a subdriver and make a pre-action if required
    subDriver_onActivate(kehopsActuators.gfxDisplay[gfxID].hw_driver.name);
    
    if(!strcmp(kehopsActuators.gfxDisplay[gfxID].hw_driver.type, DRIVER_SH1106) || !strcmp(kehopsActuators.gfxDisplay[gfxID].hw_driver.type, DRIVER_SSD1306)){
        usleep(50000);
        ptrDev = getDriverConfig_ptr(DRIVER_SH1106, kehopsActuators.gfxDisplay[gfxID].hw_driver.name);
        
        if(ptrDev>=0){
            if(dev_U8G2_display[ptrDev].deviceAddress > 0){
                if(dev_U8G2_display[ptrDev].width >= 128 && dev_U8G2_display[ptrDev].height >= 64){

                    display_clearBuffer(&dev_U8G2_display[ptrDev]);
                    
                    // Select the border 
                    if(!strcmp(border, "bubble"))
                        display_addXBM(&dev_U8G2_display[ptrDev], 0, 0, bubble_128x64_width, bubble_128x64_height, bubble_128x64_bits);
                    if(!strcmp(border, "normal"))
                        display_addXBM(&dev_U8G2_display[ptrDev], 0, 0, rectangle_128x64_width, rectangle_128x64_height, rectangle_128x64_bits);
                    
                    display_addText(&dev_U8G2_display[ptrDev],10,30, 1, text);

                    display_updateScreen(&dev_U8G2_display[ptrDev]);
                }
                
// DISPLAY FOR 32px
                if(dev_U8G2_display[ptrDev].width >= 128 && dev_U8G2_display[ptrDev].height <= 32){

                    display_clearBuffer(&dev_U8G2_display[ptrDev]);

                    // Select the border 
                    if(!strcmp(border, "bubble"))
                        display_addXBM(&dev_U8G2_display[ptrDev], 0, 0, bubble_128x32_width, bubble_128x32_height, bubble_128x32_bits);
                    if(!strcmp(border, "normal"))
                        display_addXBM(&dev_U8G2_display[ptrDev], 0, 0, rectangle_128x32_width, rectangle_128x32_height, rectangle_128x32_bits);

                    display_addText(&dev_U8G2_display[ptrDev],10,16, 1, text);

                    display_updateScreen(&dev_U8G2_display[ptrDev]);
                }
            }
            else
                {
                #ifdef INFO_BUS_DEBUG                
                printf("#! Function [actuator_setKehopsDisplay] -> I2C Error: Bad address or device not connected\n");
                #endif             
            }                                       
        }else{
                printf ("#! Function [actuator_setKehopsDisplay] -> Unknown driver name: %s\n", kehopsActuators.gfxDisplay[gfxID].hw_driver.name);
        }
    }
    
    // SUBDRIVER ACTION Check if driver IC need a subdriver and make a pre-action if required
    subDriver_onDeactivate(kehopsActuators.gfxDisplay[gfxID].hw_driver.name);
}


/**
 * \brief int actuator_getFirmwareVersion(void), FUNCTION TO COMPLETE
 *  ! NOT IMPLEMENTED
 * \param ! NOT IMPLEMENTED
 * \return ! NOT IMPLEMENTED
 */  

int actuator_getFirmwareVersion(void){
    /*
    ptrDev = getEFM8BBconfig_ptr(kehops.analogInput[0].config.ain_id);
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
    ptrDev = getEFM8BBconfig_ptr(kehops.analogInput[0].config.ain_id);
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
 * \brief int getDriverConfig_ptr(char * driverType, char * name), Search in the table
 * the configuration structure correspondant to the driver selected by type and by name 
 * and return a pointer of this structure.
 * \param char * name , name of the device (like IC3, U5, etc...)
 * \return pointer of the correspondant configuration stucture
 */ 
int getDriverConfig_ptr(char * driverType, char * name){
    int i, refFound=-1;
    
    if(!strcmp(driverType, DRIVER_PCA9685)){
        for(i=0; refFound<0 && i<pca9685_count ;i++){
            if(!strcmp(dev_pca9685[i].deviceName, name)){
                refFound = i;
            }
        }
    }
    
    if(!strcmp(driverType, DRIVER_BH1745)){
        for(i=0; refFound<0 && i<bh1745_count ;i++){
            if(!strcmp(dev_bh1745[i].deviceName, name)){
                refFound = i;
            }
        }
    }

    if(!strcmp(driverType, DRIVER_EFM8BB)){
        for(i=0; refFound<0 && i<efm8bb_count ;i++){
            if(!strcmp(dev_efm8bb[i].deviceName, name)){
                refFound = i;
            }
        }        
    }
    if(!strcmp(driverType, DRIVER_MCP23008)){
        for(i=0; refFound<0 && i<mcp230xx_count ;i++){
            if(!strcmp(dev_mcp230xx[i].deviceName, name)){
                refFound = i;
            }
        }        
    }
    if(!strcmp(driverType, DRIVER_MCP23017)){
    for(i=0; refFound<0 && i<mcp230xx_count ;i++){
        if(!strcmp(dev_mcp230xx[i].deviceName, name)){
            refFound = i;
        }
    }        
    }
    if(!strcmp(driverType, DRIVER_PCA9629)){
        for(i=0; refFound<0 && i<pca9629_count ;i++){
            if(!strcmp(dev_pca9629[i].deviceName, name)){
                refFound = i;
            }
        }        
    }
    if(!strcmp(driverType, DRIVER_VL53L0X)){
        for(i=0; refFound<0 && i<vl53l0x_count ;i++){
            if(!strcmp(dev_vl53l0x[i].deviceName, name)){
                refFound = i;
            }
        }        
    }
    if(!strcmp(driverType, DRIVER_MCP4725)){
        for(i=0; refFound<0 && i<mcp4725_count ;i++){
            if(!strcmp(dev_mcp4725[i].deviceName, name)){
                refFound = i;
            }
        }        
    }
    if(!strcmp(driverType, DRIVER_TCA9548A)){
        for(i=0; refFound<0 && i<tca9548a_count ;i++){
            if(!strcmp(dev_tca9548a[i].deviceName, name)){
                refFound = i;
            }
        }        
    }   
    
    if(!strcmp(driverType, DRIVER_SSD1305)){
        for(i=0; refFound<0 && i<display_U8G2_count ;i++){
            if(!strcmp(dev_U8G2_display[i].deviceName, name)){
                refFound = i;
            }
        }        
    } 
    if(!strcmp(driverType, DRIVER_SSD1306)){
        for(i=0; refFound<0 && i<display_U8G2_count ;i++){
            if(!strcmp(dev_U8G2_display[i].deviceName, name)){
                refFound = i;
            }
        }        
    }
    if(!strcmp(driverType, DRIVER_SH1106)){
        for(i=0; refFound<0 && i<display_U8G2_count ;i++){
            if(!strcmp(dev_U8G2_display[i].deviceName, name)){
                refFound = i;
            }
        }        
    }    
    if(!strcmp(driverType, DRIVER_ADS101X)){
        for(i=0; refFound<0 && i < ads101x_count ;i++){
            if(!strcmp(dev_ads101x[i].deviceName, name)){
                refFound = i;
            }
        }        
    }
    if(!strcmp(driverType, DRIVER_ADS111X)){
        for(i=0; refFound<0 && i < ads111x_count ;i++){
            if(!strcmp(dev_ads111x[i].deviceName, name)){
                refFound = i;
            }
        }        
    }    

    return refFound;
}


/*
 * \fn char actuator_genericHBridge_motorDirection()
 * \brief Get the DC MOTOR hardware id of and setup the direction
 *
 * \param motorNumber, direction
 * \return -
 */

int actuator_genericHBridge_motorDirection(int motorID, int direction){ 
    int cw_channel, ccw_channel;
    char cw_driverType[25], cw_driverName[25];
    char ccw_driverType[25], ccw_driverName[25];
    

// GET THE DEVICES IC INFORMATIONS (CHANNEL, TYPE AND NAME)
    cw_channel = kehopsActuators.dc_motor[motorID].sw_driver.dc_motor.cw.hw_driver.attributes.device_channel;    
    strcpy(cw_driverType, kehopsActuators.dc_motor[motorID].sw_driver.dc_motor.cw.hw_driver.type);
    strcpy(cw_driverName, kehopsActuators.dc_motor[motorID].sw_driver.dc_motor.cw.hw_driver.name);

    ccw_channel = kehopsActuators.dc_motor[motorID].sw_driver.dc_motor.ccw.hw_driver.attributes.device_channel;
    strcpy(ccw_driverType, kehopsActuators.dc_motor[motorID].sw_driver.dc_motor.ccw.hw_driver.type);
    strcpy(ccw_driverName, kehopsActuators.dc_motor[motorID].sw_driver.dc_motor.ccw.hw_driver.name);

// STOP THE MOTOR, NO CW OR CCW SELECTED
    driverSelector_SetDOUT(cw_driverType, cw_driverName, cw_channel, 0);
    driverSelector_SetDOUT(cw_driverType, ccw_driverName, ccw_channel, 0);

// Wait for 20mS
    usleep(20000);
    
// APPLY THE VALUE ON THE DIRECTION OUTPUT
    if(direction >0 )
        driverSelector_SetDOUT(cw_driverType, cw_driverName, cw_channel, 100);
    else 
        if(direction <0 )
            driverSelector_SetDOUT(ccw_driverType, ccw_driverName, ccw_channel, 100);
    
    return 0;
}

/*
 * \fn char actuator_genericHBridge_motorState(int motorID, int state)
 * \brief to do
 *
 * \param motorID, state
 * \return -
 */
int actuator_genericHBridge_motorState(int motorID, int state){
    int en_channel;
    char en_driverType[25], en_driverName[25];
    
    // GET THE DEVICES IC INFORMATIONS (CHANNEL, TYPE AND NAME)
    en_channel = kehopsActuators.dc_motor[motorID].sw_driver.dc_motor.enable.hw_driver.attributes.device_channel;    
    strcpy(en_driverType, kehopsActuators.dc_motor[motorID].sw_driver.dc_motor.enable.hw_driver.type);
    strcpy(en_driverName, kehopsActuators.dc_motor[motorID].sw_driver.dc_motor.enable.hw_driver.name);
    
    // APPLY THE VALUE ON THE DIRECTION OUTPUT
    driverSelector_SetDOUT(en_driverType, en_driverName, en_channel, state);
    return 0;
}

/*
 * \fn char actuator_genericHBridge_motorSpeed()
 * \brief Get the DC MOTOR hardware id of and setup the speed
 *
 * \param motorNumber, speed
 * \return -
 */

int actuator_genericHBridge_motorSpeed(int motorID, int speed){
    int ptrDev;
    char driverType[25], driverName[25];
    int result;
    int channel = kehopsActuators.dc_motor[motorID].sw_driver.dc_motor.speed.hw_driver.attributes.device_channel;
    strcpy(driverType, kehopsActuators.dc_motor[motorID].sw_driver.dc_motor.speed.hw_driver.type);
    strcpy(driverName, kehopsActuators.dc_motor[motorID].sw_driver.dc_motor.speed.hw_driver.name);
    
    // APPLY THE VALUE ON THE DIRECTION OUTPUT
    result = driverSelector_SetDOUT(driverType, driverName, channel, speed);
    
    if(result)
        printf("SET MOTOR SPEED VALUE FROM DRIVERS:  NAME:%s TYPE:%s   motor_id: %d     channel: %d     ratio: %d\n", driverName, driverType, motorID, channel, speed);                
    
    return 0;
}


/*
 * \fn char driverSelector_SetDOUT(char * driverType, char * driverName, int channel, int value)
 * \brief to do
 *
 * \param driverType, driverName, channel, value
 * \return -
 */
int driverSelector_SetDOUT(char * driverType, char * driverName, int channel, int value){
    int ptrDev=-1;
    
    ptrDev = getDriverConfig_ptr(driverType, driverName);

    // SUBDRIVER ACTION Check if driver IC need a subdriver and make a pre-action if required
    subDriver_onActivate(driverName);
    
    // USE DRIVER FOR PCA9685
    if(!strcmp(driverType, DRIVER_PCA9685)){
        if(ptrDev>=0){
            if(dev_pca9685[ptrDev].deviceAddress > 0)
                pca9685_setPWMdutyCycle(&dev_pca9685[ptrDev], channel, value);
            else
                {
                #ifdef INFO_BUS_DEBUG                
                printf("#! Function [driverSelector_SetDOUT] -> I2C Error: Bad address or device not connected\n");
                #endif             
            }             
        }
    }
        
    // USE DRIVER FOR MCP230xx
    if(!strcmp(driverType, DRIVER_MCP23008)){
        if(ptrDev>=0){
            if(dev_mcp230xx[ptrDev].deviceAddress > 0)
                mcp230xx_setChannel(&dev_mcp230xx[ptrDev], channel, value);
            else
                {
                #ifdef INFO_BUS_DEBUG                
                printf("#! Function [driverSelector_SetDOUT] -> I2C Error: Bad address or device not connected\n");
                #endif             
            }
        }
    }    

    // USE DRIVER FOR MCP23017
    if(!strcmp(driverType, DRIVER_MCP23017)){
        if(ptrDev>=0){
            if(dev_mcp230xx[ptrDev].deviceAddress > 0)
                mcp230xx_setChannel(&dev_mcp230xx[ptrDev], channel, value);
            else
                {
                #ifdef INFO_BUS_DEBUG                
                printf("#! Function [driverSelector_SetDOUT] -> I2C Error: Bad address or device not connected\n");
                #endif             
            }
        }
    } 
    
    // SUBDRIVER ACTION Check if driver IC need a subdriver and make a post-action if required
    subDriver_onDeactivate(driverName);
    
    if(ptrDev<0)
        printf ("#! Function [driverSelector_SetDOUT] -> Unknown driver name: %s\n", driverName);
    
    return ptrDev;
}

/*
 * \fn char setDeviceChannelByName(char * driverType, char * driverName, int channel, int value)
 * \brief to do
 *
 * \param driverType, driverName, channel, value
 * \return -
 */
int setDeviceChannelByName(char * deviceName, int channel, int value){
    int ptrDev=-1;
    int err=0;
    char * subDriverType;
                
    subDriverType = getDriverTypeByName(deviceName);
    ptrDev = getDriverConfig_ptr(subDriverType, deviceName);
            
    // USE DRIVER FOR TCA9548A I2C SWITCH
    if(!strcmp(subDriverType, DRIVER_TCA9548A)){
        if(ptrDev>=0){
            if(dev_tca9548a[ptrDev].deviceAddress > 0)
                err += tca9548a_setChannelState(&dev_tca9548a[ptrDev], channel, value);
            else
                {
                #ifdef INFO_BUS_DEBUG                
                printf("#! Function [setDeviceChannelByName] -> I2C Error: Bad address or device not connected\n");
                #endif 
            }            
        }
    }

    if(ptrDev<0)
        printf ("#! Function [setDeviceChannelByName] -> Unknown device name: %s\n", deviceName);
    
    return err;
}

/*
 * \fn char * getSubdriverSettingsByName(char * driverName)
 * \brief search in the boardDeviceList if the component specified by name use
 *  a sub-driver and return the name of this subdriver if found.
 *
 * \param driverType, driverName, channel, value
 * \return -
 */
struct device_subdrivers getSubdriverSettingsByName(char * driverName){
    int i;
    struct device_subdrivers dummySubdriverData;;
    
    strcpy(dummySubdriverData.name, "");
    dummySubdriverData.attributes.device_channel=-1;
    dummySubdriverData.attributes.onActivate=-1;
    dummySubdriverData.attributes.onDeactivate=-1;
    
    for(i=0; boardDevice[i].address >= 0 && i<MAX_BOARD_DEVICE; i++){
        if(!strcmp(boardDevice[i].name, driverName))
            if(strcmp(boardDevice[i].sub_driver.name, ""))
                return boardDevice[i].sub_driver;
    }
    
    return dummySubdriverData;
}



/*
 * \fn int subDriver_onActivate(char * driverName)
 * \brief search if the component specified by name use
 *  a sub-driver and set a pre action if found;
 *
 * \param driverName
 * \return -
 */

int subDriver_onActivate(char * driverName){
    struct device_subdrivers subDriverSettings;
    int status=0;;
    
    // Check if a subdriver is requiered
    subDriverSettings = getSubdriverSettingsByName(driverName);
    if(strcmp(subDriverSettings.name, "")){
        status = setDeviceChannelByName(subDriverSettings.name, subDriverSettings.attributes.device_channel, subDriverSettings.attributes.onActivate);
    }
    
    return status;
}

/*
 * \fn int subDriver_onDeactivate(char * driverName)
 * \brief search if the component specified by name use
 *  a sub-driver and set a post action if found;
 *
 * \param driverName
 * \return -
 */

int subDriver_onDeactivate(char * driverName){
    struct device_subdrivers subDriverSettings;
    int status = 0;
        
    // Check if a subdriver is requiered
    subDriverSettings = getSubdriverSettingsByName(driverName);
    if(strcmp(subDriverSettings.name, "")){
        //printf("\nSUBDRIVER POST ACTION FOR [%s]: NAME: %s, CHANNEL: %d, VALUE: %d\n", driverName, subDriverSettings.name,
        //    subDriverSettings.attributes.device_channel, 0);  
            
        status = setDeviceChannelByName(subDriverSettings.name, subDriverSettings.attributes.device_channel, subDriverSettings.attributes.onDeactivate);
    }    
    return status;
}