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

#ifdef AX58100_SPIM_MODULE_ENABLED
#include "ax58100_spim.h"

/* NAMING CONSTANT DECLARATIONS */

/* TYPE DECLARATIONS */

/* GLOBAL VARIABLES DECLARATIONS */

/* LOCAL VARIABLES DECLARATIONS */
static SPICFGR_OBJECT spicfgr;
static SPIBRR_OBJECT  spibrr;
static SPILTR_OBJECT	spiltr;
static SPIPRLR_OBJECT spiprlr;
static SPINTSR_OBJECT spintsr;
static SPIMCR_OBJECT  spimcr;
static INTSR_OBJECT   intsr;
static u8 SPIM_ChannelAccessToBitMap[] = {0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff};
static u16 SPIM_ChannelSsMask[]        = {0xfff0, 0xff0f, 0xf0ff, 0x0fff};

/* LOCAL SUBPROGRAM DECLARATIONS */

/* LOCAL SUBPROGRAM BODIES */


/* EXPORTED SUBPROGRAM BODIES */

/*
 * ----------------------------------------------------------------------------
 * Function Name: SPIM_Init
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
AX_STATUS SPIM_Init(SPIM_OBJECT *pSpimObj)
{
	SPIM_CFG_OBJECT *pCfg = &pSpimObj->Cfg;
	
	if (pSpimObj == 0)
	{
		return AX_STATUS_ERR;
	}
	
	SPIM_DeInit(pSpimObj);
	
	/* Initiate object */
	memset(pSpimObj, 0, sizeof(SPIM_OBJECT));
	pCfg->ClkMode = SCLK_MODE_3;
	pCfg->LsbXferFirst = 0;	
	pCfg->LateSampleEnable = 0;
	pCfg->Baudrate = 50000000;//50MHz
	pCfg->FirstClkDelay = 0;
	pCfg->InterSlaveSelectDelay = 0;
	pCfg->ReadyTrgPulseTimeout = 1000;	
	pCfg->LatchPulseGap = 10;	
	pCfg->LatchPulseWidth = 10;	
	
	/* Polarity */
	pCfg->TrgPulsePolarity = SPIM_PolarityActiveLow;
	pCfg->ReadyLatchPulsePolarity = SPIM_PolarityActiveLow;
	pCfg->InterruptPolarity = SPIM_PolarityActiveLow;

	/* Operation mode */
	pCfg->InterruptModeEnable = 0;
	pCfg->RxBufHandshakeEnable = 1;
	pCfg->TrgPulseEnable = 0;
	pCfg->ReadyOrLatchPulseEnable = 0;
	pCfg->TransferTimeout = 100000;
	pCfg->AutoKeepSlaveSelectEnable = 1;
	pCfg->ContinueXferEnable = 0;
	pCfg->ReadyCombinedWithMiso = 0;
	pCfg->ExtDecoderEnable = 0;
	
	/* Operation timeout */
	
	/* Initiate hardware in idle state */
	SPIM_Config(pSpimObj);
	
	pSpimObj->State = SPIM_STATE_INITED;
	
	return AX_STATUS_OK;
} /* End of SPIM_Init() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: SPIM_DeInit
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void SPIM_DeInit(SPIM_OBJECT *pSpimObj)
{
	/* Stop operation */
	SPIM_ContinueStop(pSpimObj);
	
	pSpimObj->State = SPIM_STATE_DE_INITED;
}/* End of SPIM_DeInit() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: SPIM_Config
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
AX_STATUS SPIM_Config(SPIM_OBJECT *pSpimObj)
{
	u16 tmp16;
	SPIM_CFG_OBJECT *pCfg = &pSpimObj->Cfg;
	
	/* Check input parameters */
	if (pSpimObj->State == SPIM_STATE_BUSY || pSpimObj->State == SPIM_STATE_DE_INITED)
	{
		return AX_STATUS_ERR;
	}

	/* Set baudrate */
	if (pCfg->Baudrate < SPIM_MIN_BAUDRATE)
	{
		pCfg->Baudrate = SPIM_MIN_BAUDRATE;
	}
	else if (pCfg->Baudrate > SPIM_MAX_BAUDRATE)
	{
		pCfg->Baudrate = SPIM_MAX_BAUDRATE;		
	}
	spibrr.b.clk_divider = SPIM_CLK_SRC_FRQ/pCfg->Baudrate;//Convert baudrate to divider value
	spibrr.b.clk_enable = 0;
	
	/* Set timing */
	spibrr.b.first_clk_delay_x1K = 0;
	spibrr.b.inter_ss_delay_x1K = 0;
	spibrr.b.latch_pulse_gap_x1K = 0;
	spibrr.b.latch_pulse_width_x1K = 0;
	AX_INTF_Write(SPIBRR, &spibrr.d16, 2);//Disable SCLK
	spibrr.b.clk_enable = 1;	
	AX_INTF_Write(SPIBRR, &spibrr.d16, 2);//Enable SCLK and apply new baudrate
	
	tmp16 = pCfg->FirstClkDelay;
	AX_INTF_Write(SPIDBSR, &tmp16, 2);

	tmp16 = pCfg->InterSlaveSelectDelay;
	AX_INTF_Write(SPIDTR, &tmp16, 2);

	tmp16 = pCfg->ReadyTrgPulseTimeout;
	AX_INTF_Write(SPIRPTR, &tmp16, 2);
	
	spiltr.b.latch_pulse_gap = (u8)pCfg->LatchPulseGap;
	spiltr.b.latch_pulse_width = (u8)pCfg->LatchPulseWidth;
	AX_INTF_Write(SPILTR, &spiltr.d16, 2);
	
	/* Set clock mode */
	switch (pCfg->ClkMode)
	{
	case SCLK_MODE_0:
		spicfgr.b.clk_at_xfer_begin =  0;
		spicfgr.b.clk_is_act_low = 0;		
		break;
	
	case SCLK_MODE_1:
		spicfgr.b.clk_at_xfer_begin =  0;
		spicfgr.b.clk_is_act_low = 1;				
		break;

	case SCLK_MODE_2:
		spicfgr.b.clk_at_xfer_begin =  1;
		spicfgr.b.clk_is_act_low = 0;						
		break;
		
	default:
	case SCLK_MODE_3:
		spicfgr.b.clk_at_xfer_begin =  1;
		spicfgr.b.clk_is_act_low = 1;						
		break;		
	}
	
	/* Set signal polarity */	
	spicfgr.b.ready_latch_is_act_high = (pCfg->ReadyLatchPulsePolarity == SPIM_PolarityActiveHigh) ? 1:0;
	spicfgr.b.trg_pulse_is_act_high = (pCfg->TrgPulsePolarity == SPIM_PolarityActiveHigh) ? 1:0;
	spicfgr.b.intr_is_act_high = (pCfg->InterruptPolarity == SPIM_PolarityActiveHigh) ? 1:0;
	spicfgr.b.ready_combined_with_miso = pCfg->ReadyCombinedWithMiso ? 1:0;
	spicfgr.b.intr_is_edge_trg = 0;
	spicfgr.b.intr_enable = 0;

	/* Set operation mode */
	spicfgr.b.lsb_is_xfer_first = pCfg->LsbXferFirst ? 1:0;
	spicfgr.b.late_sample_enable = pCfg->LateSampleEnable ? 1:0;
	spicfgr.b.dac_mode_enable = pCfg->DacModeEnable ? 1:0;
	spicfgr.b.ext_decoder_enable = pCfg->ExtDecoderEnable ? 1:0;
	
	AX_INTF_Write(SPICFGR, &spicfgr.d16, 2);

	/* Open interrupt */
	if (pCfg->InterruptModeEnable)
	{
		MISC_InterruptsEnable(SPIM_COMPLETE_INTR_ENABLE | SPIM_ERR_INTR_ENABLE);
	}
	else
	{
		MISC_InterruptsDisable(SPIM_COMPLETE_INTR_ENABLE | SPIM_ERR_INTR_ENABLE);		
	}
	
	/* Clear Slave Allocation */
	pSpimObj->SlaveNum = 0;
	pSpimObj->ChannelNumInUse = 0;
	
	pSpimObj->State = SPIM_STATE_READY;
	return AX_STATUS_OK;
} /* End of SPIM_Config() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: SPIM_SwitchSlave
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
AX_STATUS SPIM_SwitchSlave(SPIM_OBJECT *pSpimObj, SPIM_SLAVE_ID SlaveId)
{
	if ((SlaveId + 1) > SPIM_MAX_SLAVE_NUM)
	{
		return AX_STATUS_ERR;
	}
	
	pSpimObj->CurrSlaveId = SlaveId;
	
	return AX_STATUS_OK;

} /* End of SPIM_SwitchSlave() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: SPIM_SetRxStartByte
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void SPIM_SetRxStartByte(SPIM_OBJECT *pSpimObj, u8 StartByte)
{
	SPIM_SLAVE_INFO *pSlave = &pSpimObj->SlaveInfo[pSpimObj->CurrSlaveId];
	
	pSlave->RxStartByte = StartByte;

}/* End of SPIM_SetRxStartByte() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: SPIM_WriteTxBuf
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
s32 SPIM_WriteTxBuf(SPIM_OBJECT *pSpimObj, u8 *pData, u8 Len)
{
	u32 i;
	u16 tmp16, regAddr, regValue;
	u8 tmp8, *pTmp8, txByteCnt, rxStartByte;
	SPIM_CFG_OBJECT *pCfg = &pSpimObj->Cfg;
	SPIM_SLAVE_INFO *pSlave = &pSpimObj->SlaveInfo[pSpimObj->CurrSlaveId];
	
	/* Check available channels */
	if (pSpimObj->ChannelNumInUse >= SPIM_MAX_CHANNEL_NUM)
	{
		return 0;
	}
	
	/* Get slave information */
	tmp8 = (SPIM_MAX_CHANNEL_NUM - pSpimObj->ChannelNumInUse) * SPIM_MAX_BUF_SIZE_PER_CH;
	if (Len > tmp8)
	{
		Len = tmp8;
	}
	pSlave->InUse = 1;
	pSlave->StartChannel = pSpimObj->ChannelNumInUse;
	pSlave->UsedChannels = (Len + (SPIM_MAX_BUF_SIZE_PER_CH - 1))/SPIM_MAX_BUF_SIZE_PER_CH;
	pSlave->TxBufAddr = SPIC0DR + (pSlave->StartChannel * SPIM_MAX_BUF_SIZE_PER_CH);//Calculate Tx data buffer offset
	pSlave->TxLen = Len;
	if ((pSlave->RxStartByte + 1) > pSlave->TxLen)
	{
		pSlave->RxStartByte = 0;
	}
	pSlave->RxBufAddr = pSlave->TxBufAddr + (pSlave->RxStartByte & 0xf8);//Calculate Rx data buffer offset
	
	/* Added 0x200 offset for data reading in SPI master buffer */
	if (pSlave->TxBufAddr >= 0x3000)
	{
		pSlave->RxBufAddr += 0x200;
	}
	
	pSlave->RxLen = pSlave->TxLen - pSlave->RxStartByte;
	
	pSpimObj->ChannelNumInUse += pSlave->UsedChannels;
	pSpimObj->SlaveNum++;
	
	/* Allocate channels */
	for (i=pSlave->StartChannel; i<pSpimObj->ChannelNumInUse; i++)
	{
		pSpimObj->SlaveIdOfChannel[i] = pSpimObj->CurrSlaveId;
		
		/* Read register */
		if (i==pSlave->StartChannel || i==4)
		{
			regAddr = (i < 4) ? SPI03SSR:SPI47SSR;
			AX_INTF_Read(regAddr, &regValue, 2);
		}
		tmp8 = ((i%4) * 4);
		regValue &= SPIM_ChannelSsMask[(i%4)];
		
		/* Set Slave ID */
		tmp16 = (pSpimObj->CurrSlaveId & 0x0007);		
		
		/* Set keep assert at same Slave ID */
		if (pCfg->AutoKeepSlaveSelectEnable)
		{
			if ((i+1) != pSpimObj->ChannelNumInUse)
			{
				tmp16 |= 0x0008;
			}
		}
		
		regValue |= (tmp16 << tmp8);

		/* Write register */		
		if (i==3 || ((i+1)>=pSpimObj->ChannelNumInUse))
		{
			AX_INTF_Write(regAddr, &regValue, 2);
		}
	}	

	/* Write Tx buffer */
	AX_INTF_Write(pSlave->TxBufAddr, pData, Len);

	/* Set Tx byte count/Rx start byte */
	txByteCnt = pSlave->TxLen;
	rxStartByte = pSlave->RxStartByte;
	pTmp8 = (u8*)&regValue;	
	for (i=pSlave->StartChannel; i<pSpimObj->ChannelNumInUse; i++)
	{
		/* Read register */
		if (i==pSlave->StartChannel || (i&0x01)==0)
		{
			regAddr = SPI01BCR + (i&0xfffe);
			AX_INTF_Read(regAddr, &regValue, 2);
		}
		
		/* Set Tx byte count */
		tmp8 = (txByteCnt > SPIM_MAX_BUF_SIZE_PER_CH) ? SPIM_MAX_BUF_SIZE_PER_CH:txByteCnt;
		pTmp8[i&0x01] = tmp8 - 1;
		txByteCnt -= tmp8;
		
		/* Set Rx start byte */
		if (rxStartByte < SPIM_MAX_BUF_SIZE_PER_CH)
		{
			pTmp8[i&0x01] |= (rxStartByte << 4);
			rxStartByte = 0;
		}
		else
		{
			pTmp8[i&0x01] |= (0x07 << 4);			
			rxStartByte -= SPIM_MAX_BUF_SIZE_PER_CH;					
		}

		/* Write register */		
		if ((i&0x01)!=0 || ((i+1)>=pSpimObj->ChannelNumInUse))
		{
			AX_INTF_Write(regAddr, &regValue, 2);
		}
	}
	
	/* Waiting for trigger pulse */
	AX_INTF_Read(SPIPRLR, &spiprlr.d16, 2);	
	if (pCfg->TrgPulseEnable)
	{
		spiprlr.d16 |= (u16)(0x01 << pSlave->StartChannel);
	}

	/* Waiting for ready pulse */
	if (pCfg->ReadyOrLatchPulseEnable)
	{
		if (pCfg->DacModeEnable)
		{
			spiprlr.d16 |= (u16)(0x0100 << (pSpimObj->ChannelNumInUse-1));
		}
		else
		{
			spiprlr.d16 |= (u16)(0x0100 << pSlave->StartChannel);		
		}
	}
	AX_INTF_Write(SPIPRLR, &spiprlr.d16, 2);	
	
	return Len;
} /* End of SPIM_WriteTxBuf() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: SPIM_ReadRxBuf
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
s32 SPIM_ReadRxBuf(SPIM_OBJECT *pSpimObj, u8 *pBuf, u8 Size)
{
	SPIM_SLAVE_INFO *pSlave = &pSpimObj->SlaveInfo[pSpimObj->CurrSlaveId];
	u8 tmp8, len;
	u16 tmp16;
	
	/* Check parameters */
	if (pBuf == 0 || Size == 0)
	{
		return 0;
	}
		
	/* Read Rx buffer */
	if (pSlave->TxLen > pSlave->RxStartByte)
	{
		pSlave->RxLen = pSlave->TxLen - pSlave->RxStartByte;
	}
	else
	{
		pSlave->RxLen = 0;		
	}

	if (Size > pSlave->RxLen)
	{
		Size = pSlave->RxLen;
	}
	len = Size;

	if (len)
	{
		tmp16 = pSlave->RxBufAddr;		
		tmp8 = SPIM_MAX_BUF_SIZE_PER_CH - (pSlave->RxStartByte % SPIM_MAX_BUF_SIZE_PER_CH);
		if (tmp8 > len)
		{
			tmp8 = len;
		}
		if (tmp8)
		{
			AX_INTF_Read(tmp16, pBuf, tmp8);
			pBuf += tmp8;
			len -= tmp8;
			tmp16	+= SPIM_MAX_BUF_SIZE_PER_CH;		
		}
		if (len)
		{
			AX_INTF_Read(tmp16, pBuf, len);		
		}
	}
	return Size;	
} /* End of SPIM_ReadRxBuf() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: SPIM_Start
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
AX_STATUS SPIM_Start(SPIM_OBJECT *pSpimObj)
{
	u32 i;
	SPIM_CFG_OBJECT *pCfg = &pSpimObj->Cfg;
	
	if (pSpimObj->State == SPIM_STATE_BUSY)
	{
		return AX_STATUS_ERR;
	}
	
	/* Clear SPI master interrupt flags */
	if (pSpimObj->Cfg.InterruptModeEnable)
	{
		intsr.d16 = 0;			
		intsr.b.spim_compl_intr_stu = 1;
		intsr.b.spim_err_intr_stu = 1;		
		AX_INTF_Write(INTSR, &intsr.d16, 2);		
	}
	
	/* Clear rx buffer */
	spimcr.d16 = 0x00ff;
