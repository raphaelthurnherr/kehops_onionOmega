/**
 * \file pca9685.c
 * \brief PCA9685 16 channels driver
 * \author Raphael Thurnherr
 * \version 0.1
 * \date 08.03.2019
 *
 * Library to setup and drive the 16 channel PCA9685 I2C device
 * 
 */


// Register Definitions
#define MODE1 0x00		//Mode  register  1
#define MODE2 0x01		//Mode  register  2
#define SUBADR1 0x02		//I2C-bus subaddress 1
#define SUBADR2 0x03		//I2C-bus subaddress 2
#define SUBADR3 0x04		//I2C-bus subaddress 3
#define ALLCALLADR 0x05         //LED All Call I2C-bus address
#define LED0 0x06		//LED0 start register
#define LED0_ON_L 0x06		//LED0 output and brightness control byte 0
#define LED0_ON_H 0x07		//LED0 output and brightness control byte 1
#define LED0_OFF_L 0x08		//LED0 output and brightness control byte 2
#define LED0_OFF_H 0x09		//LED0 output and brightness control byte 3

#define ALLLED_ON_L 0xFA        //load all the LEDn_ON registers, byte 0 (turn 0-7 channels on)
#define ALLLED_ON_H 0xFB	//load all the LEDn_ON registers, byte 1 (turn 8-15 channels on)
#define ALLLED_OFF_L 0xFC	//load all the LEDn_OFF registers, byte 0 (turn 0-7 channels off)
#define ALLLED_OFF_H 0xFD	//load all the LEDn_OFF registers, byte 1 (turn 8-15 channels off)
#define PRE_SCALE 0xFE		//prescaler for output frequency

#define LED_MULTIPLYER 4	// For the other 15 channels
#define INTERNAL_CLK_FREQ 25000000     //25MHz default oscillator clock

// dependency definition
#include "pca9685.h"
#include <onion-i2c.h>

unsigned char pca9685_init(device_pca9685 *pca9685_handler);        // PCA9685 driver initialization

/**
 * \fn unsigned char pca9685_init(int freq, int outputStates)
 * \brief PCA9685 driver initialization
 *
 * \param deviceAdr Specify the device bus address
 * \param freq Set the base frequecy for PWM outputs, -1 don't set the frequency
 * \param outputStates Set the default state of all PWM outputs -1 don't set the state
 * \return {Bus error count during initialization}
 */


unsigned char pca9685_init(device_pca9685 *pca9685config){
	unsigned char err=0;
/*        
        printf("Device Adr: %d \n", pca9685config->deviceAddress);
        printf("Device OutStates: %d \n", pca9685config->defaultOutputStates);
        printf("Device Freq: %d \n", pca9685config->frequency);
        printf("Device Totem: %d \n", pca9685config->totemPoleOutput);
        printf("Device EXTCLK: %d \n", pca9685config->useExternalClock);
        
        pca9685config->useExternalClock=123;
  */
        unsigned char deviceAddr = pca9685config->deviceAddress;
        unsigned char freq = pca9685config->frequency;
        unsigned char totemPole = pca9685config->totemPoleOutput;
        unsigned char invertedOut = pca9685config->invertedOutput;
        long extClkMHz = pca9685config->externalClock;
        
        long clockFreq;

        unsigned char data;
        
                    
	// MODE1 register, sleep before config
        err+= i2c_write(0, deviceAddr, MODE1, 0x10);
        
        
        // MODE1 register setup, configure clock source
        data=0;
        clockFreq = INTERNAL_CLK_FREQ;                      // default value is 25000
                
        if(extClkMHz>0){
            data |= 0x40;                                   // External clock selected
            clockFreq = extClkMHz;
        }
        
        // Write MODE1 Register
        err+= i2c_write(0, deviceAddr, MODE1, data);
        
	// Prescaler config for user frequency operation
        unsigned char prescale_value = (((clockFreq/4096) / freq)-1);
        
        // Write PRE_SCALE Register
        err+= i2c_write(0, deviceAddr, PRE_SCALE, prescale_value);
        
	// Setup MODE 2 register (inverted output and output type)
        data=0;
        
        if(invertedOut)
            data |= 0x10;
        if(totemPole)
            data |= 0x04;
        
        // Write MODE2 Register
        err+= i2c_write(0, deviceAddr, MODE2, data);
        
        // All outputs on clock 0
        err+= i2c_write(0, deviceAddr, ALLLED_ON_L, 0x00);
        err+= i2c_write(0, deviceAddr, ALLLED_ON_H, 0x00);

	// Write MODE 1 register, system ready (no sleep, no allcall_adr)
        err+= i2c_write(0, deviceAddr, MODE1, 0x81);
        
	return err;    
}