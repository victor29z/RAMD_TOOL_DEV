/**
  ******************************************************************************
  * @FileName:		BSP_MPU9250.h
  * @Author:		Hui
  * @Version:		V1.0.0
  * @Date:			03-11-2020
  * @Description:   
  * @Others:
  ******************************************************************************
  * @Copyright(C), 2020, Smokie Robotics, Inc
  ******************************************************************************
  * @History:
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_MPU9250_H
#define __BSP_MPU9250_H


/* Private Includes ----------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "spi.h"
#include "BSP_LED.h"

/* Private Typedefs ----------------------------------------------------------*/
typedef struct
{
	int16_t x;
	int16_t y;
	int16_t z;
}S_INT16_XYZ;

typedef struct
{
	float x;
	float y;
	float z;
}S_FLOAT_XYZ;

//Raw MPU sensor data
typedef struct
{
	S_INT16_XYZ gyro;
	S_INT16_XYZ acc;
	S_INT16_XYZ mag;
	int16_t temp;
}MPU9250_Raw_Data;

//Calibrated MPU sensor data
typedef struct
{
	S_FLOAT_XYZ gyro;
	S_FLOAT_XYZ acc;
	S_FLOAT_XYZ mag;
	float temp;
}MPU9250_Cali_Data;


/* Macros --------------------------------------------------------------------*/
#define MPU9250_spi 				hspi2	//Map MPU9250 to SPI2

//�Ĵ�������
#define SELF_TEST_X_GYRO		0X00
#define SELF_TEST_Y_GYRO		0X01
#define SELF_TEST_Z_GYRO		0X02

#define SELF_TEST_X_ACCEL		0X0D
#define SELF_TEST_Y_ACCEL		0X0E
#define SELF_TEST_Z_ACCEL		0X0F

#define XG_OFFSET_H					0X13
#define XG_OFFSET_L					0X14
#define YG_OFFSET_H					0X15
#define YG_OFFSET_L					0X16
#define ZG_OFFSET_H					0X17
#define ZG_OFFSET_L					0X18

#define SMPLRT_DIV					0X19 //�����ǲ����� ����ֵΪ0X07  1000/(1+7)=125HZ
#define CONFIG							0X1A //��ͨ�˲���  ����ֵ0x06 5hz
#define GYRO_CONFIG					0X1B //�����ǲ�����Χ 0X18 ����2000��
#define ACCEL_CONFIG				0X1C //���ٶȼƲ�����Χ 0X18 ����16g
#define ACCEL_CONFIG2				0X1D //���ٶȼƵ�ͨ�˲��� 0x06 5hz

#define LP_ACCEL_ODR				0X1E
#define WOM_THR							0X1F
#define FIFO_EN							0X23

#define ACCEL_XOUT_H				0X3B  //���ٶȼ��������
#define ACCEL_XOUT_L				0X3C
#define ACCEL_YOUT_H				0X3D
#define ACCEL_YOUT_L				0X3E
#define ACCEL_ZOUT_H				0X3F
#define ACCEL_ZOUT_L				0X40

#define TEMP_OUT_H					0X41  //�¶ȼ��������
#define TEMP_OUT_L					0X42

#define GYRO_XOUT_H					0X43  //�������������
#define GYRO_XOUT_L					0X44
#define GYRO_YOUT_H					0X45
#define GYRO_YOUT_L					0X46
#define GYRO_ZOUT_H					0X47
#define GYRO_ZOUT_L					0X48

#define MAG_XOUT_L          0x4A	//0X03; 0x49 is ST1	
#define MAG_XOUT_H          0x4B	//0X04
#define MAG_YOUT_L          0x4C	//0X05
#define MAG_YOUT_H          0x4D	//0X06
#define MAG_ZOUT_L          0x4E	//0X07
#define MAG_ZOUT_H          0x4F	//0X08


#define PWR_MGMT_1					0X6B //��Դ����1 ����ֵΪ0x00
#define PWR_MGMT_2					0X6C //��Դ����2 ����ֵΪ0X00

