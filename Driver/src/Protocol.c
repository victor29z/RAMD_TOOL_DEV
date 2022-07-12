/**
  ******************************************************************************
  * @FileName:	Protocol.c
  * @Author:		Hui
  * @Version:		V1.0.0
  * @Date:			06-16-2020
  * @Description:   
  * @Others:
  ******************************************************************************
  * @Copyright(C), 2020, Smokie Robotics, Inc
  ******************************************************************************
  * @History:
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "BSP_UART.h"

/* Private Includes ----------------------------------------------------------*/
#include "Protocol.h"

/* Private Typedefs ----------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private Variables ---------------------------------------------------------*/

/* External Variables --------------------------------------------------------*/
uint16_t tool_state[TOOL_STATE_BUF_SIZE]={
0,																//0x00						Reserved
0xFD,															//0x01						SYS_ID             				  Driver ID
2,  															//0x02						SYS_MODEL_TYPE      				Driver Model. 1-AJ3; 2-AJ5; 3-AJ10
(uint16_t)((1<<8)|(0<<4)|(1)),		//0x03						SYS_FW_VER 									Firmwire version. 1.0.0
0,																//0x04						SYS_ERROR 									Error code.
0,																//0x05						SYS_VOLTAGE									System voltagy.(0.1V).
0,																//0x06						SYS_TEMP										system temperature.(0.1C).
1,																//0x07						SYS_BAUDRATE_485						RS232 port baud rate. 0-19200; 1-115200; 2-500k; 3-1M.				
2,																//0x08						SYS_BAUDRATE_CAN						CAN baud rate. 0-250k; 1-500k; 2-1M.
0,																//0x09						Remain											Remain
1,																//0x0a						SYS_IO_PWR_ENABLE						IO ports power enable flag. 0-IO power off; 1-IO power on.
0,																//0x0b						SYS_SAVE_TO_FLASH						Flag of saving data onto flash.
0,																//0x0c						SYS_CLEAR_ERROR							clear error flags.
0,0,0,														//0x0d~0x0f				Reserved
0,																//0x10						SYS_CURRENT_L								Low 16bits of current (mA).
0,																//0x11						SYS_CURRENT_H								High 16bits of current(mA).
0,0,0,0,0,0,0,0,0,0,							//0x12~0x1b				Reserved
0,																//0x1c						ACD_CAL_DEF0								axial calibration data0.
0,																//0x1d						ACD_CAL_DEF1								axial calibration data1.
0,																//0x1e						ACD_CAL_DEF2								axial calibration data2.
0,																//0x1f						ACD_CAL_DEF3								axial calibration data3.
0,0,0,0,0,0,											//0x20~0x25				Reserved
0,																//0x26						MODEL_TYPE									Module type. 0-machine; 1-Cast.
0,																//0X27						MODEL_ID
0,0,0,0,0,0,0,0,									//0x28~0x2f				Reserved
0,																//0x30						LIT_MAX_CURRENT							Limitation of maximum current (mA).
0,0,0,0,0,												//0x31~0x35				Reserved
0,																//0x36						MPU_TEMP_DATA								Temperature of MPU.
0,																//0x37						MPU_ACC_X_DATA							ACC ADC value on x axis of MPU
0,																//0x38						MPU_ACC_Y_DATA							ACC ADC value on y axis of MPU
0,																//0x39						MPU_ACC_Z_DATA							ACC ADC value on z axis of MPU
0,																//0x3a						MPU_GYR_X_DATA							Gyro ADC value on x axis of MPU
0,																//0x3b						MPU_GYR_Y_DATA							Gyro ADC value on y axis of MPU
0,																//0x3c						MPU_GYR_Z_DATA							Gyro ADC value on z axis of MPU
0,																//0x3d						MPU_MAG_X_DATA							Magnet ADC value on x axis of MPU
0,																//0x3e						MPU_MAG_Y_DATA							Magnet ADC value on y axis of MPU
0,																//0x3f						MPU_MAG_Z_DATA							Magnet ADC value on z axis of MPU
0,																//0x40						INSTALL_DRCT								0-Normal;1-Reverse
0,0,0,0,0,0,											//0x41~0x46				Reserved
0,																//0x47						ANLG_INPUT1_TYPE						Analog input1 type:0-Voltage;1-Current;2-Float
0,																//0x48						ANLG_INPUT2_TYPE						Analog input2 type:0-Voltage;1-Current;2-Float
0,																//0x49						ANLG_INPUT1_VAL_L						Analog input1 value low byte.
0,																//0x4a						ANLG_INPUT1_VAL_H						Analog input1 value high byte.
0,																//0x4b						ANLG_INPUT2_VAL_L						Analog input2 value low byte.
0,																//0x4c						ANLG_INPUT2_VAL_H						Analog input2 value high byte.
0,0,0,														//0x4d~0x4f				Remain
0,																//0x50						USER_RS485_ENABLE						User RS485 enable flag:0-disable; 1-Enable.
3,																//0x51						USER_RS485_BAUDRATE					User RS485 Baudrate:0-9600; 1-19200; 2-38400; 3-57600; 3-115200; 4-1M; 5-2M; 6-5M.
0,0,0,0,													//0x52~0x55				Remain
0,																//0x56						TOOL_OUTPUT_VOLT						tool output voltage:0-0v;1-12v;2-24V.
2,																//0x57						DO0_TYPE										0-Sinking(NPN);1-Source(PNP);2-PP;3-Dual Pin Power
2,																//0x58						DO1_TYPE										0-Sinking(NPN);1-Source(PNP);2-PP;3-Dual Pin Power.
0,																//0x59						DO0_STATE										0-Inactive;1-Active
0,																//0x5a						DO1_STATE										0-Inactive;1-Active
0,																//0x5b						DI0_STATE										0-LOW;1-HIGH
0,																//0x5c						DI1_STATE										0-LOW;1-HIGH
0,0,0															//0x5d~0x5f				Remain
};

