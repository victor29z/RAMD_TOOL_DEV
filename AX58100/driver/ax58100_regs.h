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
#ifndef __AX58100_REGS_H__
#define __AX58100_REGS_H__

/* INCLUDE FILE DECLARATIONS */
#include "ax_types.h"

/* NAMING CONSTANT DECLARATIONS */
#define AX58100_ALWAYS_USE_FUN_PDI

#define AX58100_FUN_WR_REGS_ADDR 0x0000
#define AX58100_FUN_RD_REGS_ADDR 0x0000
#define AX58100_ESC_WR_REGS_ADDR 0x3000
#define AX58100_ESC_RD_REGS_ADDR 0x3200

#ifdef AX58100_ALWAYS_USE_FUN_PDI
	#define AX58100_REGS_WR_BASE     AX58100_FUN_WR_REGS_ADDR
	#define AX58100_REGS_RD_BASE     AX58100_FUN_RD_REGS_ADDR
#else
	#define AX58100_REGS_WR_BASE     AX58100_ESC_WR_REGS_ADDR
	#define AX58100_REGS_RD_BASE     AX58100_ESC_RD_REGS_ADDR
#endif

/* ====================== Function Register Address Definition ====================== */
	/* Motor Control Registers */
#define MCTLR       (AX58100_REGS_WR_BASE+0x00)      /* 0x00: Motor Control Register */
#define PXCFGR      (AX58100_REGS_WR_BASE+0x02)      /* 0x02: PWM Pulse X Configuration Register */
#define PTAPPR      (AX58100_REGS_WR_BASE+0x04)      /* 0x04: PWM Trigger A Pulse Position Register */
#define PTBPPR      (AX58100_REGS_WR_BASE+0x06)      /* 0x06: PWM Trigger B Pulse Position Register */
#define PPCR        (AX58100_REGS_WR_BASE+0x08)      /* 0x08: PWM Period Cycle Register */
#define PBBMR       (AX58100_REGS_WR_BASE+0x0A)      /* 0x0A: PWM Pulse Brake Before Make Register */
#define P1CTRLR     (AX58100_REGS_WR_BASE+0x0C)      /* 0x0C: PWM1 Control Register */
#define P1SHR       (AX58100_REGS_WR_BASE+0x0E)      /* 0x0E: PWM1 Counter Shift Register */
#define P1HPWR      (AX58100_REGS_WR_BASE+0x10)      /* 0x10: PWM1 High Pulse Width Register */
#define P2CTRLR     (AX58100_REGS_WR_BASE+0x12)      /* 0x12: PWM2 Control Register */
#define P2SHR       (AX58100_REGS_WR_BASE+0x14)      /* 0x14: PWM2 Counter Shift Register */
#define P2HPWR      (AX58100_REGS_WR_BASE+0x16)      /* 0x16: PWM2 High Pulse Width Register */
#define P3CTRLR     (AX58100_REGS_WR_BASE+0x18)      /* 0x18: PWM3 Control Register */
#define P3SHR       (AX58100_REGS_WR_BASE+0x1A)      /* 0x1A: PWM3 Counter Shift Register */
#define P3HPWR      (AX58100_REGS_WR_BASE+0x1C)      /* 0x1C: PWM3 High Pulse Width Register */
                                                     /* 0x1E: Reserved */
#define SGTLR       (AX58100_REGS_WR_BASE+0x20)      /* 0x20: Step Gap Time Low Register */
#define SGTHR       (AX58100_REGS_WR_BASE+0x22)      /* 0x22: Step Gap Time High Register */
#define SHPWR       (AX58100_REGS_WR_BASE+0x24)      /* 0x24: Step High Pulse Width Register */
#define TDLYR       (AX58100_REGS_WR_BASE+0x26)      /* 0x26: Transform Delay Register */
#define STNLR       (AX58100_REGS_WR_BASE+0x28)      /* 0x28: Step Target Number Low Word Register */
#define STNHR       (AX58100_REGS_WR_BASE+0x2A)      /* 0x2A: Step Target Number High Word Register */
#define SCFGR       (AX58100_REGS_WR_BASE+0x2C)      /* 0x2C: Step Configuration Register */
#define SCTRLR      (AX58100_REGS_WR_BASE+0x2E)      /* 0x2E: Step Control Register */
#define SCNTLR      (AX58100_REGS_RD_BASE+0x30)      /* 0x30: Step Counter Content Low Register */   
#define SCNTHR      (AX58100_REGS_RD_BASE+0x32)      /* 0x32: Step Counter Content High Register */	
                                                     /* 0x34: Reserved */
	/* Encoder Registers */
#define ECNTVL      (AX58100_REGS_WR_BASE+0x40)      /* 0x40: Encoder Counter Value Low */
#define ECNTVH      (AX58100_REGS_WR_BASE+0x42)      /* 0x42: Encoder Counter Value High */
#define ECNSTL      (AX58100_REGS_WR_BASE+0x44)      /* 0x44: Encoder Constant Low */
#define ECNSTH      (AX58100_REGS_WR_BASE+0x46)      /* 0x46: Encoder Constant High */
#define ELATL       (AX58100_REGS_RD_BASE+0x48)      /* 0x48: Encoder Latched Low */
#define ELATH       (AX58100_REGS_RD_BASE+0x4A)      /* 0x4A: Encoder Latched High */
#define EMOD        (AX58100_REGS_WR_BASE+0x4C)      /* 0x4C: Encoder Mode Configuration */
#define ECLR        (AX58100_REGS_WR_BASE+0x4E)      /* 0x4E: Encoder Clear */
#define HALLST      (AX58100_REGS_RD_BASE+0x50)      /* 0x50: Hall Sensing State */

	/* I/O Watchdog Registers */
