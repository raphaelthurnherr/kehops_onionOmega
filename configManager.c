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

    // Get the config file and setup the structure board device
    // in the deviceMappingFile
    srcDataBuffer = OpenConfigFromFile("devices.cfg"); 
    LoadDevicesDescriptor(srcDataBuffer, &boardDevice[0]);

    // Get the config file and setup the structure board parts
    // in the deviceMappingFile        
    srcDataBuffer = OpenConfigFromFile("deviceMap.cfg"); 
    LoadBoardDescriptor(srcDataBuffer, &kehopsActuators);
    
    srcDataBuffer = OpenConfigFromFile("kehops.cfg");         
    extractKehopsConfig(srcDataBuffer);

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