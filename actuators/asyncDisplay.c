/**
 * \file asyncDisplay.c
 * \brief run asnchronous action for display
 * 
 * \author Raphael Thurnherr
 * \version 0.1
 * \date 13.05.2019
 *
 * Library to setup and drive the 12 bit ADC converter ADS111x 
 * 
 */

#include "asyncDisplay.h"
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

int setAsyncDisplayAction(int actionNumber, int displayName, int value);
int endDisplayAction(int actionNumber, int displayName);

/**
 * \brief Set an Display action to the timer
 * \param int actionNumber: action number (msg ID) to set in the timer for action identification
 * \param int displayName: The name of the display define in the config file (kehops.cfg)
 * \param int value: Value to put on the output
 * \return code error
 */

int setAsyncDisplayAction(int actionNumber, int displayName, int value){
	int setTimerResult;
	int endOfTask;
        
	// D�marre un timer d'action sur le PWM et sp�cifie la fonction call back � appeler en time-out
	// Valeur en retour >0 signifie que l'action "en retour" � �t� �cras�e

        setDisplayText(displayName, kehops.gfx[displayName].text, kehops.gfx[displayName].border, kehops.gfx[displayName].icon);  
/*        
        if(mode==ON)
            setPwmPower(pwmName, kehops.pwm[pwmName].power);
        else
            if(mode==OFF)
                setPwmPower(pwmName, 0);
 */ 
        // Utilise un delais de 5ms sinon message "Begin" arrive apres
        setTimerResult=setTimer(kehops.gfx[displayName].action.timeOut, &endDisplayAction, actionNumber, displayName, DISPLAY);     // Consid�re un blink infini  

        
	if(setTimerResult!=0){                                          // Timer pret, action effectu�e
		if(setTimerResult>1){					// Le timer � �t� �cras� par la nouvelle action en retour car sur le meme peripherique
			endOfTask=removeBuggyTask(setTimerResult);	// Supprime l'ancienne t�che qui � �t� �cras�e par la nouvelle action
                        if(endOfTask){
                                sprintf(reportBuffer, "Annulation des actions DISPLAY pour la tache #%d\n", setTimerResult);

                                // Recupere l'expediteur original du message ayant provoque
                                // l'evenement
                                char msgTo[32];
                                int ptr=getSenderFromMsgId(endOfTask);
                                strcpy(msgTo, msgEventHeader[ptr].msgFrom);
                                // Libere la memorisation de l'expediteur
                                removeSenderOfMsgId(endOfTask);
                                
                                messageResponse[0].responseType=EVENT_ACTION_ABORT;
                                sendResponse(endOfTask, message.msgFrom, EVENT, pDISPLAY, 1);		// Envoie un message ALGOID de fin de t�che pour l'action �cras�
                                printf(reportBuffer);                                                   // Affichage du message dans le shell
                                sendMqttReport(endOfTask, reportBuffer);				// Envoie le message sur le canal MQTT "Report"
                        }
		}
                return 0;
	}
	else {
            printf("Error, Impossible to set timer display\n");
            return -1;
        }
}

/**
 * \brief Function called at the end of the timer action
 * \param int actionNumber: action number (msg ID) to remove in the timer for action identification
 * \param int displayName: The name of the display define in the config file (kehops.cfg)
 * \return code error
 */
int endDisplayAction(int actionNumber, int displayName){
	int endOfTask;

	// Retire l'action de la table et v�rification si toute les actions sont effectu�es
	// Pour la t�che en cours donn�e par le message ALGOID

        endOfTask=removeBuggyTask(actionNumber);
        if(endOfTask){
            sprintf(reportBuffer, "FIN DES ACTIONS DISPLAY pour la tache #%d\n", endOfTask);

            // R�cup�re l'expediteur original du message ayant provoqu�
            // l'�venement
            char msgTo[32];
            int ptr=getSenderFromMsgId(endOfTask);
            strcpy(msgTo, msgEventHeader[ptr].msgFrom);
            // Lib�re la memorisation de l'expediteur
            removeSenderOfMsgId(endOfTask);
            messageResponse[0].responseType=EVENT_ACTION_END;
            sendResponse(endOfTask, msgTo, EVENT, pDISPLAY, 1);		// Envoie un message ALGOID de fin de t�che pour l'action �cras�
            printf(reportBuffer);						// Affichage du message dans le shell
            sendMqttReport(endOfTask, reportBuffer);			// Envoie le message sur le canal MQTT "Report"

            kehops.gfx[displayName].action.timeOut = 0;
        }
        
	return 0;
}