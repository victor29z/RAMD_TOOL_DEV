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

/* Includes ----------------------------------------------------------*/
#include "BSP_UART.h"

/* Private Includes ----------------------------------------------------------*/
#include "BSP_ICM20600.h"

/* Private Typedefs ----------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private Variables ---------------------------------------------------------*/
uint8_t	 ICM20600_buf[22];

/* External Variables --------------------------------------------------------*/
ICM20600_Raw_Data icm20600_raw_data = {0};
ICM20600_Cali_Data icm20600_cali_data = {0};
extern DMA_HandleTypeDef hdma_spi2_rx;
extern DMA_HandleTypeDef hdma_spi2_tx;
extern SPI_HandleTypeDef hspi2;
/* Exported Functions --------------------------------------------------------*/


/**
  * @brief  Try on connecting with ICM20600
  * @param  None
  * @retval 0-success; 1-fail.
  */
uint8_t BSP_IMU_Found(void)
{
	if(BSP_ICM20600_Read_Reg(WHO_AM_I)==0x11)	
		return 1;
	return 0;
}


/**
  * @brief  initialize IMU, set up configuration of acc(1khz, +-4g), gyro (1khz, +-500g)
  * @param  None
  * @retval 0-success; 1-fail
  */
uint8_t BSP_ICM20600_Init(void)
{
	uint8_t i = 0;
	
	printf("Initializing ICM20600 ... ");
	
	do{
			if(BSP_ICM20600_Read_Reg(WHO_AM_I) == 0x11)				//Find ICM20600 
			{
				BSP_ICM20600_Write_Reg(PWR_MGMT_1, 0x80);   		//��Դ����,��λICM20600
				HAL_Delay(200);																	// delay_ms(200);
				BSP_ICM20600_Write_Reg(PWR_MGMT_1, 0x01);   		//ѡ��ʱ��Դ
				BSP_ICM20600_Write_Reg(PWR_MGMT_2, 0x00);   		//ʹ�ܼ��ٶȼƺ�������
				
				BSP_ICM20600_Write_Reg(CONFIG, 0x02);						//��ͨ�˲��� 0x02 92hz (3.9ms delay) fs=1khz
				BSP_ICM20600_Write_Reg(SMPLRT_DIV, 0x00);				//������1000/(1+0)=1000HZ
				BSP_ICM20600_Write_Reg(GYRO_CONFIG, 0x08);  		//�����ǲ�����Χ 0x18 ����500��/s
				BSP_ICM20600_Write_Reg(ACCEL_CONFIG, 0x08); 		//���ٶȼƲ�����Χ 0x08 ����4g
				BSP_ICM20600_Write_Reg(ACCEL_CONFIG2, 0x08);		//���ٶȼ�����1khz �˲���460hz (1.94ms delay)
				
				printf("Found ... Done\r\n");
				return 0;
			}			
			i++;
			HAL_Delay(200);		
	}while(i < 10);

	printf("Not Found ... Fail\r\n");
	return 1;
}


/**
  * @brief  Read ADC values of Gyro sensor (x, y, z)
  * @param  None
  * @retval None
  */
void BSP_ICM20600_Read_Gyro(void)
{
	uint8_t i;
	
	ICM20600_SPI_CS_ENABLE(); //ʹ��SPI����
	
	//�Ӽ��ٶȼƵļĴ�����ʼ���ж�ȡ�����Ǻͼ��ٶȼƵ�ֵ
	BSP_ICM20600_SPI_ReadWriteByte(GYRO_XOUT_H|0x80); //���Ͷ�����+�Ĵ�����
	
	for(i=0;i<6;i++)//һ����ȡ6�ֽڵ�����
	{
		ICM20600_buf[i] = BSP_ICM20600_SPI_ReadWriteByte(0xff); //ѭ����ȡ д0xff����Ϊslave��ʶ��
	}	
	
	/*datas are in HL style*/
	icm20600_raw_data.gyro.x = ((int16_t)ICM20600_buf[0]<<8) | ICM20600_buf[1];
	icm20600_raw_data.gyro.y = ((int16_t)ICM20600_buf[2]<<8) | ICM20600_buf[3];
	icm20600_raw_data.gyro.z = ((int16_t)ICM20600_buf[4]<<8) | ICM20600_buf[5];	
		
	icm20600_cali_data.gyro.x = icm20600_raw_data.gyro.x*500.0/32767;
	icm20600_cali_data.gyro.y = icm20600_raw_data.gyro.y*500.0/32767;
	icm20600_cali_data.gyro.z = icm20600_raw_data.gyro.z*500.0/32767;
	
	ICM20600_SPI_CS_DISABLE();										//��ֹSPI����

}


