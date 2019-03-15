/**
 * \file deviceMApping.c
 * \brief  Interconnect the user parts (like LEDs components) to the hardware
 *  driver IC output (like PCA9685 driver) or generic driver.
 *      
 * \author Raphael Thurnherr
 * \version 0.1
 * \date 09.03.2019
 *
 *  With reading the deviceMap.cfg file and the device.cfg (electronic components), these
 *  functions will define the structure of the hardware board.
 *  The connections between the user components parts (leds, motors, etc..) and the terminals
 *  of the drivers IC will be create:
 * 
 * 
 */
#define PRINT_INFO

#define MAX_BOARD_DEVICE 50
#define MAX_MQTT_BUFF 8192

// Library dependency
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "jRead.h"
#include "jWrite.h"
#include "deviceMapping_jsonKeys.h"
#include "deviceMapping.h"


// Create structure for devices on the board
devices_list boardDevice[MAX_BOARD_DEVICE];
kehopsParts kparts;


char * OpenDataFromFile(char *filename);
char LoadDescriptor(char * fileName);
char LoadDevicesDescriptor(char * fileName);
  
int getSettings(char * buffer, char * deviceType, struct device * mydevice);
int getDriverSettings(char * buffer, char * deviceType, struct device * mydevice);

// Functions déclaration

unsigned char printDriverData(int partsNb, struct device * device);  // Print a formatted map of the drivers settings using "deviceMap.cfg"
unsigned char printDeviceData(int deviceNb, devices_list * device);  // Print a formatted map of the device IC setting using "devices.cfg"

