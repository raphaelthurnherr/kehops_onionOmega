/**
 * \file pca9629.h
 * \brief pca9629 Stepper motor drivers 
 * \author Raphael Thurnherr
 * \version 0.1
  * \date 15.11.2020
 *
 * Setup and drive stepper motors via PCA9629 IC
 * 
 */

#ifndef I2CSIMU

// REGISTER DEFINITION FOR PCA9629 IC

#include "pca9629.h"
#include <onion-i2c.h>


/**
 * \brief Initial configuration for Stepper motor controller
 * \param handler to PCA9629 configuration structure
 * \return code error
 */

int pca9629_init(device_pca9629 *pca9629config){
    unsigned char err=0;
    
    // CONFIGURATION DU CIRCUIT DRIVER MOTEUR PAS A PAS
    // bit 6 et 7 non utilisés dans les registres

    unsigned char OP_CFG_PHS_DATA = 0x10;
    
    unsigned char devAddress = pca9629config->deviceAddress;
    unsigned char gpioDirection = pca9629config->gpioDirection & 0x0F;

    switch(pca9629config->driveMode){
        case 0 : OP_CFG_PHS_DATA |= 0x10; break;        // Wavedrive
        case 1 : OP_CFG_PHS_DATA |= 0x40; break;        // Full step
        case 2 : OP_CFG_PHS_DATA |= 0x80; break;        // Half step
        default : OP_CFG_PHS_DATA |= 0x10; break;       // Wavedrive default
    }
        
    err+= i2c_write(0, devAddress, 0x00, 0x20);    // MODE - Configuration du registre MODE (pin INT désactivée, Allcall Adr. désactivé)
    err+= i2c_write(0, devAddress, 0x01, 0xFF);    // WDTOI
    err+= i2c_write(0, devAddress, 0x02, 0x00);    // WDCNTL
    err+= i2c_write(0, devAddress, 0x03, gpioDirection);         //  Configure PCA9629 GPIO as input or output
    err+= i2c_write(0, devAddress, 0x04, 0x10);    // INTMODE
    err+= i2c_write(0, devAddress, 0x05, 0x1F);    // MSK
    err+= i2c_write(0, devAddress, 0x06, 0x00);    // INTSTAT
    //err+= i2c_write(0, PCA9629, 0x07, 0x);    // IP
    err+= i2c_write(0, devAddress, 0x08, 0x00);    // INT_MTR_ACT
    err+= i2c_write(0, devAddress, 0x09, 0x00);    // EXTRASTEPS0
    err+= i2c_write(0, devAddress, 0x0A, 0x00);    // EXTRASTEPS1
    err+= i2c_write(0, devAddress, 0x0B, OP_CFG_PHS_DATA);    // OP_CFG_PHS
    err+= i2c_write(0, devAddress, 0x0C, 0x00);    // OP_STAT_TO
    err+= i2c_write(0, devAddress, 0x0D, 0x00);    // RUCNTL
    err+= i2c_write(0, devAddress, 0x0E, 0x00);    // RDCNTL
    err+= i2c_write(0, devAddress, 0x0F, 0x01);    // PMA - 0x01 Action unique, 0x00 action continue
    err+= i2c_write(0, devAddress, 0x10, 0x05);    // LOOPDLY_CW - Pour un delais de 20ms d'inversion de sens
    err+= i2c_write(0, devAddress, 0x11, 0x05);    // LOOPDLY_CCW Pour un delais de 20ms d'inversion de sens
    err+= i2c_write(0, devAddress, 0x12, 0xFF);    // CWSCOUNTL - Nombre de pas CW
    err+= i2c_write(0, devAddress, 0x13, 0xFF);    // CWSCOUNTH
    err+= i2c_write(0, devAddress, 0x14, 0xFF);    // CCWSCOUNTL - Nombre de pas CCW
    err+= i2c_write(0, devAddress, 0x15, 0xFF);    // CCWSCOUNTH
    err+= i2c_write(0, devAddress, 0x16, 0x9A);    // CWPWL - Vitesse / Largeur d'impulsion pour CW (1mS)
    err+= i2c_write(0, devAddress, 0x17, 0x02);    // CWPWH
    err+= i2c_write(0, devAddress, 0x18, 0x9A);    // CCWPWL - Vitesse / Largeur d'impulsion pour CCW
    err+= i2c_write(0, devAddress, 0x19, 0x02);    // CCWPWH
    err+= i2c_write(0, devAddress, 0x1A, 0x00);    // MCNTL - Registre contrôle moteur
    err+= i2c_write(0, devAddress, 0x1B, 0xE2);    // SUBA1
    err+= i2c_write(0, devAddress, 0x1C, 0xE4);    // SUBA2
    err+= i2c_write(0, devAddress, 0x1D, 0xE8);    // SUBA3
    err+= i2c_write(0, devAddress, 0x1E, 0xE0);    // ALLCALLA
    //err+= i2c_write(0, PCA9629, 0x1F, 0x00);    // STEPCOUNT0
    //err+= i2c_write(0, PCA9629, 0x20, 0x00);    // STEPCOUNT1
    //err+= i2c_write(0, PCA9629, 0x21, 0x00);    // STEPCOUNT2
    //err+= i2c_write(0, PCA9629, 0x22, 0x00);    // STEPCOUNT3
   
    if(err)
        printf("Kehops I2C Step motor driver device initialization with %d error\n", err);
    
    return err;        
}