/**
  * @brief  Read ADC values of acc sensor (x, y, z)
  * @param  None
  * @retval None
  */
void BSP_ICM20600_Read_Acc(void)
{
	uint8_t i;
	
	ICM20600_SPI_CS_ENABLE(); //ʹ��SPI����
	
	//�Ӽ��ٶȼƵļĴ�����ʼ���ж�ȡ�����Ǻͼ��ٶȼƵ�ֵ
	BSP_ICM20600_SPI_ReadWriteByte(ACCEL_XOUT_H|0x80); //���Ͷ�����+�Ĵ�����
	
	for(i=0;i<6;i++)//һ����ȡ6�ֽڵ�����
	{
		ICM20600_buf[i] = BSP_ICM20600_SPI_ReadWriteByte(0xff); //ѭ����ȡ д0xff����Ϊslave��ʶ��
	}	
	
	/*datas are in HL style*/
	icm20600_raw_data.acc.x = ((int16_t)ICM20600_buf[0]<<8) | ICM20600_buf[1];
	icm20600_raw_data.acc.y = ((int16_t)ICM20600_buf[2]<<8) | ICM20600_buf[3];
	icm20600_raw_data.acc.z = ((int16_t)ICM20600_buf[4]<<8) | ICM20600_buf[5];	
		
	icm20600_cali_data.acc.x = icm20600_raw_data.acc.x*4.0/32767;
	icm20600_cali_data.acc.y = icm20600_raw_data.acc.y*4.0/32767;
	icm20600_cali_data.acc.z = icm20600_raw_data.acc.z*4.0/32767;
	
	ICM20600_SPI_CS_DISABLE();										//��ֹSPI����
	
}


/**
  * @brief  Read ADC values of Temp sensor
  * @param  None
  * @retval None
  */
void BSP_ICM20600_Read_Temp(void)
{
	uint8_t i;
	
	ICM20600_SPI_CS_ENABLE(); //ʹ��SPI����
	
	//�Ӽ��ٶȼƵļĴ�����ʼ���ж�ȡ�����Ǻͼ��ٶȼƵ�ֵ
	BSP_ICM20600_SPI_ReadWriteByte(TEMP_OUT_H|0x80); //���Ͷ�����+�Ĵ�����
	
	for(i=0;i<2;i++)//һ����ȡ2�ֽڵ�����
	{
		ICM20600_buf[i] = BSP_ICM20600_SPI_ReadWriteByte(0xff); //ѭ����ȡ д0xff����Ϊslave��ʶ��
	}	
	
	icm20600_raw_data.temp = ((int16_t)ICM20600_buf[0]<<8) | ICM20600_buf[1];
	
	icm20600_cali_data.temp = icm20600_raw_data.temp/326.8 + 25.0;
	
	ICM20600_SPI_CS_DISABLE();										//��ֹSPI����
	
}


/**
  * @brief  Read ADC values of all sensors (acc-3x2; temp-2; gyro-3x2)
  * @param  None
  * @retval None
  */
