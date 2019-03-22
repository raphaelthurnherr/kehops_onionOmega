/*
 * algoid_2wd_buggy.h
 *
 *  Created on: 8 avr. 2016
 *      Author: raph
 */

#ifndef KEHOPS_MAIN_H_
#define KEHOPS_MAIN_H_

#include "type.h"

#define OFF               0
#define ON                1
#define BLINK             2

#define MILLISECOND       0
#define CENTIMETER	  1
#define INFINITE          2
#define STEP              3
#define ROTATION          4
#define ANGLE             5

extern t_system sysInfo;

//extern t_device device;            // Device structure with actuator & sensor     
extern robot_kehops kehops;
extern t_sysConf sysConf;
extern t_sysApp sysApp;

int removeBuggyTask(int actionNumber);
#endif /* ALGOID_2WD_BUGGY_H_ */
