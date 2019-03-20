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
#include "fileIO.h"
  
int getSettings(char * buffer, char * deviceType, struct device * mydevice);
int getDriverSettings(struct jReadElement  * myDevice, hwDeviceDriver * hwDevice);
int getGenericHBridgeSettings(struct jReadElement  * myDevice, swDeviceDriver * swDevice);

unsigned char printDriverData(int partsNb, struct device * device);  // Print a formatted map of the drivers settings using "deviceMap.cfg"
unsigned char printDeviceData(int deviceNb, devices_list * device);  // Print a formatted map of the device IC setting using "devices.cfg"

void clearBoardSettings(kehopsParts * kparts);
void clearDeviceSettings(devices_list * boardDevice);

// Function to clear the drivers and devices structure
char LoadDevicesDescriptor(char * fileName, devices_list * boardDevice);
char LoadBoardDescriptor(char * fileName, kehopsParts * kparts);


/**
 * \fn char LoadDriversDescriptor(char * fileName)
 * \brief Extract the file config content of IC devices and store the JSON result convertion
 *  to the structure.
 * 
 * NOTE: The ID field of devices in the config file will define the field in the 
 * structure array. Not uses later.
 *
 * \param filename to open
 * \return error
 */

char LoadDevicesDescriptor(char * fileName, devices_list * boardDevice){
    struct jReadElement devList, deviceData, deviceSetting;
    int devicesCount, deviceId, settingCount;
    int i, j;
    char * srcDataBuffer;
    char strValue[25];

    // Read file and store the result in buffer
    OpenConfigFromFile(fileName, srcDataBuffer); 

    clearDeviceSettings(boardDevice);

    // Check that the file is not empty
    if(srcDataBuffer != NULL){

        // Get the device list 
        jRead((char *)srcDataBuffer, FILE_KEY_DEVICES, &devList );
        
        if(devList.dataType == JREAD_ARRAY ){
            devicesCount = devList.elements;       // Get the number of devices
            
            if(devicesCount > MAX_BOARD_DEVICE)
                printf("[driversDescriptor.c] !!! LoadDriversDescriptor() WARNING, MAX DEVICES LIMIT, ONLY THE %d FIRST ID WILL BE USED\n ", MAX_BOARD_DEVICE);
            
            //Get the device settings for each IC
            for(i=0; i < devicesCount; i++){ 
                
                jReadParam(devList.pValue, KEY_OBJ_X_DEVICE, &deviceData, &i);
                
                if(deviceData.dataType == JREAD_OBJECT){
                    deviceId=-1;
                    deviceId = jRead_int((char *)deviceData.pValue, KEY_DEVICE_STR_ID, NULL);
                    if(deviceId >= 0 && deviceId < MAX_BOARD_DEVICE){
                        boardDevice[deviceId].device_id=deviceId;
                        // Get the type (name) of the device
                        if(jRead_string((char *)deviceData.pValue, KEY_DRIVER_STR_TYPE, strValue, 25, NULL )>0)
                            strcpy(boardDevice[deviceId].type, strValue);
                        else strcpy(boardDevice[deviceId].type, "error");

                        // Get the bus address of the device, detect if address is a 
                        // string or a number, if string, convert to number
                        jRead((char *)deviceData.pValue, KEY_DRIVER_STR_ADDRESS, &deviceSetting);
                        if(deviceSetting.dataType == JREAD_STRING){
                            // Convert string to int
                            if(jRead_string((char *)deviceData.pValue, KEY_DRIVER_STR_ADDRESS, strValue, 25, NULL )>0)
                                boardDevice[deviceId].address = strtol(strValue, NULL, 0);
                            else boardDevice[deviceId].address=NULL;
                        }
                        else{
                                if(deviceSetting.dataType == JREAD_NUMBER){
                                    boardDevice[deviceId].address = jRead_double((char *)deviceData.pValue, KEY_DRIVER_STR_ADDRESS, NULL); 
                                }
                        } 
         /*               
                        
                        jRead((char *)deviceData.pValue, KEY_DEVICE_OBJ_ATTRIBUTES_DEVINIT, &deviceSetting);
                        if(deviceSetting.dataType == JREAD_ARRAY){
                            settingCount = deviceSetting.elements;
                          
                            for(j=0;j<settingCount;j++){
                                // Get the init data attributes
                                jReadParam((char *)deviceSetting.pValue, KEY_DEVICE_ARRAY_ATT_INIT_REGADDR, &data, &j);
                                 
                                if(data.dataType == JREAD_STRING){
                                    // Convert string to int
                                    if(jRead_string((char *)data.pValue, KEY_DEVICE_ARRAY_ATT_INIT_REGADDR, strValue, 25, &j )>0)
                                        boardDevice[deviceId].attributes.deviceInit[j].regAddr = strtol(strValue, NULL, 0);
                                    else boardDevice[deviceId].attributes.deviceInit[j].regAddr= NULL;
                                }
                                else{
                                        if(deviceSetting.dataType == JREAD_NUMBER){
                                            boardDevice[deviceId].attributes.deviceInit[j].regAddr = jRead_double((char *)data.pValue, KEY_DEVICE_ARRAY_ATT_INIT_REGADDR, &j); 
                                        }
                                }          
                               
                                jReadParam((char *)deviceSetting.pValue, KEY_DEVICE_ARRAY_ATT_INIT_REGDATA, &data, &j);
                                
                                if(data.dataType == JREAD_STRING){
                                    // Convert string to int
                                    if(jRead_string((char *)data.pValue, KEY_DEVICE_ARRAY_ATT_INIT_REGDATA, strValue, 25, &j )>0)
                                        boardDevice[deviceId].attributes.deviceInit[j].regData = strtol(strValue, NULL, 0);
                                    else boardDevice[deviceId].attributes.deviceInit[j].regData = NULL;
                                }
                                else{
                                        if(deviceSetting.dataType == JREAD_NUMBER){
                                            boardDevice[deviceId].attributes.deviceInit[j].regData = jRead_double((char *)data.pValue, KEY_DEVICE_ARRAY_ATT_INIT_REGDATA, &j); 
                                        }
                                }
                     
                            }
                             
                        }
           */
                        
                        #ifdef PRINT_INFO                     
                           // printDeviceData(i, &boardDevice[deviceId]);
                        #endif    
                  }
                }
            }
        }
    }

    return -1;
}