void BSP_ICM20600_Read_All(void)
{
	uint8_t i;
	
	ICM20600_SPI_CS_ENABLE(); //ʹ��SPI����
	
	//�Ӽ��ٶȼƵļĴ�����ʼ���ж�ȡ�����Ǻͼ��ٶȼƵ�ֵ
	BSP_ICM20600_SPI_ReadWriteByte(ACCEL_XOUT_H|0x80); //���Ͷ�����+�Ĵ�����
	//HAL_SPI_Receive_DMA(&hspi2,ICM20600_buf,14);
	
	/**/
	for(i=0;i<14;i++)//һ����ȡ14�ֽڵ�����
	{
		ICM20600_buf[i] = BSP_ICM20600_SPI_ReadWriteByte(0xff); //ѭ����ȡ д0xff����Ϊslave��ʶ��
	}	
	
	icm20600_raw_data.acc.x = ((int16_t)ICM20600_buf[0]<<8) | ICM20600_buf[1];
	icm20600_raw_data.acc.y = ((int16_t)ICM20600_buf[2]<<8) | ICM20600_buf[3];
	icm20600_raw_data.acc.z = ((int16_t)ICM20600_buf[4]<<8) | ICM20600_buf[5];	
	
	icm20600_raw_data.temp = ((int16_t)ICM20600_buf[6]<<8) | ICM20600_buf[7];	
	
	icm20600_raw_data.gyro.x = ((int16_t)ICM20600_buf[8]<<8) | ICM20600_buf[9];
	icm20600_raw_data.gyro.y = ((int16_t)ICM20600_buf[10]<<8) | ICM20600_buf[11];
	icm20600_raw_data.gyro.z = ((int16_t)ICM20600_buf[12]<<8) | ICM20600_buf[13];	
	
	icm20600_cali_data.gyro.x = icm20600_raw_data.gyro.x*500.0/32767;
	icm20600_cali_data.gyro.y = icm20600_raw_data.gyro.y*500.0/32767;
	icm20600_cali_data.gyro.z = icm20600_raw_data.gyro.z*500.0/32767;
	
	icm20600_cali_data.acc.x = icm20600_raw_data.acc.x*4.0/32767;
	icm20600_cali_data.acc.y = icm20600_raw_data.acc.y*4.0/32767;
	icm20600_cali_data.acc.z = icm20600_raw_data.acc.z*4.0/32767;
	
	icm20600_cali_data.temp = icm20600_raw_data.temp/326.8 + 25.0;
	
	ICM20600_SPI_CS_DISABLE();										//��ֹSPI����	

}

void BSP_ICM20600_Cyclical_Update(void){
	static uint8_t i = 0;
	ICM20600_SPI_CS_ENABLE(); //ʹ��SPI����
	
	//�Ӽ��ٶȼƵļĴ�����ʼ���ж�ȡ�����Ǻͼ��ٶȼƵ�ֵ
	BSP_ICM20600_SPI_ReadWriteByte((ACCEL_XOUT_H + i)|0x80); //��
	ICM20600_buf[i] = BSP_ICM20600_SPI_ReadWriteByte(0xff); //ѭ����ȡ д0xff����
	ICM20600_buf[i+1] = BSP_ICM20600_SPI_ReadWriteByte(0xff); //ѭ����ȡ д0xff����
	
	i = (i+2)%14;
	ICM20600_SPI_CS_DISABLE();		

	

	icm20600_raw_data.acc.x = ((int16_t)ICM20600_buf[0]<<8) | ICM20600_buf[1];
	icm20600_raw_data.acc.y = ((int16_t)ICM20600_buf[2]<<8) | ICM20600_buf[3];
	icm20600_raw_data.acc.z = ((int16_t)ICM20600_buf[4]<<8) | ICM20600_buf[5];	
	
	icm20600_raw_data.temp = ((int16_t)ICM20600_buf[6]<<8) | ICM20600_buf[7];	
	
	icm20600_raw_data.gyro.x = ((int16_t)ICM20600_buf[8]<<8) | ICM20600_buf[9];
	icm20600_raw_data.gyro.y = ((int16_t)ICM20600_buf[10]<<8) | ICM20600_buf[11];
	icm20600_raw_data.gyro.z = ((int16_t)ICM20600_buf[12]<<8) | ICM20600_buf[13];	
	
	icm20600_cali_data.gyro.x = icm20600_raw_data.gyro.x*500.0/32767;
	icm20600_cali_data.gyro.y = icm20600_raw_data.gyro.y*500.0/32767;
	icm20600_cali_data.gyro.z = icm20600_raw_data.gyro.z*500.0/32767;
	
	icm20600_cali_data.acc.x = icm20600_raw_data.acc.x*4.0/32767;
	icm20600_cali_data.acc.y = icm20600_raw_data.acc.y*4.0/32767;
	icm20600_cali_data.acc.z = icm20600_raw_data.acc.z*4.0/32767;
	
	icm20600_cali_data.temp = icm20600_raw_data.temp/326.8 + 25.0;



}

