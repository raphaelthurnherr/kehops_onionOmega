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

#define DRIVER_PCA9685 "pca9685"
#define DRIVER_BH1745 "bh1745"
#define DRIVER_EFM8BB "efm8bb"
#define DRIVER_MCP23008 "mcp23008"
#define DRIVER_PCA9629 "pca9629"
#define DRIVER_VL53L0X "vl53l0x"
#define DRIVER_MCP4725 "mcp4725"
#define DRIVER_TCA9548A "tca9548a"
#define DRIVER_SSD1306 "ssd1306"
#define DRIVER_ADS101X "ads101x"
#define DRIVER_ADS111X "ads111x"

#define IFACE_GEN_HBRIDGE_MOTOR "generic_hbridge"
#define IFACE_DEVICE_I2C "I2C"

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
 * \fn char actuator_setDoutValue()
 * \brief Get the DOUT hardware id of the output from config and apply the
 *  PWM settings if available, else boolean value is apply
 *
 * \param ledID, powerr
 * \return -
 */
extern char actuator_setDoutValue(int doutID, int value);

/**
 * \fn char actuator_setAnalogValue()
 * \brief Get the AOUT hardware id of the output from config and apply the
 *  AOUT settings if available, else boolean value is apply
 *
 * \param ledID, powerr
 * \return -
 */
extern char actuator_setAnalogValue(int aoutID, int value);

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
extern int actuator_setStepperSpeed(int stepperID, int speed);


/**
 * \fn char actuator_setStepperStepAction()
 * \brief Get the STEPPER hardware id of and setup direction and step count to do
 *
 * \param motorNumber, direction, stepCount
 * \return -
 */
extern int actuator_setStepperStepAction(int stepperID, int direction, int stepCount);


extern int actuator_genericHBridge_motorDirection(int motorID, int direction);
extern int actuator_genericHBridge_motorSpeed(int motorID, int speed);
extern int actuator_genericHBridge_motorState(int motorID, int state);


extern int actuator_getFirmwareVersion(void);
extern int actuator_getBoardId(void);

extern int actuator_getCounterFrequency(unsigned char freqCounterID);          // Retourne la fr�quence actuelle mesuree sur l'encodeur
extern int actuator_getCounterPulses(unsigned char pulseCounterID);             // Retourne le nombre d'impulsion d'encodeur moteur depuis le d�marrage
extern int actuator_getDigitalInput(unsigned char dinID);                // Retourne l'état de l'entrée numérique spécifiée
extern int actuator_getDistance(unsigned char distanceSensorID);					// Retourne la distance en cm
extern int actuator_getVoltage(unsigned char ainID);			// Retourne la tension battery en mV
extern int actuator_getRGBColor(unsigned char rgbID, RGB_COLOR * rgbColor);			// Retourne la tension battery en mV
extern void actuator_clearWheel(unsigned char Id);
extern int actuator_getStepperState(int stepperID);                   // 

#endif /* ACTUATORSDRIVERS_H */