/**
 * \fn char LoadDevicesDescriptor(char * fileName)
 * \brief Extract the file content of Device parts from buffer and dispatch the settings to the
 * kehops structure.
 *
 * \param filename to open
 * \return pointer to the buffer with file content
 */

char LoadBoardDescriptor(char * fileName, kehopsParts * kparts){
    char *srcDataBuffer;
    
    //printf("MY FILE NAME: %s", &fileName);
       
    OpenConfigFromFile("deviceMap.cfg", srcDataBuffer);


        
    // Set the ID to "unknown"
    clearBoardSettings(kparts);

    
     if(srcDataBuffer != NULL){

        getSettings(srcDataBuffer, KEY_ARRAY_MOTOR, kparts->dc_motor);
        getSettings(srcDataBuffer, KEY_ARRAY_STEPPER, kparts->stepper_motors);
        getSettings(srcDataBuffer, KEY_ARRAY_DOUT, kparts->dout);
        getSettings(srcDataBuffer, KEY_ARRAY_DIN, kparts->din);
        getSettings(srcDataBuffer, KEY_ARRAY_AIN, kparts->ain);
        getSettings(srcDataBuffer, KEY_ARRAY_CNT, kparts->counter);
        getSettings(srcDataBuffer, KEY_ARRAY_RGB, kparts->rgbSensor);
        getSettings(srcDataBuffer, KEY_ARRAY_DISTANCE, kparts->distanceSensor);
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
    struct jReadElement deviceList, myDevice;
    int deviceCount, deviceId;
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

                if(!strcmp(mydevice[deviceId].interface, "I2C"))        
                    getDriverSettings(&myDevice, &mydevice[deviceId].hw_driver);
                
                if(!strcmp(mydevice[deviceId].interface, "generic_hbridge")){       
                    getGenericHBridgeSettings(&myDevice, &mydevice[deviceId].sw_driver);
//                    printf("\n------- ENABLE: ID %d  TYPE:  %s  ATT. CHANNEL: %d\n", mydevice[deviceId].sw_driver.dc_motor.enable.hw_driver.device_id, mydevice[deviceId].sw_driver.dc_motor.enable.hw_driver.device_type, mydevice[deviceId].sw_driver.dc_motor.enable.hw_driver.attributes.device_channel);
                }

             }
         }
        
     #ifdef PRINT_INFO            
         printf("\SETTIGS LIST FOR %s [%d found]\n", deviceType, deviceCount);                       
         for(i=0;i<MAX_DRIVERS_PER_TYPE;i++){
             if(mydevice[i].id > -1)
                 printBoardData(i, &mydevice[i]);
         }
     #endif
         
    }    
}

