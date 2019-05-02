/*
 * buggy_descriptor.h
 *
 *  Created on: 25 nov. 2016
 *      Author: raph
 * test Git
 */

#ifndef ALGOIDCOM_BUGGY_DESCRIPTOR_H_
#define ALGOIDCOM_BUGGY_DESCRIPTOR_H_

typedef enum o_type{
	UNKNOWN = -1,
	MOTOR,
        STEPMOTOR,
	PWM,
	LED,
        AOUT
}t_type;


#define MAXPWM 64
#define MAXLED 64
#define MAXAOUT 64
#define MAXAIN 32
#define MAXBTN 32
#define MAXSONAR 16
#define MAXSTEPPER 16
#define MAXMOTOR 16
#define MAXRGBC 32
#define MAXDIN 64
#define MAXCOUNTER 16


// Check TO CONVERT IN INT -1 / 0 / +1   IF NECESSARY !!!!
#define BUGGY_STOP 		0
#define BUGGY_FORWARD           1
#define BUGGY_BACK 		-1

#endif /* ALGOIDCOM_BUGGY_DESCRIPTOR_H_ */
