/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   wifi_json.h
 * Author: raph-pnp
 *
 * Created on 30. janvier 2019, 13:21
 */

#ifndef WIFI_JSON_H
#define WIFI_JSON_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "../type.h"


extern int GetWifiScanJsonResults(APDATA *destMessage, char *srcDataBuffer);    


#ifdef __cplusplus
}
#endif

#endif /* WIFI_JSON_H */

