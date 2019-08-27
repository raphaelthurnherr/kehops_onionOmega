/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../buggy_descriptor.h"
#include "../timerManager.h"
#include "linux_json.h"
#include "../kehops_main.h"
#include "asyncTools.h"
#include "hwManager.h"
#include <math.h>
#include <../tools.h>

char reportBuffer[256];

int setAsyncMotorAction(int actionNumber, int motorNb, int usrSetpoint, char unit, int value);
int endWheelAction(int actionNumber, int motorNb);
int checkMotorEncoder(int actionNumber, int encoderName);
int dummyMotorAction(int actionNumber, int encoderName);

float rpmToPercent(int motorName, int rpm);
void checkDCmotorPower(void);				// Fonction temporaire pour rampe d'acceleration
//int motorSpeedSetpoint(int motorName, int ratio);  // Applique la consigne de vélocité pour un moteur donné

// -------------------------------------------------------------------
// SETASYNCMOTORACTION
// Effectue l'action sur une roue sp�cifi�e
// - D�marrage du timer avec definition de fonction call-back, et no d'action
// - D�marrage du mouvement de la roue sp�cifi�e
// - V�locit� entre -100 et +100 qui d�fini le sens de rotation du moteur
// -------------------------------------------------------------------

int setAsyncMotorAction(int actionNumber, int motorNb, int usrSetpoint, char unit, int value){
	int setTimerResult;
	int endOfTask;  
        


	// D�marre de timer d'action sur la roue et sp�cifie la fonction call back � appeler en time-out
	// Valeur en retour >0 signifie que l'action "en retour" � �t� �cras�e
	switch(unit){
		case  MILLISECOND:  setTimerResult=setTimer(value, &endWheelAction, actionNumber, motorNb, MOTOR); break;
		case  CENTIMETER:   //motorNb = getOrganNumber(motorNb);
                                    kehops.dcWheel[motorNb].data.startValue = getMotorPulses(motorNb) *( kehops.dcWheel[motorNb].data._MMPP / 10) ; // (/10 = Convert millimeter per pulse to centimeter per pulse)
                                    kehops.dcWheel[motorNb].data.stopValue = kehops.dcWheel[motorNb].data.startValue + value;
                                    setTimerResult=setTimer(50, &checkMotorEncoder, actionNumber, motorNb, MOTOR); break;// D�marre un timer pour contr�le de distance chaque 35mS
                                   
                case  INFINITE:     setTimerResult=setTimer(100, &dummyMotorAction, actionNumber, motorNb, MOTOR); break;
		default: printf("\n!!! ERROR Function [setAsyncMotorAction] -> unknown mode");break;
	}
        
	if(setTimerResult!=0){						// Timer pret, action effectuée ()
		if(setTimerResult>1){					// Le timer � �t� �cras� par la nouvelle action en retour car sur la m�me roue
			endOfTask=removeBuggyTask(setTimerResult);	// Supprime l'ancienne t�che qui � �t� �cras�e par la nouvelle action
			if(endOfTask){
				sprintf(reportBuffer, "Annulation des actions moteur pour la tache #%d\n", endOfTask);
                                
				// R�cup�re l'expediteur original du message ayant provoqu�
				// l'�venement
				char msgTo[32];
				int ptr=getSenderFromMsgId(endOfTask);
				strcpy(msgTo, msgEventHeader[ptr].msgFrom);
				// Lib�re la memorisation de l'expediteur
				removeSenderOfMsgId(endOfTask);

				messageResponse[0].responseType=EVENT_ACTION_ABORT;
				sendResponse(endOfTask, message.msgFrom, EVENT, MOTORS, 1);			// Envoie un message ALGOID de fin de t�che pour l'action �cras�
				printf(reportBuffer);									// Affichage du message dans le shell
				sendMqttReport(endOfTask, reportBuffer);                                                // Envoie le message sur le canal MQTT "Report"
			}
		}
                
		// Défini le "nouveau" sens de rotation à applique au moteur ainsi que la consigne de vitesse
		if(setMotorDirection(motorNb, kehops.dcWheel[motorNb].motor.direction)){                                                            // Sens de rotation
                            int powerOut= kehops.dcWheel[motorNb].config.motor.powerMin + ((float)(100-kehops.dcWheel[motorNb].config.motor.powerMin) /100)*kehops.dcWheel[motorNb].motor.userSpeedSetPoint;
                        ///setMotorSpeed(motorNb, kehops.dcWheel[motorNb].motor.userSpeedSetPoint);
                        printf("Powerout: %d \n", powerOut);
                        setMotorSpeed(motorNb, powerOut);


			// Envoie de message ALGOID et SHELL
			sprintf(reportBuffer, "Start wheel %d with power %d for time %d\n", motorNb, kehops.dcWheel[motorNb].motor.userSpeedSetPoint, value);
			printf(reportBuffer);
			sendMqttReport(actionNumber, reportBuffer);
		}
		else{
			sprintf(reportBuffer, "Error, impossible to start wheel %d\n",motorNb);
			printf(reportBuffer);
			sendMqttReport(actionNumber, reportBuffer);
		}

	}
	else printf("Error, Impossible to set timer wheel\n");
	return 0;
}

