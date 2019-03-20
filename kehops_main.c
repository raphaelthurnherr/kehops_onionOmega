#define FIRMWARE_VERSION "0.6.6b"

#define DEFAULT_EVENT_STATE 1   

#define TASK_NUMBER 0
#define ACTION_ALGOID_ID 1
#define ACTION_COUNT 2

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "buildNumber.h"

#include "buggy_descriptor.h"
#include "kehopsCom/messagesManager.h"
#include "networkManager.h"
#include "linux_json.h"
#include "tools.h"
#include "kehops_main.h"
#include "timerManager.h"
#include "hwManager.h"
#include "asyncTools.h"
#include "asyncPWM.h"
#include "asyncSERVO.h"
#include "asyncLED.h"
#include "asyncMOTOR.h"
#include "asyncSTEPPER.h"
#include "configManager.h"
#include "type.h"
#include "wifi_json.h"

int getStartupArg(int count, char *arg[]);

int createBuggyTask(int MsgId, int actionCount);
int removeBuggyTask(int actionNumber);

void distanceEventCheck(void);
void batteryEventCheck(void);
void DINEventCheck(void);
void BUTTONEventCheck(void);
void COLOREventCheck(void);

// Traitement du message algoid recu
int processmessage(void);
int processAlgoidRequest(void);

int makeSensorsRequest(void);
int makeDistanceRequest(void);
int makeBatteryRequest(void);
int makeStatusRequest(int msgType);
int makeMotorRequest(void);
int makeButtonRequest(void);
int makeRgbRequest(void);
int makeConfigRequest(void);

int runMotorAction(void);
int runStepperAction(void);

int getWDvalue(int wheelName);
int getStepperValue(int motorName);

int runPwmAction(void);

//int setAsyncPwmAction(int actionNumber, int ledName, int time, int count);
//int endPwmAction(int actionNumber, int wheelNumber);

int getPwmSetting(int name);

int runLedAction(void);

int getLedSetting(int name);

int runUpdateCommand(int type);
void runRestartCommand(void);

void resetConfig(void);
void wifiSendScanResult(void);
void wifiSendNetworkList(void);

char reportBuffer[512];
int ActionTable[10][3];

int wifiScanDone=0;
int wifiListDone=0;

int wifiRequestMessageID=0;

robot_kehops kehops;
t_sysApp sysApp;
t_sysConf sysConf;

// -------------------------------------------------------------------
// MAIN APPLICATION
// - Cr�ation de t�che de gestion de la messagerie avec ALGOID, (ALGOID->JSON->MQTT BROCKER->JSON->BUGGY)
// - Cr�ation de t�che de gestion des timers pour la commande ON/OFF des roues, de l'acc�l�ration des roues, et timer @ 50mS, 100mS, 10Sec
// - Initialisation de la carte de commande hardware pour les moteurs, capteurs, etc...
// - Initialisation d'un broadcast UDP pour publication de la p�sence du buggy sur le r�seau
// -------------------------------------------------------------------

int main(int argc, char *argv[]) {
	int i, j;
        int systemDataStreamCounter=0;       // Compteur pour l'envoie periodique du flux de donnees des capteur
                                             // si activ�.
        char welcomeMessage[100];
	system("clear");

        // Récupération des paramètres [NomClient et address brocker] durant l'execution de l'application
        getStartupArg(argc, argv);
        
        sprintf(&welcomeMessage[0], "KEHOPS V%s - %s - build #%d\n", FIRMWARE_VERSION, __DATE__ , BUILD_CODE);		// Formattage du message avec le Nom du client buggy
        printf(welcomeMessage);
        printf ("------------------------------------\n");
        
// Cr�ation de la t�che pour la gestion réseau
        
	if(InitNetworkManager(&sysApp.info.wan_online, &sysConf.communication.mqtt.broker.address, &sysApp.info.name, &sysApp.info.group)) printf ("#[CORE] Creation tâche réseau : ERREUR\n");
        else {
            printf ("#[CORE] Demarrage tâche réseau: OK\n");            
        }
        
// Cr�ation de la t�che pour la gestion de la messagerie avec ALGOID

	if(InitMessager(&sysApp.info.name, &sysApp.info.group)) printf ("#[CORE] Creation t�che messagerie : ERREUR\n");
	else printf ("#[CORE] Demarrage tache Messager: OK\n");

        
// Cr�ation de la t�che pour la gestion des différents timers utilisés
	if(InitTimerManager()) printf ("#[CORE] Creation tâche timer : ERREUR\n");
		else printf ("#[CORE] Demarrage tâche timer: OK\n");

// Cr�ation de la t�che pour la gestion hardware
	if(InitHwManager()) printf ("#[CORE] Creation tâche hardware : ERREUR\n");
        else {
            resetHardware(&sysConf);            // Reset les peripheriques hardware selon configuration initiale
            printf ("#[CORE] Demarrage tâche hardware: OK\n");
        }
        
        sysApp.kehops.resetConfig=1;
        
// --------------------------------------------------------------------
// BOUCLE DU PROGRAMME PRINCIPAL
// - Messagerie avec ALGOID, attentes de messages en provenance de l'h�te -> D�marrage du traitement des commandes
// - Annonce UDP de pr�sence du buggy sur le r�seau  chaque 10Seconde
// - Gestion de l'acceleration du Buggy
// - Mesure sur les capteurs de distance, DIN et batterie
// - Gestion des �venements provoqu�s par les capteurs
// --------------------------------------------------------------------
               
	while(1){
            
        // CHeck if WifiScanResult is available
        if(wifiScanDone){
            wifiSendScanResult();
            wifiScanDone = 0;
        }

        // Check if WifiNetworkList is available
        if(wifiListDone){
            wifiSendNetworkList();
            wifiListDone = 0;
        }        
        
        // Check if reset was triggered by user
        
        if(sysApp.kehops.resetConfig>0){
            // Reset configuration to default value
            resetConfig();
            resetHardware(&sysConf);
            systemDataStreamCounter=0;
            runBashPing();
        }
           
        // Controle periodique de l'envoie du flux de donnees des capteurs (status)
        if(sysConf.communication.mqtt.stream.state==ON){
            if(systemDataStreamCounter++ >= sysConf.communication.mqtt.stream.time_ms){
                
                // Retourne un message "Status" sur topic "Stream"
                makeStatusRequest(DATAFLOW);
                systemDataStreamCounter=0;
            }
        }

        // Contr�le de la messagerie, recherche d'�ventuels messages ALGOID et effectue les traitements n�c�ssaire
        // selon le type du message [COMMAND, REQUEST, NEGOCIATION, ACK, REPONSE, ERROR, etc...]

        if(pullMsgStack(0)){
            switch(message.msgType){
                    case COMMAND : processmessage(); break;						// Traitement du message de type "COMMAND"
                    case REQUEST : processAlgoidRequest(); break;						// Traitement du message de type "REQUEST"
                    default : break;
            }
        }


	// Gestion de la v�locit� pour une acceleration proggressive
    	// modification de la v�locit� environ chaque 50mS
        
        if(checkMotorPowerFlag){
            checkDCmotorPower();													// Contr�le si la v�locit� correspond � la consigne
            checkMotorPowerFlag=0;
        }
         
        // Contr�le du TIMER 10seconde
    	if(t10secFlag){
    		t10secFlag=0;
    	}
               
        if(t60secFlag){
            t60secFlag=0;
        }


	// Contr�le du TIMER 100mS
    	// - R�cup�ration de la tension de batterie
    	// - R�cup�ration de la distance mesur�e au sonar
    	// - Gestion des �venements batterie, digital inputs et distance
    	if(t100msFlag){
                        for(i=0;i<NBMOTOR;i++){   
                            // Convert millimeter per pulse to centimeter per pulse and calculation of distance
                            kehops.dcWheel[i].measure.speed_cmS = (float)(getMotorFrequency(i)) * (kehops.dcWheel[i].data._MMPP / 10.0);
                            kehops.dcWheel[i].measure.rpm = 60 * (float)(getMotorFrequency(i)) / (kehops.dcWheel[i].config.pulsesPerRot);
                            kehops.dcWheel[i].measure.distance = (float)(getMotorPulses(i)) * (kehops.dcWheel[i].data._MMPP / 10.0);
                        }
                        
                        kehops.sonar[0].measure.distance_cm = getSonarDistance()/10;
			distanceEventCheck();										// Provoque un �venement de type "distance" si la distance mesur�e					// est hors de la plage sp�cifi�e par l'utilisateur
                        
			DINEventCheck();										// Cont�le de l'�tat des entr�es num�rique
															// G�n�re un �venement si changement d'�tat d�tect�

                        BUTTONEventCheck();										// Cont�le de l'�tat des entr�es bouton
															// G�n�re un �venement si changement d'�tat d�tect�
                                        										// Cont�le les valeur RGB des capteurs
                        
                        kehops.battery[0].measure.voltage_mV = getBatteryVoltage();
                        kehops.battery[0].measure.capacity =(kehops.battery[0].measure.voltage_mV-3500)/((4210-3500)/100);
                        batteryEventCheck();

                                                // R�cup�ration des couleur mesur�e sur les capteurs
                        for(i=0;i<NBRGBC;i++){
                            kehops.rgb[i].color.red.measure.value = getColorValue(i,RED);
                            kehops.rgb[i].color.green.measure.value = getColorValue(i,GREEN);
                            kehops.rgb[i].color.blue.measure.value = getColorValue(i,BLUE);
                            kehops.rgb[i].color.clear.measure.value = getColorValue(i,CLEAR);
                        }
                        
                        COLOREventCheck();
			t100msFlag=0;												// Quittance le flag 100mS
    	}
        
        sysApp.info.startUpTime++;
    	usleep(1000);	// Attente de 1ms
    }
 
	// ------------ FIN DE LA BOUCLE PRINCIPALE ----------------------


	// Fermetur du programme
	int endState=CloseMessager();										// Ferme la t�che de messagerie
	if(!endState)
		  printf( "# ARRET tache Messager - status: %d\n", endState);
	else printf( "# ARRET tache Messager erreur - status: %d\n", endState);

	return EXIT_SUCCESS;												// Fin du programme
}

