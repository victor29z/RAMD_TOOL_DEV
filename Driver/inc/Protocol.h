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
#ifndef __PROTOCAL_H
#define __PROTOCAL_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"


/* Private Includes ----------------------------------------------------------*/
#include "BSP_UART.h"
#include "BSP_CAN.h"


/* Private Typedefs ----------------------------------------------------------*/


/* Macros --------------------------------------------------------------------*/
//Frame of RS232
#define TEMP_UART_FRAME_SIZE 		64

#define RS232_Frame_Head_H			0
#define RS232_Frame_Head_L			1
#define RS232_Frame_Length			2
#define RS232_Frame_ID					3
#define RS232_Frame_CMD					4
#define RS232_Frame_INDEX				5
#define RS232_Frame_Data				6

#define Frame_Header_RS232 			(uint16_t)((0x55<<8)|(0xaa))					//Header of frame
#define Frame_WR_Ack_Length_RS232		0x03
	
//Frame of CAN
#define Frame_CMD_CAN					0
#define Frame_INDEX_CAN				1
#define Frame_Data_Init_CAN		2	


// System state
#define			SYS_ID											0x01			//Driver ID
#define  		SYS_MODEL_TYPE							0x02			//Driver Model. 1-AJ3; 2-AJ5; 3-AJ10
#define			SYS_FW_VER									0x03			//Firmwire version. 1.0.0
#define			SYS_ERROR										0x04			//Error code.
#define			SYS_VOLTAGE									0x05			//System voltagy.(0.01V).
#define			SYS_TEMP										0x06			//system temperature.(0.1C).
#define			SYS_BAUDRATE_485						0x07			//RS232 port baud rate. 0-19200; 1-115200; 2-500k; 3-1M.				
#define			SYS_BAUDRATE_CAN						0x08			//CAN baud rate. 0-250k; 1-500k; 2-1M.

#define			SYS_IO_PWR_ENABLE						0x0a			//IO ports power enable flag. 0-IO power off; 1-IO power on.
#define			SYS_SAVE_TO_FLASH						0x0b			//Flag of saving data onto flash.
#define			SYS_CLEAR_ERROR							0x0c			//clear error flags.

#define			SYS_CURRENT_L								0x10			//Low 16bits of current (mA).
#define			SYS_CURRENT_H								0x11			//High 16bits of current(mA).

#define			ACD_CAL_DEF0								0x1c			//axial calibration data0.
#define			ACD_CAL_DEF1								0x1d			//axial calibration data1.
#define			ACD_CAL_DEF2								0x1e			//axial calibration data2.
#define			ACD_CAL_DEF3								0x1f			//axial calibration data3.

#define			MODEL_TYPE									0x26			//Module type. 0-machine; 1-Cast.
#define			MODEL_ID										0X27			//						

#define			LIT_MAX_CURRENT							0x30			//Limitation of maximum current (mA).

#define			MPU_TEMP_DATA								0x36			//Temperature of MPU.
#define			MPU_ACC_X_DATA							0x37			//ACC value on x axis of MPU
#define			MPU_ACC_Y_DATA							0x38			//ACC value on y axis of MPU
#define			MPU_ACC_Z_DATA							0x39			//ACC value on z axis of MPU
#define			MPU_GYR_X_DATA							0x3a			//Gyro value on x axis of MPU
#define			MPU_GYR_Y_DATA							0x3b			//Gyro value on y axis of MPU
#define			MPU_GYR_Z_DATA							0x3c			//Gyro value on z axis of MPU
#define			MPU_MAG_X_DATA							0x3d			//Magnet value on x axis of MPU
#define			MPU_MAG_Y_DATA							0x3e			//Magnet value on y axis of MPU
#define			MPU_MAG_Z_DATA							0x3f			//Magnet value on Z axis of MPU
#define			MPU_INST_DRCT								0x40			//0-Normal;1-Reverse

#define			ANLG_INPUT1_TYPE						0x47			//Analog input1 type:0-Voltage;1-Current;2-Float
#define			ANLG_INPUT2_TYPE						0x48			//Analog input2 type:0-Voltage;1-Current;2-Float
#define			ANLG_INPUT1_VAL_L						0x49			//Analog input1 value low byte.
#define			ANLG_INPUT1_VAL_H						0x4a			//Analog input1 value high byte.
#define			ANLG_INPUT2_VAL_L						0x4b			//Analog input2 value low byte.
#define			ANLG_INPUT2_VAL_H						0x4c			//Analog input2 value high byte.

#define			USER_RS485_ENABLE						0x50			//User RS485 enable flag:0-disable; 1-Enable.
#define			USER_RS485_BAUDRATE					0x51			//User RS485 Baudrate:0-9600; 1-19200; 2-38400; 3-57600; 3-115200; 4-1M; 5-2M; 6-5M.

#define			TOOL_OUTPUT_VOLT						0x56			//tool output voltage:0-0v;1-12v;2-24V.
#define			DO0_TYPE										0x57			//0-Sinking(NPN);1-Source(PNP);2-PP;3-Dual Pin Power
#define			DO1_TYPE										0x58			//0-Sinking(NPN);1-Source(PNP);2-PP;3-Dual Pin Power
#define			DO0_STATUS									0x59			//0-Inactive;1-Active
#define			DO1_STATUS									0x5a			//0-Inactive;1-Active
#define			DI0_STATUS									0x5b
#define			DI1_STATUS									0x5c

// Macro definition of command type
#define CMDTYPE_RD			0x01		/**< Reading command type */
#define CMDTYPE_WR			0x02		/**< Writing command type */
#define CMDTYPE_WR_NR		0x03		/**< Writing command type. No reutrn */
#define CMDTYPE_WR_REG	0x04		/**< Asynchronous writing command type (Reserved) */
#define CMDTYPE_SCP			0x05		/**< Command for data return of oscilloscope (Reserved) */
#define CMDTYPE_RST			0x011		/**< Reset the control table (Reset) */

// Macro definition of Uart decoding error
#define UART_FRAME_HEAD_ERR					0x01		/**< header error */
#define UART_FRAME_LEN_ERR					0x02		/**< data length error */
#define UART_FRAME_CHKSUM_ERR				0x03		/**< check sum error */
#define UART_FRAME_ID_ERR						0x04		/**< ID error */
#define UART_FRAME_WR_NR_ERR				0x05		/**< writing without response error */
#define UART_FRAME_WR_ERR						0x06		/**< writing error */
#define UART_FRAME_CMD_ERR					0x07		/**< unknown command error */


// Macro definition of CAN decoding error
#define CAN_WR_NR_ERR					0x01		/**< writing without response error */
#define CAN_WR_ERR						0x02		/**< writing error */
#define CAN_CMD_ERR						0x03		/**< unknown command error */

#define TOOL_STATE_BUF_SIZE  96
/* Private Variables ---------------------------------------------------------*/


/* External Variables --------------------------------------------------------*/
extern uint16_t tool_state[TOOL_STATE_BUF_SIZE];
extern bool new_uart_frame_flag;
extern bool new_can_cmd_flag;
//extern uint16_t uart_frame_data[];

extern uint8_t temp_uart_frame_data[TEMP_UART_FRAME_SIZE];

/* Exported Functions --------------------------------------------------------*/
uint8_t UART_Frame_Check(void);

uint8_t MSG_Decoding_UART(void);
uint8_t MSG_Decoding_CAN(void);

#endif


/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/