#define WTLR        (AX58100_REGS_WR_BASE+0x60)      /* 0x60: Watchdog Timer Low Register */	
#define WTHR        (AX58100_REGS_WR_BASE+0x62)      /* 0x62: Watchdog Timer High Register */	
#define WCFGR       (AX58100_REGS_WR_BASE+0x64)      /* 0x64: Watchdog Configure Register */	
#define WTPVCR      (AX58100_REGS_WR_BASE+0x66)      /* 0x66: Watchdog Timer Peak Value Clear Register */		
#define WMSPLR      (AX58100_REGS_WR_BASE+0x68)      /* 0x68: Watchdog Monitored Signals Polarity Low Register */		
#define WMSPHR      (AX58100_REGS_WR_BASE+0x6A)      /* 0x6A: Watchdog Monitored Signals Polarity High Register */
#define WMSMLR      (AX58100_REGS_WR_BASE+0x6C)      /* 0x6C: Watchdog Monitored Signals Mask Low Register */
#define WMSMHR      (AX58100_REGS_WR_BASE+0x6E)      /* 0x6E: Watchdog Monitored Signals Mask High Register */
#define WMSOMLR     (AX58100_REGS_WR_BASE+0x70)      /* 0x70: Watchdog Monitored Signals Output Mask Low Register */
#define WMSOMHR     (AX58100_REGS_WR_BASE+0x72)      /* 0x72: Watchdog Monitored Signals Output Mask High Register */
#define WMSOELR     (AX58100_REGS_WR_BASE+0x74)      /* 0x74: Watchdog Monitored Signals Output Enable Low Register */
#define WMSOEHR     (AX58100_REGS_WR_BASE+0x76)      /* 0x76: Watchdog Monitored Signals Output Enable High Register */	
#define WMSOPLR     (AX58100_REGS_WR_BASE+0x78)      /* 0x78: Watchdog Monitored Signals Output Polarity Low Register */	
#define WMSOPHR     (AX58100_REGS_WR_BASE+0x7A)      /* 0x7A: Watchdog Monitored Signals Output Polarity High Register */	
#define WTPVLR      (AX58100_REGS_WR_BASE+0x7C)      /* 0x7C: Watchdog Timer Peak Value Low Register */	
#define WTPVHR      (AX58100_REGS_WR_BASE+0x7E)      /* 0x7E: Watchdog Timer Peak Value High Register */		

	/* SPI Master Registers */
#define SPICFGR     (AX58100_REGS_WR_BASE+0x80)	     /* 0x80: SPI Configure Register */
#define SPIBRR      (AX58100_REGS_WR_BASE+0x82)      /* 0x82: SPI Baud Rate Register */
#define SPIDBSR     (AX58100_REGS_WR_BASE+0x84)      /* 0x84: SPI Delay Byte and SS Register */
#define SPIDTR      (AX58100_REGS_WR_BASE+0x86)      /* 0x86: SPI Delay Transfer Register */
#define SPIRPTR     (AX58100_REGS_WR_BASE+0x88)      /* 0x88: SPI Ready, Trigger Pulse Timeout Register */
#define SPILTR      (AX58100_REGS_WR_BASE+0x8A)      /* 0x8A: SPI Latch Gap Time, Pulse Width Register */
#define SPIPRLR     (AX58100_REGS_WR_BASE+0x8C)      /* 0x8C: Pulse/ RDY/ LDAC Function Register */
                                                     /* 0x8F~0x8E: Reserved */
#define SPI01BCR    (AX58100_REGS_WR_BASE+0x90)      /* 0x90: SPI 0/1 Byte Count Register */
#define SPI23BCR    (AX58100_REGS_WR_BASE+0x92)      /* 0x92: SPI 2/3 Byte Count Register */
#define SPI45BCR    (AX58100_REGS_WR_BASE+0x94)      /* 0x94: SPI 4/5 Byte Count Register */
#define SPI67BCR    (AX58100_REGS_WR_BASE+0x96)      /* 0x96: SPI 6/7 Byte Count Register */
#define SPI03SSR    (AX58100_REGS_WR_BASE+0x98)      /* 0x98: SPI 0/1/2/3 Slave Select Register */
#define SPI47SSR    (AX58100_REGS_WR_BASE+0x9A)      /* 0x9A: SPI 4/5/6/7 Slave Select Register */
																					           /* 0x9C~A7: Reserved */
#define	SPINTSR     (AX58100_REGS_RD_BASE+0xA8)      /* 0xA8: SPI Interrupt Status Register */
#define SPITSR      (AX58100_REGS_RD_BASE+0xAA)      /* 0xAA: SPI Timeout Status Register */
#define SPIPOSR     (AX58100_REGS_RD_BASE+0xAC)      /* 0xAC: SPI Pulse Overrun Status Register */
#define SPIDSR      (AX58100_REGS_RD_BASE+0xAE)      /* 0xAE: SPI Data Status Register */
#define SPIC0DR     (AX58100_REGS_WR_BASE+0xB0)      /* 0xB0: SPI Channel 0 Data Register */
#define SPIC1DR     (AX58100_REGS_WR_BASE+0xB8)      /* 0xB8: SPI Channel 1 Data Register */
#define SPIC2DR     (AX58100_REGS_WR_BASE+0xC0)      /* 0xC0: SPI Channel 2 Data Register */
#define SPIC3DR     (AX58100_REGS_WR_BASE+0xC8)      /* 0xC8: SPI Channel 3 Data Register */
#define SPIC4DR     (AX58100_REGS_WR_BASE+0xD0)      /* 0xD0: SPI Channel 4 Data Register */
#define SPIC5DR     (AX58100_REGS_WR_BASE+0xD8)      /* 0xD8: SPI Channel 5 Data Register */
#define SPIC6DR     (AX58100_REGS_WR_BASE+0xE0)      /* 0xE0: SPI Channel 6 Data Register */
#define SPIC7DR     (AX58100_REGS_WR_BASE+0xE8)      /* 0xE8: SPI Channel 7 Data Register */
#define SPIDSMR     (AX58100_REGS_RD_BASE+0xF0)      /* 0xF0: SPI Data Status Mirror Register */
#define SPIMCR      (AX58100_REGS_WR_BASE+0xF2)      /* 0xF2: SPI Master Control Register */

	/* Miscellaneous Registers */
#define INTCR       (AX58100_REGS_WR_BASE+0x100)     /* 0x100: Interrupt Configure Register */
#define INTSR       (AX58100_REGS_WR_BASE+0x102)     /* 0x102: Interrupt Status Register */
	/* Notice: Below registers are only be accessed at FUN side */
