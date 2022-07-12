/*
 ******************************************************************************
 *     Copyright (c) 2018	ASIX Electronic Corporation      All rights reserved.
 *
 *     This is unpublished proprietary source code of ASIX Electronic Corporation
 *
 *     The copyright notice above does not evidence any actual or intended
 *     publication of such source code.
 ******************************************************************************
 */
#ifndef __AX58100_PWM_H__
#define __AX58100_PWM_H__

/* INCLUDE FILE DECLARATIONS */
#include "ax58100_regobjs.h"

/* NAMING CONSTANT DECLARATIONS */
#define PWM_MAX_CHANNELS					3

/* TYPE DECLARATIONS */
typedef enum
{
	PWM_PolarityPositive = 0,
	PWM_PolarityNegative,
} PWM_Polarity;

typedef enum
{
	PWM_LeftAlign = 1,
	PWM_RightAlign,
	PWM_CenterAlign,
} PWM_AlignMode;

typedef enum
{
	PWM_Channel_1 = 0,
	PWM_Channel_2,
	PWM_Channel_3,
} PWM_Channels;

typedef struct _PWM_OBJECT
{
	u16             PeriodCycle;
	u16             PwmhBbmTime;
	u16             PwmlBbmTime;	
	PWM_Polarity    PwmhPolarity[PWM_MAX_CHANNELS];
	PWM_Polarity    PwmlPolarity[PWM_MAX_CHANNELS];
	u16             PwmShiftTime[PWM_MAX_CHANNELS];
	PWM_AlignMode   AlignMode;
	u16             AbcsabHighPulseWidth;
	PWM_Polarity    AbcsabPulsePolarity;
	u16             A_PulseTrigPosition;		
	u16             B_PulseTrigPosition;
} PWM_OBJECT;

/* GLOBAL VARIABLES */

/* EXPORTED SUBPROGRAM SPECIFICATIONS */
AX_STATUS PWM_Init(PWM_OBJECT *pPwmObj);
void      PWM_DeInit(void);
void      PWM_SetHighPulseWidth(PWM_OBJECT *pPwmObj, PWM_Channels Channel, u16 HighPulseWidth);
void      PWM_SetAPulsePosition(PWM_OBJECT *pPwmObj, u16 Position);
void      PWM_Driving(PWM_Channels Channel, u8 EnableDriving);
void      PWM_H_Output(PWM_Channels Channel, u8 EnableOutput);
void      PWM_L_Output(PWM_Channels Channel, u8 EnableOutput);
void      PWM_A_Output(u8 EnableOutput);
void      PWM_B_Output(u8 EnableOutput);
void      PWM_C_Output(u8 EnableOutput);
void      PWM_Z_Output(u8 EnableOutput);
void      PWM_AB_Output(u8 EnableOutput);
void      PWM_FuncEnable(void);
void      PWM_FuncDisable(void);
void      PWM_StopAllOutputs(void);
void      PWM_AllDriving(u8 EnableDriving);
void      PWM_All_PWM_Outputs(u8 EnableOutput);
void      PWM_All_L_Outputs(u8 EnableOutput);
void      PWM_H_Polarity(PWM_Channels Channel, PWM_Polarity HighPolarity);
void      PWM_L_Polarity(PWM_Channels Channel, PWM_Polarity LowPolarity);
u8        Check_PWM_OutputEnabled(void);

#endif /* __AX58100_PWM_H__ */

/* End of ax58100_pwm.h */
