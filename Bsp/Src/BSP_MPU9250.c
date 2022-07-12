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

/* Private Includes ----------------------------------------------------------*/
#include "BSP_MPU9250.h"

/* Private Includes ----------------------------------------------------------*/

/* Private Typedefs ----------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private Variables ---------------------------------------------------------*/
uint8_t	 MPU9250_buf[22];

/* External Variables --------------------------------------------------------*/
MPU9250_Raw_Data mpu9250_raw_data = {0};

/* Exported Functions --------------------------------------------------------*/


/**
  * @brief  Try on connecting with MPU9250
  * @param  None
  * @retval 0-success; 1-fail.
  */
uint8_t BSP_IMU_Found(void)
{
	if(BSP_MPU9250_Read_Reg(WHO_AM_I)==0x11)
		return 1;
	return 0;
};


/**
  * @brief  initialize IMU, set up configuration of acc(1khz, +-4g), gyro (1khz, +-500g) & mag(400kHz I2c)
  * @param  None
  * @retval 0-success; 1-fail
  */
uint8_t BSP_MPU9250_Init(void)
{
	printf("Initializing MPU9250 ... ");
	
	if(BSP_MPU9250_Read_Reg(WHO_AM_I)==0x71)				//Find MPU9250 
	{
		BSP_MPU9250_Write_Reg(PWR_MGMT_1,0X80);   		//��Դ����,��λMPU9250
		HAL_Delay(200);																// delay_ms(200);
		BSP_MPU9250_Write_Reg(PWR_MGMT_1,0X01);   		//ѡ��ʱ��Դ
		BSP_MPU9250_Write_Reg(PWR_MGMT_2,0X00);   		//ʹ�ܼ��ٶȼƺ�������

		
		BSP_MPU9250_Write_Reg(CONFIG,0X02);						//��ͨ�˲��� 0x02 92hz (3.9ms delay) fs=1khz
		BSP_MPU9250_Write_Reg(SMPLRT_DIV,0x00);				//������1000/(1+0)=1000HZ
		BSP_MPU9250_Write_Reg(GYRO_CONFIG,0X08);  		//�����ǲ�����Χ 0X18 ����500��
		BSP_MPU9250_Write_Reg(ACCEL_CONFIG,0x08); 		//���ٶȼƲ�����Χ 0X08 ����4g
		BSP_MPU9250_Write_Reg(ACCEL_CONFIG2,0x08);		//���ٶȼ�����1khz �˲���460hz (1.94ms delay)
		
		BSP_MPU9250_Write_Reg(MAG_INT_PIN_CFG,0x30); 	//�в���������жϱ�־
    BSP_MPU9250_Write_Reg(MAG_I2C_MST_CTRL,0x4D); // I2C Speed 400 kHz
		BSP_MPU9250_Write_Reg(USER_CTRL,0X30);  			//ʹ��MPU9250 I2C Master and SPI Slave!!!!!!!!!!!!!!!!!!!!!
		
		HAL_Delay(10);																	// delay_ms(1);
		
		return BSP_AK8963_Init();
	}
	
	return 1;
}


//����AK8963��ģʽ ��������ģʽ2 (���ڼ����ٶ�Ϊ138hz ����ʹ��mode2 ���Դﵽ100hz)
/**
  * @brief  initialize AK8963(magnetic sensor), continous mode2, 16bit output. 
  * @param  hcan: None
  * @retval 0-success; 1-fail.
  */
