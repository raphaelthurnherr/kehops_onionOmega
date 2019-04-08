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
#include <stdio.h>
#include "hwManager.h"
#include "../kehops_main.h"
#include "../config/kehopsConfig.h"


#ifdef I2CSIMU
#include "boardHWsimu.h"
#define POOLTIME 20000
#else
#include "boardHWctrl.h"
#include "actuatorsDrivers.h"
#define POOLTIME 1000
#endif

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

typedef struct t_actuator{
    struct actuator_motor motor[MAXMOTOR];
    struct actuator_stepper stepperMotor[MAXSTEPPER];
    struct actuator_dout digitalOutput[MAXPWM+MAXLED];
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

//char getOrganNumber(int organName);		// Retourne le num�ro du moteur 0..xx selon le nom d'organe sp�cifi�

unsigned char getOrganI2Cregister(char organType, unsigned char organName); // Retourne l'adresse du registre correspondant au nom de l'organe

int setMotorSpeed(int motorName, int ratio);
int setMotorDirection(char motorName, int direction);

int setStepperStepAction(int motorNumber, int direction, int stepCount);      // Effectue une action sur le moteur pas à pas (direction, nombre de pas)
int setStepperSpeed(int motorNumber, int speed);                              // Configuration de la vitesse du moteur pas à pas

int getStepperState(int motorNumber);                                         // Récupère l'état actuel du moteur pas à pas (run/off)

void setServoPosition(unsigned char smName, char position);
void setLedPower(unsigned char ledID, unsigned char power);
void setPwmPower(unsigned char ID, unsigned char power);

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
        char dinState=0;
        int i;
        
	if(buggyBoardInit() && boardHWinit() == 0){       
		printf("\n#[HW MANAGER] Initialisation carte HW: OK\n");
		sendMqttReport(0,"#[HW MANAGER] Initialisation carte HW: OK\n");
	}
	else{
		printf("#[HW MANAGER] Initialisation carte HW: ERREUR \n");
		sendMqttReport(0,"#[HW MANAGER] Initialisation carte HW: ERREUR\n");
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
                                      sensor.counter[i].counter = actuator_getCounterPulses(i);
                                      sensor.counter[i].frequency = actuator_getCounterFrequency(i);
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
                                        if(actuator_getDigitalInput(i) > 0) sensor.din[i].value = 1;
                                        else sensor.din[i].value = 0;
                                    }
                                    break;

                        case 20	:   
                                    for(i = 0;i<NBAIN;i++){
                                        sensor.ain[i].value = actuator_getVoltage(i);        // Conversion de distance mm en cm
                                        //printf("    sensor.ain[%d].value: %d\n",i, sensor.ain[i].value);
                                    }
                                    
                                    break;
                                    
			case 25	:   for(i = 0;i<NBSONAR;i++){
                                        sensor.distance[i].value = actuator_getDistance(i);        // Conversion de distance mm en cm
                                        //printf("    sensor.ain[%d].value: %d\n",i, sensor.ain[i].value);
                                    }
                                    break;
                        
                        case 30	:   //sensor.din[DIN_4].value = MCP2308_ReadGPIO(BTN_0);
                                    //sensor.din[DIN_5].value = MCP2308_ReadGPIO(BTN_1);
                                    for(i = 0;i<NBBTN;i++){
                                        if(actuator_getButtonInput(i) > 0) sensor.button[i].value = 1;
                                        else sensor.button[i].value = 0;
                                    }
                                    break;                         

                        case 35 :   for(i = 0;i<NBRGBC;i++){
                                        actuator_getRGBColor(i, &sensor.rgbc[i]);        // Get RGB Sensor value
                                    }
                                    break; 

                        case 40 :   for(i=0;i<NBSTEPPER;i++){
                                        actuator.stepperMotor[i].isRunning = actuator_getStepperState(i);
                                    }
                                    break;
                            //actuator.stepperMotor[STEPPER_0].isRunning = actuator_getStepperState(STEPPER_0); break;
                                
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
// SETMOTORDIRECTION
// !!!!!!!!!!!!! FONCTION A RETRAVAILLER !!!!!!!!!!!!!!!!!!!
// ---------------------------------------------------------------------------
int setMotorDirection(char motorName, int direction){
	unsigned char motorAdress;

        // Check if motor inversion requiered and modify if necessary
        if(kehops.dcWheel[motorName].config.motor.inverted)
            direction *= -1;


	// Conversion No de moteur en adresse du registre du PWM controleur
	motorAdress=getOrganI2Cregister(MOTOR, motorName);

        set_i2c_command_queue(&MCP2308_DCmotorSetRotation, motorAdress, direction, NULL);
        
	return(1);
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
    // USING THE NEW DRIVER
    //set_i2c_command_queue(&actuator_setStepperStepAction, motorNumber, direction);
    
    printf("\n-------- SET STEPPER STEP ACTION -------------   %d STEPS\n", stepCount);
    //actuator_setStepperStepAction(motorNumber, direction, stepCount);
    set_i2c_command_queue(&actuator_setStepperStepAction, motorNumber, direction, stepCount);
    return (0);
} 

// -------------------------------------------------------------------
// SETSTEPPERSPEED
// Configuration de la vitesse du moteur pas à pas
// - Numéro de moteur
// - vitesse 0..100%
// -------------------------------------------------------------------
int setStepperSpeed(int motorNumber, int speed){
    printf("\n-------- SET STEPPER SPEED -------------\n");
    // USING THE NEW DRIVER
    set_i2c_command_queue(&actuator_setStepperSpeed, motorNumber, speed, NULL);
    
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

// ---------------------------------------------------------------------------
// SETMOTORSPEED
// Applique la consigne de v�locit� pour un moteur donn�
// Cette consigne n'est pas appliqu�e directement sur les moteur mais sera progressivement
// approch�e par le gestionnaire d'acceleration.
// ---------------------------------------------------------------------------
int setMotorSpeed(int motorName, int ratio){
    	unsigned char motorAdress;
	motorAdress = getOrganI2Cregister(MOTOR, motorName);
        
    	// V�rification ratio max et min comprise entre 0..100%
	if(ratio > 100)
		ratio = 100;
	if (ratio<0)
		ratio = 0;
        
        //NEW
        set_i2c_command_queue(&PCA9685_DCmotorSetSpeed, motorAdress, ratio, NULL);
        
	return(1);
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
        // USING THE NEW DRIVER
        set_i2c_command_queue(&actuator_setLedPower, ledID, power, NULL);        
}

void setPwmPower(unsigned char ID, unsigned char power){
        // USING THE NEW DRIVER
        set_i2c_command_queue(&actuator_setPwmPower, ID, power, NULL);        
}

void setServoPosition(unsigned char ID, char position){
        set_i2c_command_queue(&actuator_setServoPosition, ID, position, NULL);
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


// ------------------------------------------------------------------------------------
// getOrganAdress: Conversion du non d'organe en adresse I2C
// Retourne l'adresse du registre correspondant au nom de l'organe
// ------------------------------------------------------------------------------------
unsigned char getOrganI2Cregister(char organType, unsigned char organName){
	unsigned char organAdr;

	if(organType == MOTOR){
		switch(organName){
			case MOTOR_0 : organAdr = PCA_DCM0; break;
			case MOTOR_1 : organAdr = PCA_DCM1; break;
			default :	organAdr = UNKNOWN; break;
		}
	}

	return organAdr;
}

// -------------------------------------------------------------------
// RESET HARDFWARE
// Applique un etat initial aux moteurs, LEDS, PWM, etc...
// -------------------------------------------------------------------

int resetHardware(t_sysConf * Config){
    int i;
    
    // Etat initial des moteur
    for(i=0;i<NBMOTOR;i++){
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