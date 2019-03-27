/**
 * \file pca9629.h
 * \brief pca9629 Stepper motor drivers 
 * \author Raphael Thurnherr
 * \version 0.1
 * \date 18.03.2019
 *
 * Setup and drive stepper motors via PCA9629 IC
 * 
 */


#ifndef PCA9629_H
#define PCA9629_H

/**
 * \struct device_pca9629 [pca9629.h] Configuration structure definition
 */

typedef struct pca9629{
    unsigned char deviceAddress;                // Bus device address
    unsigned char pulsesWidth_ms;               // Specify the GPIO's port dirtection, 1 input, 0 output
} device_pca9629;



/**
 * \brief Initial configuration for Stepper motor controller
 * \return code error
 */

extern int pca9629_init(device_pca9629 *pca9629config);

/**
 * \brief pca9629_motorControl, Set the control of motor
 * \return code error
 */

extern int pca9629_motorControl(int motorNumber, int data);

#endif /* PCA9629_H */
