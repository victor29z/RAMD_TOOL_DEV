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
#ifndef __AX58100_REGOBJS_H__
#define __AX58100_REGOBJS_H__

/* INCLUDE FILE DECLARATIONS */
#include "ax58100_regs.h"

/* NAMING CONSTANT DECLARATIONS */

/* ====================== Register Bit Definition ====================== */

/* ------------- Motor Control ------------- */
  /* MCTLR */
typedef union _MCTLR_OBJECT
{
  u16 d16;
  struct{
    u16 pwm_func_enable:         1;  /* MCTLR.0      PWM function enable */
    u16 pwm_8x_enable:           1;  /* MCTLR.1      PWM 8X Magnified enable */		
    u16 reserved_3_2:            2;
    u16 step_func_enable:        1;  /* MCTLR.4      Step function enable */	
    u16 reseverd_15_5:          11;
  } b;
} MCTLR_OBJECT;

  /* PXCFGR */
typedef union _PXCFGR_OBJECT
{
  u16 d16;
  struct{
    u16 abcsab_high_pulse_width: 8;  /* PXCFGR.7:0   A/B/C/S/AB high pulse width */
    u16 abcsab_pulse_pol:        1;  /* PXCFGR.8     A/B/C/S/AB pulse polarity */
    u16 s_pulse_output_enable:   1;  /* PXCFGR.9     S pulse output enable */	
    u16 c_pulse_output_enable:   1;  /* PXCFGR.10    C pulse output enable */	
    u16 a_pulse_output_enable:   1;  /* PXCFGR.11    A pulse output enable */	
    u16 b_pulse_output_enable:   1;  /* PXCFGR.12    B pulse output enable */	
    u16 ab_pulse_output_enable:  1;  /* PXCFGR.13    AB pulse output enable */	
    u16 pwm_align_mode:          2;  /* PXCFGR.15:14 PWM High pulse alignment */	
  } b;
} PXCFGR_OBJECT;

  /* PBBMR */
typedef union _PBBMR_OBJECT
{
  u16 d16;
  struct{
    u16 pwm_l_bbm_time:          8;  /* PBBMR.7:0   PWM break before make time for low side MOS-FET control */
    u16 pwm_h_bbm_time:          8;  /* PBBMR.15:8  PWM break before make time for high side MOS-FET control */
  } b;
} PBBMR_OBJECT;

  /* P1CTRLR/P2CTRLR/P3CTRLR */
typedef union _PxCTRLR_OBJECT
{
  u16 d16;
  struct{
    u16 pwm_h_pol_is_neg:        1;  /* PxCTRLR.0    PWMx H polarity setting */
    u16 pwm_l_pol_is_neg:        1;  /* PxCTRLR.1    PWMx L polarity setting */
    u16 pwm_h_output_enable:     1;  /* PxCTRLR.2    PWMx H output enable */
    u16 pwm_l_output_enable:     1;  /* PxCTRLR.3    PWMx L output enable */			
    u16 pwm_channel_enable:      1;  /* PxCTRLR.4    PWMx channel enable */					
    u16 reserved_15_5:					 11;
  } b;
} PxCTRLR_OBJECT;

  /* SCFGR */
typedef union _SCFGR_OBJECT
{
	u16 d16;
	struct{
		u16 step_pol_is_neg:         1;	/* SCFGR.0   Step pulse polarity */
		u16 dir_pol_is_neg:          1;	/* SCFGR.1   Direction signal polarity */
		u16 reserved_15_2:           14;
	} b;
} SCFGR_OBJECT;

  /* SCTRLR */
typedef union _SCTRLR_OBJECT
{
	u16 d16;
	struct{
		u16 dir_output_enable:       1;	/* SCTRLR.0   DIR output enable */
		u16 clear_counter:           1;	/* SCTRLR.1   Clear counter */
		u16 free_run_enable:         1;	/* SCTRLR.2   Free run mode enable */
		u16 step_output_enable:      1;	/* SCTRLR.3   STP output enable */		
		u16 reserved_15_4:           12;
	} b;
} SCTRLR_OBJECT;

/* ------------- Encoder ------------- */
  /* EMOD */
