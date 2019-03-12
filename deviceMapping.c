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
#define MAX_DRIVERS_PER_TYPE 25
#define MAX_MQTT_BUFF 8192

// Library dependency
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "jRead.h"
#include "jWrite.h"
#include "deviceMapping_jsonKeys.h"
#include "deviceMapping.h"


char * OpenDataFromFile(char *filename);
char LoadDescriptor(char * fileName);
char LoadDevicesDescriptor(char * fileName);


/**
 * \fn char * printDriverData(int partsNb, struct device * device)
 * \brief Print a structured view of a device settings
 *
 * \param int partsNb (No of part in array) 
 * \param struct device * device (No of part in array)
 * 
 * \return pointer to the buffer with file content
 */
unsigned char printDriverData(int partsNb, struct device * device);


/**
 * \fn char * OpenConfigFromFile(char *filename)
 * \brief Open the config file get the content for futur use.
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
    struct jReadElement partsList;
    int partsCount, driverId;
    int i, data, readResult;
    char * srcDataBuffer;
    char strValue[25];
        
    kehopsParts kparts;
    
    srcDataBuffer = OpenDataFromFile(fileName); 

     if(srcDataBuffer != NULL){
         
    // Get the DOUT device list 
         //strcpy(partsList.pValue, "");   // Clear the device data
        jRead((char *)srcDataBuffer, FILE_KEY_DRIVERS_DOUT, &partsList );
        if(partsList.dataType == JREAD_ARRAY ){
            partsCount = partsList.elements;       // Get the number of devices
            //printf("\nDOUT LIST:COUNT: %d     \n", partsCount);           
            for(i=0;i<partsCount;i++){
                driverId=jRead_int((char *)partsList.pValue, FILE_KEY_DRIVER_ID, &i);
                
                if(driverId >= 0 && driverId < MAX_DRIVERS_PER_TYPE){
                    // Get and save the driver ID
                    kparts.dout[driverId].id = driverId;

                    // Get the device ID of IC
                    kparts.dout[driverId].driver.device_id = jRead_int((char *)partsList.pValue, FILE_KEY_DRIVER_DEVICE, &i); 

                    // Get the type of device
                    if(jRead_string((char *)partsList.pValue, FILE_KEY_DRIVER_TYPE, strValue, 15, &i )>0)
                        strcpy(kparts.dout[driverId].driver.device_type, strValue);

                    // Get the channel attribute of device
                    kparts.dout[driverId].driver.attributes.device_channel = jRead_int((char *)partsList.pValue, FILE_KEY_DRIVER_ATTRIBUTES_CHANNEL, &i);
                }else
                    kparts.dout[driverId].id = -1;
                    
            }
            
            for(i=0;i<partsCount;i++)
                printDriverData(i, &kparts.dout[i]);
        }

    // Get the DIN device list 
    // strcpy(partsList.pValue, "");   // Clear the device data
        jRead((char *)srcDataBuffer, FILE_KEY_DRIVERS_DIN, &partsList );
        if(partsList.dataType == JREAD_ARRAY ){
            partsCount = partsList.elements;       // Get the number of devices
          
            //printf("\DIN LIST:COUNT: %d        \n", partsCount); 
            for(i=0;i<partsCount;i++){
                driverId=jRead_int((char *)partsList.pValue, FILE_KEY_DRIVER_ID, &i); 
                
                if(driverId >= 0 && driverId < MAX_DRIVERS_PER_TYPE){
                    // Get and save the driver ID
                    kparts.din[driverId].id = driverId;

                    // Get the device ID of IC
                    kparts.din[driverId].driver.device_id = jRead_int((char *)partsList.pValue, FILE_KEY_DRIVER_DEVICE, &i); 

                    // Get the type of device
                    if(jRead_string((char *)partsList.pValue, FILE_KEY_DRIVER_TYPE, strValue, 15, &i )>0)
                        strcpy(kparts.din[driverId].driver.device_type, strValue);

                    // Get the channel attribute of device
                    kparts.din[driverId].driver.attributes.device_channel = jRead_int((char *)partsList.pValue, FILE_KEY_DRIVER_ATTRIBUTES_CHANNEL, &i);
                    //printDriverData(i, &kparts.din[driverId]);
                }else
                    kparts.din[driverId].id = -1;
            }
        }
        
    // Get the AIN device list 
  //      strcpy(partsList.pValue, "");   // Clear the device data
        jRead((char *)srcDataBuffer, FILE_KEY_DRIVERS_AIN, &partsList );
        if(partsList.dataType == JREAD_ARRAY ){
            partsCount = partsList.elements;       // Get the number of devices
            //printf("\nAIN LIST:COUNT: %d      \n", partsCount);           
            for(i=0;i<partsCount;i++){
                driverId=jRead_int((char *)partsList.pValue, FILE_KEY_DRIVER_ID, &i); 
                
                if(driverId >= 0 && driverId < MAX_DRIVERS_PER_TYPE){                
                    // Get and save the driver ID
                    kparts.ain[driverId].id = driverId;

                    // Get the device ID of IC
                    kparts.ain[driverId].driver.device_id = jRead_int((char *)partsList.pValue, FILE_KEY_DRIVER_DEVICE, &i); 

                    // Get the type of device
                    if(jRead_string((char *)partsList.pValue, FILE_KEY_DRIVER_TYPE, strValue, 15, &i )>0)
                        strcpy(kparts.ain[driverId].driver.device_type, strValue);

                    // Get the channel attribute of device
                    kparts.ain[driverId].driver.attributes.device_channel = jRead_int((char *)partsList.pValue, FILE_KEY_DRIVER_ATTRIBUTES_CHANNEL, &i);

                    //printDriverData(i, &kparts.ain[driverId]);
                }else
                    kparts.ain[driverId].id = -1;
            }
        } 
        
    // Get the COUNTER device list 
        //strcpy(partsList.pValue, "");   // Clear the device data
        jRead((char *)srcDataBuffer, FILE_KEY_DRIVERS_CNT, &partsList );
        if(partsList.dataType == JREAD_ARRAY ){
            partsCount = partsList.elements;       // Get the number of devices
            //printf("\COUNTER LIST:COUNT: %d       \n", partsCount);           
            for(i=0;i<partsCount;i++){
                driverId=jRead_int((char *)partsList.pValue, FILE_KEY_DRIVER_ID, &i); 
                
                if(driverId >= 0 && driverId < MAX_DRIVERS_PER_TYPE){                
                    // Get and save the driver ID
                    kparts.counter[driverId].id = driverId;

                    // Get the device ID of IC
                    kparts.counter[driverId].driver.device_id = jRead_int((char *)partsList.pValue, FILE_KEY_DRIVER_DEVICE, &i); 

                    // Get the type of device
                    if(jRead_string((char *)partsList.pValue, FILE_KEY_DRIVER_TYPE, strValue, 15, &i )>0)
                        strcpy(kparts.counter[driverId].driver.device_type, strValue);

                    // Get the channel attribute of device
                    kparts.counter[driverId].driver.attributes.device_channel = jRead_int((char *)partsList.pValue, FILE_KEY_DRIVER_ATTRIBUTES_CHANNEL, &i);

                    //printDriverData(i, &kparts.counter[driverId]);
                }else
                    kparts.counter[driverId].id = -1;
            }
        }

            // Get the RGB Sensor device list 
//        strcpy(partsList.pValue, "");   // Clear the device data
        jRead((char *)srcDataBuffer, FILE_KEY_DRIVERS_RGB, &partsList );
        if(partsList.dataType == JREAD_ARRAY ){
            partsCount = partsList.elements;       // Get the number of devices
            //printf("\nRGB LIST:COUNT: %d           \n", partsCount);           
            for(i=0;i<partsCount;i++){
                driverId=jRead_int((char *)partsList.pValue, FILE_KEY_DRIVER_ID, &i); 
                
                if(driverId >= 0 && driverId < MAX_DRIVERS_PER_TYPE){                
                    // Get and save the driver ID
                    kparts.rgbSensor[driverId].id = driverId;

                    // Get the device ID of IC
                    kparts.rgbSensor[driverId].driver.device_id = jRead_int((char *)partsList.pValue, FILE_KEY_DRIVER_DEVICE, &i); 

                    // Get the type of device
                    if(jRead_string((char *)partsList.pValue, FILE_KEY_DRIVER_TYPE, strValue, 15, &i )>0)
                        strcpy(kparts.rgbSensor[driverId].driver.device_type, strValue);

                    // Get the channel attribute of device
                    kparts.rgbSensor[driverId].driver.attributes.device_channel  = jRead_int((char *)partsList.pValue, FILE_KEY_DRIVER_ATTRIBUTES_CHANNEL, &i);

                    //printDriverData(i, &kparts.rgbSensor[driverId]);
                }else
                    kparts.rgbSensor[driverId].id = -1;
            }
        }
        
    // Get the DISTANCE device list 
   //     strcpy(partsList.pValue, "");   // Clear the device data
        jRead((char *)srcDataBuffer, FILE_KEY_DRIVERS_DISTANCE, &partsList );
        if(partsList.dataType == JREAD_ARRAY ){
            partsCount = partsList.elements;       // Get the number of devices
            //printf("\DISTANCE LIST:COUNT: %d           \n", partsCount);           
            for(i=0;i<partsCount;i++){
                driverId=jRead_int((char *)partsList.pValue, FILE_KEY_DRIVER_ID, &i); 
                
                if(driverId >= 0 && driverId < MAX_DRIVERS_PER_TYPE){                
                    // Get and save the driver ID
                    kparts.distanceSensor[driverId].id = driverId;

                    // Get the device ID of IC
                    kparts.distanceSensor[driverId].driver.device_id = jRead_int((char *)partsList.pValue, FILE_KEY_DRIVER_DEVICE, &i); 

                    // Get the type of device
                    if(jRead_string((char *)partsList.pValue, FILE_KEY_DRIVER_TYPE, strValue, 15, &i )>0)
                        strcpy(kparts.distanceSensor[driverId].driver.device_type, strValue);

                    // Get the channel attribute of device
                    kparts.distanceSensor[driverId].driver.attributes.device_channel = jRead_int((char *)partsList.pValue, FILE_KEY_DRIVER_ATTRIBUTES_CHANNEL, &i);

                    //printDriverData(i, &kparts.distanceSensor[driverId]);
                }else
                    kparts.distanceSensor[driverId].id = -1;
            }
        }

            // Get the STEPPER device list 
 //       strcpy(partsList.pValue, "");   // Clear the device data
        jRead((char *)srcDataBuffer, FILE_KEY_DRIVERS_STEPPER, &partsList );
        if(partsList.dataType == JREAD_ARRAY ){
            partsCount = partsList.elements;       // Get the number of devices
            //printf("\STEPPER LIST:COUNT: %d           \n", partsCount);           
            for(i=0;i<partsCount;i++){
                driverId=jRead_int((char *)partsList.pValue, FILE_KEY_DRIVER_ID, &i); 
                if(driverId >= 0 && driverId < MAX_DRIVERS_PER_TYPE){
                    // Get and save the driver ID
                    kparts.stepper_motors[driverId].id = driverId;

                    // Get the device ID of IC
                    kparts.stepper_motors[driverId].driver.device_id = jRead_int((char *)partsList.pValue, FILE_KEY_DRIVER_DEVICE, &i); 

                    // Get the type of device
                    if(jRead_string((char *)partsList.pValue, FILE_KEY_DRIVER_TYPE, strValue, 15, &i )>0)
                        strcpy(kparts.stepper_motors[driverId].driver.device_type, strValue);

                    // Get the channel attribute of device
                    kparts.stepper_motors[driverId].driver.attributes.device_channel = jRead_int((char *)partsList.pValue, FILE_KEY_DRIVER_ATTRIBUTES_CHANNEL, &i);

                    //printDriverData(i, &kparts.distanceSensor[driverId]);
                }else
                    kparts.stepper_motors[driverId].id = -1;
            }
        }

     }
        return -1;
}



/**
 * \fn char * printDriverData(char *filename)
 * \brief Open the config file get the content for futur use.
 *
 * \param filename to open
 * \return pointer to the buffer with file content
 * 
 * output format:

 * /**
 * \fn char * printDriverData(int partsNb, struct device * device)
 * \brief Print a structured view of a device settings
 *
 * \param int partsNb (No of part in array) 
 * \param struct device * device (No of part in array)
 * 
 * \return pointer to the buffer with file content
 * 
 *   DIN #0 
 *  |__ ID: 1
 *  |__ Driver
 *     |__ deviceId: 2
 *     |__ type: 
 *     |__ attributes
 *        |__ channel: 5
 * 
 * 
 */

unsigned char printDriverData(int partsNb, struct device * device){
    
    int devId = device->id;
    
    printf("\n PARTS #%d \n |__ ID: %d\n |__ Driver\n    |__ deviceId: %d\n    |__ type: %s\n    |__ attributes\n       |__ channel: %d\n"
            , partsNb, devId, device->driver.device_id, device->driver.device_type,
            device->driver.attributes.device_channel);        
}






