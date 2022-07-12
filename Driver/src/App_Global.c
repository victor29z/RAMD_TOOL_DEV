/**
  ******************************************************************************
  * @FileName:	
  * @Author:		Frank
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



/* Includes ------------------------------------------------------------------*/
#include "BSP_LED.h"
#include "BSP_ICM20600.h"
#include "Protocol.h"
#include "State_Observer.h"
#include "Flash_RW.h"
#include "Tool_CONN_AI.h"


/* Private Includes ----------------------------------------------------------*/
#include "App_Global.h"

/* Private Typedefs ----------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private Variables ---------------------------------------------------------*/

/* External Variables --------------------------------------------------------*/
bool firmware_update = false;
uint16_t uart_err_frame_cnt = 0;

/* Exported Functions --------------------------------------------------------*/
/**
  * @brief  Search IMU device; try on reading addr of MPU9250 with SPI.
  * @param  None.
  * @retval 0-success; 1-fail.
  */
uint8_t Find_IMU(void)
{
	for(uint8_t i=0; i<10; i++)
	{
		printf("Searching for IMU ... ");
		if(BSP_IMU_Found())	
		{
			printf("Found\n");
			return 0;
		}		
//		IMU_Not_Found;	//LED indication. LED1 and LED2 on.
		printf("Not found!\n");
		HAL_Delay(100);
	}
	
	return 1;
};