// -------------------------------------------------------------------
// PROCESSCOMMAND
// S�l�ctionne et traite le param�tre de commande recue [LL2WD, BACK, FORWARD, STOP, SPIN, etc...]
// -------------------------------------------------------------------
int processmessage(void){
    int i, valCnt;
    int updateResult;
	switch(message.msgParam){
		case MOTORS : 	
                                for(i=0;i<message.msgValueCnt;i++){
                                   
                                    // Controle que le moteur existe...
                                    if(message.DCmotor[i].motor >= 0 && message.DCmotor[i].motor<NBMOTOR)
                                        messageResponse[i].MOTresponse.motor=message.DCmotor[i].motor;
                                    else
                                        messageResponse[i].MOTresponse.motor=-1;
                                            
                                    // Récupération des paramètes de commandes
                                    
                                    // Retourne un message ALGOID si velocité hors tolérences
                                    if((message.DCmotor[i].userSetPoint < -100) ||(message.DCmotor[i].userSetPoint > 100)){
                                            message.DCmotor[i].userSetPoint=0;
                                            messageResponse[i].MOTresponse.userSetPoint=-1;
                                            
                                    }else{
                                        messageResponse[i].MOTresponse.userSetPoint=message.DCmotor[i].userSetPoint;
                                    }
                                        messageResponse[i].MOTresponse.cm=message.DCmotor[i].cm;
                                        messageResponse[i].MOTresponse.time=message.DCmotor[i].time;
                                        messageResponse[i].responseType = RESP_STD_MESSAGE;
                                    
                                        
                                }
                                // Retourne en r�ponse le message v�rifi�
                                sendResponse(message.msgID, message.msgFrom, RESPONSE, MOTORS, message.msgValueCnt);  // Retourne une r�ponse d'erreur, (aucun moteur d�fini)
                                runMotorAction(); break;			// Action avec en param�tre MOTEUR, VELOCITE, ACCELERATION, TEMPS d'action
                                
		case STEPPER : 	
                                for(i=0;i<message.msgValueCnt;i++){
                                   
                                    // Controle que le moteur existe...
                                    if(message.StepperMotor[i].motor >= 0 && message.StepperMotor[i].motor < NBSTEPPER)
                                        messageResponse[i].STEPPERresponse.motor=message.StepperMotor[i].motor;
                                    else
                                        messageResponse[i].STEPPERresponse.motor=-1;
                                            
                                    // Récupération des paramètes de commandes
                                    
                                    // Retourne un message ALGOID si velocit� hors tol�rences
                                    if((message.StepperMotor[i].userSetPoint < -100) ||(message.StepperMotor[i].userSetPoint > 100)){
                                            message.StepperMotor[i].userSetPoint=0;
                                            messageResponse[i].STEPPERresponse.userSetPoint=-1;
                                    }else
                                        messageResponse[i].STEPPERresponse.userSetPoint=message.StepperMotor[i].userSetPoint;
                                    
                                    messageResponse[i].STEPPERresponse.step=message.StepperMotor[i].step;
                                    messageResponse[i].STEPPERresponse.rotation=message.StepperMotor[i].rotation;
                                    messageResponse[i].responseType = RESP_STD_MESSAGE;
                                }
                                // Retourne en r�ponse le message v�rifi�
                                sendResponse(message.msgID, message.msgFrom, RESPONSE, STEPPER, message.msgValueCnt);  // Retourne une r�ponse d'erreur, (aucun moteur d�fini)
                                
                                runStepperAction(); break;			// Action avec en param�tre MOTEUR, VELOCITE, PAS, ROTATION
                                
                case pPWM  :
                                for(i=0;i<message.msgValueCnt;i++){
                                    // Vérification de l'existance de l'index de sortie PWM et défini le mode PWM(FULL)
                                    if(message.PWMarray[i].id >= 0 && message.PWMarray[i].id <NBPWM){
                                        kehops.pwm[message.PWMarray[i].id].config.mode = 0;
                                        messageResponse[i].PWMresponse.id=message.PWMarray[i].id;
                                    }
                                    else
                                        messageResponse[i].PWMresponse.id=-1;
                                            
                                    // R�cup�ration des param�tes 
                                    strcpy(messageResponse[i].PWMresponse.state, message.PWMarray[i].state);
                                    messageResponse[i].PWMresponse.powerPercent=message.PWMarray[i].powerPercent;
                                    messageResponse[i].PWMresponse.blinkCount=message.PWMarray[i].blinkCount;
                                    messageResponse[i].PWMresponse.time=message.PWMarray[i].time;
                                    messageResponse[i].responseType = RESP_STD_MESSAGE;
                                }

                                // Retourne en r�ponse le message v�rifi�
                                sendResponse(message.msgID, message.msgFrom, RESPONSE, pPWM, message.msgValueCnt);     
                    
                                runPwmAction();break;

                case pSERVO  : 
                                for(i=0;i<message.msgValueCnt;i++){
                                    // Vérification de l'existance de l'index de sortie PWM et défini le mode SERVO
                                    if(message.PWMarray[i].id >= 0 && message.PWMarray[i].id <NBPWM){
                                        messageResponse[i].PWMresponse.id=message.PWMarray[i].id;
                                        kehops.pwm[message.PWMarray[i].id].config.mode = 1;
                                    }
                                    else
                                        messageResponse[i].PWMresponse.id=-1;
                                            
                                    // R�cup�ration des param�tes 
                                    strcpy(messageResponse[i].PWMresponse.state, message.PWMarray[i].state);
                                    
                                    messageResponse[i].PWMresponse.powerPercent=message.PWMarray[i].powerPercent;
                                    messageResponse[i].responseType = RESP_STD_MESSAGE;
                                }
                                // Retourne en r�ponse le message v�rifi�
                                sendResponse(message.msgID, message.msgFrom, RESPONSE, pSERVO, message.msgValueCnt);     
                    
                                runPwmAction();break;
                                
		case pLED  : 	
                                for(i=0;i<message.msgValueCnt;i++){
                                    // Controle que le moteur existe...
                                    if(message.LEDarray[i].id >= 0 && message.LEDarray[i].id <NBLED)
                                        messageResponse[i].LEDresponse.id=message.LEDarray[i].id;
                                    else
                                        messageResponse[i].LEDresponse.id=-1;
                                            
                                    // R�cup�ration des param�tes 
                                    strcpy(messageResponse[i].LEDresponse.state, message.LEDarray[i].state);
                                    messageResponse[i].LEDresponse.powerPercent=message.LEDarray[i].powerPercent;
                                    messageResponse[i].LEDresponse.blinkCount=message.LEDarray[i].blinkCount;
                                    messageResponse[i].LEDresponse.time=message.LEDarray[i].time;
                                    messageResponse[i].responseType = RESP_STD_MESSAGE;
                                }
                                // Retourne en r�ponse le message v�rifi�
                                sendResponse(message.msgID, message.msgFrom, RESPONSE, pLED, message.msgValueCnt);               
                                
                                runLedAction();
                                break;
                                
            case CONFIG  :
                
                                for(valCnt=0;valCnt<message.msgValueCnt;valCnt++){
                                // CONFIG COMMAND FOR RESET
                                    if(!strcmp(message.Config.action.reset, "true")){
                                        resetConfig();              // !!! Dont'work, string stay in structure and are used later
                                    }

                            // CONFIG COMMAND FOR DATASTREAM

                                    // Récupére les parametres de configuration du nom du robot si specifié
                                    if(strcmp(message.Config.robot.name, ""))
                                        strcpy(sysApp.info.name, message.Config.robot.name);                      // Enregistrement du nom du system
                                    
                                    // R�cup�re les parametres de configuration du group du robot
                                    if(strcmp(message.Config.robot.group, ""))
                                        strcpy(sysApp.info.group, message.Config.robot.group);                      // Enregistrement du group
                                    
                                    // R�cup�re les parametres de configuration du broker distant
                                    if(strcmp(message.Config.broker.address, ""))
                                        strcpy(sysConf.communication.mqtt.broker.address, message.Config.broker.address);                      // Enregistrement du broker distant
                                    
                                    // R�cup�re les parametres eventuelle pour la configuration de l'etat de l'envoie du stream par polling
                                    if(!strcmp(message.Config.stream.state, "on"))
                                        sysConf.communication.mqtt.stream.state=1; 			// Activation de l'envoie du datastream
                                    else
                                        if(!strcmp(message.Config.stream.state, "off"))
                                            sysConf.communication.mqtt.stream.state=0; 		// Desactivation de l'envoie du datastream

                                    
                                    // R�cup�re les parametres eventuelle pour la configuration de l'etat de l'envoie du stream par evenement
                                    if(!strcmp(message.Config.stream.onEvent, "on"))
                                        sysConf.communication.mqtt.stream.onEvent=1; 			// Activation de l'envoie du datastream
                                    else
                                        if(!strcmp(message.Config.stream.onEvent, "off"))
                                            sysConf.communication.mqtt.stream.onEvent=0; 		// Desactivation de l'envoie du datastr
                                    
                                    if(message.Config.stream.time>0)
                                        sysConf.communication.mqtt.stream.time_ms=message.Config.stream.time;
                                    
                                // CONFIG COMMAND FOR MOTOR SETTING
                                    for(i=0;i<message.Config.motValueCnt; i++){
                                        messageResponse[valCnt].CONFIGresponse.motValueCnt=message.Config.motValueCnt;
                                        // Check if motor exist...
                                        if(message.Config.motor[i].id >= 0 && message.Config.motor[i].id <NBMOTOR){
                                            // Save config for motor inversion
                                            if(!strcmp(message.Config.motor[i].inverted, "on")){
                                                kehops.dcWheel[message.Config.motor[i].id].config.motor.inverted = 1;
                                                strcpy(messageResponse[valCnt].CONFIGresponse.motor[i].inverted, "on");
                                            }
                                            else if(!strcmp(message.Config.motor[i].inverted, "off")){
                                                    kehops.dcWheel[message.Config.motor[i].id].config.motor.inverted = 0;
                                                    strcpy(messageResponse[valCnt].CONFIGresponse.motor[i].inverted, "off");
                                            }

                                            // Save config for motor Min PWM for run
                                            if(message.Config.motor[i].minPWM >=0)
                                                kehops.dcWheel[message.Config.motor[i].id].config.motor.powerMin = message.Config.motor[i].minPWM;
                                            
                                            // Save config for motor Min Max RPM
                                            if(message.Config.motor[i].minRPM >=0)
                                                kehops.dcWheel[message.Config.motor[i].id].config.rpmMin = message.Config.motor[i].minRPM;
                                            if(message.Config.motor[i].maxRPM >=0)
                                                kehops.dcWheel[message.Config.motor[i].id].config.rpmMax = message.Config.motor[i].maxRPM;
                                            
                                            // Save config for motor PID regulator
                                            if(!strcmp(message.Config.motor[i].rpmRegulator.PIDstate, "on")){
                                                kehops.dcWheel[message.Config.motor[i].id].config.pidReg.enable = 1;
                                                strcpy(messageResponse[valCnt].CONFIGresponse.motor[i].rpmRegulator.PIDstate, "on");
                                            }
                                            else if(!strcmp(message.Config.motor[i].rpmRegulator.PIDstate, "off")){
                                                kehops.dcWheel[message.Config.motor[i].id].config.pidReg.enable = 0;
                                                strcpy(messageResponse[valCnt].CONFIGresponse.motor[i].rpmRegulator.PIDstate, "off");
                                            }
                                            if(message.Config.motor[i].rpmRegulator.PID_Kp >= 0.0)
                                                kehops.dcWheel[message.Config.motor[i].id].config.pidReg.Kp = message.Config.motor[i].rpmRegulator.PID_Kp;
                                            if(message.Config.motor[i].rpmRegulator.PID_Ki >= 0.0)
                                                kehops.dcWheel[message.Config.motor[i].id].config.pidReg.Ki = message.Config.motor[i].rpmRegulator.PID_Ki;
                                            if(message.Config.motor[i].rpmRegulator.PID_Kd >= 0.0)
                                                kehops.dcWheel[message.Config.motor[i].id].config.pidReg.Kd = message.Config.motor[i].rpmRegulator.PID_Kd;                                            
                                            
                                            
                                            messageResponse[valCnt].CONFIGresponse.motor[i].id = message.Config.motor[i].id;
                                            messageResponse[valCnt].CONFIGresponse.motor[i].minPWM = message.Config.motor[i].minPWM;
                                            messageResponse[valCnt].CONFIGresponse.motor[i].minRPM = message.Config.motor[i].minRPM;
                                            messageResponse[valCnt].CONFIGresponse.motor[i].maxRPM = message.Config.motor[i].maxRPM;
                                            messageResponse[valCnt].CONFIGresponse.motor[i].rpmRegulator.PID_Kp = message.Config.motor[i].rpmRegulator.PID_Kp;
                                            messageResponse[valCnt].CONFIGresponse.motor[i].rpmRegulator.PID_Ki = message.Config.motor[i].rpmRegulator.PID_Ki;
                                            messageResponse[valCnt].CONFIGresponse.motor[i].rpmRegulator.PID_Kd = message.Config.motor[i].rpmRegulator.PID_Kd;
                                        }
                                        else
                                            messageResponse[valCnt].CONFIGresponse.motor[i].id=-1;
                                    }

                                // CONFIG COMMAND FOR WHEEL SETTING
                                    for(i=0;i<message.Config.wheelValueCnt; i++){
                                        messageResponse[valCnt].CONFIGresponse.wheelValueCnt=message.Config.wheelValueCnt;
                                        // Check if motor exist...
                                        if(message.Config.wheel[i].id >= 0 && message.Config.wheel[i].id <NBMOTOR){
                                            // Save config for motor inversion
                                            if(message.Config.wheel[i].diameter >= 0)
                                                kehops.dcWheel[message.Config.wheel[i].id].config.diameter = message.Config.wheel[i].diameter;
                                            if(message.Config.wheel[i].pulsesPerRot)
                                                kehops.dcWheel[message.Config.wheel[i].id].config.pulsesPerRot = message.Config.wheel[i].pulsesPerRot;
                                                
                                                // Calculation of value for centimeter for each pulse
                                                kehops.dcWheel[message.Config.wheel[i].id].data._MMPP = (kehops.dcWheel[message.Config.wheel[i].id].config.diameter * 3.1415926535897932384)/kehops.dcWheel[message.Config.wheel[i].id].config.pulsesPerRot;
                                            
                                            messageResponse[valCnt].CONFIGresponse.wheel[i].id = message.Config.wheel[i].id;
                                            messageResponse[valCnt].CONFIGresponse.wheel[i].diameter = kehops.dcWheel[message.Config.wheel[i].id].config.diameter;
                                            messageResponse[valCnt].CONFIGresponse.wheel[i].pulsesPerRot = kehops.dcWheel[message.Config.wheel[i].id].config.pulsesPerRot;
                                            
                                            
                                        }
                                        else
                                            messageResponse[valCnt].CONFIGresponse.wheel[i].id=-1;
                                    }                                    
                                    
                                // CONFIG COMMAND FOR STEPPER SETTING
                                    for(i=0;i<message.Config.stepperValueCnt; i++){
                                        messageResponse[valCnt].CONFIGresponse.stepperValueCnt=message.Config.stepperValueCnt;
                                        // Check if motor exist...
                                        if(message.Config.stepper[i].id >= 0 && message.Config.stepper[i].id < NBSTEPPER){
                                            // Save config for motor inversion
                                            if(!strcmp(message.Config.stepper[i].inverted, "on")){
                                                kehops.stepperWheel[message.Config.stepper[i].id].config.motor.inverted = 1;
                                                strcpy(messageResponse[valCnt].CONFIGresponse.stepper[i].inverted, "on");
                                            }
                                            else if(!strcmp(message.Config.stepper[i].inverted, "off")){
                                                kehops.stepperWheel[message.Config.stepper[i].id].config.motor.inverted = 0;
                                                    strcpy(messageResponse[valCnt].CONFIGresponse.stepper[i].inverted, "off");
                                            }
                                            
                                            kehops.stepperWheel[message.Config.stepper[i].id].config.motor.ratio = message.Config.stepper[i].ratio;
                                            kehops.stepperWheel[message.Config.stepper[i].id].config.motor.steps = message.Config.stepper[i].stepsPerRot;
                                            
                                            
                                            messageResponse[valCnt].CONFIGresponse.stepper[i].id = message.Config.stepper[i].id;
                                            messageResponse[valCnt].CONFIGresponse.stepper[i].ratio = kehops.stepperWheel[message.Config.stepper[i].id].config.motor.ratio;
                                            messageResponse[valCnt].CONFIGresponse.stepper[i].stepsPerRot = kehops.stepperWheel[message.Config.stepper[i].id].config.motor.steps;
                                            
                                        }
                                        else
                                            messageResponse[valCnt].CONFIGresponse.stepper[i].id=-1;
                                    }                                    

                                // CONFIG COMMAND FOR LED SETTING
                                    for(i=0;i<message.Config.ledValueCnt; i++){
                                        messageResponse[valCnt].CONFIGresponse.ledValueCnt=message.Config.ledValueCnt;
                                        
                                        // Check if led exist...
                                        if(message.Config.led[i].id >= 0 && message.Config.led[i].id <NBLED){
                                            kehops.led[message.Config.led[i].id].config.defaultPower = message.Config.led[i].power;
                                            messageResponse[valCnt].CONFIGresponse.led[i].power=message.Config.led[i].power;
                                            // Save config for led inversion
                                            if(!strcmp(message.Config.led[i].state, "on")){
                                                kehops.led[message.Config.led[i].id].config.defaultState = 1;
                                                strcpy(messageResponse[valCnt].CONFIGresponse.led[i].state, "on");
                                            }
                                            else if(!strcmp(message.Config.led[i].state, "off")){
                                                kehops.led[message.Config.led[i].id].config.defaultState = 0;
                                                strcpy(messageResponse[valCnt].CONFIGresponse.led[i].state, "off");
                                            }

                                            messageResponse[valCnt].CONFIGresponse.led[i].id = message.Config.led[i].id;
                                        }
                                        else
                                            messageResponse[valCnt].CONFIGresponse.led[i].id=-1;
                                    }
                                    
                                    // CONFIG COMMAND FOR PWM OUTPUT SETTING
                                    for(i=0;i<message.Config.pwmValueCnt; i++){
                                        messageResponse[valCnt].CONFIGresponse.pwmValueCnt=message.Config.pwmValueCnt;
                                        
                                        // Check if PWM exist...
                                        if(message.Config.pwm[i].id >= 0 && message.Config.pwm[i].id <NBPWM){
                                            kehops.pwm[message.Config.pwm[i].id].config.defaultPower = message.Config.pwm[i].power;
                                            messageResponse[valCnt].CONFIGresponse.pwm[i].power=message.Config.pwm[i].power;
                                            // Save config for led inversion
                                            if(!strcmp(message.Config.pwm[i].state, "on")){
                                                kehops.pwm[message.Config.pwm[i].id].config.defaultState = 1;
                                                strcpy(messageResponse[valCnt].CONFIGresponse.pwm[i].state, "on");
                                            }
                                            else if(!strcmp(message.Config.pwm[i].state, "off")){
                                                kehops.pwm[message.Config.pwm[i].id].config.defaultState = 0;
                                                strcpy(messageResponse[valCnt].CONFIGresponse.pwm[i].state, "off");
                                            }

                                            messageResponse[valCnt].CONFIGresponse.pwm[i].id = message.Config.pwm[i].id;
                                        }
                                        else
                                            messageResponse[valCnt].CONFIGresponse.pwm[i].id=-1;
                                    }
                                    
                                    // CONFIG COMMAND FOR DIN SETTING
                                    for(i=0;i<message.Config.dinValueCnt; i++){
                                        messageResponse[valCnt].CONFIGresponse.dinValueCnt=message.Config.dinValueCnt;
                                        
                                        
                                        // Check if DIN exist...
                                        if(message.Config.din[i].id >= 0 && message.Config.din[i].id<NBDIN){

                                            // Save config for DIN event State
                                            if(!strcmp(message.Config.din[i].event_state, "on")){
                                                kehops.proximity[message.Config.din[i].id].event.enable = 1;
                                                strcpy(messageResponse[valCnt].CONFIGresponse.din[i].event_state, "on");
                                            }
                                            else if(!strcmp(message.Config.din[i].event_state, "off")){
                                                kehops.proximity[message.Config.din[i].id].event.enable = 0;
                                                strcpy(messageResponse[valCnt].CONFIGresponse.din[i].event_state, "off");
                                            }
                                            messageResponse[valCnt].CONFIGresponse.din[i].id = message.Config.din[i].id;
                                        }
                                        else
                                            messageResponse[valCnt].CONFIGresponse.din[i].id=-1;
                                    }
                                    
                                    // CONFIG COMMAND FOR BTN SETTING
                                    for(i=0;i<message.Config.dinValueCnt; i++){
                                        messageResponse[valCnt].CONFIGresponse.btnValueCnt=message.Config.btnValueCnt;
                                        
                                        // Check if DIN exist...
                                        if(message.Config.btn[i].id >= 0 && message.Config.btn[i].id <NBBTN){

                                            // Save config for BTN event State
                                            if(!strcmp(message.Config.btn[i].event_state, "on")){
                                                kehops.button[message.Config.btn[i].id].event.enable = 1;
                                                strcpy(messageResponse[valCnt].CONFIGresponse.btn[i].event_state, "on");
                                            }
                                            else if(!strcmp(message.Config.btn[i].event_state, "off")){
                                                kehops.button[message.Config.btn[i].id].event.enable = 0;
                                                strcpy(messageResponse[valCnt].CONFIGresponse.btn[i].event_state, "off");
                                            }
                                            messageResponse[valCnt].CONFIGresponse.btn[i].id = message.Config.btn[i].id;
                                        }
                                        else
                                            messageResponse[valCnt].CONFIGresponse.btn[i].id=-1;
                                    }
                                    
                                    // CONFIG COMMAND FOR SONAR SETTING
                                    for(i=0;i<message.Config.sonarValueCnt; i++){
                                        messageResponse[valCnt].CONFIGresponse.sonarValueCnt=message.Config.sonarValueCnt;
                                        
                                        // Check if SONAR exist...
                                        if(message.Config.sonar[i].id >= 0 && message.Config.sonar[i].id <NBSONAR){

                                            // Save config for SONAR event State
                                            if(!strcmp(message.Config.sonar[i].event_state, "on")){
                                                kehops.sonar[message.Config.sonar[i].id].event.enable = 1;
                                                strcpy(messageResponse[valCnt].CONFIGresponse.sonar[i].event_state, "on");
                                            }
                                            else if(!strcmp(message.Config.sonar[i].event_state, "off")){
                                                kehops.sonar[message.Config.sonar[i].id].event.enable = 0;
                                                strcpy(messageResponse[valCnt].CONFIGresponse.sonar[i].event_state, "off");
                                            }
                                            // Save config for SONAR event LOW, HIGH and HYSTERESIS
                                            kehops.sonar[message.Config.sonar[i].id].event.low = message.Config.sonar[i].event_low;
                                            kehops.sonar[message.Config.sonar[i].id].event.high = message.Config.sonar[i].event_high;
                                            kehops.sonar[message.Config.sonar[i].id].event.hysteresis = message.Config.sonar[i].event_hyst;
                                            
                                            messageResponse[valCnt].CONFIGresponse.sonar[i].id = message.Config.sonar[i].id;
                                            messageResponse[valCnt].CONFIGresponse.sonar[i].event_low = message.Config.sonar[i].event_low;
                                            messageResponse[valCnt].CONFIGresponse.sonar[i].event_high = message.Config.sonar[i].event_high;
                                            messageResponse[valCnt].CONFIGresponse.sonar[i].event_hyst = message.Config.sonar[i].event_hyst;
                                        }
                                        else
                                            messageResponse[valCnt].CONFIGresponse.sonar[i].id=-1;
                                    }

                                    // CONFIG COMMAND FOR BATTERY SETTING
                                    for(i=0;i<message.Config.battValueCnt; i++){
                                        messageResponse[valCnt].CONFIGresponse.battValueCnt=message.Config.battValueCnt;
                                        
                                        // Check if BATTERY exist...
                                        if(message.Config.battery[i].id >= 0 && message.Config.battery[i].id <NBAIN){

                                            // Save config for BATTERY event State
                                            if(!strcmp(message.Config.battery[i].event_state, "on")){
                                                kehops.battery[message.Config.battery[i].id].event.enable = 1;
                                                strcpy(messageResponse[valCnt].CONFIGresponse.battery[i].event_state, "on");
                                            }
                                            else if(!strcmp(message.Config.battery[i].event_state, "off")){
                                                kehops.battery[message.Config.battery[i].id].event.enable = 0;
                                                strcpy(messageResponse[valCnt].CONFIGresponse.battery[i].event_state, "off");
                                            }
                                            // Save config for SONAR event LOW, HIGH and HYSTERESIS
                                            kehops.battery[message.Config.battery[i].id].event.low = message.Config.battery[i].event_low;
                                            kehops.battery[message.Config.battery[i].id].event.high = message.Config.battery[i].event_high;
                                            kehops.battery[message.Config.battery[i].id].event.hysteresis = message.Config.battery[i].event_hyst;
                                            
                                            messageResponse[valCnt].CONFIGresponse.battery[i].id = message.Config.battery[i].id;
                                            messageResponse[valCnt].CONFIGresponse.battery[i].event_low = message.Config.battery[i].event_low;
                                            messageResponse[valCnt].CONFIGresponse.battery[i].event_high = message.Config.battery[i].event_high;
                                            messageResponse[valCnt].CONFIGresponse.battery[i].event_hyst = message.Config.battery[i].event_hyst;
                                        }
                                        else
                                            messageResponse[valCnt].CONFIGresponse.battery[i].id=-1;
                                    }
                                    
                                // CONFIG COMMAND FOR SAVE
                                    if(!strcmp(message.Config.action.save, "true")){
                                        SaveConfig("kehops.cfg");
                                        sprintf(reportBuffer, "Save KEHOPS configuration for message #%d\n", message.msgID);
                                        printf(reportBuffer);                                                             // Affichage du message dans le shell
                                        sendMqttReport(message.msgID, reportBuffer);				      // Envoie le message sur le canal MQTT "Report"
                                    }                                    
                                    
                        // Préparation des valeurs du message de réponse
                                    
                                    strcpy(messageResponse[valCnt].CONFIGresponse.robot.name, sysApp.info.name);
                                    strcpy(messageResponse[valCnt].CONFIGresponse.robot.group, sysApp.info.group);
                                    strcpy(messageResponse[valCnt].CONFIGresponse.broker.address, sysConf.communication.mqtt.broker.address);
                                    
                                // GET STREAM CONFIG FOR RESPONSE
                                    messageResponse[valCnt].CONFIGresponse.stream.time=sysConf.communication.mqtt.stream.time_ms;
                                    
                                    if(sysConf.communication.mqtt.stream.onEvent==0) 
                                        strcpy(messageResponse[valCnt].CONFIGresponse.stream.onEvent, "off");
                                    else strcpy(messageResponse[valCnt].CONFIGresponse.stream.onEvent, "on");

                                    if(sysConf.communication.mqtt.stream.state==0) 
                                        strcpy(messageResponse[valCnt].CONFIGresponse.stream.state, "off");
                                    else strcpy(messageResponse[valCnt].CONFIGresponse.stream.state, "on");

                                    if(sysApp.kehops.resetConfig == 1) 
                                        strcpy(messageResponse[valCnt].CONFIGresponse.action.reset, "true");
                                    else strcpy(messageResponse[valCnt].CONFIGresponse.action.reset, "---");
                                    
                                    if(!strcmp(message.Config.action.save, "true")) 
                                        strcpy(messageResponse[valCnt].CONFIGresponse.action.save, "true");
                                    else strcpy(messageResponse[valCnt].CONFIGresponse.action.save, "---");
                                    
                                    messageResponse[valCnt].responseType = RESP_STD_MESSAGE;
                                } 
                                
                                //messageResponse[0].responseType = RESP_STD_MESSAGE;                     
                                // Retourne en r�ponse le message v�rifi�
                                sendResponse(message.msgID, message.msgFrom, RESPONSE, CONFIG, message.msgValueCnt);
                                
                                sprintf(reportBuffer, "Update KEHOPS configuration for message #%d\n", message.msgID);
                                printf(reportBuffer);                                                             // Affichage du message dans le shell
                                sendMqttReport(message.msgID, reportBuffer);				      // Envoie le message sur le canal MQTT "Report"

                                break;
                                
            case SYSTEM :       
                                // RECHERCHE DES MISE A JOURS
                                if(!strcmp(message.System.firmwareCommand, "check")){
                                    messageResponse[0].responseType=EVENT_ACTION_BEGIN;                                            
                                    updateResult = runUpdateCommand(0);
                                                               
                                    switch(updateResult){
                                        case 1 :   strcpy(messageResponse[0].returnMessage, "connection error");
                                                   strcpy(messageResponse[0].returnMessage, "connection error"); break;
                                        case 10 :  strcpy(messageResponse[0].returnMessage, "update available"); break;
                                        case 11 :  strcpy(messageResponse[0].returnMessage, "no update"); break;
                                        default:   
                                                   sprintf(messageResponse[0].returnMessage, "error %d", updateResult); break;
                                    }
                                    
                                    strcpy(messageResponse[0].SYSCMDresponse.firmwareCommand, "check");

                                    messageResponse[0].responseType = RESP_FIRMWARE;
                                    sendResponse(message.msgID, message.msgFrom, RESPONSE, SYSTEM, message.msgValueCnt);
                                    
                                    // Reset la commande system de type firmware
                                    strcpy(message.System.firmwareCommand,"");
                                }
                                
                                // MISE A JOUR DE L'APPLICATION
                                if(!strcmp(message.System.firmwareCommand, "update")){
                                    
                                    // Retourne le message en réponse sur topic "RESPONSE"
                                    messageResponse[0].responseType = RESP_FIRMWARE;
                                    strcpy(messageResponse[0].SYSCMDresponse.firmwareCommand, "update");
                                    strcpy(messageResponse[0].returnMessage, "updating... ");
                                    sendResponse(message.msgID, message.msgFrom, RESPONSE, SYSTEM, message.msgValueCnt);

                                    // Retourne le message sur topic "EVENT"                                    
                                    messageResponse[0].responseType=EVENT_ACTION_BEGIN;
                                    sendResponse(message.msgID, message.msgFrom, EVENT, SYSTEM, message.msgValueCnt);
                                    
                                    updateResult = runUpdateCommand(1);
                                  
                                    // FIN DE L'APPLICATION DES CE MOMENT!!!!
                                }
                                
                                // Restart application
                                if(!strcmp(message.System.firmwareCommand, "restart")){
                                    
                                    // Retourne le message en réponse sur topic "RESPONSE"               
                                    messageResponse[0].responseType = RESP_FIRMWARE;
                                    strcpy(messageResponse[0].SYSCMDresponse.firmwareCommand, "restart");
                                    strcpy(messageResponse[0].returnMessage, "restarting... ");
                                    sendResponse(message.msgID, message.msgFrom, RESPONSE, SYSTEM, message.msgValueCnt);
                                    
                                    // Retourne le message sur topic "EVENT"    
                                    messageResponse[0].responseType=EVENT_ACTION_BEGIN;
                                    sendResponse(message.msgID, message.msgFrom, EVENT, SYSTEM, message.msgValueCnt);
                                    
                                    usleep(1000);
                                    runRestartCommand();

                                    // FIN DE L'APPLICATION DES CE MOMENT!!!!    
                                }
                                
                                // wifiSetup
                                if(!strcmp(message.System.wifi.command.name, "scan")){
                                    
                                    strcpy(messageResponse[0].SYSCMDresponse.wifi.command.name, "scan");
                                    messageResponse[0].responseType = RESP_WIFI_COMMAND;
                                    strcpy(messageResponse[0].returnMessage, "scanning for wifi... ");
                                    sendResponse(message.msgID, message.msgFrom, RESPONSE, SYSTEM, message.msgValueCnt);
                                    
                                    messageResponse[0].responseType=EVENT_ACTION_BEGIN;
                                    sendResponse(message.msgID, message.msgFrom, EVENT, SYSTEM, message.msgValueCnt);                                    
                                    
                                    saveSenderOfMsgId(message.msgID, message.msgFrom);
                                    wifiRequestMessageID = message.msgID;
                                    
                                    wifiNetworkScan(&wifiScanDone, &sysConf.wifi);
                                    
                                }
                                
                                // wifilist (get configured network)
                                if(!strcmp(message.System.wifi.command.name, "list")){
                                    
                                    strcpy(messageResponse[0].SYSCMDresponse.wifi.command.name, "list");
                                    messageResponse[0].responseType = RESP_WIFI_COMMAND;
                                    strcpy(messageResponse[0].returnMessage, "Get wifi known list... ");
                                    sendResponse(message.msgID, message.msgFrom, RESPONSE, SYSTEM, message.msgValueCnt);
                                    
                                    messageResponse[0].responseType=EVENT_ACTION_BEGIN;
                                    sendResponse(message.msgID, message.msgFrom, EVENT, SYSTEM, message.msgValueCnt);                                    
                                    
                                    saveSenderOfMsgId(message.msgID, message.msgFrom);
                                    wifiRequestMessageID = message.msgID;
                                    
                                    wifiNetworkKnownList(&wifiListDone, &sysConf.wifi);
                                }                                
                                
                                if(!strcmp(message.System.wifi.command.name, "config")){
                                    messageResponse[0].SYSCMDresponse.wifi.command.index = message.System.wifi.command.index;
                                    strcpy(messageResponse[0].SYSCMDresponse.wifi.command.config.ssid, message.System.wifi.command.mode);
                                    strcpy(messageResponse[0].SYSCMDresponse.wifi.command.config.ssid, message.System.wifi.command.mode);
                                    strcpy(messageResponse[0].SYSCMDresponse.wifi.command.config.ssid, message.System.wifi.command.config.ssid);
                                    strcpy(messageResponse[0].SYSCMDresponse.wifi.command.config.key, message.System.wifi.command.config.key);
                                    strcpy(messageResponse[0].SYSCMDresponse.wifi.command.config.security, message.System.wifi.command.config.security);
                                    
                                    //char ssidError = wifiNetworkConfig(message.System.wifi.command.config.ssid, message.System.wifi.command.config.key);
                                    char ssidError = wifiNetworkConfig(message.System.wifi.command);
                                    
                                    if(ssidError){
                                        strcpy(messageResponse[0].returnMessage, "ERROR: SSID don't exit");                                        
                                        messageResponse[0].responseType = EVENT_ACTION_ABORT;
                                        sendResponse(message.msgID, message.msgFrom, EVENT, SYSTEM, message.msgValueCnt);
                                    
                                    }
                                    else{
                                        strcpy(messageResponse[0].returnMessage, "Configuring wifi...");
                                        // Retourne le message sur topic "EVENT"                                    
                                        messageResponse[0].responseType=EVENT_ACTION_BEGIN;
                                        sendResponse(message.msgID, message.msgFrom, EVENT, SYSTEM, 1);
                                    }

                                    messageResponse[0].responseType = RESP_WIFI_DATA;
                                    sendResponse(message.msgID, message.msgFrom, RESPONSE, SYSTEM, message.msgValueCnt);
                                }
                                
                                sprintf(reportBuffer, "Traitement de la commande système pour le message #%d\n", message.msgID);
                                printf(reportBuffer);                                                             // Affichage du message dans le shell
                                sendMqttReport(message.msgID, reportBuffer);				      // Envoie le message sur le canal MQTT "Report"                                
                                break;
		default : break;
	}
	return 0;
}