uint8_t BSP_AK8963_Init(void)
{
	uint8_t temp=0;
	
	HAL_Delay(500);
	
	/*Reset sensor*/
	BSP_MPU9250_Write_Reg(MAG_I2C_SLV0_ADDR,0x0C);					//write I2C addr 0000 1100
	HAL_Delay(1);	
	BSP_MPU9250_Write_Reg(MAG_I2C_SLV0_DO,0x01);						//Reset and initialize sensor.
	BSP_MPU9250_Write_Reg(MAG_I2C_SLV0_REG,AK8963_CNTL2);		//write from ak8963_CNTL2;
	BSP_MPU9250_Write_Reg(MAG_I2C_SLV0_CTRL,0X81);					//write 1byte. 8-enable write or read�� 1-1byte
	
	HAL_Delay(500);
	
	/*Read addr of sensor and test the connection*/
	BSP_MPU9250_Write_Reg(MAG_I2C_SLV0_ADDR,0x8c);		//transfer is a read
	HAL_Delay(1);
	BSP_MPU9250_Write_Reg(MAG_I2C_SLV0_REG, MAG_WIA);	//read from 0 (0x00 Device ID 0X48)
	BSP_MPU9250_Write_Reg(MAG_I2C_SLV0_CTRL,0x81);		//read 1byte
	HAL_Delay(500);; //�������ʱ ������� ��С600us ����I2Cͨ���ٶ��йأ� 	����ʹ��I2C_SLV4 �����
	temp = BSP_MPU9250_Read_Reg(MAG_EXT_SENS_DATA_00);
	
	printf("WIA = 0x%02x\n", temp);
	if(temp == 0x48)
	{
		HAL_Delay(100); //�ɹ�
	}
	else 
	{		
		return 2;  //ʧ��
	}
	
	/*set 16bit continuous measurement mode2*/
	BSP_MPU9250_Write_Reg(MAG_I2C_SLV0_ADDR,0x0C);//write I2C addr
	HAL_Delay(1);	
	BSP_MPU9250_Write_Reg(MAG_I2C_SLV0_DO,0x16); //��AK8963_CNTL1��д��0x16, ѡ����������ģʽ 16bit���
	BSP_MPU9250_Write_Reg(MAG_I2C_SLV0_REG, AK8963_CNTL1);
	BSP_MPU9250_Write_Reg(MAG_I2C_SLV0_CTRL,0X81);//д��1byte
	HAL_Delay(500);;	//�������ʱ ������� ��С200us ����I2Cͨ���ٶ��йأ�
	
	BSP_MPU9250_Write_Reg(MAG_I2C_SLV0_ADDR,0x8C);//read I2C addr
	HAL_Delay(1);	
	BSP_MPU9250_Write_Reg(MAG_I2C_SLV0_REG,AK8963_CNTL1);
	BSP_MPU9250_Write_Reg(MAG_I2C_SLV0_CTRL,0X81);//��ȡһ������
	HAL_Delay(500);	//�������ʱ ������� ��С200us ����I2Cͨ���ٶ��йأ�
	temp = BSP_MPU9250_Read_Reg(MAG_EXT_SENS_DATA_00);
	
	if(temp == 0x16)
	{		
		HAL_Delay(500);  //��ʼ���ɹ�
	}
	else 
	{
		return 2;  //��ʼ��ʧ��
	}
	
	/*Start Read, 8 bytes	(0x49)(ST1 HXL HXH HYL HYH HZL HZH ST2)*/
	BSP_MPU9250_Write_Reg(MAG_I2C_SLV0_ADDR, 0x8C);          // Set AK8963_I2C_ADDR = 7'b000_1100
	HAL_Delay(1);
	BSP_MPU9250_Write_Reg(MAG_I2C_SLV0_REG, AK8963_ST1);     // Set Read Reg
	BSP_MPU9250_Write_Reg(MAG_I2C_SLV0_CTRL, 0x88);          // Start Read, 8 bytes	(0x49)(ST1 HXL HXH HYL HYH HZL HZH ST2), ���ú�֮��, I2C ������������ͣ�ظ���ȡ
	HAL_Delay(100);
	
	printf("MPU9250 initialization Done\r\n");
	
	return 0;
}


/**
  * @brief  Read ADC values of Gyro sensor (x, y, z)
  * @param  None
  * @retval None
  */
