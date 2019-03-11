/**
 * \file partsDescriptor.c
 * \brief  Interconnect the user parts (like LEDs components) to the hardware
 *  driver IC output (like PCA9685 driver) or generic driver.
 *      
 * \author Raphael Thurnherr
 * \version 0.1
 * \date 09.03.2019
 *
 *  With reading the partsDescriptor.cfg file, these functions will create dynamically
 *  the connections between the user components parts (leds, motors, etc..) and the terminals
 *  of the driver IC.
 * 
 */

#define MAX_BOARD_DEVICE 25
#define MAX_MQTT_BUFF 8192

// Library dependency
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "jRead.h"
#include "jWrite.h"
#include "driverDescriptor_jsonKeys.h"
#include "driversDescriptor.h"


char * OpenDataFromFile(char *filename);
char LoadDescriptor(char * fileName);
char LoadDevicesDescriptor(char * fileName);

/**
 * \fn char * OpenConfigFromFile(char *filename)
 * \brief Open the config file get the content for futur use.
 *
 * \param filename to open
 * \return pointer to the buffer with file content
 */

char * OpenDataFromFile(char *filename){   
    FILE *myFile = fopen(filename, "rw+");
   static char *srcDataContent = NULL;
   
   int string_size, read_size;

   if (myFile)
   {
       // Seek the last byte of the file
       fseek(myFile, 0, SEEK_END);
       // Offset from the first to the last byte, or in other words, filesize
       string_size = ftell(myFile);
       // go back to the start of the file
       rewind(myFile);

       // Allocate a string that can hold it all
       srcDataContent = (char*) malloc(sizeof(char) * (string_size + 1) );

       // Read it all in one operation
       read_size = fread(srcDataContent, sizeof(char), string_size, myFile);

       // fread doesn't set it so put a \0 in the last position
       // and buffer is now officially a string
       srcDataContent[string_size] = '\0';

       if (string_size != read_size)
       {
           // Something went wrong, throw away the memory and set
           // the buffer to NULL
           free(srcDataContent);
           srcDataContent = NULL;
       }

       // Always remember to close the file.
       fclose(myFile);
    }
      
   return(srcDataContent);
}

/**
 * \fn char LoadDriversDescriptor(char * fileName)
 * \brief Extract the file config content and store the JSON result convertion
 *  to the structure.
 * 
 * NOTE: The ID field of devices in the config file will define the field in the 
 * structure array. Not uses later.
 *
 * \param filename to open
 * \return error
 */

char LoadDriversDescriptor(char * fileName){
    struct jReadElement devList, deviceData, deviceInitData;
    int devicesCount, deviceId;
    int i, j;
    char * srcDataBuffer;
    char strValue[15];

    // Create structure for devices on the board
    devices_list boardDevice[MAX_BOARD_DEVICE];

    // Read file and store the result in buffer
    srcDataBuffer = OpenDataFromFile(fileName); 


    // Check that the file is not empty
    if(srcDataBuffer != NULL){

        // Get the device list 
        jRead((char *)srcDataBuffer, FILE_KEY_DEVICES, &devList );
        
        if(devList.dataType == JREAD_ARRAY ){
            devicesCount = devList.elements;       // Get the number of devices
            
            if(devicesCount > MAX_BOARD_DEVICE)
                printf("[driversDescriptor.c] !!! LoadDriversDescriptor() WARNING, MAX DEVICES LIMIT, ONLY THE %d FIRST ID WILL BE USED\n ", MAX_BOARD_DEVICE);
            for(i=0; i < devicesCount; i++){ 
                deviceId=-1;
                deviceId=jRead_int((char *)srcDataBuffer, FILE_KEY_DEVICES_ID, &i); 

                // Get the device setting if ID specified
                if(deviceId >= 0 && deviceId < MAX_BOARD_DEVICE){
                    // Get the type (name) of the device
                    if(jRead_string((char *)srcDataBuffer, FILE_KEY_DEVICES_TYPE, strValue, 15, &i )>0)
                        strcpy(boardDevice[deviceId].type, strValue);
                    else strcpy(boardDevice[deviceId].type, "error");

                    // Get the bus address of the device, detect if address is a 
                    // string or a number, if string, convert to number
                    jRead((char *)srcDataBuffer, FILE_KEY_DEVICES_ADDRESS, &deviceData);
                    if(deviceData.dataType == JREAD_STRING){
                        // Convert string to int
                        if(jRead_string((char *)srcDataBuffer, FILE_KEY_DEVICES_ADDRESS, strValue, 15, &i )>0)
                            boardDevice[deviceId].address = strtol(strValue, NULL, 0);
                        else boardDevice[deviceId].address= -1;
                    }
                    else{
                            if(deviceData.dataType == JREAD_NUMBER){
                                boardDevice[deviceId].address = jRead_double((char *)srcDataBuffer, FILE_KEY_DEVICES_ADDRESS, &i); 
                            }
                    }
/*RECURSIVE SEARCH IN ARRAY DON'T WORK*/   
                    /*
                    // Get the attribute of the device
                    jReadParam((char *)srcDataBuffer, FILE_KEY_DEVICES_ATTRIBUTES_DEVINIT, &deviceInitData, i);  

//                    jRead((char *)deviceInitData.pValue, DEVICES_ATTRIBUTES_DEVINIT, &deviceInitData);
                    printf(" !!!!!!!!! MY INIT PARAM %d DATA: %s\n", i, deviceInitData.pValue);

                    
                    if(deviceInitData.dataType == JREAD_ARRAY){
                                         printf(" !!!!!!!!! MY INIT  DATA: %s\n", deviceInitData.pValue);   
                        int initDataCount = deviceInitData.elements;
                        for(j=0; j<initDataCount;j++){
                             // Get all the init attributes "register address"
                            jRead((char *)srcDataBuffer, DEVICES_ATTRIBUTES_DEVINIT_INIT_ADDR, &deviceInitData);
                            
                            
                            if(deviceInitData.dataType == JREAD_STRING){
                                // Convert string to int
                                if(jRead_string((char *)srcDataBuffer, DEVICES_ATTRIBUTES_DEVINIT_INIT_ADDR, strValue, 15, &i )>0)
                                    boardDevice[deviceId].attributes.deviceInit[j].regAddr = strtol(strValue, NULL, 0);
                                else boardDevice[deviceId].attributes.deviceInit[j].regAddr= -1;
                            }
                            else{
                                    if(deviceInitData.dataType == JREAD_NUMBER){
                                       boardDevice[deviceId].attributes.deviceInit[j].regAddr = jRead_double((char *)srcDataBuffer, DEVICES_ATTRIBUTES_DEVINIT_INIT_ADDR, &i); 
                                    }
                            }
                            
                            // Get all the init attributes "register data"
                            jRead((char *)srcDataBuffer, DEVICES_ATTRIBUTES_DEVINIT_INIT_DATA, &deviceInitData);
                            if(deviceInitData.dataType == JREAD_STRING){
                                // Convert string to int
                                if(jRead_string((char *)srcDataBuffer, DEVICES_ATTRIBUTES_DEVINIT_INIT_DATA, strValue, 15, &i )>0)
                                    boardDevice[deviceId].attributes.deviceInit[j].regData = strtol(strValue, NULL, 0);
                                else boardDevice[deviceId].attributes.deviceInit[j].regData = -1;
                            }
                            else{
                                    if(deviceInitData.dataType == JREAD_NUMBER){
                                        boardDevice[deviceId].attributes.deviceInit[j].regData = jRead_double((char *)srcDataBuffer, DEVICES_ATTRIBUTES_DEVINIT_INIT_DATA, &i); 
                                    }
                            }                            
                        }
                    }
                     * */
                }
            }
            
            printf("\n DEBUG ----- DEVICE IN CONFIG FILE: %d -------\n", devicesCount);
            for(i=0;i<devicesCount;i++){
                printf("\n   Device ID #%d     type: %s    address: %d", i, boardDevice[i].type, boardDevice[i].address);
                    //for(j=0;j<3;j++){
                        //printf("\n     Register: %d   Data: %d", i);
            //}
            }
        }
    }

    return -1;
}