// -------------------------------------------------------------------
// PROCESSREQUEST
// S�l�ction et traite le param�tre de requete recu [DISTANCE, TENSION BATTERIE, ENTREE DIGITAL, etc...]
// -------------------------------------------------------------------
int processAlgoidRequest(void){
	switch(message.msgParam){
		case DISTANCE : makeDistanceRequest();					// Requete de distance
						break;

		case BATTERY :  makeBatteryRequest();					// Requete de tension batterie
						break;

		case DINPUT :	makeSensorsRequest();					// Requete d'�tat des entr�es digitale
						break;
                case BUTTON :	makeButtonRequest();					// Requete d'�tat des entr�es digitale type bouton
						break;

		case STATUS :	makeStatusRequest(RESPONSE);				// Requete d'�tat du systeme
						break;
        	case MOTORS :	makeMotorRequest();					// Requete commande moteur

                case COLORS :	makeRgbRequest();					// Requete commande moteur
                                                break;                            
                case CONFIG :	makeConfigRequest();					// Requete de la configuration actuelle
                                                break;                                                                            

		default : break;
	}
	return 0;
}


// -------------------------------------------------------------------
// runMotorAction
// Effectue une action avec les param�tre recus: MOTEUR, VELOCITE, ACCELERATION, TEMPS d'action
// -------------------------------------------------------------------
int runMotorAction(void){
	int ptrData;
	int myTaskId;
	unsigned char actionCount=0;
	int action=0;
        int i;
        int ID;

	// Comptabilise le nombre de param�tre (moteur) recu dans le message
	// 
        for(i=0;i<NBMOTOR;i++){
            ptrData = getWDvalue(i);
            if(ptrData>=0){
                actionCount++;
                        kehops.dcWheel[i].motor.userSpeedSetPoint = message.DCmotor[ptrData].userSetPoint;
                        
                        if(kehops.dcWheel[i].motor.userSpeedSetPoint < 0){
                            kehops.dcWheel[i].motor.direction = -1;
                            kehops.dcWheel[i].motor.userSpeedSetPoint *= -1;                    // Rétabli la consigne sous forme positive
                        }
                        else 
                            if(kehops.dcWheel[i].motor.userSpeedSetPoint == 0)
                                kehops.dcWheel[i].motor.direction = 0;
                            else
                                if(kehops.dcWheel[i].motor.userSpeedSetPoint > 0)
                                    kehops.dcWheel[i].motor.direction = 1;
                            
                        kehops.dcWheel[i].target.distanceCM = message.DCmotor[ptrData].cm;
                        kehops.dcWheel[i].target.time = message.DCmotor[ptrData].time;
            }
        }

        // Au moin une action � effectuer
        if(actionCount>0){
            
            // Retoure un message EVENT de type BEGIN 
            messageResponse[0].responseType = EVENT_ACTION_BEGIN;
            // Retourne un message event ALGOID 
            sendResponse(message.msgID, message.msgFrom,  EVENT, MOTORS, 1);
                    
            // Ouverture d'une t�che pour les toutes les actions du message algoid � effectuer
            // Recois un num�ro de tache en retour
            myTaskId=createBuggyTask(message.msgID, actionCount);			// 2 actions pour mouvement 2WD

            // D�marrage des actions
            if(myTaskId>0){
                    printf("Creation de tache MOTOR: #%d avec %d actions\n", myTaskId, actionCount);

                    // Sauvegarde du nom de l'emetteur et du ID du message pour la r�ponse
                    // en fin d'�venement
                    saveSenderOfMsgId(message.msgID, message.msgFrom);

                    for(ptrData=0; action < actionCount && ptrData<10; ptrData++){
                        ID = message.DCmotor[ptrData].motor;
                        if(ID >= 0){
                            
                            // Effectue l'action sur la roue
                            if(kehops.dcWheel[ID].target.distanceCM <= 0 && kehops.dcWheel[ID].target.time <= 0){
                                sprintf(reportBuffer, "ATTENTION: Action infinie, aucun parametre defini \"time\" ou \"cm\" pour l'action sur le moteur %d\n", ID);

                                printf(reportBuffer);                                                             // Affichage du message dans le shell
                                sendMqttReport(message.msgID, reportBuffer);				      // Envoie le message sur le canal MQTT "Report"     
                                setAsyncMotorAction(myTaskId, ID, kehops.dcWheel[ID].motor.userSpeedSetPoint, INFINITE, NULL);

                                // Défini l'état de laction comme "en cours" pour message de réponse
                                messageResponse[0].responseType = EVENT_ACTION_RUN;
                                // Retourne un message event ALGOID 
                                sendResponse(message.msgID, message.msgFrom,  EVENT, MOTORS, 1);
                            }else
                            {
                                if(kehops.dcWheel[ID].target.distanceCM > 0)
                                        setAsyncMotorAction(myTaskId, ID, kehops.dcWheel[ID].motor.userSpeedSetPoint, CENTIMETER, kehops.dcWheel[ID].target.distanceCM);
                                else{
                                        setAsyncMotorAction(myTaskId, ID, kehops.dcWheel[ID].motor.userSpeedSetPoint, MILLISECOND, kehops.dcWheel[ID].target.time);                                        
                                }
                            }
                        }
                        action++;
                    }
                    return 0;
            }
            else
                return 1;
        }
        // Aucun param�tre trouv� ou moteur inexistant
        else{
            
            messageResponse[0].responseType = EVENT_ACTION_ERROR;
            sendResponse(myTaskId, message.msgFrom, EVENT, MOTORS, 1);               // Envoie un message EVENT error
            sprintf(reportBuffer, "ERREUR: Aucun moteur defini ou inexistant pour le message #%d\n", message.msgID);
            printf(reportBuffer);                                                             // Affichage du message dans le shell
            sendMqttReport(message.msgID, reportBuffer);				      // Envoie le message sur le canal MQTT "Report"
        }
}

