/*
 * hwMagager.c
 *
 *  Created on: 26 nov. 2016
 *      Author: raph
 */

#define  CALLBACK 0
#define  ADR	  1
#define	 CMD      2
#define	 PRM      3

#include "pthread.h"
#include <unistd.h>
#include "string.h"
#include <stdio.h>
#include "hwManager.h"
#include "../kehops_main.h"
#include "../config/kehopsConfig.h"

#include "hardwareDrivers.h"

#define POOLTIME 1000

#include "../buggy_descriptor.h"
#include "../config/deviceMapping.h"
#include "../type.h"


// Device drivers declaration
#include "pca9685.h"
#include "pca9629.h"
#include "efm8_mcu_kehops.h"
#include "mcp23008.h"
#include "bh1745.h"




// Thread Messager
pthread_t th_hwManager;

// -------------------------------------
// DEFINITION DES TYPE DE CAPTEURS
// -------------------------------------
struct s_i2c_colorReg{
    int red;
    int green;
    int blue;
    int clear;
};

struct s_analog{
	int value;
};
/*
struct s_rgbConfig{
	int I2CdeviceAddress;
        struct s_i2c_colorReg I2CcolorAddress;
};
*/

struct s_din{
	int value;
};

struct s_counter{
	int frequency;
        int counter;
};


// -------------------------------------
// DEFINITION DES TYPE DE SORTIE
// -------------------------------------

// --------------------------------------
// MOTEURS
// --------------------------------------
struct s_motor_sp{
    int speed;
    int direction;    
};


struct actuator_motor{
    struct s_motor_sp setpoint;
};

// --------------------------------------
// STEP MOTOR
// --------------------------------------

struct s_stepper_sp{
    int speed;
    int direction;    
    int steps;  
};


struct actuator_stepper{
    int isRunning;
    struct s_stepper_sp setpoint;
};

// --------------------------------------
// DOUT
// --------------------------------------

struct s_dout_sp{
    int  power;  
};

struct s_dout_config{   
    char isServo;   
};

struct actuator_dout{
    struct s_dout_sp setpoint;
    struct s_dout_config config;
};

struct actuator_aout{
    struct s_dout_sp setpoint;
    struct s_aout_config config;
};

typedef struct t_actuator{
    struct actuator_motor motor[MAXMOTOR];
    struct actuator_stepper stepperMotor[MAXSTEPPER];
    struct actuator_dout digitalOutput[MAXPWM+MAXLED];
    struct actuator_aout analogOutput[MAXAOUT];
}ACTUATORS;

typedef struct t_sensor{
	struct s_din din[MAXDIN];
        struct s_analog ain[MAXAIN];
        struct s_din button[MAXBTN];
        struct s_analog distance[MAXSONAR];
	struct s_counter counter[MAXCOUNTER];
	RGB_COLOR rgbc[MAXRGBC];

}SENSORS;

// --------------------------------------
// HIGH LEVEL
// --------------------------------------

ACTUATORS actuator;

SENSORS sensor;            // Device structure with actuator & sensor

typedef struct tHWversion{
        int mcuVersion;
        int HWrevision;
}t_HWversion;

t_HWversion BoardInfo;

int i2c_command_queuing[50][4];
int timeCount_ms=0;

int getMotorFrequency(unsigned char motorNb);                   // Retourne la fr�quence actuelle mesuree sur l'encodeur
int getMotorPulses(unsigned char motorName);                    // Retourne le nombre d'impulsion d'encodeur moteur depuis le d�marrage
char getDigitalInput(unsigned char inputNumber);                // Retourne l'�tat de l'entr�e num�rique sp�cifi�e
char getButtonInput(unsigned char buttonNumber);                // Retourne l'�tat du bouton
int getSonarDistance(unsigned char distanceSensorID);					// Retourne la distance en cm
int getBatteryVoltage(unsigned char ainID);					// Retourne la tension battery en mV

int getColorValue(unsigned char sensorID, unsigned char color);      // Retourne la valeur de la couleur d�finie sur le capteur d�fini

int setMotorSpeed(int motorName, int ratio);
int setMotorDirection(char motorName, int direction);