// Function to clear the drivers and devices structure
void clearDriverSettings(void);
void clearDeviceSettings(void);


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
    char strValue[25];

    // Read file and store the result in buffer
    srcDataBuffer = OpenDataFromFile(fileName); 

    clearDeviceSettings();

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
                    
                    boardDevice[deviceId].device_id=deviceId;
                                    
                    // Get the type (name) of the device
                    if(jRead_string((char *)srcDataBuffer, FILE_KEY_DEVICES_TYPE, strValue, 25, &i )>0)
                        strcpy(boardDevice[deviceId].type, strValue);
                    else strcpy(boardDevice[deviceId].type, "error");

                    // Get the bus address of the device, detect if address is a 
                    // string or a number, if string, convert to number
                    jRead((char *)srcDataBuffer, FILE_KEY_DEVICES_ADDRESS, &deviceData);
                    if(deviceData.dataType == JREAD_STRING){
                        // Convert string to int
                        if(jRead_string((char *)srcDataBuffer, FILE_KEY_DEVICES_ADDRESS, strValue, 25, &i )>0)
                            boardDevice[deviceId].address = strtol(strValue, NULL, 0);
                        else boardDevice[deviceId].address= NULL;
                    }
                    else{
                            if(deviceData.dataType == JREAD_NUMBER){
                                boardDevice[deviceId].address = jRead_double((char *)srcDataBuffer, FILE_KEY_DEVICES_ADDRESS, &i); 
                            }
                    }
                #ifdef PRINT_INFO                     
                    printDeviceData(i, &boardDevice[deviceId]);
                #endif    
                }
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
    char * srcDataBuffer;
 
            
    srcDataBuffer = OpenDataFromFile(fileName); 

    // Set the ID to "unknown"
    clearDriverSettings();
             
     if(srcDataBuffer != NULL){
/*         
    // Get the DC MOTOR device list 
        jRead((char *)srcDataBuffer, KEY_ARRAY_MOTOR, &deviceList );
        if(deviceList.dataType == JREAD_ARRAY ){
            deviceCount = deviceList.elements;       // Get the number of devices

            for(i=0;i<deviceCount;i++){
                
                driverId=jRead_int((char *)deviceList.pValue, FILE_KEY_DRIVER_ID, &i);

                if(driverId >= 0 && driverId < MAX_DRIVERS_PER_TYPE){
                    // Get and save the driver ID
                    kparts.dc_motor[driverId].id = driverId;
                    
                    // Get and save the device interface
                    if(jRead_string((char *)deviceList.pValue, FILE_KEY_DRIVER_INTERFACE, strValue, 25, &i )>0){
                        strcpy(kparts.dc_motor[driverId].interface, strValue);
                       
                        if(!strcmp(kparts.dc_motor[driverId].interface, "generic_hbridge")){
                            printf("****************** GENERIC ***************\n");

                            // Get the "ENABLE SUB-SETTINGS"
                            jReadParam((char *)deviceList.pValue, KEY_ATTRIBUTES_EN, &myDevice, i );

 //                           printf("-----------------------MON DEVICE KEXX:: %s\n", genericList.pValue);  

                            if(jRead_int((char *)myDevice.pValue, KEY_DEVICE, NULL)>0){
                                kparts.dc_motor[driverId].sw_driver.dc_motor.enable.hw_driver.device_id = strValue;
                            }                            
                            
                            if(jRead_string((char *)myDevice.pValue, KEY_TYPE, strValue, 25, NULL)>0){
                                printf("-----------------------MON DEVICE TYPE:: %s\n", strValue);  
                                strcpy(kparts.dc_motor[driverId].sw_driver.dc_motor.enable.hw_driver.device_type, strValue);
                            }                            

                        }else
                        {
                            printf("****************** device ***************\n");
                            
                            // Get the device ID of IC
                            kparts.dc_motor[driverId].hw_driver.device_id = jRead_int((char *)deviceList.pValue, FILE_KEY_DRIVER_DEVICE, &i); 

                            // Get the type of device
                            if(jRead_string((char *)deviceList.pValue, FILE_KEY_DRIVER_TYPE, strValue, 25, &i )>0)
                                strcpy(kparts.dc_motor[driverId].hw_driver.device_type, strValue);

                            // Get the channel attribute of device
                            kparts.dc_motor[driverId].hw_driver.attributes.device_channel = jRead_int((char *)deviceList.pValue, FILE_KEY_DRIVER_ATTRIBUTES_CHANNEL, &i);
                        }
                    }
                }
            }
        }

*/

     getSettings(srcDataBuffer, KEY_ARRAY_MOTOR, kparts.dc_motor);
     getSettings(srcDataBuffer, KEY_ARRAY_STEPPER, kparts.stepper_motors);
     getSettings(srcDataBuffer, KEY_ARRAY_DOUT, kparts.dout);
     getSettings(srcDataBuffer, KEY_ARRAY_DIN, kparts.din);
     getSettings(srcDataBuffer, KEY_ARRAY_AIN, kparts.ain);
     getSettings(srcDataBuffer, KEY_ARRAY_CNT, kparts.counter);
     getSettings(srcDataBuffer, KEY_ARRAY_RGB, kparts.rgbSensor);
     getSettings(srcDataBuffer, KEY_ARRAY_DISTANCE, kparts.distanceSensor);
     
    // Get the DOUT device list 
 
        
      /*   

    // Get the DIN device list 
 
    // Get the AIN device list 

    // Get the COUNTER device list 
// Get the RGB Sensor device list 
        
    // Get the DISTANCE device list 

        // Get the STEPPER device list 
*/
     }
        return -1;
}



/**
 * \fn int getSettings(char * buffer, char * deviceType, struct device * mydevice)
 * \brief Extract the DRIVER settings from config buffer
 *
 * \param char * buffer, Buffer with config
 * \param char * deviceType, JSON KEY for Device array beginning (like:  "{'drivers'{'dout'")
 * \param struct device * mydevice, Structure to store the extracted values)
 *
 * \return -
 * 
 * output format:
 * 
 *  driverArray[partsNb] 
 *  |__ ID: 1
 *  |__ Interface: i2c
 *  |__ Driver
 *     |__ deviceId: 2
 *     |__ type: 
 *     |__ attributes
 *        |__ channel: 5
 * 
 * 
 */