typedef union _EMOD_OBJECT
{
	u16 d16;
	struct{
		u16 a_pol_to_gen_iz:                1;	/* EMOD.0     Required A input polarity for internal Z */
		u16 b_pol_to_gen_iz:                1;	/* EMOD.1     Required B input polarity for internal Z */
		u16 ignore_ab_to_gen_iz:            1;	/* EMOD.2     Internal Z is generated regardless of A and B signals */	
		u16 z_pol_to_gen_iz:                1;	/* EMOD.3     Required Z input polarity for internal Z */	
		u16 trg_event_at_iz_assert:         1;	/* EMOD.4     Event generated when internal Z becomes assert */	
		u16 trg_event_at_iz_deassert:       1;	/* EMOD.5     Event generated when internal Z becomes de-assert */	
		u16 reserved_7_6:                   2;		
		u16 encoder_ratio:                  2;	/* EMOD.9:8   Position encoder select ratio */	
		u16 encoder_decimal:                1;	/* EMOD.10    Position encoder select decimal */	
		u16 reserved_11:                    1;
		u16 encoder_mode:                   2;	/* EMOD.13:12 Select encoder mode */			
		u16 hall_sensor_select:             1;	/* EMOD.14    Hall sensor select */			
		u16 enc_func_enable:                1;	/* EMOD.15    Enable ENC function */	
	} b;
} EMOD_OBJECT;

  /* ECLR */
typedef union _ECLR_OBJECT
{
	u16 d16;
	struct{
		u16 latch_value_before_clr:  1;	/* ECLR.0     Latch encoder counter value before clear */
		u16 clr_value_every_event:   1;	/* ECLR.1     Clear encoder counter value every Z event */
		u16 clr_value_once_event:    1;	/* ECLR.2     Clear encoder counter value once with Z event */	
		u16 clr_value_directly:      1;	/* ECLR.3     Clear encoder counter value directly, without Z event */	
		u16 clr_hall_overrun:        1;	/* ECLR.4     Clear hall overrun state */
		u16 reserved_15_5:          11;
	} b;
} ECLR_OBJECT;

  /* HALLST */
typedef union _HALLST_OBJECT
{
	u16 d16;
	struct{
		u16 curr_cba_stu:            3;	/* HALLST.2:0   Current hall signal CBA status */
		u16 reserved_3:              1;
		u16 keep_cba_stu:            3;	/* HALLST.6:4   Keeped hall signal CBA status */	
		u16 over_run:                1;	/* HALLST.7     Phase change and current state is equal to keep state */			
		u16 reserved_15_8:           8;
	} b;
} HALLST_OBJECT;

/* ------------- IO Watchdog ------------- */
  /* WCFGR */
typedef union _WCFGR_OBJECT
{
	u16 d16;
	struct{
		u16 sof_detect_enable:       1;	/* WCFGR.0     ESC SOF detects enable */
		u16 esc_cs_enable:           1;	/* WCFGR.1     ESC chip select detects enable */	
		u16 fun_cs_enable:           1;	/* WCFGR.2     Function chip select detects enable */	
		u16 detect_input_rising:     1;	/* WCFGR.3     Detect input condition's edge */			
		u16 watchdog_enable:         1;	/* WCFGR.4     Watchdogs enable */		
		u16 emergency_enable:        1;	/* WCFGR.5     Emergency enable */				
		u16 reserved_15_6:          10;
	} b;
} WCFGR_OBJECT;

  /* WTPVCR */
typedef union _WTPVCR_OBJECT
{
	u16 d16;
	struct{
		u16 clear_peak_value:        1;	/* WTPVCR.0     Clear Watchdog Timer Peak Value */
		u16 reserved_15_1:          15;
	} b;
} WTPVCR_OBJECT;

/* ------------- SPI Master ------------- */
  /* SPICFGR */
typedef union _SPICFGR_OBJECT
{
	u16 d16;
	struct{
		u16 clk_at_xfer_begin:        1;	/* SPICFGR.0     Set first clock edge at beginning of transfer */
		u16 clk_is_act_low:           1;	/* SPICFGR.1     SPI clock polarity is active low */
		u16 lsb_is_xfer_first:        1;	/* SPICFGR.2     LSB is transfer first */	
		u16 late_sample_enable:       1;	/* SPICFGR.3     Late sample enable */	
		u16 dac_mode_enable:          1;	/* SPICFGR.4     ADC/DAC mode selection */			
		u16 ready_latch_is_act_high:  1;	/* SPICFGR.5     DRDY and LDAC polarity is active high */
		u16 trg_pulse_is_act_high:    1;	/* SPICFGR.6     Trigger pulse polarity is active high */					
		u16 ready_combined_with_miso: 1;	/* SPICFGR.7     DRDY combined with MISO */					
		u16 intr_is_act_high:         1;	/* SPICFGR.8     Interrupt pulse polarity is active high */
		u16 intr_is_edge_trg:         1;	/* SPICFGR.9     Interrupt is edge trigger */
		u16 intr_enable:              1;	/* SPICFGR.10    Interrupt enable */		
		u16 ext_decoder_enable:       1;	/* SPICFGR.11    External decoder enable */				
		u16 sclk_miso_driving:        2;	/* SPICFGR.13:12 00:4ma, 01:8ma, 10:12ma, 11:16ma */							
		u16 reserved_15_14:           2;	/* SPICFGR.15:14 Reserved */					
	} b;
} SPICFGR_OBJECT;

  /* SPIBRR */
