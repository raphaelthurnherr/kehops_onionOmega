
#ifndef I2CSIMU

#include "boardHWctrl.h"
#include <onion-i2c.h>
#include "../buggy_descriptor.h"

unsigned char buggyBoardInit(void);                             // Initialisation of the board (PWM Driver, GPIO driver, etc..)

//================================================================================
// BUGGYBOARDINIT
// Initialisation of the board (PWM Driver, GPIO driver, etc..)
//================================================================================

unsigned char buggyBoardInit(void){
	unsigned char err;
        
        // Reset la distance de la carte EFM8BB
	/*
        EFM8BB_clearWheelDistance(MOTOR_ENCODER_LEFT);
	EFM8BB_clearWheelDistance(MOTOR_ENCODER_RIGHT);
        */
	MCP2308_DCmotorState(1);				// Set the HDRIVER ON
	if(err){
            printf("Kehops I2C devices initialization with %d error\n", err);
            return 0;   // Erreur
        }
	else
            return 1;
}


//================================================================================
// DCMOTORSTATE
// Defini l'etat general de tout les moteurs DC (Driver pont en H)
//
//================================================================================

void MCP2308_DCmotorState(unsigned char state){
	int MCP2308_GPIO_STATE;
        char err;
        
        err=i2c_readByte(0, MCP2308, 0x09, &MCP2308_GPIO_STATE);
        
	if(state) MCP2308_GPIO_STATE |= 0x10;                                   // Activation du driver pont en H
	else MCP2308_GPIO_STATE &= 0xEF;					// d�sactivation du driver pont en H

        i2c_write(0, MCP2308, 0x0A, MCP2308_GPIO_STATE);
}


//================================================================================
// DCMOTORSETROTATION
// D�fini le sense de rottion d'un moteur DC (sens horaire, antihoraire ou stop)
//================================================================================

void MCP2308_DCmotorSetRotation(unsigned char motorAdr, char direction){
	int MCP2308_GPIO_STATE;

	// Sélection du chip d'entrée/sortie qui pilote le pont en H
	i2c_readByte(0, MCP2308, 0x09, &MCP2308_GPIO_STATE);
        
        // le bit n�n�ssaire
	//	SELECTION DU MOTEUR No 0
	if(motorAdr==PCA_DCM0){
		// Désactive la commande du moteur
		// avant de changer de sens de rotation
		MCP2308_GPIO_STATE &= 0xF9;

                i2c_write(0, MCP2308, 0x0A, MCP2308_GPIO_STATE);
                
		// S�l�ction du sens de rotation du moteur ou OFF
		switch(direction){
			case MCW 	 :  MCP2308_GPIO_STATE |= 0x02; break;
			case MCCW 	 :  MCP2308_GPIO_STATE |= 0x04; break;
			case MSTOP 	 :  MCP2308_GPIO_STATE |= 0x00; break;
			default		 : ;break;
		}

                i2c_write(0, MCP2308, 0x0A, MCP2308_GPIO_STATE);
        }

//	SELECTION DU MOTEUR No 1
	if(motorAdr==PCA_DCM1){

		// D�sactive la commande du moteur
		// avant de changer de sens de rotation
		MCP2308_GPIO_STATE &= 0xF6;										// Force H-Bridge Off for motor 1

                i2c_write(0, MCP2308, 0x0A, MCP2308_GPIO_STATE);
		// S�l�ction du sens de rotation du moteur ou OFF
		switch(direction){
			case MCW 	 :  MCP2308_GPIO_STATE |= 0x01; break;
			case MCCW 	 :  MCP2308_GPIO_STATE |= 0x08; break;
			case MSTOP 	 :  MCP2308_GPIO_STATE |= 0x00; break;
			default		 : ;break;
		}

                i2c_write(0, MCP2308, 0x0A, MCP2308_GPIO_STATE);
        }

}

//================================================================================
// DCMOTORSETSPEED
// D�fini le duty cyle � appliquer sur les sorties du chip PWM (0..100%)
// motorAdr: Adresse de sortie du contr�leur PWM sur lequel doit �tre appliqu� le dutyCycle
//================================================================================

void PCA9685_DCmotorSetSpeed(unsigned char motorAdr, unsigned char dutyCycle){
	unsigned int power;
	unsigned char PowerLow;
	unsigned char PowerHigh;

	// Conversion du dutyclycle en valeur � appliquer au contr�leur PWM
	power = (4095*dutyCycle)/100;
	PowerLow = power&0x00FF;;
	PowerHigh = (power&0x0F00) >>8;
        
	i2c_write(0, PCA9685, motorAdr, PowerLow);
        i2c_write(0, PCA9685, motorAdr+1, PowerHigh);
}


// -------------------------------------------------------------------
// GETFIRMWAREVERSION
// RECUPERE LA VERSION FIRMWARE DU MCU
// -------------------------------------------------------------------
int EFM8BB_getFirmwareVersion(void){
	char err;
	int value=-1;
        
        err = i2c_readByte(0, EFM8BB, FIRMWARE_REG, &value);

	if(!err){
		return value;
	}else{
            printf("EFM8BB_getFirmwareVersion() -> Read error\n");
            return -1;
        }
}

// -------------------------------------------------------------------
// GETBOARDTYPE
// Recupere le type de montage de la carte
// -------------------------------------------------------------------
int EFM8BB_getBoardType(void){
	char err;
	int value=-1;
        
        err = i2c_readByte(0, EFM8BB, BOARDTYPE_REG, &value);
	if(!err){
		return value;
	}else{
            printf("EFM8BB_getBoardType() -> Read error\n");
            return -1;
        }
}


// -------------------------------------------------------------------
// BH1445GETRGBVALUE
// RECUPERE LA VALEUR DU REGISTRE POUR LA COULEUR:
// RED =0, GREEN=1, BLUE=2, CLEAR=3
// -------------------------------------------------------------------
int BH1745_getRGBvalue(unsigned char sensorNb, int color){
	char err;
	int value=-1;
        int RGBregAdr = 0x56;  // Registre CLEAR LSB par defaut 
        unsigned char SensorAdr=BH1745_0;
        
        unsigned int pcMSB=0;
        unsigned int pcLSB=0;
        
        switch(sensorNb){
            case RGBC_SENS_0: SensorAdr=BH1745_0;break;
            case RGBC_SENS_1: SensorAdr=BH1745_1;break;
            default: SensorAdr=BH1745_0;break;
        }
        
        switch(color){
            case RED :   RGBregAdr=0x50; break;
            case GREEN : RGBregAdr=0x52; break;
            case BLUE :  RGBregAdr=0x54; break;
            case CLEAR : RGBregAdr=0x56; break;
            
            default : value=-1; break;
        }
        
        err = i2c_readByte(0, SensorAdr, RGBregAdr, &pcLSB);
        err+= i2c_readByte(0, SensorAdr, RGBregAdr+1, &pcMSB);
                
	if(!err){
            value = pcLSB + (pcMSB<<8);
		return value;
	}else{
            printf("BH1745_getRGBvalue() -> Read error\n");
            return -1;
        }
}
#endif