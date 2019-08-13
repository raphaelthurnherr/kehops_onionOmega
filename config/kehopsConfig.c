/**
 * \file kehopsConfig.h
 * \brief  Kehops configuration utility functions
 *      
 * \author Raphael Thurnherr
 * \version 0.1
 * \date 21.03.2019
 *
 * Function libryry for hi level kehops configuration using kehops.cfg
 * 
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
#define FILE_KEY_CONFIG_LED_MAP_ID "{'led'[*{'dout_id'"
#define FILE_KEY_CONFIG_LED_POWER "{'led'[*{'power'"
#define FILE_KEY_CONFIG_LED_STATE "{'led'[*{'state'"

#define FILE_KEY_CONFIG_PWM "{'pwm'"
#define FILE_KEY_CONFIG_PWM_ID     "{'pwm'[*{'pwm'"
#define FILE_KEY_CONFIG_PWM_MAP_ID "{'pwm'[*{'dout_id'"
#define FILE_KEY_CONFIG_PWM_POWER  "{'pwm'[*{'power'"
#define FILE_KEY_CONFIG_PWM_STATE  "{'pwm'[*{'state'"

#define FILE_KEY_CONFIG_DIN "{'din'"
#define FILE_KEY_CONFIG_DIN_ID "{'din'[*{'din'"
#define FILE_KEY_CONFIG_DIN_MAP_ID "{'din'[*{'din_id'"
#define FILE_KEY_CONFIG_DIN_EVENT_STATE "{'din'[*{'event'"

#define FILE_KEY_CONFIG_AOUT "{'aout'"
#define FILE_KEY_CONFIG_AOUT_ID "{'aout'[*{'aout'"
#define FILE_KEY_CONFIG_AOUT_MAP_ID "{'aout'[*{'aout_id'"
#define FILE_KEY_CONFIG_AOUT_EVENT_STATE "{'aout'[*{'event'"

#define FILE_KEY_CONFIG_BTN "{'button'"
#define FILE_KEY_CONFIG_BTN_ID "{'button'[*{'btn'"
#define FILE_KEY_CONFIG_BTN_MAP_ID "{'button'[*{'din_id'"
#define FILE_KEY_CONFIG_BTN_EVENT_STATE "{'button'[*{'event'"

#define FILE_KEY_CONFIG_SONAR "{'sonar'"
#define FILE_KEY_CONFIG_SONAR_ID "{'sonar'[*{'sonar'"
#define FILE_KEY_CONFIG_SONAR_MAP_ID "{'sonar'[*{'distanceSensor_id'"
#define FILE_KEY_CONFIG_SONAR_EVENT_STATE "{'sonar'[*{'event'"
#define FILE_KEY_CONFIG_SONAR_EVENT_LOW "{'sonar'[*{'event_lower'"
#define FILE_KEY_CONFIG_SONAR_EVENT_HIGH "{'sonar'[*{'event_higher'"
#define FILE_KEY_CONFIG_SONAR_EVENT_HYST "{'sonar'[*{'event_hysteresis'"

#define FILE_KEY_CONFIG_VOLTAGE "{'voltage'"
#define FILE_KEY_CONFIG_VOLTAGE_ID "{'voltage'[*{'voltage'"
#define FILE_KEY_CONFIG_VOLTAGE_MAP_ID "{'voltage'[*{'ain_id'"
#define FILE_KEY_CONFIG_VOLTAGE_EVENT_STATE "{'voltage'[*{'event'"
#define FILE_KEY_CONFIG_VOLTAGE_EVENT_LOW "{'voltage'[*{'event_lower'"
#define FILE_KEY_CONFIG_VOLTAGE_EVENT_HIGH "{'voltage'[*{'event_higher'"
#define FILE_KEY_CONFIG_VOLTAGE_EVENT_HYST "{'voltage'[*{'event_hysteresis'"

#define FILE_KEY_CONFIG_MOTOR "{'motor'"
#define FILE_KEY_CONFIG_MOTOR_ID "{'motor'[*{'motor'"
#define FILE_KEY_CONFIG_MOTOR_MAP_ID "{'motor'[*{'dc_motor_id'"
#define FILE_KEY_CONFIG_MOTOR_INVERT "{'motor'[*{'inverted'"
#define FILE_KEY_CONFIG_MOTOR_MINPWM "{'motor'[*{'pwmMin'"
#define FILE_KEY_CONFIG_MOTOR_MINRPM "{'motor'[*{'rpmMin'"
#define FILE_KEY_CONFIG_MOTOR_MAXRPM "{'motor'[*{'rpmMax'"

#define FILE_KEY_CONFIG_STEPPER "{'stepper'"
#define FILE_KEY_CONFIG_STEPPER_ID "{'stepper'[*{'motor'"
#define FILE_KEY_CONFIG_STEPPER_MAP_ID "{'stepper'[*{'stepper_motor_id'"
#define FILE_KEY_CONFIG_STEPPER_INVERT "{'stepper'[*{'inverted'"
#define FILE_KEY_CONFIG_STEPPER_RATIO "{'stepper'[*{'ratio'"
#define FILE_KEY_CONFIG_STEPPER_STEPS "{'stepper'[*{'steps'"

#define FILE_KEY_CONFIG_WHEEL "{'wheel'"
#define FILE_KEY_CONFIG_WHEEL_ID "{'wheel'[*{'wheel'"
#define FILE_KEY_CONFIG_WHEEL_PULSES "{'wheel'[*{'pulses'"
#define FILE_KEY_CONFIG_WHEEL_DIAMETER "{'wheel'[*{'diameter'"
#define FILE_KEY_CONFIG_WHEEL_FREQCOUNT "{'wheel'[*{'freqCounter_id'"
#define FILE_KEY_CONFIG_WHEEL_PULSCOUNT "{'wheel'[*{'pulsesCounter_id'"
#define FILE_KEY_CONFIG_WHEEL_PIDEN  "{'wheel'[*{'rpmRegulator'{'state'"
#define FILE_KEY_CONFIG_WHEEL_PIDkp  "{'wheel'[*{'rpmRegulator'{'PID_Kp'"
#define FILE_KEY_CONFIG_WHEEL_PIDki  "{'wheel'[*{'rpmRegulator'{'PID_Ki'"
#define FILE_KEY_CONFIG_WHEEL_PIDkd  "{'wheel'[*{'rpmRegulator'{'PID_Kd'"

#define FILE_KEY_CONFIG_COLOR "{'color'"
#define FILE_KEY_CONFIG_COLOR_ID "{'color'[*{'color'"
#define FILE_KEY_CONFIG_COLOR_MAP_ID "{'color'[*{'rgbSensor_id'"
#define FILE_KEY_CONFIG_COLOR_EVENT_STATE "{'color'[*{'event'"
#define FILE_KEY_CONFIG_COLOR_RED "{'color'[*{'red'"
#define FILE_KEY_CONFIG_COLOR_GREEN "{'color'[*{'green'"
#define FILE_KEY_CONFIG_COLOR_BLUE "{'color'[*{'blue'"
#define FILE_KEY_CONFIG_COLOR_EVENT_LOW "{'event_lower'"
#define FILE_KEY_CONFIG_COLOR_EVENT_HIGH "{'event_higher'"
#define FILE_KEY_CONFIG_COLOR_EVENT_HYST "{'event_hysteresis'"

#define FILE_KEY_CONFIG_DISPLAY "{'display'"
#define FILE_KEY_CONFIG_DISPLAY_ID "{'display'[*{'display'"
#define FILE_KEY_CONFIG_DISPLAY_MAP_ID "{'display'[*{'display_id'"
#define FILE_KEY_CONFIG_HID_SCREEN"{'display'[*{'screen_hid'"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "jRead.h"
#include "jWrite.h"
#include "../kehops_main.h"
#include "kehopsConfig.h"


unsigned char NBPWM=0;
unsigned char NBLED=0;
unsigned char NBAIN=0;
unsigned char NBSONAR=0;
unsigned char NBSTEPPER=0;
unsigned char NBMOTOR=0;
unsigned char NBRGBC=0;
unsigned char NBBTN=0;
unsigned char NBDIN=0;
unsigned char NBWHEEL=0;
unsigned char NBAOUT=0;
unsigned char NBDISPLAY=0;

/**
 * \brief Extract JSON configuration from FileBuffer to the kehops structrue configuration
 * \param char * buffer, pointer to the source buffer to extractz data
 * \return code error
 */  