uint8_t temp_uart_frame_data[TEMP_UART_FRAME_SIZE] = {0};

/* Exported Functions --------------------------------------------------------*/

uint8_t UART_Frame_Check(void)
{
	memcpy(temp_uart_frame_data, uart_frame_data, uart_frame_size);
	
	/* check frame head */
	if ((temp_uart_frame_data[RS232_Frame_Head_H] != 0x55)||(temp_uart_frame_data[RS232_Frame_Head_L] != 0xAA))
	{
		return UART_FRAME_HEAD_ERR;
	}

	/* check checksum */
	uint8_t frame_check_sum = temp_uart_frame_data[uart_frame_size-1];
	uint8_t temp_check_sum = 0x00;
	
	for(uint16_t i=0; i<(temp_uart_frame_data[RS232_Frame_Length]+2); i++)	//calculate checksum
	{
		temp_check_sum += temp_uart_frame_data[RS232_Frame_Length+i];
	}
	if(frame_check_sum != temp_check_sum)
	{ 
		return UART_FRAME_CHKSUM_ERR;
	}
	
	/* Compare driver ID */
	if((temp_uart_frame_data[RS232_Frame_ID]!=0xff) && (uart_frame_data[RS232_Frame_ID] != tool_state[SYS_ID]))
	{
		return UART_FRAME_ID_ERR;
	}
	
	return 0;
}

/**
  * @brief  Decode UART message. 
  * @param  None.
  * @retval 0-success; 1-fail.
  */
