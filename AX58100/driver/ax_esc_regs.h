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
#ifndef __ESC_REGS_H__
#define __ESC_REGS_H__

/* INCLUDE FILE DECLARATIONS */
#include "ax_types.h"


/* NAMING CONSTANT DECLARATIONS */


/* ====================== Register Bit Definition ====================== */

/* ------------- Features ------------- */
#define ESC_CORE_TYPE               0x0000  /* Type register */
#define ESC_CORE_MAJOR_REV_X        0x0001	/* Revision register */
#define ESC_CORE_BUILD              0x0002	/* Build register */
typedef union
{
  u16 d16;
  struct{
    u8 maintenance_ver_z:       4;  /* Bit0:3    Maintenance version Z */
    u8 minor_ver_y:             4;  /* Bit7:4    Minor version Y */	
    u8 patch_level:             8;  /* Bit15:8   Patch level/development build */			
  } b;
} oESC_CORE_BUILD;
#define FMMUS_SUPPORTED             0x0004
#define SYNC_MANAGERS_SUPPORTED     0x0005
#define RAM_SIZE                    0x0006
#define PORT_DESCRIPTOR             0x0007
typedef union
{
  u8 d8;
  struct{
    u8 port0_config:            2;  /* 00: Not implemented, 01: Not configured, 10: EBUS, 11: MII/RMII/RGMII */
    u8 port1_config:            2;
    u8 port2_config:            2;		
    u8 port3_config:            2;		
  } b;
} oPORT_DESCRIPTOR;
#define ESC_FEATURES_SUPPORTED      0x0008
typedef union
{
  u16 d16;
  struct{
    u16 fmmu_operation:             1;  /* Bit0   0: Bit oriented, 1: Byte oriented */
    u16 unused_register_access:     1;  /* Bit1   0: Allowed, 1: Not supported */
    u16 distributed_clocks:         1;  /* Bit2   0: Not available, 1: Available */		
    u16 dc_width:                   1;  /* Bit3   0: 32bit, 1: 64bit */
    u16 reserved_5_4:               2;  /* Bit5:4 */
    u16 enhanced_link_detec_mii:    1;  /* Bit6   0: Not available, 1: Available */
    u16 separate_handle_of_fcs_err: 1;  /* Bit7   0: Not supported, 1: Supported */
    u16 enhanced_dc_sync_act:       1;  /* Bit8   0: Not available, 1: Available */		
    u16 lrw_command_support:        1;  /* Bit9   0: Supported, 1: Not supported */
    u16 read_write_cmd_support:     1;  /* Bit10  0: Supported, 1: Not supported */		
    u16 fixed_fmmu_sm_config:       1;  /* Bit11  0: Variable configuration, 1: Fixed configuration */				
    u16 reserved_15_12:             4;
  } b;
} oESC_FEATURES_SUPPORTED;
#define CONFIG_STATION_ADDR         0x0010
#define CONFIG_STATION_ALIAS        0x0012
#define REG_WRITE_ENABLE            0x0020
typedef union
{
  u8 d8;
  struct{
    u8 reg_write_enable:            1;  /* Bit0   0: Register write is enabled, 1: Register write is disabled */
    u8 reserved_7_1:                7;
  } b;
} oREG_WRITE_ENABLE;
#define REG_WRITE_PROTECTION        0x0021
typedef union
{
  u8 d8;
  struct{
    u8 reg_write_protect:           1;  /* Bit0   Register 0x0000:0x0F7F(except for 0x0020 and 0x0030) write protection is 0: disabled, 1: enabled */
    u8 reserved_7_1:                7;		
  } b;
} oREG_WRITE_PROTECTION;
#define ESC_WRITE_ENABLE            0x0030
typedef union
{
  u8 d8;
  struct{
    u8 esc_write_enable:            1;  /* Bit0   All areas write protection is 0: enabled, 1: Register write is disabled */
    u8 reserved_7_1:                7;		
  } b;
} oESC_WRITE_ENABLE;
#define ESC_WRITE_PROTECTION        0x0031
typedef union
{
  u8 d8;
  struct{
    u8 esc_write_protect:           1;  /* Bit0   All areas (except for 0x0030) write protection is 0: disabled, 1: enabled */
    u8 reserved_7_1:                7;		
  } b;
} oESC_WRITE_PROTECTION;

