
#ifndef A10_MEMORYMAP_H
#define A10_MEMORYMAP_H

/***
 * 
 * Author: Dariusz Bruj (dariusz.bruj@gmail.com)
 * 
 * This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/.
 * 
 * */

namespace A10
{

	#define PA_SRAM_BASE                   0x00000000
	#define PA_SDRAM_START                 0x40000000
	#define PA_IO_BASE                     0x01c00000
	#define PA_SRAM_IO_BASE                0x01c00000   /* 4KB */
	#define PA_DRAM_IO_BASE                0x01c01000
	#define PA_DMAC_IO_BASE                0x01c02000
	#define PA_NANDFLASHC_IO_BASE          0x01c03000
	#define PA_TSI_IO_BASE                 0x01c04000
	#define PA_SPI0_IO_BASE                0x01c05000
	#define PA_SPI1_IO_BASE                0x01c06000
	#define PA_MSCC_IO_BASE                0x01c07000
	#define PA_TVD_IO_BASE                 0x01c08000
	#define PA_CSI0_IO_BASE                0x01c09000
	#define PA_TVE_IO_BASE                 0x01c0a000
	#define PA_EMAC_IO_BASE                0x01c0b000
	#define PA_TCON0_IO_BASE               0x01c0c000
	#define PA_TCON1_IO_BASE               0x01c0d000
	#define PA_VE_IO_BASE                  0x01c0e000
	#define PA_SDC0_IO_BASE                0x01c0f000
	#define PA_SDC1_IO_BASE                0x01c10000
	#define PA_SDC2_IO_BASE                0x01c11000
	#define PA_SDC3_IO_BASE                0x01c12000
	#define PA_USB0_IO_BASE                0x01c13000
	#define PA_USB1_IO_BASE                0x01c14000
	#define PA_SSE_IO_BASE                 0x01c15000
	#define PA_HDMI_IO_BASE                0x01c16000
	#define PA_SPI2_IO_BASE                0x01c17000
	#define PA_SATA_IO_BASE                0x01c18000
	#define PA_PATA_IO_BASE                0x01c19000
	#define PA_ACE_IO_BASE                 0x01c1a000
	#define PA_TVE1_IO_BASE                0x01c1b000
	#define PA_USB2_IO_BASE                0x01c1c000
	#define PA_CSI1_IO_BASE                0x01c1d000
	#define PA_TZASC_IO_BASE               0x01c1e000
	#define PA_SPI3_IO_BASE                0x01c1f000
	
	// PAGE 
	#define PA_CCM_IO_BASE                 0x01c20000
	#define PA_CCM_IO_SIZE				   1024		
	#define PA_INT_IO_BASE                 0x01c20400
	#define PA_INT_IO_SIZE				   1024	
	#define PA_PORTC_IO_BASE               0x01c20800
	#define PA_PORTC_IO_SIZE			   1024		
	#define PA_TIMERC_IO_BASE              0x01c20c00
	#define PA_TIMERC_IO_SIZE			   1024		
	
	// PAGE
	#define PA_SPDIF_IO_BASE               0x01c21000
	#define PA_AC97_IO_BASE                0x01c21400
	#define PA_IR0_IO_BASE                 0x01c21800
	#define PA_IR1_IO_BASE                 0x01c21c00
	#define PA_IIS_IO_BASE                 0x01c22400
	#define PA_LRADC_IO_BASE               0x01c22800
	#define PA_ADDA_IO_BASE                0x01c22c00
	#define PA_KEYPAD_IO_BASE              0x01c23000
	#define PA_TZPC_IO_BASE                0x01c23400
	#define PA_SID_IO_BASE                 0x01c23800
	#define PA_SJTAG_IO_BASE               0x01c23c00
	#define PA_TP_IO_BASE                  0x01c25000
	#define PA_PMU_IO_BASE                 0x01c25400
	#define PA_UART0_IO_BASE               0x01c28000
	#define PA_UART1_IO_BASE               0x01c28400
	#define PA_UART2_IO_BASE               0x01c28800
	#define PA_UART3_IO_BASE               0x01c28c00
	#define PA_UART4_IO_BASE               0x01c29000
	#define PA_UART5_IO_BASE               0x01c29400
	#define PA_UART6_IO_BASE               0x01c29800
	#define PA_UART7_IO_BASE               0x01c29c00
	#define PA_PS20_IO_BASE                0x01c2a000
	#define PA_PS21_IO_BASE                0x01c2a400
	#define PA_TWI0_IO_BASE                0x01c2ac00
	#define PA_TWI1_IO_BASE                0x01c2b000
	#define PA_TWI2_IO_BASE                0x01c2b400
	#define PA_CAN0_IO_BASE                0x01c2bc00
	#define PA_CAN1_IO_BASE                0x01c2c000
	#define PA_SCR_IO_BASE                 0x01c2c400
	#define PA_GPS_IO_BASE                 0x01c30000
	#define PA_MALI_IO_BASE                0x01c40000
	#define PA_DEFE0_IO_BASE               0x01e00000
	#define PA_DEFE1_IO_BASE               0x01e20000
	#define PA_DEBE0_IO_BASE               0x01e60000
	#define PA_DEBE1_IO_BASE               0x01e40000
	#define PA_MP_IO_BASE                  0x01e80000
	#define PA_AVG_IO_BASE                 0x01ea0000
	#define PA_BROM_BASE                   0xffff0000
	
}

#endif
