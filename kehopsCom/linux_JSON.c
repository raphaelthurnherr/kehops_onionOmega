/*
 ============================================================================
 Name        : linux_JSON.c
 Author      : Raph
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */



#define KEY_TO "{'MsgTo'"
#define KEY_FROM "{'MsgFrom'"
#define KEY_MSGID "{'MsgID'"
#define KEY_MESSAGE ""
#define KEY_MESSAGE_TYPE "{'MsgData'{'MsgType'"
#define KEY_MESSAGE_PARAM "{'MsgData'{'MsgParam'"
#define KEY_MESSAGE_VALUE "{'MsgData'{'MsgValue'"

#define KEY_MESSAGE_VALUE_DIN "{'MsgData'{'MsgValue'[*{'din'"
#define KEY_MESSAGE_VALUE_BTN "{'MsgData'{'MsgValue'[*{'btn'"
#define KEY_MESSAGE_VALUE_SONAR "{'MsgData'{'MsgValue'[*{'sonar'"
#define KEY_MESSAGE_VALUE_ANGLE "{'MsgData'{'MsgValue'[*{'angle'"
#define KEY_MESSAGE_VALUE_BATT "{'MsgData'{'MsgValue'[*{'battery'"
#define KEY_MESSAGE_VALUE_RGB "{'MsgData'{'MsgValue'[*{'rgb'"

#define KEY_MESSAGE_VALUE_PWM "{'MsgData'{'MsgValue'[*{'pwm'"
#define KEY_MESSAGE_VALUE_LED "{'MsgData'{'MsgValue'[*{'led'"
#define KEY_MESSAGE_VALUE_POWER "{'MsgData'{'MsgValue'[*{'power'"
#define KEY_MESSAGE_VALUE_STATE "{'MsgData'{'MsgValue'[*{'state'"
#define KEY_MESSAGE_VALUE_COUNT "{'MsgData'{'MsgValue'[*{'count'"
#define KEY_MESSAGE_VALUE_POSPERCENT "{'MsgData'{'MsgValue'[*{'position'"


#define KEY_MESSAGE_VALUE_EVENT_STATE "{'MsgData'{'MsgValue'[*{'event'"
#define KEY_MESSAGE_VALUE_EVENT_LOWER "{'MsgData'{'MsgValue'[*{'event_lower'"
#define KEY_MESSAGE_VALUE_EVENT_HIGHER "{'MsgData'{'MsgValue'[*{'event_higher'"
#define KEY_MESSAGE_VALUE_EVENT_RED_LOWER "{'MsgData'{'MsgValue'[*{'red'{'event_lower'"
#define KEY_MESSAGE_VALUE_EVENT_RED_HIGHER "{'MsgData'{'MsgValue'[*{'red'{'event_higher'"
#define KEY_MESSAGE_VALUE_EVENT_GREEN_LOWER "{'MsgData'{'MsgValue'[*{'green'{'event_lower'"
#define KEY_MESSAGE_VALUE_EVENT_GREEN_HIGHER "{'MsgData'{'MsgValue'[*{'green'{'event_higher'"
#define KEY_MESSAGE_VALUE_EVENT_BLUE_LOWER "{'MsgData'{'MsgValue'[*{'blue'{'event_lower'"
#define KEY_MESSAGE_VALUE_EVENT_BLUE_HIGHER "{'MsgData'{'MsgValue'[*{'blue'{'event_higher'"
#define KEY_MESSAGE_VALUE_EVENT_CLEAR_LOWER "{'MsgData'{'MsgValue'[*{'clear'{'event_lower'"
#define KEY_MESSAGE_VALUE_EVENT_CLEAR_HIGHER "{'MsgData'{'MsgValue'[*{'clear'{'event_higher'"

#define KEY_MESSAGE_VALUE_MOTOR "{'MsgData'{'MsgValue'[*{'motor'"
#define KEY_MESSAGE_VALUE_VELOCITY "{'MsgData'{'MsgValue'[*{'velocity'"
#define KEY_MESSAGE_VALUE_TIME "{'MsgData'{'MsgValue'[*{'time'"
#define KEY_MESSAGE_VALUE_CM "{'MsgData'{'MsgValue'[*{'cm'"
#define KEY_MESSAGE_VALUE_STEP "{'MsgData'{'MsgValue'[*{'step'"
#define KEY_MESSAGE_VALUE_ROTATION "{'MsgData'{'MsgValue'[*{'rotation'"

#define KEY_MESSAGE_VALUE_CFG_RESET "{'MsgData'{'MsgValue'[*{'config'{'reset'"
#define KEY_MESSAGE_VALUE_CFG_SAVE "{'MsgData'{'MsgValue'[*{'config'{'save'"

#define KEY_MESSAGE_VALUE_CFG_STREAM_STATE "{'MsgData'{'MsgValue'[*{'stream'{'state'"
#define KEY_MESSAGE_VALUE_CFG_STREAM_TIME "{'MsgData'{'MsgValue'[*{'stream'{'time'"
#define KEY_MESSAGE_VALUE_CFG_STREAM_ONEVENT "{'MsgData'{'MsgValue'[*{'stream'{'onEvent'"

#define KEY_MESSAGE_VALUE_CFG_MOTOR "{'MsgData'{'MsgValue'[*{'motor'"
#define KEY_MESSAGE_VALUE_CFG_MOTOR_ID "{'MsgData'{'MsgValue'[{'motor'[*{'motor'"
#define KEY_MESSAGE_VALUE_CFG_MOTOR_INVERT "{'MsgData'{'MsgValue'[{'motor'[*{'inverted'"
#define KEY_MESSAGE_VALUE_CFG_MOTOR_MINPWM "{'MsgData'{'MsgValue'[{'motor'[*{'pwmMin'"
#define KEY_MESSAGE_VALUE_CFG_MOTOR_MINRPM "{'MsgData'{'MsgValue'[{'motor'[*{'rpmMin'"
#define KEY_MESSAGE_VALUE_CFG_MOTOR_MAXRPM "{'MsgData'{'MsgValue'[{'motor'[*{'rpmMax'"
#define KEY_MESSAGE_VALUE_CFG_MOTOR_PIDREG "{'MsgData'{'MsgValue'[{'motor'[*{'rpmRegulator'{'state'"
#define KEY_MESSAGE_VALUE_CFG_MOTOR_PIDKP "{'MsgData'{'MsgValue'[{'motor'[*{'rpmRegulator'{'PID_Kp'"
#define KEY_MESSAGE_VALUE_CFG_MOTOR_PIDKI "{'MsgData'{'MsgValue'[{'motor'[*{'rpmRegulator'{'PID_Ki'"
#define KEY_MESSAGE_VALUE_CFG_MOTOR_PIDKD "{'MsgData'{'MsgValue'[{'motor'[*{'rpmRegulator'{'PID_Kd'"