#define ESTOR       (0x104)  /* 0x104: ESC State Override Register */
#define HSTSR       (0x106)  /* 0x106: Host Interface Status Register */	
#define PHYPR       (0x108)  /* 0x108: PHY Parameter Register */	
#define MINFR       (0x10A)  /* 0x10A: Manuafacturing Information Register */	
#define ECTRLR      (0x110)  /* 0x110: Efuse Control Register */	
#define ERDR        (0x112)  /* 0x112: Efuse Read Data Register */	

/* ====================== Function Register Bit Definition ====================== */
/*---------------------------------------
     Motor Control Module
----------------------------------------*/
	/* Bit definition for MCTLR register */
#define MC_PWM_FUNC_ENABLE            BIT_0   /* MCTLR.0   PWM function enable */
#define MC_PWM_8X_ENABLE              BIT_1   /* MCTLR.1   PWM 8X Magnified enable */
#define MC_STEP_FUNC_ENABLE           BIT_4   /* MCTLR.4   Step function enable */	

	/* Bit definition for PXCFGR register */
#define MC_PWM_ABCSAC_WIDTH_MASK      0x00FF  /* PXCFGR.7:0   A/B/C/S/AB high pulse width */
#define MC_PWM_ABCSAC_POL_NEGATIVE    BIT_8   /* PXCFGR.8     A/B/C/S/AB pulse polarity */
#define MC_PWM_S_OUTPUT_ENABLE        BIT_9   /* PXCFGR.9     S pulse output enable */	
#define MC_PWM_C_OUTPUT_ENABLE        BIT_10  /* PXCFGR.10    C pulse output enable */	
#define MC_PWM_A_OUTPUT_ENABLE        BIT_11  /* PXCFGR.11    A pulse output enable */	
#define MC_PWM_B_OUTPUT_ENABLE        BIT_12  /* PXCFGR.12    B pulse output enable */	
#define MC_PWM_AB_OUTPUT_ENABLE       BIT_13  /* PXCFGR.13    AB pulse output enable */	
#define MC_PWM_ALIGNMENT_MASK         0xC000  /* PXCFGR.15:14 PWM High pulse alignment */	
  #define MC_PWM_LEFT_ALIGNMENT       0x4000  /* PWM left alignment */
  #define MC_PWM_RIGHT_ALIGNMENT      0x8000  /* PWM right alignment */
  #define MC_PWM_CENTER_ALIGNMENT     0xC000  /* PWM center alignment */
	
	/* Bit definition for P1CTRLR/P2CTRLR/P3CTRLR register */
#define MC_PWM_H_POLARITY_NEGATIVE    BIT_0   /* PxCTRLR.0    PWMx H polarity setting */
#define MC_PWM_L_POLARITY_NEGATIVE    BIT_1   /* PxCTRLR.1    PWMx L polarity setting */
#define MC_PWM_H_OUTPUT_ENABLE        BIT_2   /* PxCTRLR.2    PWMx H output enable */
#define MC_PWM_L_OUTPUT_ENABLE        BIT_3   /* PxCTRLR.3    PWMx L output enable */			
#define MC_PWM_CHANNEL_ENABLE         BIT_4   /* PxCTRLR.4    PWMx channel enable */		
		
	/* Bit definition for STNHR register */
#define MC_TARGET_NUM_30_16BIT_MASK   0x7FFF  /* STNHR.14:0   Step target number[30:16] */
#define MC_DIR_IS_BACKWARD            BIT_15  /* STNHR.15     Direction control */
		
	/* Bit definition for SCFGR register */
#define MC_STEP_PULSE_NEGATIVE        BIT_0   /* SCFGR.0   Step pulse polarity */
#define MC_DIR_SIGNAL_NEGATIVE        BIT_1   /* SCFGR.1   Direction signal polarity */
		
	/* Bit definition for SCTRLR register */
#define MC_DIR_SIGNAL_OUTPUT_ENABLE   BIT_0   /* SCTRLR.0   DIR output enable */
#define MC_CLR_STEP_COUNT_VALUE       BIT_1   /* SCTRLR.1   Clear counter */
#define MC_FREE_RUN_ENABLE            BIT_2   /* SCTRLR.2   Free run mode enable */
#define MC_STEP_PULSE_OUTPUT_ENABLE   BIT_3   /* SCTRLR.3   STP output enable */
		
/*---------------------------------------
     Encoder Module
----------------------------------------*/	
	/* Bit definition for ENC_MOD register */
#define ENC_A_POL_TO_GEN_IZ           BIT_0   /* ENC_MOD.0     Required A input polarity for internal Z */
#define ENC_B_POL_TO_GEN_IZ           BIT_1   /* ENC_MOD.1     Required B input polarity for internal Z */
#define ENC_IGNORE_AB_TO_GEN_IZ       BIT_2   /* ENC_MOD.2     Internal Z is generated regardless of A and B signals */
#define ENC_Z_POL_TO_GEN_IZ           BIT_3   /* ENC_MOD.3     Required Z input polarity for internal Z */
#define TRG_EVENT_AT_IZ_ASSERT        BIT_4   /* ENC_MOD.4     Event generated when internal Z becomes assert */
#define TRG_EVENT_AT_IZ_DEASSERT      BIT_5   /* ENC_MOD.5     Event generated when internal Z becomes de-assert */
#define ENC_SEL_RATIO_MASK            0x0300  /* ENC_MOD.9:8   Position encoder select ratio */
  #define ENC_SEL_RATIO_1X            0x0300
  #define ENC_SEL_RATIO_2X            0x0200
  #define ENC_SEL_RATIO_4X            0x0100
#define ENC_DECIMAL_ENABLE            BIT_10  /* ENC_MOD.10    Position encoder select decimal */
#define ENC_SEL_MODE_MASK             0x3000  /* ENC_MOD.13:12 Select encoder mode */
  #define ENC_SEL_MODE_ABZ            0x1000
  #define ENC_SEL_MODE_CW_CCW         0x2000
  #define ENC_SEL_MODE_CLK_DIR        0x3000
#define ENC_HALL_ENABLE               BIT_14  /* ENC_MOD.14    Hall sensor select */
#define ENC_ENABLE                    BIT_15  /* ENC_MOD.15    Enable ENC function */
		
	/* Bit definition for ENC_CLR register */
