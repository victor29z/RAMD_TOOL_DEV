/**
  ******************************************************************************
  * @FileName:		PID_CTRL.c
  * @Author:		Hui
  * @Version:		V1.0.0
  * @Date:			06-23-2020
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
#include "PID_CTRL.h"

/* Private Includes ----------------------------------------------------------*/

/* Private Typedefs ----------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private Variables ---------------------------------------------------------*/
_pid pid = {
	0.0,     	//SetValue
	0.0,			//ActualValue
	0.0,			//Err
	0.0,			//Err_last
	0.1,			//Kp
	0.015,		//Ki
	0.01,			//Kd
	0.0,			//output
	0.0,			//integral
	300,			//integral_threshold
	1000,			//output_max
	0					//output_min
};
/* External Variables --------------------------------------------------------*/

/* Exported Functions --------------------------------------------------------*/
/**
  * @brief  Write robot ID into EEPROM.
  * @param  None
	* @retval 1:Error; 0:correct.
  */
void PID_Init(_pid pid)
{
	printf("PID_init begin \n");
	pid.SetValue = 0.0;
	pid.ActualValue = 0.0;
	pid.Err = 0.0;
	pid.Err_last = 0.0;
	pid.output = 0.0;
	pid.integral = 0.0;
	pid.Kp = 0.1;
	pid.Ki = 0.015;
	pid.Kd = 0.02;
	pid.output_max = 10000;
	pid.output_min = 0;
	printf("PID_Init end\n");
};


void PID_Inc_Init(_pid_inc pid_inc)
{
	pid_inc.SetValue = 0.0;
	pid_inc.ActualValue = 0.0;
	pid_inc.Err = 0.0;
	pid_inc.Err_last = 0.0;
	pid_inc.Err_next = 0.0;
	pid_inc.Kp = 0.005;
	pid_inc.Ki = 0.015;
	pid_inc.Kd = 0.02;
};


float PID_Realize(float target_value, float real_value)
{
	uint8_t integral_index;
	int8_t PWM_Dutycycle = 0;
	pid.SetValue = target_value;
	pid.ActualValue = real_value;
	pid.Err = pid.ActualValue - pid.SetValue;
	printf("pid.Err = %f\n", pid.Err);
//	if(pid.output > pid.output_max)
//	{
//		if(fabs(pid.Err) > pid.integral_threshold)
//			integral_index = 0;
//		else
//		{
//			integral_index = 1;
//			if(pid.Err<0)
//				pid.integral += pid.Err;
//		}
//	}
//	
//	else if(pid.output < pid.output_min)
//	{
//		if(fabs(pid.Err) > pid.integral_threshold)
//			integral_index = 0;
//		else
//		{
//			integral_index = 1;
//			if(pid.Err>0)
//				pid.integral += pid.Err;
//		}
//	}
//	
//	else
//	{
//		if(fabs(pid.Err) > pid.integral_threshold)
//			integral_index = 0;
//		else
//		{
//			integral_index = 1;
//			pid.integral += pid.Err;
//		}
//	}
		
//	pid.output = -(pid.Kp*pid.Err + integral_index*pid.Ki*pid.integral + pid.Kd*(pid.Err-pid.Err_last));

	if(fabs(pid.Err) > pid.integral_threshold)
		integral_index = 0;
	else
	{
		integral_index = 1;
		pid.integral += pid.Err;
	}
		pid.output = pid.Kp*pid.Err + pid.Ki*pid.integral;
//	pid.output = -(pid.Kp*pid.Err + pid.Ki*pid.integral + pid.Kd*(pid.Err-pid.Err_last));
//	pid.output =-pid.Kp*pid.Err;
	printf("pid.output = %f\n", pid.output);
	
	pid.Err_last = pid.Err;
	
	PWM_Dutycycle = pid.output;
	
	if(PWM_Dutycycle<0)
		PWM_Dutycycle=0;
	if(PWM_Dutycycle>100)
		PWM_Dutycycle=100;
	
	return PWM_Dutycycle;
};



float PID_Inc_Realize(_pid_inc pid_inc, float target_value)
{
	pid_inc.SetValue = target_value;
	pid_inc.Err = pid_inc.SetValue - pid_inc.ActualValue;
	float inc_output = pid_inc.Kp*(pid_inc.Err-pid_inc.Err_next) + pid_inc.Ki*pid_inc.Err + pid_inc.Kd*(pid_inc.Err-2*pid_inc.Err_next+pid_inc.Err_last);
	
	pid_inc.ActualValue += inc_output;
	pid_inc.Err_last = pid_inc.Err_next;
	pid_inc.Err_next = pid_inc.Err;
	
	return pid_inc.ActualValue;
};
/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/