typedef union _SPIBRR_OBJECT
{
	u16 d16;
	struct{
		u16 clk_divider:              8;	/* SPIBRR.7:0   System clock divider */
		u16 first_clk_delay_x1K:      1;	/* SPIBRR.8 */
		u16 inter_ss_delay_x1K:       1;	/* SPIBRR.9 */	
		u16 latch_pulse_gap_x1K:      1;	/* SPIBRR.10 */	
		u16 latch_pulse_width_x1K:    1;	/* SPIBRR.11 */			
		u16 reserved_14_12:           3;	/* SPIBRR.14:12 */	
		u16 clk_enable:               1;	/* SPIBRR.15 */			
	} b;
} SPIBRR_OBJECT;

  /* SPIDBSR */
/*
Mode0, 1 transfer with DBS1K:
  tDBS1 = (1024*(DBS + 1) + 1.0)*Tsclk
  tDBS2 = (1024*(DBS + 1) + 0.5)*Tsclk
  tDBS3 = (1024*(DBS + 1) + 0.5)*Tsclk

Mode2, 3 transfer with DBS1K:
  tDBS1 = (1024*(DBS + 1) + 0.5)*Tsclk
  tDBS2 = (1024*(DBS + 1) + 0.5)*Tsclk
  tDBS3 = (1024*(DBS + 1) + 1.0)*Tsclk

Mode0, 1 transfer without DBS1K:
  tDBS1 = (DBS + 1.0)*Tsclk
  tDBS2 = (DBS + 0.5)*Tsclk
  tDBS3 = (DBS + 0.5)*Tsclk

Mode2, 3 transfer without DBS1K:
  tDBS1 = (DBS + 0.5)*Tsclk
  tDBS2 = (DBS + 0.5)*Tsclk
  tDBS3 = (DBS + 1.0)*Tsclk	
	** Tsclk = SCLK clock period
*/

  /* SPIRPTR */


  /* SPILTR */
typedef union _SPILTR_OBJECT
{
	u16 d16;
	struct{
		u16 latch_pulse_gap:           8;	/* SPILTR.7:0   DAC latch pulse gap time = (dac_latch_gap_x1K*1023+1)*(lacth_gap+1)*Tsclk */
		u16 latch_pulse_width:         8;	/* SPILTR.15:8  DAC latch pulse width = (dac_latch_width_x1K*1023+1)*(latch_width+1)*Tsclk */		
	} b;
} SPILTR_OBJECT;

  /* SPIPRLR */
typedef union _SPIPRLR_OBJECT
{
	u16 d16;
	struct{
		u16 wait_pulse_before_s0:                 1;	/* SPIPRLR.0   Wait pulse before SPI0 */
		u16 wait_pulse_before_s1:                 1;	/* SPIPRLR.1   Wait pulse before SPI1 */
		u16 wait_pulse_before_s2:                 1;	/* SPIPRLR.2   Wait pulse before SPI2 */
		u16 wait_pulse_before_s3:                 1;	/* SPIPRLR.3   Wait pulse before SPI3 */
		u16 wait_pulse_before_s4:                 1;	/* SPIPRLR.4   Wait pulse before SPI4 */
		u16 wait_pulse_before_s5:                 1;	/* SPIPRLR.5   Wait pulse before SPI5 */
		u16 wait_pulse_before_s6:                 1;	/* SPIPRLR.6   Wait pulse before SPI6 */
		u16 wait_pulse_before_s7:                 1;	/* SPIPRLR.7   Wait pulse before SPI7 */		
		u16 waitRdyBefore_genLdacAfter_s0:        1;	/* SPIPRLR.8   Wait RDY before/Generate LDAC after SPI0 */
		u16 waitRdyBefore_genLdacAfter_s1:        1;	/* SPIPRLR.9   Wait RDY before/Generate LDAC after SPI1 */
		u16 waitRdyBefore_genLdacAfter_s2:        1;	/* SPIPRLR.10  Wait RDY before/Generate LDAC after SPI2 */
		u16 waitRdyBefore_genLdacAfter_s3:        1;	/* SPIPRLR.11  Wait RDY before/Generate LDAC after SPI3 */
		u16 waitRdyBefore_genLdacAfter_s4:        1;	/* SPIPRLR.12  Wait RDY before/Generate LDAC after SPI4 */
		u16 waitRdyBefore_genLdacAfter_s5:        1;	/* SPIPRLR.13  Wait RDY before/Generate LDAC after SPI5 */
		u16 waitRdyBefore_genLdacAfter_s6:        1;	/* SPIPRLR.14  Wait RDY before/Generate LDAC after SPI6 */
		u16 waitRdyBefore_genLdacAfter_s7:        1;	/* SPIPRLR.15  Wait RDY before/Generate LDAC after SPI7 */				
	} b;
} SPIPRLR_OBJECT;

  /* SPI03SSR/SPI47SSR */