#define KEY_MESSAGE_VALUE_CFG_WHEEL "{'MsgData'{'MsgValue'[*{'wheel'"
#define KEY_MESSAGE_VALUE_CFG_WHEEL_ID "{'MsgData'{'MsgValue'[{'wheel'[*{'wheel'"
#define KEY_MESSAGE_VALUE_CFG_WHEEL_DIAMETER "{'MsgData'{'MsgValue'[{'wheel'[*{'diameter'"
#define KEY_MESSAGE_VALUE_CFG_WHEEL_PULSES "{'MsgData'{'MsgValue'[{'wheel'[*{'pulses'"

#define KEY_MESSAGE_VALUE_CFG_STEPPER "{'MsgData'{'MsgValue'[*{'stepper'"
#define KEY_MESSAGE_VALUE_CFG_STEPPER_ID "{'MsgData'{'MsgValue'[{'stepper'[*{'motor'"
#define KEY_MESSAGE_VALUE_CFG_STEPPER_INVERT "{'MsgData'{'MsgValue'[{'stepper'[*{'inverted'"
#define KEY_MESSAGE_VALUE_CFG_STEPPER_RATIO "{'MsgData'{'MsgValue'[{'stepper'[*{'ratio'"
#define KEY_MESSAGE_VALUE_CFG_STEPPER_STEPS "{'MsgData'{'MsgValue'[{'stepper'[*{'steps'"

#define KEY_MESSAGE_VALUE_CFG_LED "{'MsgData'{'MsgValue'[*{'led'"
#define KEY_MESSAGE_VALUE_CFG_LED_ID "{'MsgData'{'MsgValue'[{'led'[*{'led'"
#define KEY_MESSAGE_VALUE_CFG_LED_STATE "{'MsgData'{'MsgValue'[{'led'[*{'state'"
#define KEY_MESSAGE_VALUE_CFG_LED_POWER "{'MsgData'{'MsgValue'[{'led'[*{'power'"

#define KEY_MESSAGE_VALUE_SYS_APP "{'MsgData'{'MsgValue'[*{'application'"
#define KEY_MESSAGE_VALUE_SYS_FIRMWARE "{'MsgData'{'MsgValue'[*{'firmware'"
#define KEY_MESSAGE_VALUE_SYS_WEBAPP "{'MsgData'{'MsgValue'[*{'webAppUpdate'"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "type.h"
#include "../buggy_descriptor.h"
#include "linux_json.h"
#include "libs/lib_json/jRead.h"
#include "libs/lib_json/jWrite.h"

void jsonBuilder(char * buffer, int msgId, char* to, char * from, char * msgType,char * msgParam, unsigned char orgType, unsigned char count);
char GetAlgoidMsg(ALGOID *destMessage, char *srcDataBuffer);

ALGOID myReplyMessage;

// -----------------------------------------------------------------------------
// MAIN, APPLICATION PRINCIPALE-------------------------------------------------
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// GetAlgoidMsg
// Get message from buffer and set in the message structure
// -----------------------------------------------------------------------------

