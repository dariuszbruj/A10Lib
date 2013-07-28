#ifndef A10_SPI_H
#define A10_SPI_H

#include "debug.h"

#include "a10_memorymap.h"
#include "a10_gpio.h"

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
    class SPI
    {
        private:

            // a SPIx pointer
            volatile uintptr_t* 	_spix_address;

            // a PIO pointer
            volatile uintptr_t* 	_gpio_address;

            // address of mapped memory
            volatile void*          _map;

            // is PIO initialized ?
            uint8_t 	    _isInitialized;

            // memory page size
            uint32_t       _page_size;

            // a page mask used to get an offset of main address
            uint32_t       _page_mask;

            // get pages count for this register.
            uint32_t       _spix_size;


        public:

                /*
                 * Available ports on this chips.
                 * */
                enum class Module : uint8_t {
                    SPI0 = 0,
                    SPI1 = 1,
                    SPI2 = 2,
                    SPI3 = 3,
                    SOFT = 8
                 };


            /** Default constructor */
            SPI();

            /** Default destructor */
            virtual ~SPI();

            /*
             * Initialize a spi module
             * */
            uint8_t init(A10::GPIO *gpio);

            /*
             * Initialize a spiX module
             * */
            uint8_t init(A10::SPI::Module module);

            /*
             * Checks if this module is intiialized.
             * */
            uint8_t		isInitialized();

            /*
                SDC

                Master Sample Data Control
                Set this bit to  ̳1‘ to make the internal read sample point
                with a delay of half cycle of SPI_CLK. It is used in high
                speed read operation to reduce the error caused by the time
                delay of SPI_CLK propagating between master and slave.
                1 – delay internal read sample point
                0 –  normal operation, do not delay internal read sample point
            */
            void SetSDC();

            /*
                TP_EN
                Transmit Pause Enable
                In master mode, it is used to control transmit state machine
                to stop smart burst sending when RX FIFO is full.
                1 – stop transmit data when RXFIFO full
                0 – normal operation, ignore RXFIFO status
            */
            void SetTP_EN();


            /*
                SS_LEVEL
                When control SS signal manually (SPI_CTRL_REG.SS_CTRL==1),
                set this bit to '1' or '0' to control the level of SS signal.
                1 – set SS to high
                0 – set SS to low
            */
            void SetSS_LEVEL();

            /*
                SS_CTRL
                SS Output Mode Select
                Usually, controller sends SS signal automatically with data
                together. When this bit is set to 1, software must manually
                write SPI_CTRL_REG.SS_LEVEL (bit [17]) to 1 or 0 to
                control the level of SS signal.
                1 – manual output SS
                0 – automatic output SS
            */
            void SetSS_CTRL();

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
            void SetDHB();

            /*
                DDB
                Dummy Burst Type
                0: The bit value of dummy SPI burst is zero
                1: The bit value of dummy SPI burst is one
            */
            void SetDDB();

            /*
                SS
                SPI Chip Select
                Select one of four external SPI Master/Slave Devices

                00: SPI_SS0 will be asserted
                01: SPI_SS1 will be asserted
                10: SPI_SS2 will be asserted
                11: SPI_SS3 will be asserted
                Notes: This two bits can‘t be configured for SPI1 Engine
            */
            void SetSS();

            /*
                RPSM
                Rapid mode select.
                Selects rapids operation for high speed read.
                0: Normal read mode
                1: Rapids read mode
            */
            void SetRPSM();

            /*
                XCH
                Exchange Burst
                In master mode it is used to start to SPI burst
                0: Idle
                1: Initiates exchange. After finishing the SPI bursts transfer
                specified by BC, this bit is cleared to zero by SPI Controller.
            */
            void SetXCH();

            /*
                RF_RST
                RXFIFO Reset Write '1' to reset the control portion of the receiver FIFO
                and treats the FIFO as empty.
                It is 'self-clearing'. It is not necessary to clear this bit

            */
            void SetRF_RST();

            /*
                TF_RST

                TXFIFO Reset Write '1' to reset the control portion of the transmit FIFO
                and treats the FIFO as empty.
                It is 'self-clearing'. It is not necessary to clear this bit.
            */
            void SetTF_RST();

            /*
                SSCTL
                In master mode, this bit selects the output wave form for the
                SPI_SSx signal.
                0: SPI_SSx remains asserted between SPI bursts
                1: Negate SPI_SSx between SPI bursts
            */
            void SetSSCTL();

            /*
                LMTF
                LSB/ MSB Transfer First select
                0: MSB first
                1: LSB first
            */
            void SetLMTF();

            /*
                DMAMC
                SPI DMA Mode Control
                0: Normal DMA mode
                1: Dedicate DMA mode
            */
            void SetDMAMC();

            /*
                SSPOL
                SPI Chip Select Signal Polarity Control
                0: Active high polarity (0 = Idle)
                1: Active low polarity (1 = Idle)
            */
            void SetSSPOL();

            /*
                POL
                SPI Clock Polarity Control
                0: Active high polarity (0 = Idle)
                1: Active low polarity (1 = Idle)
            */
            void SetPOL();

            /*
                PHA
                SPI Clock/Data Phase Control
                0: Phase 0 (Leading edge for sample data)
                1: Phase 1 (Leading edge for setup data)
            */
            void SetPHA();

            /*
                MODE
                SPI Function Mode Select
                0: Slave Mode
                1: Master Mode
            */
            void SetMODE();

            /*
                EN
                SPI Module Enable Control
                0: Disable
                1: Enable
            */
            void Enable();
            void Disable();

    };

}
#endif // A10_SPI_H
