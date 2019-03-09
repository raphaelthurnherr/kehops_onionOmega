/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#define MAX_MQTT_BUFF 4096

#define FILE_KEY_CONFIG_ROBOT "{'robot'"
#define FILE_KEY_CONFIG_ROBOT_NAME  "{'robot'{'name'"
#define FILE_KEY_CONFIG_ROBOT_GROUP  "{'robot'{'group'"

#define FILE_KEY_CONFIG_MQTT "{'mqtt'"
#define FILE_KEY_CONFIG_MQTT_BROKER_ADDRESS  "{'mqtt'{'broker'{'address'"
#define FILE_KEY_CONFIG_MQTT_STREAM_STATE "{'mqtt'{'stream'{'state'"
#define FILE_KEY_CONFIG_MQTT_STREAM_TIME "{'mqtt'{'stream'{'time'"
#define FILE_KEY_CONFIG_MQTT_STREAM_ONEVENT "{'mqtt'{'stream'{'onEvent'"

#define FILE_KEY_CONFIG_LED "{'led'"
#define FILE_KEY_CONFIG_LED_ID "{'led'[*{'led'"
#define FILE_KEY_CONFIG_LED_POWER "{'led'[*{'power'"
#define FILE_KEY_CONFIG_LED_STATE "{'led'[*{'state'"

#define FILE_KEY_CONFIG_PWM "{'pwm'"
#define FILE_KEY_CONFIG_PWM_ID "{'pwm'[*{'pwm'"
#define FILE_KEY_CONFIG_PWM_POWER "{'pwm'[*{'power'"
#define FILE_KEY_CONFIG_PWM_STATE "{'pwm'[*{'state'"

#define FILE_KEY_CONFIG_DIN "{'din'"
#define FILE_KEY_CONFIG_DIN_ID "{'din'[*{'din'"
#define FILE_KEY_CONFIG_DIN_EVENT_STATE "{'din'[*{'event'"

#define FILE_KEY_CONFIG_BTN "{'button'"
#define FILE_KEY_CONFIG_BTN_ID "{'button'[*{'btn'"
#define FILE_KEY_CONFIG_BTN_EVENT_STATE "{'button'[*{'event'"

#define FILE_KEY_CONFIG_SONAR "{'sonar'"
#define FILE_KEY_CONFIG_SONAR_ID "{'sonar'[*{'sonar'"
#define FILE_KEY_CONFIG_SONAR_EVENT_STATE "{'sonar'[*{'event'"
#define FILE_KEY_CONFIG_SONAR_EVENT_LOW "{'sonar'[*{'event_lower'"
#define FILE_KEY_CONFIG_SONAR_EVENT_HIGH "{'sonar'[*{'event_higher'"
#define FILE_KEY_CONFIG_SONAR_EVENT_HYST "{'sonar'[*{'event_hysteresis'"

#define FILE_KEY_CONFIG_BATTERY "{'battery'"
#define FILE_KEY_CONFIG_BATTERY_ID "{'battery'[*{'battery'"
#define FILE_KEY_CONFIG_BATTERY_EVENT_STATE "{'battery'[*{'event'"
#define FILE_KEY_CONFIG_BATTERY_EVENT_LOW "{'battery'[*{'event_lower'"
#define FILE_KEY_CONFIG_BATTERY_EVENT_HIGH "{'battery'[*{'event_higher'"
#define FILE_KEY_CONFIG_BATTERY_EVENT_HYST "{'battery'[*{'event_hysteresis'"

#define FILE_KEY_CONFIG_MOTOR "{'motor'"
#define FILE_KEY_CONFIG_MOTOR_ID "{'motor'[*{'motor'"
#define FILE_KEY_CONFIG_MOTOR_INVERT "{'motor'[*{'inverted'"
#define FILE_KEY_CONFIG_MOTOR_MINPWM "{'motor'[*{'pwmMin'"
#define FILE_KEY_CONFIG_MOTOR_MINRPM "{'motor'[*{'rpmMin'"
#define FILE_KEY_CONFIG_MOTOR_MAXRPM "{'motor'[*{'rpmMax'"


