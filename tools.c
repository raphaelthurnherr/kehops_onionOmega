/*
 * tools.c
 *
 *  Created on: 15 avr. 2016
 *      Author: raph
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <math.h>

#include "tools.h"
#include "type.h"
#include "kehops_main.h"

int mygetch();  // Fonction getch non blocante
int speed_to_percent(float maxSpeed, float speed_cmS);
int PID_speedControl(int motorId, float currentSpeed, float setPoint);

// -------------------------------------------------------------------
// SPEED_TO_PERCENT, Fonction de conversion de la vitesse mesurée en %
// de la vitesse max
// -------------------------------------------------------------------
int speed_to_percent(float maxSpeed, float speed_cmS){
    
    int result = 100 - (round((speed_cmS - maxSpeed)/maxSpeed * 100) * -1);
    return result;
}


// -------------------------------------------------------------------
// PID_SPEEDCPMTROL, Fonction PID pour gestion vitesse du moteur
// -------------------------------------------------------------------
int PID_speedControl(int motorId, float currentSpeed, float setPoint){

    float loopTimeDT = 1; 
    
    static int lastSpeed[MAXMOTOR];
    static float sumError[MAXMOTOR];
        
    float output;
    float outputMin=0;
    float outputMax=100;
    float error;
    float newSum;
    float dErrorLoopTime;
    
    float Kp = kehops.stepperWheel[motorId].config.pidReg.Kp;   
    float Ki = kehops.stepperWheel[motorId].config.pidReg.Ki;   
    float Kd = kehops.stepperWheel[motorId].config.pidReg.Kd;   
     
    error = setPoint - currentSpeed;
    newSum = (sumError[motorId] + error) * loopTimeDT;
    dErrorLoopTime = (lastSpeed[motorId] - currentSpeed) / loopTimeDT;
    lastSpeed[motorId] = currentSpeed;
    
    output = Kp * error + Ki * sumError[motorId] + Kd * dErrorLoopTime;
    
    if(output >= outputMax)
        output = outputMax;
    else
        if(output <= outputMin)
            output = outputMin;
        else 
            sumError[motorId] =  newSum;
    
    return output;
}


// -------------------------------------------------------------------
// MYGETCH, Fonction getch non blocante
// -------------------------------------------------------------------
int mygetch(void)
{
	struct termios oldt,newt;
	int ch;
	tcgetattr( STDIN_FILENO, &oldt );
	newt = oldt;
	newt.c_lflag &= ~( ICANON | ECHO );
	tcsetattr( STDIN_FILENO, TCSANOW, &newt );
	ch = getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
	return ch;
}