void House_Keeping(void)
{
	
	/* Power Control */
	if(tool_state[SYS_IO_PWR_ENABLE])
	{
		DIO_Power_On();
		BSP_LED1_ON;
		//printf("Powered on \r\n");
	}
	else
	{
		DIO_Power_Off();
		BSP_LED1_OFF;
		//printf("Powered off \r\n");
	}
	
	/* System Voltage Sampling */
	tool_state[SYS_VOLTAGE] = Get_Power_Supply_Volt();  //ȱ�ٵ�ѹ���
//	//printf(" SYS_VOLTAGE = %4.1fV \r\n", base_state[SYS_VOLTAGE]/10.0f);
	
	/* System Current Sampling */
	int32_t temp = Get_Cur();			//ȱ�ٵ������
	memcpy(&tool_state[SYS_CURRENT_L], &temp, 4);	
	//printf(" Current = %dmA \r\n", temp);
	//printf(" Current = %dmA \r\n", ((base_state[SYS_CURRENT_H]<<16) + (base_state[SYS_CURRENT_L])));
	
	/* Base Temperature Sampling */
	tool_state[SYS_TEMP] = Get_Tool_Temp();
//	printf(" SYS_TEMP = %4.1fC \r\n", tool_state[SYS_TEMP]/10.0f);
	
	/* IMU Sampling */ 	
// 	BSP_MPU9250_Read_All();  

// 	tool_state[MPU_GYR_X_DATA] = mpu9250_raw_data.gyro.x;
// 	tool_state[MPU_GYR_Y_DATA] = mpu9250_raw_data.gyro.y;
// 	tool_state[MPU_GYR_Z_DATA] = mpu9250_raw_data.gyro.z;
// //	printf("GYR_X = %d\r\n", (int16_t)tool_state[MPU_GYR_X_DATA]);
// //	printf("GYR_Y = %d\r\n", (int16_t)tool_state[MPU_GYR_Y_DATA]);
// //	printf("GYR_Z = %d\r\n", (int16_t)tool_state[MPU_GYR_Z_DATA]);
// //	HAL_Delay(1000);
	
// 	tool_state[MPU_ACC_X_DATA] = mpu9250_raw_data.acc.x;
// 	tool_state[MPU_ACC_Y_DATA] = mpu9250_raw_data.acc.y;
// 	tool_state[MPU_ACC_Z_DATA] = mpu9250_raw_data.acc.z;
// //	printf("ACC_X = %d\r\n", (int16_t)base_state[MPU_ACC_X_DATA]);
// //	printf("ACC_Y = %d\r\n", (int16_t)base_state[MPU_ACC_Y_DATA]);
// //	printf("ACC_Z = %d\r\n", (int16_t)base_state[MPU_ACC_Z_DATA]);
	

// 	tool_state[MPU_MAG_X_DATA] = mpu9250_raw_data.mag.x;
// 	tool_state[MPU_MAG_Y_DATA] = mpu9250_raw_data.mag.y;
// 	tool_state[MPU_MAG_Z_DATA] = mpu9250_raw_data.mag.z;
// //	printf("MAG_X = %d\r\n", (int16_t)base_state[MPU_MAG_X_DATA]);
// //	printf("MAG_Y = %d\r\n", (int16_t)base_state[MPU_MAG_Y_DATA]);
// //	printf("MAG_Z = %d\r\n", (int16_t)base_state[MPU_MAG_Z_DATA]);

// 	tool_state[MPU_TEMP_DATA] = mpu9250_raw_data.temp;
// //	printf("TEMP = %d\r\n\r\n", (int16_t)base_state[MPU_TEMP_DATA]);
	
	//BSP_ICM20600_Read_All();
	BSP_ICM20600_Cyclical_Update();
	tool_state[MPU_ACC_X_DATA] = icm20600_raw_data.acc.x;
	tool_state[MPU_ACC_Y_DATA] = icm20600_raw_data.acc.y;
	tool_state[MPU_ACC_Z_DATA] = icm20600_raw_data.acc.z;
	
	tool_state[MPU_GYR_X_DATA] = icm20600_raw_data.gyro.x;
	tool_state[MPU_GYR_Y_DATA] = icm20600_raw_data.gyro.y;
	tool_state[MPU_GYR_Z_DATA] = icm20600_raw_data.gyro.z;
	
	tool_state[MPU_TEMP_DATA] = icm20600_cali_data.temp * 10;	

	/*check installation pose*/
	if((int16_t)tool_state[MPU_ACC_Z_DATA] > 0)	//acc_z>0 -> upwards, LED2 on.
	{
		tool_state[MPU_INST_DRCT] = 0;
		BSP_LED1_ON;
	}
	
	else	//acc_z<0 -> downwards, LED2 off.
	{
		tool_state[MPU_INST_DRCT] = 1;
		BSP_LED1_OFF;
	}
	
	if(tool_state[USER_RS485_ENABLE])
	{	
		switch(USER_RS485_BAUDRATE)
		{
			case 0:
				huart6.Init.BaudRate = 9600;
				break;
			case 1:
				huart6.Init.BaudRate = 19200;
				break;
			case 2:
				huart6.Init.BaudRate = 38400;
				break;
			case 3:
				huart6.Init.BaudRate = 57600;
				break;
			case 4:
				huart6.Init.BaudRate = 115200;
				break;
			case 5:
				huart6.Init.BaudRate = 128000;
				break;
			case 6:
				huart6.Init.BaudRate = 256000;
				break;
			case 7:
				huart6.Init.BaudRate = 460800;
				break;
			default:
				break;				
		}		
		
		User_RS485_Enable();
	}
	
	else  //User_RS485_Disable
	{
		if(tool_state[ANLG_INPUT1_TYPE]) //1-Current
		{
			AI_Port_Config(Read_Current);
			int32_t AC_32 = Get_ACin1();
			memcpy(&tool_state[ANLG_INPUT1_VAL_L], &AC_32, 4);
			
			float AC;
			memcpy(&AC, &tool_state[ANLG_INPUT1_VAL_L], 4);
//			printf("AC1 = %f\r\n", AC);
		}
		
		else //0-Voltage
		{
			AI_Port_Config(Read_Voltage);
			int32_t AV_32 = Get_AVin1();
			memcpy(&tool_state[ANLG_INPUT1_VAL_L], &AV_32, 4);
			
			float AV;
			memcpy(&AV, &tool_state[ANLG_INPUT1_VAL_L], 4);
//			printf("AV1 = %f\r\n", AV);
		}
		
		if(tool_state[ANLG_INPUT2_TYPE]) //1-Current
		{
			AI_Port_Config(Read_Current);
			int32_t AC_32 = Get_ACin2();
			memcpy(&tool_state[ANLG_INPUT2_VAL_L], &AC_32, 4);
			
			float AC;
			memcpy(&AC, &tool_state[ANLG_INPUT2_VAL_L], 4);
//			printf("AC2 = %f\r\n", AC);
		}
		
		else //0-Voltage
		{
			AI_Port_Config(Read_Voltage);
			int32_t AV_32 = Get_AVin2();
			memcpy(&tool_state[ANLG_INPUT2_VAL_L], &AV_32, 4);
			
			float AV;
			memcpy(&AV, &tool_state[ANLG_INPUT2_VAL_L], 4);
//			printf("AV2 = %f\r\n", AV);
		}
	}

	//Tool DO config
	if(tool_state[TOOL_OUTPUT_VOLT] == PWR_0)
		DO_PWR_Config(PWR_0);
	else
	{
		DO_PWR_Config(tool_state[TOOL_OUTPUT_VOLT]);
		
		DO0_Config(tool_state[DO0_STATUS], tool_state[DO0_TYPE]);
		DO1_Config(tool_state[DO1_STATUS], tool_state[DO1_TYPE]);
	}	
	
	//Tool DI read
	tool_state[DI0_STATUS] = Read_DI_Port(Port_TI0);
	tool_state[DI1_STATUS] = Read_DI_Port(Port_TI1);
	
	/*Write system_state into Flash*/
	/*
	if(tool_state[SYS_SAVE_TO_FLASH])
	{
		tool_state[SYS_SAVE_TO_FLASH] = 0;
		Flash_Mem_Write(tool_state, TOOL_STATE_BUF_SIZE*2, FLASH_START_ADDR_SYSTEM_STATE);
	}	
	*/
}