#define ENC_VALUE_LATCH_ENABLE        BIT_0   /* ENC_CLR.0     Latch encoder counter value before clear */
#define ENC_CLR_EVERY_TRG_EVENT       BIT_1   /* ENC_CLR.1     Clear encoder counter value every Z event */
#define ENC_CLR_ONCE_TRG_EVENT        BIT_2   /* ENC_CLR.2     Clear encoder counter value once with Z event */
#define ENC_CLR_FORCE                 BIT_3   /* ENC_CLR.3     Clear encoder counter value directly, without Z event */
#define ENC_CLR_HALL_OVERRUN          BIT_4   /* ENC_CLR.4     Clear hall overrun state */

	/* Bit definition for HALST register */
#define ENC_CURR_STATUS_MASK          0x0007  /* HALL_ST.2:0   Current hall signal CBA status */
#define ENC_KEEP_STATUS_MASK          0x0070  /* HALL_ST.6:4   Keeped hall signal CBA status */
#define ENC_HALL_OVERRUN              BIT_7   /* HALL_ST.7     Phase change and current state is equal to keep state */

/*---------------------------------------
     I/O Watchdog Module
----------------------------------------*/	
	/* Bit definition for WCFGR register */
#define IOWD_SOF_DETECT               BIT_0   /* WCFGR.0     ESC SOF detects enable */
#define IOWD_ESC_CS_DETECT            BIT_1   /* WCFGR.1     ESC chip select detects enable */	
#define IOWD_FUN_CS_DETECT            BIT_2   /* WCFGR.2     Function chip select detects enable */	
#define IOWD_DETECT_INPUT_RISING      BIT_3   /* WCFGR.3     Detect input condition's edge */		
#define IOWD_WD_ENABLE                BIT_4   /* WCFGR.4     Watchdogs enable */
#define IOWD_EM_ENABLE                BIT_5   /* WCFGR.5     Emergency enable */

	/* Bit definition for WTPVCR register */
#define IOWD_CLR_WTP                  BIT_0   /* WTPVCR.0    Clear watchdog timer peak value */

/*---------------------------------------
     SPI Master Module
----------------------------------------*/	
	/* Bit definition for SPICFGR register */
#define SPIM_CLK_AT_XFER_BEGIN       	BIT_0   /* SPICFGR.0     Set first clock edge at beginning of transfer */
#define SPIM_CLK_IS_ACT_LOW         	BIT_1   /* SPICFGR.1     SPI clock polarity is active low */
#define SPIM_LSB_IS_XFER_FIRST       	BIT_2   /* SPICFGR.2     LSB is transfer first */
#define SPIM_LATE_SAMPLE_ENABLE      	BIT_3   /* SPICFGR.3     Late sample enable */
#define SPIM_DAC_MODE_ENABLE        	BIT_4   /* SPICFGR.4     ADC/DAC mode selection */			
#define SPIM_RDY_LAT_IS_ACT_HIGH     	BIT_5   /* SPICFGR.5     DRDY and LDAC polarity is active high */
#define SPIM_TRG_PULSE_IS_ACT_HIGH   	BIT_6   /* SPICFGR.6     Trigger pulse polarity is active high */					
#define SPIM_RDY_COMBINED_WITH_MISO  	BIT_7   /* SPICFGR.7     DRDY combined with MISO */					
#define SPIM_INTR_IS_ACT_HIGH       	BIT_8   /* SPICFGR.8     Interrupt pulse polarity is active high */
#define SPIM_INTR_IS_EDGE_TRG       	BIT_9   /* SPICFGR.9     Interrupt is edge trigger */
#define SPIM_INTR_ENABLE            	BIT_10  /* SPICFGR.10    Interrupt enable */		
#define SPIM_EXT_DECODER_ENABLE      	BIT_11  /* SPICFGR.11    External decoder enable */		
#define SPIM_SCLK_MISO_DRIV_MASK      (BIT_13|BIT12)  /* SPICFGR.13:12    00:4ma, 01:8ma, 10:12ma, 11:16ma */		
	#define SCLK_MISO_DRIV_4mA          0x0000
	#define SCLK_MISO_DRIV_8mA          BIT12
	#define SCLK_MISO_DRIV_12mA         BIT13
	#define SCLK_MISO_DRIV_16mA         (BIT_13|BIT12)

	/* Bit definition for SPIBRR register */
#define SPIM_CLK_DIVIDER_MASK         0x00ff  /* SPIBRR.7:0   System clock divider */
#define SPIM_FIRST_CLK_DELAYx1K       BIT_8   /* SPIBRR.8 */
#define SPIM_INTR_SS_DELAYx1K         BIT_9   /* SPIBRR.9 */
#define SPIM_LAT_PULSE_GAPx1K         BIT_10  /* SPIBRR.10 */
#define SPIM_LAT_PULSE_WIDTHx1K       BIT_11  /* SPIBRR.11 */
#define SPIM_CLK_ENABLE               BIT_15  /* SPIBRR.15 */

	/* Bit definition for SPILTR register */
#define SPIM_LAT_PULSE_GAP_MASK       0x00ff  /* SPILTR.7:0   DAC latch pulse gap time = (dac_latch_gap_x1K*1023+1)*(lacth_gap+1)*Tsclk */
#define SPIM_LAT_PULSE_WIDTH_MASK     0xff00  /* SPILTR.15:8  DAC latch pulse width = (dac_latch_width_x1K*1023+1)*(latch_width+1)*Tsclk */

  /* Bit definition for SPIPRLR register */