/**
 * \fn int getDriverSettings(struct jReadElement * myDevice, hwDeviceDriver * hwDevice)
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
int getDriverSettings(struct jReadElement * myDevice, hwDeviceDriver * hwDevice){
struct jReadElement deviceDriver, driverAttributes, driverSubdriver;
int deviceId, driverId, data;
char strValue[25];

// GET THE DEVICE DRIVER
// Get the DRIVER settings
    jRead((char *)myDevice->pValue, KEY_DEVICE_OBJ_DRIVER, &deviceDriver);

    if(deviceDriver.dataType == JREAD_OBJECT){
        // Get the device ID of the driver
        driverId=jRead_int((char *)deviceDriver.pValue, KEY_DRIVER_STR_ID, NULL);

        //Check that the driver ID is valid
        if(driverId >= 0){
            hwDevice->device_id = driverId;
            if(jRead_string((char *)deviceDriver.pValue, KEY_DRIVER_STR_TYPE, strValue, 25, NULL )>0){
                strcpy(hwDevice->device_type, strValue);
            }              
            // Get the ATTRIBUTES settings of driver
            jRead((char *)deviceDriver.pValue, KEY_DRIVER_OBJ_ATTRIBUTES, &driverAttributes);
            if(driverAttributes.dataType == JREAD_OBJECT){
                // Get the channel attibute of the driver
                data=jRead_int((char *)driverAttributes.pValue, KEY_DRIVER_STR_CHANNEL, NULL);
                if(data>=0){
                    hwDevice->attributes.device_channel = data;
                }
            }
            
         // Get the SUBDRIVERS settings of driver
            jRead((char *)deviceDriver.pValue, KEY_DRIVER_OBJ_SUBDRIVER, &driverSubdriver);
            if(driverSubdriver.dataType == JREAD_OBJECT){
                // Get the device ID of the driver
                driverId=jRead_int((char *)driverSubdriver.pValue, KEY_DRIVER_STR_ID, NULL);

                //Check that the driver ID is valid
                if(driverId >= 0){
                    hwDevice->sub_driver.device_id = driverId;
                    if(jRead_string((char *)driverSubdriver.pValue, KEY_DRIVER_STR_TYPE, strValue, 25, NULL )>0){
                        strcpy(hwDevice->sub_driver.device_type, strValue);
                    }              
                    // Get the ATTRIBUTES settings of driver
                    jRead((char *)driverSubdriver.pValue, KEY_DRIVER_OBJ_ATTRIBUTES, &driverAttributes);
                    if(driverAttributes.dataType == JREAD_OBJECT){
                        // Get the channel attibute of the driver
                        data=jRead_int((char *)driverAttributes.pValue, KEY_DRIVER_STR_CHANNEL, NULL);
                       if(data>=0){
                            hwDevice->sub_driver.attributes.device_channel = data;
                       }
                    }                        
                }                                
            }else
                hwDevice->sub_driver.device_id = -1;
        } 
    }  
     return 0;
}


/**
 * \fn int getGenericHBridgeSettings(struct jReadElement  * myDevice, swDeviceDriver * swDevice)
 * \brief Extract the GENERIC H BRIDGE composed with many drivers settings
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
int getGenericHBridgeSettings(struct jReadElement  * myDevice, swDeviceDriver * swDevice){
struct jReadElement deviceDriver, deviceAttributes, driverAttributes;
int deviceId, driverId, data;
char strValue[25];

    // Get the ATTRIBUTES settings of driver
    jRead((char *)myDevice->pValue, KEY_DRIVER_OBJ_ATTRIBUTES, &deviceAttributes);

    
    if(deviceAttributes.dataType == JREAD_OBJECT){
        // Get the channel attibute of the driver
        // Get the ATTRIBUTES ENABLE settings of driver
        
// GET THE ENABLE ATTRIBUTES        
        jRead((char *)deviceAttributes.pValue, KEY_DEVICE_ATTRIBUTES_EN, &deviceDriver);
        if(deviceDriver.dataType == JREAD_OBJECT){
            
            // GET THE DEVICE INTERFACE    
            // Get and save the device interface
            if(jRead_string((char *)deviceDriver.pValue, KEY_DEVICE_STR_INTERFACE, strValue, 25, NULL )>0){
                strcpy(swDevice->dc_motor.enable.interface, strValue);
            }            
            if(!strcmp(swDevice->dc_motor.enable.interface, "I2C"))
                getDriverSettings(&deviceDriver, &swDevice->dc_motor.enable.hw_driver);
        }
        
// GET THE SPEED ATTRIBUTES        
        jRead((char *)deviceAttributes.pValue, KEY_DEVICE_ATTRIBUTES_SPEED, &deviceDriver);
        if(deviceDriver.dataType == JREAD_OBJECT){
            
            // GET THE DEVICE INTERFACE    
            // Get and save the device interface
            if(jRead_string((char *)deviceDriver.pValue, KEY_DEVICE_STR_INTERFACE, strValue, 25, NULL )>0){
                strcpy(swDevice->dc_motor.speed.interface, strValue);
            }            
            if(!strcmp(swDevice->dc_motor.speed.interface, "I2C"))
                getDriverSettings(&deviceDriver, &swDevice->dc_motor.speed.hw_driver);
        }
        
// GET THE CW ATTRIBUTES        
        jRead((char *)deviceAttributes.pValue, KEY_DEVICEATTRIBUTES_CW, &deviceDriver);
        if(deviceDriver.dataType == JREAD_OBJECT){
            
            // GET THE DEVICE INTERFACE    
            // Get and save the device interface
            if(jRead_string((char *)deviceDriver.pValue, KEY_DEVICE_STR_INTERFACE, strValue, 25, NULL )>0){
                strcpy(swDevice->dc_motor.cw.interface, strValue);
            }            
            if(!strcmp(swDevice->dc_motor.cw.interface, "I2C"))
                getDriverSettings(&deviceDriver, &swDevice->dc_motor.cw.hw_driver);
        }

// GET THE CCW ATTRIBUTES        
        jRead((char *)deviceAttributes.pValue, KEY_DEVICE_ATTRIBUTES_CCW, &deviceDriver);
        if(deviceDriver.dataType == JREAD_OBJECT){
            
            // GET THE DEVICE INTERFACE    
            // Get and save the device interface§
            if(jRead_string((char *)deviceDriver.pValue, KEY_DEVICE_STR_INTERFACE, strValue, 25, NULL )>0){
                strcpy(swDevice->dc_motor.ccw.interface, strValue);
            }            
            if(!strcmp(swDevice->dc_motor.ccw.interface, "I2C"))
                getDriverSettings(&deviceDriver, &swDevice->dc_motor.ccw.hw_driver);
        }
        
    }
            
 return 0;   
}
/**
 * \fn unsigned char printBoardData(int partsNb, struct device * device)
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

unsigned char printBoardData(int partsNb, struct device * device){
    
    int devId = device->id;
    
    if(!strcmp(device->interface, "I2C")){       
        printf("\n#%d \n |__ ID: %d\n |__ Interface: %s\n |__ Driver\n    |__ deviceId: %d\n    |__ type: %s\n    |__ attributes\n       |__ channel: %d\n"
            , partsNb, devId, device->interface, device->hw_driver.device_id, device->hw_driver.device_type, device->hw_driver.attributes.device_channel);  
        if(device->hw_driver.sub_driver.device_id >= 0){
            printf("    |__ sub-driver\n       |__ deviceId: %d\n       |__ type: %s\n       |__ attributes\n           |__ channel: %d\n    ", 
                    device->hw_driver.sub_driver.device_id, device->hw_driver.sub_driver.device_type, device->hw_driver.sub_driver.attributes.device_channel);
        }
    }
    else
        if(!strcmp(device->interface, "generic_hbridge")){       
            printf("\n#%d \n |__ ID: %d\n |__ Interface: %s\n |__ Attributes\n", partsNb, devId, device->interface);  
            
            if(!strcmp(device->sw_driver.dc_motor.enable.interface, "I2C")){
                printf("    |__ Enable\n       |__ Interface: %s\n       |__ Driver\n         |__ deviceId: %d\n         |__ type: %s\n         |__ attributes\n            |__ channel: %d\n"
                , device->sw_driver.dc_motor.enable.interface, device->sw_driver.dc_motor.enable.hw_driver.device_id, device->sw_driver.dc_motor.enable.hw_driver.device_type, device->sw_driver.dc_motor.enable.hw_driver.attributes.device_channel);  
                if(device->sw_driver.dc_motor.enable.hw_driver.sub_driver.device_id >= 0){
                    printf("         |__ sub-driver\n            |__ deviceId: %d\n            |__ type: %s\n            |__ attributes\n                |__ channel: %d\n    ", 
                    device->sw_driver.dc_motor.enable.hw_driver.sub_driver.device_id, device->sw_driver.dc_motor.enable.hw_driver.sub_driver.device_type, device->sw_driver.dc_motor.enable.hw_driver.sub_driver.attributes.device_channel);
                }
                
                printf("    |__ CW\n       |__ Interface: %s\n       |__ Driver\n         |__ deviceId: %d\n         |__ type: %s\n         |__ attributes\n            |__ channel: %d\n"
                , device->sw_driver.dc_motor.cw.interface, device->sw_driver.dc_motor.cw.hw_driver.device_id, device->sw_driver.dc_motor.cw.hw_driver.device_type, device->sw_driver.dc_motor.cw.hw_driver.attributes.device_channel);  
                if(device->sw_driver.dc_motor.cw.hw_driver.sub_driver.device_id >= 0){
                    printf("       |__ sub-driver\n          |__ deviceId: %d\n          |__ type: %s\n          |__ attributes\n              |__ channel: %d\n    ", 
                    device->sw_driver.dc_motor.cw.hw_driver.sub_driver.device_id, device->sw_driver.dc_motor.cw.hw_driver.sub_driver.device_type, device->sw_driver.dc_motor.cw.hw_driver.sub_driver.attributes.device_channel);
                }
                                
                printf("    |__ CCW\n       |__ Interface: %s\n       |__ Driver\n        |__ deviceId: %d\n         |__ type: %s\n         |__ attributes\n            |__ channel: %d\n"
                , device->sw_driver.dc_motor.ccw.interface, device->sw_driver.dc_motor.ccw.hw_driver.device_id, device->sw_driver.dc_motor.ccw.hw_driver.device_type, device->sw_driver.dc_motor.ccw.hw_driver.attributes.device_channel);  
                if(device->sw_driver.dc_motor.ccw.hw_driver.sub_driver.device_id >= 0){
                    printf("         |__ sub-driver\n            |__ deviceId: %d\n            |__ type: %s\n            |__ attributes\n                |__ channel: %d\n    ", 
                    device->sw_driver.dc_motor.ccw.hw_driver.sub_driver.device_id, device->sw_driver.dc_motor.ccw.hw_driver.sub_driver.device_type, device->sw_driver.dc_motor.ccw.hw_driver.sub_driver.attributes.device_channel);
                }
                                                
                printf("    |__ Speed\n       |__ Interface: %s\n       |__ Driver\n         |__ deviceId: %d\n         |__ type: %s\n         |__ attributes\n            |__ channel: %d\n"
                , device->sw_driver.dc_motor.speed.interface, device->sw_driver.dc_motor.speed.hw_driver.device_id, device->sw_driver.dc_motor.speed.hw_driver.device_type, device->sw_driver.dc_motor.speed.hw_driver.attributes.device_channel);  
                if(device->sw_driver.dc_motor.speed.hw_driver.sub_driver.device_id >= 0){
                    printf("         |__ sub-driver\n            |__ deviceId: %d\n            |__ type: %s\n            |__ attributes\n                |__ channel: %d\n    ", 
                    device->sw_driver.dc_motor.speed.hw_driver.sub_driver.device_id, device->sw_driver.dc_motor.speed.hw_driver.sub_driver.device_type, device->sw_driver.dc_motor.speed.hw_driver.sub_driver.attributes.device_channel);
                }
            }
        }    
}


/**
 * \fn unsigned char printDeviceData(int partsNb, struct device * device)
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
    
    printf("\n#%d \n |__ ID: %d\n |__ Type: %s\n |__ Address: 0x%2x\n |__ Attributes:\n     |__deviceInit\n        |__RegAdr: %d    RegData: %d\n",
           deviceNb, devId, device->type, device->address, device->attributes.deviceInit[0].regAddr, device->attributes.deviceInit[0].regData);        
}



/**
 * \fn void clearDriverSettings(void)
 * \brief Clear all the drivers structures with setting setting the ID to -1
 * \param -
 * \return -
 */

