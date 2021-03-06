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
#include "../hwControl/hwManager.h"


char reportBuffer[256];

int setAsyncPwmAction(int actionNumber, int pwmName, int mode, int time, int count);
int checkBlinkPwmCount(int actionNumber, int pwmName);
int endPwmAction(int actionNumber, int pwmNumber);

// -------------------------------------------------------------------
// SETASYNCPWMACTION
// Effectue l'action de clignotement
// - D�marrage du timer avec definition de fonction call-back, et no d'action
// - D�marrage du clignotement
// - vitesse de clignotement en mS
// -------------------------------------------------------------------

int setAsyncPwmAction(int actionNumber, int pwmName, int mode, int time, int count){
	int setTimerResult;
	int endOfTask;
        
	// D�marre un timer d'action sur le PWM et sp�cifie la fonction call back � appeler en time-out
	// Valeur en retour >0 signifie que l'action "en retour" � �t� �cras�e
        if(mode==BLINK){
            setTimerResult=setTimer(time, &checkBlinkPwmCount, actionNumber, pwmName, PWM);
        }
        else{
            if(mode==ON)
                setPwmPower(pwmName, kehops.pwm[pwmName].power); 
            else
                if(mode==OFF)
                    setPwmPower(pwmName, 0);
            // Utilise un delais de 5ms sinon message "Begin" arrive apres
            setTimerResult=setTimer(5, &checkBlinkPwmCount, actionNumber, pwmName, PWM);     // Consid�re un blink infini  
        }
        
	if(setTimerResult!=0){                                          // Timer pret, action effectu�e
		if(setTimerResult>1){					// Le timer � �t� �cras� par la nouvelle action en retour car sur le meme peripherique
			endOfTask=removeBuggyTask(setTimerResult);	// Supprime l'ancienne t�che qui � �t� �cras�e par la nouvelle action
                        if(endOfTask){
                                sprintf(reportBuffer, "Annulation des actions PWM pour la tache #%d\n", setTimerResult);

                                // Recupere l'expediteur original du message ayant provoque
                                // l'evenement
                                char msgTo[32];
                                int ptr=getSenderFromMsgId(endOfTask);
                                strcpy(msgTo, msgEventHeader[ptr].msgFrom);
                                // Libere la memorisation de l'expediteur
                                removeSenderOfMsgId(endOfTask);
                                
                                messageResponse[0].responseType=EVENT_ACTION_ABORT;
                                sendResponse(endOfTask, message.msgFrom, EVENT, pPWM, 1);		// Envoie un message ALGOID de fin de t�che pour l'action �cras�
                                printf(reportBuffer);                                                   // Affichage du message dans le shell
                                sendMqttReport(endOfTask, reportBuffer);				// Envoie le message sur le canal MQTT "Report"
                        }
		}
                return 0;
	}
	else {
            printf("Error, Impossible to set timer pwm\n");
            return -1;
        }
}

// ----------------------------------------------------------------------
// CHECKBLINKPWMCOUNT
// CONTROLE LE NOMBRE DE CLIGNOTEMENT SUR LA SORTIE PWM
// Fonction appel�e apr�s le timout d�fini par l'utilisateur.
// -----------------------------------------------------------------------

int checkBlinkPwmCount(int actionNumber, int pwmName){
	static int blinkCount=0;     // Variable de comptage du nombre de clignotements       
        static int PWMtoggleState[MAXPWM];
         
        // Si mode blink actif, toggle sur PWM et comptage
        if(kehops.pwm[pwmName].state == BLINK){
            
            // Performe the PWM toggle
            if(PWMtoggleState[pwmName]>0){
                setPwmPower(pwmName, 0);
                PWMtoggleState[pwmName]=0;
            }else
            {
                setPwmPower(pwmName, kehops.pwm[pwmName].power);
                PWMtoggleState[pwmName]=1;
            }
           
            // Consigned de clignotement atteinte ?
            if(blinkCount >= kehops.pwm[pwmName].action.blinkCount-1){
                kehops.pwm[pwmName].state = PWMtoggleState[pwmName];      // Update the actual state of pPWM
                endPwmAction(actionNumber, pwmName);
                blinkCount=0;                                   // Reset le compteur
            }
            else{
                    setTimer(kehops.pwm[pwmName].action.blinkTime, &checkBlinkPwmCount, actionNumber, pwmName, PWM);                    
                    blinkCount++;
            }
        }
        else{
            // Termine l'action unique (on/off)
            endPwmAction(actionNumber, pwmName);
            blinkCount=0;
        }
    
	return 0;
}

// -------------------------------------------------------------------
// ENDPWMACTION
// Fin de l'action de clignotement
// Fonction appel�e apr�s le timout d�fini par l'utilisateur, Stop le clignotement
// -------------------------------------------------------------------
int endPwmAction(int actionNumber, int pwmNumber){
	int endOfTask;

	// Retire l'action de la table et v�rification si toute les actions sont effectu�es
	// Pour la t�che en cours donn�e par le message ALGOID

        endOfTask=removeBuggyTask(actionNumber);
        if(endOfTask){
                sprintf(reportBuffer, "FIN DES ACTIONS PWM pour la tache #%d\n", endOfTask);

                // R�cup�re l'expediteur original du message ayant provoqu�
                // l'�venement
                char msgTo[32];
                int ptr=getSenderFromMsgId(endOfTask);
                strcpy(msgTo, msgEventHeader[ptr].msgFrom);
                // Lib�re la memorisation de l'expediteur
                removeSenderOfMsgId(endOfTask);
                messageResponse[0].responseType=EVENT_ACTION_END;
                sendResponse(endOfTask, msgTo, EVENT, pPWM, 1);			// Envoie un message ALGOID de fin de t�che pour l'action �cras�
                printf(reportBuffer);									// Affichage du message dans le shell
                sendMqttReport(endOfTask, reportBuffer);				// Envoie le message sur le canal MQTT "Report"
        }

	return 0;
}
 