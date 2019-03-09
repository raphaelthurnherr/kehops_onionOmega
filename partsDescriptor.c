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


// Library dependency
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "jRead.h"
#include "jWrite.h"
#include "partsDescriptor.h"

char * OpenDataFromFile(char *filename);
char LoadDescriptor(char * fileName);

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
 * \fn char LoadDescriptor(char * fileName)
 * \brief Extract the file content from buffer and dispatch the settings to the
 * kehops structure.
 *
 * \param filename to open
 * \return pointer to the buffer with file content
 */

char LoadDescriptor(char * fileName){
	struct jReadElement cfg_devices_list, cfg_mqtt_list;
        int nbOfDeviceInConf, deviceId;
	int i;
        char * srcDataBuffer;
        char dataValue[15];
        
        srcDataBuffer = OpenDataFromFile(fileName); 
        
        
        if(srcDataBuffer != NULL){
            
/*            
        // EXTRACT MQTT SETTINGS FROM CONFIG        
            jRead((char *)srcDataBuffer, FILE_KEY_CONFIG_MQTT, &cfg_mqtt_list );
            // RECHERCHE DATA DE TYPE OBJ
            if(cfg_mqtt_list.dataType == JREAD_OBJECT ){
                
        // EXTRACT ROBOR NAME AND GROUP
            jRead_string((char *)srcDataBuffer, FILE_KEY_CONFIG_ROBOT_NAME, sysApp.info.name, 32, &i);                
            jRead_string((char *)srcDataBuffer, FILE_KEY_CONFIG_ROBOT_GROUP, sysApp.info.group, 32, &i);
            
        // EXTRACT BROKER SETTINGS FROM CONFIG
            jRead_string((char *)srcDataBuffer, FILE_KEY_CONFIG_MQTT_BROKER_ADDRESS, sysConf.communication.mqtt.broker.address, 100, &i);

        // EXTRACT STREAM SETTINGS FROM CONFIG            
            // Load data for stream TIME
            sysConf.communication.mqtt.stream.time_ms = jRead_int((char *) srcDataBuffer, FILE_KEY_CONFIG_MQTT_STREAM_TIME, &i);
        
            // Load data for stream STATE
            jRead_string((char *)srcDataBuffer, FILE_KEY_CONFIG_MQTT_STREAM_STATE, dataValue, 15, &i );

            if(!strcmp(dataValue, "on")){
                sysConf.communication.mqtt.stream.state = 1;
                
            }else
                if(!strcmp(dataValue, "off")){
                    sysConf.communication.mqtt.stream.state = 0;
                }

            // Load data for stream ONEVENT
            jRead_string((char *)srcDataBuffer, FILE_KEY_CONFIG_MQTT_STREAM_ONEVENT, dataValue, 15, &i );
            if(!strcmp(dataValue, "on")){
                sysConf.communication.mqtt.stream.onEvent = 1;
            }else
                if(!strcmp(dataValue, "off")){
                    sysConf.communication.mqtt.stream.onEvent = 0;
                }                 
            }


        // EXTRACT MOTOR SETTINGS FROM CONFIG    
            // Reset motor data config before reading
            
            for(i=0;i<NBMOTOR;i++){
              kehops.dcWheel[i].config.motor.inverted = 0;
              kehops.dcWheel[i].config.rpmMin = 20;
              kehops.dcWheel[i].config.rpmMax = 200;
            }

            // Motor Setting
            jRead((char *)srcDataBuffer, FILE_KEY_CONFIG_MOTOR, &cfg_devices_list );

            // RECHERCHE DATA DE TYPE ARRAY
            if(cfg_devices_list.dataType == JREAD_ARRAY ){
                // Get the number of motors in array
                nbOfDeviceInConf=cfg_devices_list.elements;

                for(i=0; i < nbOfDeviceInConf; i++){ 
                    
                    
                    deviceId=-1;
                    deviceId=jRead_int((char *)srcDataBuffer, FILE_KEY_CONFIG_MOTOR_ID, &i); 

                    if(deviceId >= 0 && deviceId < NBMOTOR){
                        kehops.dcWheel[deviceId].config.rpmMin = jRead_int((char *)srcDataBuffer, FILE_KEY_CONFIG_MOTOR_MINRPM, &i); 
                        kehops.dcWheel[deviceId].config.rpmMax = jRead_int((char *)srcDataBuffer, FILE_KEY_CONFIG_MOTOR_MAXRPM, &i); 
                         kehops.dcWheel[deviceId].config.motor.powerMin = jRead_int((char *)srcDataBuffer, FILE_KEY_CONFIG_MOTOR_MINPWM, &i); 
                        jRead_string((char *)srcDataBuffer, FILE_KEY_CONFIG_MOTOR_INVERT, dataValue, 15, &i );
                        if(!strcmp(dataValue, "on")){
                            kehops.dcWheel[deviceId].config.motor.inverted = 1;
                        }else
                            if(!strcmp(dataValue, "off")){
                                kehops.dcWheel[deviceId].config.motor.inverted = 0;
                            }
                        // RECUPERATION DES PARAMETRE DU REGULATOR PID
                        jRead_string((char *)srcDataBuffer, FILE_KEY_CONFIG_WHEEL_PIDEN, dataValue, 15, &i );
                        if(!strcmp(dataValue, "on")){
                            kehops.dcWheel[deviceId].config.pidReg.enable = 1;
                        }else
                            if(!strcmp(dataValue, "off")){
                                kehops.dcWheel[deviceId].config.pidReg.enable = 0;
                            }                        
                        kehops.dcWheel[deviceId].config.pidReg.Kp = jRead_double((char *)srcDataBuffer, FILE_KEY_CONFIG_WHEEL_PIDkp, &i); 
                        kehops.dcWheel[deviceId].config.pidReg.Ki = jRead_double((char *)srcDataBuffer, FILE_KEY_CONFIG_WHEEL_PIDki, &i); 
                        kehops.dcWheel[deviceId].config.pidReg.Kd = jRead_double((char *)srcDataBuffer, FILE_KEY_CONFIG_WHEEL_PIDkd, &i); 

                    }
                }

            } 

            // Reset settings
    //            jRead_string((char *)srcDataBuffer, KEY_MESSAGE_VALUE_CFG_APPRESET, AlgoidMessageRX.Config.config.reset, 15, &i );
            return 0;

 */
        }
        
        return -1;
}






