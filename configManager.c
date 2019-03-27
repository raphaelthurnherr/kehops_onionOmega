/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "fileIO.h"
#include "config/kehopsConfig.h"
#include "config/deviceMapping.h"
#include "configManager.h"

/*
// Create the structure for hardware description
//and get the setting from configs file

devices_list boardDevice[MAX_BOARD_DEVICE];
kehopsParts kehopsActuators;
  
*/

/**
 * \fn char LoadConfig(char * fileName)
 * \brief Get the configuration from configurations files (kehops.cgf, deviceMap.cfg, drivers.cfg),
 *
 * \param filename to open
 * \return pointer to the buffer with file content
 */

char LoadConfig(void){

    char * srcDataBuffer;

    srcDataBuffer = OpenConfigFromFile("kehops.cfg");         
    extractKehopsConfig(srcDataBuffer);
    
    // Get the config file and setup the structure board device
    // in the deviceMappingFile
    srcDataBuffer = OpenConfigFromFile("devices.cfg"); 
    LoadDevicesDescriptor(srcDataBuffer, &boardDevice[0]);

    // Get the config file and setup the structure board parts
    // in the deviceMappingFile. Use the board Device for get the IC information
    srcDataBuffer = OpenConfigFromFile("deviceMap.cfg"); 
    LoadBoardDescriptor(srcDataBuffer, &kehopsActuators, &boardDevice[0]);
       
    printf("\n\n ********\n Config extracted: \n MOTORS: %d   STEPPERS: %d  PWM: %d   LED: %d   DIN: %d   AIN: %d   COUNTER: %d  BUTTON: %d  SONAR: %d  COLOR RGB: %d\n*********\n\n",
            NBMOTOR, NBSTEPPER, NBPWM, NBLED, NBDIN, NBAIN, NBCOUNTER, NBBTN, NBSONAR, NBRGBC);

    return -1;
}

/**
 * \fn char SaveConfig(char * fileName)
 * \brief Create configuration file for kehops.
 *
 * \param filename to open
 * \return pointer to the buffer with file content
 */

char SaveConfig(char * fileName){
    
    SaveKehopsConfig("kehops.cfg");
}