/* ------------- Application Layer ------------- */
#define AL_CONTROL                  0x0120
typedef union
{
  u16 d16;
  struct{
    u16 initiate_state:                  4;  /* Bit3:0    1:Request Init State
                                                          3:Request Bootstrap State
                                                          2:Request Pre-Operational State		
                                                          4:Request Safe-Operational State		
                                                          8:Request Operational State		
                                             */
    u16 err_ind_ack:                     1;  /* Bit4 0:No ack of error ind in AL status, 1:Ack of error ind in AL status */
    u16 device_identification:           1;  /* Bit5 0:No request, 1:Request  */
    u16 reserved_15_6:                  10;  /* Bit15:6 */
  } b;
} oAL_CONTROL;
#define AL_STATUS                   0x0130
typedef union
{
  u16 d16;
  struct{
    u16 actual_state:                    4;  /* Bit3:0    1:Init State
                                                          3:Bootstrap State
                                                          2:Pre-Operational State		
                                                          4:Safe-Operational State		
                                                          8:Operational State		
                                             */
    u16 err_ind:                         1;  /* Bit4 0:Device is in state as requested, 1:Device has not entered requested state */
    u16 device_identification:           1;  /* Bit5 0:Device indentification not valid, 1:Device indentification loaded */
    u16 reserved_15_6:                  10;  /* Bit15:6 */
  } b;
} oAL_STATUS;
#define AL_STATUS_CODE              0x0134
#define PDI_CONTROL                 0x0140
#define ESC_CONFIG                  0x0141 /*  ESC Configuration Register (0x0141) */
typedef union
{
  u8 d8;
  struct{
    u8 device_emulation:                 1;  /* Bit0 0:AL status has to be set by PDI, 1: */
    u8 enhanced_link_detec_all_port:     1;  /* Bit1 0:disable, 1:enable */
    u8 distributed_clk_sync_out_unit:    1;  /* Bit2 0:disable(power saving), 1:enable */
    u8 distributed_clk_latch_in_unit:    1;  /* Bit3 0:disable(power saving), 1:enable */
    u8 enhanced_link_port0:              1;  /* Bit4 0:disable, 1:enable  */
    u8 enhanced_link_port1:              1;  /* Bit5 0:disable, 1:enable  */
    u8 enhanced_link_port2:              1;  /* Bit6 0:disable, 1:enable  */
    u8 enhanced_link_port3:              1;  /* Bit7 0:disable, 1:enable */
  } b;
} oESC_CONFIG;

#define PDI_CONFIG                       0x0150 /*  PDI Configuration Register (0x0150:0x0153) */
typedef union
{
  u32 d32;

		/* PDI General Terms */
  struct{
		u32 pdi_cfg_7_0:             8;  /* Bit7:0 */
		u32 sync0_driver_pol:        2;  /* Bit9:8    00b: Push-Pull/Active Low
		                                              01b: Open-Drain/Active Low 
		                                              10b: Push-Pull/Active High
		                                              11b: Open-Source/Active High
		                                 */
		u32 sync0_latch0_cfg:        1;  /* Bit10     0b: Latch0 Input
		                                              1b: Sync0 Output
		                                 */
		u32 sync0_map_al_event:      1;  /* Bit11     0b: Disable
		                                              1b: Enable
		                                 */
		
		u32 sync1_driver_pol:        2;  /* Bit13:12  00b: Push-Pull/Active Low
		                                              01b: Open-Drain/Active Low 
		                                              10b: Push-Pull/Active High
		                                              11b: Open-Source/Active High
		                                 */
		u32 sync1_latch1_cfg:        1;  /* Bit14     0b: Latch1 Input
		                                              1b: Sync1 Output
		                                 */
		u32 sync1_map_al_event:      1;  /* Bit15     0b: Disable
		                                              1b: Enable
		                                 */		
		u32 pdi_cfg_31_16:          16;  /* Bit31:16 */
  } bGeneralTerm;

	/* PDI Digital I/O Configuration */
  struct{
    u32 output_valid_pol:        1;  /* Bit0      OUTVALID polarity, 0: Active high, 1: Active low */
    u32 output_valid_mode:       1;  /* Bit1      OUTVALID mode, 0: Output event signaling, 1: Process data watchdog trigger */
    u32 unidir_bidir_mode:       1;  /* Bit2     */
    u32 watchdog_behavior:       1;  /* Bit3     */	
    u32 input_sample_at:         2;  /* Bit5:4   */	
    u32 output_update_at:        2;  /* Bit7:6   */
    u32 general_term_15_8:       8;  /* Bit15:8  */	
    u32 io_dir:                 16;  /* Bit31:16 */
  } bDIO;
	
	/* PDI SPI Slave Configuration */
  struct{
    u32 spi_mode:                2;  /* Bit1:0    00b: Mode0
                                                  01b: Mode1
                                                  10b: Mode2
                                                  11b: Mode3 
		                                 */
    u32 spi_irq_driver_pol:      2;  /* Bit3:2    00b: Push-Pull/Active Low 
                                                  01b: Open-Drain/Active Low
                                                  10b: Push-Pull/Active High
                                                  11b: Open-Source/Active High
		                                 */
    u32 spi_sel_pol:             1;  /* Bit4      0b:  Active Low
                                                  1b:  Active High
                                     */
    u32 data_out_sampl_mode:     1;  /* Bit5      0b:  Normal sample
                                                  1b:  Late sample
                                     */	
    u32 reserved_7_6:            2;  /* Bit7:6   */
    u32 general_term_15_8:       8;  /* Bit15:8  */
    u32 io_dir:                 16;  /* Bit31:16 */
  } bSPIS;
	
} oPDI_CONFIG;

