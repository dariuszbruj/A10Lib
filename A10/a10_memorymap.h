
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

#include <cstdint>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <cstdint>

namespace A10
{
    static const uintptr_t  PA_SRAM_BASE                   =0x00000000;
	static const uintptr_t  PA_SDRAM_START                 =0x40000000;
	static const uintptr_t  PA_IO_BASE                     =0x01c00000;
	static const uintptr_t  PA_SRAM_IO_BASE                =0x01c00000;  /* 4KB */
	static const uintptr_t  PA_DRAM_IO_BASE                =0x01c01000;
	static const uintptr_t  PA_DMAC_IO_BASE                =0x01c02000;
	static const uintptr_t  PA_NANDFLASHC_IO_BASE          =0x01c03000;
	static const uintptr_t  PA_TSI_IO_BASE                 =0x01c04000;

    // SPI0 page
	static const uintptr_t  PA_SPI0_IO_BASE                =0x01c05000;
	static const uintptr_t  PA_SPI0_IO_SIZE                =4096;

	static const uintptr_t  PA_SPI1_IO_BASE                =0x01c06000;
	static const uintptr_t  PA_MSCC_IO_BASE                =0x01c07000;
	static const uintptr_t  PA_TVD_IO_BASE                 =0x01c08000;
	static const uintptr_t  PA_CSI0_IO_BASE                =0x01c09000;
	static const uintptr_t  PA_TVE_IO_BASE                 =0x01c0a000;
	static const uintptr_t  PA_EMAC_IO_BASE                =0x01c0b000;
	static const uintptr_t  PA_TCON0_IO_BASE               =0x01c0c000;
	static const uintptr_t  PA_TCON1_IO_BASE               =0x01c0d000;
	static const uintptr_t  PA_VE_IO_BASE                  =0x01c0e000;
	static const uintptr_t  PA_SDC0_IO_BASE                =0x01c0f000;
	static const uintptr_t  PA_SDC1_IO_BASE                =0x01c10000;
	static const uintptr_t  PA_SDC2_IO_BASE                =0x01c11000;
	static const uintptr_t  PA_SDC3_IO_BASE                =0x01c12000;
	static const uintptr_t  PA_USB0_IO_BASE                =0x01c13000;
	static const uintptr_t  PA_USB1_IO_BASE                =0x01c14000;
	static const uintptr_t  PA_SSE_IO_BASE                 =0x01c15000;
	static const uintptr_t  PA_HDMI_IO_BASE                =0x01c16000;
	static const uintptr_t  PA_SPI2_IO_BASE                =0x01c17000;
	static const uintptr_t  PA_SATA_IO_BASE                =0x01c18000;
	static const uintptr_t  PA_PATA_IO_BASE                =0x01c19000;
	static const uintptr_t  PA_ACE_IO_BASE                 =0x01c1a000;
	static const uintptr_t  PA_TVE1_IO_BASE                =0x01c1b000;
	static const uintptr_t  PA_USB2_IO_BASE                =0x01c1c000;
	static const uintptr_t  PA_CSI1_IO_BASE                =0x01c1d000;
	static const uintptr_t  PA_TZASC_IO_BASE               =0x01c1e000;
	static const uintptr_t  PA_SPI3_IO_BASE                =0x01c1f000;

	// PAGE
	static const uintptr_t  PA_CCM_IO_BASE                 =0x01c20000;
	static const uintptr_t  PA_CCM_IO_SIZE				   =1024;
	static const uintptr_t  PA_INT_IO_BASE                 =0x01c20400;
	static const uintptr_t  PA_INT_IO_SIZE				   =1024;
	static const uintptr_t  PA_PORTC_IO_BASE               =0x01c20800;
	static const uintptr_t  PA_PORTC_IO_SIZE			   =1024;
	static const uintptr_t  PA_TIMERC_IO_BASE              =0x01c20c00;
	static const uintptr_t  PA_TIMERC_IO_SIZE			   =1024;

	// PAGE
	static const uintptr_t  PA_SPDIF_IO_BASE               =0x01c21000;
	static const uintptr_t  PA_AC97_IO_BASE                =0x01c21400;
	static const uintptr_t  PA_IR0_IO_BASE                 =0x01c21800;
	static const uintptr_t  PA_IR1_IO_BASE                 =0x01c21c00;
	static const uintptr_t  PA_IIS_IO_BASE                 =0x01c22400;
	static const uintptr_t  PA_LRADC_IO_BASE               =0x01c22800;
	static const uintptr_t  PA_ADDA_IO_BASE                =0x01c22c00;
	static const uintptr_t  PA_KEYPAD_IO_BASE              =0x01c23000;
	static const uintptr_t  PA_TZPC_IO_BASE                =0x01c23400;
	static const uintptr_t  PA_SID_IO_BASE                 =0x01c23800;
	static const uintptr_t  PA_SJTAG_IO_BASE               =0x01c23c00;
	static const uintptr_t  PA_TP_IO_BASE                  =0x01c25000;
	static const uintptr_t  PA_PMU_IO_BASE                 =0x01c25400;
	static const uintptr_t  PA_UART0_IO_BASE               =0x01c28000;
	static const uintptr_t  PA_UART1_IO_BASE               =0x01c28400;
	static const uintptr_t  PA_UART2_IO_BASE               =0x01c28800;
	static const uintptr_t  PA_UART3_IO_BASE               =0x01c28c00;
	static const uintptr_t  PA_UART4_IO_BASE               =0x01c29000;
	static const uintptr_t  PA_UART5_IO_BASE               =0x01c29400;
	static const uintptr_t  PA_UART6_IO_BASE               =0x01c29800;
	static const uintptr_t  PA_UART7_IO_BASE               =0x01c29c00;
	static const uintptr_t  PA_PS20_IO_BASE                =0x01c2a000;
	static const uintptr_t  PA_PS21_IO_BASE                =0x01c2a400;
	static const uintptr_t  PA_TWI0_IO_BASE                =0x01c2ac00;
	static const uintptr_t  PA_TWI1_IO_BASE                =0x01c2b000;
	static const uintptr_t  PA_TWI2_IO_BASE                =0x01c2b400;
	static const uintptr_t  PA_CAN0_IO_BASE                =0x01c2bc00;
	static const uintptr_t  PA_CAN1_IO_BASE                =0x01c2c000;
	static const uintptr_t  PA_SCR_IO_BASE                 =0x01c2c400;
	static const uintptr_t  PA_GPS_IO_BASE                 =0x01c30000;
	static const uintptr_t  PA_MALI_IO_BASE                =0x01c40000;
	static const uintptr_t  PA_DEFE0_IO_BASE               =0x01e00000;
	static const uintptr_t  PA_DEFE1_IO_BASE               =0x01e20000;
	static const uintptr_t  PA_DEBE0_IO_BASE               =0x01e60000;
	static const uintptr_t  PA_DEBE1_IO_BASE               =0x01e40000;
	static const uintptr_t  PA_MP_IO_BASE                  =0x01e80000;
	static const uintptr_t  PA_AVG_IO_BASE                 =0x01ea0000;
	static const uintptr_t  PA_BROM_BASE                   =0xffff0000;

}

#endif
