/**
 * \file kehopsConfig.h
 * \brief  Kehops configuration utility functions
 *      
 * \author Raphael Thurnherr
 * \version 0.1
 * \date 21.03.2019
 *
 * Function libryry for hi level kehops configuration using kehops.cfg
 * 
 */

#ifndef KEHOPSCONFIG_H
#define KEHOPSCONFIG_H

extern void extractKehopsConfig(char * srcDataBuffer);
extern char SaveKehopsConfig(char * fileName);

extern unsigned char NBPWM;
extern unsigned char NBLED;
extern unsigned char NBAIN;
extern unsigned char NBSONAR;
extern unsigned char NBSTEPPER;
extern unsigned char NBMOTOR;
extern unsigned char NBRGBC;
extern unsigned char NBBTN;
extern unsigned char NBDIN;
extern unsigned char NBWHEEL;
extern unsigned char NBAOUT;
extern unsigned char NBDISPLAY;

#endif /* KEHOPSCONFIG_H */