int getSettings(char * buffer, char * deviceType, struct device * mydevice){
    struct jReadElement deviceList, myDevice, deviceDriver, driverAttributes, driverSubdriver;
    int deviceCount, deviceId, driverId, data;
       char strValue[25];
    int i;
    
    jRead((char *)buffer, deviceType, &deviceList );
     if(deviceList.dataType == JREAD_ARRAY ){
         deviceCount = deviceList.elements;       // Get the number of devices

         for(i=0;i<deviceCount;i++){
             jReadParam((char *)deviceList.pValue, KEY_OBJ_X_DEVICE, &myDevice, &i );

         // GET THE DEVICE ID
             deviceId=jRead_int((char *)myDevice.pValue, KEY_DEVICE_STR_ID, NULL);

             if(deviceId >= 0 && deviceId < MAX_DRIVERS_PER_TYPE){
                 // Get and save the driver ID
                 mydevice[deviceId].id = deviceId;

         // GET THE DEVICE INTERFACE    
             // Get and save the device interface
                 if(jRead_string((char *)myDevice.pValue, KEY_DEVICE_STR_INTERFACE, strValue, 25, NULL )>0){
                     strcpy(mydevice[deviceId].interface, strValue);
                 }

         // GET THE DEVICE DRIVER
             // Get the DRIVER settings
                 jRead((char *)myDevice.pValue, KEY_DEVICE_OBJ_DRIVER, &deviceDriver);

                 if(deviceDriver.dataType == JREAD_OBJECT){
                     // Get the device ID of the driver
                     driverId=jRead_int((char *)deviceDriver.pValue, KEY_DRIVER_STR_ID, NULL);

                     //Check that the driver ID is valid
                     if(driverId >= 0){
                         mydevice[deviceId].hw_driver.device_id = driverId;
                         if(jRead_string((char *)deviceDriver.pValue, KEY_DRIVER_STR_TYPE, strValue, 25, NULL )>0){
                             strcpy(mydevice[deviceId].hw_driver.device_type, strValue);
                         }              
                         // Get the ATTRIBUTES settings of driver
                         jRead((char *)deviceDriver.pValue, KEY_DRIVER_OBJ_ATTRIBUTES, &driverAttributes);
                         if(driverAttributes.dataType == JREAD_OBJECT){
                             // Get the channel attibute of the driver
                             data=jRead_int((char *)driverAttributes.pValue, KEY_DRIVER_STR_CHANNEL, NULL);
                             if(data>=0){
                                 mydevice[deviceId].hw_driver.attributes.device_channel = data;
                             }
                         }
                     // Get the SUBDRIVERS settings of driver
                         jRead((char *)deviceDriver.pValue, KEY_DRIVER_OBJ_SUBDRIVER, &driverSubdriver);
                         if(driverSubdriver.dataType == JREAD_OBJECT){
                             // Get the device ID of the driver
                             driverId=jRead_int((char *)driverSubdriver.pValue, KEY_DRIVER_STR_ID, NULL);

                             //Check that the driver ID is valid
                             if(driverId >= 0){
                                 mydevice[deviceId].hw_driver.sub_driver.device_id = driverId;
                                 if(jRead_string((char *)driverSubdriver.pValue, KEY_DRIVER_STR_TYPE, strValue, 25, NULL )>0){
                                     strcpy(mydevice[deviceId].hw_driver.sub_driver.device_type, strValue);
                                 }              
                                 // Get the ATTRIBUTES settings of driver
                                 jRead((char *)driverSubdriver.pValue, KEY_DRIVER_OBJ_ATTRIBUTES, &driverAttributes);
                                 if(driverAttributes.dataType == JREAD_OBJECT){
                                     // Get the channel attibute of the driver
                                     data=jRead_int((char *)driverAttributes.pValue, KEY_DRIVER_STR_CHANNEL, NULL);
                                     if(data>=0){
                                         mydevice[deviceId].hw_driver.sub_driver.attributes.device_channel = data;
                                     }
                                 }                        
                             }                                

                         }                        
                     } 
                 }
             }
         }
     #ifdef PRINT_INFO            
         printf("\SETTIGS LIST FOR %s [%d found]\n", deviceType, deviceCount);                       
         for(i=0;i<MAX_DRIVERS_PER_TYPE;i++){
             if(mydevice[i].id > -1)
                 printDriverData(i, &mydevice[i]);
         }
     #endif
    }    
}

