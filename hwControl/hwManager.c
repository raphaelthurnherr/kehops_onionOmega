/*
 * hwMagager.c
 *
 *  Created on: 26 nov. 2016
 *      Author: raph
 */

#define  CALLBACK 0
#define  ADR	  1
#define	 CMD      2

#include "pthread.h"
#include <unistd.h>
#include <stdio.h>
#include "hwManager.h"
#include "../kehops_main.h"

#ifdef I2CSIMU
#include "boardHWsimu.h"
#define POOLTIME 20000
#else
#include "boardHWctrl.h"
#define POOLTIME 1000
#endif

#include "../buggy_descriptor.h"
#include "../type.h"

// -------------------------------------
// DEFINITION DES TYPE DE CAPTEURS
// -------------------------------------
struct s_color{
	int value;
};

struct s_i2c_colorReg{
    int red;
    int green;
    int blue;
    int clear;
};
struct s_rgbConfig{
	int I2CdeviceAddress;
        struct s_i2c_colorReg I2CcolorAddress;
};

struct s_din{
	int value;
};

struct s_ain{
	int value;
};

struct s_rgbc{
        int red;
        int green;
        int blue;
        int clear;
        struct s_rgbConfig config;
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


struct t_actuator{
    struct actuator_motor motor[NBMOTOR];
    struct actuator_stepper stepperMotor[NBSTEPPER];
    struct actuator_dout digitalOutput[NBPWM+NBLED+NBSERVO];
};

struct t_sensor{
	struct s_din din[NBDIN];
        struct s_ain ain[NBAIN];
	struct s_counter counter[NBMOTOR];
	struct s_rgbc rgbc[NBRGBC];

};

// --------------------------------------
// HIGH LEVEL
// --------------------------------------

typedef struct t_device{
    struct t_sensor sensor;
    struct t_actuator actuator;
}t_device;


t_device device;            // Device structure with actuator & sensor


// Thread Messager
pthread_t th_hwManager;

typedef struct tHWversion{
        int mcuVersion;
        int HWrevision;
}t_HWversion;

t_HWversion BoardInfo;

int i2c_command_queuing[50][3];

int timeCount_ms=0;

int getMotorFrequency(unsigned char motorNb);	// Retourne la fr�quence actuelle mesuree sur l'encodeur
int getMotorPulses(unsigned char motorName);		// Retourne le nombre d'impulsion d'encodeur moteur depuis le d�marrage
char getDigitalInput(unsigned char inputNumber);	// Retourne l'�tat de l'entr�e num�rique sp�cifi�e
char getButtonInput(unsigned char buttonNumber);        // Retourne l'�tat du bouton
int getSonarDistance(void);						// Retourne la distance en cm
int getBatteryVoltage(void);					// Retourne la tension battery en mV
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
void execCommand(void (*ptrFunc)(char, int), char adr, int cmd);
int set_i2c_command_queue(int (*callback)(char, int),char adr, int cmd);

int getHWversion(void);                                                 // Get the hardware board version
int getMcuFirmware(void);                                              // Get the hardware microcontroller version

int resetHardware(t_sysConf * Config);
// ------------------------------------------
// Programme principale TIMER
// ------------------------------------------
void *hwTask (void * arg){
	int i;
        char dinState=0;

	if(buggyBoardInit()){
                
		printf("\n#[HW MANAGER] Initialisation carte HW: OK\n");
		sendMqttReport(0,"#[HW MANAGER] Initialisation carte HW: OK\n");
	}
	else{
		printf("#[HW MANAGER] Initialisation carte HW: ERREUR \n");
		sendMqttReport(0,"#[HW MANAGER] Initialisation carte HW: ERREUR\n");
	}
        
        BoardInfo.mcuVersion=EFM8BB_getFirmwareVersion();      
        BoardInfo.HWrevision=EFM8BB_getBoardType();

	while(1){
		// Sequencage des messages sur bus I2C à interval régulier
                // de 250mS
		switch(timeCount_ms){

                        case 5	: device.sensor.counter[MOTOR_ENCODER_LEFT].counter = EFM8BB_readPulseCounter(MOTOR_ENCODER_LEFT);
                                  device.sensor.counter[MOTOR_ENCODER_RIGHT].counter = EFM8BB_readPulseCounter(MOTOR_ENCODER_RIGHT);
                                //printf("Pulses left: %d - ",sensor.counter[MOTOR_ENCODER_LEFT].pulseFromStartup);
                                //printf("Pulses right: %d\n\n",sensor.counter[MOTOR_ENCODER_RIGHT].pulseFromStartup);
                                break;
			case 10	: 
                                //sensor.counter[MOTOR_ENCODER_LEFT].frequency = EFM8BB_readFrequency(MOTOR_ENCODER_LEFT); 
                                device.sensor.counter[MOTOR_ENCODER_LEFT].frequency = EFM8BB_readFrequency(MOTOR_ENCODER_LEFT); 
                                device.sensor.counter[MOTOR_ENCODER_RIGHT].frequency = EFM8BB_readFrequency(MOTOR_ENCODER_RIGHT); 
                                //printf("Speed left [cm/s]: %d - ",sensor.counter[MOTOR_ENCODER_LEFT].frequency) ;
                                //printf("Speed right [cm/s]: %d\n\n",sensor.counter[MOTOR_ENCODER_RIGHT].frequency);
                                break;
                                          
			case 15	:   dinState = EFM8BB_readDigitalInput(0);              // Param�tre transmis non utilis� par la fonction...
                                    if(dinState & 0x01) device.sensor.din[DIN_0].value = 1;
                                    else device.sensor.din[DIN_0].value=0;
                        
                                    if(dinState & 0x02) device.sensor.din[DIN_1].value = 1;
                                    else device.sensor.din[DIN_1].value=0;
                        
                                    if(dinState & 0x04) device.sensor.din[DIN_2].value = 1;
                                    else device.sensor.din[DIN_2].value=0;
                        
                                    if(dinState & 0x08) device.sensor.din[DIN_3].value = 1;
                                    else device.sensor.din[DIN_3].value=0;
                                    break;

                        case 20	: device.sensor.ain[1].value = EFM8BB_readSonarDistance()/10;        // Conversion de distance mm en cm
                                    //printf("Dist cm: %d - ",sensor.pwm[SONAR_0]);
                                    break;
                                    
			case 25	: device.sensor.ain[0].value = EFM8BB_readBatteryVoltage(); 
                                  //printf("Battery: %d\n",sensor.ain[BATT_0]);
                                break;
                        
                        case 30	: device.sensor.din[DIN_4].value = MCP2308_ReadGPIO(BTN_0);
                                  device.sensor.din[DIN_5].value = MCP2308_ReadGPIO(BTN_1);
                                  break;

                        //case 35	: sensor.RGBC[RGBC_SENS_0].red = BH1745_getRGBvalue(RGBC_SENS_0, RED) ;
                        case 35 : device.sensor.rgbc[RGBC_SENS_0].red = BH1745_getRGBvalue(RGBC_SENS_0, RED) ;
                                  device.sensor.rgbc[RGBC_SENS_0].green = BH1745_getRGBvalue(RGBC_SENS_0, GREEN) ;
                                  device.sensor.rgbc[RGBC_SENS_0].blue = BH1745_getRGBvalue(RGBC_SENS_0,BLUE) ;
                                  device.sensor.rgbc[RGBC_SENS_0].clear = BH1745_getRGBvalue(RGBC_SENS_0,CLEAR) ; break;
 
                        case 36 : device.sensor.rgbc[RGBC_SENS_1].red = BH1745_getRGBvalue(RGBC_SENS_1, RED) ;
                                  device.sensor.rgbc[RGBC_SENS_1].green = BH1745_getRGBvalue(RGBC_SENS_1, GREEN) ;
                                  device.sensor.rgbc[RGBC_SENS_1].blue = BH1745_getRGBvalue(RGBC_SENS_1, BLUE) ;
                                  device.sensor.rgbc[RGBC_SENS_1].clear = BH1745_getRGBvalue(RGBC_SENS_1, CLEAR) ; break;
                        
//                        case 40 : motor.stepper[STEPPER_0].isRunning = PCA9629_ReadMotorState(STEPPER_0) & 0x80; break;
                        case 40 : device.actuator.stepperMotor[STEPPER_0].isRunning = PCA9629_ReadMotorState(STEPPER_0) & 0x80; break;
                                
			default: 
                            if(i2c_command_queuing[0][CALLBACK]!=0)processCommandQueue(); break;
		}

		// Reset le compteur au bout de 50mS
		if(timeCount_ms<50)
			timeCount_ms++;
		else timeCount_ms=0;

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
	int pulses;

        pulses = device.sensor.counter[motorName].counter;
	/*
	switch(motorName){
		case MOTOR_0: pulses = buggySensor.left_encoder.pulseFromStartup; break;
		case MOTOR_1: pulses = buggySensor.right_encoder.pulseFromStartup; break;
		default: pulses= -1; break;
	}
	*/
	return pulses;
}

char getDigitalInput(unsigned char inputNumber){
	char inputState=0;

        inputState = device.sensor.din[inputNumber].value;
//        printf("DIG %d: %d\n",inputNumber, inputState);
	return inputState;
}

char getButtonInput(unsigned char buttonNumber){
	char inputState=0;

	//inputState = sensor.btn[buttonNumber];
        inputState = device.sensor.din[buttonNumber].value;
	return inputState;
}

int getMotorFrequency(unsigned char motorNb){
	int freq;
        
        freq = device.sensor.counter[motorNb].frequency;
        //printf("\n----- FREQ #%d: %d -----\n",motorNb, freq);
	return freq;
}


int getSonarDistance(void){
	int sonarCm=0;

	//sonarCm = sensor.pwm[SONAR_0];
        sonarCm = device.sensor.ain[1].value;
	//sonarCm= buggySensor.usonic;
	return sonarCm;
}

int getBatteryVoltage(void){
	int voltage=0;
	//voltage = sensor.ain[BATT_0];
        voltage = device.sensor.ain[0].value;
	//voltage = buggySensor.battery;
	return voltage;
}

int getColorValue(unsigned char sensorID, unsigned char color){
    int colorValue;
    
    switch(color){
        case RED : colorValue= device.sensor.rgbc[sensorID].red; break;
        case GREEN : colorValue=device.sensor.rgbc[sensorID].green; break;
        case BLUE : device.sensor.rgbc[sensorID].blue; break;
        case CLEAR : device.sensor.rgbc[sensorID].clear; break;
        default : colorValue = -1; break;
    }
/*    
    printf("RGBC# %d Values: RED: %d, GREEN: %d, BLUE: %d, CLEAR: %d VALUE: %d\n", sensorID,
                        sensor.RGBC[RGBC_SENS_0].red,
                        sensor.RGBC[RGBC_SENS_0].green,
                        sensor.RGBC[RGBC_SENS_0].blue,
                        sensor.RGBC[RGBC_SENS_0].clear,colorValue);
  */      
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

        set_i2c_command_queue(&MCP2308_DCmotorSetRotation, motorAdress, direction);
        
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
    
    unsigned char ctrlData = 0;
    unsigned char PMAmode = 0;
        

        // Check if motor inversion requiered and modify if necessary
    if(kehops.stepperWheel[motorNumber].config.motor.inverted)
        direction *= -1;

    switch(direction){
            case BUGGY_FORWARD :	ctrlData = 0x80; break;
            case BUGGY_BACK :           ctrlData = 0x81; break;

            case BUGGY_STOP : 		ctrlData = 0x20; break;
            default :		     	break;
    }
        
    if(stepCount<=0)
        // Configuration du driver pour une rotation continue
       PMAmode = 0x00;
    else
        // Configuration du driver pour une action unique
        PMAmode = 0x01;
    
    // Reset le registre de contronle
    // (Indispensable pour une nouvelle action après une action infinie)
    set_i2c_command_queue(&PCA9629_StepperMotorControl, motorNumber, 0x00);
    
    // Assignation du mode action continu ou unique
    set_i2c_command_queue(&PCA9629_StepperMotorMode, motorNumber, PMAmode);
    set_i2c_command_queue(&PCA9629_StepperMotorSetStep, motorNumber, stepCount);
    set_i2c_command_queue(&PCA9629_StepperMotorControl, motorNumber, ctrlData);

    
    return (0);
} 

// -------------------------------------------------------------------
// SETSTEPPERSPEED
// Configuration de la vitesse du moteur pas à pas
// - Numéro de moteur
// - vitesse 0..100%
// -------------------------------------------------------------------
int setStepperSpeed(int motorNumber, int speed){
        int regData;
    
    	// V�rification ratio max et min comprise entre 0..100%
	if(speed > 100)
		speed = 100;
	if (speed<0)
		speed = 1;

        // Periode minimum (2mS) + vitesse en % (max 22.5mS)
        regData = 0x029A + ((100-speed) * 75);
       
//        printf("\n\n\n REG DATA: %4x speed: %d\n\n\n", regData, speed);
        
	if(motorNumber >= 0)
		set_i2c_command_queue(&PCA9629_StepperMotorPulseWidth, motorNumber, regData);
	else
		printf("\n function [setStepperSpeed] : undefine motor #%d", motorNumber);
         
    return (1);
}                           

// -------------------------------------------------------------------
// GETSTEPPERSTATE
// Récupère l'état actuel du moteur pas à pas (run/off)
// - Numéro de moteur
// -------------------------------------------------------------------
int getStepperState(int motorNumber){
    return device.actuator.stepperMotor[motorNumber].isRunning;
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
        set_i2c_command_queue(&PCA9685_DCmotorSetSpeed, motorAdress, ratio);
        
	return(1);
}


// ------------------------------------------------------------------------------------
// SET_I2C_COMMAND_QUEUE: Mise en file d'attente de l'appelle d'une fonction I2C
// ------------------------------------------------------------------------------------
int set_i2c_command_queue(int (*callback)(char, int),char adr, int cmd){
	unsigned char freeIndex, i;

	// Recherche d'un emplacement libre dans la file d'attente
	for(freeIndex=0;(freeIndex<50) && (i2c_command_queuing[freeIndex][CALLBACK]>0);freeIndex++);

	if(freeIndex>=49) printf("\n[hwManager]->File de commande pleine !\n");
	else
	{
		i2c_command_queuing[freeIndex][CALLBACK] =  callback;
		i2c_command_queuing[freeIndex][ADR] =  adr;
		i2c_command_queuing[freeIndex][CMD] =  cmd;
	}


	return freeIndex;
}

void setLedPower(unsigned char ledID, unsigned char power){
	unsigned char ledAdress;
	ledAdress=getOrganI2Cregister(LED, ledID);
	set_i2c_command_queue(&PCA9685_setLedPower, ledAdress, power);
}

void setPwmPower(unsigned char ID, unsigned char power){
	unsigned char pwmAdress;
	pwmAdress=getOrganI2Cregister(PWM, ID);
	set_i2c_command_queue(&PCA9685_setLedPower, pwmAdress, power);
}

void setServoPosition(unsigned char ID, char position){
	unsigned char pwmAdress;
	pwmAdress=getOrganI2Cregister(PWM, ID);
	set_i2c_command_queue(&PCA9685_setServoPos, pwmAdress, position);
}

// ------------------------------------------------------------------------------------
// ONTIMEOUT: Fcontion appelee en fin de timer
// appelle une fonction callback pr�d�finie par *ptrFunc
// ------------------------------------------------------------------------------------
void execCommand(void (*ptrFunc)(char, int), char adr, int cmd){
	(*ptrFunc)(adr, cmd);		// Appelle de la fonction call back pr�d�finie par *ptrFonc avec les param�tre recus
}


void processCommandQueue(void){
	int i;
	// ENVOIE DE LA COMMANDE I2C

	//printf("#%d  callback: %d, adr: %d cmd: %d\n",0 ,i2c_command_queuing[0][CALLBACK],i2c_command_queuing[0][ADR],i2c_command_queuing[0][CMD]);
	execCommand(i2c_command_queuing[0][CALLBACK], i2c_command_queuing[0][ADR], i2c_command_queuing[0][CMD]);
	// DECALAGE DE LA PILE

	for(i=0;i<50;i++){
		i2c_command_queuing[i][CALLBACK] = i2c_command_queuing[i+1][CALLBACK];
		i2c_command_queuing[i][ADR] = i2c_command_queuing[i+1][ADR];
		i2c_command_queuing[i][CMD] = i2c_command_queuing[i+1][CMD];
	}
	i2c_command_queuing[49][CALLBACK]=i2c_command_queuing[49][ADR]=i2c_command_queuing[49][CMD]=0;
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
        
	if(organType == PWM){
		switch(organName){
			case PWM_0 : organAdr = PCA_CN1_4; break;
			case PWM_1 : organAdr = PCA_CN2_4; break;
			case PWM_2 : organAdr = PCA_CN3_7; break;
                        case PWM_3 : organAdr = PCA_CN4_4; break;
                        case PWM_4 : organAdr = PCA_CN7_3; break;
                        case PWM_5 : organAdr = PCA_CN8_3; break;
                        case PWM_6 : organAdr = PCA_CN9_7; break;
                        case PWM_7 : organAdr = PCA_CN10_4; break;
                        case PWM_8 : organAdr = PCA_CN11_3; break;
                        case PWM_9 : organAdr = PCA_CN12_3; break;
                        
			default :	organAdr = UNKNOWN; break;
		}
	}

	if(organType == LED){
		switch(organName){
			case LED_0 : organAdr = PCA_LED0; break;
			case LED_1 : organAdr = PCA_LED1; break;
			case LED_2 : organAdr = PCA_LED2; break;
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
        setMotorSpeed(i, 0);
        setMotorDirection(i, BUGGY_FORWARD);
        EFM8BB_clearWheelDistance(i);
    }

    // Etat initial des servomoteur   
    for(i=0;i<NBSERVO;i++)
        setServoPosition(i, 0);

    // Etat initial des LED       
    for(i=0;i<NBLED;i++){
//        if(Config->led[i].state)
//            setLedPower(i, Config->led[i].power);
//        else
//            setLedPower(i, 0);
    }
    // Etat initial des sorties PWM LED
    for(i=0;i<NBPWM;i++){
        setPwmPower(i,0);
    }
    return 0;
}