#define SPIM_WAIT_PULSE_BEFORE_S0     BIT_0   /* SPIPRLR.0   Wait pulse before SPI0 */
#define SPIM_WAIT_PULSE_BEFORE_S1     BIT_1   /* SPIPRLR.1   Wait pulse before SPI1 */
#define SPIM_WAIT_PULSE_BEFORE_S2     BIT_2   /* SPIPRLR.2   Wait pulse before SPI2 */
#define SPIM_WAIT_PULSE_BEFORE_S3     BIT_3   /* SPIPRLR.3   Wait pulse before SPI3 */
#define SPIM_WAIT_PULSE_BEFORE_S4     BIT_4   /* SPIPRLR.4   Wait pulse before SPI4 */
#define SPIM_WAIT_PULSE_BEFORE_S5     BIT_5   /* SPIPRLR.5   Wait pulse before SPI5 */
#define SPIM_WAIT_PULSE_BEFORE_S6     BIT_6   /* SPIPRLR.6   Wait pulse before SPI6 */
#define SPIM_WAIT_PULSE_BEFORE_S7     BIT_7   /* SPIPRLR.7   Wait pulse before SPI7 */
#define SPIM_WAIT_RDY_ENABLE_LAT_S0   BIT_8   /* SPIPRLR.8   Wait RDY before/LDAC enable after SPI0 */
#define SPIM_WAIT_RDY_ENABLE_LAT_S1   BIT_9   /* SPIPRLR.9   Wait RDY before/LDAC enable after SPI1 */
#define SPIM_WAIT_RDY_ENABLE_LAT_S2   BIT_10  /* SPIPRLR.10  Wait RDY before/LDAC enable after SPI2 */
#define SPIM_WAIT_RDY_ENABLE_LAT_S3   BIT_11  /* SPIPRLR.11  Wait RDY before/LDAC enable after SPI3 */
#define SPIM_WAIT_RDY_ENABLE_LAT_S4   BIT_12  /* SPIPRLR.12  Wait RDY before/LDAC enable after SPI4 */
#define SPIM_WAIT_RDY_ENABLE_LAT_S5   BIT_13  /* SPIPRLR.13  Wait RDY before/LDAC enable after SPI5 */
#define SPIM_WAIT_RDY_ENABLE_LAT_S6   BIT_14  /* SPIPRLR.14  Wait RDY before/LDAC enable after SPI6 */
#define SPIM_WAIT_RDY_ENABLE_LAT_S7   BIT_15  /* SPIPRLR.15  Wait RDY before/LDAC enable after SPI7 */

  /* Bit definition for SPI03SS/SPI47SS register */
#define SPIM_CH04_ID_MASK             0x0007  /* SPI03SSR/SPI47SSR.2:0   Channel 0/4 slave select */
#define SPIM_CH04_KEEP_ASSERT         BIT_3   /* SPI03SSR/SPI47SSR.3     Channel 0/4 slave select keep assert */
#define SPIM_CH15_ID_MASK             0x0070  /* SPI03SSR/SPI47SSR.6:4   Channel 1/5 slave select */
#define SPIM_CH15_KEEP_ASSERT         BIT_7   /* SPI03SSR/SPI47SSR.7     Channel 1/5 slave select keep assert */
#define SPIM_CH26_ID_MASK             0x0700  /* SPI03SSR/SPI47SSR.10:8  Channel 2/6 slave select */
#define SPIM_CH26_KEEP_ASSERT         BIT_11  /* SPI03SSR/SPI47SSR.11    Channel 2/6 slave select keep assert */
#define SPIM_CH37_ID_MASK             0x7000  /* SPI03SSR/SPI47SSR.14:12 Channel 3/7 slave select */
#define SPIM_CH37_KEEP_ASSERT         BIT_15  /* SPI03SSR/SPI47SSR.15    Channel 3/7 slave select keep assert */

  /* Bit definition for SPI01BC/SPI23BC/SPI45BC/SPI67BC register */
#define SPIM_CH0246_TX_CNT_MASK       0x0007  /* S01BC/S23BC/S45BC/S67BC.2:0   Channel 0/2/4/6 TX byte count */
#define SPIM_CH0246_RX_START_MASK     0x0070  /* S01BC/S23BC/S45BC/S67BC.6:4   Channel 0/2/4/6 RX start byte count */
#define SPIM_CH1357_TX_CNT_MASK       0x0700  /* S01BC/S23BC/S45BC/S67BC.10:8  Channel 1/3/5/7 TX byte count */
#define SPIM_CH1357_RX_START_MASK     0x7000  /* S01BC/S23BC/S45BC/S67BC.14:12 Channel 1/3/5/7 RX start byte count */

  /* Bit definition for SPINTS register */
#define SPIM_ALL_XFER_COMPLETED       BIT_0   /* SPINTSR.0 */
#define SPIM_INTR_IS_ASSERTED         BIT_1   /* SPINTSR.1 */
#define SPIM_BUSY                     BIT_2   /* SPINTSR.2 */
#define SPIM_SLAVE_SELECT_ERR         BIT_3   /* SPINTSR.3 */
#define SPIM_WAIT_TRG_PULSE_TIMEOUT   BIT_4   /* SPINTSR.4 */
#define SPIM_WAIT_RDY_TIMEOUT         BIT_5   /* SPINTSR.5 */
#define SPIM_TRG_PULSE_IS_OVERRUN     BIT_6   /* SPINTSR.6 */
#define SPIM_RX_BUF_IS_OVERRUN        BIT_7   /* SPINTSR.7 */

  /* Bit definition for SPITS register */
#define SPIM_CH0_TRG_PULSE_TIMEOUT    BIT_0   /* SPITSR.0 */
#define SPIM_CH1_TRG_PULSE_TIMEOUT    BIT_1   /* SPITSR.1 */
#define SPIM_CH2_TRG_PULSE_TIMEOUT    BIT_2   /* SPITSR.2 */
#define SPIM_CH3_TRG_PULSE_TIMEOUT    BIT_3   /* SPITSR.3 */
#define SPIM_CH4_TRG_PULSE_TIMEOUT    BIT_4   /* SPITSR.4 */
#define SPIM_CH5_TRG_PULSE_TIMEOUT    BIT_5   /* SPITSR.5 */
#define SPIM_CH6_TRG_PULSE_TIMEOUT    BIT_6   /* SPITSR.6 */
#define SPIM_CH7_TRG_PULSE_TIMEOUT    BIT_7   /* SPITSR.7 */
#define SPIM_CH8_TRG_PULSE_TIMEOUT    BIT_8   /* SPITSR.8 */
#define SPIM_CH9_TRG_PULSE_TIMEOUT    BIT_9   /* SPITSR.9 */
#define SPIM_CH10_TRG_PULSE_TIMEOUT   BIT_10  /* SPITSR.10 */
#define SPIM_CH11_TRG_PULSE_TIMEOUT   BIT_11  /* SPITSR.11 */
#define SPIM_CH12_TRG_PULSE_TIMEOUT   BIT_12  /* SPITSR.12 */
#define SPIM_CH13_TRG_PULSE_TIMEOUT   BIT_13  /* SPITSR.13 */
#define SPIM_CH14_TRG_PULSE_TIMEOUT   BIT_14  /* SPITSR.14 */
#define SPIM_CH15_TRG_PULSE_TIMEOUT   BIT_15  /* SPITSR.15 */

  /* Bit definition for SPIPOSR register */
