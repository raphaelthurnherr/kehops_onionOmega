/**
 * \file asyncDisplay.c
 * \brief run asnchronous action for display
 * 
 * \author Raphael Thurnherr
 * \version 0.1
 * \date 13.05.2019
 *
 * Library to setup and drive the 12 bit ADC converter ADS111x 
 * 
 */


/**
 * \brief Set an Display action to the timer
 * \param int actionNumber: action number (msg ID) to set in the timer for action identification
 * \param int displayName: The name of the display define in the config file (kehops.cfg)
 * \param int value: Value to put on the output
 * \return code error
 */

extern int setAsyncDisplayAction(int actionNumber, int displayName, int value);

/**
 * \brief Function called at the end of the timer action
 * \param int actionNumber: action number (msg ID) to remove in the timer for action identification
 * \param int displayName: The name of the display define in the config file (kehops.cfg)
 * \return code error
 */
extern int endDisplayAction(int actionNumber, int displayName);


#ifndef ASYNCDISPLAY_H
#define ASYNCDISPLAY_H

#endif /* ASYNCDISPLAY_H */