/**
  * @brief  Read data in registers of ICM20600 with SPI.
  * @param  reg-addr of register.
  * @retval 1Byte data stored in register.
  */
uint8_t BSP_ICM20600_Read_Reg(uint8_t reg)
{
	uint8_t reg_val;
	ICM20600_SPI_CS_ENABLE();													//ʹ��SPI����
	BSP_ICM20600_SPI_ReadWriteByte(reg|0x80); 				//���Ͷ�����+�Ĵ�����
	reg_val = BSP_ICM20600_SPI_ReadWriteByte(0xff);		//��ȡ�Ĵ���ֵ
	ICM20600_SPI_CS_DISABLE();												//��ֹSPI����
	
	return(reg_val);
}


/**
  * @brief  Write data into registers of ICM20600 with SPI.
  * @param  reg-addr of register; value-1Byte data.
  * @retval 1Byte read from SPI.
  */
uint8_t BSP_ICM20600_Write_Reg(uint8_t reg,uint8_t value)
{
	uint8_t status;
	ICM20600_SPI_CS_ENABLE();
	status = BSP_ICM20600_SPI_ReadWriteByte(reg); 		//����д����+�Ĵ�����
	BSP_ICM20600_SPI_ReadWriteByte(value);						//д��Ĵ���ք1�7
	ICM20600_SPI_CS_DISABLE();
	
	return(status);															
}


/**
  * @brief  Transmit and receive 1Byte data with SPI master.
  * @param  TxData-1Byte data.
  * @retval 1Byte read from SPI master.
  */
uint8_t BSP_ICM20600_SPI_ReadWriteByte(uint8_t TxData)
{		
	uint8_t d_read,d_send=TxData;
	
  if(HAL_SPI_TransmitReceive(&ICM20600_spi,&d_send,&d_read,1,0xFFFFFF)!=HAL_OK)
    d_read=Dummy_Byte;

  return d_read; 		    
}


/**
  * @brief  Test ICM20600; read and print all sensor data with 100ms delay.
  * @param  None
  * @retval None
  */
void BSP_ICM20600_Test(void)
{
	printf("***ICM20600_Test***\r\n");
	
//	BSP_ICM20600_Read_Gyro();
//	BSP_ICM20600_Read_Acc();
//	BSP_ICM20600_Read_Temp();
	
	BSP_ICM20600_Read_All();

	/* Raw data print 
	printf("Raw Gyro.x = %d\r\n", icm20600_raw_data.gyro.x);
	printf("Raw Gyro.y = %dr\n", icm20600_raw_data.gyro.y);
	printf("Raw Gyro.z = %d\r\n\r\n", icm20600_raw_data.gyro.z);

	printf("Raw Acc.x = %dr\n", icm20600_raw_data.acc.x);
	printf("Raw Acc.y = %d\r\n", icm20600_raw_data.acc.y);
	printf("Raw Acc.z = %d\r\n\r\n", icm20600_raw_data.acc.z);

	printf("Raw Temp = %d\r\n\r\n", icm20600_raw_data.temp); 
	*/
	
	/* Cali data print */	
	printf("Cali Gyro.x = %fdps\r\n", icm20600_cali_data.gyro.x);
	printf("Cali Gyro.y = %fdps\r\n", icm20600_cali_data.gyro.y);
	printf("Cali Gyro.z = %fdps\r\n\r\n", icm20600_cali_data.gyro.z);

	printf("Cali Acc.x = %fg\r\n", icm20600_cali_data.acc.x);
	printf("Cali Acc.y = %fg\r\n", icm20600_cali_data.acc.y);
	printf("Cali Acc.z = %fg\r\n\r\n", icm20600_cali_data.acc.z);

	printf("Cali Temp = %fC\r\n\r\n", icm20600_cali_data.temp);
}