// -------------------------------------------------------------------
// END2WDACTION
// Fin de l'action sur une roue
// Fonction appel�e apr�s le timout d�fini par l'utilisateur, Stop le moteur sp�cifi�
// -------------------------------------------------------------------
int endWheelAction(int actionNumber, int motorNb){
	int endOfTask;
	//printf("Action number: %d - End of timer for wheel No: %d\n",actionNumber , motorNb);

	// Stop le moteur
	setMotorSpeed(motorNb, 0);
        //motorSpeedSetpoint(motorNb, 0);
        kehops.dcWheel[motorNb].motor.userSpeedSetPoint = 0;
        kehops.dcWheel[motorNb].motor.direction = BUGGY_STOP;
        
	// Retire l'action de la table et v�rification si toute les actions sont effectu�es
	// Pour la t�che en cours donn�e par le message ALGOID

	endOfTask = removeBuggyTask(actionNumber);

	// Contr�le que toutes les actions ont �t� effectu�e pour la commande recue dans le message ALGOID
	if(endOfTask){
		// R�cup�re l'expediteur original du message ayant provoqu�
		// l'�venement
		char msgTo[32];
		int ptr=getSenderFromMsgId(endOfTask);
		strcpy(msgTo, msgEventHeader[ptr].msgFrom);
		// Lib�re la memorisation de l'expediteur
		removeSenderOfMsgId(endOfTask);

		messageResponse[0].responseType=EVENT_ACTION_END;

		sendResponse(endOfTask, msgTo, EVENT, MOTORS, 1);
		sprintf(reportBuffer, "FIN DES ACTIONS \"WHEEL\" pour la tache #%d\n", endOfTask);
		printf(reportBuffer);
		sendMqttReport(endOfTask, reportBuffer);
	}

	return 0;
}


// ----------------------------------------------------------------------
// CHECKMOTORENCODER
// Contr�le la distance parcourue et stop la roue si destination atteinte
// Fonction appel�e apr�s le timout d�fini par l'utilisateur.
// -----------------------------------------------------------------------

int checkMotorEncoder(int actionNumber, int encoderName){
	float distance;					// Variable de distance parcourue depuis le start
        
	distance = getMotorPulses(encoderName);

	if(distance >=0){
            distance = distance * (kehops.dcWheel[encoderName].data._MMPP / 10);
            //usleep(1000);
	}else  printf("\n ERROR: I2CBUS READ\n");
	//printf("\n Encodeur #%d -> START %.2f cm  STOP %.2f cm", encoderNumber, startEncoderValue[encoderNumber], stopEncoderValue[encoderNumber]);

	if(distance >= kehops.dcWheel[encoderName].data.stopValue){
		endWheelAction(actionNumber, encoderName);
        }
	else{
		setTimer(50, &checkMotorEncoder, actionNumber, encoderName, MOTOR);
        }

	return 0;
}

int dummyMotorAction(int actionNumber, int encoderName){
        setTimer(0, &dummyMotorAction, actionNumber, encoderName, MOTOR);
    return 0;
}



// ----------------------------------------------------------------------
// RPMToPercent
// Redefini l'echelle donnée en % en une échelle utilisable
// selon les caractéristique du motor (par ex. PWM minimum pour démarrage moteur)
// donnés dans le fichier de configuration
// -----------------------------------------------------------------------

float rpmToPercent(int motorName, int rpm){
        float RPMpercent = 0;                 // % minimum pour fonctionnement du moteur 
        int newRatio;
        
        RPMpercent = (((rpm * 100) / (float)(kehops.dcWheel[motorName].config.rpmMax-kehops.dcWheel[motorName].config.rpmMin)))-kehops.dcWheel[motorName].config.rpmMin;
           
        return RPMpercent;
}