int setStepperStepAction(int motorNumber, int direction, int stepCount);      // Effectue une action sur le moteur pas à pas (direction, nombre de pas)
int setStepperSpeed(int motorNumber, int speed);                              // Configuration de la vitesse du moteur pas à pas

int getStepperState(int motorNumber);                                         // Récupère l'état actuel du moteur pas à pas (run/off)

void setServoPosition(unsigned char smName, char position);
void setLedPower(unsigned char ledID, unsigned char power);
void setPwmPower(unsigned char pwmID, unsigned char power);

void setAnalogValue(unsigned char analogID, int value);

void processCommandQueue(void);
void execCommand(void (*ptrFunc)(char, int, int), char adr, int cmd, int param);
int set_i2c_command_queue(int (*callback)(char, int, int),char adr, int cmd, int param);

int getHWversion(void);                                                 // Get the hardware board version
int getMcuFirmware(void);                                              // Get the hardware microcontroller version

int resetHardware(t_sysConf * Config);



// ------------------------------------------
// Programme principale TIMER
// ------------------------------------------
void *hwTask (void * arg){
        int i;
        int initResult;

	//if(buggyBoardInit() && boardHWinit() == 0){   
        initResult = boardHWinit();
        if(initResult == 0){
		printf("\n#[HW MANAGER] Initialisation carte HW: OK\n");
		sendMqttReport(0,"#[HW MANAGER] Initialisation carte HW: OK\n");
	}
	else{
            if(initResult > 0){
		printf("#[HW MANAGER] Initialisation carte HW: ERREUR \n");
		sendMqttReport(0,"#[HW MANAGER] Initialisation carte HW: ERREUR\n");
            }
            else{
                    printf("#[HW MANAGER] Initialisation carte HW: AVERTISSEMENT \n");
                    sendMqttReport(0,"#[HW MANAGER] Initialisation carte HW: AVERTISSEMENT\n");
                }
	}
        
        
/**************        
        
        BoardInfo.mcuVersion=actuator_getFirmwareVersion();
        BoardInfo.HWrevision=actuator_getBoardId();

 ****************/        
	while(1){
            
		// Sequencage des messages sur bus I2C à interval régulier
                // de 250mS
		switch(timeCount_ms){
                        //case 0	: printf("Start --------------------------\n");
                    
                                  printf("\n**************\n");
                        case 5	: //sensor.counter[MOTOR_ENCODER_LEFT].counter = actuator_getCounterPulses(MOTOR_ENCODER_LEFT);
                                  //sensor.counter[MOTOR_ENCODER_RIGHT].counter = actuator_getCounterPulses(MOTOR_ENCODER_RIGHT);
                                  for(i=0;i<NBWHEEL;i++){
                                      sensor.counter[i].counter = actuator_getCounterPulses(kehops.dcWheel[i].config.encoder.pulseCounter_id);
                                      sensor.counter[i].frequency = actuator_getCounterFrequency(kehops.dcWheel[i].config.encoder.freqCounter_id);
                                  }

                                //printf("Pulses left: %d - ",sensor.counter[MOTOR_ENCODER_LEFT].pulseFromStartup);
                                //printf("Pulses right: %d\n\n",sensor.counter[MOTOR_ENCODER_RIGHT].pulseFromStartup);
                                break;
			case 10	: 
                                //sensor.counter[MOTOR_ENCODER_LEFT].frequency = EFM8BB_readFrequency(MOTOR_ENCODER_LEFT); 
                               // sensor.counter[MOTOR_ENCODER_LEFT].frequency = actuator_getCounterFrequency(MOTOR_ENCODER_LEFT); 
                                //sensor.counter[MOTOR_ENCODER_RIGHT].frequency = actuator_getCounterFrequency(MOTOR_ENCODER_RIGHT); 
                                //printf("Speed left [cm/s]: %d - ",sensor.counter[MOTOR_ENCODER_LEFT].frequency) ;
                                //printf("Speed right [cm/s]: %d\n\n",sensor.counter[MOTOR_ENCODER_RIGHT].frequency);
                                break;
                                          
			case 15	:   //dinState = actuator_getDigitalInput(0);              // Param�tre transmis non utilis� par la fonction...
                                    for(i = 0;i<NBDIN;i++){
                                        if(actuator_getDigitalInput(kehops.proximity[i].config.din_id) > 0) sensor.din[i].value = 1;
                                        else sensor.din[i].value = 0;
                                    }
                                    break;

                        case 20	:   
                                    for(i = 0;i<NBAIN;i++){
                                        sensor.ain[i].value = actuator_getVoltage(kehops.battery[i].config.ain_id);        // Conversion de distance mm en cm
                                        //printf("    sensor.ain[%d].value: %d\n",i, sensor.ain[i].value);
                                    }
                                    
                                    break;
                                    
			case 25	:   for(i = 0;i<NBSONAR;i++){
                                        sensor.distance[i].value = actuator_getDistance(kehops.sonar[i].config.distanceSensor_id);        // Conversion de distance mm en cm
                                        //printf("    sensor.ain[%d].value: %d\n",i, sensor.ain[i].value);
                                    }
                                    break;
                        
                        case 30	:   //sensor.din[DIN_4].value = MCP2308_ReadGPIO(BTN_0);
                                    //sensor.din[DIN_5].value = MCP2308_ReadGPIO(BTN_1);
                                    for(i = 0;i<NBBTN;i++){
                                        if(actuator_getDigitalInput(kehops.button[i].config.din_id) > 0) sensor.button[i].value = 1;
                                        else sensor.button[i].value = 0;
                                    }
                                    break;                         

                        case 35 :   for(i = 0;i<NBRGBC;i++){
                                        actuator_getRGBColor(i, &sensor.rgbc[kehops.rgb[i].config.rgbID]);        // Get RGB Sensor value
                                    }
                                    break; 

                        case 40 :   for(i=0;i<NBSTEPPER;i++){
                                        actuator.stepperMotor[i].isRunning = actuator_getStepperState(kehops.stepperWheel[i].config.motor.stepper_motor_id);
                                    }
                                    break;
                                
			default:
                                  if(i2c_command_queuing[0][CALLBACK]!=0)
                                      processCommandQueue(); break;
		}

		// Reset le compteur au bout de 50mS
		if(timeCount_ms<100)
			timeCount_ms++;
		else 
                    timeCount_ms=0;
                
		usleep(POOLTIME);
	}
	pthread_exit (0);
}