#define FILE_KEY_CONFIG_WHEEL "{'wheel'"
#define FILE_KEY_CONFIG_WHEEL_ID "{'wheel'[*{'wheel'"
#define FILE_KEY_CONFIG_WHEEL_PULSES "{'wheel'[*{'pulses'"
#define FILE_KEY_CONFIG_WHEEL_DIAMETER "{'wheel'[*{'diameter'"
#define FILE_KEY_CONFIG_WHEEL_PIDEN  "{'wheel'[*{'rpmRegulator'{'state'"
#define FILE_KEY_CONFIG_WHEEL_PIDkp  "{'wheel'[*{'rpmRegulator'{'PID_Kp'"
#define FILE_KEY_CONFIG_WHEEL_PIDki  "{'wheel'[*{'rpmRegulator'{'PID_Ki'"
#define FILE_KEY_CONFIG_WHEEL_PIDkd  "{'wheel'[*{'rpmRegulator'{'PID_Kd'"

#define FILE_KEY_CONFIG_STEPPER "{'stepper'"
#define FILE_KEY_CONFIG_STEPPER_ID "{'stepper'[*{'motor'"
#define FILE_KEY_CONFIG_STEPPER_INVERT "{'stepper'[*{'inverted'"
#define FILE_KEY_CONFIG_STEPPER_RATIO "{'stepper'[*{'ratio'"
#define FILE_KEY_CONFIG_STEPPER_STEPS "{'stepper'[*{'steps'"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "type.h"
#include "jRead.h"
#include "jWrite.h"
#include "kehops_main.h"
#include "hwControl/hwManager.h"
#include "configManager.h"

char * OpenConfigFromFile(char *filename);
char LoadConfig(char * fileName);
char SaveConfig(char * fileName);

unsigned char mode=0;
unsigned char dataCommandReady=0;

/**
 * \fn char * OpenConfigFromFile(char *filename)
 * \brief Open the config file get the content for futur use.
 *
 * \param filename to open
 * \return 0 is returned if no errors, otherwise, return -1;
 */

