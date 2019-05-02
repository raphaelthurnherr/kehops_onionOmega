/**
 * \file asyncAOUT.c
 * \brief Set an asynchronous action for Analog output to the timer
 * 
 * \author Raphael Thurnherr
 * \version 0.1
 * \date 29.04.2019
 *
 * Library to setup and drive the 8 channel I2C switch
 *
 */

#include "asyncAOUT.h"

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


int checkAoutStatus(int actionNumber, int aoutName);

/**
 * \brief Set an Analog outup action to the timer
 * \param int actionNumber: action number (msg ID) to set in the timer for action identification
 * \param int aoutName: The name of the aout define in the config file (kehops.cfg)
 * \param int mode: Working mode (0: normal (Set the value one time)
 * \param int value: Value to put on the output
 * \return code error
 */

int setAsyncAoutAction(int actionNumber, int aoutName, int mode, int value){
    int setTimerResult;
    int endOfTask;
  
    // D�marre de timer d'action sur la roue et sp�cifie la fonction call back � appeler en time-out
    // Valeur en retour >0 signifie que l'action "en retour" � �t� �cras�e
    switch(mode){               
            case  ON:       setAnalogValue(aoutName, kehops.aout[aoutName].power);
                            break;

            case  OFF:      setAnalogValue(aoutName, 0);
                            break;

                                break;
            default: printf("\n!!! ERROR Function [setAsyncAoutAction] -> unknown mode"); break;
    }
        
    // Utilise un delais de 5ms sinon message "Begin" arrive apres
    setTimerResult = setTimer(5, &endAoutAction, actionNumber, aoutName, AOUT);     // Considère un blink infini  
            
    if(setTimerResult!=0){                                          // Timer pret, action effectu�e
            if(setTimerResult>1){					// Le timer � �t� �cras� par la nouvelle action en retour car sur le meme peripherique
                    endOfTask=removeBuggyTask(setTimerResult);	// Supprime l'ancienne t�che qui � �t� �cras�e par la nouvelle action
                    if(endOfTask){
                            sprintf(reportBuffer, "Annulation des actions AOUT pour la tache #%d\n", setTimerResult);

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
        printf("Error, Impossible to set timer AOUT\n");
        return -1;
    }    
}

/**
 * \brief Function called at the end of the timer action
 * \param int actionNumber: action number (msg ID) to remove in the timer for action identification
 * \param int aoutName: The name of the aout define in the config file (kehops.cfg)
 * \return code error
 */
int endAoutAction(int actionNumber, int aoutName){
	int endOfTask;

	// Retire l'action de la table et v�rification si toute les actions sont effectu�es
	// Pour la t�che en cours donn�e par le message ALGOID

        endOfTask=removeBuggyTask(actionNumber);
        if(endOfTask){
                sprintf(reportBuffer, "FIN DES ACTIONS aout pour la tache #%d\n", endOfTask);

                // R�cup�re l'expediteur original du message ayant provoqu�
                // l'�venement
                char msgTo[32];
                int ptr=getSenderFromMsgId(endOfTask);
                strcpy(msgTo, msgEventHeader[ptr].msgFrom);
                // Lib�re la memorisation de l'expediteur
                removeSenderOfMsgId(endOfTask);
                messageResponse[0].responseType=EVENT_ACTION_END;
                sendResponse(endOfTask, msgTo, EVENT, pAOUT, 1);			// Envoie un message ALGOID de fin de t�che pour l'action �cras�
                printf(reportBuffer);									// Affichage du message dans le shell
                sendMqttReport(endOfTask, reportBuffer);				// Envoie le message sur le canal MQTT "Report"
        }

	return 0;
}


/**
 * \brief checkStepperStatus Function called at the end of the timer action
 * \param int actionNumber: action number (msg ID) to remove in the timer for action identification
 * \param int aoutName: The name of the aout define in the config file (kehops.cfg)
 * \return code error
 */

int checkAoutStatus(int actionNumber, int aoutName){
     
    /*
    if(!getAoutState(aoutName)){
        endAoutAction(actionNumber, aoutName);
    }
     */
    if(1){
        endAoutAction(actionNumber, aoutName);
    }
    else{
        setTimer(100, &checkAoutStatus, actionNumber, aoutName, AOUT);
    }
	return 0;
}

/**
 * \brief Function called at the end of the timer action
 * \param int actionNumber: action number (msg ID) to remove in the timer for action identification
 * \param int aoutName: The name of the aout define in the config file (kehops.cfg)
 * \return code error
 */
int dummyAoutAction(int actionNumber, int aoutName){
        setTimer(0, &dummyAoutAction, actionNumber, aoutName, AOUT);
    return 0;
}