// ------------------------------------------------------------------------------------
// TIMERMANAGER: Initialisation du gestionnaire de timer
// - D�marre le thread
// ------------------------------------------------------------------------------------
int InitHwManager(void){
    // CREATION DU THREAD DE TIMER
      if (pthread_create (&th_hwManager, NULL, hwTask, NULL)!= 0) {
            return (1);
      }else
          return (0);
}

// ------------------------------------------------------------------------------------
// CLOSEHWMANAGER: Fermeture du gestionnaire hardware
// - Stop le thread hardware
// ------------------------------------------------------------------------------------

int CloseHwManager(void){
    int result;
    // TERMINE LE THREAD DE MESSAGERIE
    pthread_cancel(th_hwManager);
    // Attends la terminaison du thread de messagerie
    result=pthread_join(th_hwManager, NULL);
    return (result);
}

// ------------------------------------------------------------------------------------
// GETPULSEMOTOR: lecture de l'encodeur optique du moteur sp�cifi�
// Entr�e: Num�ro de l'encodeur
// Sortie:
// ------------------------------------------------------------------------------------
int getMotorPulses(unsigned char motorName){
    return sensor.counter[motorName].counter;
}

char getDigitalInput(unsigned char inputNumber){
    return sensor.din[inputNumber].value;
}

char getButtonInput(unsigned char buttonNumber){
    return sensor.button[buttonNumber].value;
}

int getMotorFrequency(unsigned char motorNb){
    //printf("\n----- FREQ #%d: %d -----\n",motorNb, sensor.counter[motorNb].frequency);
    return sensor.counter[motorNb].frequency;
}


int getSonarDistance(unsigned char distanceSensorID){
    return sensor.distance[distanceSensorID].value;
}

int getBatteryVoltage(unsigned char ainID){
    return sensor.ain[ainID].value;
}