#define WHO_AM_I						0X75 //����ID MPU9250Ĭ��IDΪ0X71
#define WHO_AM_MAG					0X00 //����ID MPU9250Ĭ��IDΪ0X71
#define USER_CTRL						0X6A //�û����� ��Ϊ0X10ʱʹ��SPIģʽ

#define MAG_I2C_SLV0_ADDR 			0x25
#define MAG_I2C_SLV0_REG				0x26
#define MAG_I2C_SLV0_CTRL				0x27
#define MAG_MODE_CTRL1      		0X0A
#define MAG_I2C_MST_CTRL				0x24
#define MAG_I2C_MST_DELAY_CTRL 	0x67
#define MAG_I2C_SLV0_DO 				0x63
#define MAG_INT_PIN_CFG 				0x37
#define MAG_EXT_SENS_DATA_00 		0x49

#define MAG_I2C_ADDR        		0x0C
#define MAG_WIA									0x00

// Read-only Reg
#define AK8963_WIA                  ((uint8_t)0x00)
#define AK8963_INFO                 ((uint8_t)0x01)
#define AK8963_ST1                  ((uint8_t)0x02)
#define AK8963_HXL                  ((uint8_t)0x03)
#define AK8963_HXH                  ((uint8_t)0x04)
#define AK8963_HYL                  ((uint8_t)0x05)
#define AK8963_HYH                  ((uint8_t)0x06)
#define AK8963_HZL                  ((uint8_t)0x07)
#define AK8963_HZH                  ((uint8_t)0x08)
#define AK8963_ST2                  ((uint8_t)0x09)
// Write/Read Reg
#define AK8963_CNTL1                ((uint8_t)0x0A)
#define AK8963_CNTL2                ((uint8_t)0x0B)
#define AK8963_ASTC                 ((uint8_t)0x0C)
#define AK8963_TS1                  ((uint8_t)0x0D)
#define AK8963_TS2                  ((uint8_t)0x0E)
#define AK8963_I2CDIS               ((uint8_t)0x0F)
// Read-only Reg ( ROM )
#define AK8963_ASAX                 ((uint8_t)0x10)
#define AK8963_ASAY                 ((uint8_t)0x11)
#define AK8963_ASAZ                 ((uint8_t)0x12)

#define Dummy_Byte                  0xFF	//slave doesn't recognize 0xFF

//SPI Enable control
#define MPU9250_SPI_CS_ENABLE()            HAL_GPIO_WritePin(MPU_SPI_CS_GPIO_Port, MPU_SPI_CS_Pin, GPIO_PIN_RESET)
#define MPU9250_SPI_CS_DISABLE()           HAL_GPIO_WritePin(MPU_SPI_CS_GPIO_Port, MPU_SPI_CS_Pin, GPIO_PIN_SET)

/* Private Variables ---------------------------------------------------------*/

/* External Variables --------------------------------------------------------*/
extern uint8_t 	MPU9250_MAG_BUF[6];
extern S_INT16_XYZ GYRO_OFFSET;
extern S_INT16_XYZ ACC_OFFSET;				
extern S_INT16_XYZ MPU9250_ACC_LAST;
extern S_INT16_XYZ MPU9250_GYRO_LAST;
extern S_INT16_XYZ MPU9250_MAG_LAST;

extern MPU9250_Raw_Data mpu9250_raw_data;

/* Exported Functions --------------------------------------------------------*/
extern uint8_t BSP_IMU_Found(void);

extern uint8_t BSP_MPU9250_Init(void);
extern uint8_t BSP_AK8963_Init(void);
extern uint8_t BSP_MPU9250_Write_Reg(uint8_t reg,uint8_t value);
extern uint8_t BSP_MPU9250_Read_Reg(uint8_t reg);
extern uint8_t BSP_MPU9250_SPI_ReadWriteByte(uint8_t TxData);//SPI���߶�дһ���ֽ�

extern void BSP_MPU9250_Read_Gyro(void);
extern void BSP_MPU9250_Read_Acc(void);
extern void BSP_MPU9250_Read_Mag(void);
extern void BSP_MPU9250_Read_Temp(void);
extern void BSP_MPU9250_Read_All(void);

extern void BSP_MPU9250_Debug(void);

#endif


/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/

