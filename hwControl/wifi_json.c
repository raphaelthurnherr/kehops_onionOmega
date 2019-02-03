
#define KEY_RESULTS "{'results'"
#define KEY_RESULTS_SSID               "{'results'[*{'ssid'"
#define KEY_RESULTS_ENCRYPT_ENABLE     "{'results'[*{'encryption'{'enabled'"
#define KEY_RESULTS_ENCRYPT_WPA        "{'results'[*{'encryption'{'wpa'"
#define KEY_RESULTS_ENCRYPT_WPA_        "{'results'[*{'encryption'{'wpa'["
#define KEY_RESULTS_ENCRYPT_AUTH       "{'results'[*{'encryption'{'authentication'"
#define KEY_RESULTS_ENCRYPT_AUTH_       "{'results'[*{'encryption'{'authentication'["

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>


#include "libs/lib_json/jRead.h"
#include "libs/lib_json/jWrite.h"
#include "wifi_json.h"

//void jsonBuilder(char * buffer, int msgId, char* to, char * from, char * msgType,char * msgParam, unsigned char orgType, unsigned char count);
int GetWifiScanJsonResults(APDATA *destMessage, char *srcDataBuffer);

// -----------------------------------------------------------------------------
// GetWifiScanJsonResults
// Get message from buffer and set in the message structure
// -----------------------------------------------------------------------------

int GetWifiScanJsonResults(APDATA *destMessage, char *srcBuffer){
	struct jReadElement element, auth_list;
	int i, j;
        char test;
        jRead((char *)srcBuffer, KEY_RESULTS, &element );

          // RECHERCHE DATA ARRAY
        if(element.dataType == JREAD_ARRAY ){
          for(i=0; i<element.elements; i++ )    // loop for no. of elements in JSON
          {
                
                jRead_string((char *)srcBuffer, KEY_RESULTS_SSID, destMessage->list[i].ssid, 32, &i);
                jRead_string((char *)srcBuffer, KEY_RESULTS_ENCRYPT_ENABLE, destMessage->list[i].encryption.enable, 15, &i);
                jRead_string((char *)srcBuffer, KEY_RESULTS_ENCRYPT_AUTH_, destMessage->list[i].encryption.authentification[0].mode, 15, &i);        
                jRead_string((char *)srcBuffer, KEY_RESULTS_ENCRYPT_WPA_, destMessage->list[i].encryption.wpa[0].type, 15, &i);        

                printf("\n");
          }
        }
        else
            return 0;

        return element.elements;
}