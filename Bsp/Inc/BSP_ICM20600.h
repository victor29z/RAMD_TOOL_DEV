/**
  ******************************************************************************
  * @FileName:		BSP_ICM20600.h
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
#ifndef __BSP_ICM20600_H
#define __BSP_ICM20600_H


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
}ICM20600_Raw_Data;

//Calibrated MPU sensor data
typedef struct
{
	S_FLOAT_XYZ gyro;
	S_FLOAT_XYZ acc;
	S_FLOAT_XYZ mag;
	float temp;
}ICM20600_Cali_Data;


/* Macros --------------------------------------------------------------------*/
#define ICM20600_spi 				hspi2	//Map ICM20600 to SPI2

/***************************************************************
    ICM20600 Register
 ***************************************************************/
#define SELF_TEST_X_GYRO		0X00
#define SELF_TEST_Y_GYRO		0X01
#define SELF_TEST_Z_GYRO		0X02

#define ICM20600_XG_OFFS_TC_H           0x04
#define ICM20600_XG_OFFS_TC_L           0x05
#define ICM20600_YG_OFFS_TC_H           0x07
#define ICM20600_YG_OFFS_TC_L           0x08
#define ICM20600_ZG_OFFS_TC_H           0x0a
#define ICM20600_ZG_OFFS_TC_L           0x0b

#define SELF_TEST_X_ACCEL		0X0D
#define SELF_TEST_Y_ACCEL		0X0E
#define SELF_TEST_Z_ACCEL		0X0F

#define XG_OFFSET_H					0X13
#define XG_OFFSET_L					0X14
#define YG_OFFSET_H					0X15
#define YG_OFFSET_L					0X16
#define ZG_OFFSET_H					0X17
#define ZG_OFFSET_L					0X18

#define SMPLRT_DIV					0X19 //�����ǲ����� ����ֵΪ0007  1000/(1+7)=125HZ
#define CONFIG							0X1A //��ͨ�˲���  ����ֵ0x06 5hz
#define GYRO_CONFIG					0X1B //�����ǲ�����Χ 0018 ����2000��
#define ACCEL_CONFIG				0X1C //���ٶȼƲ�����Χ 0018 ����16g
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

#define PWR_MGMT_1					0X6B //��Դ����1 ����ֵΪ0x01
#define PWR_MGMT_2					0X6C //��Դ����2 ����ֵΪ0X00

#define WHO_AM_I						0X75 //����ID ICM20600Ĭ��IDΪ0X71
#define WHO_AM_MAG					0X00 //����ID ICM20600Ĭ��IDΪ0X71
#define USER_CTRL						0X6A //�û����� ��Ϊ0X10ʱʹ��SPIģʽ


#define Dummy_Byte                  0xFF	//slave doesn't recognize 0xFF

//SPI Enable control
#define SPI2_CS_GPIO_Port						GPIOB
#define SPI2_CS_Pin									GPIO_PIN_12

#define ICM20600_SPI_CS_ENABLE()            HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_RESET)
#define ICM20600_SPI_CS_DISABLE()           HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_SET)

/* Private Variables ---------------------------------------------------------*/

/* External Variables --------------------------------------------------------*/
extern uint8_t 	ICM20600_MAG_BUF[6];
extern S_INT16_XYZ GYRO_OFFSET;
extern S_INT16_XYZ ACC_OFFSET;				
extern S_INT16_XYZ ICM20600_ACC_LAST;
extern S_INT16_XYZ ICM20600_GYRO_LAST;
extern S_INT16_XYZ ICM20600_MAG_LAST;

extern ICM20600_Raw_Data icm20600_raw_data;
extern ICM20600_Cali_Data icm20600_cali_data;

/* Exported Functions --------------------------------------------------------*/
extern uint8_t BSP_IMU_Found(void);

extern uint8_t BSP_ICM20600_Init(void);
//extern uint8_t BSP_AK8963_Init(void);
extern uint8_t BSP_ICM20600_Write_Reg(uint8_t reg,uint8_t value);
extern uint8_t BSP_ICM20600_Read_Reg(uint8_t reg);
extern uint8_t BSP_ICM20600_SPI_ReadWriteByte(uint8_t TxData);//SPI���߶�дһ���ֽ�

extern void BSP_ICM20600_Read_Gyro(void);
extern void BSP_ICM20600_Read_Acc(void);
//extern void BSP_ICM20600_Read_Mag(void);
extern void BSP_ICM20600_Read_Temp(void);
extern void BSP_ICM20600_Read_All(void);
void BSP_ICM20600_Cyclical_Update(void);
extern void BSP_ICM20600_Test(void);


#endif


/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/

