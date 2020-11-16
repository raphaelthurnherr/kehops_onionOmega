/**
 * \file pca9629.h
 * \brief pca9629 Stepper motor drivers 
 * \author Raphael Thurnherr
 * \version 0.2
 * \date 15.11.2020
 *
 * Setup and drive stepper motors via PCA9629 IC
 * 
 */


#ifndef PCA9629_H
#define PCA9629_H

#define PCA_9629A_CLK_PRESCALER_REGVALUE  1

/**
 * \struct device_pca9629 [pca9629.h] Configuration structure definition
 */

typedef struct pca9629{
    char deviceName[25];                        // Device Name of IC
    unsigned char deviceAddress;                // Bus device address
    //float pulsesWidth_ms;                       // Specify the pulse width for motor driving
    int frequency;                       // Specify the pulse width for motor driving
    unsigned char driveMode;                    // Set the drive mode (0 wavedrive, 1 fullstep, 2 halfstep)
    unsigned char gpioDirection;                // Specify the GPIO's port dirtection, 1 input, 0 output
} device_pca9629;


/**
 * \brief Initial configuration for Stepper motor controller
 * \return code error
 */

extern int pca9629_init(device_pca9629 *pca9629config);

extern int PCA9629_StepperMotorControl(device_pca9629 *pca9629config, int data);
extern int PCA9629_StepperStepperMode(device_pca9629 *pca9629config, int mode);

extern int PCA9629_StepperMotorMode(device_pca9629 *pca9629config, int data);                 // Configuration mode continu ou single action
extern int PCA9629_StepperMotorSetStep(device_pca9629 *pca9629config, int stepCount);         //Configuration du registre "PAS" du driver moteur
extern int PCA9629_StepperDriveMode(device_pca9629 *pca9629config, unsigned char data);       // Mode action continue ou unique
extern int PCA9629_StepperMotorPulseWidth(device_pca9629 *pca9629config, int data);           // Définition de la largeur d'impulstion
extern int PCA9629_ReadMotorState(device_pca9629 *pca9629config);                             // Lecture du registre de contrôle du moteur

extern int PCA9629_GPIOConfig(device_pca9629 *pca9629config, unsigned char data);             // Configuration du registre GPIO

/**
 * \brief PCA9629 set output state on specified input channel, the function read port state before rewrite
 * \param pointer on the configuration structure
 * \return code error
 */
extern int PCA9629_setChannel(device_pca9629 *pca9629config, unsigned char channel, unsigned char state);

/**
 * \brief PCA9629 read input state on specified input channel
 * \param pointer on the configuration structure
 * \return code error
 */

extern int PCA9629_getChannel(device_pca9629 *pca9629config, unsigned char channel);

#endif /* PCA9629_H */
