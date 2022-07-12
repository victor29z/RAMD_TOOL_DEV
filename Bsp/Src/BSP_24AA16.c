/**
  ******************************************************************************
  * @FileName:		BSP_24AA16.c
  * @Author:		Hui Liu
  * @Version:		V1.0.0
  * @Date:			06-15-2020
  * @Description:   
  * @Others:
  ******************************************************************************
  * @FunctionsList:	
  *
  *
  ******************************************************************************
  * @Copyright(C), 2020 Smokie Robotics, Inc
  ******************************************************************************
  * @History:
  *
  ******************************************************************************
  */



/* Private Includes ----------------------------------------------------------*/
#include "BSP_24AA16.h"


/* Private Includes ----------------------------------------------------------*/

/* Private Typedefs ----------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private Variables ---------------------------------------------------------*/

/* External Variables --------------------------------------------------------*/

/* Exported Functions --------------------------------------------------------*/

uint8_t BSP_24AA16_Init(void)
{
	printf("Initializing 24AA16 ... ");
	printf("Done\r\n");
	
	return 0;
}

/**
  * @brief  I2C write uint16_t data into EEPROM
  * @param  Mem_Addr: Initial address of memory storing the data. (0x00~0x2048)
						*WriteBuffer: uint16_t pointer of input data.
						BuffSize: size of data (byte unit)
	* @retval Err_State: 1:error. 0:correct.
  */
uint16_t BSP_I2C_Write(uint16_t Mem_Addr, uint16_t *WriteBuffer, uint16_t NumByteToWrite)
{
	if((Mem_Addr+NumByteToWrite) > ROM_SIZE_24AA16-1) //1 block has 256 byte. 24aa16 has 2KBytes. check if the size of writing data overflow.
		return WDATA_OVERFLOW_24AA16;

	uint8_t first_block = Mem_Addr/256;  //0~7
	uint8_t last_block = (Mem_Addr+NumByteToWrite)/256; //0~7
	uint16_t Mem_Addr_first_block = Mem_Addr%256;  //首块的写内存起始地址
	uint16_t first_block_datalen = 0;
	uint16_t last_block_datalen = (Mem_Addr+NumByteToWrite)%256; //0~255
	uint16_t *pdata = WriteBuffer;

	if(first_block == last_block)		//只有1block，写第一块数据即可，数据长度等sizeofdata
	{
		first_block_datalen = NumByteToWrite;
		if(BSP_I2C_Block_Write(first_block, Mem_Addr_first_block, pdata, first_block_datalen) != HAL_OK)
			return WDATA_HAL_ERR_24AA16;
	}
		
	else		//至少有2block，先写第一块，再写中间256byte块（共3块及以上），再写最后一块。
	{
		first_block_datalen = 0xff - Mem_Addr_first_block + 1;			//先写第一块，数据长度等于255-地址+1
		if(BSP_I2C_Block_Write(first_block, Mem_Addr_first_block, pdata, first_block_datalen) != HAL_OK)
			return WDATA_HAL_ERR_24AA16;

		pdata += first_block_datalen/2; //pdata 是uint16 指针，2byte
		
		for(uint8_t i=first_block+1; i<last_block; i++)							//写中间满块数据
		{
			if(BSP_I2C_Block_Write(i, 0, pdata, 256) != HAL_OK)
				return WDATA_HAL_ERR_24AA16;
			pdata += 256/2;
		}

		//写最后一块数据
		if(BSP_I2C_Block_Write(last_block, 0, pdata, last_block_datalen) != HAL_OK )
			return WDATA_HAL_ERR_24AA16;
	}
	
	return 0;
}


/**
  * @brief  I2C read uint16_t data from EEPROM
  * @param  Mem_Addr: Initial address of memory storing the data. (0x00~0x2048)
						*ReadBuffer: uint16_t pointer of output data.
						BuffSize: size of data (byte unit)
	* @retval Err_State: 1:error. 0:correct.
  */
