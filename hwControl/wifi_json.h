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

struct wifiEncrypt{
    char enable[15];
};

struct authList{
    char mode [15];   // Encryption PSK, WEP, ETC
};

typedef struct accesspoint_data{
    char ssid[32];          // Nom du réseau
    struct wifiEncrypt encryption;    //  Encryption activée ON/OFF
    struct authList authentification[10];
}APDATA;    

extern int GetWifiScanJsonResults(APDATA *destMessage, char *srcDataBuffer);    

APDATA wifilist[25]; 


#ifdef __cplusplus
}
#endif

#endif /* WIFI_JSON_H */

