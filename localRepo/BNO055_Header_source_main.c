
//  HEADER FILE


#ifndef BNO055_H
#define BNO055_H

#include "stm32g474re_hal.h"

#define BNO055_ADDR (0x28 << 1)

/* Registers */
#define BNO055_CHIP_ID 0x00
#define BNO055_OPR_MODE 0x3D
#define BNO055_PWR_MODE 0x3E
#define BNO055_SYS_TRIGGER 0x3F
#define BNO055_EULER_H_LSB 0x1A

/* Modes */
#define CONFIGMODE 0x00
#define NDOF_MODE 0x0C

void BNO055_Init(I2C_HandleTypeDef *hi2c);
void BNO055_ReadEuler(I2C_HandleTypeDef *hi2c,
                      float *heading,
                      float *roll,
                      float *pitch);

#endif

// SOURCE FILE 


#include "bno055.h"

void BNO055_Init(I2C_HandleTypeDef *hi2c)
{
    uint8_t data;

    /* Check chip ID */
    HAL_I2C_Mem_Read(hi2c, BNO055_ADDR,BNO055_CHIP_ID,   1, &data, 1, HAL_MAX_DELAY);

                                   
    HAL_Delay(100);

    /* Set CONFIG mode */
    data = CONFIGMODE;
    HAL_I2C_Mem_Write(hi2c, BNO055_ADDR,BNO055_OPR_MODE,1, &data, 1, HAL_MAX_DELAY);

                      
                      
    HAL_Delay(20);

    /* Set normal power mode */
    data = 0x00;
    HAL_I2C_Mem_Write(hi2c, BNO055_ADDR, BNO055_PWR_MODE,1, &data, 1, HAL_MAX_DELAY);
                     
    HAL_Delay(10);

    /* Set NDOF fusion mode */
    data = NDOF_MODE;
    HAL_I2C_Mem_Write(hi2c, BNO055_ADDR,BNO055_OPR_MODE,1, &data, 1, HAL_MAX_DELAY);
                      
    HAL_Delay(20);
}

void BNO055_ReadEuler(I2C_HandleTypeDef *hi2c,float *heading,float *roll, float *pitch)
                                       
{
    uint8_t buffer[6];

    HAL_I2C_Mem_Read(hi2c, BNO055_ADDR,BNO055_EULER_H_LSB,1,buffer,6,HAL_MAX_DELAY);
                     
    int16_t h =(buffer[1] << 8) | buffer[0];
    int16_t r =(buffer[3] << 8) | buffer[2];
    int16_t p =(buffer[5] << 8) | buffer[4];

    *heading = h / 16.0;
    *roll = r / 16.0;
    *pitch = p / 16.0;
}


// main file 


#include "main.h"
#include "bno055.h"

extern I2C_HandleTypeDef hi2c1;

float heading;
float roll;
float pitch;

int main(void)
{
  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_I2C1_Init();

  /* Initialize BNO055 */
  BNO055_Init(&hi2c1);

  while (1)
  {
      BNO055_ReadEuler(&hi2c1,&heading,&roll,&pitch);
                     
      HAL_Delay(100);
  }
}

