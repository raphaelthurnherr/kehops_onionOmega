/**
 * \file bh1745.h
 * \brief bh1745 NUC Color Sensor driver
 * \author Raphael Thurnherr
 * \version 0.1
 * \date 18.03.2019
 *
 * Setup and drive the 16 bit RGB color sensor
 */

#ifndef I2CSIMU

// REGISTER DEFINITION FOR BH1745NUC IC

#define SYSTEM_CONTROL  0x40 // System control
#define MODE_CONTROL1   0x41 // Function setting
#define MODE_CONTROL2   0x42 // Function setting
#define MODE_CONTROL3   0x44 // Function setting
#define RED_DATA_LSBs   0x50 // Low byte of RED
#define RED_DATA_MSBs   0x51 // High byte of RED
#define GREEN_DATA_LSBs 0x52 // Low byte of GREEN
#define GREEN_DATA_MSBs 0x53 // High byte of GREEN
#define BLUE_DATA_LSBs  0x54 // Low byte of BLUE
#define BLUE_DATA_MSBs  0x55 // High byte of BLUE
#define CLEAR_DATA_LSBs 0x56 // Low byte of CLEAR
#define CLEAR_DATA_MSBs 0x57 // High byte of CLEAR
#define DINT_DATA_LSBs  0x58 // Low byte of Internal Data
#define DINT_DATA_MSBs  0x59 // High byte of Internal Data
#define INTERRUPT       0x60 // Interrupt setting
#define PERSISTENCE     0x61 // Persistence setting
#define TH_LSBs         0x62 // threshold low byte
#define TH_MSBs         0x63 // threshold high byte
#define TL_LSBs         0x64 // threshold low byte
#define TL_MSBs         0x65 // threshold high byte
#define MANID           0x92 // Manufacturer ID

#include "bh1745.h"
#include <onion-i2c.h>


/**
 * \brief bh1745nuc_init, device initialisation
 * \param device_bh1745 bh1745Config, pointer on the configuration structure
 * \return code error
 */
unsigned char bh1745nuc_init(device_bh1745 *bh1745Config){
    unsigned char err=0;
    unsigned char deviceAddress = bh1745Config->deviceAddress;
    
    // Control register
    // b7:Initial reset, b6, INT inactive
    err+= i2c_write(0, deviceAddress, SYSTEM_CONTROL, 0xC0);   
    // Control register mode1 (Measurement time=640mS)
    err+= i2c_write(0, deviceAddress, MODE_CONTROL1, 0x02);   
    // Control register mode2 (Mesure RGBC active, Gain=1)
    err+= i2c_write(0, deviceAddress, MODE_CONTROL2, 0x10);   
    // Interruption register (disable interrupt, pin disable)
    err+= i2c_write(0, deviceAddress, INTERRUPT, 0x00);
    // Persistance register
    err+= i2c_write(0, deviceAddress, PERSISTENCE, 0x00);  
    
    if(err)
        printf("Kehops I2C RGB BH1745 device initialization with %d error\n", err);
    
    return err;    
}


/**
 * \brief bh1745_getChannelRGBvalue, get color value for the specified channel 
 * \param device_bh1745 bh1745Config, pointer on the configuration structure
 * \param int channel, specify the channel (0 = RED, 1 = GREEN, 2 = BLUE, 3 = CLEAR)
 * \return code error
 */

int bh1745nuc_getChannelRGBvalue(device_bh1745 * bh1745Config, int channel){
	char err;
        unsigned char deviceAddress = bh1745Config->deviceAddress;
        
	int value=-1;
        int RGBregAdr = CLEAR_DATA_LSBs;  // Registre CLEAR LSB par defaut 
        
        unsigned int pcMSB=0, pcLSB=0;
        
        switch(channel){
            case RED :   RGBregAdr=RED_DATA_LSBs; break;
            case GREEN : RGBregAdr=GREEN_DATA_LSBs; break;
            case BLUE :  RGBregAdr=BLUE_DATA_LSBs; break;
            case CLEAR : RGBregAdr=CLEAR_DATA_LSBs; break;
            
            default : value=-1; break;
        }
        
        err = i2c_readByte(0, deviceAddress, RGBregAdr, &pcLSB);
        err+= i2c_readByte(0, deviceAddress, RGBregAdr+1, &pcMSB);
                
	if(!err){
            value = pcLSB + (pcMSB<<8);
		return value;
	}else{
            printf("BH1745_getRGBvalue() -> Read error\n");
            return -1;
        }
}

#endif