#define ECAT_EVENT_MASK           0x0200 /* ECAT Event Mask (0x0200:0x0201) */
#define PDI_AL_EVENT_MASK         0x0204 /* PDI AL Event Mask (0x0204:0x0207) */
#define ECAT_EVENT_REQUEST        0x0210 /* ECAT Event Request (0x0210:0x0211) */
#define AL_EVENT_REQUEST          0x0220 /* AL Event Request (0x0220:0x0223) */
typedef union
{
  u16 d16;
  struct{
    u16 dc_latch_event:                 1;  /* Bit0 0: No change on DC latch input, 1: At least one change on DC latch input */
    u16 reserved_1:                     1;  /* Bit1 */
    u16 dc_status_event:                1;  /* Bit2 0: No change in DL status, 1: DL status change */
    u16 al_status_event:                1;  /* Bit3 0: No change in AL status, 1: AL status change */
    u16 sync_0_7_manager_status:        8;  /* Bit11:4 0: No Sync channel 0 event, 1: Sync channel 0 event pending */
		u16 reserved_15_12:                 4;
  } b;
} oECAT_EVENT;

typedef union
{
  u32 d32;
  struct{
    u32 al_control_event:               1;  /* Bit0 0: No AL control register change, 1: AL control register has been written */
    u32 dc_latch_event:                 1;  /* Bit1 */
    u32 state_of_dc_sync_0:             1;  /* Bit2 */
    u32 state_of_dc_sync_1:             1;  /* Bit3 */
    u32 sm_activation:                  1;  /* Bit4 0: No change in any SyncManager, 1: At least one SyncManager changed */
    u32 eep_emulation:                  1;  /* Bit5 0: No command pending, 1: EEPROM command pending */		
    u32 watchdog_process_data:          1;  /* Bit6 0: Has not expired, 1: Has expired */				
    u32 sm_0_15_interrupts:            16;  /* Bit23:7 0: No SyncManager[x] interrupt, 1: SyncManager[x] interrupt pending */				
    u32 reserved_32_24:                15;  /* Bit32:24 */						
  } b;
} oAL_EVENT;
#define PDI_ERR_COUNTER           0x030D /* PDI Error Counter (0x030D) */
#define PDI_ERR_CODE              0x030E /* PDI Error Code (0x030E) */
typedef union
{
  u8 d8;
  struct{
		u8 spi_clk_num_of_access:           3;  /* Bit2:0 */
		u8 busy_violation_during_read:      1;  /* Bit3 */
		u8 read_termination_missing:        1;  /* Bit4 */		
		u8 access_continue_after_read:      1;  /* Bit5 */
		u8 cmd_err:                         2;  /* Bit7:6 */		
  } bSPI;
	
  struct{
		u8 busy_viola_during_read:          1;  /* Bit0 */
		u8 busy_viola_during_write:         1;  /* Bit1 */		
		u8 addr_err_for_read:               1;  /* Bit2 */
		u8 addr_err_for_write:              1;  /* Bit3 */		
		u8 reserved_7_4:                    4;  /* Bit7:4 */		
  } bASYNC_SYNC;	
} oPDI_ERR_CODE;
#define LOST_LINK_COUNTER         0x0310 /* Lost link counter (0x0310:0x313) */

/* ------------- Watchdog ------------- */
#define WD_DIVIDER                0x0400 /* Watchdog Divider (0x0400:0x0401) */
#define WD_TIME_PDI               0x0410 /* Watchdog Time PDI (0x0410:0x0411) */
#define WD_TIME_PROCESS_DATA      0x0420 /* Watchdog Time Process Data (0x0420:0x0421) */
#define WD_STATUS_PROCESS_DATA    0x0440 /* Watchdog Status Process Data (0x0440:0x0441) */
typedef union
{
  u16 d16;
  struct{
        u16 wd_process_data_status:         1;  /* Bit0 0: Watchdog process data expired, 1: Watchdog process data is active or disable */				
        u16 reserved_15_1:                 15;  /* Bit15:1 */						
  } b;
} oWD_STATUS_PROCESS_DATA;
#define WD_COUNTER_PROCESS_DATA   0x0442 /* Watchdog Counter Process Data (0x0442) */
#define WD_COUNTER_PDI            0x0443 /* Watchdog Counter PDI (0x0442) */