/**
 * \brief pca9629_motorControl, Set the control register of motor
 * \return code error
 */

int PCA9629_StepperMotorControl(device_pca9629 *pca9629config, int data){
   	unsigned char err=0;

        unsigned char devAddress = pca9629config->deviceAddress;

        // Configuration du registre dans le sens horaire
        err += i2c_write(0, devAddress, 0x1a, data & 0x00FF);           // Défini le nombre de rotation dans le registre LOW       
        
        return(err);
}


/**
 * \brief int PCA9629_StepperMotorSetStep, Set the number of step to do in CW and CCW direction
 * \param handler to PCA9629 configuration structure
 * \return code error
 */

int PCA9629_StepperMotorSetStep(device_pca9629 *pca9629config, int stepCount){
   	unsigned char err=0;
       
        unsigned char devAddress = pca9629config->deviceAddress;

        // Configuration du registre de nombre de pas dans le sens horaire
        err += i2c_write(0, devAddress, 0x12, stepCount&0x00FF);           // Défini le nombre de pas dans le registre LOW
        err += i2c_write(0, devAddress, 0x13, (stepCount&0xFF00)>>8);    // Défini le nombre de pas dans le registre HIGH

        // Configuration du registre de nombre de pas dans le sens anti-horaire
        err += i2c_write(0, devAddress, 0x14, stepCount&0x00FF);           // Défini le nombre de pas dans le registre LOW
        err += i2c_write(0, devAddress, 0x15, (stepCount&0xFF00)>>8);    // Défini le nombre de pas dans le registre HIGH        

	return(err);
}

/**
 * \brief int PCA9629_ReadMotorState, Get the actual state of the motor
 * \param handler to PCA9629 configuration structure
 * \return code error
 */
int PCA9629_ReadMotorState(device_pca9629 *pca9629config){
   	unsigned char err=0;
        int regState = 0;
    
    unsigned char devAddress = pca9629config->deviceAddress;

        // LEcture du registre de controle du driver moteur
        err += i2c_readByte(0, devAddress, 0x1a, &regState);
    
    if(!err){    
        return regState;
	}else{
            printf("PCA9629_ReadMotorState() -> Read error\n");
            return -1;
        }
}


/**
 * \brief int PCA9629_StepperMotorMode, Set the mode continuous or single action
 * \param handler to PCA9629 configuration structure
 * \return code error
 */

int PCA9629_StepperMotorMode(device_pca9629 *pca9629config, int data){
   	unsigned char err=0;
        
        unsigned char devAddress = pca9629config->deviceAddress;


        // Configuration du registre dans le sens horaire
        err += i2c_write(0, devAddress, 0x0f, data & 0x00FF);           // Défini le nombre de rotation dans le registre LOW    
        return(err);
}