void CMD_Processing(void)
{
	/* UART CMD Processing*/
	if(new_uart_frame_flag == true)
	{
		//printf("CMD_Processing %d\r\n", UART_Frame_Check());
		if (UART_Frame_Check() == 0)
		{
			uint16_t number_to_write = temp_uart_frame_data[RS232_Frame_Length]-2;
			uint8_t *pdata = (uint8_t *)&(tool_state[temp_uart_frame_data[RS232_Frame_INDEX]]);
			
			uint8_t number_to_read = temp_uart_frame_data[RS232_Frame_Data];
			uint8_t checksum_of_read =0;
			uint8_t	status = 0;
			
			switch (temp_uart_frame_data[RS232_Frame_CMD])
      {
				/* Command write without response */
      	case CMDTYPE_WR_NR: 
					memcpy(pdata, &temp_uart_frame_data[RS232_Frame_Data], number_to_write);
      		break;
				
				case CMDTYPE_WR:
					memcpy(pdata, &temp_uart_frame_data[RS232_Frame_Data], number_to_write);
					uint8_t serial_ack_data[8] = {							//generate writing failure ack data.
						0x55, 0xAA,  //frame header
						0x03,				 //frame length = 1+2
						temp_uart_frame_data[RS232_Frame_ID], 		//ID
						temp_uart_frame_data[RS232_Frame_CMD],		//CMD
						temp_uart_frame_data[RS232_Frame_INDEX],	//Index
						0x00,		//1,correct; 0,fail.
						(uint8_t)(0x03+temp_uart_frame_data[RS232_Frame_ID]+temp_uart_frame_data[RS232_Frame_CMD]+temp_uart_frame_data[RS232_Frame_INDEX]+0x01)		//check_sum
					};
				
					if(memcmp(&temp_uart_frame_data[RS232_Frame_Data], (uint8_t *)&(tool_state[temp_uart_frame_data[RS232_Frame_INDEX]]), number_to_write))
					{
						serial_ack_data[RS232_Frame_Data] = 0;						
						status = UART_FRAME_WR_ERR;
					}
					else
					{
						serial_ack_data[RS232_Frame_Data] = 1;	
					}
					BSP_UART_Send(&debug_uart, serial_ack_data, 8);
					break;
					
				case CMDTYPE_RD:
					temp_uart_frame_data[RS232_Frame_Length] += (number_to_read - 1);
					memcpy(&temp_uart_frame_data[RS232_Frame_Data], pdata, number_to_read);
					//Calculate checksum
					for(uint8_t i=2; i<temp_uart_frame_data[RS232_Frame_Length]+4; i++)
					{
						checksum_of_read += temp_uart_frame_data[i]; 
					}	
					temp_uart_frame_data[temp_uart_frame_data[RS232_Frame_Length]+4] = checksum_of_read;
					
					BSP_UART_Send(&debug_uart, temp_uart_frame_data, temp_uart_frame_data[RS232_Frame_Length]+5);			
					break;
      	default: break;
      }	
		}	
		else
		{
			printf("uart_err_frame_cnt = %d\r\n", ++uart_err_frame_cnt); //????
		}
		new_uart_frame_flag = false;
	}
	
	/* CAN CMD Processing*/
	if(new_can_cmd_flag == true)
	{
		//To do
		uint8_t status = 0;
		uint8_t temp_can_cmd_data[8] = {0};
		memcpy(temp_can_cmd_data, can_cmd_data, can_cmd_size);
		uint16_t can_data_len = can_cmd_size - 2;
		
		uint8_t *pdata = (uint8_t *)&(tool_state[temp_can_cmd_data[Frame_INDEX_CAN]]);
		
		uint16_t send_times = temp_can_cmd_data[Frame_Data_Init_CAN] / 6;
		uint16_t send_left = temp_can_cmd_data[Frame_Data_Init_CAN] % 6;
		uint16_t Can_ID = tool_state[SYS_ID] + 0x100;
		
		switch (temp_can_cmd_data[Frame_CMD_CAN])
    {
    	case CMDTYPE_WR_NR:
				/* write data into board without response */
				memcpy(pdata, &temp_can_cmd_data[Frame_Data_Init_CAN], can_data_len);	
    		break;
    	case CMDTYPE_WR:
				memcpy(pdata, &temp_can_cmd_data[Frame_Data_Init_CAN], can_data_len);	
					
				if(memcmp(&temp_can_cmd_data[Frame_Data_Init_CAN], (uint8_t *)&(tool_state[temp_can_cmd_data[Frame_INDEX_CAN]]), can_data_len))
				{
					//fail to write.
					temp_can_cmd_data[Frame_Data_Init_CAN] = 0x00;
					status = CAN_WR_ERR;
				}
				else
				{
					temp_can_cmd_data[Frame_Data_Init_CAN] = 0x01;
				}
				
				BSP_CANx_SendNormalData(Can_ID, temp_can_cmd_data, 3);	
    		break;
				
			case CMDTYPE_RD:
				for(uint16_t i=0; i<send_times; i++)
				{						
					memcpy(&temp_can_cmd_data[Frame_Data_Init_CAN], pdata, 6);
					BSP_CANx_SendNormalData(Can_ID, temp_can_cmd_data, 8); 
					
					temp_can_cmd_data[Frame_INDEX_CAN] += 3;
					pdata += 6;		     
				}

				if (send_left > 0)
				{
					memcpy(&temp_can_cmd_data[Frame_Data_Init_CAN], pdata, send_left);						
					BSP_CANx_SendNormalData(Can_ID, temp_can_cmd_data, send_left+2); 
				}			
				break;
				
    	default: break;
    }
		
		new_can_cmd_flag = false;		
	}
}

/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/