void BSP_MPU9250_Read_Gyro(void)
{
	uint8_t i;
	
	MPU9250_SPI_CS_ENABLE(); //ʹ��SPI����
	
	//�Ӽ��ٶȼƵļĴ�����ʼ���ж�ȡ�����Ǻͼ��ٶȼƵ�ֵ
	BSP_MPU9250_SPI_ReadWriteByte(GYRO_XOUT_H|0x80); //���Ͷ�����+�Ĵ�����
	
	for(i=0;i<6;i++)//һ����ȡ6�ֽڵ�����
	{
		MPU9250_buf[i] = BSP_MPU9250_SPI_ReadWriteByte(0xff); //ѭ����ȡ д0xff����Ϊslave��ʶ��
	}	
	
	/*datas are in HL style*/
	mpu9250_raw_data.gyro.x = ((int16_t)MPU9250_buf[0]<<8) | MPU9250_buf[1];
	mpu9250_raw_data.gyro.y = ((int16_t)MPU9250_buf[2]<<8) | MPU9250_buf[3];
	mpu9250_raw_data.gyro.z = ((int16_t)MPU9250_buf[4]<<8) | MPU9250_buf[5];	
	
	MPU9250_SPI_CS_DISABLE();										//��ֹSPI����
	
	/*delay for software SPI_CS*/
	uint16_t delay=10;
	while(delay--);
}


/**
  * @brief  Read ADC values of acc sensor (x, y, z)
  * @param  None
  * @retval None
  */
void BSP_MPU9250_Read_Acc(void)
{
	uint8_t i;
	
	MPU9250_SPI_CS_ENABLE(); //ʹ��SPI����
	
	//�Ӽ��ٶȼƵļĴ�����ʼ���ж�ȡ�����Ǻͼ��ٶȼƵ�ֵ
	BSP_MPU9250_SPI_ReadWriteByte(ACCEL_XOUT_H|0x80); //���Ͷ�����+�Ĵ�����
	
	for(i=0;i<6;i++)//һ����ȡ6�ֽڵ�����
	{
		MPU9250_buf[i] = BSP_MPU9250_SPI_ReadWriteByte(0xff); //ѭ����ȡ д0xff����Ϊslave��ʶ��
	}	
	
	/*datas are in HL style*/
	mpu9250_raw_data.acc.x = ((int16_t)MPU9250_buf[0]<<8) | MPU9250_buf[1];
	mpu9250_raw_data.acc.y = ((int16_t)MPU9250_buf[2]<<8) | MPU9250_buf[3];
	mpu9250_raw_data.acc.z = ((int16_t)MPU9250_buf[4]<<8) | MPU9250_buf[5];	
	
	MPU9250_SPI_CS_DISABLE();										//��ֹSPI����
	
	/*delay for software SPI_CS*/
	uint16_t delay=10;
	while(delay--);
}


/**
  * @brief  Read ADC values of Magnetic sensor (x, y, z)
  * @param  None
  * @retval None
  */
void BSP_MPU9250_Read_Mag(void)
{
	uint8_t i;
	
	MPU9250_SPI_CS_ENABLE(); //ʹ��SPI����
	
	//�Ӽ��ٶȼƵļĴ�����ʼ���ж�ȡ�����Ǻͼ��ٶȼƵ�ֵ
	BSP_MPU9250_SPI_ReadWriteByte(MAG_XOUT_L|0x80); //���Ͷ�����+�Ĵ�����
	
	for(i=0;i<6;i++)//һ����ȡ6�ֽڵ�����
	{
		MPU9250_buf[i] = BSP_MPU9250_SPI_ReadWriteByte(0xff); //ѭ����ȡ д0xff����Ϊslave��ʶ��
	}	
	
	/*datas are in LH style*/
	mpu9250_raw_data.mag.y = ((int16_t)MPU9250_buf[1]<<8) | MPU9250_buf[0];		//mag_y is aligned with acc_x and gyro_x
	mpu9250_raw_data.mag.x = ((int16_t)MPU9250_buf[3]<<8) | MPU9250_buf[2];		//mag_x is aligned with acc_y and gyro_y
	mpu9250_raw_data.mag.z = -((int16_t)MPU9250_buf[5]<<8) | MPU9250_buf[4];	//mag_z is aligned with -acc_z and -gyro_z
	
	MPU9250_SPI_CS_DISABLE();										//��ֹSPI����
	
	/*delay for software SPI_CS*/
	uint16_t delay=10;
	while(delay--);
}


