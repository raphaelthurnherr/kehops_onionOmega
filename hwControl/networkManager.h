/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   networkManager.h
 * Author: raph-pnp
 *
 * Created on 28. janvier 2019, 13:36
 */

#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

int InitNetworkManager(int *wanState, char *address, char *name, char *group);						// Ouverture du thread Timer
int CloseNetworkManager(void);					// Fermeture du thread Timer
int runCloudTestCommand(void);

extern unsigned char t10secFlag;				// Flag 10S scrut� par le programme principal
extern unsigned char t60secFlag;				// Flag 60Sec scrut� par le programme principal

#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* NETWORKMANAGER_H */