/* ------------- SII EEPROM Interface ------------- */
#define EEPCFGR                   0x0500
#define EEPPASR                   0x0501
#define EEPCSR                    0x0502
#define EEPAR                     0x0504
#define EEPDR                     0x0508

	/* EEPROM Configuration Register (0x0500) */
typedef union
{
  u8 d8;
  struct{
    u8 eep_offered_to_pdi:      1;  /* EEPCFGR.0      0: No, 1: Yes */
    u8 force_ecat_access:       1;  /* EEPCFGR.1      0: Do not change bit 0x0501[0], 1: Reset bit 0x0501[0] to 0 */	
		u8 reserved_7_2:            6;
  } b;
} oEEPCFGR;

	/* EEPROM PDI Access State Register (0x0501) */
typedef union
{
  u8 d8;
  struct{
    u8 pdi_access_to_eep:       1;  /* EEPPASR.0      0: PDI release EEPROM access, 1: PDI takes EEPROM access */
		u8 reserved_7_1:            7;
  } b;
} oEEPPASR;

/* EEPROM Control/Status Register (0x0502:0x503) */
#define EEPCSR_CMD_IDLE           0x00
#define EEPCSR_CMD_READ           0x01
#define EEPCSR_CMD_WRITE          0x02
#define EEPCSR_CMD_RELOAD         0x04
typedef union
{
  u16 d16;
  struct{
    u16 write_enable:            1;  /* EEPCSR.0      0: Write disabled, 1: Write enabled */
    u16 reserved_4_1:            4;  /* EEPCSR.4:1 */		
    u16 eep_emulation:           1;  /* EEPCSR.5      0: Normal operation, 1: PDI emulates EEPROM */			
    u16 read_8bytes:             1;  /* EEPCSR.6      0: 4 bytes, 1: 8 bytes */					
    u16 two_addr_bytes:          1;  /* EEPCSR.7      0: 1 address byte(1Kbit~16Kbit), 1: 2 address bytes(32Kbit~4Mbit) */							
    u16 cmd:                     3;  /* EEPCSR.10:8   000: No command, 001: Read, 010:Write, 100:Reload */									
    u16 checksum_err:            1;  /* EEPCSR.11     0: Checksum ok, 1: checksum error */									
    u16 eep_loading_status:      1;  /* EEPCSR.12     0: Device information ok, 1: Device information not available */
    u16 err_ack_cmd:             1;  /* EEPCSR.13     0: No error, 1: Missing ACK or command error */		
    u16 err_write_enable:        1;  /* EEPCSR.14     0: No error, 1: Write command without write enable */				
    u16 eep_intf_busy:           1;  /* EEPCSR.15     0: Idle, 1: Busy */						
  } b;
} oEEPCSR;

typedef struct
{
  oEEPCFGR   eepcfgr;	
  oEEPPASR   eeppasr;		
  oEEPCSR    eepcsr;
	u32        eepar;
	u8         eepdr[8];	
} EEP_REGS;

/* ------------- MII Management Interface ------------- */
#define MMCSR                    0x0510
#define PAR                      0x0512
#define PRAR                     0x0513
#define PDR                      0x0514
#define MMEASR                   0x0516
#define MMPASR                   0x0517
#define PPSR                     0x0518

	/* MII Management Control/Status Register (0x0510:0x0511) */
typedef union
{
  u16 d16;
  struct{
    u16 write_enable:            1;  /* MMCSR.0      0: Write disabled, 1: Write enabled */
    u16 pdi_ctrl_possible:       1;  /* MMCSR.1      0: Only ECAT control, 1: PDI control possible */		
    u16 link_detec_enable:       1;  /* MMCSR.2      MI link detection and configuration */		
    u16 port0_phy_addr:          5;  /* MMCSR.7:3    PHY address for port 0 */
    u16 cmd:                     2;  /* MMCSR.9:8    Command */		
    u16 reseverd_12_10:          3;  /* MMCSR.12:10 */
    u16 read_err:                1;  /* MMCSR.13     Read error */
    u16 cmd_err:                 1;  /* MMCSR.14     Command error */
    u16 busy:                    1;  /* MMCSR.15     Busy */		
  } b;
} oMMCSR;

#define MMCSR_CMD_IDLE           0x00
#define MMCSR_CMD_READ           0x01
#define MMCSR_CMD_WRITE          0x02

  /* PHY Address Register (0x0512) */