/**
  * @brief  Read ADC values of Temp sensor
  * @param  None
  * @retval None
  */
void BSP_MPU9250_Read_Temp(void)
{
	uint8_t i;
	
	MPU9250_SPI_CS_ENABLE(); //ʹ��SPI����
	
	//�Ӽ��ٶȼƵļĴ�����ʼ���ж�ȡ�����Ǻͼ��ٶȼƵ�ֵ
	BSP_MPU9250_SPI_ReadWriteByte(TEMP_OUT_H|0x80); //���Ͷ�����+�Ĵ�����
	
	for(i=0;i<2;i++)//һ����ȡ2�ֽڵ�����
	{
		MPU9250_buf[i] = BSP_MPU9250_SPI_ReadWriteByte(0xff); //ѭ����ȡ д0xff����Ϊslave��ʶ��
	}	
	
	mpu9250_raw_data.temp = ((int16_t)MPU9250_buf[0]<<8) | MPU9250_buf[1];
	
	MPU9250_SPI_CS_DISABLE();										//��ֹSPI����
	
	/*delay for software SPI_CS*/
	uint16_t delay=10;
	while(delay--);
}


/**
  * @brief  Read ADC values of all sensors (acc-3x2; gyro-3x2; mag-3x2+2; temp-2)
  * @param  None
  * @retval None
  */
void BSP_MPU9250_Read_All(void)
{
	uint8_t i;
	
	MPU9250_SPI_CS_ENABLE(); //ʹ��SPI����
	
	//�Ӽ��ٶȼƵļĴ�����ʼ���ж�ȡ�����Ǻͼ��ٶȼƵ�ֵ
	BSP_MPU9250_SPI_ReadWriteByte(ACCEL_XOUT_H|0x80); //���Ͷ�����+�Ĵ�����
	
	for(i=0;i<22;i++)//һ����ȡ22�ֽڵ�����
	{
		MPU9250_buf[i] = BSP_MPU9250_SPI_ReadWriteByte(0xff); //ѭ����ȡ д0xff����Ϊslave��ʶ��
	}	
	
	mpu9250_raw_data.acc.x = ((int16_t)MPU9250_buf[0]<<8) | MPU9250_buf[1];
	mpu9250_raw_data.acc.y = ((int16_t)MPU9250_buf[2]<<8) | MPU9250_buf[3];
	mpu9250_raw_data.acc.z = ((int16_t)MPU9250_buf[4]<<8) | MPU9250_buf[5];	
	
	mpu9250_raw_data.temp = ((int16_t)MPU9250_buf[6]<<8) | MPU9250_buf[7];	
	
	mpu9250_raw_data.gyro.x = ((int16_t)MPU9250_buf[8]<<8) | MPU9250_buf[9];
	mpu9250_raw_data.gyro.y = ((int16_t)MPU9250_buf[10]<<8) | MPU9250_buf[11];
	mpu9250_raw_data.gyro.z = ((int16_t)MPU9250_buf[12]<<8) | MPU9250_buf[13];	
	
	mpu9250_raw_data.mag.y = ((int16_t)MPU9250_buf[16]<<8) | MPU9250_buf[15];
	mpu9250_raw_data.mag.x = ((int16_t)MPU9250_buf[18]<<8) | MPU9250_buf[17];
	mpu9250_raw_data.mag.z = -((int16_t)MPU9250_buf[20]<<8) | MPU9250_buf[19];	
	
	MPU9250_SPI_CS_DISABLE();										//��ֹSPI����	
	
	/*delay for software SPI_CS*/
	//uint16_t delay=10;
	//while(delay--);
}


/**
  * @brief  Read data in registers of MPU9250 with SPI.
  * @param  reg-addr of register.
  * @retval 1Byte data stored in register.
  */