void clearBoardSettings(kehopsParts * kparts){
    int i;
    // Init ID of device to "unknown"
    for(i=0;i<MAX_DRIVERS_PER_TYPE; i++){
        kparts->dout[i].id=-1;
        kparts->dout[i].hw_driver.attributes.device_channel = -1;
        kparts->dout[i].hw_driver.sub_driver.device_id=-1;
        kparts->dout[i].hw_driver.sub_driver.attributes.device_channel=-1;
        
        kparts->din[i].id = -1;
        kparts->din[i].hw_driver.attributes.device_channel = -1;
        kparts->din[i].hw_driver.sub_driver.device_id=-1;
        kparts->din[i].hw_driver.sub_driver.attributes.device_channel=-1;
        
        kparts->ain[i].id = -1;
        kparts->ain[i].hw_driver.attributes.device_channel = -1;
        kparts->ain[i].hw_driver.sub_driver.device_id=-1;
        kparts->ain[i].hw_driver.sub_driver.attributes.device_channel=-1;
             
        kparts->stepper_motors[i].id = -1;
        kparts->stepper_motors[i].hw_driver.attributes.device_channel = -1;
        kparts->stepper_motors[i].hw_driver.sub_driver.device_id=-1;
        kparts->stepper_motors[i].hw_driver.sub_driver.attributes.device_channel=-1;
        
        kparts->dc_motor[i].id = -1;
        kparts->dc_motor[i].hw_driver.attributes.device_channel = -1;
        kparts->dc_motor[i].hw_driver.sub_driver.device_id=-1;
        kparts->dc_motor[i].hw_driver.sub_driver.attributes.device_channel=-1;
        
        kparts->distanceSensor[i].id = -1;
        kparts->distanceSensor[i].hw_driver.attributes.device_channel = -1;
        kparts->distanceSensor[i].hw_driver.sub_driver.device_id=-1;
        kparts->distanceSensor[i].hw_driver.sub_driver.attributes.device_channel=-1;
        
        kparts->rgbSensor[i].id = -1;
        kparts->rgbSensor[i].hw_driver.attributes.device_channel = -1;
        kparts->rgbSensor[i].hw_driver.sub_driver.device_id=-1;
        kparts->rgbSensor[i].hw_driver.sub_driver.attributes.device_channel=-1;
        
        kparts->counter[i].id = -1;
        kparts->counter[i].hw_driver.attributes.device_channel = -1;
        kparts->counter[i].hw_driver.sub_driver.device_id=-1;
        kparts->counter[i].hw_driver.sub_driver.attributes.device_channel=-1;
    }
}

/**
 * \fn void clearDeviceSettings(void)
 * \brief Clear all the devices structures with setting setting the ID to -1
 * \param -
 * \return -
 */
void clearDeviceSettings(devices_list * boardDevice){
    int i;
    // Init ID of device to "unknown"
    for(i=0;i<MAX_BOARD_DEVICE; i++){
        boardDevice[i].device_id = -1;
    }
}


/**
 * \fn char LoadKehopsHardwareMap(kehopsParts * parts)
 * \brief Clear all the devices structures with setting setting the ID to -1
 * \param kehopsParts * parts, pointer to the hardwareMap structure use for the drivers
 * \return error
 */
char LoadKehopsHardwareMap(kehopsParts * parts){
    // Create structure for devices on the board
    devices_list boardDevice[MAX_BOARD_DEVICE];
    
    //LoadDevicesDescriptor("devices.cfg", boardDevice);  
    printf("\nsdknhfksjhdfkjhsadkfjhsadf\n");
   
    LoadBoardDescriptor("deviceMap.cfg", parts);
}