uint16_t BSP_I2C_Read(uint16_t Mem_Addr, uint16_t *ReadBuffer, uint16_t NumByteToWrite)
{
	if((Mem_Addr+NumByteToWrite) > ROM_SIZE_24AA16-1) //1 block has 256 byte. 24aa16 has 2KBytes. check if the size of writing data overflow.
		return RDATA_OVERFLOW_24AA16;
	
	uint8_t block_num = Mem_Addr/256;  //0~7
	uint16_t Mem_Addr_block = Mem_Addr%256;  //首块的写内存起始地址
	
	uint8_t read_times = NumByteToWrite/500;
	uint16_t last_read_datalen = NumByteToWrite%500;
	uint16_t *pdata = ReadBuffer;
	for(uint8_t i=0; i<read_times; i++)
	{
		if(BSP_I2C_Block_Read(block_num, Mem_Addr_block, pdata, 500) != HAL_OK)		//一次最多读500个byte
			return RDATA_HAL_ERR_24AA16;
		pdata += 500/2;
		Mem_Addr += 500;
		block_num = Mem_Addr/256;
		Mem_Addr_block = Mem_Addr%256;
		HAL_Delay(5);
	}

	if (BSP_I2C_Block_Read(block_num, Mem_Addr_block, pdata, last_read_datalen) != HAL_OK) //读取数据多的话，timeout要给够
		return RDATA_HAL_ERR_24AA16;
	
	return 0;
}

/**
  * @brief  I2C write uint16_t data into EEPROM block.
	* @param  Block_Num: Block number of EEPROM. 24aa16 has 8 blocks.
						Mem_Addr: Initial address of memory storing the data. (0x00~0xff). each block has 256 bytes.
						*WriteBuffer: uint16_t pointer of input data.
						BuffSize: size of data (unit byte).
	* @retval Err_State: 1:error. 0:correct.
  */
uint16_t BSP_I2C_Block_Write(uint16_t Block_Num, uint16_t Mem_Addr, uint16_t *WriteBuffer, uint16_t NumByteToWrite)
{
	uint8_t NumOfPage = 0, NumOfSingle = 0, count = 0;
	uint16_t Addr = 0;
	
	if(NumByteToWrite > (0xff-Mem_Addr+1))	//1 block has 256 byte. 24aa16 has 2KBytes. check if the size of writing data overflow.
		return WDATA_OVERFLOW_24AA16;
	
	uint16_t Addr_Block_Wirte = BASE_ADDR_24AA16_Write + 2*Block_Num; //device write address.
	uint8_t *pdata = (uint8_t *)WriteBuffer;
	
  Addr = Mem_Addr % EEPROM_PAGESIZE;
	count = EEPROM_PAGESIZE - Addr;
	NumOfPage =  NumByteToWrite / EEPROM_PAGESIZE;
	NumOfSingle = NumByteToWrite % EEPROM_PAGESIZE;	

	// If WriteAddr is EEPROM_PAGESIZE aligned
  if (Addr == 0) 
	{    
    // If NumByteToWrite < EEPROM_PAGESIZE
    if (NumOfPage == 0) 
		{
      // Start writting data
			if(HAL_I2C_Mem_Write(&I2C_handle, Addr_Block_Wirte, Mem_Addr, I2C_MEMADD_SIZE_8BIT, pdata, NumOfSingle, 0xffff) != HAL_OK)
				return WDATA_HAL_ERR_24AA16;
			HAL_Delay(5);
    }
		else 
		{      
			while (NumOfPage--)
			{		
				if(HAL_I2C_Mem_Write(&I2C_handle, Addr_Block_Wirte, Mem_Addr, I2C_MEMADD_SIZE_8BIT, pdata, EEPROM_PAGESIZE, 0xffff) != HAL_OK)
					return WDATA_HAL_ERR_24AA16;

				Mem_Addr +=  EEPROM_PAGESIZE;
				pdata += EEPROM_PAGESIZE;
				HAL_Delay(5);
			}
            
      if (NumOfSingle != 0) 
			{
				if(HAL_I2C_Mem_Write(&I2C_handle, Addr_Block_Wirte, Mem_Addr, I2C_MEMADD_SIZE_8BIT, pdata, NumOfSingle, 0xffff) != HAL_OK)
					return WDATA_HAL_ERR_24AA16;
				HAL_Delay(5);				
      }
    }
  }
	
	else  //If WriteAddr is not EEPROM_PAGESIZE aligned
	{   
		if(NumOfPage == 0) //内容不足一页
		{       
      if(NumByteToWrite > count)		//跨页写两页
			{            
				// Write the data conained in same page
				if(HAL_I2C_Mem_Write(&I2C_handle, Addr_Block_Wirte, Mem_Addr, I2C_MEMADD_SIZE_8BIT, pdata, count, 0xffff) != HAL_OK)
					return WDATA_HAL_ERR_24AA16;                   
         HAL_Delay(5);
				
				// Write the remaining data in the following page
				if(HAL_I2C_Mem_Write(&I2C_handle, Addr_Block_Wirte, (Mem_Addr + count), I2C_MEMADD_SIZE_8BIT, (uint8_t *)(pdata + count), (NumByteToWrite - count), 0xffff) != HAL_OK)
					return WDATA_HAL_ERR_24AA16;
				HAL_Delay(5);
			}
			else 	//写在一页内即可
			{		
				if(HAL_I2C_Mem_Write(&I2C_handle, Addr_Block_Wirte, Mem_Addr, I2C_MEMADD_SIZE_8BIT, pdata, NumByteToWrite, 0xffff) != HAL_OK)
					return WDATA_HAL_ERR_24AA16;
				HAL_Delay(5);
			}
		}
		
		else //内容超过一页
		{ 
      NumByteToWrite -= count;
			NumOfPage =  NumByteToWrite / EEPROM_PAGESIZE;
			NumOfSingle = NumByteToWrite % EEPROM_PAGESIZE;
			
      if(count != 0) //页不对齐
			{
				if(HAL_I2C_Mem_Write(&I2C_handle, Addr_Block_Wirte, Mem_Addr, I2C_MEMADD_SIZE_8BIT, pdata, count, 0xffff) != HAL_OK)
					return WDATA_HAL_ERR_24AA16;                   
      
        Mem_Addr += count;
				pdata += count;
				HAL_Delay(5);
			}
            
      while(NumOfPage--) //整页写
			{
				if(HAL_I2C_Mem_Write(&I2C_handle, Addr_Block_Wirte, Mem_Addr, I2C_MEMADD_SIZE_8BIT, pdata, EEPROM_PAGESIZE, 0xffff) != HAL_OK)
					return WDATA_HAL_ERR_24AA16;
				
        Mem_Addr +=  EEPROM_PAGESIZE;
				pdata += EEPROM_PAGESIZE;
				HAL_Delay(5);
			}
            
      if(NumOfSingle != 0) //写最后一页
			{
        if(HAL_I2C_Mem_Write(&I2C_handle, Addr_Block_Wirte, Mem_Addr, I2C_MEMADD_SIZE_8BIT, pdata, NumOfSingle, 0xffff) != HAL_OK)
					return WDATA_HAL_ERR_24AA16;
				HAL_Delay(5);				
      }
    }
	}
	
	return 0;
}