uint8_t MSG_Decoding_UART(void)
{
	uint8_t temp_uart_frame_data[uart_frame_size];
	memcpy(temp_uart_frame_data, uart_frame_data, uart_frame_size);
	uint16_t length_data = temp_uart_frame_data[RS232_Frame_Length]-2;
	
	/*****Compare frame header.*****/
	uint16_t temp_Frame_Header = (temp_uart_frame_data[RS232_Frame_Head_H]<<8)|(temp_uart_frame_data[RS232_Frame_Head_L]); //!!!!!!

	if((Frame_Header_RS232-temp_Frame_Header))
	{
		new_uart_frame_flag = false; //!!!!!
		return UART_FRAME_HEAD_ERR;
	}
	
	/*****Compare check sum.*****/
	uint8_t *p = (uint8_t*)(&temp_uart_frame_data + 1);			
	uint8_t check_sum_data = *(p-1);	//data of check sum in Frame_R232
	uint8_t check_sum = 0x00;
	for(uint16_t i=0; i<(temp_uart_frame_data[RS232_Frame_Length]+2); i++)	//calculate check sum
	{
		check_sum += temp_uart_frame_data[RS232_Frame_Length+i];
	}
	if(check_sum_data != check_sum)
	{
		new_uart_frame_flag = false; //!!!!!
		return UART_FRAME_CHKSUM_ERR;
	}
	
	/*****Compare driver ID*****/
	if((temp_uart_frame_data[RS232_Frame_ID]!=0xff) && ((uint16_t)uart_frame_data[RS232_Frame_ID]-tool_state[SYS_ID]))
	{
		new_uart_frame_flag = false; //!!!!!		
		return UART_FRAME_ID_ERR;
	}
	
	/*****Command write without response.*****/
	if(temp_uart_frame_data[RS232_Frame_CMD]==CMDTYPE_WR_NR)		
	{
		uint8_t *pdata = (uint8_t *)&(tool_state[temp_uart_frame_data[RS232_Frame_INDEX]]);
		for(uint8_t i=0; i<length_data; i++)
		{
			*(pdata+i) = temp_uart_frame_data[RS232_Frame_Data+i];
		}
		
		if(memcmp(&temp_uart_frame_data[RS232_Frame_Data], (uint8_t *)&(tool_state[temp_uart_frame_data[RS232_Frame_INDEX]]), length_data))
		{
			new_uart_frame_flag = false; //!!!!!
			return UART_FRAME_WR_NR_ERR;
		}	
		
		new_uart_frame_flag = false; //!!!!!
		return 0;
	}
	
	/*****Command write.*****/
	if(temp_uart_frame_data[RS232_Frame_CMD]==CMDTYPE_WR)		
	{
		uint8_t *pdata = (uint8_t *)&(tool_state[temp_uart_frame_data[RS232_Frame_INDEX]]);  //*pdata point to system_state data.
		for(uint8_t i=0; i<length_data; i++)  //data length = frame length -2
		{
			*(pdata+i) = temp_uart_frame_data[RS232_Frame_Data+i];
		}
		
		/*Compare data after writing*/
		if(memcmp(&temp_uart_frame_data[RS232_Frame_Data], (uint8_t *)&(tool_state[temp_uart_frame_data[RS232_Frame_INDEX]]), length_data))
		{
			uint8_t serial_ack_data[8] = {							//generate writing failure ack data.
				0x55, 0xAA,  //frame header
				0x03,				 //frame length = 1+2
				temp_uart_frame_data[RS232_Frame_ID], 		//ID
				temp_uart_frame_data[RS232_Frame_CMD],		//CMD
				temp_uart_frame_data[RS232_Frame_INDEX],	//Index
				0x00,		//1,correct; 0,fail.
				(uint8_t)(0x03+temp_uart_frame_data[RS232_Frame_ID]+temp_uart_frame_data[RS232_Frame_CMD]+temp_uart_frame_data[RS232_Frame_INDEX]+0x01)		//check_sum
			};
			
			BSP_UART_Send(&debug_uart, serial_ack_data, 8);
			new_uart_frame_flag = false; //!!!!!
			return UART_FRAME_WR_ERR;
		}
		
		uint8_t serial_ack_data[8] = {			//generate ack data.
				0x55, 0xAA,  //frame header
				0x03,				 //frame length = 1+2
				temp_uart_frame_data[RS232_Frame_ID], 		//ID
				temp_uart_frame_data[RS232_Frame_CMD],		//CMD
				temp_uart_frame_data[RS232_Frame_INDEX],	//Index
				0x01,		//1,correct; 0,fail.
				(uint8_t)(0x03+temp_uart_frame_data[RS232_Frame_ID]+temp_uart_frame_data[RS232_Frame_CMD]+temp_uart_frame_data[RS232_Frame_INDEX]+0x01)		//check_sum
			};
		
		BSP_UART_Send(&debug_uart, serial_ack_data, 8);
		new_uart_frame_flag = false; //!!!!!
		return 0;
	}

	/*****Command Read.*****/
	if(temp_uart_frame_data[RS232_Frame_CMD]==CMDTYPE_RD)		//Command read.
	{
		uint8_t *pdata = (uint8_t *)&(tool_state[temp_uart_frame_data[RS232_Frame_INDEX]]);
	
		uint8_t serial_ack_data[48] = {0};  //generate ack data buffer
		uint8_t serial_ack_size = 7+temp_uart_frame_data[RS232_Frame_Data]; //valid frame size
		serial_ack_data[RS232_Frame_Head_H] = 0x55;
		serial_ack_data[RS232_Frame_Head_L] = 0xaa;
		serial_ack_data[RS232_Frame_Length] = 2 + temp_uart_frame_data[RS232_Frame_Data];
		serial_ack_data[RS232_Frame_ID] = temp_uart_frame_data[RS232_Frame_ID];
		serial_ack_data[RS232_Frame_CMD] = temp_uart_frame_data[RS232_Frame_CMD];
		serial_ack_data[RS232_Frame_INDEX] = temp_uart_frame_data[RS232_Frame_INDEX];
		for(uint8_t i=0; i<temp_uart_frame_data[RS232_Frame_Data]; i++)
		{
			serial_ack_data[RS232_Frame_Data+i] = *(pdata+i);
		}
		
		uint8_t check_sum = 0;
		for(uint8_t i=0; i<4 + temp_uart_frame_data[RS232_Frame_Data]; i++)
		{
			check_sum += serial_ack_data[RS232_Frame_Length+i];
		}
		serial_ack_data[serial_ack_size-1] = check_sum;
		
		BSP_UART_Send(&debug_uart, serial_ack_data, serial_ack_size);

		new_uart_frame_flag = false; //!!!!!
		return 0;
	}
	
	new_uart_frame_flag = false; //!!!!!
	return UART_FRAME_CMD_ERR;
}



