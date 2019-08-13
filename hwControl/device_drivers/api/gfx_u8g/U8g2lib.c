#include <onion-i2c.h>
#include "U8g2lib.h"

uint8_t u8x8_arm_linux_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
    switch(msg)
    {
        case U8X8_MSG_DELAY_NANO:            // delay arg_int * 1 nano second
            usleep(1);
            break;    
    
        case U8X8_MSG_DELAY_100NANO:        // delay arg_int * 100 nano seconds
            usleep(1);
            break;
  
        case U8X8_MSG_DELAY_10MICRO:        // delay arg_int * 10 micro seconds
            usleep(10);
            break;

        case U8X8_MSG_DELAY_MILLI:            // delay arg_int * 1 milli second
            usleep(1000);
            break;
  
        case U8X8_MSG_GPIO_AND_DELAY_INIT:  
            // Function which implements a delay, arg_int contains the amount of ms  
/*            
            // Export pin 
            exportGPIOPin(u8x8->pins[U8X8_PIN_RESET]);
            exportGPIOPin(u8x8->pins[U8X8_PIN_DC]);
            // exportGPIOPin(u8x8->pins[U8X8_PIN_CS]);
  
            // Set mode
            setGPIODirection(u8x8->pins[U8X8_PIN_RESET], GPIO_OUT);
            setGPIODirection(u8x8->pins[U8X8_PIN_DC], GPIO_OUT);
            // setGPIODirection(u8x8->pins[U8X8_PIN_CS], GPIO_OUT);
  
            // Set value
            setGPIOValue(u8x8->pins[U8X8_PIN_RESET], GPIO_HIGH);
            setGPIOValue(u8x8->pins[U8X8_PIN_DC], GPIO_HIGH);
            // setGPIOValue(u8x8->pins[U8X8_PIN_CS], GPIO_HIGH);
 */
            break;
  
        case U8X8_MSG_GPIO_CS:
            // Function to define the logic level of the CS line  
            // if(arg_int)        setGPIOValue(u8x8->pins[U8X8_PIN_CS], GPIO_HIGH);
            // else        setGPIOValue(u8x8->pins[U8X8_PIN_CS], GPIO_LOW);
            break;
  
        case U8X8_MSG_GPIO_DC:
/*   
            //Function to define the logic level of the Data/ Command line  
            if(arg_int) setGPIOValue(u8x8->pins[U8X8_PIN_DC], GPIO_HIGH);
            else setGPIOValue(u8x8->pins[U8X8_PIN_DC], GPIO_LOW);
 */ 
            break;  
  
        case U8X8_MSG_GPIO_RESET:
/*            
            //Function to define the logic level of the RESET line
            if (arg_int) setGPIOValue(u8x8->pins[U8X8_PIN_RESET], GPIO_HIGH);
            else setGPIOValue(u8x8->pins[U8X8_PIN_RESET], GPIO_LOW);
 */
            break;
  
            default:
            return 0;
    }
    return 1;
}

uint8_t u8x8_byte_arm_linux_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
    /* u8g2/u8x8 will never send more than 32 bytes between START_TRANSFER and END_TRANSFER */
    static uint8_t buffer[32];        
    static uint8_t buf_idx;
    uint8_t *data;
    
    switch(msg)
    {
        case U8X8_MSG_BYTE_SEND:
            data = (uint8_t *)arg_ptr;      
            while( arg_int > 0 )
            {
                buffer[buf_idx++] = *data;
                data++;
                arg_int--;
            }
            break;

        case U8X8_MSG_BYTE_INIT:
/*            
            i2c_device = openI2CDevice(i2c_bus);
            
 */
            //printf("I2C INIT FROM DRIVER DISPLAY: \n");
            break;

        case U8X8_MSG_BYTE_START_TRANSFER:
/*            setI2CSlave(i2c_device, u8x8_GetI2CAddress(u8x8)>>1);
            buf_idx = 0;
            // printf("I2C Address: %02x\n", u8x8_GetI2CAddress(u8x8)>>1);
 */
            buf_idx = 0;
            //i2c_writeBufferRaw(0, u8x8_GetI2CAddress(u8x8)>>1, buffer, buf_idx);
            //printf("I2C START TRANSFER FROM DRIVER DISPLAY:  ADDR:0x%2x\n", u8x8_GetI2CAddress(u8x8)>>1);
            break;

        case U8X8_MSG_BYTE_END_TRANSFER:
/*            
            I2CWriteBytes(i2c_device, buffer, buf_idx);
*/
            i2c_writeBufferRaw(0, u8x8_GetI2CAddress(u8x8)>>1, buffer, buf_idx);
            //printf("I2C WRITE BYTE FROM DRIVER DISPLAY:\n");
            break;

        default:
            return 0;
    }
    return 1;
}