typedef union
{
  u8 d8;
  struct{
    u8  phy_addr:                5;  /* PAR.4:0   PHY Address */
    u8  reserved_6_5:            2;  /* PAR.6:5 */
    u8  show_phy_addr:           1;  /* PAR.7     Show configured PHY address of port0-3 */	
  } b;
} oPAR;

  /* PHY Register Address Register (0x0513) */
typedef union
{
  u8 d8;
  struct{
    u8  phy_reg_addr:            5;  /* PRAR.4:0   Address of PHY Register that shall be read/written */
    u8  reserved_7_5:            3;  /* PRAR.7:5 */		
  } b;
} oPRAR;

	/* PHY Data Register (0x0514:0x0515) */
typedef union
{
  u16 d16;
  struct{
    u16 rw_data:                 16;  /* PDR.15:0   PHY Read/Write Data */
  } b;
} oPDR;

  /* MII Management ECAT Acces State (0x0516) */
typedef union
{
  u8 d8;
  struct{
    u8 exclusive_access_mii:      1;  /* MMEASR.0   Access to MII management */
    u8 reserved_7_1:              7;  /* MMEASR.7:1 */		
  } b;
} oMMEASR;

  /* MII Management PDI Access State (0x0517) */
typedef union
{
  u8 d8;
  struct{
    u8 pdi_access_mii:            1;  /* MMPASR.0    Access to MII management */
    u8 ecat_force_pdi_access:     1;  /* MMPASR.1    ECAT Force PDI Access State */
    u8 reserved_7_2:              6;  /* MMPASR.7:2 */
  } b;
} oMMPASR;

/* PHY Port(x) Status Register (0x0518:0x051B) */
typedef union
{
  u8 d8;
  struct{
    u8 phy_link_detected:         1;  /* PPSR.0   Phsical link status */
    u8 link_detected:             1;  /* PPSR.1   Link status */		
    u8 link_error:                1;  /* PPSR.2   Link status error */				
    u8 read_error:                1;  /* PPSR.3   Read error */						
    u8 link_partner_error:        1;  /* PPSR.4   Link partner error */								
    u8 phy_config_updated:        1;  /* PPSR.5   PHY configuration updated */										
    u8 reserved_7_6:              2;  /* PPSR.7:6 */												
  } b;
} oPPSR;

typedef struct
{
  oMMCSR    mmcsr;
  oPAR      par;
  oPRAR     prar;
  oPDR      pdr;	
  oMMEASR   mmeasr;	
  oMMPASR   mmpasr;		
  oPPSR     ppsr[4];			
} MII_REGS;

/* ------------- FMMU ------------- */
#define FMMU_0_LOGIC_START_ADDR   0x0600 /* FMMU[x] Logical Start Address (0x0600:0x0603) */
#define FMMU_0_LENGTH             0x0604 /* FMMU[x] Length (0x0604:0x0605) */
#define FMMU_0_LOGIC_START_BIT    0x0606 /* FMMU[x] Logical Start bit (0x0606) */
#define FMMU_0_LOGIC_STOP_BIT     0x0607 /* FMMU[x] Logical Stop bit (0x0607) */
typedef union
{
  u8 d8;
  struct{
		u8 logical_bit:                    3;  /* Bit2:0 */				
		u8 reserved_7_3:                   5;  /* Bit7:3 */						
  } b;
} oFMMU_LOGIC_START_STOP_BIT;
#define FMMU_0_PHY_START_ADDR     0x0608 /* FMMU[x] Physical Start Address (0x0608:0x0609) */
#define FMMU_0_PHY_START_BIT      0x060A /* FMMU[x] Physical Start bit (0x060A) */
#define FMMU_0_TYPE               0x060B /* FMMU[x] Type (0x060B) */
#define FMMU_0_ACTIVATE           0x060C /* FMMU[x] Activate (0x060C) */
#define FMMU_OFFSET               0x0010

