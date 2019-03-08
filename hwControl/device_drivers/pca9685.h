/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pca9685.h
 * Author: raph-pnp
 *
 * Created on 8. mars 2019, 11:16
 */

#ifndef PCA9685_H
#define PCA9685_H

typedef struct pca9685{
    unsigned char deviceAddress;
    unsigned char frequency;
    unsigned char invertedOutput;
    unsigned char totemPoleOutput;
    long externalClock;                         // 0=driver internal clock 25MHz otherwise set the external frequency in [Hz]
} device_pca9685;


extern unsigned char pca9685_init(device_pca9685 *pca9685config);        // PCA9685 driver initialization

#endif /* PCA9685_H */
