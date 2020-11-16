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

//#define PRINT_MAP_INFO

#define MAX_MQTT_BUFF 32768

// Library dependency
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "jRead.h"
#include "jWrite.h"
#include "deviceMapping_jsonKeys.h"
#include "deviceMapping.h"

char * getDriverTypeByName(char * name);

int getSettings(char * buffer, char * deviceType, struct device * mydevice, devices_list * icDevice);
int getDriverSettings(struct jReadElement  * myDevice, hwDeviceDriver * hwDevice, devices_list * icDevice);
int getGenericHBridgeSettings(struct jReadElement  * myDevice, swDeviceDriver * swDevice, devices_list * icDevice);

unsigned char printDriverData(int partsNb, struct device * device);  // Print a formatted map of the drivers settings using "deviceMap.cfg"
unsigned char printDeviceData(int deviceNb, devices_list * device);  // Print a formatted map of the device IC setting using "devices.cfg"

void clearBoardSettings(kehopsParts * kparts);
void clearDeviceSettings(devices_list * boardDevice);

// Function to clear the drivers and devices structure
char LoadDevicesDescriptor(char * srcDataBuffer, devices_list * boardDevice);
char LoadBoardDescriptor(char * srcDataBuffer, kehopsParts * kparts, devices_list * boardDevice);

/**
 * \fn char LoadDevicesDescriptor(char * fileName)
 * \brief Extract the file config content of IC devices and store the JSON result convertion
 *  to the structure.
 * 
 * NOTE: The ID field of devices in the config file will define the field in the 
 * structure array. Not uses later.
 *
 * \param filename to open
 * \return error
 */