/* ------------- SyncManagers ------------- */
#define SM_0_PHY_START_ADDR       0x0800 /* SM[x] Physical Start Address (0x0800:0x0801) */
#define SM_0_LENGTH               0x0802 /* SM[x] Length (0x0802:0x0803) */
#define SM_0_CONTROL              0x0804 /* SM[x] Control Register (0x0804) */
typedef union
{
  u8 d8;
  struct{
		u8 operation_mode:                 2;  /* Bit1:0  00: 3 buffer mode, 01: reserved, 10: Mailbox, 11: reserved */				
		u8 direction:                      2;  /* Bit3:2  00: ECAT read, PDI write 01: ECAT write, PDI read 10: reserved 11: reserved */
		u8 intr_in_ecat_event_request:     1;  /* Bit4 */		
		u8 intr_in_al_event_request:       1;  /* Bit5 */				
		u8 watchdog_trigger_enable:        1;  /* Bit6 */						
		u8 reserved_7:                     1;  /* Bit7 */								
  } b;
} oSM_CONTROL;
#define SM_0_STATUS               0x0805 /* SM[x] Status Register (0x0805) */
typedef union
{
  u8 d8;
  struct{
		u8 intr_write:                     1;  /* Bit0    0: After first byte of buffer was read, 1: After buffer was completely write */				
		u8 intr_read:                      1;  /* Bit1    0: After first byte of buffer was written, 1: After buffer was completely read */
		u8 reserved_2:                     1;  /* Bit2 */		
		u8 mailbox_status:                 1;  /* Bit3    0: Mailbox empty, 1: Mailbox full */				
		u8 three_buf_status:               2;  /* Bit5:4  00: 1st buffer, 01: 2nd buffer, 10: 3rd buffer, 11: no buffer written */						
		u8 read_buf_in_use:                1;  /* Bit6 */								
		u8 write_buf_in_use:               1;  /* Bit7 */										
  } b;
} oSM_STATUS;
#define SM_0_ACTIVATE             0x0806 /* SM[x] Activate (0x0806) */
typedef union
{
  u8 d8;
  struct{
		u8 sm_enable:                      1;  /* Bit0    0: SM disable, 1: SM enable */				
		u8 repeat_request:                 1;  /* Bit1 */
		u8 reserved_5_2:                   4;  /* Bit5:2 */		
		u8 latch_event_ecat:               1;  /* Bit6    0: No, 1: Generate latch event when EtherCAT master issue a buffer exchange */				
		u8 latch_event_pdi:                1;  /* Bit7    0: No, 1: Generate latch events when PDI issues a buffer change or when PDI access buffer start address */						
  } b;
} oSM_ACTIVATE;
#define SM_0_PDI_CONTROL          0x0807 /* SM[x] PDI Control (0x0807) */
typedef union
{
  u8 d8;
  struct{
		u8 deactivate_sm:                  1;  /* Bit0 */				
		u8 repeat_ack:                     1;  /* Bit1 */
		u8 reserved_7_2:                   4;  /* Bit7:2 */		
  } b;
} oSM_PDI_CONTROL;
#define SM_OFFSET                 0x0010

/* ------------- DC Module ------------- */
#define DC_PORT0_RECV_TIME        0x0900 /* Receive Time Port 0 (0x0900:0x0903) */
#define DC_PORT1_RECV_TIME        0x0904 /* Receive Time Port 1 (0x0904:0x0907) */
#define DC_PORT2_RECV_TIME        0x0908 /* Receive Time Port 2 (0x0908:0x090B) */
#define DC_PORT3_RECV_TIME        0x090F /* Receive Time Port 3 (0x090C:0x090F) */
typedef union
{
  u32 d32;
  struct{
		u32 local_time7_0_at_wr_reg_0x900:  8;  /* Bit7:0 */				
		u32 local_time24_8_at_wr_reg_0x900: 24; /* Bit31:8 */
  } b;
} oDC_PORT0_RECV_TIME;

#define DC_PROC_UNIT_RECV_TIME    0x0918 /* Receive Time ECAT Processing Unit (0x0918:0x091F) */
#define DC_SYSTEM_TIME            0x0910 /* System Time (0x0910:0x0917) */
typedef union
{
  u32 d32[2];
  struct{
		u32 value_compare_with_systim:    32; /* Bit31:0 */				
		u32 local_copy_of_systim:         32; /* Bit63:32 */
  } b;
} oDC_SYSTEM_TIME;

#define DC_SYSTEM_TIME_OFFSET     0x0920 /* System Time Offset (0x0920:0x0927) */
#define DC_SYSTEM_TIME_DELAY      0x0928 /* System Time Delay (0x0928:0x092B) */
#define DC_SYSTEM_TIME_DIFF       0x092C /* System Time Difference (0x092C:0x092F) */
typedef union
{
  s32 d32;
  struct{
		u32 diff_rev_systim_loc_copy_systim: 31; /* Bit30:0 */				
		u32 loc_copy_systim_LorE_rev_systim: 1; /* Bit32 */
  } b;
} oDC_SYSTEM_TIME_DIFF;

#define DC_SPEED_COUNTER_START           0x0930 /* Speed Counter Start (0x0930:0x0931) */
typedef union
{
  u16 d16;
  struct{
		u16 bw_for_adj_of_loc_copy_of_systim: 15; /* Bit14:0 */				
		u16 reserved_15:                       1; /* Bit15 */
  } b;
} oDC_SPEED_COUNTER_START;