/**
 * \fn char LoadDevicesDescriptor(char * fileName)
 * \brief Extract the file content from buffer and dispatch the settings to the
 * kehops structure.
 *
 * \param filename to open
 * \return pointer to the buffer with file content
 */

char LoadDevicesDescriptor(char * fileName){
    struct jReadElement partsList, deviceData, deviceInitData;
    int devicesCount, deviceId;
    int i, j;
    char * srcDataBuffer;
    char strValue[15];
        
    srcDataBuffer = OpenDataFromFile(fileName); 

/*
    if(srcDataBuffer != NULL){
        
        // Get the device list 
        jRead((char *)srcDataBuffer, FILE_KEY_DEVICES, &partsList );

        if(partsList.dataType == JREAD_ARRAY ){
            devicesCount = partsList.elements;       // Get the number of devices

            if(devicesCount > MAX_BOARD_DEVICE)
                printf("[driversDescriptor.c] !!! LoadDriversDescriptor() WARNING, MAX DEVICES LIMIT, ONLY THE %d FIRST ID WILL BE USED\n ", MAX_BOARD_DEVICE);
            for(i=0; i < devicesCount; i++){ 
                deviceId=-1;
                deviceId=jRead_int((char *)srcDataBuffer, FILE_KEY_DEVICES_ID, &i); 

                // Get the device setting if ID specified
                if(deviceId >= 0 && deviceId < MAX_BOARD_DEVICE){
                    // Get the type (name) of the device
                    if(jRead_string((char *)srcDataBuffer, FILE_KEY_DEVICES_TYPE, strValue, 15, &i )>0)
                        strcpy(boardDevice[deviceId].type, strValue);
                    else strcpy(boardDevice[deviceId].type, "error");

                    // Get the bus address of the device, detect if address is a 
                    // string or a number, if string, convert to number
                    jRead((char *)srcDataBuffer, FILE_KEY_DEVICES_ADDRESS, &deviceData);
                    if(deviceData.dataType == JREAD_STRING){
                        // Convert string to int
                        if(jRead_string((char *)srcDataBuffer, FILE_KEY_DEVICES_ADDRESS, strValue, 15, &i )>0)
                            boardDevice[deviceId].address = strtol(strValue, NULL, 0);
                        else boardDevice[deviceId].address= -1;
                    }
                    else{
                            if(deviceData.dataType == JREAD_NUMBER){
                                boardDevice[deviceId].address = jRead_double((char *)srcDataBuffer, FILE_KEY_DEVICES_ADDRESS, &i); 
                            }
                    }
                }
            }

            printf("\n DEBUG ----- DEVICE IN CONFIG FILE: %d -------\n", devicesCount);
            for(i=0;i<devicesCount;i++){
                printf("\n   Device ID #%d     type: %s    address: %d", i, boardDevice[i].type, boardDevice[i].address);
                    //for(j=0;j<3;j++){
                        //printf("\n     Register: %d   Data: %d", i);
            //}
            }
        }
    }
        */
        return -1;
}