// ------------------------------------------------------------------------------------
// CHECKDCMOTORPOWER:
// Fonction appel�e periodiquement pour la gestion de l'acceleration
// D�cel�ration du moteur.
// Elle va augmenter ou diminuer la velocite du moteur jusqu'a atteindre la consigne
// ------------------------------------------------------------------------------------
void checkDCmotorPower(void){
        static float oldSetpoint;
	unsigned char i;
        float userSetpoint;
        float normalizeSetpoint;
        float pidSetpoint;
        float actualRpmInPercent;
        int fixedSetpoint;
        float newSetpoint;
        
	//unsigned char PowerToSet;

	// Contr�le successivement la puissance sur chaque moteur et effectue une rampe d'acc�l�ration ou d�c�leration
	for(i=0;i<MAXMOTOR;i++){
            
            // Converti la consigne donnée en % en consigne  CM/SEC
            
            userSetpoint=(float)(kehops.dcWheel[i].motor.userSpeedSetPoint);
            
            //actualRpmInPercent = rpmToPercent(i, robot.motor[i].speed_rpm);
            actualRpmInPercent = rpmToPercent(i, kehops.dcWheel[i].measure.rpm);
            
            if(kehops.dcWheel[i].motor.userSpeedSetPoint <= 0){   
                //setMotorSpeed(i, 0);
            }else{
                
                if(kehops.dcWheel[i].config.pidReg.enable > 0){
                //normalizeSetpoint = sysConfig.motor[0].minRPM + userSetpoint + ((float)(sysConfig.motor[0].maxRPM - sysConfig.motor[0].minRPM)/100);
                normalizeSetpoint = rpmToPercent(i,kehops.dcWheel[i].config.rpmMin) + userSetpoint;
                                
                //printf("\nnormalizeSetpoint: %.2f", normalizeSetpoint);
                    pidSetpoint = PID_speedControl(i, actualRpmInPercent, normalizeSetpoint);
                    
                    //if(pidSetpoint < sysConfig.motor[i].minPWM)
                    if(pidSetpoint < kehops.dcWheel[i].config.motor.powerMin)
                        pidSetpoint = kehops.dcWheel[i].config.motor.powerMin;
                    newSetpoint = pidSetpoint;  
              
                   
                    //Ajoute 30% de consigne pour le démarrage moteur si RPM trop bas (20% < RPMmin)
                    if(kehops.dcWheel[i].measure.rpm < kehops.dcWheel[i].config.rpmMin - (kehops.dcWheel[i].config.rpmMin / 100 * 50)){
                        newSetpoint += ((float)kehops.dcWheel[i].config.motor.powerMin / 100) * 25;
                        printf("\n !!!!!!! KICK START !!!!!\n");
                    }

                    if((newSetpoint != oldSetpoint)){
                        setMotorSpeed(i, newSetpoint); 

                    }

                    printf("\n* MOTOR #%d  USER setpoint [pc]: %.2f - Actual RPM [pc] : %.2f - New SETPOINT [pc]: %.2f\n",i, normalizeSetpoint, actualRpmInPercent, newSetpoint);

                    oldSetpoint = newSetpoint;                    
                }               

            }

            //printf("\n--- MOTOR #%d  ACTUAL RPM: %.1f  ACTUAL RPM [percent]: %.1f   USER SETPOINT: %.1f\n",0 , robot.motor[0].speed_rpm, actualSpeedPercent, userSetpoint);
            //pidSetpoint = PID_speedControl(0, actualSpeedPercent, robot.motor[0].velocity);           
            //setpoint = sysConfig.motor[0].minRPM + RPMToPercent(0, setpoint);
	}
}

/*
// ---------------------------------------------------------------------------
// motorSpeedSetpoint
// Applique la consigne de v�locit� pour un moteur donn�
// Cette consigne n'est pas appliqu�e directement sur les moteur mais sera progressivement
// approchée par le gestionnaire d'acceleration.
// ---------------------------------------------------------------------------
int motorSpeedSetpoint(int motorName, int ratio){
	if(motorName >= 0)
		//motorDCtargetPower[motorName]=ratio;
	else
		printf("\n function [motorSpeedSetpoint] : undefine motor #%d", motorName);
        
        return 0;
}

*/

 