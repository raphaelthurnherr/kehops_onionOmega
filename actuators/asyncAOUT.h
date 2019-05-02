/**
 * \file asyncAOUT.h
 * \brief Set an asynchronous action for Analog output to the timer
 * 
 * \author Raphael Thurnherr
 * \version 0.1
 * \date 29.04.2019
 *
 * Library to setup and drive the 8 channel I2C switch
 *
 */

#ifndef ASYNCAOUT_H
#define ASYNCAOUT_H

/**
 * \brief Set an Analog outup action to the timer
 * \param int actionNumber: action number (msg ID) to set in the timer for action identification
 * \param int aoutName: The name of the aout define in the config file (kehops.cfg)
 * \param int mode: Working mode (0: normal (Set the value one time)
 * \param int value: Value to put on the output
 * \return code error
 */

extern int setAsyncAoutAction(int actionNumber, int aoutName, int mode, int value);

/**
 * \brief Function called at the end of the timer action
 * \param int actionNumber: action number (msg ID) to remove in the timer for action identification
 * \param int aoutName: The name of the aout define in the config file (kehops.cfg)
 * \return code error
 */
extern int endAoutAction(int actionNumber, int aoutName);


#endif /* ASYNCAOUT_H */
