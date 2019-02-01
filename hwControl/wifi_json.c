
#define KEY_RESULTS "{'results'"
#define KEY_RESULTS_SSID               "{'results'[*{'ssid'"
#define KEY_RESULTS_ENCRYPT_ENABLE     "{'encryption'{'enabled'"
#define KEY_RESULTS_ENCRYPT_AUTH       "{'encryption'{'authentication'"
#define KEY_RESULTS_ENCRYPT_AUTH_MODE  "{'encryption'{'authentication'["
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
        jRead((char *)srcBuffer, KEY_RESULTS, &element );

          // RECHERCHE DATA ARRAY
        if(element.dataType == JREAD_ARRAY ){
          for(i=0; i<element.elements; i++ )    // loop for no. of elements in JSON
          {
                jRead_string((char *)srcBuffer, KEY_RESULTS_SSID, destMessage->list[i].ssid, 32, &i);
                jRead_string((char *)srcBuffer, KEY_RESULTS_ENCRYPT_ENABLE, destMessage->list[i].encryption.enable, 15, &i);
                  
   
                jRead(element.pValue, KEY_RESULTS_ENCRYPT_AUTH, &auth_list );
                if(auth_list.dataType == JREAD_ARRAY )
                {
                    printf("YEAH !!!!!!!!!!   %d\n", i);
                    char *pArray= (char *)auth_list.pValue;
                    struct jReadElement arrayElement;
                    int index;
                    for( index=0; index < auth_list.elements; index++ )
                    {
                        pArray= jReadArrayStep( pArray, &arrayElement );
                        if(arrayElement.dataType == JREAD_STRING)
                        {
                            printf("YEAH !!!!!!!!!!   %d\n", i);
                        }
                    }        
                } 
                
   
   /*
                    int nbOfauth=auth_list.elements;
                    for(j=0;j<nbOfauth;j++){
                        jRead_string((char *)srcBuffer, KEY_RESULTS_ENCRYPT_AUTH_MODE, destMessage->list[i].encryption.authentification[j].mode, 15, &j);        
                        printf("-------------%d         %s",i,  destMessage->list[i].encryption.authentification[j].mode);
                    }
                        */
          }
        }
        else
            return 0;

        return element.elements;
}