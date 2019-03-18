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

#ifndef EFM8_MCU_KEHOPS_H
#define EFM8_MCU_KEHOPS_H

/**
 * \struct efm8_mcu_kehops [efm8_mcu_kehops.h] Configuration structure definition
 */
typedef struct efm8_mcu_kehops{
    unsigned char deviceAddress;                // Bus device address
} device_efm8McuKehops;

/**
 * \brief EFM8BB_getFirmwareVersion, Get the firmware version of MCU software
 * \param pointer on the configuration structure
 * \return code error
 */
extern int EFM8BB_kehops_getFirmwareVersion(device_efm8McuKehops *efm8bbconfig);

/**
 * \brief EFM8BB_getBoardType, Get the boardTypeVersion read by the MCU on the port pins
 * \param pointer on the configuration structure
 * \return code error
 */
extern int EFM8BB_kehops_getBoardType(device_efm8McuKehops *efm8bbconfig);

/**
 * \brief EFM8BB_readSonarDistance, Get the measured distance in mm by the sonar type (HC-SR04)
 * \param pointer on the configuration structure
 * \return code error
 */
extern int EFM8BB_kehops_getSonarDistance(device_efm8McuKehops *efm8bbconfig);

/**
 * \brief EFM8BB_readBatteryVoltage, Get the voltage value in mV reand on the MCU ADC input
 * \param pointer on the configuration structure
 * \return code error
 */
extern int EFM8BB_kehops_getVoltage(device_efm8McuKehops *efm8bbconfig);

/**
 * \brief EFM8BB_kehops_getFrequency, Get the frequency measured by the MCU on input
 * \param pointer on the configuration structure
 * \return code error
 */
extern int EFM8BB_kehops_getFrequency(device_efm8McuKehops *efm8bbconfig, unsigned char channel);

/**
 * \brief EFM8BB_kehops_getCounter, Get the counter values measured by the MCU on input
 * \param pointer on the configuration structure
 * \return code error
 */
extern int EFM8BB_kehops_getCounter(device_efm8McuKehops *efm8bbconfig, unsigned char channel);

/**
 * \brief EFM8BB_kehops_getDinState, Get the digital input states on the MCU inputs
 * \param pointer on the configuration structure
 * \return code error
 */
extern char EFM8BB_kehops_getDinState(device_efm8McuKehops *efm8bbconfig);

/**
 * \brief EFM8BB_kehops_clearCounter, Clear the pulse counter register
 * \param pointer on the configuration structure
 * \return code error
 */
extern int EFM8BB_kehops_clearCounter(device_efm8McuKehops *efm8bbconfig, unsigned char channel);


#endif /* EFM8_MCU_KEHOPS_H */
