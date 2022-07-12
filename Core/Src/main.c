/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "can.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "samplehw.h"
#include "ecatappl.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
//void Test(void);
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void Test(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
	
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_CAN1_Init();
  MX_I2C2_Init();
  MX_SPI2_Init();
  MX_USART6_UART_Init();
  MX_TIM4_Init();
  MX_TIM6_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_FSMC_Init();
  MX_TIM7_Init();
  MX_TIM9_Init();
  /* USER CODE BEGIN 2 */
	/* Keep initializing bsp until success */
	while (BSP_Global_Init())
	{
		printf("BSP init failed ... \r\n");
		BSP_LED1_Toggle;
		Delay_ms(500);
	}
	
	/* Keep checking encryption until success */
//	while (BSP_Encrypt_Chip_Check())
//	{
//		printf("Encryption check failed ... \r\n");
//		BSP_LED1_Toggle;
//		Delay_ms(500);
//	}
	
	/* Bootloader related*/
//	if (firmware_update)
//	{
//		printf("To update firmware ... \r\n");
//		// To do
//	}
	
	/* Keep searching for IMU until found */
	while (Find_IMU())
	{
		printf("IMU not found ... \r\n");
		BSP_LED1_Toggle;
		Delay_ms(500);
	}
	
	/* Base Init*/
	//Flash_Mem_Read(base_state, BASE_STATE_BUF_SIZE*2, FLASH_START_ADDR_SYSTEM_STATE);
	//Put everything to default safe state
	
//	BSP_Clock_Register(&runtime_clock);
	
	printf("\r\nReady to go ... \r\n");
	//Test();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		House_Keeping();
		
		//CMD_Processing();

//	  HAL_Delay(5000);
	  //BSP_LED1_Toggle;
//	  BSP_CAN_Test();
//	  Get_Tool_Temp();
//	  BSP_I2C_test();
//	  BSP_Get_Chip_ID();
//	  BSP_Output_PWR_Test();
//	  BSP_Output_DO_Test();
	  //Test();

#if (ETHERCAT_SLAVE_STACK_ENABLE)
		HW_IntrDequeue();
		MainLoop();
#endif

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void Test(void)   //���Ը��ֹ���
{
	BSP_LED1_ON;  //����LED
	
	/*CPU ID Test*/
	BSP_Get_Chip_ID();
	printf("Chip ID: %X-%X-%X\r\n",CPU_ID[0],CPU_ID[1],CPU_ID[2]);
	printf("Flash Size: %dK \r\n\r\n", *(__IO uint16_t *)(0x1FFF7A22));
	HAL_Delay(1000);
	
	/*Debug Uart Test*/
	printf("Smokie BSP  : STM32F405RGT6_v1.0.1\r\n");
	printf("Date        : 07-12-2020\r\n");
	printf("COPYRIGHT 2020 Smokie Robotics, Inc\r\n\r\n");
	HAL_Delay(1000);
	
	/*��Դ�������������??*/
	DIO_Power_On();
	DO_PWR_Config(PWR_24);
//	DO0_Config(DO_Port_Active, DO_Port_Type_NPN);

////set DO0 to GND
//	BSP_CPUIO2_OFF;
//	BSP_CPUIO3_ON;
//
	DO1_Config(DO_Port_Active, DO_Port_Type_PP);
	DO0_Config(DO_Port_Active, DO_Port_Type_PP);
	BSP_Output_DO0(Port_ON);
	BSP_Output_DO1(Port_ON);
//	AI_Port_Config(Read_Voltage);
	AI_Port_Config(Read_Current);

//	BSP_SPST_485_EN();
	FT485_Transmit_ENABLE;

	uint8_t rs485_data[3]={0xA,0xB,0xC};

	while(1)
	{
		printf("TI0 Value: %d \r\n",Read_DI_Port(Port_TI0));
		printf("TI1 Value: %d \r\n\n",Read_DI_Port(Port_TI1));
//		printf("Ain1 Value: %ld \r\n",AI_Port_Read(Port_AI0, Read_Voltage));
//		printf("Ain2 Value: %ld \r\n",AI_Port_Read(Port_AI1, Read_Voltage));
		printf("Ain1 Value: %ld \r\n",AI_Port_Read(Port_AI0, Read_Current));
		printf("Ain2 Value: %ld \r\n\n",AI_Port_Read(Port_AI1, Read_Current));
//		HAL_UART_Transmit(&huart1, rs485_data, 3, 1000);

		printf("STO0 Value: %d \r\n", STO0_Read());
		printf("STO1 Value: %d \r\n", STO1_Read());

//		Robot_State_Printf();
		HAL_Delay(1000);
	}
	
}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
