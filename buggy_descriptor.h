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
	LED
}t_type;

typedef enum o_encoder{
	MOTOR_ENCODER_LEFT,
	MOTOR_ENCODER_RIGHT,
	NBCOUNTER_
}t_encoder;

typedef enum o_din{
	DIN_0,
	DIN_1,
        DIN_2,
        DIN_3,
        DIN_4,
        DIN_5,
	NBDIN_
}t_din;

typedef enum o_btn{
	BTN_0,
	BTN_1,
	NBBTN_
}t_btn;

typedef enum o_colorSens{
	RGBC_SENS_0,
	RGBC_SENS_1,
	NBRGBC_
}t_rgbc;

typedef enum o_ain{
	BATT_0,
	NBAIN_
}t_ain;

typedef enum o_sonar{
	SONAR_0,
	NBSONAR_
}t_sonar;

typedef enum o_motor{
	MOTOR_0,
	MOTOR_1,
	NBMOTOR_
}t_motor;

typedef enum o_stepper{
	STEPPER_0,
        NBSTEPPER_
}t_stepper;

#define MAXPWM 64
#define MAXLED 64
#define MAXAIN 32
#define MAXBTN 32
#define MAXSONAR 16
#define MAXSTEPPER 16
#define MAXMOTOR 16
#define MAXRGBC 32
#define MAXDIN 64
#define MAXCOUNTER 16


//unsigned char NBPWM=0;



// Check TO CONVERT IN INT -1 / 0 / +1   IF NECESSARY !!!!
#define BUGGY_STOP 		0
#define BUGGY_FORWARD           1
#define BUGGY_BACK 		-1

#endif /* ALGOIDCOM_BUGGY_DESCRIPTOR_H_ */