#define DC_SPEED_COUNTER_DIFF            0x0932 /* Speed Counter Diff (0x0932:0x0933) */
#define DC_SYSTIME_DIFF_FILTER_DEPTH     0x0934 /* System Time Diff Filter Depth (0x0934) */
typedef union
{
  u8 d8;
  struct{
		u8 filt_depth_for_avg_rev_systim_deva: 4; /* Bit3:0 */				
		u8 reserved_7_4:                       4; /* Bit7:4 */
  } b;
} oDC_SYSTIME_DIFF_FILTER_DEPTH;

#define DC_SPEED_COUNTER_FILTER_DEPTH     0x0935 /* Speed Counter Filter Depth (0x0935) */
typedef union
{
  u8 d8;
  struct{
		u8 filt_depth_for_avg_clk_period_deva: 4; /* Bit3:0 */				
		u8 reserved_7_4:                       4; /* Bit7:4 */
  } b;
} oDC_SPEED_COUNTER_FILTER_DEPTH;

#define DC_REV_TIME_LATCH_MODE            0x0936 /* Receive Time Latch Mode (0x0936) */
typedef union
{
  u8 d8;
  struct{
		u8 rev_time_latch_mode:                1; /* Bit0
		                                             0: Forwarding mode, used if frame are entering ESC at port 0 first.
		                                             1: Reverse mode, used if frame are entering ESC at port 1-3 first.
		                                           */				
		u8 reserved_7_1:                       7; /* Bit7:1 */
  } b;
} oDC_REV_TIME_LATCH_MODE;

#define DC_CYCLIC_UNIT_CTRL               0x0980 /* Cyclic Unit Control (0x0980) */
typedef union
{
  u8 d8;
  struct{
		u8 sync_out_unit_ctrl:                 1; /* Bit0 0: ECAT controlled, 1: PDI controlled */
		u8 reserved_3_1:                       3; /* Bit3:1 */
		u8 latch_in_unit_0:                    1; /* Bit4 0: ECAT controlled, 1: PDI controlled */
		u8 latch_in_unit_1:                    1; /* Bit5 0: ECAT controlled, 1: PDI controlled */		
		u8 reserved_7_6:                       2; /* Bit7:6 */		
  } b;
} oDC_CYCLIC_UNIT_CTRL;

#define DC_SYNC_ACTIVATION                0x0981 /* Sync. Acviation (0x0981) */
typedef union
{
  u8 d8;
  struct{
		u8 sync_out_unit_act:                  1; /* Bit0 0: Deactivated, 1: Activated */
		u8 sync0_gen:                          1; /* Bit1 0: Deactivated, 1: SYNC0 pulse is generated*/
		u8 sync1_gen:                          1; /* Bit2 0: Deactivated, 1: SYNC1 pulse is generated */		
		u8 auto_act_by_wr_start_time_cyc_op:   1; /* Bit3 0: Disabled, 1: Auto-activation enabled */
		u8 ext_of_start_time_cyc_op:           1; /* Bit4 0: No extension, 1: Extend 32 bit written Start Time to 64 bit */
		u8 start_time_plausibility_chk:        1; /* Bit5 0: Disabled, 1: Immediate SyncSignal generation if Start Time is outside near future */
		u8 near_future_configuration:          1; /* Bit6 0: 1/2 dc width future, 1: ~2.1 sec. future */
		u8 sync_debug_pulse:                   1; /* Bit7 0: Deactived
		                                                  1: Immediately generate one ping only on SYNC0-1 according to 0x0981 for debugging
                                          		*/		
  } b;
} oDC_SYNC_ACTIVATION;

#define DC_PULSE_LEN_OF_SYNC_SIGNAL       0x0982 /* Pulse length of SyncSignals (0x0982:0x983) */
#define DC_ACTIVATION_STATUS              0x0984 /* Activation Status (0x0984) */
typedef union
{
  u8 d8;
  struct{
		u8 sync0_act_state:                    1; /* Bit0 0/1: First SYNC0 pulse is not pending/pending */
		u8 sync1_act_state:                    1; /* Bit1 0/1: First SYNC1 pulse is not pending/pending */
		u8 start_time_plausibility_chk_result: 1; /* Bit2 0/1: Start Time was within/out of near future */		
		u8 reserved_7_3:                       5; /* Bit7:3 */				
  } b;
} oDC_ACTIVATION_STATUS;

#define DC_SYNC0_STATUS                   0x098E /* SYNC0 Status (0x098E) */
#define DC_SYNC1_STATUS                   0x098F /* SYNC1 Status (0x098F) */
typedef union
{
  u8 d8;
  struct{
		u8 syncx_state_for_ack_mode:           1; /* Bit0 */
		u8 reserved_7_1:                       7; /* Bit7:1 */				
  } b;
} oDC_SYNCx_STATUS;

