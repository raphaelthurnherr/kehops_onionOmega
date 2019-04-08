/**
 * \file actuatorsDrivers.h
 * \brief  Set or Get action on an actuator of Kehops
 *      
 * \author Raphael Thurnherr
 * \version 0.1
 * \date 21.03.2019
 *
 * Using the configManager with devices_list (IC) and parts list (LED, Motor, etc...), these functions will
 * interconnect the hi level commands (motors, led, etc...) to the hardware output or inputs devices
 * 
 * Note: Per definition, a generic "drivers" can use more one IC drivers for create an action on an actuator
 */


#ifndef ACTUATORSDRIVERS_H
#define ACTUATORSDRIVERS_H


typedef struct s_color{
        int red;
        int green;
        int blue;
        int clear;
//        struct s_rgbConfig config;
}RGB_COLOR;


/**
 * \brief Initialize the devices IC of the board
 * \param -
 * \return -
 */  
extern int boardHWinit();

/**
 * \fn char actuator_setLedPower()
 * \brief Get the DOUT hardware id of the LED from config and apply the PWM settings
 *
 * \param ledID, powerr
 * \return -
 */
extern char actuator_setLedPower(int doutID, int power);

/**
 * \fn char actuator_setPwmPower()
 * \brief Get the DOUT hardware id of the PWM output from config and apply the PWM settings
 *
 * \param ledID, powerr
 * \return -
 */
extern char actuator_setPwmPower(int doutID, int power);


/**
 * \fn char actuator_setsetServoPosition()
 * \brief Get the DOUT hardware id of the SERVO from config and apply the PWM settings
 *
 * \param pwmID, position
 * \return -
 */
extern char actuator_setServoPosition(int doutID, int position);
        

/**
 * \fn char actuator_setStepperSpeed()
 * \brief Get the STEPPER hardware id of and setup the speed
 *
 * \param motorNumber, direction, stepCount
 * \return -
 */
extern int actuator_setStepperSpeed(int motorNumber, int speed);


/**
 * \fn char actuator_setStepperStepAction()
 * \brief Get the STEPPER hardware id of and setup direction and step count to do
 *
 * \param motorNumber, direction, stepCount
 * \return -
 */
extern int actuator_setStepperStepAction(int motorNumber, int direction, int stepCount);

extern int actuator_getFirmwareVersion(void);
extern int actuator_getBoardId(void);

extern int actuator_getCounterFrequency(unsigned char wheelID);          // Retourne la fr�quence actuelle mesuree sur l'encodeur
extern int actuator_getCounterPulses(unsigned char wheelID);             // Retourne le nombre d'impulsion d'encodeur moteur depuis le d�marrage
extern int actuator_getDigitalInput(unsigned char dinID);                // Retourne l'état de l'entrée numérique spécifiée
extern int actuator_getButtonInput(unsigned char btnID);
extern int actuator_getDistance(unsigned char distanceSensorID);					// Retourne la distance en cm
extern int actuator_getVoltage(unsigned char ainID);			// Retourne la tension battery en mV
extern int actuator_getRGBColor(unsigned char rgbID, RGB_COLOR * rgbColor);			// Retourne la tension battery en mV
extern void actuator_clearWheel(unsigned char Id);
extern int actuator_getStepperState(int motorNumber);                   // 

#endif /* ACTUATORSDRIVERS_H */