char * OpenConfigFromFile(char *filename){   
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

// -----------------------------------------------------------------------------
// LoadConfig
// Get configuration file and load data into config structure
// -----------------------------------------------------------------------------

/**
 * \fn char LoadConfig(char * fileName)
 * \brief Extract the file content from buffer and dispatch the settings to the
 * kehops structure.
 *
 * \param filename to open
 * \return pointer to the buffer with file content
 */

char LoadConfig(char * fileName){
	struct jReadElement cfg_devices_list, cfg_mqtt_list;
        int nbOfDeviceInConf, deviceId;
	int i;
        char * srcDataBuffer;
        char dataValue[15];
        
        srcDataBuffer = OpenConfigFromFile(fileName); 
        
        
        if(srcDataBuffer != NULL){
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
            
        // EXTRACT WHEEL SETTINGS FROM CONFIG    
            // Reset motor data config before reading
            for(i=0;i<NBMOTOR;i++){
              kehops.dcWheel[deviceId].config.diameter = -1;
              kehops.dcWheel[deviceId].config.pulsesPerRot = -1;
            }

            // Wheel Setting
            jRead((char *)srcDataBuffer, FILE_KEY_CONFIG_WHEEL, &cfg_devices_list );

            // RECHERCHE DATA DE TYPE ARRAY
            if(cfg_devices_list.dataType == JREAD_ARRAY ){
                // Get the number of motors in array
                nbOfDeviceInConf=cfg_devices_list.elements;

                for(i=0; i < nbOfDeviceInConf; i++){ 
                    deviceId=-1;
                    deviceId=jRead_long((char *)srcDataBuffer, FILE_KEY_CONFIG_WHEEL_ID, &i); 

                    if(deviceId >= 0 && deviceId < NBMOTOR){
                        kehops.dcWheel[deviceId].config.diameter = jRead_long((char *)srcDataBuffer, FILE_KEY_CONFIG_WHEEL_DIAMETER, &i);
                        kehops.dcWheel[deviceId].config.pulsesPerRot = jRead_long((char *)srcDataBuffer, FILE_KEY_CONFIG_WHEEL_PULSES, &i);
                        kehops.dcWheel[deviceId].data._MMPP = (kehops.dcWheel[deviceId].config.diameter * 3.1415926535897932384) / kehops.dcWheel[deviceId].config.pulsesPerRot;
                        kehops.dcWheel[deviceId].data._MAXSPEED_CMSEC = ((float)kehops.dcWheel[deviceId].config.rpmMax /60) *  ((kehops.dcWheel[deviceId].config.diameter * 3.1415926535897932384)/10);
                    }
                }
            }
            
        // EXTRACT STEPPER MOTOR SETTINGS FROM CONFIG
        
        // Reset motor data config before reading
        for(i=0;i<NBSTEPPER;i++){
          kehops.stepperWheel[i].config.motor.inverted = -1;
          kehops.stepperWheel[i].config.motor.ratio = -1;
          kehops.stepperWheel[i].config.motor.steps = -1;
        }
            
        // Stepper motor Settings
            jRead((char *)srcDataBuffer, FILE_KEY_CONFIG_STEPPER, &cfg_devices_list );

            // RECHERCHE DATA DE TYPE ARRAY
            if(cfg_devices_list.dataType == JREAD_ARRAY ){
                // Get the number of motors in array
                nbOfDeviceInConf=cfg_devices_list.elements;

                for(i=0; i < nbOfDeviceInConf; i++){ 
                    deviceId=-1;
                    deviceId=jRead_long((char *)srcDataBuffer, FILE_KEY_CONFIG_STEPPER_ID, &i); 

                    if(deviceId >= 0 && deviceId < NBSTEPPER){
                        jRead_string((char *)srcDataBuffer, FILE_KEY_CONFIG_STEPPER_INVERT, dataValue, 15, &i );
                        if(!strcmp(dataValue, "on")){
                           kehops.stepperWheel[deviceId].config.motor.inverted = 1;
                        }else
                            if(!strcmp(dataValue, "off")){
                                kehops.stepperWheel[deviceId].config.motor.inverted = 0;
                            }
                        kehops.stepperWheel[deviceId].config.motor.ratio = jRead_long((char *)srcDataBuffer, FILE_KEY_CONFIG_STEPPER_RATIO, &i); 
                        kehops.stepperWheel[deviceId].config.motor.steps = jRead_long((char *)srcDataBuffer, FILE_KEY_CONFIG_STEPPER_STEPS, &i); 
                    }
                }
            }            

        // EXTRACT LED SETTINGS FROM CONFIG    
          // Reset motor data config before reading
          for(i=0;i<NBLED;i++){
              kehops.led[i].config.defaultPower = -1;
              kehops.led[i].config.defaultState = -1;
              kehops.led[i].config.mode = -1;
          }

        // LED Setting
            jRead((char *)srcDataBuffer, FILE_KEY_CONFIG_LED, &cfg_devices_list );

            // RECHERCHE DATA DE TYPE ARRAY
            if(cfg_devices_list.dataType == JREAD_ARRAY ){
                // Get the number of motors in array
                nbOfDeviceInConf=cfg_devices_list.elements;

                for(i=0; i < nbOfDeviceInConf; i++){ 
                    deviceId=-1;
                    deviceId=jRead_long((char *)srcDataBuffer, FILE_KEY_CONFIG_LED_ID, &i); 

                    kehops.led[deviceId].config.defaultPower = jRead_int((char *)srcDataBuffer, FILE_KEY_CONFIG_LED_POWER, &i);

                    if(deviceId >= 0 && deviceId < NBLED){
                        jRead_string((char *)srcDataBuffer, FILE_KEY_CONFIG_LED_STATE, dataValue, 15, &i );
                        if(!strcmp(dataValue, "on")){
//                            Config->led[deviceId].state = 1;
                            kehops.led[deviceId].config.defaultState = 1;
                        }else
                            if(!strcmp(dataValue, "off")){
                            kehops.led[deviceId].config.defaultState = 0;
                            }
                    }
                }
            }

        // EXTRACT PWM SETTINGS FROM CONFIG    
          // Reset motor data config before reading
          for(i=0;i<NBPWM;i++){
              kehops.pwm[i].config.defaultPower = 0;
              kehops.pwm[i].config.defaultState = 0;
              kehops.pwm[i].config.mode = 0;
          }
            
        // PWM Setting
            jRead((char *)srcDataBuffer, FILE_KEY_CONFIG_PWM, &cfg_devices_list );

            // RECHERCHE DATA DE TYPE ARRAY
            if(cfg_devices_list.dataType == JREAD_ARRAY ){
                // Get the number of PWM in array
                nbOfDeviceInConf = cfg_devices_list.elements;
                for(i=0; i < nbOfDeviceInConf; i++){ 
                    deviceId=-1;
                    deviceId = jRead_long((char *)srcDataBuffer, FILE_KEY_CONFIG_PWM_ID, &i); 

                    kehops.pwm[deviceId].config.defaultPower = jRead_int((char *)srcDataBuffer, FILE_KEY_CONFIG_PWM_POWER, &i);
                    if(deviceId >= 0 && deviceId < NBLED){
                        jRead_string((char *)srcDataBuffer, FILE_KEY_CONFIG_PWM_STATE, dataValue, 15, &i );
                        if(!strcmp(dataValue, "on")){
                            kehops.pwm[deviceId].config.defaultState = 1;
                        }else
                            if(!strcmp(dataValue, "off")){
                            kehops.pwm[deviceId].config.defaultState = 0;
                            }
                    }
                }
            }
            
        // DIN Setting
            jRead((char *)srcDataBuffer, FILE_KEY_CONFIG_DIN, &cfg_devices_list );

            // RECHERCHE DATA DE TYPE ARRAY
            if(cfg_devices_list.dataType == JREAD_ARRAY ){
                // Get the number of DIN in array
                nbOfDeviceInConf = cfg_devices_list.elements;
                for(i=0; i < nbOfDeviceInConf; i++){ 
                    deviceId=-1;
                    deviceId = jRead_long((char *)srcDataBuffer, FILE_KEY_CONFIG_DIN_ID, &i); 

                    if(deviceId >= 0 && deviceId < NBDIN){
                        jRead_string((char *)srcDataBuffer, FILE_KEY_CONFIG_DIN_EVENT_STATE, dataValue, 15, &i );
                        if(!strcmp(dataValue, "on")){
                            kehops.proximity[deviceId].event.enable = 1;
                        }else
                            if(!strcmp(dataValue, "off")){
                                kehops.proximity[deviceId].event.enable = 0;
                            }
                    }
                }
            }
            
        // BTN Setting
            jRead((char *)srcDataBuffer, FILE_KEY_CONFIG_BTN, &cfg_devices_list );

            // RECHERCHE DATA DE TYPE ARRAY
            if(cfg_devices_list.dataType == JREAD_ARRAY ){
                // Get the number of BTN in array
                nbOfDeviceInConf = cfg_devices_list.elements;
                for(i=0; i < nbOfDeviceInConf; i++){ 
                    deviceId=-1;
                    deviceId = jRead_long((char *)srcDataBuffer, FILE_KEY_CONFIG_BTN_ID, &i); 

                    if(deviceId >= 0 && deviceId < NBBTN){
                        jRead_string((char *)srcDataBuffer, FILE_KEY_CONFIG_BTN_EVENT_STATE, dataValue, 15, &i );
                        if(!strcmp(dataValue, "on")){
                            kehops.button[deviceId].event.enable = 1;
                        }else
                            if(!strcmp(dataValue, "off")){
                                kehops.button[deviceId].event.enable = 0;
                            }
                    }
                }
            }

            // SONAR Setting
            jRead((char *)srcDataBuffer, FILE_KEY_CONFIG_SONAR, &cfg_devices_list );

            // RECHERCHE DATA DE TYPE ARRAY
            if(cfg_devices_list.dataType == JREAD_ARRAY ){
                // Get the number of SONAR in array
                nbOfDeviceInConf = cfg_devices_list.elements;
                for(i=0; i < nbOfDeviceInConf; i++){ 
                    deviceId=-1;
                    deviceId = jRead_long((char *)srcDataBuffer, FILE_KEY_CONFIG_SONAR_ID, &i); 

                    if(deviceId >= 0 && deviceId < NBSONAR){
                        jRead_string((char *)srcDataBuffer, FILE_KEY_CONFIG_SONAR_EVENT_STATE, dataValue, 15, &i );
                        if(!strcmp(dataValue, "on")){
                            kehops.sonar[deviceId].event.enable = 1;
                        }else
                            if(!strcmp(dataValue, "off")){
                                kehops.sonar[deviceId].event.enable = 0;
                            }
                        kehops.sonar[deviceId].event.low = jRead_long((char *)srcDataBuffer, FILE_KEY_CONFIG_SONAR_EVENT_LOW, &i); 
                        kehops.sonar[deviceId].event.high = jRead_long((char *)srcDataBuffer, FILE_KEY_CONFIG_SONAR_EVENT_HIGH, &i); 
                        kehops.sonar[deviceId].event.hysteresis = jRead_long((char *)srcDataBuffer, FILE_KEY_CONFIG_SONAR_EVENT_HYST, &i); 
                    }
                }
            }
            
            // BATTERY Setting
            jRead((char *)srcDataBuffer, FILE_KEY_CONFIG_BATTERY, &cfg_devices_list );

            // RECHERCHE DATA DE TYPE ARRAY
            if(cfg_devices_list.dataType == JREAD_ARRAY ){
                // Get the number of BATTERY in array
                nbOfDeviceInConf = cfg_devices_list.elements;
                for(i=0; i < nbOfDeviceInConf; i++){ 
                    deviceId=-1;
                    deviceId = jRead_long((char *)srcDataBuffer, FILE_KEY_CONFIG_BATTERY_ID, &i); 

                    if(deviceId >= 0 && deviceId < NBSONAR){
                        jRead_string((char *)srcDataBuffer, FILE_KEY_CONFIG_BATTERY_EVENT_STATE, dataValue, 15, &i );
                        if(!strcmp(dataValue, "on")){
                            kehops.battery[deviceId].event.enable = 1;
                        }else
                            if(!strcmp(dataValue, "off")){
                                kehops.battery[deviceId].event.enable = 0;
                            }
                        kehops.battery[deviceId].event.low = jRead_long((char *)srcDataBuffer, FILE_KEY_CONFIG_BATTERY_EVENT_LOW, &i); 
                        kehops.battery[deviceId].event.high = jRead_long((char *)srcDataBuffer, FILE_KEY_CONFIG_BATTERY_EVENT_HIGH, &i); 
                        kehops.battery[deviceId].event.hysteresis = jRead_long((char *)srcDataBuffer, FILE_KEY_CONFIG_BATTERY_EVENT_HYST, &i); 
                    }
                }
            }            

            // Reset settings
    //            jRead_string((char *)srcDataBuffer, KEY_MESSAGE_VALUE_CFG_APPRESET, AlgoidMessageRX.Config.config.reset, 15, &i );
            return 0;
        }
        
        return -1;
}


// -----------------------------------------------------------------------------
// SaveConfig
// Save configuration to file
// -----------------------------------------------------------------------------

char SaveConfig(char * fileName){
    char buffer[MAX_MQTT_BUFF];
    unsigned int buflen= MAX_MQTT_BUFF;
    int i;
    // CREATE JSON STRING FOR CONFIGURATION FILE
	jwOpen( buffer, buflen, JW_OBJECT, JW_PRETTY );		// start root object  

        // CREATE JSON CONFIG FOR MQTT        
            jwObj_object( "robot" );        
                jwObj_string("name", sysApp.info.name);
                jwObj_string("group", sysApp.info.group);
            jwEnd();
            
        // CREATE JSON CONFIG FOR MQTT        
            jwObj_object( "mqtt" );
                jwObj_object( "broker" );
                    jwObj_string("address", sysConf.communication.mqtt.broker.address);
                jwEnd();
                jwObj_object( "stream" );
                if(sysConf.communication.mqtt.stream.state == 0)
                    jwObj_string("state", "off");
                else 
                    if(sysConf.communication.mqtt.stream.state == 1)
                        jwObj_string("state", "on");

                    jwObj_int( "time", sysConf.communication.mqtt.stream.time_ms);

                if(sysConf.communication.mqtt.stream.onEvent == 0)
                    jwObj_string("onEvent", "off");
                else 
                    if(sysConf.communication.mqtt.stream.onEvent == 1)
                        jwObj_string("onEvent", "on");                
                jwEnd();
            jwEnd();

        // CREATE JSON CONFIG FOR MOTOR            
            jwObj_array("motor");
                for(i=0;i<NBMOTOR;i++){
                    jwArr_object();
                        jwObj_int( "motor", i);
                        if(kehops.dcWheel[i].config.motor.inverted == 0)
                            jwObj_string("inverted", "off");
                        else 
                            if(kehops.dcWheel[i].config.motor.inverted == 1)
                                jwObj_string("inverted", "on");
                        jwObj_int( "pwmMin", kehops.dcWheel[i].config.motor.powerMin);
                        jwObj_int( "rpmMin", kehops.dcWheel[i].config.rpmMin);
                        jwObj_int( "rpmMax", kehops.dcWheel[i].config.rpmMax);
                    jwEnd();
                } 
            jwEnd();
            
        // CREATE JSON CONFIG FOR WHEEL SETTING            
            jwObj_array("wheel");
                for(i=0;i<NBMOTOR;i++){
                    jwArr_object();
                        jwObj_int( "wheel", i);
                        jwObj_int( "diameter", kehops.dcWheel[i].config.diameter);
                        jwObj_int( "pulses", kehops.dcWheel[i].config.pulsesPerRot);
                        jwObj_object("rpmRegulator");
                            if(kehops.dcWheel[i].config.pidReg.enable == 0)
                                jwObj_string("state", "off");
                            else 
                                if(kehops.dcWheel[i].config.pidReg.enable == 1)
                                    jwObj_string("state", "on");
                                    jwObj_double( "PID_Kp", kehops.dcWheel[i].config.pidReg.Kp);
                                    jwObj_double( "PID_Ki", kehops.dcWheel[i].config.pidReg.Ki);
                                    jwObj_double( "PID_Kd", kehops.dcWheel[i].config.pidReg.Kd);
                        jwEnd();
                    jwEnd();
                } 
            jwEnd();            
            
        // CREATE JSON CONFIG FOR STEPPER MOTOR            
            jwObj_array("stepper");
                for(i=0;i<NBSTEPPER;i++){
                    jwArr_object();
                        jwObj_int( "motor", i);
                        if(kehops.stepperWheel[i].config.motor.inverted == 0)
                            jwObj_string("inverted", "off");
                        else 
                            if(kehops.stepperWheel[i].config.motor.inverted == 1)
                                jwObj_string("inverted", "on");
                        jwObj_int( "ratio", kehops.stepperWheel[i].config.motor.ratio);
                        jwObj_int( "steps", kehops.stepperWheel[i].config.motor.steps);
                    jwEnd();
                } 
            jwEnd();            
            
        // CREATE JSON CONFIG FOR LED
            jwObj_array("led");
                for(i=0;i<NBLED;i++){
                    jwArr_object();
                        jwObj_int( "led", i);
                        if(kehops.led[i].config.defaultState == 0)
                            jwObj_string("state", "off");
                        else 
                            if(kehops.led[i].config.defaultState == 1)
                                jwObj_string("state", "on");
                        jwObj_int( "power", kehops.led[i].config.defaultPower);
                    jwEnd();
                } 
            jwEnd();            

        // CREATE JSON CONFIG FOR PWM OUTPUT
            jwObj_array("pwm");
                for(i=0;i<NBPWM;i++){
                    jwArr_object();
                        jwObj_int( "pwm", i);
                        if(kehops.pwm[i].config.defaultState == 0)
                            jwObj_string("state", "off");
                        else 
                            if(kehops.pwm[i].config.defaultState == 1)
                                jwObj_string("state", "on");
                        jwObj_int( "power", kehops.pwm[i].config.defaultPower);
                    jwEnd();
                } 
            jwEnd();
            
        // CREATE JSON CONFIG FOR DIN CONFIG
            jwObj_array("din");
                for(i=0;i<NBDIN;i++){
                    jwArr_object();
                        jwObj_int( "din", i);
                        if(kehops.proximity[i].event.enable == 0)
                            jwObj_string("event", "off");
                        else 
                            if(kehops.proximity[i].event.enable == 1)
                                jwObj_string("event", "on");
                    jwEnd();
                } 
            jwEnd();  

        // CREATE JSON CONFIG FOR BTN CONFIG
            jwObj_array("button");
                for(i=0;i<NBBTN;i++){
                    jwArr_object();
                        jwObj_int( "btn", i);
                        if(kehops.button[i].event.enable == 0)
                            jwObj_string("event", "off");
                        else 
                            if(kehops.button[i].event.enable == 1)
                                jwObj_string("event", "on");
                    jwEnd();
                } 
            jwEnd();

        // CREATE JSON CONFIG FOR SONAR CONFIG
            jwObj_array("sonar");
                for(i=0;i<NBSONAR;i++){
                    jwArr_object();
                        jwObj_int( "sonar", i);
                        if(kehops.sonar[i].event.enable == 0)
                            jwObj_string("event", "off");
                        else 
                            if(kehops.sonar[i].event.enable == 1)
                                jwObj_string("event", "on");
                        jwObj_int( "event_lower", kehops.sonar[i].event.low);
                        jwObj_int( "event_higher", kehops.sonar[i].event.high);
                        jwObj_int( "event_hysteresis", kehops.sonar[i].event.hysteresis);
                    jwEnd();
                } 
            jwEnd(); 
            
        // CREATE JSON CONFIG FOR BATTERY CONFIG
            jwObj_array("battery");
                for(i=0;i<NBAIN;i++){
                    jwArr_object();
                        jwObj_int( "battery", i);
                        if(kehops.battery[i].event.enable == 0)
                            jwObj_string("event", "off");
                        else 
                            if(kehops.battery[i].event.enable == 1)
                                jwObj_string("event", "on");
                        jwObj_int( "event_lower", kehops.battery[i].event.low);
                        jwObj_int( "event_higher", kehops.battery[i].event.high);
                        jwObj_int( "event_hysteresis", kehops.battery[i].event.hysteresis);
                    jwEnd();
                } 
            jwEnd();             

        jwClose();          
       
    // CREATE JSON STRING FOR CONFIGURATION   
        FILE *fp;
        int x = 10;

        fp=fopen(fileName, "w");
        if(fp == NULL)
            printf("Error during config file save");
        
        fprintf(fp, buffer);
        fclose(fp);
    return 0;
}