/**
  * @brief  Decode CAN message. 
  * @param  None.
  * @retval 0-success; 1-fail.
  */
uint8_t MSG_Decoding_CAN(void)
{
	uint8_t temp_can_cmd_data[8] = {0};
	memcpy(temp_can_cmd_data, can_cmd_data, can_cmd_size);
	
	uint8_t *pdata = (uint8_t *)&(tool_state[temp_can_cmd_data[Frame_INDEX_CAN]]);

	/*****write data into board without response*****/
	if(temp_can_cmd_data[Frame_CMD_CAN]==CMDTYPE_WR_NR)
	{
		uint16_t length_data = can_cmd_size-2;
		for(uint16_t i=0; i<length_data; i++)
		{
			*(pdata+i) = temp_can_cmd_data[Frame_Data_Init_CAN+i];
		}
		
		if(memcmp(&temp_can_cmd_data[Frame_Data_Init_CAN], (uint8_t *)&(tool_state[temp_can_cmd_data[Frame_INDEX_CAN]]), length_data))
		{
			new_can_cmd_flag = false;
			return CAN_WR_NR_ERR;
		}
		
		new_can_cmd_flag = false;
		return 0;
	}
		
	/*****write data into board*****/
	if(temp_can_cmd_data[Frame_CMD_CAN]==CMDTYPE_WR)
	{
		uint16_t length_data = can_cmd_size-2;
		for(uint16_t i=0; i<length_data; i++)
		{
			*(pdata+i) = temp_can_cmd_data[Frame_Data_Init_CAN+i];
		}
		
		uint16_t Can_ID = tool_state[SYS_ID] + 0x100;
		uint8_t can_ack_data[8] = {0};  //generate ack data buffer

		can_ack_data[Frame_CMD_CAN] = temp_can_cmd_data[Frame_CMD_CAN];
		can_ack_data[Frame_INDEX_CAN] = temp_can_cmd_data[Frame_INDEX_CAN];
		
		if(memcmp(&temp_can_cmd_data[Frame_Data_Init_CAN], (uint8_t *)&(tool_state[temp_can_cmd_data[Frame_INDEX_CAN]]), length_data))
		{
			//fail to write.
			can_ack_data[Frame_Data_Init_CAN] = 0x00;
			
			BSP_CANx_SendNormalData(Can_ID, can_ack_data, 3); //!!!!!!!!!!!!!!!!!
			new_can_cmd_flag = false;
			return CAN_WR_ERR;
		}
		
		can_ack_data[Frame_Data_Init_CAN] = 0x01;
		BSP_CANx_SendNormalData(Can_ID, can_ack_data, 3); //!!!!!!!!!!!!!!!!!
		new_can_cmd_flag = false;
		return 0;		
	}		
	
	/*****read data from board*****/
	if(temp_can_cmd_data[Frame_CMD_CAN]==CMDTYPE_RD)
	{
		uint16_t send_times = temp_can_cmd_data[Frame_Data_Init_CAN]/6;
		uint16_t send_left = temp_can_cmd_data[Frame_Data_Init_CAN]%6;
		uint16_t i=0;
		uint16_t Can_ID = tool_state[SYS_ID] + 0x100;
		
		for(i=0; i<send_times; i++)
		{
			uint8_t can_ack_data[8] = {0};  //generate ack data buffer

			can_ack_data[Frame_CMD_CAN] = temp_can_cmd_data[Frame_CMD_CAN];
			can_ack_data[Frame_INDEX_CAN] = temp_can_cmd_data[Frame_INDEX_CAN] + i*6;
			for(uint8_t j=0; j<8; j++)
			{
				can_ack_data[Frame_Data_Init_CAN+j] = *(pdata+i*8+j); //8->6
			}
			
			BSP_CANx_SendNormalData(Can_ID, can_ack_data, 8);      //!!!!!!!!!!!!!!!!!
		}
		
		uint8_t can_ack_data[8] = {0};  //generate ack data buffer
		
		can_ack_data[Frame_CMD_CAN] = temp_can_cmd_data[Frame_CMD_CAN];
		can_ack_data[Frame_INDEX_CAN] = temp_can_cmd_data[Frame_INDEX_CAN] + i*6;
		for(uint8_t j=0; j<send_left; j++)
		{
			can_ack_data[Frame_Data_Init_CAN+j] = *(pdata+i*8+j);
		}
		BSP_CANx_SendNormalData(Can_ID, can_ack_data, send_left+2); //!!!!!!!!!!!!!!!!!
		new_can_cmd_flag = false;
		return 0;		
	}	
	
	new_can_cmd_flag = false;
	return CAN_CMD_ERR;
};