char GetAlgoidMsg(ALGOID *destMessage, char *srcBuffer){
	struct jReadElement element, cfg_device_list;
	int i;
        ALGOID myMessage;
        //myMessage = &destMessage;
        
	// ENTETE DE MESSAGE
		jRead_string((char *)srcBuffer, KEY_TO, destMessage->msgTo, 15, NULL );
		jRead_string((char *)srcBuffer, KEY_FROM, destMessage->msgFrom, 15, NULL );
		destMessage->msgID= jRead_int((char *)srcBuffer,  KEY_MSGID, NULL);

	// MESSAGE TYPE
				char myDataString[20];
				// Clear string
				for(i=0;i<20;i++) myDataString[i]=0;

				jRead_string((char *)srcBuffer,  KEY_MESSAGE_TYPE,myDataString,15, NULL);

				destMessage->msgType= ERR_TYPE;
				if(!strcmp(myDataString, "command")) destMessage->msgType = COMMAND;
				if(!strcmp(myDataString, "request")) destMessage->msgType = REQUEST;
				if(!strcmp(myDataString, "ack")) destMessage->msgType = ACK;
				if(!strcmp(myDataString, "response")) destMessage->msgType = RESPONSE;
				if(!strcmp(myDataString, "event")) destMessage->msgType = EVENT;
				if(!strcmp(myDataString, "error")) destMessage->msgType = ERR_TYPE;

	// MESSAGE PARAM
				// Clear string
				for(i=0;i<20;i++) myDataString[i]=0;
				jRead_string((char *)srcBuffer,  KEY_MESSAGE_PARAM,myDataString,15, NULL);

				destMessage->msgParam=ERR_PARAM;
					if(!strcmp(myDataString, "stop")) destMessage->msgParam = STOP;
					if(!strcmp(myDataString, "motor")) destMessage->msgParam = MOTORS;
					if(!strcmp(myDataString, "pwm")) destMessage->msgParam = pPWM;
					if(!strcmp(myDataString, "led")) destMessage->msgParam = pLED;
                                        if(!strcmp(myDataString, "servo")) destMessage->msgParam = pSERVO;
                                        if(!strcmp(myDataString, "button")) destMessage->msgParam = BUTTON;
					if(!strcmp(myDataString, "distance")) destMessage->msgParam = DISTANCE;
					if(!strcmp(myDataString, "battery")) destMessage->msgParam = BATTERY;
					if(!strcmp(myDataString, "din")) destMessage->msgParam = DINPUT;
					if(!strcmp(myDataString, "status")) destMessage->msgParam = STATUS;
                                        if(!strcmp(myDataString, "rgb")) destMessage->msgParam = COLORS;
                                        if(!strcmp(myDataString, "config")) destMessage->msgParam = CONFIG;
                                        if(!strcmp(myDataString, "system")) destMessage->msgParam = SYSTEM;
                                        if(!strcmp(myDataString, "stepper")) destMessage->msgParam = STEPPER;

				  jRead((char *)srcBuffer, KEY_MESSAGE_VALUE, &element );

                                    // RECHERCHE DATA ARRAY
				  if(element.dataType == JREAD_ARRAY ){
                                    destMessage->msgValueCnt=element.elements;

				      for(i=0; i<element.elements; i++ )    // loop for no. of elements in JSON
				      {
				    	  if(destMessage->msgParam == MOTORS){
				    		  destMessage->DCmotor[i].motor=UNKNOWN;	// Initialisation roue inconnue
				    		  //jRead_string((char *)srcBuffer, KEY_MESSAGE_VALUE_MOTOR, myDataString, 15, &i );
                                                  destMessage->DCmotor[i].motor= jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_MOTOR, &i);
                                                 
					    	  destMessage->DCmotor[i].velocity= jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_VELOCITY, &i);
					    	  destMessage->DCmotor[i].time= jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_TIME, &i);
					    	  destMessage->DCmotor[i].cm= jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_CM, &i);
				    	  }
                                          
                                            if(destMessage->msgParam == STEPPER){
                                                destMessage->StepperMotor[i].motor=UNKNOWN;	// Initialisation roue inconnue
                                                //jRead_string((char *)srcBuffer, KEY_MESSAGE_VALUE_MOTOR, myDataString, 15, &i );
                                                destMessage->StepperMotor[i].motor= jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_MOTOR, &i);

                                                destMessage->StepperMotor[i].velocity= jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_VELOCITY, &i);
                                                destMessage->StepperMotor[i].angle= jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_ANGLE, &i);
                                                destMessage->StepperMotor[i].step= jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_STEP, &i);
                                                destMessage->StepperMotor[i].rotation= jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_ROTATION, &i);
                                                destMessage->StepperMotor[i].time= jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_TIME, &i);
                                            }

				    	  if(destMessage->msgParam == DINPUT){
						 destMessage->DINsens[i].id= jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_DIN, &i);
				    		 jRead_string((char *)srcBuffer, KEY_MESSAGE_VALUE_EVENT_STATE, destMessage->DINsens[i].event_state, 15, &i );
				    	  }
                                          
                                          if(destMessage->msgParam == BUTTON){
						 destMessage->BTNsens[i].id= jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_BTN, &i);
				    		 jRead_string((char *)srcBuffer, KEY_MESSAGE_VALUE_EVENT_STATE, destMessage->BTNsens[i].event_state, 15, &i );
				    	  }

				    	  if(destMessage->msgParam == DISTANCE){
				    		  jRead_string((char *)srcBuffer, KEY_MESSAGE_VALUE_EVENT_STATE, destMessage->DISTsens[i].event_state, 15, &i );
				    		  destMessage->DISTsens[i].id= jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_SONAR, &i);
				    		  destMessage->DISTsens[i].angle= jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_ANGLE, &i);
				    		  destMessage->DISTsens[i].event_low= jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_EVENT_LOWER, &i);
				    		  destMessage->DISTsens[i].event_high= jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_EVENT_HIGHER, &i);
				    	  }

                                          if(destMessage->msgParam == COLORS){
				    		  jRead_string((char *)srcBuffer, KEY_MESSAGE_VALUE_EVENT_STATE, destMessage->RGBsens[i].event_state, 15, &i );
				    		  destMessage->RGBsens[i].id= jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_RGB, &i);
				    		  destMessage->RGBsens[i].red.event_low= jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_EVENT_RED_LOWER, &i);
				    		  destMessage->RGBsens[i].red.event_high= jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_EVENT_RED_HIGHER, &i);
                                                  destMessage->RGBsens[i].green.event_low= jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_EVENT_GREEN_LOWER, &i);
				    		  destMessage->RGBsens[i].green.event_high= jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_EVENT_GREEN_HIGHER, &i);
                                                  destMessage->RGBsens[i].blue.event_low= jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_EVENT_BLUE_LOWER, &i);
				    		  destMessage->RGBsens[i].blue.event_high= jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_EVENT_BLUE_HIGHER, &i);
                                                  destMessage->RGBsens[i].clear.event_low= jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_EVENT_CLEAR_LOWER, &i);
				    		  destMessage->RGBsens[i].clear.event_high= jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_EVENT_CLEAR_HIGHER, &i);
				    	  }

                                          // BATTERY
				    	  if(destMessage->msgParam == BATTERY){
				    		  jRead_string((char *)srcBuffer, KEY_MESSAGE_VALUE_EVENT_STATE, destMessage->BATTsens[i].event_state, 15, &i );
				    		  destMessage->BATTsens[i].id= jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_BATT, &i);
				    		  destMessage->BATTsens[i].event_low= jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_EVENT_LOWER, &i);
				    		  destMessage->BATTsens[i].event_high= jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_EVENT_HIGHER, &i);
				    	  }
                                          
                                          // LED
				    	  if(destMessage->msgParam == pLED){
                                                  destMessage->LEDarray[i].time=-1;
                                                  destMessage->LEDarray[i].powerPercent=-1;
                                                  strcpy(destMessage->LEDarray[i].state,"null");
                                                  destMessage->LEDarray[i].blinkCount=-1;
                                                  
				    		  jRead_string((char *)srcBuffer, KEY_MESSAGE_VALUE_STATE, destMessage->LEDarray[i].state, 15, &i );
				    		  int ledId=jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_LED, &i);
				    		  destMessage->LEDarray[i].id=ledId;
				    		  destMessage->LEDarray[i].powerPercent= jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_POWER, &i);                                                  
                                                  destMessage->LEDarray[i].time= jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_TIME, &i);
                                                  destMessage->LEDarray[i].blinkCount= jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_COUNT, &i);
				    	  }
                                          
                                          // PWM
				    	  if(destMessage->msgParam == pPWM){
                                                  destMessage->PWMarray[i].time=-1;
                                                  destMessage->PWMarray[i].powerPercent=-1;
                                                  strcpy(destMessage->PWMarray[i].state,"null");
                                                  destMessage->PWMarray[i].blinkCount=-1;
				    		  
                                                  jRead_string((char *)srcBuffer, KEY_MESSAGE_VALUE_STATE, destMessage->PWMarray[i].state, 15, &i );
				    		  int pwmId=jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_PWM, &i);
				    		  destMessage->PWMarray[i].id=pwmId;
				    		  destMessage->PWMarray[i].powerPercent= jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_POWER, &i);                                                  
                                                  destMessage->PWMarray[i].time= jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_TIME, &i);
                                                  destMessage->PWMarray[i].blinkCount= jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_COUNT, &i);
				    	  }
                                          
                                          // SERVO
				    	  if(destMessage->msgParam == pSERVO){
                                                  destMessage->PWMarray[i].time=-1;
                                                  destMessage->PWMarray[i].powerPercent=-1;
                                                  strcpy(destMessage->PWMarray[i].state,"null");
                                                  destMessage->PWMarray[i].blinkCount=-1;
                                                  
				    		  jRead_string((char *)srcBuffer, KEY_MESSAGE_VALUE_STATE, destMessage->PWMarray[i].state, 15, &i );
				    		  int pwmId=jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_PWM, &i);
				    		  destMessage->PWMarray[i].id=pwmId;
				    		  destMessage->PWMarray[i].powerPercent= jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_POSPERCENT, &i);                                                                                                   
				    	  }

                                        // STATUS
				    	  if(destMessage->msgParam == STATUS){
                                                  // Nothing to get, return status of all system
				    	  }
                                          
                                        // CONFIGURATION
                                          if(destMessage->msgParam == CONFIG){
                                              int nbOfdeviceInConf;
                                              int i_dev;
                                              
                                              for(i_dev=0;i_dev<4;i_dev++){
                                                destMessage->Config.motor[i_dev].id=-1;
                                              }
                                              
                                            // Stream settings
                                                  jRead_string((char *)srcBuffer, KEY_MESSAGE_VALUE_CFG_STREAM_STATE, destMessage->Config.stream.state, 15, &i );
                                                  destMessage->Config.stream.time= jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_CFG_STREAM_TIME, &i);
                                                  jRead_string((char *)srcBuffer, KEY_MESSAGE_VALUE_CFG_STREAM_ONEVENT, destMessage->Config.stream.onEvent, 15, &i );
                                                  
                                            // Motor Setting
                                                jRead((char *)srcBuffer, KEY_MESSAGE_VALUE_CFG_MOTOR, &cfg_device_list );

                                                // RECHERCHE DATA DE TYPE ARRAY
                                                if(cfg_device_list.dataType == JREAD_ARRAY ){
                                                    // Get the number of motors in array
                                                    nbOfdeviceInConf=cfg_device_list.elements;
                                                    destMessage->Config.motValueCnt=nbOfdeviceInConf;
                                                    
                                                    for(i_dev=0; i_dev < nbOfdeviceInConf; i_dev++){                 
                                                        destMessage->Config.motor[i_dev].id=jRead_int((char *)srcBuffer, KEY_MESSAGE_VALUE_CFG_MOTOR_ID, &i_dev); 
                                                        destMessage->Config.motor[i_dev].minRPM=jRead_int((char *)srcBuffer, KEY_MESSAGE_VALUE_CFG_MOTOR_MINRPM, &i_dev); 
                                                        destMessage->Config.motor[i_dev].maxRPM=jRead_int((char *)srcBuffer, KEY_MESSAGE_VALUE_CFG_MOTOR_MAXRPM, &i_dev); 
                                                        destMessage->Config.motor[i_dev].minPWM=jRead_int((char *)srcBuffer, KEY_MESSAGE_VALUE_CFG_MOTOR_MINPWM, &i_dev); 
                                                        jRead_string((char *)srcBuffer, KEY_MESSAGE_VALUE_CFG_MOTOR_INVERT, destMessage->Config.motor[i_dev].inverted, 15, &i_dev ); 
                                                        jRead_string((char *)srcBuffer, KEY_MESSAGE_VALUE_CFG_MOTOR_PIDREG, destMessage->Config.motor[i_dev].rpmRegulator.PIDstate, 15, &i_dev ); 
                                                        destMessage->Config.motor[i_dev].rpmRegulator.PID_Kp=jRead_double((char *)srcBuffer, KEY_MESSAGE_VALUE_CFG_MOTOR_PIDKP, &i_dev); 
                                                        destMessage->Config.motor[i_dev].rpmRegulator.PID_Ki=jRead_double((char *)srcBuffer, KEY_MESSAGE_VALUE_CFG_MOTOR_PIDKI, &i_dev); 
                                                        destMessage->Config.motor[i_dev].rpmRegulator.PID_Kd=jRead_double((char *)srcBuffer, KEY_MESSAGE_VALUE_CFG_MOTOR_PIDKD, &i_dev); 
                                                        
                                                    }
                                                }

                                            // Wheel Setting
                                                jRead((char *)srcBuffer, KEY_MESSAGE_VALUE_CFG_WHEEL, &cfg_device_list );

                                                // RECHERCHE DATA DE TYPE ARRAY
                                                if(cfg_device_list.dataType == JREAD_ARRAY ){
                                                    // Get the number of motors in array
                                                    nbOfdeviceInConf=cfg_device_list.elements;
                                                    destMessage->Config.wheelValueCnt=nbOfdeviceInConf;
                                                    
                                                    for(i_dev=0; i_dev < nbOfdeviceInConf; i_dev++){                 
                                                        destMessage->Config.wheel[i_dev].id=jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_CFG_WHEEL_ID, &i_dev); 
                                                        destMessage->Config.wheel[i_dev].diameter=jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_CFG_WHEEL_DIAMETER, &i_dev); 
                                                        destMessage->Config.wheel[i_dev].pulsesPerRot=jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_CFG_WHEEL_PULSES, &i_dev);
                                                    }
                                                }                                                
                                                
                                                // Stepper motor Setting
                                                jRead((char *)srcBuffer, KEY_MESSAGE_VALUE_CFG_STEPPER, &cfg_device_list );

                                                // RECHERCHE DATA DE TYPE ARRAY
                                                if(cfg_device_list.dataType == JREAD_ARRAY ){
                                                    // Get the number of motors in array
                                                    nbOfdeviceInConf=cfg_device_list.elements;
                                                    destMessage->Config.stepperValueCnt=nbOfdeviceInConf;
                                                    
                                                    for(i_dev=0; i_dev < nbOfdeviceInConf; i_dev++){                 
                                                        destMessage->Config.stepper[i_dev].id=jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_CFG_STEPPER_ID, &i_dev); 
                                                        jRead_string((char *)srcBuffer, KEY_MESSAGE_VALUE_CFG_STEPPER_INVERT, destMessage->Config.stepper[i_dev].inverted, 15, &i_dev ); 
                                                        destMessage->Config.stepper[i_dev].ratio=jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_CFG_STEPPER_RATIO, &i_dev); 
                                                        destMessage->Config.stepper[i_dev].stepsPerRot=jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_CFG_STEPPER_STEPS, &i_dev); 
                                                    }
                                                }
                                                
                                            // LEDS Setting
                                                jRead((char *)srcBuffer, KEY_MESSAGE_VALUE_CFG_LED, &cfg_device_list );

                                                // RECHERCHE DATA DE TYPE ARRAY
                                                if(cfg_device_list.dataType == JREAD_ARRAY ){
                                                    // Get the number of leds in array
                                                    nbOfdeviceInConf=cfg_device_list.elements;
                                                    destMessage->Config.ledValueCnt=nbOfdeviceInConf;
                                                    
                                                    for(i_dev=0; i_dev < nbOfdeviceInConf; i_dev++){
                                                        destMessage->Config.led[i_dev].id=jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_CFG_LED_ID, &i_dev); 
                                                        destMessage->Config.led[i_dev].power=jRead_long((char *)srcBuffer, KEY_MESSAGE_VALUE_CFG_LED_POWER, &i_dev); 
                                                        jRead_string((char *)srcBuffer, KEY_MESSAGE_VALUE_CFG_LED_STATE, destMessage->Config.led[i_dev].state, 15, &i_dev ); 
                                                    }
                                                }                                                
                                                
                                            // Reset settings
                                                jRead_string((char *)srcBuffer, KEY_MESSAGE_VALUE_CFG_RESET, destMessage->Config.config.reset, 15, &i );
                                            // Save settings
                                                jRead_string((char *)srcBuffer, KEY_MESSAGE_VALUE_CFG_SAVE, destMessage->Config.config.save, 15, &i );
				    	  }
                                          
                                        // SYSTEM                                          
                                          if(destMessage->msgParam == SYSTEM){
                                                  jRead_string((char *)srcBuffer, KEY_MESSAGE_VALUE_SYS_FIRMWARE, destMessage->System.firmwareUpdate, 15, &i );
                                                  jRead_string((char *)srcBuffer, KEY_MESSAGE_VALUE_SYS_APP, destMessage->System.application, 15, &i );
				    	  }
				    }
				  }
				  else
					  destMessage->msgValueCnt=0;

				  if((destMessage->msgParam == ERR_PARAM) || (destMessage->msgType == ERR_TYPE)){
					  return 0;
				  }else
					  return 1;
}