typedef union _SPIxxSS_OBJECT
{
	u16 d16;
	struct{
		u16 ch04_id:               3;	/* SPI03SSR/SPI47SSR.2:0   Channel 0/4 slave select */
		u16 ch04_keep_assert:      1;	/* SPI03SSR/SPI47SSR.3     Channel 0/4 slave select keep assert */
		u16 ch15_id:               3;	/* SPI03SSR/SPI47SSR.6:4   Channel 1/5 slave select */	
		u16 ch15_keep_assert:      1;	/* SPI03SSR/SPI47SSR.7     Channel 1/5 slave select keep assert */	
		u16 ch26_id:               3;	/* SPI03SSR/SPI47SSR.10:8  Channel 2/6 slave select */			
		u16 ch26_keep_assert:      1;	/* SPI03SSR/SPI47SSR.11    Channel 2/6 slave select keep assert */			
		u16 ch37_id:               3;	/* SPI03SSR/SPI47SSR.14:12 Channel 3/7 slave select */			
		u16 ch37_keep_assert:      1;	/* SPI03SSR/SPI47SSR.15    Channel 3/7 slave select keep assert */					
	} b;
} SPIxxSS_OBJECT;

  /* SPI01BCR/SPI23BCR/SPI45BCR/SPI67BCR */
typedef union _SPIxxBC_OBJECT
{
	u16 d16;
	struct{
		u16 ch0246_tx_byte_cnt:    3;	/* S01BC/S23BC/S45BC/S67BC.2:0   Channel 0/2/4/6 TX byte count */
		u16 reserved_3:            1;	/* S01BC/S23BC/S45BC/S67BC.3 */
		u16 ch0246_rx_sta_byte:    3;	/* S01BC/S23BC/S45BC/S67BC.6:4   Channel 0/2/4/6 RX start byte count */
		u16 reserved_7:            1;	/* S01BC/S23BC/S45BC/S67BC.7 */		
		u16 ch1357_tx_byte_cnt:    3;	/* S01BC/S23BC/S45BC/S67BC.10:8  Channel 1/3/5/7 TX byte count */
		u16 reserved_11:           1;	/* S01BC/S23BC/S45BC/S67BC.11 */		
		u16 ch1357_rx_sta_byte:    3;	/* S01BC/S23BC/S45BC/S67BC.14:12 Channel 1/3/5/7 RX start byte count */		
		u16 reserved_15:           1;	/* S01BC/S23BC/S45BC/S67BC.15 */				
	} b;
} SPIxxBCR_OBJECT;

  /* SPINTSR */
typedef union _SPINTSR_OBJECT
{
	u16 d16;
	struct{
		u16 all_xfer_completed:      1;	/* SPINTSR.0 */
		u16 interrupt_is_asserted:   1;	/* SPINTSR.1 */
		u16 busy:                    1;	/* SPINTSR.2 */
		u16 slave_select_err :       1;	/* SPINTSR.3 */
		u16 wait_trg_pulse_timeout:  1;	/* SPINTSR.4 */		
		u16 wait_rdy_timeout:        1;	/* SPINTSR.5 */		
		u16 trg_pulse_is_overrun:    1;	/* SPINTSR.6 */		
		u16 rx_buf_is_overrun:       1;	/* SPINTSR.7 */		
		u16 reserved_15_8:           8;
	} b;
} SPINTSR_OBJECT;

  /* SPITSR */
typedef union _SPITSR_OBJECT
{
	u16 d16;
	struct{
		u16 ch0_trg_pulse_timeout:      1;	/* SPITSR.0 */
		u16 ch1_trg_pulse_timeout:      1;	/* SPITSR.1 */
		u16 ch2_trg_pulse_timeout:      1;	/* SPITSR.2 */
		u16 ch3_trg_pulse_timeout:      1;	/* SPITSR.3 */
		u16 ch4_trg_pulse_timeout:      1;	/* SPITSR.4 */
		u16 ch5_trg_pulse_timeout:      1;	/* SPITSR.5 */
		u16 ch6_trg_pulse_timeout:      1;	/* SPITSR.6 */
		u16 ch7_trg_pulse_timeout:      1;	/* SPITSR.7 */
		u16 ch0_rdy_pulse_timeout:      1;	/* SPITSR.8 */
		u16 ch1_rdy_pulse_timeout:      1;	/* SPITSR.9 */
		u16 ch2_rdy_pulse_timeout:      1;	/* SPITSR.10 */
		u16 ch3_rdy_pulse_timeout:      1;	/* SPITSR.11 */
		u16 ch4_rdy_pulse_timeout:      1;	/* SPITSR.12 */
		u16 ch5_rdy_pulse_timeout:      1;	/* SPITSR.13 */
		u16 ch6_rdy_pulse_timeout:      1;	/* SPITSR.14 */
		u16 ch7_rdy_pulse_timeout:      1;	/* SPITSR.15 */
	} b;
} SPITSR_OBJECT;

  /* SPIPOSR */
