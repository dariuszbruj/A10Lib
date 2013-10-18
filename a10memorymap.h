/* 
 * File:   memorymap.h
 * Author: dbruj
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/.
 *
 * Created on 18 październik 2013, 17:52
 */

#ifndef A10MEMORY_H
#define	A10MEMORY_H

struct A10MEMORY
{
   static const uintptr_t  SRAM_BASE            = 0x00000000;
   static const uintptr_t  SDRAM_START          = 0x40000000;
   static const uintptr_t  IO_BASE              = 0x01c00000;
   static const uintptr_t  SRAM_IO_BASE         = 0x01c00000;  /* 4KB */
   static const uintptr_t  DRAM_IO_BASE         = 0x01c01000;
   static const uintptr_t  DMAC_IO_BASE         = 0x01c02000;
   static const uintptr_t  NANDFLASHC_IO_BASE   = 0x01c03000;
   static const uintptr_t  TSI_IO_BASE          = 0x01c04000;

    // SPI0 page
   static const uintptr_t  SPI0_IO_BASE         = 0x01c05000;
   static const uintptr_t  SPI0_IO_SIZE         = 4096;

   static const uintptr_t  SPI1_IO_BASE         = 0x01c06000;
   static const uintptr_t  MSCC_IO_BASE         = 0x01c07000;
   static const uintptr_t  TVD_IO_BASE          = 0x01c08000;
   static const uintptr_t  CSI0_IO_BASE         = 0x01c09000;
   static const uintptr_t  TVE_IO_BASE          = 0x01c0a000;
   static const uintptr_t  EMAC_IO_BASE         = 0x01c0b000;
   static const uintptr_t  TCON0_IO_BASE        = 0x01c0c000;
   static const uintptr_t  TCON1_IO_BASE        = 0x01c0d000;
   static const uintptr_t  VE_IO_BASE           = 0x01c0e000;
   static const uintptr_t  SDC0_IO_BASE         = 0x01c0f000;
   static const uintptr_t  SDC1_IO_BASE         = 0x01c10000;
   static const uintptr_t  SDC2_IO_BASE         = 0x01c11000;
   static const uintptr_t  SDC3_IO_BASE         = 0x01c12000;
   static const uintptr_t  USB0_IO_BASE         = 0x01c13000;
   static const uintptr_t  USB1_IO_BASE         = 0x01c14000;
   static const uintptr_t  SSE_IO_BASE          = 0x01c15000;
   static const uintptr_t  HDMI_IO_BASE         = 0x01c16000;
   static const uintptr_t  SPI2_IO_BASE         = 0x01c17000;
   static const uintptr_t  SATA_IO_BASE         = 0x01c18000;
   static const uintptr_t  PATA_IO_BASE         = 0x01c19000;
   static const uintptr_t  ACE_IO_BASE          = 0x01c1a000;
   static const uintptr_t  TVE1_IO_BASE         = 0x01c1b000;
   static const uintptr_t  USB2_IO_BASE         = 0x01c1c000;
   static const uintptr_t  CSI1_IO_BASE         = 0x01c1d000;
   static const uintptr_t  TZASC_IO_BASE        = 0x01c1e000;
   static const uintptr_t  SPI3_IO_BASE         = 0x01c1f000;

   // PAGE
   static const uintptr_t  CCM_IO_BASE          = 0x01c20000;
   static const uintptr_t  CCM_IO_SIZE          = 1024;
   static const uintptr_t  INT_IO_BASE          = 0x01c20400;
   static const uintptr_t  INT_IO_SIZE          = 1024;
   static const uintptr_t  PORTC_IO_BASE        = 0x01c20800;
   static const uintptr_t  PORTC_IO_SIZE        = 1024;
   static const uintptr_t  TIMERC_IO_BASE       = 0x01c20c00;
   static const uintptr_t  TIMERC_IO_SIZE       = 1024;

   // PAGE
   static const uintptr_t  SPDIF_IO_BASE        = 0x01c21000;
   static const uintptr_t  AC97_IO_BASE         = 0x01c21400;
   static const uintptr_t  IR0_IO_BASE          = 0x01c21800;
   static const uintptr_t  IR1_IO_BASE          = 0x01c21c00;
   static const uintptr_t  IIS_IO_BASE          = 0x01c22400;
   static const uintptr_t  LRADC_IO_BASE        = 0x01c22800;
   static const uintptr_t  ADDA_IO_BASE         = 0x01c22c00;
   static const uintptr_t  KEYPAD_IO_BASE       = 0x01c23000;
   static const uintptr_t  TZPC_IO_BASE         = 0x01c23400;
   static const uintptr_t  SID_IO_BASE          = 0x01c23800;
   static const uintptr_t  SJTAG_IO_BASE        = 0x01c23c00;
   static const uintptr_t  TP_IO_BASE           = 0x01c25000;
   static const uintptr_t  PMU_IO_BASE          = 0x01c25400;
   static const uintptr_t  UART0_IO_BASE        = 0x01c28000;
   static const uintptr_t  UART1_IO_BASE        = 0x01c28400;
   static const uintptr_t  UART2_IO_BASE        = 0x01c28800;
   static const uintptr_t  UART3_IO_BASE        = 0x01c28c00;
   static const uintptr_t  UART4_IO_BASE        = 0x01c29000;
   static const uintptr_t  UART5_IO_BASE        = 0x01c29400;
   static const uintptr_t  UART6_IO_BASE        = 0x01c29800;
   static const uintptr_t  UART7_IO_BASE        = 0x01c29c00;
   static const uintptr_t  PS20_IO_BASE         = 0x01c2a000;
   static const uintptr_t  PS21_IO_BASE         = 0x01c2a400;
   static const uintptr_t  TWI0_IO_BASE         = 0x01c2ac00;
   static const uintptr_t  TWI1_IO_BASE         = 0x01c2b000;
   static const uintptr_t  TWI2_IO_BASE         = 0x01c2b400;
   static const uintptr_t  CAN0_IO_BASE         = 0x01c2bc00;
   static const uintptr_t  CAN1_IO_BASE         = 0x01c2c000;
   static const uintptr_t  SCR_IO_BASE          = 0x01c2c400;
   static const uintptr_t  GPS_IO_BASE          = 0x01c30000;
   static const uintptr_t  MALI_IO_BASE         = 0x01c40000;
   static const uintptr_t  DEFE0_IO_BASE        = 0x01e00000;
   static const uintptr_t  DEFE1_IO_BASE        = 0x01e20000;
   static const uintptr_t  DEBE0_IO_BASE        = 0x01e60000;
   static const uintptr_t  DEBE1_IO_BASE        = 0x01e40000;
   static const uintptr_t  MP_IO_BASE           = 0x01e80000;
   static const uintptr_t  AVG_IO_BASE          = 0x01ea0000;
   static const uintptr_t  BROM_BASE            = 0xffff0000;
};

#endif	/* A10MEMORY_H */

