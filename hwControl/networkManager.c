/*
 * networkManager.c
 *
 *  Created on: 8 avr. 2016
 *      Author: raph
 */

// Defninition des emplacement dans les variables timer avec callback

#include "pthread.h"
#include <unistd.h>
#include <stdio.h>
#include "networkManager.h"
#include "udpPublish.h"
#include "messagesManager.h"

// Thread Messager
pthread_t th_network;

int *ptr_wanOnline;
char *ptr_pingAddress;
char *ptr_robotName;
char *ptr_robotGroup;

int runCloudTestCommand(void);

// ------------------------------------------
// Programme principale TIMER
// ------------------------------------------
void *networkTask (void * arg){
	unsigned int cyclicTimer10sec;	// Compteur du timer cyclique 10Secondes
        unsigned int cyclicTimer60sec;	// Compteur du timer cyclique 10Secondes
        
        
        // Initialisation UDP pour broadcast IP Adresse
	initUDP();

// --------------------------------------------------------------------
// BOUCLE DU PROGRAMME PRINCIPAL
// - Annonce UDP de pr�sence du buggy sur le r�seau  chaque 10Seconde
// - Ping du broker pour test connexion internet
// --------------------------------------------------------------------

        runCloudTestCommand();             
        
	while(1){
            
            // Controle le time out de 10 secondes
		if(cyclicTimer10sec>=10000){

                    // Envoie un message UDP sur le r�seau, sur port 53530 (CF udpPublish.h)
                    // Avec le ID du buggy (fourni par le gestionnaire de messagerie)
                    char udpMessage[50];
                    sprintf(&udpMessage[0], "[ %s ] I'm here", ptr_robotName);		// Formattage du message avec le Nom du client buggy
                    sendUDPHeartBit(udpMessage);								// Envoie du message
    //		printf("\n Send UDP: %s", udpMessage);                
                    t10secFlag=0;
                    
                    
                    cyclicTimer10sec=0;				// Reset le compteur 10secondes
		}

                // Controle le time out de 10 secondes
		if(cyclicTimer60sec>=60000){

                    // Check internet connectivity
                    runCloudTestCommand();             
                    t60secFlag=0;  

                    cyclicTimer60sec=0;				// Reset le compteur 10secondes
		}
            
		cyclicTimer10sec++;				// Reset le compteur 10secondes
                cyclicTimer60sec++;
		usleep(1000);
	}
	pthread_exit (0);
}

// ------------------------------------------------------------------------------------
// INITNETWORKMANAGER: Initialisation du gestionnaire réseau
// - D�marre le thread
// ------------------------------------------------------------------------------------
int InitNetworkManager(int *wanState, char *address, char *name, char *group){
    
        // Récupération des variable de destination pour le status internet 
        // et IP du broker;
        ptr_wanOnline = wanState;
        ptr_pingAddress = address;
        ptr_robotName = name;
        ptr_robotGroup = group;

	// CREATION DU THREAD DE TIMER
	  if (pthread_create (&th_network, NULL, networkTask, NULL)!=0) {
		return (1);
	  }else return (0);
}

// ------------------------------------------------------------------------------------
// CLOSETIMER: Fermeture du gestionnaire de timers
// - Stop le thread timers
// ------------------------------------------------------------------------------------

int CloseNetworkManager(void){
	int result;
	// TERMINE LE THREAD DE GESTION RESEAU
	pthread_cancel(th_network);
	// Attends la terminaison du thread de messagerie
	result=pthread_join(th_network, NULL);
	return (result);
}

int runCloudTestCommand(void){
    int status=0;
    char systemCmd[128];
 //       sendMqttReport(message.msgID, "Try to ping cloud server on vps596769.ovh.net...");// Envoie le message sur le canal MQTT "Report"   
        
        sprintf(&systemCmd, "ping -q -c 3 %s", ptr_pingAddress);
        //sprintf(&systemCmd, "ping -q -c 2 -t 1000 %s", "www.google.com");
        status=system(systemCmd);
        if(status != 0)
            *ptr_wanOnline = 0;
        else 
            *ptr_wanOnline = 1;
   
    return ptr_wanOnline;
}