/**
 * \brief int PCA9629_StepperMotorPulseWidth, Set the pulse width in CW and CCW direction
 * between 2mS (500Hz) and 22.5mS (44Hz)
 * \param handler to PCA9629 configuration structure
 * \return code error
 */

int PCA9629_StepperMotorPulseWidth(device_pca9629 *pca9629config, int data){
   	unsigned char err=0;

        unsigned char devAddress = pca9629config->deviceAddress;

        
        // Configuration du registre dans le sens horaire
        err+= i2c_write(0, devAddress, 0x16, data & 0x00FF);         // CWPWL - Vitesse / Largeur d'impulsion pour CW
        err+= i2c_write(0, devAddress, 0x17, (data & 0xFF00)>>8);    // CWPWH
        
        err+= i2c_write(0, devAddress, 0x18, data & 0x00FF);         // CCWPWL - Vitesse / Largeur d'impulsion pour CCW
        err+= i2c_write(0, devAddress, 0x19, (data & 0xFF00)>>8);    // CCWPWH
        return(err);
}

 int PCA9629_StepperDriveMode(device_pca9629 *pca9629config, unsigned char data){
   	unsigned char err=0;
    unsigned char devAddress = pca9629config->deviceAddress;

    data = ((data << 6) & (unsigned char)0xC0) | 0x10;

    err+= i2c_write(0, devAddress, 0x0B, data);         //  OP_CFG_PHS Change Phase control register and motor drive output
    return(err);
 }

  int PCA9629_GPIOConfig(device_pca9629 *pca9629config, unsigned char data){
   	unsigned char err=0;
    unsigned char devAddress = pca9629config->deviceAddress;

    //data = ((data << 6) & (unsigned char)0xC0) | 0x10;

    err+= i2c_write(0, devAddress, 0x03, data);         //  Configure PCA9629 GPIO as input or output
    return(err);
 }
  
/**
 * \brief PCA9629 set output state on specified input channel, the function read port state before rewrite
 * \param pointer on the configuration structure
 * \param channel, specify the channel to set state
 * \param state, state to apply on output
 * \return code error
 */
int PCA9629_setChannel(device_pca9629 *pca9629config, unsigned char channel, unsigned char state){
    unsigned char err =0;
    int PCA9629_GPIO_STATE;
    int PCA9629_GPIO_MODE_IO;
    unsigned char GPIOCFGREG;
    
    unsigned char deviceAddress = pca9629config->deviceAddress;
    
    // Get the PORT x GPIO mode (shared register))
    err += i2c_readByte(0, deviceAddress, 0x03, &PCA9629_GPIO_MODE_IO);
    
    // Get the PORT x Value before update
    err += i2c_readByte(0, deviceAddress, 0x07, &PCA9629_GPIO_STATE);
    
    if(state)
        PCA9629_GPIO_STATE |= (0x01<<channel);
    else
        PCA9629_GPIO_STATE &= (0xFF-(0x01 << channel));
    
    
    GPIOCFGREG = PCA9629_GPIO_MODE_IO & 0x0F;               // Rewrite mode
    GPIOCFGREG |= (PCA9629_GPIO_STATE & 0x0F) << 4;         // Write the new value
                
    err += i2c_write(0, deviceAddress, 0x03, GPIOCFGREG);
    
    return err;
}  

/**
 * \brief PCA9629 read input state on specified input channel
 * \param pointer on the configuration structure
 * \param channel, specify the channel to get state
 * \return code error
 */
int PCA9629_getChannel(device_pca9629 *pca9629config, unsigned char channel){
    unsigned char err =0;
    unsigned char deviceAddress = pca9629config->deviceAddress;
    int PCA9629_GPIO_STATE = 0;
    unsigned char value=0;
      
    // Get the PORT Value
    err += i2c_readByte(0, deviceAddress, 0x07, &PCA9629_GPIO_STATE);
    
    if(PCA9629_GPIO_STATE & (0x01<<channel))
        value = 1;
    else 
        value = 0;

    if(!err)
        return value;
    else 
        return -1;    
}

#endif