#define DC_START_TIME_CYCLIC_OPERATION    0x0990 /* Start Time Cyclic Operation (0x0990:0x0997)
                                                    Write: Start system time of cyclic operation in ns.
                                                    Read: System time of next SYNC0 pulse in ns.
                                                  */

#define DC_NEXT_SYNC1_PULSE               0x0998 /* System time of next SYNC1 (0x0998:0x099B) */
#define DC_SYNC0_CYCLE_TIME               0x09A0 /* Time between two consecutive SYNC0 pulse in ns (0x09A0:0x09A3) */
#define DC_SYNC1_CYCLE_TIME               0x09A4 /* Time between SYNC0 pulse and SYNC1 pulse in ns (0x09A4:0x09A7) */
#define DC_LATCH0_CONTROL                 0x09A8 /* LATCH 0 Control (0x09A8) */
#define DC_LATCH1_CONTROL                 0x09A9 /* LATCH 1 Control (0x09A9) */
typedef union
{
  u8 d8;
  struct{
		u8 latchx_positive_edge:               1; /* Bit0, 0: Continue latch active, 1: Single event */
		u8 latchx_negative_edge:               1; /* Bit1, 0: Continue latch active, 1: Single event */				
		u8 reserved_7_2:                       6; /* Bit7:2 */						
  } b;
} oDC_LATCHx_CONTROL;

#define DC_LATCH0_STATUS                  0x09AE /* LATCH 0 Status (0x09AE) */
#define DC_LATCH1_STATUS                  0x09AF /* LATCH 1 Status (0x09AF) */
typedef union
{
  u8 d8;
  struct{
		u8 event_latchx_positive_edge:         1; /* Bit0, 0: Positive edge not detected or continue mode
		                                                 , 1: Positive edge detected in single event mode only
                                          		*/
		u8 event_latchx_negative_edge:         1; /* Bit1, 0: Negative edge not detected or continue mode
		                                                 , 1: Negative edge detected in single event mode only
                                          		*/
		u8 latchx_pin_state:                   1;
		u8 reserved_7_3:                       5; /* Bit7:3 */						
  } b;
} oDC_LATCHx_STATUS;

#define DC_LATCH0_TIME_POSITIVE_EDGE      0x09B0 /* LATCH 0 Time Positive Edge (0x09B0:0x09B7) */
#define DC_LATCH0_TIME_NEGATIVE_EDGE      0x09B8 /* LATCH 0 Time Negative Edge (0x09B8:0x09BF) */
#define DC_LATCH1_TIME_POSITIVE_EDGE      0x09C0 /* LATCH 1 Time Positive Edge (0x09C0:0x09C7) */
#define DC_LATCH1_TIME_NEGATIVE_EDGE      0x09C8 /* LATCH 1 Time Negative Edge (0x09C8:0x09CF) */
#define DC_ECAT_BUF_CHANGE_EVENT_TIME     0x09F0 /* ECAT Buffer Change Event Time (0x09F0:0x09F3) */
#define DC_PDI_BUF_START_EVENT_TIME       0x09F8 /* PDI Buffer Start Event Time (0x09F8:0x09FB) */
#define DC_PDI_BUF_CHANGE_EVENT_TIME      0x09FC /* PDI Buffer Change Event Time (0x09FC:0x09FF) */

/* --------- Product&Vendor ID ------------- */
#define IC_PRODUCT_ID               0x0E00
typedef union
{
  u32 d32[2];
  struct{
		u32 chip_revision:                  8;  /* Bit7:0, 0x01 */				
		u32 package_type:                   4;  /* Bit11:8, 0x00 */
		u32 product_id:                    20;  /* Bit31:12, 0x5 8100 */		
		u32 reserved_63_32:                32;  /* Bit63:32 */
  } b;
} oIC_PRODUCT_ID;

#define IC_VENDOR_ID                0x0E08
typedef union
{
  u32 d32[2];
  struct{
		u32 vendor_id:                      32; /* Bit31:0, 0x0000 0b95 */				
		u32 reserved_63_32:                 32; /* Bit63:32 */
  } b;
} oIC_VENDOR_ID;

/* ------------- Digital I/O Registers ------------- */
#define DIOOR                    0x0F00
#define DIOIR                    0x1000

/* --------- General Purpose I/O Registers ------------- */
#define GIOOR                    0x0F10
#define GIOIR                    0x0F18

/* TYPE DECLARATIONS */

/* GLOBAL VARIABLES */

/* EXPORTED SUBPROGRAM SPECIFICATIONS */

#endif /* __ESC_REGS_H__ */

/* End of esc_regs.h */