typedef union _SPIPOSR_OBJECT
{
	u16 d16;
	struct{
		u16 ch0_trg_pulse_overrun:      1;	/* SPIPOSR.0 */
		u16 ch1_trg_pulse_overrun:      1;	/* SPIPOSR.1 */
		u16 ch2_trg_pulse_overrun:      1;	/* SPIPOSR.2 */
		u16 ch3_trg_pulse_overrun:      1;	/* SPIPOSR.3 */
		u16 ch4_trg_pulse_overrun:      1;	/* SPIPOSR.4 */
		u16 ch5_trg_pulse_overrun:      1;	/* SPIPOSR.5 */
		u16 ch6_trg_pulse_overrun:      1;	/* SPIPOSR.6 */
		u16 ch7_trg_pulse_overrun:      1;	/* SPIPOSR.7 */
		u16 reserved_15_8:              8;	/* SPIPOSR.15:8 */
	} b;
} SPIPOSR_OBJECT;

  /* SPIDSR */
typedef union _SPIDSR_OBJECT
{
	u16 d16;
	struct{
		u16 ch0_complete:               1;	/* SPIDSR.0 */
		u16 ch1_complete:               1;	/* SPIDSR.1 */
		u16 ch2_complete:               1;	/* SPIDSR.2 */
		u16 ch3_complete:               1;	/* SPIDSR.3 */
		u16 ch4_complete:               1;	/* SPIDSR.4 */
		u16 ch5_complete:               1;	/* SPIDSR.5 */
		u16 ch6_complete:               1;	/* SPIDSR.6 */
		u16 ch7_complete:               1;	/* SPIDSR.7 */
		u16 ch0_rx_overrun:             1;	/* SPIDSR.8 */
		u16 ch1_rx_overrun:             1;	/* SPIDSR.9 */
		u16 ch2_rx_overrun:             1;	/* SPIDSR.10 */
		u16 ch3_rx_overrun:             1;	/* SPIDSR.11 */
		u16 ch4_rx_overrun:             1;	/* SPIDSR.12 */
		u16 ch5_rx_overrun:             1;	/* SPIDSR.13 */
		u16 ch6_rx_overrun:             1;	/* SPIDSR.14 */
		u16 ch7_rx_overrun:             1;	/* SPIDSR.15 */		
	} b;
} SPIDSR_OBJECT;

typedef union _SPIMCR_OBJECT
{
	u16 d16;
	struct{
		u16 ch0_rx_buf_clr	          :1;	/* SPIMCR.0	Clear RX Channel 0 */
		u16 ch1_rx_buf_clr				    :1;	/* SPIMCR.1	Clear RX Channel 1 */
		u16 ch2_rx_buf_clr				    :1;	/* SPIMCR.2	Clear RX Channel 2 */
		u16 ch3_rx_buf_clr				    :1;	/* SPIMCR.3	Clear RX Channel 3 */
		u16 ch4_rx_buf_clr				    :1;	/* SPIMCR.4	Clear RX Channel 4 */
		u16 ch5_rx_buf_clr				    :1;	/* SPIMCR.5	Clear RX Channel 5 */
		u16 ch6_rx_buf_clr				    :1;	/* SPIMCR.6	Clear RX Channel 6 */
		u16 ch7_rx_buf_clr				    :1;	/* SPIMCR.7	Clear RX Channel 7 */
		u16 go				                :1; /* SPIMCR.8 Start the transfer enable */
		u16 access_channels				    :3;	/* SPIMCR.9:11 Access Channel */
		u16 continue_mode_enable			:1; /* SPIMCR.12 Continuous Access Enable */
		u16 rx_buf_handshake_enable		:1; /* SPIMCR.13 RX Update Setting */
		u16 clr_complete_flag	        :1; /* SPIMCR.14 Clear complete status */
		u16 clr_interrupt_flag		    :1; /* SPIMCR.15 Clear interrupt */
	}b;
}SPIMCR_OBJECT;