uint8_t BSP_MPU9250_Read_Reg(uint8_t reg)
{
	uint8_t reg_val;
	MPU9250_SPI_CS_ENABLE();												//ʹ��SPI����
//	BSP_MPU9250_SPI_ReadWriteByte(reg|0x80); 				//���Ͷ�����+�Ĵ�����
//	reg_val = BSP_MPU9250_SPI_ReadWriteByte(0xff);	//��ȡ�Ĵ���
	reg_val = BSP_MPU9250_SPI_ReadWriteByte(reg|0x80); //Modified by Nathanֵ
	MPU9250_SPI_CS_DISABLE();												//��ֹSPI����
	
	/*delay for software SPI_CS*/
	uint16_t delay=10;
	while(delay--);
	
	return(reg_val);
}


/**
  * @brief  Write data into registers of MPU9250 with SPI.
  * @param  reg-addr of register; value-1Byte data.
  * @retval 1Byte read from SPI.
  */
uint8_t BSP_MPU9250_Write_Reg(uint8_t reg,uint8_t value)
{
	uint8_t status;
	MPU9250_SPI_CS_ENABLE();
	status = BSP_MPU9250_SPI_ReadWriteByte(reg); 		//����д����+�Ĵ�����
	BSP_MPU9250_SPI_ReadWriteByte(value);						//д��Ĵ���ֵ
	MPU9250_SPI_CS_DISABLE();
	
	/*delay for software SPI_CS*/
	uint16_t delay=10;
	while(delay--);
	
	return(status);															
}


/**
  * @brief  Transmit and receive 1Byte data with SPI master.
  * @param  TxData-1Byte data.
  * @retval 1Byte read from SPI master.
  */
uint8_t BSP_MPU9250_SPI_ReadWriteByte(uint8_t TxData)
{		
	uint8_t d_read,d_send=TxData;
	
//	HAL_StatusTypeDef result = HAL_SPI_TransmitReceive(&MPU9250_spi,&d_send,&d_read,1,0xFFFFFF);
	HAL_SPI_Transmit(&MPU9250_spi, &d_send, 1, 1000);
	HAL_StatusTypeDef result = HAL_SPI_Receive(&MPU9250_spi, &d_read, 1, 1000);
//  if(HAL_SPI_TransmitReceive(&MPU9250_spi,&d_send,&d_read,1,0xFFFFFF)!=HAL_OK)
//    d_read=Dummy_Byte;
	if(result!=HAL_OK)
		d_read=Dummy_Byte;

  return d_read; 		    
}


/**
  * @brief  Debug MPU9250; read and print all sensor data with 100ms delay.
  * @param  None
  * @retval None
  */
void BSP_MPU9250_Debug(void)
{
	printf("MPU9250 Debuging..........\n");
	
	BSP_MPU9250_Read_Gyro();
	BSP_MPU9250_Read_Acc();
	BSP_MPU9250_Read_Mag();
	BSP_MPU9250_Read_Temp();
	//	BSP_MPU9250_Read_All();

	
	printf("Raw Gyro.x = %d\r\n", mpu9250_raw_data.gyro.x*500/32767);
	printf("Raw Gyro.y = %d\r\n", mpu9250_raw_data.gyro.y*500/32767);
	printf("Raw Gyro.z = %d\r\n\r\n", mpu9250_raw_data.gyro.z*500/32767);

	printf("Raw Acc.x = %d\r\n", mpu9250_raw_data.acc.x*4*98/32767);
	printf("Raw Acc.y = %d\r\n", mpu9250_raw_data.acc.y*4*98/32767);
	printf("Raw Acc.z = %d\r\n\r\n", mpu9250_raw_data.acc.z*4*98/32767);

	printf("Raw Mag.x = %d\r\n", mpu9250_raw_data.mag.x*4900/32767);
	printf("Raw Mag.y = %d\r\n", mpu9250_raw_data.mag.y*4900/32767);
	printf("Raw Mag.z = %d\r\n\r\n", mpu9250_raw_data.mag.z*4900/32767);

	printf("Raw Temp = %d\r\n\r\n", mpu9250_raw_data.temp);

	HAL_Delay(1000);
}