/**
 * \fn int getDriverSettings(char * buffer, char * deviceType, struct device * mydevice)
 * \brief Extract the DRIVER settings from config buffer
 *
 * \param char * buffer, Buffer with config
 * \param char * deviceType, JSON KEY for Device array beginning (like:  "{'drivers'{'dout'")
 * \param struct device * mydevice, Structure to store the extracted values)
 *
 * \return -
 * 
 * search structure format:
 * 
 *  |__ Driver
 *     |__ deviceId: 2
 *     |__ type: 
 *     |__ attributes
 *        |__ channel: 5
 * 
 */
int getDriverSettings(char * buffer, char * deviceType, struct device * mydevice){
    
    
}
/**
 * \fn unsigned char printDriverData(int partsNb, struct device * device)
 * \brief Print a structured view of a device settings
 *
 * \param int partsNb, number of the field in the array driver
 * \param struct device * device, The driver to print
 *
 * \return -
 * 
 * output format:
 * 
 *  driverArray[partsNb] 
 *  |__ ID: 1
 *  |__ Interface: i2c
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
    
    printf("\n#%d \n |__ ID: %d\n |__ Interface: %s\n |__ Driver\n    |__ deviceId: %d\n    |__ type: %s\n    |__ attributes\n       |__ channel: %d\n    |__ sub-driver\n       |__ deviceId: %d\n       |__ type: %s\n       |__ attributes\n           |__ channel: %d\n    "
            , partsNb, devId, device->interface, device->hw_driver.device_id, device->hw_driver.device_type,
            device->hw_driver.attributes.device_channel, device->hw_driver.sub_driver.device_id, device->hw_driver.sub_driver.device_type, device->hw_driver.sub_driver.attributes.device_channel);  
}


/**
 * \fn unsigned char printDriverData(int partsNb, struct device * device)
 * \brief Print a structured view of a device settings
 *
 * \param int partsNb, number of the field in the array driver
 * \param struct device * device, The driver to print
 *
 * \return -
 * 
 * output format:
 * 
 * deviceArray[partsNb] 
 * |__ ID: 5
 *   |__ Type: _tca9546
 *   |__ Address: 0xe0
  *  |__ Attributes:{Not implemented}
 * 
 * 
 */

unsigned char printDeviceData(int deviceNb, devices_list * device){
    
    int devId = device->device_id;
    
    printf("\n#%d \n |__ ID: %d\n |__ Type: %s\n |__ Address: 0x%2x\n |__ Attributes:{Not implemented}\n",
           deviceNb, devId, device->type, device->address);        
}



/**
 * \fn void clearDriverSettings(void)
 * \brief Clear all the drivers structures with setting setting the ID to -1
 * \param -
 * \return -
 */

void clearDriverSettings(void){
    int i;
    // Init ID of device to "unknown"
    for(i=0;i<MAX_DRIVERS_PER_TYPE; i++){
        kparts.dout[i].id = -1;        
        kparts.din[i].id = -1;
        kparts.ain[i].id = -1;
        kparts.stepper_motors[i].id = -1;
        kparts.dc_motor[i].id = -1;
        kparts.distanceSensor[i].id = -1;
        kparts.rgbSensor[i].id = -1;
        kparts.counter[i].id = -1;
    }
}

/**
 * \fn void clearDeviceSettings(void)
 * \brief Clear all the devices structures with setting setting the ID to -1
 * \param -
 * \return -
 */
void clearDeviceSettings(void){
    int i;
    // Init ID of device to "unknown"
    for(i=0;i<MAX_BOARD_DEVICE; i++){
        boardDevice[i].device_id = -1;
    }
}