/* ------------- Interrupt ------------- */
  /* INTCR */
typedef union _INTCR_OBJECT
{
	u16 d16;
	struct{
		u16 pwm_pulse_a_intr_enable:             1;     /* INTCR.0   PWM pulse A interrupt enable */				
		u16 pwm_pulse_b_intr_enable:             1;     /* INTCR.1   PWM pulse B interrupt enable */
		u16 pwm_cycle_center_intr_enable:        1;     /* INTCR.2   PWM cycle center trigger interrupt enable */		
		u16 pwm_cycle_start_intr_enable:         1;     /* INTCR.3   PWM cycle start trigger interrupt enable */
		u16 step_compl_intr_enable:              1;     /* INTCR.4   Step completed interrupt enable */
		u16 spim_compl_intr_enable:              1;     /* INTCR.5   SPIM completed interrupt enable */
		u16 spim_err_intr_enable:                1;     /* INTCR.6   SPIM error interrupt enable */
		u16 reserved_7:                          1;     /* INTCR.7   */		
		u16 enc_z_assert_intr_enable:            1;     /* INTCR.8   ENC Z assert event interrupt enable */		
		u16 enc_z_deassert_intr_enable:          1;     /* INTCR.9   ENC Z de-assert event interrupt enable */				
		u16 enc_err_intr_enable:                 1;     /* INTCR.10  ENC error interrupt enable */
		u16 iowd_timeout_intr_enable:            1;     /* INTCR.11  I/O Watchdog timeout interrupt enable */
		u16 lb_err_intr_enable:                  1;     /* INTCR.12  Local bus internal error interrupt enable */
		u16 spi_err_intr_enable:                 1;     /* INTCR.13  SPI internal error interrupt enable */
		u16 reserved_14:                         1;     /* INTCR.14 */
		u16 emergency_intr_enable:               1;     /* INTCR.15  Activation of external low active emergency enable */		
	} b;
} INTCR_OBJECT;

  /* INTSR */
typedef union _INTSR_OBJECT
{
	u16 d16;
	struct{
		u16 pwm_pulse_a_intr_stu:                1;     /* INTSR.0   PWM pulse A interrupt status */		
		u16 pwm_pulse_b_intr_stu:                1;     /* INTSR.1   PWM pulse B interrupt status */		
		u16 pwm_cycle_center_intr_stu:           1;     /* INTSR.2   PWM cycle center trigger interrupt status */
		u16 pwm_cycle_start_intr_stu:            1;     /* INTSR.3   PWM cycle start trigger interrupt status */
		u16 step_compl_intr_stu:                 1;     /* INTSR.4   Step completed interrupt status */
		u16 spim_compl_intr_stu:                 1;     /* INTSR.5   SPIM completed interrupt status */
		u16 spim_err_intr_stu:                   1;     /* INTSR.6   SPIM error interrupt status */
		u16 reserved_7:                          1;     /* INTSR.7   */		
		u16 enc_z_assert_intr_stu:               1;     /* INTSR.8   ENC Z assert event interrupt status */		
		u16 enc_z_deassert_intr_stu:             1;     /* INTSR.9   ENC Z de-assert event interrupt status */				
		u16 enc_err_intr_stu:                    1;     /* INTSR.10  ENC error interrupt status */
		u16 iowd_timeout_intr_stu:               1;     /* INTSR.11  I/O Watchdog timeout interrupt status */
		u16 lb_err_intr_stu:                     1;     /* INTSR.12  Local bus internal error interrupt status */
		u16 spi_err_intr_stu:                    1;     /* INTSR.13  SPI internal error interrupt status */
		u16 esc_intr_stu:                        1;     /* INTSR.14  ESC interrupt status */
		u16 emergency_intr_stu:                  1;     /* INTSR.15  Activation of external low active emergency status */		
	} b;
} INTSR_OBJECT;

  /* ESTOR */
typedef union _ESTOR_OBJECT
{
	u16 d16;
	struct{
		u16 motor_ctrl_override:     1;	/* ESTOR.0 Motor control function override */
		u16 spi_master_override:     1;	/* ESTOR.1 SPI Master function override */		
		u16 reserved_6_2:            5;		
		u16 brg_override:            1;	/* ESTOR.7 Bridge function override */				
		u16 reserved_15_8:           8;
	} b;
} ESTOR_OBJECT;

  /* HSTSR */