#define SPIM_CH0_TRG_PULSE_OVERRUN    BIT_0   /* SPIPOSR.0 */
#define SPIM_CH1_TRG_PULSE_OVERRUN    BIT_1   /* SPIPOSR.1 */
#define SPIM_CH2_TRG_PULSE_OVERRUN    BIT_2   /* SPIPOSR.2 */
#define SPIM_CH3_TRG_PULSE_OVERRUN    BIT_3   /* SPIPOSR.3 */
#define SPIM_CH4_TRG_PULSE_OVERRUN    BIT_4   /* SPIPOSR.4 */
#define SPIM_CH5_TRG_PULSE_OVERRUN    BIT_5   /* SPIPOSR.5 */
#define SPIM_CH6_TRG_PULSE_OVERRUN    BIT_6   /* SPIPOSR.6 */
#define SPIM_CH7_TRG_PULSE_OVERRUN    BIT_7   /* SPIPOSR.7 */

  /* Bit definition for SPIDSR register */
#define SPIM_CH0_OVERRUN              BIT_0   /* SPIDSR.0 */
#define SPIM_CH1_OVERRUN              BIT_1   /* SPIDSR.1 */
#define SPIM_CH2_OVERRUN              BIT_2   /* SPIDSR.2 */
#define SPIM_CH3_OVERRUN              BIT_3   /* SPIDSR.3 */
#define SPIM_CH4_OVERRUN              BIT_4   /* SPIDSR.4 */
#define SPIM_CH5_OVERRUN              BIT_5   /* SPIDSR.5 */
#define SPIM_CH6_OVERRUN              BIT_6   /* SPIDSR.6 */
#define SPIM_CH7_OVERRUN              BIT_7   /* SPIDSR.7 */
#define SPIM_CH8_OVERRUN              BIT_8   /* SPIDSR.8 */
#define SPIM_CH9_OVERRUN              BIT_9   /* SPIDSR.9 */
#define SPIM_CH10_OVERRUN             BIT_10  /* SPIDSR.10 */
#define SPIM_CH11_OVERRUN             BIT_11  /* SPIDSR.11 */
#define SPIM_CH12_OVERRUN             BIT_12  /* SPIDSR.12 */
#define SPIM_CH13_OVERRUN             BIT_13  /* SPIDSR.13 */
#define SPIM_CH14_OVERRUN             BIT_14  /* SPIDSR.14 */
#define SPIM_CH15_OVERRUN             BIT_15  /* SPIDSR.15 */		

  /* Bit definition for SPIMCR register */
#define SPIM_CH0_RX_BUF_CLR           BIT_0   /* SPIMCR.0 Clear RX Channel 0 */
#define SPIM_CH1_RX_BUF_CLR           BIT_1   /* SPIMCR.1 Clear RX Channel 1 */
#define SPIM_CH2_RX_BUF_CLR           BIT_2   /* SPIMCR.2 Clear RX Channel 2 */
#define SPIM_CH3_RX_BUF_CLR           BIT_3   /* SPIMCR.3 Clear RX Channel 3 */
#define SPIM_CH4_RX_BUF_CLR           BIT_4   /* SPIMCR.4 Clear RX Channel 4 */
#define SPIM_CH5_RX_BUF_CLR           BIT_5   /* SPIMCR.5 Clear RX Channel 5 */
#define SPIM_CH6_RX_BUF_CLR           BIT_6   /* SPIMCR.6 Clear RX Channel 6 */
#define SPIM_CH7_RX_BUF_CLR           BIT_7   /* SPIMCR.7 Clear RX Channel 7 */
#define SPIM_GO                       BIT_8   /* SPIMCR.8 Start the transfer enable */
#define SPIM_ACCESS_CHANNELS_MASK     0x0E00  /* SPIMCR.9:11 Access Channel */
#define SPIM_CONTINUE_MODE_ENABLE     BIT_12  /* SPIMCR.12 Continuous Access Enable */
#define SPIM_RX_BUF_HANDSHAKE_ENABLE  BIT_13  /* SPIMCR.13 RX Update Setting */
#define SPIM_CLR_COMPLETE_STATUS      BIT_14  /* SPIMCR.14 Clear complete status */
#define SPIM_CLR_INTR                 BIT_15  /* SPIMCR.15 Clear interrupt */

/*---------------------------------------
     Bridge Module
----------------------------------------*/	
	/* Bit definition for INTCR register */
#define PWM_A_INTR_ENABLE                 BIT_0   /* INTCR.0   PWM pulse A interrupt enable */
#define PWM_B_INTR_ENABLE                 BIT_1   /* INTCR.1   PWM pulse B interrupt enable */
#define PWM_CENTER_INTR_ENABLE            BIT_2   /* INTCR.2   PWM cycle center trigger interrupt enable */
#define PWM_START_INTR_ENABLE             BIT_3   /* INTCR.3   PWM cycle start trigger interrupt enable */
#define STEP_COMPLETE_INTR_ENABLE         BIT_4   /* INTCR.4   Step completed interrupt enable */
#define SPIM_COMPLETE_INTR_ENABLE         BIT_6   /* INTCR.6   SPIM completed interrupt enable */
#define SPIM_ERR_INTR_ENABLE              BIT_7   /* INTCR.7   SPIM error interrupt enable */
#define ENC_Z_ASSERT_EVENT_INTR_ENABLE    BIT_8   /* INTCR.8   ENC Z assert event interrupt enable */
#define ENC_Z_DEASSERT_EVENT_INTR_ENABLE  BIT_9   /* INTCR.9   ENC Z de-assert event interrupt enable */
#define ENC_ERR_INTR_ENABLE               BIT_10  /* INTCR.10  ENC error interrupt enable */
#define IOWD_TIMEOUT_INTR_ENABLE          BIT_11  /* INTCR.11  I/O Watchdog timeout interrupt enable */
#define LB_ERR_INTR_ENABLE                BIT_12  /* INTCR.12  Local bus internal error interrupt enable */
#define SPIS_ERR_INTR_ENABLE              BIT_13  /* INTCR.13  SPI slave internal error interrupt enable */
#define EM_INTR_ENABLE                    BIT_15  /* INTCR.15  Activation of external low active emergency enable */

	/* Bit definition for INTSR register */
