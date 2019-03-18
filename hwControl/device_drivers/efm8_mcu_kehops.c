/**
 * \file efm8_mcu_kehops.h
 * \brief efm8bb microcontroller with kehops firmware
 * \author Raphael Thurnherr
 * \version 0.1
 * \date 18.03.2019
 *
 * Library to get sonar, counter and din data
 * 
 */

// REGISTER DEFINITION FOR EFM8 MICROCONTROLLER

#define FIRMWARE_REG                        0x01
#define BOARDTYPE_REG                       0x00
#define DIN_REG                             0x04
#define SON0                                0x08
#define VOLT0                               0x0E
#define ENC_FREQ0                           0x13
#define ENC_CNT1_RESET                      0x24
#define ENC_CNT1                            0x14    
#define ENC_FREQ1                           0x17
#define ENC_CNT0_RESET                      0x28
#define ENC_CNT0                            0x18

#include "efm8_mcu_kehops.h"
#include <onion-i2c.h>

/**
 * \brief EFM8BB_readSonarDistance, Get the measured distance in mm by the sonar type (HC-SR04)
 * \param pointer on the configuration structure
 * \return code error
 */
int EFM8BB_kehops_getSonarDistance(device_efm8McuKehops *efm8bbconfig){
    char err;
    int SonarDistance_mm;
    int mmMSB;
    int mmLSB;					

    unsigned char deviceAddress = efm8bbconfig->deviceAddress;
    SonarDistance_mm=0;							// RAZ de la variable distance

    err=i2c_readByte(0, deviceAddress, SON0, &mmLSB);
    err+=i2c_readByte(0, deviceAddress, SON0+1, &mmMSB);

    if(!err){              
            SonarDistance_mm=((mmMSB<<8) & 0xFF00) + mmLSB;
            return SonarDistance_mm;
    }else{
        printf("EFM8BB_readSonarDistance() -> Read error\n");
        return -1;
    }
}


/**
 * \brief EFM8BB_readBatteryVoltage, Get the voltage value in mV reand on the MCU ADC input
 * \param pointer on the configuration structure
 * \return code error
 */
int EFM8BB_kehops_getVoltage(device_efm8McuKehops *efm8bbconfig){
    char err =0;
    int batteryVoltage_mV;
    int mVMSB;
    int mVLSB;
    unsigned char deviceAddress = efm8bbconfig->deviceAddress;
    batteryVoltage_mV=0;							// RAZ de la variable

    err=i2c_readByte(0, deviceAddress, VOLT0, &mVLSB);
    err+=i2c_readByte(0, deviceAddress, VOLT0+1, &mVMSB);
    if(!err){
            batteryVoltage_mV=((mVMSB<<8) & 0xFF00) + mVLSB;
            //printf("                       Battery: %d\n", batteryVoltage_mV);
            return batteryVoltage_mV;
    }else{
        printf("EFM8BB_readBatteryVoltage() -> Read error\n");
        return -1;
    }
}

/**
 * \brief EFM8BB_kehops_getFrequency, Get the frequency measured by the MCU on input
 * \param pointer on the configuration structure
 * \return code error
 */
int EFM8BB_kehops_getFrequency(device_efm8McuKehops *efm8bbconfig, unsigned char channel){
    char err = 0, regAddr = 0;
    int freqLSB=0;
    int freqMSB=0;
    int frequency = 0;
    unsigned char deviceAddress = efm8bbconfig->deviceAddress;

    if(channel == 0) regAddr = ENC_FREQ0;
    else regAddr = ENC_FREQ1;

    // RAZ de la variable
    err += i2c_readByte(0, deviceAddress, regAddr, &freqLSB);
    //err += i2c_readByte(0, EFM8BB, regAddr+1, &freqMSB);

    //frequency = ((freqMSB<<8) && 0xFF00 )+ freqLSB;

    frequency = freqLSB;

    if(!err){    
            return frequency;
    }else{
        printf("EFM8BB_readFrequency() -> Read error\n");
        return -1;
    }
}