// -----------------------------------------------------------------------------
// replyToHost
// convert the structure in JSON format & Send to host
// -----------------------------------------------------------------------------
void jsonBuilder(char * buffer, int msgId, char* to, char* from, char* msgType, char* msgParam, unsigned char orgType, unsigned char count ){
	unsigned int buflen= MAX_MQTT_BUFF;
	unsigned char i,j;
        
// Formatage de la réponse en JSON
	jwOpen( buffer, buflen, JW_OBJECT, JW_PRETTY );		// start root object
		jwObj_string( "MsgTo", to );				// add object key:value pairs
		jwObj_string( "MsgFrom", from );				// add object key:value pairs
		jwObj_int( "MsgID", msgId );
		jwObj_object( "MsgData" );
			jwObj_string( "MsgType", msgType );				// add object key:value pairs
			if(msgParam!=0) jwObj_string( "MsgParam", msgParam );				// add object key:value pairs

			if(count>0){

				//
                                if(orgType==STATUS)
                                    jwObj_object("MsgMap");
                                else
                                    jwObj_array( "MsgValue" );
                                
				for(i=0;i<count;i++){
					//printf("Make array: %d values: %d %d\n", i, 0,9);
					if(orgType!=STATUS)
                                            jwArr_object();

						switch(orgType){
							case MOTORS :                   
                                                                            switch(messageResponse[i].responseType){
                                                                                case EVENT_ACTION_ERROR : jwObj_string("action", "error"); break;
                                                                                case EVENT_ACTION_END : jwObj_string("action", "end"); break;
                                                                                case EVENT_ACTION_BEGIN : jwObj_string("action", "begin"); break;
                                                                                case EVENT_ACTION_RUN : jwObj_string("action", "run"); break;
                                                                                case EVENT_ACTION_ABORT : jwObj_string("action", "abort"); break;
                                                                                case RESP_STD_MESSAGE   :   if(messageResponse[i].MOTresponse.motor>=0)
                                                                                                                jwObj_int( "motor", messageResponse[i].MOTresponse.motor);
                                                                                                            else
                                                                                                                jwObj_string("motor", "unknown");
                                                                                                            jwObj_int( "cm", messageResponse[i].MOTresponse.cm);				// add object key:value pairs
                                                                                                            jwObj_int( "time", messageResponse[i].MOTresponse.time);				// add object key:value pairs
                                                                                                            jwObj_int("velocity", round((messageResponse[i].MOTresponse.velocity)));
                                                                                                            ; break;
                                                                                default : jwObj_string("error", "unknown"); break;
                                                                            }
                                                                            break;

							case STEPPER :                   
                                                                            switch(messageResponse[i].responseType){
                                                                                case EVENT_ACTION_ERROR : jwObj_string("action", "error"); break;
                                                                                case EVENT_ACTION_END : jwObj_string("action", "end"); break;
                                                                                case EVENT_ACTION_BEGIN : jwObj_string("action", "begin"); break;
                                                                                case EVENT_ACTION_RUN : jwObj_string("action", "run"); break;
                                                                                case EVENT_ACTION_ABORT : jwObj_string("action", "abort"); break;
                                                                                case RESP_STD_MESSAGE   :   if(messageResponse[i].STEPPERresponse.motor>=0)
                                                                                                                jwObj_int( "motor", messageResponse[i].STEPPERresponse.motor);
                                                                                                            else
                                                                                                                jwObj_string("motor", "unknown");
                                                                                                            jwObj_int( "step", messageResponse[i].STEPPERresponse.step);				// add object key:value pairs
                                                                                                            jwObj_int( "rotation", messageResponse[i].STEPPERresponse.rotation);				// add object key:value pairs
                                                                                                            jwObj_int("velocity", round((messageResponse[i].STEPPERresponse.velocity)));
                                                                                                            ; break;
                                                                                default : jwObj_string("error", "unknown"); break;
                                                                            }
                                                                            break;                                                                            

							case DISTANCE :                 
                                                                            jwObj_int( "sonar",messageResponse[i].DISTresponse.id);

                                                                            // add object key:value pairs
                                                                            if(messageResponse[i].value >= 0){
                                                                                    jwObj_int("cm", round((messageResponse[i].value)));					// add object key:value pairs
                                                                                    //jwObj_int("angle", messageResponse[i].DISTresponse.angle);				// add object key:value pairs
                                                                                    jwObj_string("event", messageResponse[i].DISTresponse.event_state);				// add object key:value pairs
                                                                                    jwObj_int("event_lower", messageResponse[i].DISTresponse.event_low);				// add object key:value pairs
                                                                                    jwObj_int("event_higher", messageResponse[i].DISTresponse.event_high);				// add object key:value pairs
                                                                            } else
                                                                                    jwObj_string("cm", "error");

                                                                            break;

							case COLORS :                 
                                                                            jwObj_int( "rgb",messageResponse[i].RGBresponse.id);
                                                                            jwObj_string("event", messageResponse[i].RGBresponse.event_state);


                                                                                jwObj_object("color");
                                                                                    jwObj_int("red", messageResponse[i].RGBresponse.red.value);
                                                                                    jwObj_int("green", messageResponse[i].RGBresponse.green.value);
                                                                                    jwObj_int("blue", messageResponse[i].RGBresponse.blue.value);
                                                                                    jwObj_int("clear", messageResponse[i].RGBresponse.clear.value);
                                                                                jwEnd();

                                                                            jwObj_object( "red" );                                                                                 
                                                                                    jwObj_int("event_lower", messageResponse[i].RGBresponse.red.event_low);
                                                                                    jwObj_int("event_higher", messageResponse[i].RGBresponse.red.event_high);
                                                                            jwEnd();

                                                                            jwObj_object( "green" );                                                                                 
                                                                                    jwObj_int("event_lower", messageResponse[i].RGBresponse.green.event_low);
                                                                                    jwObj_int("event_higher", messageResponse[i].RGBresponse.green.event_high);           
                                                                            jwEnd(); 

                                                                            jwObj_object( "blue" );                                                                                 
                                                                                    jwObj_int("event_lower", messageResponse[i].RGBresponse.blue.event_low);
                                                                                    jwObj_int("event_higher", messageResponse[i].RGBresponse.blue.event_high);
                                                                            jwEnd();

                                                                            jwObj_object( "clear" );                                                                                 
                                                                                    jwObj_int("event_lower", messageResponse[i].RGBresponse.clear.event_low);
                                                                                    jwObj_int("event_higher", messageResponse[i].RGBresponse.clear.event_high);
                                                                            jwEnd(); 

                                                                            break;                                                                                

							case BATTERY :                  
                                                                            jwObj_int( "battery",messageResponse[i].BATTesponse.id);

                                                                            // add object key:value pairs
                                                                            if(messageResponse[i].value >= 0){
                                                                                    jwObj_int("mV", messageResponse[i].value);
                                                                                    jwObj_int("capacity", messageResponse[i].BATTesponse.capacity);// add object key:value pairs
                                                                                    jwObj_string("event", messageResponse[i].BATTesponse.event_state);				// add object key:value pairs
                                                                                    jwObj_int("event_lower", messageResponse[i].BATTesponse.event_low);				// add object key:value pairs
                                                                                    jwObj_int("event_higher", messageResponse[i].BATTesponse.event_high);				// add object key:value pairs
                                                                                    jwObj_string("mV", "error");
                                                                            }

                                                                            break;

							case DINPUT :           
                                                                            jwObj_int("din",messageResponse[i].DINresponse.id);	
                                                                            if(messageResponse[i].value >= 0){

                                                                                                     // add object key:value pairs
                                                                                 if(messageResponse[i].value >= 0){
                                                                                         jwObj_int( "state", messageResponse[i].value);				// add object key:value pairs
                                                                                         jwObj_string("event", messageResponse[i].DINresponse.event_state);			// Etat des evenements DIN
                                                                                 } else
                                                                                         jwObj_string("state", "error");
                                                                             }
                                                                            else{
                                                                                 jwObj_string("state", "error");
                                                                            }
                                                                            break;
                                                                                    
							case BUTTON :                  
                                                                            jwObj_int("btn",messageResponse[i].BTNresponse.id);	
                                                                               if(messageResponse[i].value >= 0){

                                                                                                        // add object key:value pairs
                                                                                    if(messageResponse[i].value >= 0){
                                                                                            jwObj_int( "state", messageResponse[i].value);				// add object key:value pairs
                                                                                            jwObj_string("event", messageResponse[i].BTNresponse.event_state);				// add object key:value pairs
                                                                                    } else
                                                                                            jwObj_string("state", "error");
                                                                                }
                                                                               else{
                                                                                    jwObj_string("state", "error");
                                                                               }
                                                                            break;                                                                                    

                                                        case STATUS :               
                                                                            // ETAT DU SYSTEM
                                                                            if(i==0){
                                                                                char wanState[10];

                                                                                jwObj_string("name", messageResponse[i].SYSresponse.name);
                                                                                jwObj_double("upTime",messageResponse[i].SYSresponse.startUpTime);
                                                                                jwObj_string("firmwareVersion",messageResponse[i].SYSresponse.firmwareVersion);	
                                                                                jwObj_string("mcuVersion",messageResponse[i].SYSresponse.mcuVersion);
                                                                                jwObj_string("boardRev",messageResponse[i].SYSresponse.HWrevision);
                                                                                jwObj_double("battery_mv",messageResponse[i].SYSresponse.battVoltage);
                                                                                jwObj_double("battery_capacity",messageResponse[i].SYSresponse.battPercent);                                                                                // add object key:value pairs
                                                                                if(messageResponse[i].SYSresponse.wan_online)
                                                                                    strcpy(wanState, "online");
                                                                                else
                                                                                    strcpy(wanState, "offline");
                                                                                jwObj_string("internet",wanState);                                              // WAN State
                                                                                jwObj_double("messageTX",messageResponse[i].SYSresponse.tx_message);		// System message received
                                                                                jwObj_double("messageRX",messageResponse[i].SYSresponse.rx_message);		// System message received
                                                                            }

                                                                            // ETAT DES DIN
                                                                            if(i>=1 && i<1+NBDIN){
//                                                                                        jwObj_int("din",messageResponse[i].DINresponse.id);		// add object key:value pairs
//                                                                                        jwObj_int( "state", messageResponse[i].value);
                                                                                jwObj_array( "din" );

                                                                                    for(j=0;j<NBDIN;j++){
                                                                                        jwArr_object();
                                                                                            jwObj_int("state",messageResponse[i].value);
                                                                                            jwObj_string("event", messageResponse[i].DINresponse.event_state);			// Etat des evenements DIN
                                                                                        jwEnd();           
                                                                                        i++;
                                                                                    }
                                                                                jwEnd();       
                                                                            }

                                                                            // ETAT DES BOUTON     
                                                                            if(i>=1+NBDIN && i<1+NBDIN+NBBTN){
                                                                            //    jwObj_int("btn",messageResponse[i].BTNresponse.id);		// add object key:value pairs
                                                                            //    jwObj_int( "state", messageResponse[i].value);
                                                                                jwObj_array( "btn" );
                                                                                    for(j=0;j<NBBTN;j++){
                                                                                        jwArr_object();
                                                                                            jwObj_int("state",messageResponse[i].value);
                                                                                            jwObj_string("event", messageResponse[i].BTNresponse.event_state);				// add object key:value pairs                                                                                            
                                                                                        jwEnd();           
                                                                                        i++;
                                                                                    }
                                                                                jwEnd();     
                                                                            }


                                                                            // ETAT DES MOTEUR                                                                                        // ETAT DES AIN                                                                                       // ETAT DES DIN
                                                                            if(i>=1+NBDIN+NBBTN && i<1+NBDIN+NBBTN+NBMOTOR){
                                                                            //        jwObj_int("motor",messageResponse[i].PWMresponse.id);		// add object key:value pairs
                                                                            //        jwObj_int("cm", round((messageResponse[i].MOTresponse.cm)));		// add object key:value pairs
                                                                            //        jwObj_int("speed", round((messageResponse[i].MOTresponse.velocity)));
                                                                                jwObj_array( "motor" );
                                                                                    for(j=0;j<NBMOTOR;j++){
                                                                                        jwArr_object();
                                                                                            jwObj_double("cm",(messageResponse[i].MOTresponse.cm));
                                                                                            jwObj_int("speed",round((messageResponse[i].MOTresponse.speed)));
                                                                                            jwObj_int("setpoint",messageResponse[i].MOTresponse.velocity);
                                                                                        jwEnd();           
                                                                                        i++;
                                                                                    }
                                                                                jwEnd(); 
                                                                            }

                                                                            // ETAT DU SONAR                                                                                        // ETAT DES AIN                                                                                       // ETAT DES DIN
                                                                            if(i>=1+NBDIN+NBBTN+NBMOTOR && i<1+NBDIN+NBBTN+NBMOTOR+NBSONAR){
                                                                            //    jwObj_int("sonar",messageResponse[i].DISTresponse.id);		// add object key:value pairs
                                                                            //    jwObj_int("cm", round((messageResponse[i].value)));
                                                                                jwObj_array( "sonar" );
                                                                                    for(j=0;j<NBSONAR;j++){
                                                                                        jwArr_object();
                                                                                            jwObj_int("cm", round((messageResponse[i].value)));
                                                                                            jwObj_string("event", messageResponse[i].DISTresponse.event_state);                                                                                            
                                                                                        jwEnd();           
                                                                                        i++;
                                                                                    }
                                                                                jwEnd(); 
                                                                            }

                                                                            // ETAT DES CAPTEURS RGB                                                                                                                                                     // ETAT DES AIN                                                                                       // ETAT DES DIN
                                                                            if(i>=1+NBDIN+NBBTN+NBMOTOR+NBSONAR && i<1+NBDIN+NBBTN+NBMOTOR+NBSONAR+NBRGBC){
                                                                                jwObj_array( "rgb" );
                                                                                    for(j=0;j<NBRGBC;j++){
                                                                                        jwArr_object();
                                                                                            jwObj_string("event", messageResponse[i].RGBresponse.event_state);                                                                                        
                                                                                            jwObj_int("red",messageResponse[i].RGBresponse.red.value);
                                                                                            jwObj_int("green",messageResponse[i].RGBresponse.green.value);
                                                                                            jwObj_int("blue",messageResponse[i].RGBresponse.blue.value);
                                                                                            jwObj_int("clear",messageResponse[i].RGBresponse.clear.value);
                                                                                        jwEnd();           
                                                                                        i++;
                                                                                    }
                                                                                jwEnd();                                                                                             
                                                                            }                                                                            
                                                                            
                                                                            // ETAT DES LED                                                                                   // ETAT DES PWM                                                                                        // ETAT DES AIN                                                                                       // ETAT DES DIN
                                                                            if(i>=1+NBDIN+NBBTN+NBMOTOR+NBSONAR+NBRGBC && i<1+NBDIN+NBBTN+NBMOTOR+NBSONAR+NBRGBC+NBLED){
                                                                                jwObj_array( "led" );
                                                                                    for(j=0;j<NBLED;j++){
                                                                                        jwArr_object();
                                                                                            jwObj_int("state",messageResponse[i].value);
                                                                                            jwObj_int("power",messageResponse[i].LEDresponse.powerPercent);
                                                                                        jwEnd();           
                                                                                        i++;
                                                                                    }
                                                                                jwEnd();                                                                                             
                                                                            }                                                                            


                                                                            // ETAT DES PWM                                                                                   // ETAT DES PWM                                                                                        // ETAT DES AIN                                                                                       // ETAT DES DIN
                                                                            if(i>=1+NBDIN+NBBTN+NBMOTOR+NBSONAR+NBRGBC+NBLED && i<1+NBDIN+NBBTN+NBMOTOR+NBSONAR+NBRGBC+NBLED+NBPWM){
                                                                                jwObj_array( "pwm" );
                                                                                    for(j=0;j<NBPWM;j++){
                                                                                        jwArr_object();
                                                                                            jwObj_int("state",messageResponse[i].value);
                                                                                            jwObj_int("power",messageResponse[i].PWMresponse.powerPercent);
                                                                                        jwEnd();           
                                                                                        i++;
                                                                                    }
                                                                                jwEnd();                                                                                             
                                                                            }

                                                                            break;
                                                                                    
                                                        case pPWM :             
                                                                            switch(messageResponse[i].responseType){
                                                                                case EVENT_ACTION_ERROR :   jwObj_string("action", "error");break;
                                                                                case EVENT_ACTION_END  :   jwObj_string("action", "end"); break;
                                                                                case EVENT_ACTION_BEGIN  :   jwObj_string("action", "begin"); break;
                                                                                case EVENT_ACTION_RUN  :   jwObj_string("action", "run"); break;
                                                                                case EVENT_ACTION_ABORT  :   jwObj_string("action", "abort"); break;
                                                                                case RESP_STD_MESSAGE  :   if(messageResponse[i].PWMresponse.id>=0)
                                                                                                jwObj_int( "pwm", messageResponse[i].PWMresponse.id);
                                                                                            else
                                                                                                jwObj_string("pwm", "unknown");
                                                                                            jwObj_string( "state", messageResponse[i].PWMresponse.state);				
                                                                                            jwObj_int( "power", messageResponse[i].PWMresponse.powerPercent);				
                                                                                            jwObj_int("time", messageResponse[i].PWMresponse.time);
                                                                                            break;
                                                                                default :   jwObj_string("error", "unknown");break;
                                                                            }
                                                                            break;

                                                        case pSERVO :             
                                                                            switch(messageResponse[i].responseType){
                                                                                case EVENT_ACTION_ERROR :   jwObj_string("action", "error");break;
                                                                                case EVENT_ACTION_END  :    jwObj_string("action", "end"); break;
                                                                                case EVENT_ACTION_BEGIN  :  jwObj_string("action", "begin"); break;
                                                                                case EVENT_ACTION_ABORT  :  jwObj_string("action", "abort"); break;
                                                                                case RESP_STD_MESSAGE  :    if(messageResponse[i].PWMresponse.id>=0)
                                                                                                                jwObj_int( "pwm", messageResponse[i].PWMresponse.id);
                                                                                                            else
                                                                                                                jwObj_string("pwm", "unknown");
                                                                                                            jwObj_string( "state", messageResponse[i].PWMresponse.state);				
                                                                                                            jwObj_int( "position", messageResponse[i].PWMresponse.powerPercent);				
                                                                                                            break;
                                                                                default :                   jwObj_string("error", "unknown");break;
                                                                            }
                                                                            break;                                                                         
                                                                                   
                                                        case pLED :             
                                                                            switch(messageResponse[i].responseType){
                                                                                case EVENT_ACTION_ERROR :    jwObj_string("action", "error");break;
                                                                                case EVENT_ACTION_END  :     jwObj_string("action", "end"); break;
                                                                                case EVENT_ACTION_BEGIN  :   jwObj_string("action", "begin"); break;
                                                                                case EVENT_ACTION_RUN  :   jwObj_string("action", "run"); break;
                                                                                case EVENT_ACTION_ABORT  :   jwObj_string("action", "abort"); break;
                                                                                case RESP_STD_MESSAGE  :    if(messageResponse[i].LEDresponse.id>=0)
                                                                                                                jwObj_int( "led", messageResponse[i].LEDresponse.id);
                                                                                                            else
                                                                                                                jwObj_string("led", "unknown");
                                                                                                            jwObj_string( "state", messageResponse[i].LEDresponse.state);				// add object key:value pairs
                                                                                                            jwObj_int( "power", messageResponse[i].LEDresponse.powerPercent);				// add object key:value pairs
                                                                                                            jwObj_int("time", messageResponse[i].LEDresponse.time);
                                                                                                            jwObj_int("count", messageResponse[i].LEDresponse.blinkCount);
                                                                                                            break;
                                                                                default :   jwObj_string("error", "unknown");break;
                                                                            }
                                                                            break;
                                                                                
							case CONFIG :         
                                                                            switch(messageResponse[i].responseType){
                                                                                case EVENT_ACTION_ERROR : jwObj_string("action", "error"); break;
                                                                                case EVENT_ACTION_END :   jwObj_string("action", "end"); break;
                                                                                case EVENT_ACTION_BEGIN : jwObj_string("action", "begin"); break;
                                                                                case EVENT_ACTION_ABORT : jwObj_string("action", "abort"); break;
                                                                                case RESP_STD_MESSAGE   :   
                                                                                                            jwObj_object( "config" );                                                                                 
                                                                                                                jwObj_string("reset", messageResponse[i].CONFIGresponse.config.reset);       
                                                                                                                jwObj_string("save", messageResponse[i].CONFIGresponse.config.save);                                                                                                                       
                                                                                                            jwEnd();  
                                                                                                            
                                                                                                            jwObj_object( "stream" );                                                                                 
                                                                                                                    jwObj_string("state", messageResponse[i].CONFIGresponse.stream.state);
                                                                                                                    jwObj_int("time", messageResponse[i].CONFIGresponse.stream.time);
                                                                                                                    jwObj_string("onEvent", messageResponse[i].CONFIGresponse.stream.onEvent);         
                                                                                                            jwEnd();
                                                                                                            
                                                                                                        // CREATE JSON CONFIG FOR MOTOR  
                                                                                                            if(messageResponse[i].CONFIGresponse.motValueCnt > 0){
                                                                                                                jwObj_array("motor");
                                                                                                                    for(j=0;j<messageResponse[i].CONFIGresponse.motValueCnt;j++){
                                                                                                                        jwArr_object();
                                                                                                                            jwObj_int( "motor", messageResponse[i].CONFIGresponse.motor[j].id);
                                                                                                                            jwObj_string("inverted", messageResponse[i].CONFIGresponse.motor[j].inverted);
                                                                                                                            jwObj_int("rpmMin", messageResponse[i].CONFIGresponse.motor[j].minRPM);
                                                                                                                            jwObj_int("rpmMax", messageResponse[i].CONFIGresponse.motor[j].maxRPM);
                                                                                                                        jwEnd();
                                                                                                                    } 
                                                                                                                jwEnd();
                                                                                                            }
                                                                                                            
                                                                                                        // CREATE JSON CONFIG FOR WHEEL  
                                                                                                            if(messageResponse[i].CONFIGresponse.wheelValueCnt > 0){
                                                                                                                jwObj_array("wheel");
                                                                                                                    for(j=0;j<messageResponse[i].CONFIGresponse.wheelValueCnt;j++){
                                                                                                                        jwArr_object();
                                                                                                                            jwObj_int( "wheel", messageResponse[i].CONFIGresponse.wheel[j].id);
                                                                                                                            jwObj_int("diameter", messageResponse[i].CONFIGresponse.wheel[j].diameter);
                                                                                                                            jwObj_int("pulses", messageResponse[i].CONFIGresponse.wheel[j].pulsesPerRot);
                                                                                                                        jwEnd();
                                                                                                                    } 
                                                                                                                jwEnd();
                                                                                                            }         

                                                                                                        // CREATE JSON CONFIG FOR STEPPER  
                                                                                                            if(messageResponse[i].CONFIGresponse.stepperValueCnt > 0){
                                                                                                                jwObj_array("stepper");
                                                                                                                    for(j=0;j<messageResponse[i].CONFIGresponse.wheelValueCnt;j++){
                                                                                                                        jwArr_object();
                                                                                                                            jwObj_int( "motor", messageResponse[i].CONFIGresponse.stepper[j].id);
                                                                                                                            jwObj_string("inverted", messageResponse[i].CONFIGresponse.stepper[j].inverted);
                                                                                                                            jwObj_int("ratio", messageResponse[i].CONFIGresponse.stepper[j].ratio);
                                                                                                                            jwObj_int("steps", messageResponse[i].CONFIGresponse.stepper[j].stepsPerRot);
                                                                                                                        jwEnd();
                                                                                                                    } 
                                                                                                                jwEnd();
                                                                                                            }                                                                                                              
                  
                                                                                                            
                                                                                                        // CREATE JSON CONFIG FOR LED
                                                                                                            if(messageResponse[i].CONFIGresponse.ledValueCnt > 0){
                                                                                                                jwObj_array("led");
                                                                                                                    for(j=0;j<messageResponse[i].CONFIGresponse.ledValueCnt;j++){
                                                                                                                        jwArr_object();
                                                                                                                            jwObj_int( "led", messageResponse[i].CONFIGresponse.led[j].id);
                                                                                                                            jwObj_string("state", messageResponse[i].CONFIGresponse.led[j].state);
                                                                                                                            jwObj_int( "power", messageResponse[i].CONFIGresponse.led[j].power);
                                                                                                                        jwEnd();
                                                                                                                    } 
                                                                                                                jwEnd();                                             
                                                                                                            }
                                                                                                           
                                                                                                            break;
                                                                                default : jwObj_string("error", "unknown"); break;
                                                                            }
                                                                            break;
                                                                                
							case SYSTEM :           
                                                                            switch(messageResponse[i].responseType){
                                                                                case EVENT_ACTION_ERROR : jwObj_string("action", "error"); break;
                                                                                case EVENT_ACTION_END :   jwObj_string("action", "end"); break;
                                                                                case EVENT_ACTION_BEGIN : jwObj_string("action", "begin"); break;
                                                                                case EVENT_ACTION_ABORT : jwObj_string("action", "abort"); break;
                                                                                case RESP_STD_MESSAGE   :                                                                                    
                                                                                                            jwObj_string("application", messageResponse[i].SYSCMDresponse.application);
                                                                                                          ; break;
                                                                                default : jwObj_string("error", "unknown"); break;
                                                                            }		// add object key:value pairs

                                                                            break;                                                                                
                                                                                   
							default:                break;

						}
                                    if(orgType!=STATUS)
                                        jwEnd();
				}
				jwEnd();
			}
		jwEnd();
		jwClose();
}