/**
  * @brief  I2C read uint16_t data into EEPROM block.
	* @param  Block_Num: Block number of EEPROM. 24aa16 has 8 blocks.
						Mem_Addr: Initial address of memory storing the data. (0x00~0xff). each block has 256 bytes.
						*ReadBuffer: uint16_t pointer of input data.
						BuffSize: size of data (unit byte).
	* @retval Err_State: 1:error. 0:correct.
  */
uint16_t BSP_I2C_Block_Read(uint16_t Block_Num, uint16_t Mem_Addr, uint16_t *ReadBuffer, uint16_t NumByteToWrite)
{
	uint16_t Addr_Block_Read = BASE_ADDR_24AA16_Read + 2*Block_Num;
	uint8_t ReadBuffer_temp[NumByteToWrite];
	
	if (HAL_I2C_Mem_Read(&I2C_handle, Addr_Block_Read, Mem_Addr, I2C_MEMADD_SIZE_8BIT, ReadBuffer_temp, NumByteToWrite, 0xffff) != HAL_OK) //读取数据多的话，timeout要给够
		return RDATA_HAL_ERR_24AA16;
	
	memcpy(ReadBuffer,ReadBuffer_temp,NumByteToWrite);
	return 0;
}


/**
  * @brief  Testing I2C write and Read uint16_t data.
  * @param  Addr_Write：Write address of EEPROM.
						Addr_Read：Read address of EEPROM.
	* @retval None.
  */
