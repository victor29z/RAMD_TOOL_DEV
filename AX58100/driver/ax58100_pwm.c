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

/* INCLUDE FILE DECLARATIONS */
#include "ax_intf.h"

#ifdef AX58100_PWM_MODULE_ENABLED
#include "ax58100_pwm.h"

/* NAMING CONSTANT DECLARATIONS */

/* TYPE DECLARATIONS */

/* GLOBAL VARIABLES DECLARATIONS */

/* LOCAL VARIABLES DECLARATIONS */
static MCTLR_OBJECT   mctlr;
static PXCFGR_OBJECT  pxcfgr;
static PBBMR_OBJECT   pbbmr;
static PxCTRLR_OBJECT pxctrlr;

/* LOCAL SUBPROGRAM DECLARATIONS */

/* LOCAL SUBPROGRAM BODIES */


/* EXPORTED SUBPROGRAM BODIES */

/*
 * ----------------------------------------------------------------------------
 * Function Name: PWM_Init
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
AX_STATUS PWM_Init(PWM_OBJECT *pPwmObj)
{
	u16 tmp16;
	
	if (pPwmObj == 0)
	{
		return AX_STATUS_ERR;
	}
	
	PWM_DeInit();
	
	/* Disable A/B/C/S/AB outputs */	
	pxcfgr.d16 = 0;
	pxcfgr.b.a_pulse_output_enable = 0;
	pxcfgr.b.b_pulse_output_enable = 0;
	pxcfgr.b.c_pulse_output_enable = 0;
	pxcfgr.b.s_pulse_output_enable = 0;
	pxcfgr.b.ab_pulse_output_enable = 0;		
	/* Set A/B/C/S/AB pulse width */
	pxcfgr.b.abcsab_high_pulse_width = (pPwmObj->AbcsabHighPulseWidth < 2)?2:pPwmObj->AbcsabHighPulseWidth;
	/* Set A/B/C/S/AB pulse polarity */	
	pxcfgr.b.abcsab_pulse_pol = pPwmObj->AbcsabPulsePolarity;	
	/* Set PWM alignment mode */	
	pxcfgr.b.pwm_align_mode = pPwmObj->AlignMode;	
	AX_INTF_Write(PXCFGR, &pxcfgr.d16, 2);		
	
	/* Set A pulse trigger position */
	AX_INTF_Write(PTAPPR, &pPwmObj->A_PulseTrigPosition, 2);

	/* Set B pulse trigger position */
	AX_INTF_Write(PTBPPR, &pPwmObj->B_PulseTrigPosition, 2);
	
	/* Set PWM period cycle */
	AX_INTF_Write(PPCR, &pPwmObj->PeriodCycle, 2);
	
	/* Set PWM_H BBM time */	
	pbbmr.b.pwm_h_bbm_time = pPwmObj->PwmhBbmTime;
	/* Set PWM_H BBM time */	
	pbbmr.b.pwm_l_bbm_time = pPwmObj->PwmlBbmTime;	
	AX_INTF_Write(PBBMR, &pbbmr.d16, 2);
	
	/* Disable PWM 1 driving and signals output */	
	pxctrlr.d16 = 0;
	pxctrlr.b.pwm_h_output_enable = 0;
	pxctrlr.b.pwm_l_output_enable = 0;
	pxctrlr.b.pwm_channel_enable = 0;
	/* Set PWM 1 polarity */
	pxctrlr.b.pwm_h_pol_is_neg = pPwmObj->PwmhPolarity[0];	
	pxctrlr.b.pwm_l_pol_is_neg = pPwmObj->PwmlPolarity[0];		
	AX_INTF_Write(P1CTRLR, &pxctrlr.d16, 2);

	/* Set PWM 1 shift time */
	AX_INTF_Write(P1SHR, &pPwmObj->PwmShiftTime[0], 2);	
	
	/* Set PWM 1 high pulse width */
	tmp16 = 1;
	AX_INTF_Write(P1HPWR, &tmp16, 2);
	
	/* Disable PWM 2 driving and signals output */
	pxctrlr.d16 = 0;
	pxctrlr.b.pwm_h_output_enable = 0;
	pxctrlr.b.pwm_l_output_enable = 0;
	pxctrlr.b.pwm_channel_enable = 0;
	/* Set PWM 2 polarity */		
	pxctrlr.b.pwm_h_pol_is_neg = pPwmObj->PwmhPolarity[1];
	pxctrlr.b.pwm_l_pol_is_neg = pPwmObj->PwmlPolarity[1];	
	AX_INTF_Write(P2CTRLR, &pxctrlr.d16, 2);
	
	/* Set PWM 2 shift time */
	AX_INTF_Write(P2SHR, &pPwmObj->PwmShiftTime[1], 2);	
	
	/* Set PWM 2 high pulse width */
	tmp16 = 1;
	AX_INTF_Write(P2HPWR, &tmp16, 2);
	
	/* Disable PWM 3 driving and signals output */	
	pxctrlr.b.pwm_h_output_enable = 0;
	pxctrlr.b.pwm_l_output_enable = 0;
	pxctrlr.b.pwm_channel_enable = 0;
	/* Set PWM 3 polarity */		
	pxctrlr.b.pwm_h_pol_is_neg = pPwmObj->PwmhPolarity[2];
	pxctrlr.b.pwm_l_pol_is_neg = pPwmObj->PwmlPolarity[2];		
	AX_INTF_Write(P3CTRLR, &pxctrlr.d16, 2);
	
	/* Set PWM 3 shift time */
	AX_INTF_Write(P3SHR, &pPwmObj->PwmShiftTime[2], 2);		
	
	/* Set PWM 3 high pulse width */
	tmp16 = 1;
	AX_INTF_Write(P3HPWR, &tmp16, 2);

	/* Enable PWM function */	
	mctlr.d16 = 0;
	mctlr.b.pwm_func_enable = 1;
	mctlr.b.pwm_8x_enable = 0;
	mctlr.b.step_func_enable = 0;/* Shall disable STEP function */
	AX_INTF_Write(MCTLR, &mctlr.d16, 2);	
	
	return AX_STATUS_OK;
} /* End of PWM_Init() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: PWM_DeInit
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void PWM_DeInit(void)
{
	u16 tmp16 = 0;
	
	/* Disable PWM channel 1 driving and pulse outputs */		
	AX_INTF_Write(P1CTRLR, &tmp16, 2);
	
	/* Disable PWM channel 2 driving and pulse outputs */			
	AX_INTF_Write(P2CTRLR, &tmp16, 2);

	/* Disable PWM channel 3 driving and pulse outputs */			
	AX_INTF_Write(P3CTRLR, &tmp16, 2);

	/* Disable PWM function */		
	AX_INTF_Write(MCTLR, &tmp16, 2);	
	
} /* End of PWM_DeInit() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: PWM_Driving
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void PWM_Driving(PWM_Channels Channel, u8 EnableDriving)
{
	switch (Channel)
	{
	case PWM_Channel_1:
		AX_INTF_Read(P1CTRLR, &pxctrlr.d16, 2);	
		pxctrlr.b.pwm_channel_enable = ((EnableDriving == 0) ? 0:1);
		AX_INTF_Write(P1CTRLR, &pxctrlr.d16, 2);
		break;
	
	case PWM_Channel_2:
		AX_INTF_Read(P2CTRLR, &pxctrlr.d16, 2);	
		pxctrlr.b.pwm_channel_enable = ((EnableDriving == 0) ? 0:1);
		AX_INTF_Write(P2CTRLR, &pxctrlr.d16, 2);
		break;
	
	case PWM_Channel_3:
		AX_INTF_Read(P3CTRLR, &pxctrlr.d16, 2);	
		pxctrlr.b.pwm_channel_enable = ((EnableDriving == 0) ? 0:1);
		AX_INTF_Write(P3CTRLR, &pxctrlr.d16, 2);
		break;
	}
} /* End of PWM_Driving() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: PWM_SetHighPulseWidth
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void PWM_SetHighPulseWidth(PWM_OBJECT *pPwmObj, PWM_Channels Channel, u16 HighPulseWidth)
{
	if (pPwmObj->AlignMode == PWM_LeftAlign)
	{
		HighPulseWidth += pPwmObj->PwmhBbmTime;
		if ((HighPulseWidth + pPwmObj->PwmlBbmTime + pPwmObj->PwmShiftTime[Channel]) > pPwmObj->PeriodCycle)
		{
			HighPulseWidth = pPwmObj->PeriodCycle - (pPwmObj->PwmlBbmTime + pPwmObj->PwmShiftTime[Channel]);
		}
	}
	else if (pPwmObj->AlignMode == PWM_RightAlign)
	{
		HighPulseWidth += pPwmObj->PwmhBbmTime;		
		if ((HighPulseWidth + pPwmObj->PwmlBbmTime + pPwmObj->PwmShiftTime[Channel]) > pPwmObj->PeriodCycle)
		{
			HighPulseWidth = pPwmObj->PeriodCycle - (pPwmObj->PwmlBbmTime + pPwmObj->PwmShiftTime[Channel]);
		}		
	}
	else if (pPwmObj->AlignMode == PWM_CenterAlign)
	{
		HighPulseWidth += pPwmObj->PwmhBbmTime;
		if (((HighPulseWidth/2) + pPwmObj->PwmlBbmTime + pPwmObj->PwmShiftTime[Channel]) > (pPwmObj->PeriodCycle/2))
		{
			HighPulseWidth = pPwmObj->PeriodCycle - 2*(pPwmObj->PwmlBbmTime + pPwmObj->PwmShiftTime[Channel]);
		}			
	}
	
	switch (Channel)
	{
	case PWM_Channel_1:
		AX_INTF_Write(P1HPWR, &HighPulseWidth, 2);
		break;
	
	case PWM_Channel_2:
		AX_INTF_Write(P2HPWR, &HighPulseWidth, 2);
		break;
	
	case PWM_Channel_3:
		AX_INTF_Write(P3HPWR, &HighPulseWidth, 2);
		break;
	}
} /* End of PWM_SetHighPulseWidth() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: PWM_H_Output
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void PWM_H_Output(PWM_Channels Channel, u8 EnableOutput)
{
	switch (Channel)
	{
	case PWM_Channel_1:
		AX_INTF_Read(P1CTRLR, &pxctrlr.d16, 2);	
		pxctrlr.b.pwm_h_output_enable = ((EnableOutput == 0) ? 0:1);
		AX_INTF_Write(P1CTRLR, &pxctrlr.d16, 2);
		break;

	case PWM_Channel_2:		
		AX_INTF_Read(P2CTRLR, &pxctrlr.d16, 2);	
		pxctrlr.b.pwm_h_output_enable = ((EnableOutput == 0) ? 0:1);
		AX_INTF_Write(P2CTRLR, &pxctrlr.d16, 2);
		break;
		
	case PWM_Channel_3:
		AX_INTF_Read(P3CTRLR, &pxctrlr.d16, 2);	
		pxctrlr.b.pwm_h_output_enable = ((EnableOutput == 0) ? 0:1);
		AX_INTF_Write(P3CTRLR, &pxctrlr.d16, 2);
		break;
	}
} /* End of PWM_H_Output() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: PWM_L_Output
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void PWM_L_Output(PWM_Channels Channel, u8 EnableOutput)
{
	switch (Channel)
	{
	case PWM_Channel_1:
		AX_INTF_Read(P1CTRLR, &pxctrlr.d16, 2);	
		pxctrlr.b.pwm_l_output_enable = ((EnableOutput == 0) ? 0:1);
		AX_INTF_Write(P1CTRLR, &pxctrlr.d16, 2);
		break;

	case PWM_Channel_2:		
		AX_INTF_Read(P2CTRLR, &pxctrlr.d16, 2);	
		pxctrlr.b.pwm_l_output_enable = ((EnableOutput == 0) ? 0:1);
		AX_INTF_Write(P2CTRLR, &pxctrlr.d16, 2);
		break;
		
	case PWM_Channel_3:
		AX_INTF_Read(P3CTRLR, &pxctrlr.d16, 2);	
		pxctrlr.b.pwm_l_output_enable = ((EnableOutput == 0) ? 0:1);
		AX_INTF_Write(P3CTRLR, &pxctrlr.d16, 2);
		break;
	}
} /* End of PWM_L_Output() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: PWM_StopAllOutputs
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void PWM_StopAllOutputs(void)
{
	/* Disable A/B/Z pulse outputs */		
	AX_INTF_Read(PXCFGR, &pxcfgr.d16, 2);	
	pxcfgr.b.a_pulse_output_enable = 0;
	pxcfgr.b.b_pulse_output_enable = 0;
	pxcfgr.b.c_pulse_output_enable = 0;
	pxcfgr.b.ab_pulse_output_enable = 0;
	pxcfgr.b.s_pulse_output_enable = 0;
	AX_INTF_Write(PXCFGR, &pxcfgr.d16, 2);	

	/* Disable PWM 1 pulse outputs but still driving */	
	AX_INTF_Read(P1CTRLR, &pxctrlr.d16, 2);	
  pxctrlr.b.pwm_h_output_enable = 0;
  pxctrlr.b.pwm_l_output_enable = 0;
	AX_INTF_Write(P1CTRLR, &pxctrlr.d16, 2);
	
	/* Disable PWM 2 pulse outputs but still driving */	
	AX_INTF_Read(P2CTRLR, &pxctrlr.d16, 2);		
  pxctrlr.b.pwm_h_output_enable = 0;
  pxctrlr.b.pwm_l_output_enable = 0;
	AX_INTF_Write(P2CTRLR, &pxctrlr.d16, 2);
	
	/* Disable PWM 3 pulse outputs but still driving */	
	AX_INTF_Read(P3CTRLR, &pxctrlr.d16, 2);		
  pxctrlr.b.pwm_h_output_enable = 0;
  pxctrlr.b.pwm_l_output_enable = 0;
	AX_INTF_Write(P3CTRLR, &pxctrlr.d16, 2);

} /* End of PWM_StopAllOutputs() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: PWM_A_Output
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void PWM_A_Output(u8 EnableOutput)
{
	AX_INTF_Read(PXCFGR, &pxcfgr.d16, 2);	
	pxcfgr.b.a_pulse_output_enable = ((EnableOutput == 0) ? 0:1);
	AX_INTF_Write(PXCFGR, &pxcfgr.d16, 2);	
} /* End of PWM_A_Output() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: PWM_B_Output
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void PWM_B_Output(u8 EnableOutput)
{
	AX_INTF_Read(PXCFGR, &pxcfgr.d16, 2);	
	pxcfgr.b.b_pulse_output_enable = ((EnableOutput == 0) ? 0:1);
	AX_INTF_Write(PXCFGR, &pxcfgr.d16, 2);	
} /* End of PWM_B_Output() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: PWM_C_Output
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void PWM_C_Output(u8 EnableOutput)
{
	AX_INTF_Read(PXCFGR, &pxcfgr.d16, 2);	
	pxcfgr.b.c_pulse_output_enable = (EnableOutput == 0) ? 0:1;
	AX_INTF_Write(PXCFGR, &pxcfgr.d16, 2);	
} /* End of PWM_C_Output() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: PWM_Z_Output
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void PWM_Z_Output(u8 EnableOutput)
{
	AX_INTF_Read(PXCFGR, &pxcfgr.d16, 2);	
	pxcfgr.b.s_pulse_output_enable = (EnableOutput == 0) ? 0:1;
	AX_INTF_Write(PXCFGR, &pxcfgr.d16, 2);	
} /* End of PWM_Z_Output() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: PWM_AB_Output
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void PWM_AB_Output(u8 EnableOutput)
{
	AX_INTF_Read(PXCFGR, &pxcfgr.d16, 2);	
	pxcfgr.b.ab_pulse_output_enable = (EnableOutput == 0) ? 0:1;
	AX_INTF_Write(PXCFGR, &pxcfgr.d16, 2);	
} /* End of PWM_AB_Output() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: PWM_FuncEnable
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void PWM_FuncEnable(void)
{
	mctlr.d16 = 0;	
	mctlr.b.pwm_func_enable = 1;
	AX_INTF_Write(MCTLR, &mctlr.d16, 2);		
} /* End of PWM_FuncEnable() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: PWM_FuncDisable
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void PWM_FuncDisable(void)
{
	mctlr.d16 = 0;	
	AX_INTF_Write(MCTLR, &mctlr.d16, 2);		
} /* End of PWM_FuncDisable() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: PWM_SetAPulsePosition
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void PWM_SetAPulsePosition(PWM_OBJECT *pPwmObj, u16 Position)
{
	if ((pPwmObj->AbcsabHighPulseWidth + Position) >= pPwmObj->PeriodCycle)
	{
		Position = (pPwmObj->PeriodCycle - pPwmObj->AbcsabHighPulseWidth);
	}
	
	AX_INTF_Write(PTAPPR, &Position, 2);
} /* End of PWM_SetAPulsePosition() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: PWM_AllDriving
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void PWM_AllDriving(u8 EnableDriving)
{
	AX_INTF_Read(P1CTRLR, &pxctrlr.d16, 2);	
	pxctrlr.b.pwm_channel_enable = ((EnableDriving == 0) ? 0:1);
	AX_INTF_Write(P1CTRLR, &pxctrlr.d16, 2);

	AX_INTF_Read(P2CTRLR, &pxctrlr.d16, 2);	
	pxctrlr.b.pwm_channel_enable = ((EnableDriving == 0) ? 0:1);
	AX_INTF_Write(P2CTRLR, &pxctrlr.d16, 2);

	AX_INTF_Read(P3CTRLR, &pxctrlr.d16, 2);	
	pxctrlr.b.pwm_channel_enable = ((EnableDriving == 0) ? 0:1);
	AX_INTF_Write(P3CTRLR, &pxctrlr.d16, 2);
} /* End of PWM_AllDriving() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: PWM_All_PWM_Outputs
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void PWM_All_PWM_Outputs(u8 EnableOutput)
{
	AX_INTF_Read(P1CTRLR, &pxctrlr.d16, 2);	
	pxctrlr.b.pwm_h_output_enable = ((EnableOutput == 0) ? 0:1);
	pxctrlr.b.pwm_l_output_enable = ((EnableOutput == 0) ? 0:1);
	AX_INTF_Write(P1CTRLR, &pxctrlr.d16, 2);
	AX_INTF_Write(P2CTRLR, &pxctrlr.d16, 2);
	AX_INTF_Write(P3CTRLR, &pxctrlr.d16, 2);
} /* End of PWM_All_PWM_Outputs() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: PWM_All_L_Outputs
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void PWM_All_L_Outputs(u8 EnableOutput)
{
	AX_INTF_Read(P1CTRLR, &pxctrlr.d16, 2);	
	pxctrlr.b.pwm_l_output_enable = ((EnableOutput == 0) ? 0:1);
	AX_INTF_Write(P1CTRLR, &pxctrlr.d16, 2);

	AX_INTF_Read(P2CTRLR, &pxctrlr.d16, 2);	
	pxctrlr.b.pwm_l_output_enable = ((EnableOutput == 0) ? 0:1);
	AX_INTF_Write(P2CTRLR, &pxctrlr.d16, 2);

	AX_INTF_Read(P3CTRLR, &pxctrlr.d16, 2);	
	pxctrlr.b.pwm_l_output_enable = ((EnableOutput == 0) ? 0:1);
	AX_INTF_Write(P3CTRLR, &pxctrlr.d16, 2);
} /* End of PWM_All_L_Outputs() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: PWM_H_Polarity
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void PWM_H_Polarity(PWM_Channels Channel, PWM_Polarity HighPolarity)
{
	switch (Channel)
	{
	case PWM_Channel_1:
		AX_INTF_Read(P1CTRLR, &pxctrlr.d16, 2);	
		pxctrlr.b.pwm_h_pol_is_neg = ((HighPolarity == PWM_PolarityPositive) ? 0:1);
		AX_INTF_Write(P1CTRLR, &pxctrlr.d16, 2);
		break;

	case PWM_Channel_2:		
		AX_INTF_Read(P2CTRLR, &pxctrlr.d16, 2);	
		pxctrlr.b.pwm_h_pol_is_neg = ((HighPolarity == PWM_PolarityPositive) ? 0:1);
		AX_INTF_Write(P2CTRLR, &pxctrlr.d16, 2);
		break;
		
	case PWM_Channel_3:
		AX_INTF_Read(P3CTRLR, &pxctrlr.d16, 2);	
		pxctrlr.b.pwm_h_pol_is_neg = ((HighPolarity == PWM_PolarityPositive) ? 0:1);
		AX_INTF_Write(P3CTRLR, &pxctrlr.d16, 2);
		break;
	}
} /* End of PWM_H_Polarity() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: PWM_L_Polarity
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void PWM_L_Polarity(PWM_Channels Channel, PWM_Polarity HighPolarity)
{
	switch (Channel)
	{
	case PWM_Channel_1:
		AX_INTF_Read(P1CTRLR, &pxctrlr.d16, 2);	
		pxctrlr.b.pwm_l_pol_is_neg = ((HighPolarity == PWM_PolarityPositive) ? 0:1);
		AX_INTF_Write(P1CTRLR, &pxctrlr.d16, 2);
		break;

	case PWM_Channel_2:		
		AX_INTF_Read(P2CTRLR, &pxctrlr.d16, 2);	
		pxctrlr.b.pwm_l_pol_is_neg = ((HighPolarity == PWM_PolarityPositive) ? 0:1);
		AX_INTF_Write(P2CTRLR, &pxctrlr.d16, 2);
		break;
		
	case PWM_Channel_3:
		AX_INTF_Read(P3CTRLR, &pxctrlr.d16, 2);	
		pxctrlr.b.pwm_l_pol_is_neg = ((HighPolarity == PWM_PolarityPositive) ? 0:1);
		AX_INTF_Write(P3CTRLR, &pxctrlr.d16, 2);
		break;
	}
} /* End of PWM_L_Polarity() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: Check_PWM_OutputEnabled
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
u8 Check_PWM_OutputEnabled(void)
{
	AX_INTF_Read(P1CTRLR, &pxctrlr.d16, 2);	
	if (pxctrlr.b.pwm_h_output_enable || pxctrlr.b.pwm_l_output_enable)
	{
		return 1;
	}
	
	AX_INTF_Read(P2CTRLR, &pxctrlr.d16, 2);	
	if (pxctrlr.b.pwm_h_output_enable || pxctrlr.b.pwm_l_output_enable)
	{
		return 1;
	}
	
	AX_INTF_Read(P3CTRLR, &pxctrlr.d16, 2);	
	if (pxctrlr.b.pwm_h_output_enable || pxctrlr.b.pwm_l_output_enable)
	{
		return 1;
	}
	return 0;
} /* End of Check_PWM_OutputEnabled() */

#endif /* AX58100_PWM_MODULE_ENABLED */

/* End of ax58100_pwm.c */