int getColorValue(unsigned char sensorID, unsigned char color){
    int colorValue;
    
    switch(color){
        case RED : colorValue= sensor.rgbc[sensorID].red; break;
        case GREEN : colorValue=sensor.rgbc[sensorID].green; break;
        case BLUE : sensor.rgbc[sensorID].blue; break;
        case CLEAR : sensor.rgbc[sensorID].clear; break;
        default : colorValue = -1; break;
    }
  
	return colorValue;
}

// ---------------------------------------------------------------------------
// SETMOTORSPEED
// Applique la consigne de v�locit� pour un moteur donn�
// Cette consigne n'est pas appliqu�e directement sur les moteur mais sera progressivement
// approch�e par le gestionnaire d'acceleration.
// ---------------------------------------------------------------------------
int setMotorSpeed(int motorName, int ratio){

    	// V�rification ratio max et min comprise entre 0..100%
	if(ratio > 100)
		ratio = 100;
	if (ratio<0)
		ratio = 0;
 
        int motorId = kehops.dcWheel[motorName].config.motor.dc_motor_id; 

    if(!strcmp(kehopsActuators.dc_motor[motorId].interface, ""))
        printf("[hwManager] Error! no interface found for MOTOR [ID#%d], please check the config file <deviceMap.cfg>\n", motorId);
    else{
            if(!strcmp(kehopsActuators.dc_motor[motorId].interface, IFACE_DEVICE_I2C)) 
                printf("[hwManager] Error! no interface driver I2C for motor [ID#%d]\n", motorId);

            if(!strcmp(kehopsActuators.dc_motor[motorId].interface, IFACE_GEN_HBRIDGE_MOTOR)){
                set_i2c_command_queue(&actuator_genericHBridge_motorSpeed, motorId, ratio, NULL);
            }
    }
	return(1);
}


// ---------------------------------------------------------------------------
// SETMOTORDIRECTION
// ---------------------------------------------------------------------------
int setMotorDirection(char motorName, int direction){

    // Check if motor inversion requiered and modify if necessary
    if(kehops.dcWheel[motorName].config.motor.inverted)
        direction *= -1;

    int motorId = kehops.dcWheel[motorName].config.motor.dc_motor_id; 

    if(!strcmp(kehopsActuators.dc_motor[motorId].interface, ""))
        printf("[hwManager] Error! no interface found for MOTOR [ID#%d], please check the config file <deviceMap.cfg>\n", motorId);
    else{
        if(!strcmp(kehopsActuators.dc_motor[motorId].interface, IFACE_DEVICE_I2C)) 
            printf("[hwManager] Error! no interface driver I2C for motor [ID#%d]\n", motorId);
        if(!strcmp(kehopsActuators.dc_motor[motorId].interface, IFACE_GEN_HBRIDGE_MOTOR)){
            set_i2c_command_queue(&actuator_genericHBridge_motorDirection, motorId, direction, NULL);
        }
    }

    return(1);
}

// ---------------------------------------------------------------------------
// SETMOTORSTATE
// !!!!!!!!!!!!! FONCTION A RETRAVAILLER !!!!!!!!!!!!!!!!!!!
// ---------------------------------------------------------------------------

int setMotorState(char motorName, int state){
    int motorId = kehops.dcWheel[motorName].config.motor.dc_motor_id; 

    if(!strcmp(kehopsActuators.dc_motor[motorId].interface, ""))
        printf("[hwManager] Error! no interface found for MOTOR [ID#%d], please check the config file <deviceMap.cfg>\n", motorId);
    else{
        if(!strcmp(kehopsActuators.dc_motor[motorId].interface, IFACE_DEVICE_I2C)){
            printf("[hwManager] Error! no interface driver I2C for motor [ID#%d] \n", motorId);
        }  

        if(!strcmp(kehopsActuators.dc_motor[motorId].interface, IFACE_GEN_HBRIDGE_MOTOR)){
            set_i2c_command_queue(&actuator_genericHBridge_motorState, motorId, state, NULL);
        }
    }
    return (1);
}