char LoadDevicesDescriptor(char * srcDataBuffer, devices_list * boardDevice){
    struct jReadElement devList, deviceData, deviceSetting, deviceInit;
    int devicesCount, deviceAddress, settingCount, data;
    int i, j;
    char strValue[25];

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
                    deviceAddress=-1;
                    
                    // Get the name of the integrated circuit 
                    if(jRead_string((char *)deviceData.pValue, KEY_DRIVER_STR_NAME, strValue, 25, NULL)>0)
                        strcpy(boardDevice[i].name, strValue);
                    else strcpy(boardDevice[i].name, "error");
                    
                    // Get the bus address of the device, detect if address is a 
                    // string or a number, if string, convert to number
                    
                    jRead((char *)deviceData.pValue, KEY_DRIVER_STR_ADDRESS, &deviceSetting);
                    if(deviceSetting.dataType == JREAD_STRING){
                        // Convert string to int
                        if(jRead_string((char *)deviceData.pValue, KEY_DRIVER_STR_ADDRESS, strValue, 25, NULL )>0)
                            deviceAddress = strtol(strValue, NULL, 0);
                        else 
                            deviceAddress = -1;
                    }
                    else{
                            if(deviceSetting.dataType == JREAD_NUMBER)
                                deviceAddress = jRead_int((char *)deviceData.pValue, KEY_DRIVER_STR_ADDRESS, NULL); 
                            else
                                deviceAddress = -1;
                    }                    

                    if(deviceAddress >= 0){
                        boardDevice[i].address = deviceAddress;
                        // Get the type of the device
                        if(jRead_string((char *)deviceData.pValue, KEY_DRIVER_STR_TYPE, strValue, 25, NULL )>0)
                            strcpy(boardDevice[i].type, strValue);
                        else strcpy(boardDevice[i].type, "error");
                        

                        // Get the frequency attributes for frequency                       
                        boardDevice[i].attributes.frequency = jRead_int((char *)deviceData.pValue, KEY_DEVICE_OBJ_ATTRIBUTES_FREQUENCY, NULL); 
                        
                        // Get the frequency attributes for width and height
                        boardDevice[i].attributes.width = jRead_int((char *)deviceData.pValue, KEY_DEVICE_OBJ_ATTRIBUTES_WIDTH, NULL); 
                        boardDevice[i].attributes.height = jRead_int((char *)deviceData.pValue, KEY_DEVICE_OBJ_ATTRIBUTES_HEIGHT, NULL); 
                        
                        // Get the init data attributes for devInit                       
                        jRead((char *)deviceData.pValue, KEY_DEVICE_OBJ_ATTRIBUTES_DEVINIT, &deviceSetting);
                        if(deviceSetting.dataType == JREAD_ARRAY){
                            settingCount = deviceSetting.elements;                          
                          
                            for(j=0;j<settingCount;j++){
                                jReadParam((char *)deviceSetting.pValue, KEY_DEVICE_ARRAY_ATT_INIT_REGADDR, &deviceInit, &j);
                                 
                                if(deviceInit.dataType == JREAD_STRING){
                                    // Convert string to int
                                    if(jRead_string((char *)deviceSetting.pValue, KEY_DEVICE_ARRAY_ATT_INIT_REGADDR, strValue, 25, &j )>0)
                                        boardDevice[i].attributes.deviceInit[j].regAddr = strtol(strValue, NULL, 0);
                                    else boardDevice[i].attributes.deviceInit[j].regAddr= -1;
                                }
                                else{
                                        if(deviceInit.dataType == JREAD_NUMBER){
                                            boardDevice[i].attributes.deviceInit[j].regAddr = jRead_double((char *)deviceSetting.pValue, KEY_DEVICE_ARRAY_ATT_INIT_REGADDR, &j); 
                                        }
                                        else boardDevice[i].attributes.deviceInit[j].regAddr= -1;
                                }          
                               
                                jReadParam((char *)deviceSetting.pValue, KEY_DEVICE_ARRAY_ATT_INIT_REGDATA, &deviceInit, &j);
                                
                                if(deviceInit.dataType == JREAD_STRING){
                                    // Convert string to int
                                    if(jRead_string((char *)deviceSetting.pValue, KEY_DEVICE_ARRAY_ATT_INIT_REGDATA, strValue, 25, &j )>0)
                                        boardDevice[i].attributes.deviceInit[j].regData = strtol(strValue, NULL, 0);
                                    else boardDevice[i].attributes.deviceInit[j].regData = -1;
                                }
                                else{
                                        if(deviceInit.dataType == JREAD_NUMBER){
                                            boardDevice[i].attributes.deviceInit[j].regData = jRead_double((char *)deviceSetting.pValue, KEY_DEVICE_ARRAY_ATT_INIT_REGDATA, &j); 
                                        }else boardDevice[i].attributes.deviceInit[j].regData= -1;
                                }
                     
                            }
                             
                        }                        
                  
                        // Get the bus address of the device, detect if address is a 
                        // string or a number, if string, convert to number
                        jRead((char *)deviceData.pValue, KEY_DRIVER_OBJ_SUBDRIVER, &deviceSetting);
                        if(deviceSetting.dataType == JREAD_OBJECT){
                            if(jRead_string((char *)deviceSetting.pValue, KEY_DRIVER_STR_NAME, strValue, 25, NULL )>0){
                                strcpy(boardDevice[i].sub_driver.name, strValue);
                            } else strcpy(boardDevice[i].sub_driver.name, "");


                            // Get the ATTRIBUTES settings of sub driver
                            jRead((char *)deviceSetting.pValue, KEY_DRIVER_OBJ_ATTRIBUTES, &deviceSetting);
                            if(deviceSetting.dataType == JREAD_OBJECT){
                                // Get the channel attibute of the driver
                                data=jRead_int((char *)deviceSetting.pValue, KEY_DRIVER_STR_CHANNEL, NULL);
                                if(data>=0)
                                    boardDevice[i].sub_driver.attributes.device_channel = data;
                                
                                // Get the activate value attibute of the sub driver
                                data=jRead_int((char *)deviceSetting.pValue, KEY_DRIVER_STR_ACTIVATE, NULL);
                                if(data>=0)
                                    boardDevice[i].sub_driver.attributes.onActivate = data;
                                
                                // Get the deactivate value attibute of the sub driver
                                data=jRead_int((char *)deviceSetting.pValue, KEY_DRIVER_STR_DEACTIVATE, NULL);
                                if(data>=0)
                                    boardDevice[i].sub_driver.attributes.onDeactivate = data;                                
                            }
                        }
                        else 
                            strcpy(boardDevice[i].sub_driver.name, "");
                        
                        #ifdef PRINT_MAP_INFO                     
                            printDeviceData(i, &boardDevice[i]);
                        #endif    
                  }
                }
            }
        }
    }

    return -1;
}