typedef union _HSTSR_OBJECT
{
	u16 d16;
	struct{
		u16 intl_read_decode_err:    1;	/* HSTSR.0   Internal bus read decode error */
		u16 reserved_1:              1;
		u16 host_read_cmd_err:       1;	/* HSTSR.2   Local bus/SPI read command error */		
		u16 reserved_3:              1;
		u16 intl_write_decode_err:   1;	/* HSTSR.4   Internal bus write decode error */
		u16 intl_write_resp_err:     1;	/* HSTSR.5   Internal bus write slave response error */		
		u16 host_write_cmd_err:      1;	/* HSTSR.6   Local bus/SPI write command error */
		u16 reserved_15_7:           9;
	} b;
} HSTSR_OBJECT;

/* ------------- Access Control ------------- */
  /* Access control registers */
typedef union _ACCESSCTRL_OBJECT
{
	u8 d8;
	struct{
		u8 data_sync_trg_type:       4;	/* ACCESSCTRL.3:0 Data sync. trigger type */
		u8 is_writable_with_esc:     1;	/* ACCESSCTRL.4   Enable ESC writable */
		u8 reserved_7_5:             3;
	} b;
} ACCESSCTRL_OBJECT;

  /* FMIRER */
typedef union _FMIRER
{
	u8 d8;
	struct{
		u8 pwm_func_mirror:          1;	/* FMIRER.0   PWM function mirror */
		u8 enc_func_mirror:          1;	/* FMIRER.1   ENC function mirror */
		u8 spim_func_mirror:         1;	/* FMIRER.2   SPIM function mirror */
		u8 iowd_func_mirror:         1;	/* FMIRER.3   IOWD function mirror */		
		u8 reserved_7_4:             4;	/* FMIRER.7:4 */		
	} b;
} FMIRER_OBJECT;

/* ------------- PHY Registers ------------- */
typedef union _PHYPR_OBJECT
{
	u16 d16;
	struct{
		u16 phy0_tx_amp_fine_tune:   3;	/* PHYPR.2:0 P0TXTUN */
		u16 phy0_tx_amp_coarse_tune: 2;	/* PHYPR.4:3 P0TXTUN */		
		u16 phy1_tx_amp_fine_tune:   3;	/* PHYPR.7:5 P1TXTUN */
		u16 phy1_tx_amp_coarse_tune: 2;	/* PHYPR.9:8 P1TXTUN */		
		u16 reserved_11_10:          2;
		u16 phy_selec:               2;	/* PHYPR.13:12 PHY select: 00=use MII regoster, 01=use entry0, 1x=use entry1 */
		u16 reserved_15_14:          2;		
	} b;
} PHYPR_OBJECT;

typedef union _MINFR_OBJECT
{
	u8 Byte[6];
	struct{
		struct{
			u8 x_locate:               7;	/* MINFR.6:0  */
			u8 y_locate_0:             1;	/* MINFR.7  */
		}Byte0;
		struct{
			u8 y_locate_7_1:           6;	/* MINFR.13:8  */
			u8 wafer_id_1_0:           2;	/* MINFR.15:14 */			
		}Byte1;
		struct{
			u8 wafer_id_4_2:           3;	/* MINFR.18:16 */			
			u8 lot_id_4_0:             5;	/* MINFR.23:19 */						
		}Byte2;		
		struct{
			u8 lot_id_12_5:            8;	/* MINFR.31:24 */
		}Byte3;
		struct{
			u8 lot_id_20_13:           8;	/* MINFR.39:32 */
		}Byte4;
		struct{
			u8 lot_id_22_21:           2;	/* MINFR.41:40 */
			u8 resrved_47_42:          6;	/* MINFR.47:42 */			
		}Byte5;		
	} b;
} MINFR_OBJECT;

typedef union _ECTRLR_OBJECT
{
	u16 d16;
	struct{
		u16 efuse_bit_addr:         3;	/* ECTRLR.2:0  */
		u16 efuse_byte_addr:        3;	/* ECTRLR.5:3  */
		u16 efuse_cmd:              2;	/* ECTRLR.7:6 */
		u16 reserved_15_8:          8;	/* ECTRLR.15:8 */		
	} b;
} ECTRLR_OBJECT;