/**
 * \brief EFM8BB_kehops_getCounter, Get the counter values measured by the MCU on input
 * \param pointer on the configuration structure
 * \return code error
 */
int EFM8BB_kehops_getCounter(device_efm8McuKehops *efm8bbconfig, unsigned char channel){
    char err=0, regAddr=0;
    int pulseCount;
    int pcMSB=0;
    int pcLSB=0;
    unsigned char deviceAddress = efm8bbconfig->deviceAddress;

    if(channel==0) {
            regAddr = ENC_CNT0;
    }
    else {
            regAddr = ENC_CNT1;
    }

    pulseCount=0;							// RAZ de la variable

    err=i2c_readByte(0, deviceAddress, regAddr, &pcLSB);
    usleep(1000);
    err+=i2c_readByte(0, deviceAddress, regAddr+1, &pcMSB);

    pulseCount = ((pcMSB<<8) & 0xFF00) + pcLSB;

    if(!err){
            return pulseCount;
    }else{
        printf("EFM8BB_readPulseCounter() -> Read error\n");
        return -1;
    }
}

/**
 * \brief EFM8BB_kehops_clearCounter, Clear the pulse counter register
 * \param pointer on the configuration structure
 * \return code error
 */
int EFM8BB_kehops_clearCounter(device_efm8McuKehops *efm8bbconfig, unsigned char channel){
    char err, regAddr;
    int pulseCount;
    unsigned char deviceAddress = efm8bbconfig->deviceAddress;

    if(channel==0) {
            regAddr = ENC_CNT0_RESET;
    }
    else {
            regAddr = ENC_CNT1_RESET;
    }

    pulseCount=0;							// RAZ de la variable
    err +=i2c_readByte(0, deviceAddress, regAddr, &pulseCount);
    if(!err){
            return pulseCount;
    }else{
        printf("EFM8BB_clearWheelDistance() -> Read error\n");
        return -1;
    }
}

/**
 * \brief EFM8BB_kehops_getDinState, Get the digital input states on the MCU inputs
 * \param pointer on the configuration structure
 * \return code error
 */
char EFM8BB_kehops_getDinState(device_efm8McuKehops *efm8bbconfig){
    char err;
    char inputState=0;
    unsigned char deviceAddress = efm8bbconfig->deviceAddress;

    err = i2c_readByte(0, deviceAddress, DIN_REG, &inputState);

    if(!err){
            return inputState;
    }else{
        printf("EFM8BB_readDigitalInput() -> Read error\n");
        return -1;
    }
}


/**
 * \brief EFM8BB_getFirmwareVersion, Get the firmware version of MCU software
 * \param pointer on the configuration structure
 * \return code error
 */
int EFM8BB_kehops_getFirmwareVersion(device_efm8McuKehops *efm8bbconfig){
    char err;
    int value=-1;
    unsigned char deviceAddress = efm8bbconfig->deviceAddress;

    err = i2c_readByte(0, deviceAddress, FIRMWARE_REG, &value);

    if(!err){
            return value;
    }else{
        printf("EFM8BB_getFirmwareVersion() -> Read error\n");
        return -1;
    }
}

/**
 * \brief EFM8BB_getBoardType, Get the boardTypeVersion read by the MCU on the port pins
 * \param pointer on the configuration structure
 * \return code error
 */
int EFM8BB_kehops_getBoardType(device_efm8McuKehops *efm8bbconfig){
    char err;
    int value=-1;
    unsigned char deviceAddress = efm8bbconfig->deviceAddress;

    err = i2c_readByte(0, deviceAddress, BOARDTYPE_REG, &value);
    if(!err){
            return value;
    }else{
        printf("EFM8BB_getBoardType() -> Read error\n");
        return -1;
    }
}

