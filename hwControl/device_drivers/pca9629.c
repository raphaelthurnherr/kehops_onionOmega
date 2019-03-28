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


// REGISTER DEFINITION FOR PCA9629 IC

#define  MODE           0x00          // Mode register
#define  SUBADR1        0x01          // I2C-bus subaddress 1
#define  SUBADR2        0x02          // I2C-bus subaddress 2
#define  SUBADR3        0x03          // I2C-bus subaddress 3
#define  ALLCALLADR     0x04          // All Call I2C-bus address
#define  WDTOI          0x05          // Watchdog time-out interval register
#define  WDCNTL         0x06          // Watchdog control register
#define  IP             0x07          // read only Input Port register 
#define  INTSTAT        0x08          // read only Interrupt status register 
#define  OP             0x09          // Output Port register
#define  IOC            0x0A          // I/O Configuration register
#define  MSK            0x0B          // Mask interrupt register
#define  CLRINT         0x0C          // write only Clear interrupts 
#define  INTMODE        0x0D          // Interrupt mode register
#define  INT_ACT_SETUP  0x0E          // Interrupt action setup control register
#define  INT_MTR_SETUP  0x0F          // Interrupt motor setup control register
#define  INT_ES_SETUP   0x10          // Interrupt extra steps setup control register
#define  INT_AUTO_CLR   0x11          // Interrupt auto clear control register
#define  SETMODE        0x12          // Output state on STOP
#define  PHCNTL         0x13          // Phase control register
#define  SROTNL         0x14          // Steps per rotation low byte
#define  SROTNH         0x15          // Steps per rotation high byte
#define  CWPWL          0x16          // Step pulse width for CW rotation low byte
#define  CWPWH          0x17          // Step pulse width for CW rotation high byte
#define  CCWPWL         0x18          // Step pulse width for CCW rotation low byte
#define  CCWPWH         0x19          // Step pulse width for CCW rotation high byte
#define  CWSCOUNTL      0x1A          // Number of steps CW low byte
#define  CWSCOUNTH      0x1B          // Number of steps CW high byte
#define  CCWSCOUNTL     0x1C          // Number of steps CCW low byte
#define  CCWSCOUNTH     0x1D          // Number of steps CCW high byte
#define  CWRCOUNTL      0x1E          // Number of rotations CW low byte
#define  CWRCOUNTH      0x1F          // Number of rotations CW high byte
#define  CCWRCOUNTL     0x20          // Number of rotations CCW low byte
#define  CCWRCOUNTH     0x21          // Number of rotations CCW high byte
#define  EXTRASTEPS0    0x22          // Count value for extra steps or rotations for INTP0
#define  EXTRASTEPS1    0x23          // Count value for extra steps or rotations for INTP1
#define  RMPCNTL        0x24          // Ramp control register
#define  LOOPDLY        0x25          // Loop delay time register
#define  MCNTL          0x26          // Control start/stop motor

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
    
    unsigned char devAddress = pca9629config->deviceAddress;
    
    err+= i2c_write(0, devAddress, 0x00, 0x20);    // MODE - Configuration du registre MODE (pin INT désactivée, Allcall Adr. désactivé)
    err+= i2c_write(0, devAddress, 0x01, 0xFF);    // WDTOI
    err+= i2c_write(0, devAddress, 0x02, 0x00);    // WDCNTL
    err+= i2c_write(0, devAddress, 0x03, 0x0F);    // IO_CFG
    err+= i2c_write(0, devAddress, 0x04, 0x10);    // INTMODE
    err+= i2c_write(0, devAddress, 0x05, 0x1F);    // MSK
    err+= i2c_write(0, devAddress, 0x06, 0x00);    // INTSTAT
    //err+= i2c_write(0, PCA9629, 0x07, 0x);    // IP
    err+= i2c_write(0, devAddress, 0x08, 0x00);    // INT_MTR_ACT
    err+= i2c_write(0, devAddress, 0x09, 0x00);    // EXTRASTEPS0
    err+= i2c_write(0, devAddress, 0x0A, 0x00);    // EXTRASTEPS1
    err+= i2c_write(0, devAddress, 0x0B, 0x10);    // OP_CFG_PHS
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
    err+= i2c_write(0, devAddress, 0x16, 0x9A);    // CWPWL - Vitesse / Largeur d'impulsion pour CW
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
        err += i2c_write(0, devAddress, 0x1A, data & 0x00FF);           // Défini le nombre de rotation dans le registre LOW    
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
        err += i2c_readByte(0, devAddress, 0x1A, &regState);
        
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
        err += i2c_write(0, devAddress, 0x0F, data & 0x00FF);           // Défini le nombre de rotation dans le registre LOW    
        return(err);
}


/**
 * \brief int PCA9629_StepperMotorMode, Set the pulse width in CW and CCW direction
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