void extractKehopsConfig(char * srcDataBuffer){

    NBPWM = NBLED = NBAIN = NBSONAR = NBSTEPPER = NBSTEPPER = NBMOTOR = NBRGBC = NBBTN = NBDIN = NBWHEEL = NBAOUT = NBDISPLAY = 0;
    
    
    struct jReadElement cfg_devices_list, cfg_mqtt_list, cfg_devices;
    int nbOfDeviceInConf, deviceId;
    int i;
    char dataValue[15];
        
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

        // Motor Setting
        jRead((char *)srcDataBuffer, FILE_KEY_CONFIG_MOTOR, &cfg_devices_list );

        // RECHERCHE DATA DE TYPE ARRAY
        if(cfg_devices_list.dataType == JREAD_ARRAY ){
            // Get the number of motors in array
            nbOfDeviceInConf=cfg_devices_list.elements;

            // Reset motor data config before reading
            for(i=0;i<nbOfDeviceInConf;i++){
                kehops.dcWheel[i].config.motor.inverted = 0;
                kehops.dcWheel[i].config.rpmMin = 20;
                kehops.dcWheel[i].config.rpmMax = 200;
            }
            
            for(i=0; i < nbOfDeviceInConf; i++){ 
                deviceId=-1;
                deviceId=jRead_int((char *)srcDataBuffer, FILE_KEY_CONFIG_MOTOR_ID, &i); 

                if(deviceId >= 0){
                    NBMOTOR++;
                    kehops.dcWheel[deviceId].config.motor.dc_motor_id = jRead_int((char *)srcDataBuffer, FILE_KEY_CONFIG_MOTOR_MAP_ID, &i); 
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

        // Wheel Setting
        jRead((char *)srcDataBuffer, FILE_KEY_CONFIG_WHEEL, &cfg_devices_list );

        // RECHERCHE DATA DE TYPE ARRAY
        if(cfg_devices_list.dataType == JREAD_ARRAY ){
            // Get the number of motors in array
            nbOfDeviceInConf=cfg_devices_list.elements;

            // Reset motor data config before reading
            for(i=0;i<nbOfDeviceInConf;i++){
              kehops.dcWheel[i].config.diameter = -1;
              kehops.dcWheel[i].config.pulsesPerRot = -1;
              kehops.dcWheel[i].config.encoder.freqCounter_id = -1;
              kehops.dcWheel[i].config.encoder.pulseCounter_id = -1;
            }
        
            for(i=0; i < nbOfDeviceInConf; i++){ 
                deviceId=-1;
                deviceId=jRead_int((char *)srcDataBuffer, FILE_KEY_CONFIG_WHEEL_ID, &i); 
                if(deviceId >= 0){
                    NBWHEEL++;
                    kehops.dcWheel[deviceId].config.encoder.freqCounter_id = jRead_int((char *)srcDataBuffer, FILE_KEY_CONFIG_WHEEL_FREQCOUNT, &i);
                    kehops.dcWheel[deviceId].config.encoder.pulseCounter_id = jRead_int((char *)srcDataBuffer, FILE_KEY_CONFIG_WHEEL_PULSCOUNT, &i);
                    kehops.dcWheel[deviceId].config.diameter = jRead_long((char *)srcDataBuffer, FILE_KEY_CONFIG_WHEEL_DIAMETER, &i);
                    kehops.dcWheel[deviceId].config.pulsesPerRot = jRead_long((char *)srcDataBuffer, FILE_KEY_CONFIG_WHEEL_PULSES, &i);
                    kehops.dcWheel[deviceId].data._MMPP = (kehops.dcWheel[deviceId].config.diameter * 3.141592) / kehops.dcWheel[deviceId].config.pulsesPerRot;
                    kehops.dcWheel[deviceId].data._MAXSPEED_CMSEC = ((float)kehops.dcWheel[deviceId].config.rpmMax /60) *  ((kehops.dcWheel[deviceId].config.diameter * 3.1415926535897932384)/10);
                }
            }
        }
        
    // EXTRACT STEPPER MOTOR SETTINGS FROM CONFIG

        // Stepper motor Settings
        jRead((char *)srcDataBuffer, FILE_KEY_CONFIG_STEPPER, &cfg_devices_list );

        // RECHERCHE DATA DE TYPE ARRAY
        if(cfg_devices_list.dataType == JREAD_ARRAY ){
            // Get the number of motors in array
            nbOfDeviceInConf=cfg_devices_list.elements;

                        // Reset motor data config before reading
            for(i=0;i<nbOfDeviceInConf;i++){
              kehops.stepperWheel[i].config.motor.inverted = -1;
              kehops.stepperWheel[i].config.motor.ratio = -1;
              kehops.stepperWheel[i].config.motor.steps = -1;
            }
            
            for(i=0; i < nbOfDeviceInConf; i++){ 
                deviceId=-1;
                deviceId=jRead_long((char *)srcDataBuffer, FILE_KEY_CONFIG_STEPPER_ID, &i); 

                if(deviceId >= 0){
                    NBSTEPPER++;
                    kehops.stepperWheel[deviceId].config.motor.stepper_motor_id = jRead_int((char *)srcDataBuffer, FILE_KEY_CONFIG_STEPPER_MAP_ID, &i); 
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

    // LED Setting
        jRead((char *)srcDataBuffer, FILE_KEY_CONFIG_LED, &cfg_devices_list );

        // RECHERCHE DATA DE TYPE ARRAY
        if(cfg_devices_list.dataType == JREAD_ARRAY ){
            // Get the number of motors in array
            nbOfDeviceInConf=cfg_devices_list.elements;

            // Reset motor data config before reading
            for(i=0;i<nbOfDeviceInConf;i++){
                kehops.led[i].config.dout_id = -1;
                kehops.led[i].config.defaultPower = -1;
                kehops.led[i].config.defaultState = -1;
                kehops.led[i].config.mode = -1;
            }
            
            for(i=0; i < nbOfDeviceInConf; i++){ 
                deviceId=-1;
                deviceId=jRead_long((char *)srcDataBuffer, FILE_KEY_CONFIG_LED_ID, &i); 

                if(deviceId >= 0){
                    NBLED++;
                    kehops.led[deviceId].config.defaultPower = jRead_int((char *)srcDataBuffer, FILE_KEY_CONFIG_LED_POWER, &i);
                    kehops.led[deviceId].config.dout_id = jRead_int((char *)srcDataBuffer, FILE_KEY_CONFIG_LED_MAP_ID, &i);
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
        

    // PWM Setting
        jRead((char *)srcDataBuffer, FILE_KEY_CONFIG_PWM, &cfg_devices_list );

        // RECHERCHE DATA DE TYPE ARRAY
        if(cfg_devices_list.dataType == JREAD_ARRAY ){
            // Get the number of PWM in array
            nbOfDeviceInConf = cfg_devices_list.elements;
         
            // EXTRACT PWM SETTINGS FROM CONFIG    
              // Reset motor data config before reading
              for(i=0;i<nbOfDeviceInConf;i++){
                  kehops.pwm[i].config.dout_id = -1;
                  kehops.pwm[i].config.defaultPower = 0;
                  kehops.pwm[i].config.defaultState = 0;
                  kehops.pwm[i].config.mode = 0;
              }
            
            for(i=0; i < nbOfDeviceInConf; i++){
                deviceId=-1;
                deviceId = jRead_long((char *)srcDataBuffer, FILE_KEY_CONFIG_PWM_ID, &i); 

                if(deviceId >= 0){
                    NBPWM++;
                    kehops.pwm[deviceId].config.defaultPower = jRead_int((char *)srcDataBuffer, FILE_KEY_CONFIG_PWM_POWER, &i);
                    kehops.pwm[deviceId].config.dout_id = jRead_int((char *)srcDataBuffer, FILE_KEY_CONFIG_PWM_MAP_ID, &i);
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
                deviceId = jRead_int((char *)srcDataBuffer, FILE_KEY_CONFIG_DIN_ID, &i); 

                if(deviceId >= 0){
                    NBDIN++;
                    kehops.proximity[deviceId].config.din_id = jRead_int((char *)srcDataBuffer, FILE_KEY_CONFIG_DIN_MAP_ID, &i);
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
        
    // AOUT Setting
        jRead((char *)srcDataBuffer, FILE_KEY_CONFIG_AOUT, &cfg_devices_list );

        // RECHERCHE DATA DE TYPE ARRAY
        if(cfg_devices_list.dataType == JREAD_ARRAY ){
            // Get the number of AOUT in array
            nbOfDeviceInConf = cfg_devices_list.elements;

            // EXTRACT ANALOG SETTINGS FROM CONFIG    
              for(i=0;i<nbOfDeviceInConf;i++){
                  kehops.aout[i].config.aout_id = -1;
                  kehops.aout[i].config.defaultPower = 0;
                  kehops.aout[i].config.defaultState = 0;
                  kehops.aout[i].config.mode = 0;
              }
            
            for(i=0; i < nbOfDeviceInConf; i++){ 
                deviceId=-1;
                deviceId = jRead_int((char *)srcDataBuffer, FILE_KEY_CONFIG_AOUT_ID, &i); 
                if(deviceId >= 0){
                    NBAOUT++;
                    kehops.aout[deviceId].config.aout_id = jRead_int((char *)srcDataBuffer, FILE_KEY_CONFIG_AOUT_MAP_ID, &i);
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
                deviceId = jRead_int((char *)srcDataBuffer, FILE_KEY_CONFIG_BTN_ID, &i); 

                if(deviceId >= 0){
                    NBBTN++;
                    kehops.button[deviceId].config.din_id = jRead_int((char *)srcDataBuffer, FILE_KEY_CONFIG_BTN_MAP_ID, &i);
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
                deviceId = jRead_int((char *)srcDataBuffer, FILE_KEY_CONFIG_SONAR_ID, &i); 

                if(deviceId >= 0){
                    NBSONAR++;
                    kehops.sonar[deviceId].config.distanceSensor_id = jRead_int((char *)srcDataBuffer, FILE_KEY_CONFIG_SONAR_MAP_ID, &i); 
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

        // VOLTAGE Setting
        jRead((char *)srcDataBuffer, FILE_KEY_CONFIG_VOLTAGE, &cfg_devices_list );

        // RECHERCHE DATA DE TYPE ARRAY
        if(cfg_devices_list.dataType == JREAD_ARRAY ){
            // Get the number of VOLTAGE AIN in array
            nbOfDeviceInConf = cfg_devices_list.elements;
            for(i=0; i < nbOfDeviceInConf; i++){ 
                deviceId=-1;
                deviceId = jRead_int((char *)srcDataBuffer, FILE_KEY_CONFIG_VOLTAGE_ID, &i); 

                if(deviceId >= 0){
                    NBAIN++;
                    kehops.analogInput[deviceId].config.ain_id = jRead_int((char *)srcDataBuffer, FILE_KEY_CONFIG_VOLTAGE_MAP_ID, &i); 
                    jRead_string((char *)srcDataBuffer, FILE_KEY_CONFIG_VOLTAGE_EVENT_STATE, dataValue, 15, &i );
                    if(!strcmp(dataValue, "on")){
                        kehops.analogInput[deviceId].event.enable = 1;
                    }else
                        if(!strcmp(dataValue, "off")){
                            kehops.analogInput[deviceId].event.enable = 0;
                        }
                    kehops.analogInput[deviceId].event.low = jRead_int((char *)srcDataBuffer, FILE_KEY_CONFIG_VOLTAGE_EVENT_LOW, &i); 
                    kehops.analogInput[deviceId].event.high = jRead_int((char *)srcDataBuffer, FILE_KEY_CONFIG_VOLTAGE_EVENT_HIGH, &i); 
                    kehops.analogInput[deviceId].event.hysteresis = jRead_int((char *)srcDataBuffer, FILE_KEY_CONFIG_VOLTAGE_EVENT_HYST, &i); 
                }
            }
        }            

        // COLOR SENSORS Setting
        jRead((char *)srcDataBuffer, FILE_KEY_CONFIG_COLOR, &cfg_devices_list );

        // RECHERCHE DATA DE TYPE ARRAY
        if(cfg_devices_list.dataType == JREAD_ARRAY ){
            // Get the number of RGB sensors in array
            nbOfDeviceInConf = cfg_devices_list.elements;
            
            for(i=0; i < nbOfDeviceInConf; i++){ 
                deviceId=-1;
                deviceId = jRead_int((char *)srcDataBuffer, FILE_KEY_CONFIG_COLOR_ID, &i); 

                if(deviceId >= 0){
                    NBRGBC++;
                    kehops.rgb[deviceId].config.rgbID = jRead_int((char *)srcDataBuffer, FILE_KEY_CONFIG_COLOR_MAP_ID, &i); 
                    jRead_string((char *)srcDataBuffer, FILE_KEY_CONFIG_COLOR_EVENT_STATE, dataValue, 15, &i );
                    if(!strcmp(dataValue, "on")){
                        kehops.rgb[deviceId].config.event.enable = 1;
                    }else
                        if(!strcmp(dataValue, "off")){
                            kehops.rgb[deviceId].config.event.enable = 0;
                        }
                    
                    jReadParam((char *)srcDataBuffer, FILE_KEY_CONFIG_COLOR_RED, &cfg_devices, &i);
                    kehops.rgb[deviceId].color.red.event.low = jRead_int((char *)cfg_devices.pValue, FILE_KEY_CONFIG_COLOR_EVENT_LOW, &i); 
                    kehops.rgb[deviceId].color.red.event.high = jRead_int((char *)cfg_devices.pValue, FILE_KEY_CONFIG_COLOR_EVENT_HIGH, &i); 
                    kehops.rgb[deviceId].color.red.event.hysteresis = jRead_int((char *)cfg_devices.pValue, FILE_KEY_CONFIG_COLOR_EVENT_HYST, &i); 

                    jReadParam((char *)srcDataBuffer, FILE_KEY_CONFIG_COLOR_GREEN, &cfg_devices, &i);
                    kehops.rgb[deviceId].color.green.event.low = jRead_int((char *)cfg_devices.pValue, FILE_KEY_CONFIG_COLOR_EVENT_LOW, &i); 
                    kehops.rgb[deviceId].color.green.event.high = jRead_int((char *)cfg_devices.pValue, FILE_KEY_CONFIG_COLOR_EVENT_HIGH, &i); 
                    kehops.rgb[deviceId].color.green.event.hysteresis = jRead_int((char *)cfg_devices.pValue, FILE_KEY_CONFIG_COLOR_EVENT_HYST, &i); 

                    jReadParam((char *)srcDataBuffer, FILE_KEY_CONFIG_COLOR_BLUE, &cfg_devices, &i);
                    kehops.rgb[deviceId].color.blue.event.low = jRead_int((char *)cfg_devices.pValue, FILE_KEY_CONFIG_COLOR_EVENT_LOW, &i); 
                    kehops.rgb[deviceId].color.blue.event.high = jRead_int((char *)cfg_devices.pValue, FILE_KEY_CONFIG_COLOR_EVENT_HIGH, &i); 
                    kehops.rgb[deviceId].color.blue.event.hysteresis = jRead_int((char *)cfg_devices.pValue, FILE_KEY_CONFIG_COLOR_EVENT_HYST, &i);                     
                    
                }
            }
        }
        
        // DISPLAY Setting
        jRead((char *)srcDataBuffer, FILE_KEY_CONFIG_DISPLAY, &cfg_devices_list );

        // RECHERCHE DATA DE TYPE ARRAY
        if(cfg_devices_list.dataType == JREAD_ARRAY ){
            // Get the number of Display in array
            nbOfDeviceInConf = cfg_devices_list.elements
                    ;
            for(i=0; i < nbOfDeviceInConf; i++){ 
                deviceId=-1;
                deviceId = jRead_int((char *)srcDataBuffer, FILE_KEY_CONFIG_DISPLAY_ID, &i); 

                if(deviceId >= 0){
                    NBDISPLAY++;
                    kehops.gfx[deviceId].config.gfx_id = jRead_int((char *)srcDataBuffer, FILE_KEY_CONFIG_DISPLAY_MAP_ID, &i); 
                    jRead_string((char *)srcDataBuffer, FILE_KEY_CONFIG_HID_SCREEN, dataValue, 15, &i );
                    if(!strcmp(dataValue, "on")){
                        kehops.gfx[deviceId].config.hid.enable = 1;
                    }else
                        if(!strcmp(dataValue, "off")){
                            kehops.gfx[deviceId].config.hid.enable = 0;
                        }
                                        
                }
            }
        }         
        
        // Reset settings
//            jRead_string((char *)srcDataBuffer, KEY_MESSAGE_VALUE_CFG_APPRESET, AlgoidMessageRX.Config.config.reset, 15, &i );
        return 0;
    }
}


// -----------------------------------------------------------------------------
// SaveConfig
// Save configuration to file
// -----------------------------------------------------------------------------

char SaveKehopsConfig(char * fileName){
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
                        jwObj_int( "dc_motor_id", kehops.dcWheel[i].config.motor.dc_motor_id);
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
                for(i=0;i<NBWHEEL;i++){
                    jwArr_object();
                        jwObj_int( "wheel", i);
                        jwObj_int( "pulsesCounter_id", kehops.dcWheel[i].config.encoder.pulseCounter_id);
                        jwObj_int( "freqCounter_id", kehops.dcWheel[i].config.encoder.freqCounter_id);
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
                        jwObj_int( "dc_motor_id", kehops.stepperWheel[i].config.motor.stepper_motor_id);
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
                        jwObj_int( "dout_id", kehops.led[i].config.dout_id);
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
                        jwObj_int( "dout_id", kehops.pwm[i].config.dout_id);
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
                        jwObj_int( "din_id", kehops.proximity[i].config.din_id);
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
                        jwObj_int( "din_id", kehops.button[i].config.din_id);
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
                        jwObj_int( "distanceSensor_id", kehops.sonar[i].config.distanceSensor_id);
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
            
        // CREATE JSON CONFIG FOR VOLTAGE CONFIG
            jwObj_array("voltage");
                for(i=0;i<NBAIN;i++){
                    jwArr_object();
                        jwObj_int( "voltage", i);
                        jwObj_int( "ain_id", kehops.analogInput[i].config.ain_id);
                        if(kehops.analogInput[i].event.enable == 0)
                            jwObj_string("event", "off");
                        else 
                            if(kehops.analogInput[i].event.enable == 1)
                                jwObj_string("event", "on");
                        jwObj_int( "event_lower", kehops.analogInput[i].event.low);
                        jwObj_int( "event_higher", kehops.analogInput[i].event.high);
                        jwObj_int( "event_hysteresis", kehops.analogInput[i].event.hysteresis);
                    jwEnd();
                } 
            jwEnd();
        // CREATE JSON CONFIG FOR VOLTAGE CONFIG
            jwObj_array("display");
                for(i=0;i<NBDISPLAY;i++){
                    jwArr_object();
                        jwObj_int( "display", i);
                        jwObj_int( "display_id", kehops.gfx[i].config.gfx_id);
                        if(kehops.gfx[i].config.hid.enable == 0)
                            jwObj_string("screen_hid", "off");
                        else 
                            if(kehops.gfx[i].config.hid.enable == 1)
                                jwObj_string("screen_hid", "on");                        
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