#if 0
	spimcr.b.access_channels = (pSpim->ChannelNumInUse == 0) ? 0:(pSpim->ChannelNumInUse - 1);	
	spimcr.b.continue_mode_enable = (pCfg->ContinueXferEnable != 0) ? 1:0;	
	spimcr.b.rx_buf_handshake_enable = pCfg->RxBufHandshakeEnable ? 1:0;
#endif	
	AX_INTF_Write(SPIMCR, &spimcr.d16, 2);
	
	for (i=0; i<pSpimObj->Cfg.TransferTimeout; i++)
	{
		AX_INTF_Read(SPIMCR, &spimcr.d16, 2);
		if ((spimcr.d16 & 0x00ff) == 0)
		{
			break;
		}
	}
	if (i >= pSpimObj->Cfg.TransferTimeout)
	{
		pSpimObj->State = SPIM_STATE_ERR;
		return AX_STATUS_ERR;
	}	

	/* Start transfer */
	AX_INTF_Read(SPIMCR, &spimcr.d16, 2);
	spimcr.d16 &= 0xff00;
	spimcr.b.go = 1;
	spimcr.b.access_channels = (pSpimObj->ChannelNumInUse == 0) ? 0:(pSpimObj->ChannelNumInUse - 1);		
	spimcr.b.continue_mode_enable = (pCfg->ContinueXferEnable != 0) ? 1:0;
	spimcr.b.rx_buf_handshake_enable = (pCfg->RxBufHandshakeEnable != 0) ? 1:0;
	
	/* Clear SPI master sub-interrupt flags */
	spimcr.b.clr_complete_flag = 1;
	spimcr.b.clr_interrupt_flag = 1;

	AX_INTF_Write(SPIMCR, &spimcr.d16, 2);
	
	pSpimObj->State = SPIM_STATE_BUSY;
	
	return AX_STATUS_OK;	
	
}/* End of SPIM_Start() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: SPIM_OneShotStart
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
AX_STATUS SPIM_OneShotStart(SPIM_OBJECT *pSpimObj)
{
	pSpimObj->Cfg.ContinueXferEnable = 0;
	return SPIM_Start(pSpimObj);
}/* End of SPIM_OneShotStart() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: SPIM_ContinueStart
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
AX_STATUS SPIM_ContinueStart(SPIM_OBJECT *pSpimObj)
{
	pSpimObj->Cfg.ContinueXferEnable = 1;
	return SPIM_Start(pSpimObj);
}/* End of SPIM_ContinueStart() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: SPIM_ContinueStop
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
AX_STATUS SPIM_ContinueStop(SPIM_OBJECT *pSpimObj)
{
	u32 i;
	SPIM_CFG_OBJECT *pCfg = &pSpimObj->Cfg;
	
  if (pCfg->ContinueXferEnable)
	{
		/* Stop continue transfer mode */
		AX_INTF_Read(SPIMCR, &spimcr.d16, 2);
		spimcr.b.continue_mode_enable = 0;
		AX_INTF_Write(SPIMCR, &spimcr.d16, 2);
		
		/* Wait hardware stop */
		for (i=0; i<pSpimObj->Cfg.TransferTimeout; i++)
		{
			AX_INTF_Read(SPINTSR, &spintsr.d16, 2);
			if (spintsr.b.busy == 0)
			{
				break;
			}
		}
		if (i >= pSpimObj->Cfg.TransferTimeout)
		{
			return AX_STATUS_TIMEOUT;
		}
	}
	
	pSpimObj->State = SPIM_STATE_READY;
	return AX_STATUS_OK;	
	
}/* End of SPIM_Stop() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: SPIM_ReadyLatchPulseCtrl
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void SPIM_ReadyLatchPulseCtrl(SPIM_OBJECT *pSpimObj, u8 Enable)
{
	pSpimObj->Cfg.ReadyOrLatchPulseEnable = Enable;

}/* End of SPIM_ReadyLatchPulseCtrl() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: SPIM_CheckComplete
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
AX_STATUS SPIM_CheckComplete(SPIM_OBJECT *pSpimObj, u32 Timeout)
{
	u32 i;
	u8 *ptmp8, tmp8;
	u16 tmp16, time16;
	SPIM_CFG_OBJECT *pCfg = &pSpimObj->Cfg;
	
	ptmp8 = (u8*)&tmp16;
	pSpimObj->State = SPIM_STATE_ERR;
	
	/* Check transfer complete */
	if (pCfg->ContinueXferEnable == 0)
	{
		for (i=0; i<Timeout; i++)
		{
			AX_INTF_Read(SPINTSR, &spintsr.d16, 2);
			if (spintsr.b.busy == 0)
			{
				break;
			}
		}
		if (i >= Timeout)
		{
			return AX_STATUS_TIMEOUT;
		}		
	}
  else
	{
		/* delay 1ms */
		time16 = AX_INTF_GetTime();
		while (AX_INTF_CheckTimeout(time16, 1) == 0);
		
		AX_INTF_Read(SPIMCR, &spimcr.d16, 2);
	}
	
	/* Check slave select error */
	AX_INTF_Read(SPINTSR, &spintsr.d16, 2);		
	if (spintsr.b.slave_select_err)
	{
		return AX_STATUS_ERR;					
	}
		
	/* Check all channels complete */
	tmp8 = SPIM_ChannelAccessToBitMap[spimcr.b.access_channels];
	for (i=0; i<Timeout; i++)
	{	
		AX_INTF_Read(SPIDSR, &tmp16, 2);
		if ((ptmp8[0] & tmp8) == tmp8)
		{
			break;
		}
	}
	if (i >= Timeout)
	{
		return AX_STATUS_TIMEOUT;
	}	
		
	/* Check RX buffer overrun */
	if (pCfg->ContinueXferEnable == 0)
	{
		if (ptmp8[1] & tmp8)
		{
			return AX_STATUS_RX_BUF_OVERRUN;		
		}
	}
	
	/* Check trigger pulse timeout */
	AX_INTF_Read(SPITSR, &tmp16, 2);	
	if (pCfg->TrgPulseEnable)
	{
		if (ptmp8[0] & tmp8)
		{
			return AX_STATUS_TRG_PULSE_TIMEOUT;
		}
	}
	
	/* Check ready pulse timeout */	
	if (pCfg->ReadyOrLatchPulseEnable)
	{	
		if (ptmp8[1] & tmp8)
		{
			return AX_STATUS_RDY_PULSE_TIMEOUT;		
		}
	}

	/* Check trigger pulse overrun */
	if (pCfg->TrgPulseEnable)
	{		
		AX_INTF_Read(SPIPOSR, &tmp16, 2);
		if (ptmp8[0] & tmp8)
		{
			return AX_STATUS_TRG_PULSE_OVERRUN;
		}		
	}
	
	/* Check interrupt flags */
	if (pCfg->InterruptModeEnable)
	{
		if (spintsr.b.all_xfer_completed == 0)
		{
			return AX_STATUS_COMPLETE_TIMEOUT;					
		}
	
		if (pCfg->ContinueXferEnable == 0)
		{		
			if (spintsr.b.rx_buf_is_overrun)
			{
				return AX_STATUS_RX_BUF_OVERRUN;					
			}
		}

		if (spintsr.b.wait_trg_pulse_timeout)
		{
			return AX_STATUS_TRG_PULSE_TIMEOUT;			
		}	
		
		if (spintsr.b.wait_rdy_timeout)
		{
			return AX_STATUS_RDY_PULSE_TIMEOUT;					
		}
		
		if (spintsr.b.trg_pulse_is_overrun)
		{
			return AX_STATUS_TRG_PULSE_OVERRUN;			
		}
/*
		if (spintsr.b.interrupt_is_asserted == 0)
		{
			return AX_STATUS_TRG_PULSE_OVERRUN;				
		}	
*/		
	}	
	
	pSpimObj->State = SPIM_STATE_READY;	
	return AX_STATUS_OK;
} /* End of SPIM_CheckComplete() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: SPIM_ClearInterrupt
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void SPIM_ClearInterrupt(void)
{
	AX_INTF_Read(SPIMCR, &spimcr.d16, 2);	
	spimcr.b.ch0_rx_buf_clr = 0;
	spimcr.b.ch1_rx_buf_clr = 0;
	spimcr.b.ch2_rx_buf_clr = 0;
	spimcr.b.ch3_rx_buf_clr = 0;
	spimcr.b.ch4_rx_buf_clr = 0;
	spimcr.b.ch5_rx_buf_clr = 0;
	spimcr.b.ch6_rx_buf_clr = 0;
	spimcr.b.ch7_rx_buf_clr = 0;
	spimcr.b.go = 0;
//	spimcr.b.access_channels = 0;	
//	spimcr.b.continue_mode_enable = 0;
//	spimcr.b.rx_buf_handshake_enable = 0;
	spimcr.b.clr_complete_flag = 1;
	spimcr.b.clr_interrupt_flag = 1;
	AX_INTF_Write(SPIMCR, &spimcr.d16, 2);
	
} /* End of SPIM_ClearInterrupt() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: SPIM_ClearSlaveAllocation
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
AX_STATUS SPIM_ClearSlaveAllocation(SPIM_OBJECT *pSpimObj)
{
	u8 i;
	
	if (pSpimObj->State == SPIM_STATE_BUSY)
	{
		return AX_STATUS_ERR;
	}
		
	pSpimObj->ChannelNumInUse = 0;
	pSpimObj->SlaveNum = 0;
	
	for (i=0; i<SPIM_MAX_CHANNEL_NUM; i++)
	{
		pSpimObj->SlaveInfo[i].InUse = 0;
		pSpimObj->SlaveInfo[i].TxLen = 0;
		pSpimObj->SlaveInfo[i].RxLen = 0;
	}
	
	spiprlr.d16 = 0;
	AX_INTF_Write(SPIPRLR, &spiprlr.d16, 2);		
	return AX_STATUS_OK;
} /* End of SPIM_ClearSlaveAllocation() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: SPIM_TransmitReceive
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
s32 SPIM_TransmitReceive(SPIM_OBJECT *pSpimObj, u8 *pData, u8 *pBuf, u32 Len)
{
	int ret = 0;
	SPIM_SLAVE_INFO *pSlave = &pSpimObj->SlaveInfo[pSpimObj->CurrSlaveId];
	
	if (pSpimObj->State == SPIM_STATE_BUSY || Len == 0)
	{
		return AX_STATUS_ERR;
	}
	
	SPIM_ClearSlaveAllocation(pSpimObj);
	SPIM_WriteTxBuf(pSpimObj, pData, Len);
	SPIM_OneShotStart(pSpimObj);
	if (SPIM_CheckComplete(pSpimObj, pSpimObj->Cfg.TransferTimeout) != SPIM_STATUS_OK)
	{
		return AX_STATUS_ERR;
	}

	if (pBuf)
	{
		ret = SPIM_ReadRxBuf(pSpimObj, pBuf, pSlave->RxLen);
	}
	return ret;
} /* End of SPIM_TransmitReceive() */

#endif /* AX58100_SPIM_MODULE_ENABLED */

/* End of ax58100_spim.c */