// ---------------------------------------------------------------------------
// GETMCUHWVERSION
// Get the hardware/software version
// ---------------------------------------------------------------------------
int getMcuHWversion(void){
	return(BoardInfo.HWrevision);
}

// ---------------------------------------------------------------------------
// GETMCUFIRMWARE
// Get the hardware/software version
// ---------------------------------------------------------------------------
int getMcuFirmware(void){
	return(BoardInfo.mcuVersion);
}

// -------------------------------------------------------------------
// Effectue une action sur le moteur pas à pas (direction, nombre de pas)
// - Numéro de moteur
// - Sens de ratation
// - nombre de pas
// -------------------------------------------------------------------

int setStepperStepAction(int motorNumber, int direction, int stepCount){      
    
    // Check if motor inversion requiered and modify if necessary
    if(kehops.stepperWheel[motorNumber].config.motor.inverted)
        direction *= -1;

    int stepper_id = kehops.stepperWheel[motorNumber].config.motor.stepper_motor_id;
    
    if(!strcmp(kehopsActuators.stepper_motors[stepper_id].interface, ""))
        printf("[hwManager] Error! no interface found for STEPPER [ID#%d], please check the config file <deviceMap.cfg>\n", stepper_id);
    else
        if(!strcmp(kehopsActuators.stepper_motors[stepper_id].interface, IFACE_DEVICE_I2C))       
            set_i2c_command_queue(&actuator_setStepperStepAction, stepper_id, direction, stepCount);
    return (0);
} 

// -------------------------------------------------------------------
// SETSTEPPERSPEED
// Configuration de la vitesse du moteur pas à pas
// - Numéro de moteur
// - vitesse 0..100%
// -------------------------------------------------------------------
int setStepperSpeed(int motorNumber, int speed){
    int stepper_id = kehops.stepperWheel[motorNumber].config.motor.stepper_motor_id;
    
    if(!strcmp(kehopsActuators.stepper_motors[stepper_id].interface, ""))
        printf("[hwManager] Error! no interface found for STEPPER [ID#%d], please check the config file <deviceMap.cfg>\n", stepper_id);
    else
        if(!strcmp(kehopsActuators.stepper_motors[stepper_id].interface, IFACE_DEVICE_I2C))    
            set_i2c_command_queue(&actuator_setStepperSpeed, stepper_id, speed, NULL);
    
    return (1);
}                           

// -------------------------------------------------------------------
// GETSTEPPERSTATE
// Récupère l'état actuel du moteur pas à pas (run/off)
// - Numéro de moteur
// -------------------------------------------------------------------
int getStepperState(int motorNumber){
    return actuator.stepperMotor[motorNumber].isRunning;
}                              

// ------------------------------------------------------------------------------------
// SET_I2C_COMMAND_QUEUE: Mise en file d'attente de l'appelle d'une fonction I2C
// ------------------------------------------------------------------------------------
int set_i2c_command_queue(int (*callback)(char, int, int),char adr, int cmd, int param){
	unsigned char freeIndex;

	// Recherche d'un emplacement libre dans la file d'attente
	for(freeIndex=0;(freeIndex<50) && (i2c_command_queuing[freeIndex][CALLBACK]>0);freeIndex++);

	if(freeIndex>=49) printf("\n[hwManager]->File de commande pleine !\n");
	else
	{
		i2c_command_queuing[freeIndex][CALLBACK] =  callback;
		i2c_command_queuing[freeIndex][ADR] =  adr;
		i2c_command_queuing[freeIndex][CMD] =  cmd;
                i2c_command_queuing[freeIndex][PRM] =  param;
	}

	return freeIndex;
}

void setLedPower(unsigned char ledID, unsigned char power){
        int doutID = kehops.led[ledID].config.dout_id;

        if(!strcmp(kehopsActuators.dout[doutID].interface, ""))
            printf("[hwManager] Error! no interface found for DOUT [ID#%d], please check the config file <deviceMap.cfg>\n", doutID);
        else
            if(!strcmp(kehopsActuators.dout[doutID].interface, IFACE_DEVICE_I2C))        
                set_i2c_command_queue(&actuator_setDoutValue, doutID, power, NULL);        
}