/* ------------- eFuse Memory Map ------------- */
typedef union _eFUSE_MAP_OBJECT
{
	u8 Bytes[8];
	struct{
  	struct{
	   u8 entry0_phy0_tx_amp_fine_tune:         3;	/* Byte0.2:0  */
		 u8 entry0_phy0_tx_amp_coarse_tune:       2;	/* Byte0.4:3  */
		 u8 entry0_phy1_tx_amp_fine_tune:         3;	/* Byte0.7:5 */
	  }Byte0;
	  struct{
		 u8 entry0_phy1_tx_amp_coarse_tune:       2;	/* Byte1.1:0  */
		 u8 entry1_phy0_tx_amp_fine_tune:         3;	/* Byte1.4:2  */
		 u8 entry1_phy0_tx_amp_coarse_tune:       2;	/* Byte1.6:5 */
		 u8 entry1_phy1_tx_amp_fine_tune_0:       1;	/* Byte1.7 */		
	  }Byte1;
	  struct{
	   u8 entry1_phy1_tx_amp_fine_tune_2_1:       2;	/* Byte2.1:0  */
	   u8 entry1_phy1_tx_amp_coarse_tune:         2;	/* Byte2.3:2  */
	   u8 phy_select:                             2;	/* Byte2.5:4 */
	   u8 lot_id_22_21:                           2;	/* Byte2.7:6 */		
	  }Byte2;	
	  struct{
		 u8 lot_id_20_13:                         8;	/* Byte3.7:0  */
	  }Byte3;		
	  struct{	
		 u8 lot_id_12_5:                          8;	/* Byte4.7:0  */		
	  }Byte4;		
	  struct{	
		 u8 wafer_id_4_2:                         3;	/* Byte5.2:0  */				
		 u8 lot_id_4_0:                           5;	/* Byte5.7:3  */		
	  }Byte5;			
	  struct{	
		 u8 y_locate_6_1:                         6;	/* Byte6.5:0  */				
		 u8 wafer_id_1_0:                         2;	/* Byte6.7:6  */		
	  }Byte6;				
	  struct{	
		 u8 x_locate:                             7;	/* Byte7.6:0  */						
		 u8 y_locate_0:                           1;	/* Byte7.7  */				
	  }Byte7;					
	}b;
} eFUSE_MAP_OBJECT;

/* TYPE DECLARATIONS */
typedef struct _MC_REGS
{
  u16 mctlr;
  u16 pxcfgr;
  u16 ptappr;
  u16 ptbppr;
  u16 ppcr;
  u16 pbbmr;
  u16 p1ctrlr;
  u16 p1shr;
  u16 p1hpwr;
  u16 p2ctrlr;
  u16 p2shr;
  u16 p2hpwr;
  u16 p3ctrlr;
  u16 p3shr;
  u16 p3hpwr;
	u16 reserved_1F_1E;
  u16 sgtlr;
  u16 sgthr;
  u16 shpwr;
  u16 tdlyr;
  u16 stnlr;
  u16 stnhr;
  u16 scfgr;
  u16 sctrlr;
  u16 scntlr;
  u16 scnthr;	
} MC_REGS;

typedef struct _ENC_REGS
{
  u16 ecntvl;
  u16 ecntvh;
  u16 ecnstl;
  u16 ecnsth;
  u16 elatl;
  u16 elath;
  u16 emod;
  u16 eclr;
  u16 hallst;
} ENC_REGS;

typedef struct _IOWD_REGS
{
  u16 wtlr;
  u16 wthr;
  u16 wcfgr;
  u16 wtpvcr;
  u16 wmsplr;
  u16 wmsphr;
  u16 wmsmlr;
  u16 wmsmhr;
  u16 wmsomlr;
  u16 wmsomhr;
  u16 wmsoelr;
  u16 wmsoehr;
  u16 wmsoplr;
  u16 wmsophr;
  u16 wtpvlr;
  u16 wtpvhr;
} IOWD_REGS;

typedef struct _SPIM_REGS
{
  u16 spicfgr;
  u16 spibrr;
  u16 spidbsr;
  u16 spidtr;
  u16 spirptr;
  u16 spiltr;	
  u16 spiprlr;
  u16 reserved_8F_8E;
  u16 spi01bcr;
  u16 spi23bcr;
  u16 spi45bcr;
  u16 spi67bcr;
  u16 spi03ssr;
  u16 spi47ssr;
  u16 reserved_9C_A7[0x6];
  u16 spintsr;	
  u16 spitsr;		
  u16 spiposr;
  u16 spidsr;	
  u8  spic0dr[0x08];
  u8  spic1dr[0x08];	
  u8  spic2dr[0x08];	
  u8  spic3dr[0x08];	
  u8  spic4dr[0x08];	
  u8  spic5dr[0x08];	
  u8  spic6dr[0x08];
  u8  spic7dr[0x08];
  u16 spidsmr;
  u16 spimcr;
} SPIM_REGS;

typedef struct _FUN_SIDE_MISC_REGS
{
  u16 intcr;
  u16 intsr;
  u16 estor;
  u16 hstsr;
  u16 phypr;
  u16 minfr[3];	
  u16 ectrlr;	
  u16 erdr;	
} FUN_SIDE_MISC_REGS;

/* GLOBAL VARIABLES */

/* EXPORTED SUBPROGRAM SPECIFICATIONS */

#endif /* __AX58100_REGOBJS_H__ */

/* End of ax58100_regobjs.h */
