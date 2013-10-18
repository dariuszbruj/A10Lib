/* 
 * File:   a10spi.h
 * Author: dbruj
  *
 * This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/.
 *
 * Created on 18 październik 2013, 18:34
 */

#ifndef A10SPIH
#define	A10SPIH

   class A10SPI
   {
       private:

        /*
         * Available ports on this chips.
         * */
         enum MODULE : uint8_t {
            SPI0 = 0,
            SPI1 = 1,
            SPI2 = 2,
            SPI3 = 3,
            SOFT = 8
         };

         // a SPIx pointer
         volatile uintptr_t*  _spix_address;

         // a PIO pointer
         A10GPIO*             _gpio;

         // address of mapped memory
         volatile void*       _map;

         // is PIO initialized ?
         uint8_t              _isInitialized;

         // which module is used?
         MODULE               _module;

         // memory page size
         uint32_t             _page_size;

         // a page mask used to get an offset of main address
         uint32_t             _page_mask;

         // get pages count for this register.
         uint32_t             _spix_size;

         //Available registers
         static const uintptr_t RXDATA            = 0;
         static const uintptr_t TXDATA            = 1;
         static const uintptr_t CTRL              = 2;
         static const uintptr_t INTCTL            = 3;
         static const uintptr_t ST                = 4;
         static const uintptr_t DMACTL            = 5;
         static const uintptr_t WAIT              = 6;
         static const uintptr_t CCTL              = 7;
         static const uintptr_t BC                = 8;
         static const uintptr_t TC                = 9;
         static const uintptr_t FIFO_STA          = 10;

         // CTRL register
         static const uint32_t CTRL_REG__EN       = 0;
         static const uint32_t CTRL_REG__MODE     = 1;
         static const uint32_t CTRL_REG__PHA      = 2;
         static const uint32_t CTRL_REG__POL      = 3;
         static const uint32_t CTRL_REG__SSPOL    = 4;
         static const uint32_t CTRL_REG__DMAMC    = 5;
         static const uint32_t CTRL_REG__LMTF     = 6;
         static const uint32_t CTRL_REG__SSCTL    = 7;
         static const uint32_t CTRL_REG__TF_RST   = 8;
         static const uint32_t CTRL_REG__RF_RST   = 9;
         static const uint32_t CTRL_REG__XCH      = 10;
         static const uint32_t CTRL_REG__RPSM     = 11;
         static const uint32_t CTRL_REG__SS       = 12;
         static const uint32_t CTRL_REG__DDB      = 14;
         static const uint32_t CTRL_REG__DHB      = 15;
         static const uint32_t CTRL_REG__SS_CTRL  = 16;
         static const uint32_t CTRL_REG__SS_LEVEL = 17;
         static const uint32_t CTRL_REG__TP_EN    = 18;
         static const uint32_t CTRL_REG__SDC      = 19;

       public:

         /** Default constructor */
         A10SPI();

         /** Default destructor */
         virtual ~A10SPI();

         /*
          * Initialize a spi module
          * */
         uint8_t init(A10GPIO* gpio);

         /*
          * Initialize a spiX module
          * */
         uint8_t init(A10GPIO* gpio, A10SPI::MODULE module);

         /*
          * Checks if this module is intialized.
          * */
         uint8_t	isInitialized();

       private:
         /*
             SDC

             Master Sample Data Control
             Set this bit to  1 to make the internal read sample point
             with a delay of half cycle of CLK. It is used in high
             speed read operation to reduce the error caused by the time
             delay of CLK propagating between master and slave.
             1 -> delay internal read sample point
             0 ->  normal operation, do not delay internal read sample point
         */
         void _SetSDC(uint8_t v);

         /*
             TP_EN
             Transmit Pause Enable
             In master mode, it is used to control transmit state machine
             to stop smart burst sending when RX FIFO is full.
             1 ->stop transmit data when RXFIFO full
             0 -> normal operation, ignore RXFIFO status
         */
         void _SetTP_EN(uint8_t v);


         /*
             SS_LEVEL
             When control SS signal manually (CTRL_REG.SS_CTRL==1),
             set this bit to '1' or '0' to control the level of SS signal.
             1 -> set SS to high
             0 -> set SS to low
         */
         void _SetSS_LEVEL(uint8_t v);

         /*
             SS_CTRL
             SS Output Mode Select
             Usually, controller sends SS signal automatically with data
             together. When this bit is set to 1, software must manually
             write CTRL_REG.SS_LEVEL (bit [17]) to 1 or 0 to
             control the level of SS signal.
             1 -> manual output SS
             0 -> automatic output SS
         */
         void _SetSS_CTRL(uint8_t v);

         /*
             DHB
             Discard Hash Burst

             In master mode it controls whether discarding unused SPI
             bursts
             0: Receiving all SPI bursts in BC period
             1: Discard unused SPI bursts, only fetching the SPI bursts
             during dummy burst period. The bursts number is specified
             by WTC.
         */
         void _SetDHB(uint8_t v);

         /*
             DDB
             Dummy Burst Type
             0: The bit value of dummy SPI burst is zero
             1: The bit value of dummy SPI burst is one
         */
         void _SetDDB(uint8_t v);

         /*
             SS
             SPI Chip Select
             Select one of four external SPI Master/Slave Devices

             00: SS0 will be asserted
             01: SS1 will be asserted
             10: SS2 will be asserted
             11: SS3 will be asserted
             Notes: This two bits canâ€�t be configured for SPI1 Engine
         */
         void _SetSS(uint8_t v);

         /*
             RPSM
             Rapid mode select.
             Selects rapids operation for high speed read.
             0: Normal read mode
             1: Rapids read mode
         */
         void _SetRPSM(uint8_t v);

         /*
             XCH
             Exchange Burst
             In master mode it is used to start to SPI burst
             0: Idle
             1: Initiates exchange. After finishing the SPI bursts transfer
             specified by BC, this bit is cleared to zero by SPI Controller.
         */
         void _SetXCH(uint8_t v);

         /*
             RF_RST
             RXFIFO Reset Write '1' to reset the control portion of the receiver FIFO
             and treats the FIFO as empty.
             It is 'self-clearing'. It is not necessary to clear this bit

         */
         void _SetRF_RST(uint8_t v);

         /*
             TF_RST

             TXFIFO Reset Write '1' to reset the control portion of the transmit FIFO
             and treats the FIFO as empty.
             It is 'self-clearing'. It is not necessary to clear this bit.
         */
         void _SetTF_RST(uint8_t v);

         /*
             SSCTL
             In master mode, this bit selects the output wave form for the
             SSx signal.
             0: SSx remains asserted between SPI bursts
             1: Negate SSx between SPI bursts
         */
         void _SetSSCTL(uint8_t v);

         /*
             LMTF
             LSB/ MSB Transfer First select
             0: MSB first
             1: LSB first
         */
         void _SetLMTF(uint8_t v);

         /*
             DMAMC
             SPI DMA Mode Control
             0: Normal DMA mode
             1: Dedicate DMA mode
         */
         void _SetDMAMC(uint8_t v);

         /*
             SSPOL
             SPI Chip Select Signal Polarity Control
             0: Active high polarity (0 = Idle)
             1: Active low polarity (1 = Idle)
         */
         void _SetSSPOL(uint8_t v);

         /*
             POL
             SPI Clock Polarity Control
             0: Active high polarity (0 = Idle)
             1: Active low polarity (1 = Idle)
         */
         void _SetPOL(uint8_t v);

         /*
             PHA
             SPI Clock/Data Phase Control
             0: Phase 0 (Leading edge for sample data)
             1: Phase 1 (Leading edge for setup data)
         */
         void _SetPHA(uint8_t v);

         /*
             MODE
             SPI Function Mode Select
             0: Slave Mode
             1: Master Mode
         */
         void _SetMODE(uint8_t v);

         /*
             EN
             SPI Module Enable Control
             0: Disable
             1: Enable
         */

       public:

         void DebugSPI();

         /**
             Enable SPI Module
          */
         void Enable();

         /**
             Disable SPI Module
          */
         void Disable();

         /**
             Set SPI As Master
          */
         void SetAsMaster();

         /**
             Set SPI As Slave
          */
         void SetAsSlave();

         /**
             Set PHA to low
             0: Phase 0 (Leading edge for sample data)
          */
         void SetPHA0();

         /**
             Set PHA to high
             1: Phase 1 (Leading edge for setup data)
          */
         void SetPHA1();

         /**
             Set POL to low
             0: Active high polarity (0 = Idle)
          */
         void SetPOL0();

         /**
             Set POL to high
             1: Active low polarity (1 = Idle)
          */
         void SetPOL1();

         /**
             Set SS polarity to high
          */
         void SetSSPOL1();

         /**
             Set SS polarity to low
          */
         void SetSSPOL0();

         /**
             Set SS polarity to low
          */
         void SetSSCTLRemain();
         void SetSSCTLNegate();

         /**
             Set DMA to normal
             0: Normal DMA mode
          */
         void SetDMANormal();

         /**
             Set DMA to dedicated
             1: Dedicate DMA mode
          */
         void SetDMADedicated();

         /**
             0: MTF first
          */
         void SetMTF();

         /**
             0: LTF first
          */
         void SetLTF();

         /**
             Reset TXFIFO.
          */
         void ResetTXFIFO();

         /**
             Reset RXFIFO.
          */
         void ResetRXFIFO();

         void SetReadModeNormal();
         void SetReadModeRapid();

         void SetDummyBurstZero();
         void SetDummyBurstOne();


         void SetDiscardHashBurst();
         void SetReciveAllBursts();


         /**
             Set SS mode.
          */
         void SetSSManual();
         void SetSSAutomatic();

         /**
             If SS mode is set to manual this is used to change state of SS.
          */
         void SetSSHigh();
         void SetSSLow();

         void Write(uint8_t *data);
         void Read(uint8_t *data);

         uint32_t SetBurstCounter(uint32_t n);
         uint32_t SetTransmitCouter(uint32_t n);

         /*
          * Rozpocznij transfer.
          */
         void Transfer();

   };

#endif	/* A10SPIH */

   
   