void BSP_I2C_test(void)
{
	uint16_t i;
	uint16_t WriteBuffer[300] = {0}, ReadBuffer[300] = {0};
	printf("\r\n***************I2C Example, i2cwrite*******************************\r\n");
	for(i=0; i<300; i++)
		WriteBuffer[i]=i;    /* WriteBuffer init */
	for(i=0; i<300; i++)
		printf("WriteBuffer=%d\n", WriteBuffer[i]);	
	
	if(BSP_I2C_Write(4, WriteBuffer, 600)==0)
		printf("\r\n EEPROM 24C02 Write Test OK \r\n");
	else
		printf("\r\n EEPROM 24C02 Write Test False \r\n");		
	HAL_Delay(1);
	
	/* read date from EEPROM */
	if(BSP_I2C_Read(4, ReadBuffer, 600)==0) //芯片最多一次读取250个字节
		printf("\r\n EEPROM 24C02 Read Test OK \r\n");
	else
		printf("\r\n EEPROM 24C02 Read Test False \r\n");		
	
	for(i=0; i<300; i++)
		printf("ReadBuffer[%d]=%d\n", i, ReadBuffer[i]);

//	printf("\r\n***************I2C Example2, i2cwrite*******************************\r\n");
//	for(i=0; i<128; i++)
//		WriteBuffer[i]=i;    /* WriteBuffer init */
//	for(i=0; i<128; i++)
//		printf("WriteBuffer=%d\n", WriteBuffer[i]);	
//	
//	if(BSP_I2C_Write(6, WriteBuffer, 256)==0)
//		printf("\r\n EEPROM 24C02 Write Test OK \r\n");
//	else
//		printf("\r\n EEPROM 24C02 Write Test False \r\n");		
//	HAL_Delay(1);
//	
//	/* read date from EEPROM */
//	if(BSP_I2C_Read(6, ReadBuffer, 256)==0)
//		printf("\r\n EEPROM 24C02 Read Test OK \r\n");
//	else
//		printf("\r\n EEPROM 24C02 Read Test False \r\n");		
//	
//	for(i=0; i<128; i++)
//		printf("ReadBuffer[%d]=%d\n", i, ReadBuffer[i]);
//	
//	printf("\r\n***************I2C Example3,block_write*******************************\r\n");
//	for(i=0; i<50; i++)
//		WriteBuffer[i]=i;    /* WriteBuffer init */
//	for(i=0; i<50; i++)
//		printf("WriteBuffer=%d\n", WriteBuffer[i]);	
//	
//	if(BSP_I2C_Block_Write(0, 16, WriteBuffer, 100)==0)  //write 100 bytes 0~49 from address 16.
//		printf("\r\n EEPROM 24C02 Write Test OK \r\n");
//	else
//		printf("\r\n EEPROM 24C02 Write Test False \r\n");		
//	HAL_Delay(1);
//	
//	if(BSP_I2C_Block_Read(0, 4, ReadBuffer, 200)==0)
//		printf("\r\n EEPROM 24C02 Read Test OK \r\n");
//	else
//		printf("\r\n EEPROM 24C02 Read Test False \r\n");		
//	
//	for(i=0; i<100; i++)
//		printf("ReadBuffer[%d]=%d\n", i, ReadBuffer[i]);

//	printf("\r\n***************I2C Example3,block_write_float*******************************\r\n");
//	float data[25];
//	for(i=0; i<25; i++)
//		data[i]=i*1.0;    /* WriteBuffer init */
//	for(i=0; i<25; i++)
//		printf("data_float=%f\n", data[i]);	
//	
//	memcpy(WriteBuffer, data, 100);
//	if(BSP_I2C_Block_Write(0, 4, WriteBuffer, 100)==0)
//		printf("\r\n EEPROM 24C02 Write Test OK \r\n");
//	else
//		printf("\r\n EEPROM 24C02 Write Test False \r\n");		
//	HAL_Delay(1);
//	
//	if(BSP_I2C_Read(4, ReadBuffer, 100)==0)
//		printf("\r\n EEPROM 24C02 Read Test OK \r\n");
//	else
//		printf("\r\n EEPROM 24C02 Read Test False \r\n");		
//	
//	uint16_t *pdata = WriteBuffer, *pdata2 = ReadBuffer;
//	for(i=0; i<50; i++)
//	{
//		printf("pdata[%d]=0x%04x, pdata2[%d]=0x%04x\n", i, *(pdata+i),i, *(pdata2+i));
//	}		
}
/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/