/**
 * \fn char LoadBoardDescriptor(char * fileName)
 * \brief Extract the file content of Device parts from buffer and dispatch the settings to the
 * kehops structure.
 *
 * \param filename to open
 * \return pointer to the buffer with file content
 */

char LoadBoardDescriptor(char * srcDataBuffer, kehopsParts * kparts, devices_list * boardDevice){

    // Set the ID to "unknown"
    clearBoardSettings(kparts);
    
     if(srcDataBuffer != NULL){
        getSettings(srcDataBuffer, KEY_ARRAY_MOTOR, kparts->dc_motor, &boardDevice[0]);
        getSettings(srcDataBuffer, KEY_ARRAY_STEPPER, kparts->stepper_motors, &boardDevice[0]);
        getSettings(srcDataBuffer, KEY_ARRAY_DOUT, kparts->dout, &boardDevice[0]);
        getSettings(srcDataBuffer, KEY_ARRAY_DIN, kparts->din, &boardDevice[0]);
        getSettings(srcDataBuffer, KEY_ARRAY_AIN, kparts->ain, &boardDevice[0]);
        getSettings(srcDataBuffer, KEY_ARRAY_CNT_FREQ, kparts->freqCounter, &boardDevice[0]);
        getSettings(srcDataBuffer, KEY_ARRAY_CNT_PULSES, kparts->pulsesCounter, &boardDevice[0]);
        getSettings(srcDataBuffer, KEY_ARRAY_RGB, kparts->rgbSensor, &boardDevice[0]);
        getSettings(srcDataBuffer, KEY_ARRAY_DISTANCE, kparts->distanceSensor, &boardDevice[0]);
        getSettings(srcDataBuffer, KEY_ARRAY_AOUT, kparts->aout, &boardDevice[0]);
        getSettings(srcDataBuffer, KEY_ARRAY_DISPLAY, kparts->gfxDisplay, &boardDevice[0]);
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
 *  |__ Interface: I2C
 *  |__ Driver
 *     |__ address: 0x02
 *     |__ type: PCA9685
 *     |__ attributes
 *        |__ channel: 5 
 */

int getSettings(char * buffer, char * deviceType, struct device * mydevice, devices_list * icDevice){
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
            deviceId=jRead_int((char *)myDevice.pValue, KEY_DRIVER_STR_ID, NULL);

            if(deviceId >= 0 && deviceId < MAX_DRIVERS_PER_TYPE){
                // Get and save the driver ID
                mydevice[deviceId].id = deviceId;

        // GET THE DEVICE INTERFACE    
            // Get and save the device interface
                if(jRead_string((char *)myDevice.pValue, KEY_DRIVER_STR_INTERFACE, strValue, 25, NULL )>0){
                    strcpy(mydevice[deviceId].interface, strValue);
                }

                if(!strcmp(mydevice[deviceId].interface, "I2C"))        
                    getDriverSettings(&myDevice, &mydevice[deviceId].hw_driver, icDevice);
                
                if(!strcmp(mydevice[deviceId].interface, "generic_hbridge")){       
                    getGenericHBridgeSettings(&myDevice, &mydevice[deviceId].sw_driver, icDevice);
                }

             }
         }
        
     #ifdef PRINT_MAP_INFO            
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
int getDriverSettings(struct jReadElement * myDevice, hwDeviceDriver * hwDevice, devices_list * icDevice){
struct jReadElement deviceDriver, driverAttributes, driverSubdriver, deviceSetting;
int driverAddress, data, i, j;
char strValue[25];

// GET THE DEVICE DRIVER
// Get the DRIVER settings
    jRead((char *)myDevice->pValue, KEY_DEVICE_OBJ_DRIVER, &deviceDriver);
    if(deviceDriver.dataType == JREAD_OBJECT){
        // Get the device BUS ADDRESS AND THE TYPE OF IC 
        // in the stored 
        driverAddress = -1;
        
        jRead((char *)deviceDriver.pValue, KEY_DRIVER_STR_NAME, &deviceSetting);
        if(deviceSetting.dataType == JREAD_STRING){
            if(jRead_string((char *)deviceDriver.pValue, KEY_DRIVER_STR_NAME, strValue, 25, NULL )>0){
                for(i=0;i<MAX_BOARD_DEVICE;i++){
                    if(!strcmp(strValue, icDevice[i].name)){
                        strcpy(hwDevice->name, icDevice[i].name);         // !!!!!!! DEBUG
                        strcpy(hwDevice->type, getDriverTypeByName(icDevice[i].name));
                        driverAddress = icDevice[i].address;
                      
                        // Get the ATTRIBUTES settings of driver
                        jRead((char *)deviceDriver.pValue, KEY_DRIVER_OBJ_ATTRIBUTES, &driverAttributes);
                        if(driverAttributes.dataType == JREAD_OBJECT){
                            // Get the channel attibute of the driver
                            data=jRead_int((char *)driverAttributes.pValue, KEY_DRIVER_STR_CHANNEL, NULL);
                            if(data>=0){
                                hwDevice->attributes.device_channel = data;
                            }
                            /*
                            // Get the value attibute of the driver
                            data=jRead_int((char *)driverAttributes.pValue, KEY_DRIVER_STR_STATE, NULL);
                            if(data>=0){
                                hwDevice->attributes.value = data;
                            } 
                             */                           
                        }
                    }
                }
            }
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
int getGenericHBridgeSettings(struct jReadElement  * myDevice, swDeviceDriver * swDevice, devices_list * icDevice){
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
            if(jRead_string((char *)deviceDriver.pValue, KEY_DRIVER_STR_INTERFACE, strValue, 25, NULL )>0){
                strcpy(swDevice->dc_motor.enable.interface, strValue);
            }            
            if(!strcmp(swDevice->dc_motor.enable.interface, "I2C"))
                getDriverSettings(&deviceDriver, &swDevice->dc_motor.enable.hw_driver, icDevice);
        }
        
// GET THE SPEED ATTRIBUTES        
        jRead((char *)deviceAttributes.pValue, KEY_DEVICE_ATTRIBUTES_SPEED, &deviceDriver);
        if(deviceDriver.dataType == JREAD_OBJECT){
            
            // GET THE DEVICE INTERFACE    
            // Get and save the device interface
            if(jRead_string((char *)deviceDriver.pValue, KEY_DRIVER_STR_INTERFACE, strValue, 25, NULL )>0){
                strcpy(swDevice->dc_motor.speed.interface, strValue);
            }            
            if(!strcmp(swDevice->dc_motor.speed.interface, "I2C"))
                getDriverSettings(&deviceDriver, &swDevice->dc_motor.speed.hw_driver, icDevice);
        }
        
// GET THE CW ATTRIBUTES        
        jRead((char *)deviceAttributes.pValue, KEY_DEVICEATTRIBUTES_CW, &deviceDriver);
        if(deviceDriver.dataType == JREAD_OBJECT){
            
            // GET THE DEVICE INTERFACE    
            // Get and save the device interface
            if(jRead_string((char *)deviceDriver.pValue, KEY_DRIVER_STR_INTERFACE, strValue, 25, NULL )>0){
                strcpy(swDevice->dc_motor.cw.interface, strValue);
            }            
            if(!strcmp(swDevice->dc_motor.cw.interface, "I2C"))
                getDriverSettings(&deviceDriver, &swDevice->dc_motor.cw.hw_driver, icDevice);
        }

// GET THE CCW ATTRIBUTES        
        jRead((char *)deviceAttributes.pValue, KEY_DEVICE_ATTRIBUTES_CCW, &deviceDriver);
        if(deviceDriver.dataType == JREAD_OBJECT){
            
            // GET THE DEVICE INTERFACE    
            // Get and save the device interface§
            if(jRead_string((char *)deviceDriver.pValue, KEY_DRIVER_STR_INTERFACE, strValue, 25, NULL )>0){
                strcpy(swDevice->dc_motor.ccw.interface, strValue);
            }            
            if(!strcmp(swDevice->dc_motor.ccw.interface, "I2C"))
                getDriverSettings(&deviceDriver, &swDevice->dc_motor.ccw.hw_driver, icDevice);
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
        printf("\n#%d \n |__ ID: %d\n |__ Interface: %s\n |__ Driver\n    |__ name: %s\n    |__ type: %s\n    |__ attributes\n       |__ channel: %d\n"
            , partsNb, devId, device->interface, device->hw_driver.name,device->hw_driver.type, device->hw_driver.attributes.device_channel);  
        /*
        if(device->hw_driver.sub_driver.address >= 0){
            printf("    |__ sub-driver\n       |__ deviceAddress: 0x%2x\n       |__ type: %s\n       |__ attributes\n           |__ channel: %d\n    ", 
                    device->hw_driver.sub_driver.address, device->hw_driver.sub_driver.device_type, device->hw_driver.sub_driver.attributes.device_channel);
        }
         */
    }
    else
        if(!strcmp(device->interface, "generic_hbridge")){       
            printf("\n#%d \n |__ ID: %d\n |__ Interface: %s\n |__ Attributes\n", partsNb, devId, device->interface);  
            
            if(!strcmp(device->sw_driver.dc_motor.enable.interface, "I2C")){
                printf("    |__ Enable\n       |__ Interface: %s\n       |__ Driver\n         |__ name: %s\n         |__ attributes\n            |__ channel: %d\n"
                , device->sw_driver.dc_motor.enable.interface, device->sw_driver.dc_motor.enable.hw_driver.name, device->sw_driver.dc_motor.enable.hw_driver.attributes.device_channel);  

                
                printf("    |__ CW\n       |__ Interface: %s\n       |__ Driver\n         |__ name: %s\n         |__ attributes\n            |__ channel: %d\n"
                , device->sw_driver.dc_motor.cw.interface, device->sw_driver.dc_motor.cw.hw_driver.name, device->sw_driver.dc_motor.cw.hw_driver.attributes.device_channel);  

                                
                printf("    |__ CCW\n       |__ Interface: %s\n       |__ Driver\n        |__ name: %s\n         |__ attributes\n            |__ channel: %d\n"
                , device->sw_driver.dc_motor.ccw.interface, device->sw_driver.dc_motor.ccw.hw_driver.name, device->sw_driver.dc_motor.ccw.hw_driver.attributes.device_channel);  
                                                
                printf("    |__ Speed\n       |__ Interface: %s\n       |__ Driver\n         |__ name: %s\n         |__ attributes\n            |__ channel: %d\n"
                , device->sw_driver.dc_motor.speed.interface, device->sw_driver.dc_motor.speed.hw_driver.name, device->sw_driver.dc_motor.speed.hw_driver.attributes.device_channel);  

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
 *    |__ Name: IC5
 *    |__ Type: tca9546
 *    |__ Address: 0xe0
 *    |__ Sub-driver:
 *       |__ Name: IC2
 *       |__ Attributes: 
 *          |__ Channel: 1
 *          |__ Value:  0
 */

unsigned char printDeviceData(int deviceNb, devices_list * device){
    int i,j;
    
    printf("\n#%d \n |__ Name: %s\n |__ Type: %s\n |__ Address: 0x%2x\n", deviceNb,device->name, device->type, device->address);
    if(device->attributes.deviceInit[0].regAddr > 0){
        printf(" |__ Attributes:\n     |__deviceInit\n");
        for(i=0;i<32;i++){
            if(device->attributes.deviceInit[i].regAddr > 0){
                 printf("        |__RegAdr: %d    RegData: %d\n",
               device->attributes.deviceInit[i].regAddr, device->attributes.deviceInit[i].regData);
            }      
        }
    }
    
    if(strcmp(device->sub_driver.name, "")){
        // Check if the IC use a sub-driver
    printf(" |__ Sub-driver:\n     |__Name: %s \n     |__Attribute:\n        |__Channel %d\n        |__onActivate %d\n        |__onDeactivate %d\n",
            device->sub_driver.name, device->sub_driver.attributes.device_channel, device->sub_driver.attributes.onActivate, device->sub_driver.attributes.onDeactivate);
    }
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
        
        kparts->aout[i].id=-1;
        kparts->aout[i].hw_driver.attributes.device_channel = -1;
        
        kparts->din[i].id = -1;
        kparts->din[i].hw_driver.attributes.device_channel = -1;
        
        kparts->ain[i].id = -1;
        kparts->ain[i].hw_driver.attributes.device_channel = -1;
             
        kparts->stepper_motors[i].id = -1;
        kparts->stepper_motors[i].hw_driver.attributes.device_channel = -1;
        
        kparts->dc_motor[i].id = -1;
        kparts->dc_motor[i].hw_driver.attributes.device_channel = -1;
        
        kparts->distanceSensor[i].id = -1;
        kparts->distanceSensor[i].hw_driver.attributes.device_channel = -1;
        
        kparts->rgbSensor[i].id = -1;
        kparts->rgbSensor[i].hw_driver.attributes.device_channel = -1;
        
        kparts->freqCounter[i].id = -1;
        kparts->freqCounter[i].hw_driver.attributes.device_channel = -1;
        
        kparts->pulsesCounter[i].id = -1;
        kparts->pulsesCounter[i].hw_driver.attributes.device_channel = -1;
    }
}

/**
 * \fn void clearDeviceSettings(void)
 * \brief Clear all the devices structures with setting setting the ID to -1
 * \param -
 * \return -
 */
void clearDeviceSettings(devices_list * boardDevice){
    int i, j;
    // Init ID of device to "unknown"
    for(i=0;i<MAX_BOARD_DEVICE; i++){
        boardDevice[i].address = -1;
        strcpy(boardDevice[i].sub_driver.name, "");
        for(j=0;j<32;j++){
            boardDevice[i].attributes.deviceInit[j].regAddr = -1;
            boardDevice[i].attributes.deviceInit[j].regData = -1;
        }
    }
}




/**
 * \brief char * getDriverTypeByName(char * name), Get the device type from
 * the name and convert it to local definition
 * \param char * name , name of the device (like IC3, U5, etc...)
 * \return enum type
 */ 

char *  getDriverTypeByName(char * name){
    int i;
    static char ICtype[25]; 
    
    strcpy(ICtype, "Unknown");
    
    for(i=0; boardDevice[i].address >= 0 && i<MAX_BOARD_DEVICE; i++){
        if(!strcmp(boardDevice[i].name, name)){
            strcpy(ICtype, boardDevice[i].type);
            break;
        }
    }
    //printf("#%d Le driver trouvé pour [%s] est de type [%s]\n", i, name, boardDevice[i].type);
    return ICtype;
}