#define PWM_A_INTR_STATUS                 BIT_0   /* INTSR.0   PWM pulse A interrupt status */
#define PWM_B_INTR_STATUS                 BIT_1   /* INTSR.1   PWM pulse B interrupt status */
#define PWM_CENTER_INTR_STATUS            BIT_2   /* INTSR.2   PWM cycle center trigger interrupt status */
#define PWM_START_INTR_STATUS             BIT_3   /* INTSR.3   PWM cycle start trigger interrupt status */
#define STEP_COMPLETE_INTR_STATUS         BIT_4   /* INTSR.4   Step completed interrupt status */
#define SPIM_COMPLETE_INTR_STATUS         BIT_6   /* INTSR.6   SPIM completed interrupt status */
#define SPIM_ERR_INTR_STATUS              BIT_7   /* INTSR.7   SPIM error interrupt status */
#define ENC_Z_ASSERT_EVENT_INTR_STATUS    BIT_8   /* INTSR.8   ENC Z assert event interrupt status */
#define ENC_Z_DEASSERT_EVENT_INTR_STATUS  BIT_9   /* INTSR.9   ENC Z de-assert event interrupt status */
#define ENC_ERR_INTR_STATUS               BIT_10  /* INTSR.10  ENC error interrupt status */
#define IOWD_TIMEOUT_INTR_STATUS          BIT_11  /* INTSR.11  I/O Watchdog timeout interrupt status */
#define LB_ERR_INTR_STATUS                BIT_12  /* INTSR.12  Local bus internal error interrupt status */
#define SPIS_ERR_INTR_STATUS              BIT_13  /* INTSR.13  SPI slave internal error interrupt status */
#define ESC_INTR_STATUS                   BIT_14  /* INTSR.14  ESC interrupt status */
#define EM_INTR_STATUS                    BIT_15  /* INTSR.15  Activation of external low active emergency status */

	/* Bit definition for ESTOR register */
#define MC_FUNC_OVERRID                   BIT_0   /* ESTOR.0   Motor control function override */
#define SPIM_FUNC_OVERRID                 BIT_1   /* ESTOR.1   SPI Master function override */
#define BRIDGE_FUNC_OVERRID               BIT_7   /* ESTOR.7   Bridge function override */
		
	/* Bit definition for HSTSR register */
#define INTERNAL_READ_DECODE_ERR          BIT_0   /* HSTSR.0   Internal bus read decode error */
#define HOST_READ_CMD_ERR                 BIT_2   /* HSTSR.2   Local bus/SPI read command error */		
#define INTERNAL_WRITE_DECODE_ERR         BIT_4   /* HSTSR.4   Internal bus write decode error */
#define INTERNAL_WRITE_RESP_ERR           BIT_5   /* HSTSR.5   Internal bus write slave response error */
#define HOST_WRITE_CMD_ERR                BIT_6   /* HSTSR.6   Local bus/SPI write command error */

	/* Bit definition for PHYPR register */	
#define PHY0_TX_AMP_TUNE_MASK             0x001F  /* PHY0 TX amplitude tune */
#define PHY1_TX_AMP_TUNE_MASK             0x03E0  /* PHY1 TX amplitude tune */
#define PHY_SELECT_MASK                   0x3000  /* PHY select */

	/* Bit definition for MINFR register */	

	/* Bit definition for ECTRLR register */	
#define EFUSE_BIT_ADDR_MASK               0x0007
#define EFUSE_BYTE_ADDR_MASK              0x0038
#define EFUSE_CMD_MASK                    0x00C0
	#define EFUSE_CMD_NACT                  0x0000
	#define EFUSE_CMD_RD                    0x0001
	#define EFUSE_CMD_WR                    0x0010
	#define EFUSE_CMD_NOF                   0x0011
	
	/* Bit definition for ERDR register */	

	/* Bit definition for FMIRER register */	
#define PWM_FUN_MIRROR                    BIT_0
#define ENC_FUN_MIRROR                    BIT_1
#define SPIM_FUN_MIRROR                   BIT_2
#define IOWD_FUN_MIRROR                   BIT_3

/* ====================== Access Control Register Address Definition ====================== */
#define AX58100_ACCESS_CTRL_REGS_BASE     (0x0580)
#define AX58100_ACCESS_CTRL_REGS_END      (0x05C0)

/*---------------------------------------
     Motor Control Module
----------------------------------------*/
#define MCTLACR     0x0580    /* 0x0580: MCTLR Access Control Register */
#define PXCFGACR    0x0581    /* 0x0581: PXCFGR Access Control Register */
#define PTACFGACR   0x0582    /* 0x0582: PTAPPR Access Control Register */
#define PTBCFGACR   0x0583    /* 0x0583: PTBPPR Access Control Register */
#define PPCACR      0x0584    /* 0x0584: PPCR Access Control Register */
#define PBBMACR     0x0585    /* 0x0585: PBBMR Access Control Register */
#define P1CTRLACR   0x0586    /* 0x0586: P1CTRLR Access Control Register */
#define P1SHACR     0x0587    /* 0x0587: P1SHR Access Control Register */
#define P1HPWACR    0x0588    /* 0x0588: P1HPWR Access Control Register */
#define P2CTRLACR   0x0589    /* 0x0589: P2CTRLR Access Control Register */
#define P2SHACR     0x058A    /* 0x058A: P2SHR Access Control Register */
#define P2HPWACR    0x058B    /* 0x058B: P2HPWR Access Control Register */
#define P3CTRLACR   0x058C    /* 0x058C: P3CTRLR Access Control Register */
#define P3SHACR     0x058D    /* 0x058D: P3SHR Access Control Register */
#define P3HPWACR    0x058E    /* 0x058E: P3HPWR Access Control Register */
#define SGTACR      0x058F    /* 0x058F: Step Gap Time (SGT) Access Control Register */
#define SHPWACR     0x0590    /* 0x0590: SHPWR Access Control Register */
#define TDLYACR     0x0591    /* 0x0591: TDLYR Access Control Register */
#define STNACR      0x0592    /* 0x0592: Step Target Number (STN) Access Control Register */
#define SCFGACR     0x0593    /* 0x0593: SCFGR Access Control Register */
#define SCTRLACR    0x0594    /* 0x0594: SCTRLR Access Control Register */
#define SCNTACR     0x0595    /* 0x0595: Step Counter Content (SCNT) Access Control Register */