void setPwmPower(unsigned char pwmID, unsigned char power){
        int doutID = kehops.pwm[pwmID].config.dout_id;

        if(!strcmp(kehopsActuators.dout[doutID].interface, ""))
            printf("[hwManager] Error! no interface found for DOUT [ID#%d], please check the config file <deviceMap.cfg>\n", doutID);
        else
            if(!strcmp(kehopsActuators.dout[doutID].interface, IFACE_DEVICE_I2C))
                set_i2c_command_queue(&actuator_setDoutValue, doutID, power, NULL);        
}

void setAnalogValue(unsigned char analogID, int value){
        int aoutID = kehops.aout[analogID].config.aout_id;
        
        if(!strcmp(kehopsActuators.aout[aoutID].interface, ""))
            printf("[hwManager] Error! no interface found for AOUT [ID#%d], please check the config file <deviceMap.cfg>\n", aoutID);
        else
            if(!strcmp(kehopsActuators.aout[aoutID].interface, IFACE_DEVICE_I2C)){
                set_i2c_command_queue(&actuator_setAnalogValue, aoutID, value, NULL);
            }
            
}

void setServoPosition(unsigned char ID, char position){
        int doutID = kehops.pwm[ID].config.dout_id;
        
        if(!strcmp(kehopsActuators.dout[doutID].interface, ""))
            printf("[hwManager] Error! no interface found for DOUT [ID#%d], please check the config file <deviceMap.cfg>\n", doutID);
        else
            if(!strcmp(kehopsActuators.dout[doutID].interface, IFACE_DEVICE_I2C))        
                set_i2c_command_queue(&actuator_setServoPosition, doutID, position, NULL);
}

// ------------------------------------------------------------------------------------
// ONTIMEOUT: Fcontion appelee en fin de timer
// appelle une fonction callback pr�d�finie par *ptrFunc
// ------------------------------------------------------------------------------------
void execCommand(void (*ptrFunc)(char, int, int), char adr, int cmd, int param){
	(*ptrFunc)(adr, cmd, param);		// Appelle de la fonction call back pr�d�finie par *ptrFonc avec les param�tre recus
}


void processCommandQueue(void){
	int i;
	// ENVOIE DE LA COMMANDE I2C

	//printf("#%d  callback: %d, adr: %d cmd: %d\n",0 ,i2c_command_queuing[0][CALLBACK],i2c_command_queuing[0][ADR],i2c_command_queuing[0][CMD]);
	execCommand(i2c_command_queuing[0][CALLBACK], i2c_command_queuing[0][ADR], i2c_command_queuing[0][CMD], i2c_command_queuing[0][PRM]);
	// DECALAGE DE LA PILE

	for(i=0;i<50;i++){
		i2c_command_queuing[i][CALLBACK] = i2c_command_queuing[i+1][CALLBACK];
		i2c_command_queuing[i][ADR] = i2c_command_queuing[i+1][ADR];
		i2c_command_queuing[i][CMD] = i2c_command_queuing[i+1][CMD];
                i2c_command_queuing[i][PRM] = i2c_command_queuing[i+1][PRM];
	}
	i2c_command_queuing[49][CALLBACK]=i2c_command_queuing[49][ADR]=i2c_command_queuing[49][CMD]=i2c_command_queuing[49][PRM]=0;
}




// -------------------------------------------------------------------
// RESET HARDFWARE
// Applique un etat initial aux moteurs, LEDS, PWM, etc...
// -------------------------------------------------------------------

int resetHardware(t_sysConf * Config){
    int i;
    
    // Etat initial des moteur
    for(i=0;i<NBMOTOR;i++){
        //actuator_genericHBridge_motorState(i, 1);
        /*
        setMotorSpeed(i, 0);
        setMotorDirection(i, BUGGY_FORWARD);
        actuator_clearWheel(i);
         */ 
    }

    // Etat initial des LED       
    for(i=0;i<NBLED;i++){
//        if(Config->led[i].state)
//            setLedPower(i, Config->led[i].power);
//        else
//            setLedPower(i, 0);
    }
    // Etat initial des sorties PWM LED
//    for(i=0;i<NBPWM;i++){
  //      setPwmPower(i,0);
//    }
    return 0;
}