// -------------------------------------------------------------------
// runStepperAction
// Effectue une action avec les paramètre recus: MOTEUR, VELOCITE, PAS, ROTATION
// -------------------------------------------------------------------
int runStepperAction(void){
	int ptrData;
	int myTaskId;
	unsigned char actionCount=0;
	int action=0;
        int i;
        int ID;

	// Comptabilise le nombre de paramètre (moteur pas à pas) recu dans le message
	// 
        for(i=0;i<NBSTEPPER;i++){
            ptrData=getStepperValue(i);
            if(ptrData>=0){
                actionCount++;
                        kehops.stepperWheel[i].motor.userSpeedSetPoint = message.StepperMotor[ptrData].userSetPoint;
                        
                        if(kehops.stepperWheel[i].motor.userSpeedSetPoint < 0){
                            kehops.stepperWheel[i].motor.direction = -1;
                            kehops.stepperWheel[i].motor.userSpeedSetPoint *= -1;                    // Rétabli la consigne sous forme positive
                        }
                        else 
                            if(kehops.stepperWheel[i].motor.userSpeedSetPoint == 0)
                                kehops.stepperWheel[i].motor.direction = 0;
                            else
                                if(kehops.stepperWheel[i].motor.userSpeedSetPoint > 0)
                                    kehops.stepperWheel[i].motor.direction = 1;
                            
                        kehops.stepperWheel[i].target.time = message.StepperMotor[ptrData].time;
                        kehops.stepperWheel[i].target.steps = message.StepperMotor[ptrData].step;
                        kehops.stepperWheel[i].target.angle = message.StepperMotor[ptrData].angle;
                        kehops.stepperWheel[i].target.rotation = message.StepperMotor[ptrData].rotation;
            }
        }     
        
        // Au moin une action à effectuer
        if(actionCount>0){
            
            // Retoure un message EVENT de type BEGIN 
            messageResponse[0].responseType = EVENT_ACTION_BEGIN;
            // Retourne un message event ALGOID 
            sendResponse(message.msgID, message.msgFrom,  EVENT, STEPPER, 1);
                    
            // Ouverture d'une tâche pour les toutes les actions du message algoid � effectuer
            // Recois un numéro de tache en retour
            myTaskId=createBuggyTask(message.msgID, actionCount);			// 2 actions pour mouvement 2WD

            // Démarrage des actions
            if(myTaskId>0){
                    printf("Creation de tache STEPPER MOTOR: #%d avec %d actions\n", myTaskId, actionCount);

                    // Sauvegarde du nom de l'emetteur et du ID du message pour la r�ponse
                    // en fin d'�venement
                    saveSenderOfMsgId(message.msgID, message.msgFrom);

                    for(ptrData=0; action < actionCount && ptrData<10; ptrData++){
                        ID = message.StepperMotor[ptrData].motor;
                        if(ID >= 0){
                            // Effectue l'action sur le moteur pas à pas
                            if(kehops.stepperWheel[ID].target.time <= 0 && kehops.stepperWheel[ID].target.steps <=0 && kehops.stepperWheel[ID].target.rotation <= 0 && kehops.stepperWheel[ID].target.angle <=0){                                
                                sprintf(reportBuffer, "ATTENTION: Action infinie, aucun parametre defini \"time\" ou \"step\" ou \"rotation\" ou \"angle\"pour l'action sur le moteur pas à pas %d\n", ID);

                                printf(reportBuffer);                                                             // Affichage du message dans le shell
                                sendMqttReport(message.msgID, reportBuffer);				      // Envoie le message sur le canal MQTT "Report"     
                                setAsyncStepperAction(myTaskId, ID, kehops.stepperWheel[ID].motor.userSpeedSetPoint, INFINITE, NULL);

                                // Défini l'état de laction comme "en cours" pour message de réponse
                                messageResponse[0].responseType = EVENT_ACTION_RUN;
                                // Retourne un message event ALGOID 
                                sendResponse(message.msgID, message.msgFrom,  EVENT, STEPPER, 1);
                            }else
                            {
                                if(kehops.stepperWheel[ID].target.steps > 0){
                                    setAsyncStepperAction(myTaskId, ID, kehops.stepperWheel[ID].motor.userSpeedSetPoint, STEP, kehops.stepperWheel[ID].target.steps);
                                }
                                else{
                                    if(kehops.stepperWheel[ID].target.angle > 0){
                                       setAsyncStepperAction(myTaskId, ID, kehops.stepperWheel[ID].motor.userSpeedSetPoint, ANGLE, kehops.stepperWheel[ID].target.angle);
                                    }else
                                    {
                                        if(kehops.stepperWheel[ID].target.rotation > 0){
                                            setAsyncStepperAction(myTaskId, ID, kehops.stepperWheel[ID].motor.userSpeedSetPoint, ROTATION, kehops.stepperWheel[ID].target.rotation);
                                        }else{
                                            if(kehops.stepperWheel[ID].target.time > 0){
                                                setAsyncStepperAction(myTaskId, ID, kehops.stepperWheel[ID].motor.userSpeedSetPoint, MILLISECOND, kehops.stepperWheel[ID].target.time);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        action++;
                    }
                    return 0;
            }
            else
                return 1;
        }
        // Aucun param�tre trouv� ou moteur inexistant
        else{
            
            messageResponse[0].responseType = EVENT_ACTION_ERROR;
            sendResponse(myTaskId, message.msgFrom, EVENT, MOTORS, 1);               // Envoie un message EVENT error
            sprintf(reportBuffer, "ERREUR: Aucun moteur défini ou inexistant pour le message #%d\n", message.msgID);
            printf(reportBuffer);                                                             // Affichage du message dans le shell
            sendMqttReport(message.msgID, reportBuffer);				      // Envoie le message sur le canal MQTT "Report"
        }
}

// -------------------------------------------------------------------
// runLEDAction
//
// -------------------------------------------------------------------
int runLedAction(void){
	int ptrData;
	int myTaskId;
        int i;
        int ID;
        
        int time=-1;
        int power=0;
        int Count=-1;
        
	unsigned char actionCount=0;
	unsigned char action=0;

        // R�cup�re l'expediteur original du message ayant provoqu�
        // l'�venement
        char msgTo[32];
        
        // Recherche s'il y a des param�tres d�fini pour chaque LED
        // et mise � jour.   
        for(i=0;i<NBLED;i++){
            ptrData=getLedSetting(i);
            if(ptrData>=0){
                actionCount++;          // Incr�mente le nombre de param�tres trouv�s = action suppl�mentaire a effectuer
                
                // R�cup�ration de commande d'�tat de la led dans le message
                if(!strcmp(message.LEDarray[ptrData].state,"off"))
                    kehops.led[i].state = OFF;
                if(!strcmp(message.LEDarray[ptrData].state,"on"))
                    kehops.led[i].state = ON;
                if(!strcmp(message.LEDarray[ptrData].state,"blink"))
                    kehops.led[i].state = BLINK;
                
                // R�cup�ration des consignes dans le message (si disponible)
                if(message.LEDarray[ptrData].powerPercent > 0)
                    kehops.led[i].power = message.LEDarray[ptrData].powerPercent;
                
                if(message.LEDarray[ptrData].time > 0)
                    kehops.led[i].action.blinkTime = message.LEDarray[ptrData].time;
                
                if(message.LEDarray[ptrData].blinkCount > 0)
                    kehops.led[i].action.blinkCount = message.LEDarray[ptrData].blinkCount;
            }
        }

        // VERIFIE L'EXISTANCE DE PARAMETRE DE TYPE LED, CREATION DU NOMBRE D'ACTION ADEQUAT
        // 
        if(actionCount>0){
            // Ouverture d'une t�che pour les toutes les actions du message algoid � effectuer
            // Recois un num�ro de tache en retour
            myTaskId=createBuggyTask(message.msgID, actionCount);			//

            // D�marrage des actions
            if(myTaskId>0){
                    printf("Creation de tache LED: #%d avec %d actions\n", myTaskId, actionCount);

                    messageResponse[0].responseType=EVENT_ACTION_BEGIN;
                    sendResponse(myTaskId, message.msgFrom, EVENT, pLED, 1);                         // Envoie un message ALGOID de fin de t�che pour l'action �cras�
                    
                    // Sauvegarde du nom de l'emetteur et du ID du message pour la r�ponse
                    // en fin d'�venement
                    saveSenderOfMsgId(message.msgID, message.msgFrom);
                    
                    for(ptrData=0; action < actionCount && ptrData<10; ptrData++){
                            ID = message.LEDarray[ptrData].id;
                            if(ID >= 0){
                                    power=message.LEDarray[ptrData].powerPercent;
                                    Count=message.LEDarray[ptrData].blinkCount;
                                    time=message.LEDarray[ptrData].time;
                                    // Mode blink
                                    if(kehops.led[ID].state == BLINK){
                                        // Verifie la presence de parametres de type "time" et "count", sinon applique des
                                        // valeurs par defaut */ 
                                        if(time<=0 && Count<=0){
                                            time=500;
                                            Count=1;
                                            sprintf(reportBuffer, "ATTENTION: Action infinie, aucun parametre defini \"time\" ou \"count\" pour l'action sur la LED %d\n", ID);
                                            printf(reportBuffer);                                                             // Affichage du message dans le shell
                                            sendMqttReport(message.msgID, reportBuffer);	
                                            
                                            messageResponse[0].responseType=EVENT_ACTION_RUN;
                                            sendResponse(myTaskId, message.msgFrom, EVENT, pLED, 1);                         // Envoie un message ALGOID de fin de t�che pour l'action �cras�
                                        }

                                        if(Count<=0){
                                            Count=1;
                                            sprintf(reportBuffer, "ATTENTION: Action infinie, aucun parametre defini \"count\"  pour l'action sur la LED %d\n", ID);
                                            printf(reportBuffer);                                                             // Affichage du message dans le shell
                                            sendMqttReport(message.msgID, reportBuffer);				      // Envoie le message sur le canal MQTT "Report"     
                                        }
                                        
                                        // Creation d'un timer effectu� sans erreur, ni ecrasement d'une ancienne action
                                         setAsyncLedAction(myTaskId, ID, BLINK, time, Count);
                                     }

                                    // Mode on ou off
                                    else{
                                            if(kehops.led[ID].state == OFF)
                                                setAsyncLedAction(myTaskId, ID, OFF, NULL, NULL);

                                            if(kehops.led[ID].state == ON)
                                                setAsyncLedAction(myTaskId, ID, ON, NULL, NULL);
                                    }

                                    action++;
                            }
                    }
            }            
        }
        else{   
                sprintf(reportBuffer, "ERREUR: ID LED INEXISTANT pour le message #%d\n", message.msgID);
                messageResponse[0].responseType=EVENT_ACTION_ERROR;
                sendResponse(myTaskId, message.msgFrom, EVENT, pLED, 1);               // Envoie un message EVENT error
                printf(reportBuffer);                                                           // Affichage du message dans le shell
                sendMqttReport(message.msgID, reportBuffer);				// Envoie le message sur le canal MQTT "Report"
        }
	return 0;
}

// -------------------------------------------------------------------
// runPWMAction
//
// -------------------------------------------------------------------
int runPwmAction(void){
	int ptrData;
	int myTaskId;
        int i;
        int ID;
        
        int time=0;
        int power=0;
        int Count=0;
        
	unsigned char actionCount=0;
	unsigned char action=0;
        
        // R�cup�re l'expediteur original du message ayant provoqu�
        // l'�venement
        char msgTo[32];

        // Recherche s'il y a des param�tres d�fini pour chaque PWM
        // et mise � jour.   
        for(i=0;i<NBPWM;i++){
            ptrData=getPwmSetting(i);
            if(ptrData>=0){
                actionCount++;          // Incr�mente le nombre de param�tres trouv�s = action suppl�mentaire a effectuer
                
                // R�cup�ration de commande d'état pour la sortie PWM
                if(!strcmp(message.PWMarray[ptrData].state,"off"))
                    kehops.pwm[i].state = OFF;
                if(!strcmp(message.PWMarray[ptrData].state,"on"))
                    kehops.pwm[i].state = ON;
                if(!strcmp(message.PWMarray[ptrData].state,"blink"))
                    kehops.pwm[i].state = BLINK;
                
                // Blink mode not available in SERVO MODE (mode 1)
                if(!kehops.pwm[i].config.mode){
                    if(!strcmp(message.PWMarray[ptrData].state,"blink"))
                        kehops.pwm[i].state = BLINK;
                if(message.PWMarray[ptrData].time > 0)
                    kehops.pwm[i].action.blinkTime = message.PWMarray[ptrData].time;
                if(message.PWMarray[ptrData].blinkCount > 0)
                    kehops.pwm[i].action.blinkCount = message.PWMarray[ptrData].blinkCount;
                }
                
                
                
                // Recuperation des consignes dans le message (si disponible)
                if(message.PWMarray[ptrData].powerPercent >= 0)
                    kehops.pwm[i].power = message.PWMarray[ptrData].powerPercent;
            }
        }

        // VERIFIE L'EXISTANCE DE PARAMETRE DE TYPE PWM, CREATION DU NOMBRE D'ACTION ADEQUAT
        // 
        if(actionCount>0){
            // Ouverture d'une t�che pour les toutes les actions du message algoid � effectuer
            // Recois un num�ro de tache en retour
            myTaskId=createBuggyTask(message.msgID, actionCount);			//

            // D�marrage des actions
            if(myTaskId>0){
                    printf("Creation de tache PWM: #%d avec %d actions\n", myTaskId, actionCount);

                    // Sauvegarde du nom de l'emetteur et du ID du message pour la r�ponse
                    // en fin d'�venement
                    saveSenderOfMsgId(message.msgID, message.msgFrom);
                    
                    for(ptrData=0; action < actionCount && ptrData<10; ptrData++){
                            ID = message.PWMarray[ptrData].id;
                            if(ID >= 0){
                                    power=message.PWMarray[ptrData].powerPercent;
                                    Count=message.PWMarray[ptrData].blinkCount;
                                    time=message.PWMarray[ptrData].time;
                                    
                                    // Check if is a servomotor PWM (500uS .. 2.5mS)
                                    if(!kehops.pwm[ID].config.mode){
                                        // Mode blink
                                        if(kehops.pwm[ID].state== BLINK){
                                            // Verifie la presence de parametres de type "time" et "count", sinon applique des
                                            // valeurs par defaut
                                            if(time<=0){
                                                time=500;
                                                sprintf(reportBuffer, "ATTENTION: Action infinie, aucun parametre defini \"time\"  pour l'action PWM %d\n", ID);
                                                printf(reportBuffer);                                                             // Affichage du message dans le shell
                                                sendMqttReport(message.msgID, reportBuffer);	
                                            }

                                            if(Count<=0){
                                                sprintf(reportBuffer, "ATTENTION: Action infinie, aucun parametre defini \"count\"  pour l'action PWM %d\n", ID);
                                                printf(reportBuffer);                                                             // Affichage du message dans le shell
                                                sendMqttReport(message.msgID, reportBuffer);				      // Envoie le message sur le canal MQTT "Report"     
                                            }

                                            // Creation d'un timer effectu� sans erreur, ni ecrasement d'une ancienne action
                                             setAsyncPwmAction(myTaskId, ID, BLINK, time, Count);
                                        }
                                        else{
                                            if(kehops.pwm[ID].state == OFF)
                                                setAsyncPwmAction(myTaskId, ID, OFF, NULL, NULL);

                                            if(kehops.pwm[ID].state == ON)
                                                setAsyncPwmAction(myTaskId, ID, ON, NULL, NULL);
                                            }
                                    }
                                    else  
                                    {
                                            if(kehops.pwm[ID].state == OFF)
                                                setAsyncServoAction(myTaskId, ID, OFF, NULL);
                                            if(kehops.pwm[ID].state == ON)
                                                setAsyncServoAction(myTaskId, ID, ON, NULL);
                                    }
                                    
                                    action++;
                            }
                    }
                    messageResponse[0].responseType=EVENT_ACTION_BEGIN;
                    
                    if(!kehops.pwm[i].config.mode)
                        sendResponse(myTaskId, message.msgFrom, EVENT, pPWM, 1);               // Send EVENT message for action begin
                    else
                        sendResponse(myTaskId, message.msgFrom, EVENT, pSERVO, 1);             // Send EVENT message for action begin
            }            
        }
        else{   
                sprintf(reportBuffer, "ERREUR: ID PWM INEXISTANT pour le message #%d\n", message.msgID);
                messageResponse[0].responseType=EVENT_ACTION_ERROR;
                sendResponse(myTaskId, message.msgFrom, EVENT, pPWM, 1);               // Envoie un message EVENT error
                printf(reportBuffer);							// Affichage du message dans le shell
                sendMqttReport(message.msgID, reportBuffer);				// Envoie le message sur le canal MQTT "Report"
        }
	return 0;
}

// -------------------------------------------------------------------
// GETWDVALUE
// Recherche dans le message algoid, les param�tres
// [V�locit�, acceleration, sens de rotation et temps d'action] pour la roue sp�cifi�e
// Retourne un pointeur sur le champs de param�tre correspondant au moteur sp�cifi�
// -------------------------------------------------------------------
int getWDvalue(int wheelName){
	int i;
	int searchPtr = -1;

	// V�rifie que le moteur est existant...
		// Recherche dans les donn�e recues la valeur correspondante au param�tre "wheelName"
		for(i=0;i<message.msgValueCnt;i++){
			if(wheelName == message.DCmotor[i].motor)
				searchPtr=i;
		}
		return searchPtr;
}

// -------------------------------------------------------------------
// GETSTEPPERVALUE
// Recherche dans le message les param�tres
// Retourne un pointeur sur le champs de param�tre correspondant au moteur sp�cifi�
// -------------------------------------------------------------------
int getStepperValue(int motorName){
	int i;
	int searchPtr = -1;

	// V�rifie que le moteur est existant...
		// Recherche dans les donn�e recues la valeur correspondante au param�tre "wheelName"
		for(i=0;i<message.msgValueCnt;i++){
			if(motorName == message.StepperMotor[i].motor)
				searchPtr=i;
		}
		return searchPtr;
}

// -------------------------------------------------------------------
// GETPWMSETTING
// Recherche dans le message algoid, les param�tres
// pour une PWM sp�cifi�e
// -------------------------------------------------------------------
int getPwmSetting(int name){
	int i;
	int searchPtr = -1;

	// Recherche dans les donn�e recues la valeur correspondante au param�tre "wheelName"
	for(i=0;i<message.msgValueCnt;i++){
		if(name == message.PWMarray[i].id)
		searchPtr=i;
	}
	return searchPtr;
}

// -------------------------------------------------------------------
// GETLEDSETTING
// Recherche dans le message algoid, les param�tres
// pour une LED sp�cifi�e
// -------------------------------------------------------------------
int getLedSetting(int name){
	int i;
	int searchPtr = -1;

	// Recherche dans les donn�e recues la valeur correspondante au param�tre "name"
	for(i=0;i<message.msgValueCnt;i++){
		if(name == message.LEDarray[i].id)
		searchPtr=i;
	}
	return searchPtr;
}


// -------------------------------------------------------------------
// CREATBUGGYTASK Creation d'une tache avec le nombre
// d'actions � effectuer,
// - Retourne le num�ro d'action attribu�
// - Retourne 0 si table des taches pleine (Impossible de cr�er)
// - Retourne -1 si Message ID existe d�j�
// -------------------------------------------------------------------

int createBuggyTask(int MsgId, int actionCount){
	int i;
	int actionID, ptrSender;


	// d�fini un num�ro de tache al�atoire pour l'action � executer si pas de message id saisi
	if(MsgId == 0){
		actionID = rand() & 0xFFFFFF;
		MsgId = actionID;
	}
	else actionID = MsgId;

	// Recherche un emplacement libre dans la table d'action pour inserer les param�tre
	for(i=0;i<50;i++){
		if(ActionTable[i][TASK_NUMBER]==0){
			ActionTable[i][TASK_NUMBER]=actionID;
			ActionTable[i][ACTION_ALGOID_ID]= MsgId;
			ActionTable[i][ACTION_COUNT]=actionCount;
			return(actionID);
		}else{
			if(ActionTable[i][TASK_NUMBER]==actionID)
			{  
				sprintf(reportBuffer, "ERREUR: MessageID / Tache en cours de traitement: #%d\n", actionID);
                                printf(reportBuffer);
                                messageResponse[0].responseType=EVENT_ACTION_END;
                                ptrSender = getSenderFromMsgId(actionID);
                                sendResponse(actionID, msgEventHeader[ptrSender].msgFrom, RESPONSE, ERR_HEADER, 0);			// Envoie un message ALGOID de fin de t�che pour l'action �cras�
				sendMqttReport(actionID, reportBuffer);
				return -1;
                        }
		}
	}
	sprintf(reportBuffer, "ERREUR: Table de tâches pleine\n");
        printf(reportBuffer);
	sendMqttReport(actionID, reportBuffer);
	return(0);
}

// -------------------------------------------------------------------
// removeBuggyTask
// Mise � jour, soustrait l'action d'une tache
// - Retourne le MESSAGE ID correspondant � la tache si plus d'action � effectuer
// - Retourne 0 si actions restante
// - Retourne -1 si tache inexistante
// -------------------------------------------------------------------

int removeBuggyTask(int actionNumber){
	int i, algoidMsgId;

	// Recherche la tache correspondante dans la t�ble des action
	for(i=0;i<10;i++){
		if(ActionTable[i][TASK_NUMBER]==actionNumber){
			ActionTable[i][ACTION_COUNT]--;
			//printf("UPDATE ACTION %d  reste: %d\n", actionNumber, ActionTable[i][ACTION_COUNT]);
			if((ActionTable[i][ACTION_COUNT]) <=0){
				algoidMsgId=ActionTable[i][ACTION_ALGOID_ID];
				ActionTable[i][TASK_NUMBER]=0;				// Reset/Lib�re l'occupation de la t�che
				ActionTable[i][ACTION_ALGOID_ID]= 0;
				ActionTable[i][ACTION_COUNT]=0;
				return(algoidMsgId);					// Retourn le num�ro d'action termin�
			} else return 0;								// Action non termin�es
		}
	}
	return(-1);												// T�che inexistante
}


// -------------------------------------------------------------------
// MAKESTATUSREQUEST
// Traitement de la requete STATUS
// Envoie une message ALGOID de type "response" avec l'�tat des entr�es DIN, tension batterie, distance sonar, vitesse et distance des roues
// -------------------------------------------------------------------
int makeStatusRequest(int msgType){
	int i;
	int ptrData=0;

	message.msgValueCnt = NBDIN + NBBTN + NBMOTOR + NBSONAR + NBRGBC + NBLED + NBPWM + NBAIN +1 ; // Nombre de VALEUR � transmettre + 1 pour le SystemStatus
     
        // Preparation du message de reponse pour le status systeme
        strcpy(messageResponse[ptrData].SYSresponse.name, sysApp.info.name);
        messageResponse[ptrData].SYSresponse.startUpTime=sysApp.info.startUpTime;
        messageResponse[ptrData].SYSresponse.wan_online=sysApp.info.wan_online;
        messageResponse[ptrData].SYSresponse.rx_message=msg_stats.messageRX;
        messageResponse[ptrData].SYSresponse.tx_message=msg_stats.messageTX;
        
        
        char fv[10];
        sprintf(fv, "%d", getMcuFirmware());
        char hv[10];
        sprintf(hv, "%d", getMcuHWversion());
        
        strcpy(messageResponse[ptrData].SYSresponse.firmwareVersion,FIRMWARE_VERSION);
        strcpy(messageResponse[ptrData].SYSresponse.mcuVersion,fv);
        strcpy(messageResponse[ptrData].SYSresponse.HWrevision,hv);
        messageResponse[ptrData].SYSresponse.battVoltage = kehops.battery[0].measure.voltage_mV;
        messageResponse[ptrData].SYSresponse.battPercent = kehops.battery[0].measure.capacity;
        ptrData++;

	for(i=0;i<NBDIN;i++){
		messageResponse[ptrData].DINresponse.id=i;
                messageResponse[ptrData].value = kehops.proximity[i].measure.state;
                if(kehops.proximity[i].event.enable) strcpy(messageResponse[ptrData].DINresponse.event_state, "on");
                else strcpy(messageResponse[ptrData].DINresponse.event_state, "off");                
		ptrData++;
	}
                
        for(i=0;i<NBBTN;i++){
                messageResponse[ptrData].BTNresponse.id=i;
                messageResponse[ptrData].value = kehops.button[i].measure.state;
                
                if(kehops.button[i].event.enable) strcpy(messageResponse[ptrData].BTNresponse.event_state, "on");                
                else strcpy(messageResponse[ptrData].BTNresponse.event_state, "off");
                ptrData++;
	}

	for(i=0;i<NBMOTOR;i++){
		messageResponse[ptrData].MOTresponse.motor=i;
                messageResponse[ptrData].MOTresponse.speed=kehops.dcWheel[i].measure.rpm;
                messageResponse[ptrData].MOTresponse.cm = rpmToPercent(i, kehops.dcWheel[i].measure.rpm);
                // !!! RESPONSE VELOCITY TO CHECK...
                //messageResponse[ptrData].MOTresponse.userSetPoint = rpmToPercent(0,sysConfig.motor[0].minRPM) + robot.motor[i].userSetPoint;
                messageResponse[ptrData].MOTresponse.userSetPoint = kehops.dcWheel[i].motor.userSpeedSetPoint;
		ptrData++;
	}
        
        for(i=0;i<NBSONAR;i++){
                messageResponse[ptrData].DISTresponse.id=i;
                messageResponse[ptrData].value = kehops.sonar[i].measure.distance_cm;
                messageResponse[ptrData].DISTresponse.event_low = kehops.sonar[i].event.low;
                messageResponse[ptrData].DISTresponse.event_high = kehops.sonar[i].event.high;
                
                if(kehops.sonar[i].event.enable) strcpy(messageResponse[ptrData].DISTresponse.event_state, "on");
                else strcpy(messageResponse[ptrData].DISTresponse.event_state, "off");
                ptrData++;
	}

        for(i=0;i<NBRGBC;i++){
		messageResponse[ptrData].RGBresponse.id=i;
                messageResponse[ptrData].RGBresponse.red.value = kehops.rgb[i].color.red.measure.value;
                messageResponse[ptrData].RGBresponse.green.value = kehops.rgb[i].color.green.measure.value;
                messageResponse[ptrData].RGBresponse.blue.value = kehops.rgb[i].color.blue.measure.value;
                messageResponse[ptrData].RGBresponse.clear.value = kehops.rgb[i].color.clear.measure.value;
                
                if(kehops.rgb[i].config.event.enable) strcpy(messageResponse[ptrData].RGBresponse.event_state, "on");
                else strcpy(messageResponse[ptrData].RGBresponse.event_state, "off");
                
		ptrData++;
	}

        for(i=0;i<NBLED;i++){       
		messageResponse[ptrData].LEDresponse.id = i;
                messageResponse[ptrData].value = kehops.led[i].state;
                messageResponse[ptrData].LEDresponse.powerPercent = kehops.led[i].power;
		ptrData++;
	}
      
        
        for(i=0;i<NBPWM;i++){        
		messageResponse[ptrData].PWMresponse.id = i;
		messageResponse[ptrData].value = kehops.pwm[i].state;
                messageResponse[ptrData].PWMresponse.powerPercent = kehops.pwm[i].power;
		ptrData++;
	}
        
        for(i=0;i<NBAIN;i++){
                messageResponse[ptrData].BATTesponse.id=i;
                messageResponse[ptrData].value = kehops.battery[i].measure.voltage_mV;
                messageResponse[ptrData].BATTesponse.event_low = kehops.battery[i].event.low;
                messageResponse[ptrData].BATTesponse.event_high = kehops.battery[i].event.high;                
                if(kehops.battery[i].event.enable) strcpy(messageResponse[ptrData].BATTesponse.event_state, "on");
                else strcpy(messageResponse[ptrData].BATTesponse.event_state, "off");
                ptrData++;
	}
        
	// Envoie de la r�ponse MQTT
	sendResponse(message.msgID, message.msgFrom, msgType, STATUS, message.msgValueCnt);
	return (1);
}


// -------------------------------------------------------------------
// MAKESENSORREQUEST
// Traitement de la requete SENSORS
// Envoie une message ALGOID de type "response" avec l'�tat des entr�es DIN
// -------------------------------------------------------------------
int makeSensorsRequest(void){
	unsigned char i;

	// Pas de param�tres sp�cifi�s dans le message, retourne l'ensemble des �tats des DIN
	if(message.msgValueCnt==0){
		message.msgValueCnt=NBDIN;
		for(i=0;i<NBDIN;i++){
			messageResponse[i].DINresponse.id=i;
		}
	}else
		// ENREGISTREMENT DES NOUVEAUX PARAMETRES RECUS
		for(i=0;i<message.msgValueCnt; i++){
			messageResponse[i].DINresponse.id = message.DINsens[i].id;
			// Contr�le que le capteur soit pris en charge
			if(message.DINsens[i].id < NBDIN){
				// Recherche de param�tres suppl�mentaires et enregistrement des donn�e en "local"
                                if(!strcmp(message.DINsens[i].event_state, "on"))	kehops.proximity[message.DINsens[i].id].event.enable = 1; 			// Activation de l'envoie de messages sur �venements
				else if(!strcmp(message.DINsens[i].event_state, "off"))	kehops.proximity[message.DINsens[i].id].event.enable = 0;    // D�sactivation de l'envoie de messages sur �venements
			} else
				messageResponse[i].value = -1;
		};

	// RETOURNE EN REPONSE LES PARAMETRES ENREGISTRES ---
	for(i=0;i<message.msgValueCnt;i++){
		int temp = messageResponse[i].DINresponse.id;

		// Contr�le que le capteur soit pris en charge
		if(message.DINsens[i].id < NBDIN){
                        messageResponse[i].value = kehops.proximity[temp].measure.state;
			if(kehops.proximity[temp].event.enable) strcpy(messageResponse[i].DINresponse.event_state, "on");
				else strcpy(messageResponse[i].DINresponse.event_state, "off");
		} else
			messageResponse[i].value = -1;
	//---
	}
	// Envoie de la r�ponse MQTT
	sendResponse(message.msgID, message.msgFrom, RESPONSE, DINPUT, message.msgValueCnt);
	return (1);
}


// -------------------------------------------------------------------
// MAKEBUTTONREQUEST
// Traitement de la requete BOUTON
// Envoie une message ALGOID de type "response" avec l'�tat des entr�es DIN
// -------------------------------------------------------------------
int makeButtonRequest(void){
	unsigned char i;
        
	// Pas de param�tres sp�cifi�s dans le message, retourne l'ensemble des �tats des DIN
	if(message.msgValueCnt==0){
		message.msgValueCnt=NBBTN;
		for(i=0;i<NBBTN;i++){
			messageResponse[i].BTNresponse.id=i;
		}
	}else
		// ENREGISTREMENT DES NOUVEAUX PARAMETRES RECUS
		for(i=0;i<message.msgValueCnt; i++){
			messageResponse[i].BTNresponse.id = message.BTNsens[i].id;
			// Contr�le que le capteur soit pris en charge
			if(message.BTNsens[i].id < NBBTN){
				// Recherche de param�tres suppl�mentaires et enregistrement des donn�e en "local"
                                if(!strcmp(message.BTNsens[i].event_state, "on"))	kehops.button[message.BTNsens[i].id].event.enable = 1; 			// Activation de l'envoie de messages sur �venements
				else if(!strcmp(message.BTNsens[i].event_state, "off"))	kehops.button[message.BTNsens[i].id].event.enable = 0;    // D�sactivation de l'envoie de messages sur �venements
			} else
				messageResponse[i].value = -1;
		};

	// RETOURNE EN REPONSE LES PARAMETRES ENREGISTRES ---
	for(i=0;i<message.msgValueCnt;i++){
		int temp = messageResponse[i].BTNresponse.id;

		// Contr�le que le capteur soit pris en charge
		if(message.BTNsens[i].id < NBBTN){
                        messageResponse[i].value = kehops.button[temp].measure.state;
			if(kehops.button[temp].event.enable) strcpy(messageResponse[i].BTNresponse.event_state, "on");
                        else strcpy(messageResponse[i].BTNresponse.event_state, "off");
		} else
			messageResponse[i].value = -1;
	//---
	}
	// Envoie de la r�ponse MQTT
	sendResponse(message.msgID, message.msgFrom, RESPONSE, BUTTON, message.msgValueCnt);
	return (1);
}

// -------------------------------------------------------------------
// MAKEDISTANCEREQUEST
// Traitement de la requete de mesure de distance
// // R�cup�re les valeurs des param�tres "EVENT", "EVENT_HIGH", "EVENT_LOW", ANGLE
// Envoie un message ALGOID de type "response" avec la valeur distance mesur�e
// -------------------------------------------------------------------
int makeDistanceRequest(void){
	unsigned char i;

	// Pas de param�tres sp�cifi� dans le message, retourne l'ensemble des distances
	if(message.msgValueCnt==0){
		message.msgValueCnt=NBSONAR;
		for(i=0;i<NBSONAR;i++){
			messageResponse[i].DISTresponse.id=i;
		}
	}else
			// ENREGISTREMENT DES NOUVEAUX PARAMETRES RECUS
			for(i=0;i<message.msgValueCnt; i++){
				messageResponse[i].DISTresponse.id=message.DISTsens[i].id;

				if(message.DISTsens[i].id <NBSONAR){

					// Activation de l'envoie de messages sur �venements
					if(!strcmp(message.DISTsens[i].event_state, "on")){
                                            kehops.sonar[message.DISTsens[i].id].event.enable = 1;
                                            saveSenderOfMsgId(message.msgID, message.msgFrom);
					}
					else if(!strcmp(message.DISTsens[i].event_state, "off")){
                                            kehops.sonar[message.DISTsens[i].id].event.enable = 0;
                                            removeSenderOfMsgId(message.msgID);
					}

					// Evemenent haut
					if(message.DISTsens[i].event_high!=0)
                                            kehops.sonar[message.DISTsens[i].id].event.high = message.DISTsens[i].event_high;
					// Evemenent bas
					if(message.DISTsens[i].event_low!=0)
                                            kehops.sonar[message.DISTsens[i].id].event.low = message.DISTsens[i].event_low;
				} else
					messageResponse[i].value = -1;
			};

	for(i=0;i<message.msgValueCnt; i++){
		// RETOURNE EN REPONSE LES PARAMETRES ENREGISTRES
		// R�cup�ration des param�tres actuels et chargement du buffer de r�ponse
		int temp = messageResponse[i].DISTresponse.id;

		if(message.DISTsens[i].id <NBSONAR){
                        messageResponse[i].value=kehops.sonar[temp].measure.distance_cm;

			if(kehops.sonar[temp].event.enable)strcpy(messageResponse[i].DISTresponse.event_state, "on");
			else strcpy(messageResponse[i].DISTresponse.event_state, "off");
			messageResponse[i].DISTresponse.event_high = kehops.sonar[temp].event.high;
			messageResponse[i].DISTresponse.event_low = kehops.sonar[temp].event.low;
		} else
			messageResponse[i].value = -1;
	};

	// Envoie de la r�ponse MQTT
	sendResponse(message.msgID, message.msgFrom, RESPONSE, DISTANCE, message.msgValueCnt);

		return 1;
}

// -------------------------------------------------------------------
// MAKERGBREQUEST
// Traitement de la requete de mesure de couleur
// // R�cup�re les valeurs des param�tres "EVENT", "EVENT_HIGH", "EVENT_LOW", ANGLE
// Envoie un message ALGOID de type "response" avec les valeurs RGB mesur�es
// -------------------------------------------------------------------
int makeRgbRequest(void){
	unsigned char i;

	// Pas de param�tres sp�cifi� dans le message, retourne l'ensemble des capteur RGB
	if(message.msgValueCnt==0){
		message.msgValueCnt=NBRGBC;
		for(i=0;i<NBRGBC;i++){
			messageResponse[i].RGBresponse.id=i;
		}
	}else
			// ENREGISTREMENT DES NOUVEAUX PARAMETRES RECUS
			for(i=0;i<message.msgValueCnt; i++){
				messageResponse[i].RGBresponse.id=message.RGBsens[i].id;

				if(message.RGBsens[i].id <NBRGBC){

					// PARAMETRAGE DE L'ENVOIE DES MESSAGES SUR EVENEMENTS.
					if(!strcmp(message.RGBsens[i].event_state, "on")){
                                            kehops.rgb[message.RGBsens[i].id].config.event.enable = 1;
                                            saveSenderOfMsgId(message.msgID, message.msgFrom);
					}
					else if(!strcmp(message.RGBsens[i].event_state, "off")){
                                            kehops.rgb[message.RGBsens[i].id].config.event.enable = 0;
                                            removeSenderOfMsgId(message.msgID);
					}

                                        // Param�tre capteur ROUGE
					// Evemenent haut
					if(message.RGBsens[i].red.event_high!=0)
                                            kehops.rgb[message.RGBsens[i].id].color.red.event.high=message.RGBsens[i].red.event_high;
					// Evemenent bas
					if(message.RGBsens[i].red.event_low!=0)
                                            kehops.rgb[message.RGBsens[i].id].color.red.event.low=message.RGBsens[i].red.event_low;
                                        
                                        // Param�tre capteur VERT
                                        // Evemenent haut
					if(message.RGBsens[i].green.event_high!=0)
                                            kehops.rgb[message.RGBsens[i].id].color.green.event.high = message.RGBsens[i].green.event_high;
					// Evemenent bas
					if(message.RGBsens[i].green.event_low!=0)
                                            kehops.rgb[message.RGBsens[i].id].color.green.event.low=message.RGBsens[i].green.event_low;
                                        
                                        // Param�tre capteur BLEU
                                        // Evemenent haut
					if(message.RGBsens[i].blue.event_high!=0)
                                            kehops.rgb[message.RGBsens[i].id].color.blue.event.high=message.RGBsens[i].blue.event_high;
					// Evemenent bas
					if(message.RGBsens[i].blue.event_low!=0)
                                            kehops.rgb[message.RGBsens[i].id].color.blue.event.low=message.RGBsens[i].blue.event_low;

                                        // Param�tre capteur CLEAR
                                        // Evemenent haut
					if(message.RGBsens[i].clear.event_high!=0)
                                            kehops.rgb[message.RGBsens[i].id].color.clear.event.high=message.RGBsens[i].clear.event_high;
					// Evemenent bas
					if(message.RGBsens[i].clear.event_low!=0)
                                            kehops.rgb[message.RGBsens[i].id].color.clear.event.low = message.RGBsens[i].clear.event_low;
				} else
					messageResponse[i].value = -1;
			};

	for(i=0;i<message.msgValueCnt; i++){
		// RETOURNE EN REPONSE LES PARAMETRES ENREGISTRES
		// R�cup�ration des param�tres actuels et chargement du buffer de r�ponse
		int temp = messageResponse[i].RGBresponse.id;

		if(message.RGBsens[i].id <NBRGBC){
                        messageResponse[i].RGBresponse.red.value=kehops.rgb[temp].color.red.measure.value;
                        messageResponse[i].RGBresponse.green.value=kehops.rgb[temp].color.green.measure.value;
                        messageResponse[i].RGBresponse.blue.value=kehops.rgb[temp].color.blue.measure.value;
                        messageResponse[i].RGBresponse.clear.value=kehops.rgb[temp].color.clear.measure.value;

                        // Copie de l'etat de l'evenement
			if(kehops.rgb[i].config.event.enable)strcpy(messageResponse[i].RGBresponse.event_state, "on");
			else strcpy(messageResponse[i].RGBresponse.event_state, "off");
                        
                        // Copie des param�tres �venements haut/bas pour le ROUGE
                        messageResponse[i].RGBresponse.red.event_high=kehops.rgb[temp].color.red.event.high;
                        messageResponse[i].RGBresponse.red.event_low=kehops.rgb[temp].color.red.event.low;

                        // Copie des param�tres �venements haut/bas pour le VERT
                        messageResponse[i].RGBresponse.green.event_high=kehops.rgb[temp].color.green.event.high;
                        messageResponse[i].RGBresponse.green.event_low=kehops.rgb[temp].color.green.event.low;
                        
                        // Copie des param�tres �venements haut/bas pour le BLEU
                        messageResponse[i].RGBresponse.blue.event_high=kehops.rgb[temp].color.blue.event.high;
                        messageResponse[i].RGBresponse.blue.event_low=kehops.rgb[temp].color.blue.event.low;
                        
                        // Copie des param�tres �venements haut/bas pour le CLEAR
                        messageResponse[i].RGBresponse.clear.event_high=kehops.rgb[temp].color.clear.event.high;
                        messageResponse[i].RGBresponse.clear.event_low=kehops.rgb[temp].color.clear.event.low;
                        
                        
		} else
			messageResponse[i].value = -1;
	};

	// Envoie de la r�ponse MQTT
	sendResponse(message.msgID, message.msgFrom, RESPONSE, COLORS, message.msgValueCnt);

		return 1;
}

// -------------------------------------------------------------------
// MAKEBATTERYREQUEST
// Traitement de la requete de mesure de tension batterie
// R�cup�re les valeurs des param�tres "EVENT", "EVENT_HIGH", "EVENT_LOW"
// Envoie un message ALGOID de type "response" avec la valeur des param�tres enregistr�s
// -------------------------------------------------------------------

int makeBatteryRequest(void){
	unsigned char i;

	// Pas de param�tres sp�cifi� dans le message, retourne l'ensemble des �tats des batteries
	if(message.msgValueCnt==0){
		message.msgValueCnt=1;
		for(i=0;i<2;i++){
			messageResponse[i].BATTesponse.id=i;
		}
	}else
			for(i=0;i<message.msgValueCnt; i++){
				messageResponse[i].BATTesponse.id=message.BATTsens[i].id;

				if(message.BATTsens[i].id <NBAIN){
					// ENREGISTREMENT DES NOUVEAUX PARAMETRES RECUS
					// Recherche de param�tres suppl�mentaires
					// Evenement activ�es
					if(!strcmp(message.BATTsens[i].event_state, "on")){
                                                kehops.battery[message.BATTsens[i].id].event.enable = 1;
						saveSenderOfMsgId(message.msgID, message.msgFrom);
					}
					else if(!strcmp(message.BATTsens[i].event_state, "off")){
                                                kehops.battery[message.BATTsens[i].id].event.enable = 0;
						removeSenderOfMsgId(message.msgID);
					}
					// Evemenent haut
					if(message.BATTsens[i].event_high!=0) kehops.battery[message.BATTsens[i].id].event.high = message.BATTsens[i].event_high;
					if(message.BATTsens[i].event_low!=0) kehops.battery[message.BATTsens[i].id].event.low = message.BATTsens[i].event_low;
				}else
					messageResponse[i].value = -1;
			};

	for(i=0;i<message.msgValueCnt; i++){
		// RETOURNE EN REPONSE LES PARAMETRES ENREGISTRES
		int temp = messageResponse[i].BATTesponse.id;

		if(message.BATTsens[i].id <NBAIN){
                        messageResponse[i].value=kehops.battery[temp].measure.voltage_mV;                        

                        if(kehops.battery[temp].event.enable){
				strcpy(messageResponse[i].BATTesponse.event_state, "on");
				saveSenderOfMsgId(message.msgID, message.msgFrom);
			}
			else{
				strcpy(messageResponse[i].BATTesponse.event_state, "off");
				removeSenderOfMsgId(message.msgID);
			}
                        messageResponse[i].BATTesponse.event_high = kehops.battery[temp].event.high;
                        messageResponse[i].BATTesponse.event_low = kehops.battery[temp].event.low;
		} else
			messageResponse[i].value = -1;
	};
	// Envoie de la r�ponse MQTT
	sendResponse(message.msgID, message.msgFrom, RESPONSE, BATTERY, message.msgValueCnt);
		return 1;
}


// -------------------------------------------------------------------
// MAKEMOTORREQUEST
// Traitement de la requete SENSORS
// Envoie une message ALGOID de type "response" avec l'�tat des entr�es DIN
// -------------------------------------------------------------------
int makeMotorRequest(void){
	unsigned char i;

	// Pas de param�tres sp�cifi�s dans le message, retourne l'ensemble des �tats des moteurs
	if(message.msgValueCnt==0){
		message.msgValueCnt=NBMOTOR;
		for(i=0;i<NBMOTOR;i++){
			messageResponse[i].MOTresponse.motor=i;
		}
	}                

	// RETOURNE EN REPONSE LES PARAMETRES ENREGISTRES ---
	for(i=0;i<message.msgValueCnt;i++){
		int temp = messageResponse[i].MOTresponse.motor;

		// Contr�le que le moteur soit pris en charge
		if(message.DCmotor[i].motor < NBMOTOR){
                    
                        messageResponse[i].MOTresponse.userSetPoint = kehops.dcWheel[temp].motor.userSpeedSetPoint;
                        messageResponse[i].MOTresponse.cm = kehops.dcWheel[temp].target.distanceCM;
                        messageResponse[i].MOTresponse.time = kehops.dcWheel[temp].target.time;
                        messageResponse[i].responseType=RESP_STD_MESSAGE;
		} else
			messageResponse[i].MOTresponse.motor = -1;
	}
	// Envoie de la r�ponse MQTT
	sendResponse(message.msgID, message.msgFrom, RESPONSE, MOTORS, message.msgValueCnt);
	return (1);
}


// -------------------------------------------------------------------
// DISTANCEEVENTCHECK
// Contr�le si la distance mesur�e est hors de la plage d�fini par l'utilisateur
// et envoie un message de type "event" si tel est le cas.
// Un deuxi�me "event" est envoy� lorsque la mesure de distance entre � nouveau dans la
// plage d�finie.
// -------------------------------------------------------------------
void distanceEventCheck(void){
	static unsigned char distWarningSended[1];
	unsigned char i;
	// Contr�le periodique des mesures de distances pour envoie d'evenement
	for(i=0;i<NBSONAR;i++){
		// V�rification si envoie des EVENT activ�s
            if(kehops.sonar[i].event.enable){

                int event_low_disable, event_high_disable, distLowDetected, distHighDetected;

                // Contr�le l' individuelle des evenements ( = si valeur < 0)
                if(kehops.sonar[i].event.low < 0) event_low_disable = 1;
                else event_low_disable = 0;

                if(kehops.sonar[i].event.high < 0) event_high_disable = 1;
                else event_high_disable = 0;

                    // Detection des seuils d'alarme
                        if(kehops.sonar[i].measure.distance_cm < kehops.sonar[i].event.low) distLowDetected = 1;
			else distLowDetected = 0;

			if(kehops.sonar[i].measure.distance_cm > kehops.sonar[i].event.high) distHighDetected = 1;
			else distHighDetected = 0;

			// Evaluation des alarmes � envoyer
			if((distLowDetected && !event_low_disable) || (distHighDetected && !event_high_disable)){		// Mesure de distance hors plage
                            if(distWarningSended[i]==0){													// N'envoie l' event qu'une seule fois
                                messageResponse[i].DISTresponse.id=i;
                                messageResponse[i].value=kehops.sonar[i].measure.distance_cm;

                                if(kehops.sonar[i].event.enable) strcpy(messageResponse[i].DISTresponse.event_state, "on");
                                else strcpy(messageResponse[i].DISTresponse.event_state, "off");

                                sendResponse(message.msgID, message.msgFrom, EVENT, DISTANCE, NBSONAR);
                                distWarningSended[i]=1;

                                // Si evenement pour stream activ�, envoie une trame de type status
                                if(sysConf.communication.mqtt.stream.onEvent==1)
                                    makeStatusRequest(DATAFLOW);
                            }
			}
			else if (distWarningSended[i]==1){													// Mesure de distance revenu dans la plage
					messageResponse[i].DISTresponse.id=i;							// Et n'envoie qu'une seule fois le message
					messageResponse[i].value=kehops.sonar[i].measure.distance_cm;

                                        if(kehops.sonar[i].event.enable) strcpy(messageResponse[i].DISTresponse.event_state, "on");
                                        else strcpy(messageResponse[i].DISTresponse.event_state, "off");
                                        
					sendResponse(message.msgID, message.msgFrom, EVENT, DISTANCE, NBSONAR);
					distWarningSended[i]=0;
                                        
                                        // Si evenement pour stream activ�, envoie une trame de type status
                                        if(sysConf.communication.mqtt.stream.onEvent==1)
                                            makeStatusRequest(DATAFLOW); 
			}
		}
	}
}


// -------------------------------------------------------------------
// BATTERYEVENTCHECK
// Contr�le si la tension mesur�e est hors de la plage d�fini par l'utilisateur
// et envoie un message de type "event" si tel est le cas.
// Un deuxi�me "event" est envoy� lorsque la tension batterie entre � nouveau dans la
// plage d�finie.
// -------------------------------------------------------------------
// -------------------------------------------------------------------
void batteryEventCheck(void){
	static unsigned char battWarningSended[1];
	unsigned char i;
	// Contr�le periodique des mesures de tension batterie pour envoie d'evenement
	for(i=0;i<NBAIN;i++){
		if(kehops.battery[i].event.enable){

			int event_low_disable, event_high_disable, battLowDetected, battHighDetected;

			// Contr�le l' individuelle des evenements ( = si valeur < 0)
			if(kehops.battery[i].event.low < 0) event_low_disable = 1;
			else event_low_disable = 0;

			if(kehops.battery[i].event.high < 0) event_high_disable = 1;
			else event_high_disable = 0;

			// Detection des seuils d'alarme
			if(kehops.battery[i].measure.voltage_mV < kehops.battery[i].event.low) battLowDetected = 1;
			else battLowDetected = 0;

			if(kehops.battery[i].measure.voltage_mV > kehops.battery[i].event.high) battHighDetected = 1;
			else battHighDetected = 0;

			// Evaluation des alarmes � envoyer
			if((battLowDetected && !event_low_disable) || (battHighDetected && !event_high_disable)){				// Mesure tension hors plage
                            if(battWarningSended[i]==0){														// N'envoie qu'une seule fois l'EVENT
                                messageResponse[i].BATTesponse.id=i;
                                messageResponse[i].value = kehops.battery[i].measure.voltage_mV;
                                sendResponse(message.msgID, message.msgFrom, EVENT, BATTERY, 1);
                                battWarningSended[i]=1;

                                // Si evenement pour stream activ�, envoie une trame de type status
                                if(sysConf.communication.mqtt.stream.onEvent==1)
                                    makeStatusRequest(DATAFLOW);                                        
                            }
			}
			// Envoie un �venement Fin de niveau bas (+50mV Hysterese)
			else if (battWarningSended[i]==1 && kehops.battery[i].measure.voltage_mV > (kehops.battery[i].event.low + kehops.battery[i].event.hysteresis)){				// Mesure tension dans la plage
                                messageResponse[i].BATTesponse.id=i;											// n'envoie qu'une seule fois apr�s
                                messageResponse[i].value = kehops.battery[i].measure.voltage_mV;
                                // une hysterese de 50mV
                                sendResponse(message.msgID, message.msgFrom, EVENT, BATTERY, 1);
                                battWarningSended[i]=0;

                                // Si evenement pour stream activ�, envoie une trame de type status
                                if(sysConf.communication.mqtt.stream.onEvent==1)
                                    makeStatusRequest(DATAFLOW);                                        
			}
		}
	}
}


// -------------------------------------------------------------------
// DINEVENTCHECK
// V�rifie si une changement d'�tat � eu lieu sur les entr�es num�riques
// et envoie un event si tel est les cas.
// Seul les DIN ayant chang� d'�tat font partie du message de r�ponse
// -------------------------------------------------------------------
void DINEventCheck(void){
	// Mise � jour de l'�tat des E/S
	unsigned char ptrBuff=0, DINevent=0, oldDinValue[NBDIN], i;

	for(i=0;i<NBDIN;i++){
		// Mise � jour de l'�tat des E/S
		oldDinValue[i] = kehops.proximity[i].measure.state;
		kehops.proximity[i].measure.state = getDigitalInput(i);

		// V�rifie si un changement a eu lieu sur les entrees et transmet un message
		// "event" listant les modifications
		if(kehops.proximity[i].event.enable && (oldDinValue[i] != kehops.proximity[i].measure.state)){
			messageResponse[ptrBuff].DINresponse.id=i;
			messageResponse[ptrBuff].value = kehops.proximity[i].measure.state;

                        if(kehops.proximity[i].event.enable) strcpy(messageResponse[ptrBuff].DINresponse.event_state, "on");
                        else strcpy(messageResponse[ptrBuff].DINresponse.event_state, "off");     

			ptrBuff++;
			DINevent++;
		}
	}

	if(DINevent>0){
		sendResponse(message.msgID, message.msgFrom, EVENT, DINPUT, DINevent);
                
                // Si evenement pour stream activ�, envoie une trame de type status
                if(sysConf.communication.mqtt.stream.onEvent==1)
                    makeStatusRequest(DATAFLOW);
        }
        

}

// -------------------------------------------------------------------
// BUTTONEVENTCHECK
// V�rifie si une changement d'�tat � eu lieu sur les bouton
// et envoie un event si tel est les cas.
// Seul les DIN ayant change d'etat font partie du message de reponse
// -------------------------------------------------------------------

void BUTTONEventCheck(void){
    // Mise � jour de l'�tat des E/S
    unsigned char ptrBuff=0, BTNevent=0, oldBtnValue[NBBTN], i;

    for(i=0;i<NBBTN;i++){
        // Mise � jour de l'�tat des E/S
        oldBtnValue[i] = kehops.button [i].measure.state;
        kehops.button[i].measure.state = getDigitalInput(4+i);

        // V�rifie si un changement a eu lieu sur les entrees et transmet un message
        // "event" listant les modifications
        if(kehops.button [i].event.enable && (oldBtnValue[i] != kehops.button [i].measure.state)){
            messageResponse[ptrBuff].BTNresponse.id=i;
            messageResponse[ptrBuff].value = kehops.button [i].measure.state;

            if(kehops.button[i].event.enable) strcpy(messageResponse[ptrBuff].BTNresponse.event_state, "on");
            else strcpy(messageResponse[ptrBuff].BTNresponse.event_state, "off");

            ptrBuff++;
//			printf("CHANGEMENT BOUTON %d, ETAT:%d\n", i, robot.button[i].state);
            BTNevent++;
        }
    }

    if(BTNevent>0){
        sendResponse(message.msgID, message.msgFrom, EVENT, BUTTON, BTNevent);

        // Si evenement pour stream activ�, envoie une trame de type status
        if(sysConf.communication.mqtt.stream.onEvent == 1)
            makeStatusRequest(DATAFLOW);
    }
}


// -------------------------------------------------------------------
// COLOREVENTCHECK
// V�rifie si une changement d'�tat � eu lieu sur les entr�es num�riques
// -------------------------------------------------------------------
void COLOREventCheck(void){
        unsigned char ptrBuff=0, RGBevent=0;
        
	// Mise � jour de l'�tat des couleurs des capteur
	static unsigned char RGB_red_WarningSended[NBRGBC];
        static unsigned char RGB_green_WarningSended[NBRGBC];
        static unsigned char RGB_blue_WarningSended[NBRGBC];
        static unsigned char RGB_clear_WarningSended[NBRGBC];
        
	unsigned char i;

	for(i=0;i<NBRGBC;i++){
            if(kehops.rgb[i].config.event.enable){

                int red_event_low_disable, red_event_high_disable;                     
                int redLowDetected, redHighDetected;

                int green_event_low_disable, green_event_high_disable;                     
                int greenLowDetected, greenHighDetected;

                int blue_event_low_disable, blue_event_high_disable;                     
                int blueLowDetected, blueHighDetected;

                // Contr�le l' individuelle des evenements sur changement de couleur [ROUGE]
                if(kehops.rgb[i].color.red.event.low < 0) red_event_low_disable = 1;
                else red_event_low_disable = 0;

                if(kehops.rgb[i].color.red.event.high < 0) red_event_high_disable = 1;
                else red_event_high_disable = 0;

                // Detection des seuils d'alarme
                if(kehops.rgb[i].color.red.measure.value < kehops.rgb[i].color.red.event.low) redLowDetected = 1;
                else redLowDetected = 0;

                if(kehops.rgb[i].color.red.measure.value > kehops.rgb[i].color.red.event.high) redHighDetected = 1;
                else redHighDetected = 0;

                // Evaluation des alarmes � envoyer
                if((redLowDetected && !red_event_low_disable) || (redHighDetected && !red_event_high_disable)){				// Mesure tension hors plage
                    if(RGB_red_WarningSended[i]==0){														// N'envoie qu'une seule fois l'EVENT
                        messageResponse[ptrBuff].RGBresponse.id=i;
                        messageResponse[ptrBuff].RGBresponse.red.value = kehops.rgb[i].color.red.measure.value;
                        ptrBuff++;
                        RGBevent++;
                        //sendResponse(message.msgID, message.msgFrom, EVENT, COLORS, 1);
                        RGB_red_WarningSended[i]=1;

                        // Si evenement pour stream activ�, envoie une trame de type status
                        if(sysConf.communication.mqtt.stream.onEvent==1)
                            makeStatusRequest(DATAFLOW);
//                                        printf("CHANGEMENT ROUGE RGB %d, VALUE:%d\n", i, robot.rgb[i].red.value);
                    }
                }

                // Envoie un �venement Fin de niveau bas (+50mV Hysterese)
                else if (RGB_red_WarningSended[i]==1 && kehops.rgb[i].color.red.measure.value > (kehops.rgb[i].color.red.event.low + kehops.rgb[i].color.red.event.hysteresis)){				// Mesure tension dans la plage
                    messageResponse[ptrBuff].RGBresponse.id=i;											// n'envoie qu'une seule fois apr�s
                    messageResponse[ptrBuff].RGBresponse.red.value = kehops.rgb[i].color.red.measure.value;											// une hysterese de 50mV
                    ptrBuff++;
                    RGBevent++;
                    //sendResponse(message.msgID, message.msgFrom, EVENT, COLORS, 1);
                    RGB_red_WarningSended[i]=0;
                    // Si evenement pour stream activ�, envoie une trame de type status
                    if(sysConf.communication.mqtt.stream.onEvent==1)
                        makeStatusRequest(DATAFLOW);
//                                        printf("- CHANGEMENT ROUGE RGB %d, VALUE:%d\n", i, robot.rgb[i].red.value);
                }

                // Contr�le l' individuelle des evenements sur changement de couleur [VERT]
                if(kehops.rgb[i].color.green.event.low < 0) green_event_low_disable = 1;
                else green_event_low_disable = 0;

                if(kehops.rgb[i].color.green.event.high < 0) green_event_high_disable = 1;
                else green_event_high_disable = 0;

                // Detection des seuils d'alarme
                if(kehops.rgb[i].color.green.measure.value < kehops.rgb[i].color.green.event.low) greenLowDetected = 1;
                else greenLowDetected = 0;

                if(kehops.rgb[i].color.green.measure.value > kehops.rgb[i].color.green.event.high) greenHighDetected = 1;
                else greenHighDetected = 0;

                // Evaluation des alarmes � envoyer
                if((greenLowDetected && !green_event_low_disable) || (greenHighDetected && !green_event_high_disable)){				// Mesure tension hors plage
                    if(RGB_green_WarningSended[i]==0){														// N'envoie qu'une seule fois l'EVENT
                            messageResponse[ptrBuff].RGBresponse.id=i;
                            messageResponse[ptrBuff].RGBresponse.green.value = kehops.rgb[i].color.green.measure.value;
                            ptrBuff++;
                            RGBevent++;
                            //sendResponse(message.msgID, message.msgFrom, EVENT, COLORS, 1);
                            RGB_green_WarningSended[i]=1;

                            // Si evenement pour stream activ�, envoie une trame de type status
                            if(sysConf.communication.mqtt.stream.onEvent==1)
                                makeStatusRequest(DATAFLOW);
//                                        printf("CHANGEMENT VERT RGB %d, VALUE:%d\n", i, robot.rgb[i].green.value);
                    }
                }

                // Envoie un �venement Fin de niveau bas (+50mV Hysterese)
                else if (RGB_green_WarningSended[i]==1 && kehops.rgb[i].color.green.measure.value > (kehops.rgb[i].color.green.event.low + kehops.rgb[i].color.green.event.hysteresis)){				// Mesure tension dans la plage
                    messageResponse[ptrBuff].RGBresponse.id=i;											// n'envoie qu'une seule fois apr�s
                    messageResponse[ptrBuff].RGBresponse.green.value = kehops.rgb[i].color.green.measure.value;											// une hysterese de 50mV
                    ptrBuff++;
                    RGBevent++;
                    //sendResponse(message.msgID, message.msgFrom, EVENT, COLORS, 1);
                    RGB_green_WarningSended[i]=0;
                    // Si evenement pour stream activ�, envoie une trame de type status
                    if(sysConf.communication.mqtt.stream.onEvent==1)
                        makeStatusRequest(DATAFLOW);
//                                       printf("-CHANGEMENT VERT RGB %d, VALUE:%d\n", i, robot.rgb[i].green.value);
                }


                // Contr�le l' individuelle des evenements sur changement de couleur [BLEU]
                if(kehops.rgb[i].color.blue.event.low < 0) blue_event_low_disable = 1;
                else blue_event_low_disable = 0;

                if(kehops.rgb[i].color.blue.event.high < 0) blue_event_high_disable = 1;
                else blue_event_high_disable = 0;

                // Detection des seuils d'alarme
                if(kehops.rgb[i].color.blue.measure.value < kehops.rgb[i].color.blue.event.low) blueLowDetected = 1;
                else blueLowDetected = 0;

                if(kehops.rgb[i].color.blue.measure.value > kehops.rgb[i].color.blue.event.high) blueHighDetected = 1;
                else blueHighDetected = 0;

                // Evaluation des alarmes � envoyer
                if((blueLowDetected && !blue_event_low_disable) || (blueHighDetected && !blue_event_high_disable)){				// Mesure tension hors plage
                    if(RGB_blue_WarningSended[i]==0){														// N'envoie qu'une seule fois l'EVENT
                        messageResponse[ptrBuff].RGBresponse.id=i;
                        messageResponse[ptrBuff].RGBresponse.blue.value = kehops.rgb[i].color.blue.measure.value;
                        ptrBuff++;
                        RGBevent++;
                        //sendResponse(message.msgID, message.msgFrom, EVENT, COLORS, 1);
                        RGB_blue_WarningSended[i]=1;

                        // Si evenement pour stream activ�, envoie une trame de type status
                        if(sysConf.communication.mqtt.stream.onEvent==1)
                            makeStatusRequest(DATAFLOW);
//                                        printf("CHANGEMENT BLEU RGB %d, VALUE:%d\n", i, robot.rgb[i].blue.value);
                    }
                }

                // Envoie un �venement Fin de niveau bas (+50mV Hysterese)
                else if (RGB_blue_WarningSended[i]==1 && kehops.rgb[i].color.blue.measure.value > (kehops.rgb[i].color.blue.event.low + kehops.rgb[i].color.blue.event.hysteresis)){				// Mesure tension dans la plage
                    messageResponse[ptrBuff].RGBresponse.id=i;											// n'envoie qu'une seule fois apr�s
                    messageResponse[ptrBuff].RGBresponse.blue.value = kehops.rgb[i].color.blue.measure.value;											// une hysterese de 50mV
                    ptrBuff++;
                    RGBevent++;
                    //sendResponse(message.msgID, message.msgFrom, EVENT, COLORS, 1);
                    RGB_blue_WarningSended[i]=0;
                    // Si evenement pour stream activ�, envoie une trame de type status
                    if(sysConf.communication.mqtt.stream.onEvent==1)
                        makeStatusRequest(DATAFLOW);
//                                       printf("-CHANGEMENT BLEU RGB %d, VALUE:%d\n", i, robot.rgb[i].blue.value);
                }
            }
	}
        
        if(RGBevent>0){
            sendResponse(message.msgID, message.msgFrom, EVENT, COLORS, RGBevent);
                
            // Si evenement pour stream activ�, envoie une trame de type status
            if(sysConf.communication.mqtt.stream.onEvent==1)
                makeStatusRequest(DATAFLOW);
        }
 
}

int runUpdateCommand(int type){
    int status=0;
    int updateState=0;
    
    printf ("---------- Launching bash script ------------\n");
    
    if(type==0)
        status=system("sh /root/kehopsInstaller.sh check");
    
    if(type==1){
        sendMqttReport(message.msgID, "WARNING ! APPLICATION IS UPDATING AND WILL RESTART ");// Envoie le message sur le canal MQTT "Report"   
        usleep(500000);
        status=system("sh /root/kehopsInstaller.sh update");
    }
    
    updateState= WEXITSTATUS(status);
  
    printf ("---------- End of bash script ------------\n");
    printf ("Exit bash status: %d\n", updateState);
    
    char dbgMessage[100];
    sprintf(&dbgMessage[0], "Exit bash status: %d\n", updateState);	 // Formatage du message avec le Nom du client buggy
    sendMqttReport(message.msgID, dbgMessage);                        // Envoie le message sur le canal MQTT "Report"   

    return updateState;
}

void runRestartCommand(void){
    int status=0;
 
     printf ("---------- Launching bash script for restart ------------\n");

        sendMqttReport(message.msgID, "WARNING ! APPLICATION WILL RESTART ");// Envoie le message sur le canal MQTT "Report"   
        usleep(500000);
        status=system("sh /root/kehopsInstaller.sh restart");
    printf ("---------- End of bash script ------------\n");
}

void resetConfig(void){
    int i;
    	// Init robot membre
	for(i=0;i<NBAIN;i++){
            kehops.battery[i].event.enable = DEFAULT_EVENT_STATE;
            kehops.battery[i].event.high=65535;
            kehops.battery[i].event.low=0;
	}
    
	for(i=0;i<NBDIN;i++){
            kehops.proximity[i].event.enable = DEFAULT_EVENT_STATE;
	}

        for(i=0;i<NBBTN;i++){
            kehops.button[i].event.enable=DEFAULT_EVENT_STATE;
	}
    
        for(i=0;i<NBMOTOR;i++){
            kehops.dcWheel[i].config.motor.inverted = 0;
            kehops.dcWheel[i].target.distanceCM = 0;

            kehops.dcWheel[i].target.time = 0;
       
            kehops.dcWheel[i].config.rpmMin = 20;
            kehops.dcWheel[i].config.rpmMax = 200;
            kehops.dcWheel[i].config.pidReg.enable = 0;
            kehops.dcWheel[i].config.pidReg.Kp = 0.0;
            kehops.dcWheel[i].config.pidReg.Ki = 0.0;
            kehops.dcWheel[i].config.pidReg.Kd = 0.0;
	}  

        for(i=0;i<NBSTEPPER;i++){
            kehops.stepperWheel[i].config.motor.inverted = 0;
            kehops.stepperWheel[i].config.motor.ratio = 64;
            kehops.stepperWheel[i].config.motor.steps = 32;
            
            kehops.stepperWheel[i].target.angle = 0;
            kehops.stepperWheel[i].target.rotation = 0;
            kehops.stepperWheel[i].target.steps = 0;
            kehops.stepperWheel[i].target.time = 0;
	}

        for(i=0;i<NBSONAR;i++){
            kehops.sonar[i].event.enable = DEFAULT_EVENT_STATE;
            kehops.sonar[i].event.high = 100;
            kehops.sonar[i].event.low = 10;
            kehops.sonar[i].event.hysteresis = 0;
            kehops.sonar[i].measure.distance_cm = -1;
	}

        for(i=0;i<NBRGBC;i++){

            kehops.rgb[i].color.red.event.enable = DEFAULT_EVENT_STATE;
            kehops.rgb[i].color.green.event.enable = DEFAULT_EVENT_STATE;
            kehops.rgb[i].color.blue.event.enable = DEFAULT_EVENT_STATE;
            kehops.rgb[i].color.clear.event.enable = DEFAULT_EVENT_STATE;

            kehops.rgb[i].color.red.measure.value = -1;
            kehops.rgb[i].color.red.event.low = 0;
            kehops.rgb[i].color.red.event.high = 65535;

            kehops.rgb[i].color.green.measure.value = -1;
            kehops.rgb[i].color.green.event.low = 0;
            kehops.rgb[i].color.green.event.high = 65535;

            kehops.rgb[i].color.blue.measure.value = -1;
            kehops.rgb[i].color.blue.event.low = 0;
            kehops.rgb[i].color.blue.event.high = 65535;

            kehops.rgb[i].color.clear.measure.value = -1;
            kehops.rgb[i].color.clear.event.low = 0;
            kehops.rgb[i].color.clear.event.high = 65535;
	}

        // ------------ Initialisation de la configuration systeme
        
    
        // Initialisation configuration de flux de donn�es periodique
        sysConf.communication.mqtt.stream.state  = ON;
        sysConf.communication.mqtt.stream.time_ms = 500;
        sysApp.info.wan_online = 0;  
        
        strcpy(sysApp.info.name, "");
        strcpy(sysApp.info.group, "");
        
        // Load config data
        int configStatus = -1;
        configStatus = LoadConfig("kehops.cfg");
        if(configStatus<0){
            printf("#[CORE] Load configuration file from \"kehops.cfg\": ERROR\n");
        }else
            printf("#[CORE] Load configuration file from \"kehops.cfg\": OK\n");

        // Creation d'un id unique avec l'adresse mac si non defini au demarrage
	if(!strcmp(sysApp.info.name, ""))
            strcpy(&sysApp.info.name, getMACaddr());
        
        for(i=0;i<NBLED;i++){
            if(kehops.led[i].config.defaultState==1)
                setLedPower(i, kehops.led[i].config.defaultPower);
            else
                setLedPower(i, 0);
        }
        
        for(i=0;i<NBPWM;i++){
            if(kehops.pwm[i].config.defaultState==1)
                setPwmPower(i, kehops.pwm[i].config.defaultPower);
            else
                setPwmPower(i, 0);
        }
        
        sysApp.info.startUpTime = 0;
        sysApp.kehops.resetConfig = 0;
}

int getStartupArg(int count, char *arg[]){
    unsigned char i;
    
    for(i=0;i<count;i++){        
        if(!strcmp(arg[i], "-n"))
            sprintf(&sysApp.info.name, "%s", arg[i+1]);
        
        if(!strcmp(arg[i], "-a"))
            sprintf(&ADDRESS, "%s", arg[i+1]);
    }
}   

// Récupération de la liste des réseaux wifi detecté
// et envoie d'un message mqtt
void wifiSendScanResult(void){
    int i;
    
    printf("\n ..... FIN DE DETECTION WIFI, %d TROUVES.......\n", sysConf.wifi.wifiDetected);
    strcpy(messageResponse[0].SYSCMDresponse.wifi.command.name, "scan");
    // Retourne le message sur topic "EVENT"                                    
    messageResponse[0].responseType=EVENT_ACTION_END;
    sendResponse(message.msgID, message.msgFrom, EVENT, SYSTEM, 1);

    if(sysConf.wifi.wifiDetected>0){
        for(i=0;i<sysConf.wifi.wifiDetected;i++){
            printf("WIFI #%d    SSID: %s\n",i, sysConf.wifi.list[i].ssid);
            strcpy(messageResponse[0].SYSCMDresponse.wifi.scanResult.list[i].ssid, sysConf.wifi.list[i].ssid);
            strcpy(messageResponse[0].SYSCMDresponse.wifi.scanResult.list[i].encryption.enable, sysConf.wifi.list[i].encryption.enable);

            //for(j=0;j<sysConf.wifi.list[j].encryption.authCnt;j++)
            strcpy(messageResponse[0].SYSCMDresponse.wifi.scanResult.list[i].encryption.authentification[0].mode, sysConf.wifi.list[i].encryption.authentification[0].mode);
            //for(j=0;j<sysConf.wifi.list[j].encryption.wpaCnt;j++)
            strcpy(messageResponse[0].SYSCMDresponse.wifi.scanResult.list[i].encryption.wpa[0].type, sysConf.wifi.list[i].encryption.wpa[0].type);
        }
    }
    messageResponse[0].SYSCMDresponse.wifi.scanResult.wifiDetected = sysConf.wifi.wifiDetected;
    //getSenderFromMsgId(wifiRequestMessageID);
    char msg[100];
    sprintf(msg, "Scan result: %d hotspot detected", sysConf.wifi.wifiDetected);

    messageResponse[0].responseType = RESP_WIFI_SCAN;
    strcpy(messageResponse[0].returnMessage, msg);
    sendResponse(message.msgID, message.msgFrom, RESPONSE, SYSTEM, 1);                                    
}


void wifiSendNetworkList(void){
    int i;
    printf("\n ..... FIN DE RECUPERATION DES WIFI CONFIGURE, %d TROUVES.......\n", sysConf.wifi.wifiDetected);
    strcpy(messageResponse[0].SYSCMDresponse.wifi.command.name, "list");
    // Retourne le message sur topic "EVENT"                                    
    messageResponse[0].responseType=EVENT_ACTION_END;
    sendResponse(message.msgID, message.msgFrom, EVENT, SYSTEM, 1);

    if(sysConf.wifi.wifiDetected>0){
        for(i=0;i<sysConf.wifi.wifiDetected;i++){
            printf("WIFI #%d    SSID: %s   KEY: %s    SECURITY: %s   ACTIVE: %s\n",i, sysConf.wifi.list[i].ssid, sysConf.wifi.list[i].key, sysConf.wifi.list[i].encryption.authentification[0].mode, sysConf.wifi.list[i].active);
            strcpy(messageResponse[0].SYSCMDresponse.wifi.scanResult.list[i].ssid, sysConf.wifi.list[i].ssid);
            strcpy(messageResponse[0].SYSCMDresponse.wifi.scanResult.list[i].key, sysConf.wifi.list[i].key);
            strcpy(messageResponse[0].SYSCMDresponse.wifi.scanResult.list[i].active, sysConf.wifi.list[i].active);
            //for(j=0;j<sysConf.wifi.list[j].encryption.authCnt;j++)
            strcpy(messageResponse[0].SYSCMDresponse.wifi.scanResult.list[i].encryption.authentification[0].mode, sysConf.wifi.list[i].encryption.authentification[0].mode);
            //for(j=0;j<sysConf.wifi.list[j].encryption.wpaCnt;j++)
            //strcpy(messageResponse[0].SYSCMDresponse.wifi.scanResult.list[i].encryption.wpa[0].type, sysConf.wifi.list[i].encryption.wpa[0].type);
        }
    }
    messageResponse[0].SYSCMDresponse.wifi.scanResult.wifiDetected = sysConf.wifi.wifiDetected;
    //getSenderFromMsgId(wifiRequestMessageID);
    char msg[100];
    sprintf(msg, "Config result: %d network known", sysConf.wifi.wifiDetected);

    messageResponse[0].responseType = RESP_WIFI_NETWORK_LIST;
    strcpy(messageResponse[0].returnMessage, msg);
    sendResponse(message.msgID, message.msgFrom, RESPONSE, SYSTEM, 1);                                    
}

// -------------------------------------------------------------------
// MAKECONFIGREQUEST
// Récupère la configuration actuelle
// -------------------------------------------------------------------

int makeConfigRequest(void){   
    int i;
    int ptrData=0;
    
    // PREPARATION DU MESSAGE DE REPONSE POUR LA CONFIGURATION DE KEHOPS
    
    // Récupération du nom et du groupe
    strcpy(messageResponse[ptrData].CONFIGresponse.robot.name, sysApp.info.name);
    strcpy(messageResponse[ptrData].CONFIGresponse.robot.group, sysApp.info.group);
    
    messageResponse[ptrData].CONFIGresponse.stream.time = sysConf.communication.mqtt.stream.time_ms;      // Interval d'envoie de la stream en mode polling
    strcpy(messageResponse[ptrData].CONFIGresponse.broker.address, sysConf.communication.mqtt.broker.address);   // Adresse du broker
    if(sysConf.communication.mqtt.stream.state)
        strcpy(messageResponse[ptrData].CONFIGresponse.stream.state, "on");      // Etat d'activation de la stream
    else 
        strcpy(messageResponse[ptrData].CONFIGresponse.stream.state, "off");      // Etat d'activation de la stream
    
    if(sysConf.communication.mqtt.stream.onEvent)
        strcpy(messageResponse[ptrData].CONFIGresponse.stream.onEvent, "on");   // Envoie de la stream sur evenements
    else
        strcpy(messageResponse[ptrData].CONFIGresponse.stream.onEvent, "off");   // Envoie de la stream sur evenements
    
    
    // Récupération de la configuration des moteurs DC
    messageResponse[ptrData].CONFIGresponse.motValueCnt = NBMOTOR;
    for(i=0;i<NBMOTOR; i++){
        messageResponse[ptrData].CONFIGresponse.motor[i].id = i;
        
        // Inversion moteur
        if(kehops.dcWheel[i].config.motor.inverted)
            strcpy(messageResponse[ptrData].CONFIGresponse.motor[i].inverted,"on");
        else
            strcpy(messageResponse[ptrData].CONFIGresponse.motor[i].inverted,"off");

        // Puissance min de démarrage
        messageResponse[ptrData].CONFIGresponse.motor[i].minPWM = kehops.dcWheel[i].config.motor.powerMin;

        // RPM min et max
        messageResponse[ptrData].CONFIGresponse.motor[i].minRPM = kehops.dcWheel[i].config.rpmMin;
        messageResponse[ptrData].CONFIGresponse.motor[i].maxRPM = kehops.dcWheel[i].config.rpmMax;

        // Paramètre régulateur PID
        if(kehops.dcWheel[i].config.pidReg.enable)
            strcpy(messageResponse[ptrData].CONFIGresponse.motor[i].rpmRegulator.PIDstate, "on");
        else
            strcpy(messageResponse[ptrData].CONFIGresponse.motor[i].rpmRegulator.PIDstate, "off");
        
        messageResponse[ptrData].CONFIGresponse.motor[i].rpmRegulator.PID_Kp = kehops.dcWheel[i].config.pidReg.Kp;
        messageResponse[ptrData].CONFIGresponse.motor[i].rpmRegulator.PID_Ki = kehops.dcWheel[i].config.pidReg.Ki;
        messageResponse[ptrData].CONFIGresponse.motor[i].rpmRegulator.PID_Kd = kehops.dcWheel[i].config.pidReg.Kd;

        // Diamètre et encodeur (Pour le calcule de la vitesse et la distance)
        messageResponse[ptrData].CONFIGresponse.wheel[i].diameter = kehops.dcWheel[i].config.diameter;
        messageResponse[ptrData].CONFIGresponse.wheel[i].pulsesPerRot = kehops.dcWheel[i].config.pulsesPerRot;
    }
    
    // Récupération de la configuration des moteurs
    messageResponse[ptrData].CONFIGresponse.stepperValueCnt = NBSTEPPER;
    for(i=0;i<NBSTEPPER; i++){
        messageResponse[ptrData].CONFIGresponse.stepper[i].id = i;
        
        // Inversion moteur pas-à-pas
        if(kehops.stepperWheel[i].config.motor.inverted)
            strcpy(messageResponse[ptrData].CONFIGresponse.stepper[i].inverted,"on");
        else
            strcpy(messageResponse[ptrData].CONFIGresponse.stepper[i].inverted,"off");

        // Ratio du réducteur
        messageResponse[ptrData].CONFIGresponse.stepper[i].ratio = kehops.stepperWheel[i].config.motor.ratio;

        // Nombre de pas
        messageResponse[ptrData].CONFIGresponse.stepper[i].stepsPerRot = kehops.stepperWheel[i].config.motor.steps;
    }
    
    // Récupération de la config des LEDS
    messageResponse[ptrData].CONFIGresponse.ledValueCnt = NBLED;
    for(i=0;i<NBLED; i++){
        messageResponse[ptrData].CONFIGresponse.led[i].id = i;        
        messageResponse[ptrData].CONFIGresponse.led[i].power = kehops.led[i].config.defaultPower;        
        
        if(kehops.led[i].config.defaultState)
            strcpy(messageResponse[ptrData].CONFIGresponse.led[i].state, "on");
        else 
            strcpy(messageResponse[ptrData].CONFIGresponse.led[i].state, "off");
            
        if(kehops.led[i].config.mode)
            strcpy(messageResponse[ptrData].CONFIGresponse.led[i].isServoMode,"on");
        else
            strcpy(messageResponse[ptrData].CONFIGresponse.led[i].isServoMode,"off");
    }
    
    // Récupération de la config des PWM
    messageResponse[ptrData].CONFIGresponse.pwmValueCnt = NBPWM;
    for(i=0;i<NBPWM; i++){
        messageResponse[ptrData].CONFIGresponse.pwm[i].id = i;        
        messageResponse[ptrData].CONFIGresponse.pwm[i].power = kehops.pwm[i].config.defaultPower;        
        
        if(kehops.pwm[i].config.defaultState)
            strcpy(messageResponse[ptrData].CONFIGresponse.pwm[i].state, "on");
        else 
            strcpy(messageResponse[ptrData].CONFIGresponse.pwm[i].state, "off");
            
        if(kehops.pwm[i].config.mode)
            strcpy(messageResponse[ptrData].CONFIGresponse.pwm[i].isServoMode,"on");
        else
            strcpy(messageResponse[ptrData].CONFIGresponse.pwm[i].isServoMode,"off");
    }
    
        // Récupération de la config des DIN
    messageResponse[ptrData].CONFIGresponse.dinValueCnt = NBDIN;
    for(i=0;i<NBDIN; i++){
        messageResponse[ptrData].CONFIGresponse.din[i].id = i;        
        
        if(kehops.proximity[i].event.enable)
            strcpy(messageResponse[ptrData].CONFIGresponse.din[i].event_state, "on");
        else 
            strcpy(messageResponse[ptrData].CONFIGresponse.din[i].event_state, "off");
    }  
    
        // Récupération de la config des BOUTON
    messageResponse[ptrData].CONFIGresponse.btnValueCnt = NBBTN;
    for(i=0;i<NBBTN; i++){
        messageResponse[ptrData].CONFIGresponse.btn[i].id = i;        
        
        if(kehops.button[i].event.enable)
            strcpy(messageResponse[ptrData].CONFIGresponse.btn[i].event_state, "on");
        else 
            strcpy(messageResponse[ptrData].CONFIGresponse.btn[i].event_state, "off");
    }
    
    // Récupération de la config des SONAR
    messageResponse[ptrData].CONFIGresponse.sonarValueCnt = NBSONAR;
    for(i=0;i<NBSONAR; i++){
        messageResponse[ptrData].CONFIGresponse.sonar[i].id = i;        
        
        if(kehops.sonar[i].event.enable)
            strcpy(messageResponse[ptrData].CONFIGresponse.sonar[i].event_state, "on");
        else 
            strcpy(messageResponse[ptrData].CONFIGresponse.sonar[i].event_state, "off");
        
        messageResponse[ptrData].CONFIGresponse.sonar[i].event_low = kehops.sonar[i].event.low;
        messageResponse[ptrData].CONFIGresponse.sonar[i].event_high = kehops.sonar[i].event.high;
        messageResponse[ptrData].CONFIGresponse.sonar[i].event_hyst = kehops.sonar[i].event.hysteresis;
    }

    // Récupération de la config des BATTERIE
    messageResponse[ptrData].CONFIGresponse.sonarValueCnt = NBAIN;
    for(i=0;i<NBAIN; i++){
        messageResponse[ptrData].CONFIGresponse.battery[i].id = i;        
        
        if(kehops.battery[i].event.enable)
            strcpy(messageResponse[ptrData].CONFIGresponse.battery[i].event_state, "on");
        else 
            strcpy(messageResponse[ptrData].CONFIGresponse.battery[i].event_state, "off");
        
        messageResponse[ptrData].CONFIGresponse.battery[i].event_low = kehops.battery[i].event.low;
        messageResponse[ptrData].CONFIGresponse.battery[i].event_high = kehops.battery[i].event.high;
        messageResponse[ptrData].CONFIGresponse.battery[i].event_hyst = kehops.battery[i].event.hysteresis;
    }     
 
    // Envoie du message de réponse de la configuration
    messageResponse[ptrData].responseType = RESP_STD_MESSAGE;
    sendResponse(message.msgID, message.msgFrom, RESPONSE, CONFIG, 1);
    
    sprintf(reportBuffer, "Lecture de la configuration KEHOPS pour le message #%d\n", message.msgID);
    printf(reportBuffer);                                                             // Affichage du message dans le shell
    sendMqttReport(message.msgID, reportBuffer);				      // Envoie le message sur le canal MQTT "Report"
}