/*---------------------------------------
     Encoder Module
----------------------------------------*/
#define ECNTVACR    0x0596    /* 0x0596: Encoder Counter Value Access Control Register */
#define ECNSTACR    0x0597    /* 0x0597: Encoder Constant Access Control Register */
#define ELATACR     0x0598    /* 0x0598: Encoder Latched Access Control Register */
#define EMODACR     0x0599    /* 0x0599: ENC_MOD Access Control Register */
#define ENCSTACR    0x059A    /* 0x059A: ENC_CLR Access Control Register */
#define HSTACR      0x059B    /* 0x059B: HALL_ST Access Control Register */

/*---------------------------------------
     I/O Watchdog Module
----------------------------------------*/
#define WTACR       0x059C    /* 0x059C: Watchdog Timer Access Control Register */	
#define WCACR       0x059D    /* 0x059D: Watchdog Control Access Control Register */	
#define WPCACR      0x059E    /* 0x059E: Watchdog Peak Value Clear Register */		
#define WPACR       0x059F    /* 0x059F: Watchdog monitored signals Polarity Access Control Register */		
#define WMACR       0x05A0    /* 0x05A0: Watchdog monitored signals Mask Access Control Register */
#define WOMACR      0x05A1    /* 0x05A1: Watchdog monitored signals Output Mask Access Control Register */
#define WOEACR      0x05A2    /* 0x05A2: Watchdog monitored signals Output Enable Access Control Register */
#define WOPACR      0x05A3    /* 0x05A3: Watchdog monitored signals Output Polarity Access Control Register */	
#define WPKACR      0x05A4    /* 0x05A4: Watchdog Timer Peak value Access Control Register */		

/*---------------------------------------
     SPI Master Module
----------------------------------------*/
#define SPICFIGACR  0x05A5    /* 0x05A5: SPI Configure Access Control Register */
#define SPIBRACR    0x05A6    /* 0x05A6: SPI Baud Rate Access Control Register */
#define SPIDBSACR   0x05A7    /* 0x05A7: SPI Delay Byte and SS Access Control Register */
#define SPIDTACR    0x05A8    /* 0x05A8: SPI Delay Transfer Access Control Register */
#define SPIRPTACR   0x05A9    /* 0x05A9: SPI RDY/Pulse Time Access Control Register */
#define SPILDTACR   0x05AA    /* 0x05AA: SPI LDAC Time Access Control Register */
#define SPIPRLFACR  0x05AB    /* 0x05AB: SPI Pulse/ RDY/ LDAC Function Access Control Register */
#define SPI01BCACR  0x05AC    /* 0x05AC: SPI 0/1 Byte Count Access Control Register */
#define SPI23BCACR  0x05AD    /* 0x05AD: SPI 2/3 Byte Count Access Control Register */
#define SPI45BCACR  0x05AE    /* 0x05AE: SPI 4/5 Byte Count Access Control Register */
#define SPI67BCACR  0x05AF    /* 0x05AF: SPI 6/7 Byte Count Access Control Register */
#define SPI03SACR   0x05B0    /* 0x05B0: SPI 0/1/2/3 Slave Select Access Control Register */
#define SPI47SACR   0x05B1    /* 0x05B1: SPI 4/5/6/7 Slave Select Access Control Register */
#define SPIINTSACR  0x05B2    /* 0x05B2: SPI Interrupt Status Access Control Register */
#define SPITSACR    0x05B3    /* 0x05B3: SPI Timeout Status Access Control Register */
#define SPIPOSACR   0x05B4    /* 0x05B4: SPI Pulse Overrun Status Access Control Register */
#define SPIDSACR    0x05B5    /* 0x05B5: SPI Data Status Mirror Access Control Register */
#define SPIC0DACR   0x05B6    /* 0x05B6: SPI Channel 0 Data Access Control Register */
#define SPIC1DACR   0x05B7    /* 0x05B7: SPI Channel 1 Data Access Control Register */
#define SPIC2DACR   0x05B8    /* 0x05B8: SPI Channel 2 Data Access Control Register */
#define SPIC3DACR   0x05B9    /* 0x05B9: SPI Channel 3 Data Access Control Register */
#define SPIC4DACR   0x05BA    /* 0x05BA: SPI Channel 4 Data Access Control Register */
#define SPIC5DACR   0x05BB    /* 0x05BB: SPI Channel 5 Data Access Control Register */
#define SPIC6DACR   0x05BC    /* 0x05BC: SPI Channel 6 Data Access Control Register */
#define SPIC7DACR   0x05BD    /* 0x05BD: SPI Channel 7 Data Access Control Register */
#define SPICACR     0x05BE    /* 0x05BE: SPI Control Access Control Register */

/*---------------------------------------
     Bridge Module
----------------------------------------*/
#define INTCACR     0x05BF   /* 0x05BF: INTCR Access Control Register */
#define INTSACR     0x05C0   /* 0x05C0: INTSR Access Control Register */

	/* Mirror Registers */
#define FMIRER      0x05C1   /* 0x05C1: Function Mirror Enable Register, for ESC side only */

/* TYPE DECLARATIONS */

/* GLOBAL VARIABLES */

/* EXPORTED SUBPROGRAM SPECIFICATIONS */

#endif /* __AX58100_REGS_H__ */

/* End of ax58100_regs.h */
