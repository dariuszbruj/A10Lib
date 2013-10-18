
/***
 *
 * Author: Dariusz Bruj (dariusz.bruj@gmail.com)
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/.
 *
 * */

#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <bitset>
#include <sys/mman.h>

#include "a10.h"
#include "a10gpio.h"
#include "a10spi.h"
#include "a10memorymap.h"

A10SPI::A10SPI()
{
	// Set to uninitialized
	this->_isInitialized = 0;

	// Set default pointer
	this->_spix_address = nullptr;

	// get platform page size
	this->_page_size = sysconf(_SC_PAGESIZE);
	// get platform page mask
	this->_page_mask  = (~(this->_page_size-1));

}

A10SPI::~A10SPI()
{
    //dtor
}

uint8_t A10SPI::init(A10GPIO *gpio)
{
	return this->init(gpio, A10SPI::MODULE::SPI0);
}

uint8_t A10SPI::init(A10GPIO *gpio, A10SPI::MODULE module)
{
    // Check if GPIO is initialized
    if (!gpio->isInitialized())
    {
        #if DEBUG > 1
            std::cout << "spi: gpio not initialized." << std::endl;
        #endif

        return 1;
    }

    // Save instance of gpio
    this->_gpio = gpio;

    // Get memory file
	int mem_fd = -1;

	if ((mem_fd = open("/dev/mem", O_RDWR | O_SYNC) ) < 0)
    {
		#if DEBUG > 1
			std::cout << "spi: mem_fd failed" << std::endl;
		#endif
		// Return error code.
		return 2;
    }

	#if DEBUG > 1
		std::cout << "spi: mem_fd ok" << std::endl;
	#endif

	// map to address
	unsigned int start, offset;

    switch (module)
    {
        case A10SPI::MODULE::SPI0:
            start  = A10MEMORY::SPI0_IO_BASE   &  this->_page_mask;
            offset = A10MEMORY::SPI0_IO_BASE  & ~this->_page_mask;

            // get pages count for SPIx register.
            this->_spix_size = ((unsigned int)(A10MEMORY::SPI0_IO_SIZE / this->_page_size)+1)*this->_page_size;

            #if DEBUG > 1
                std::cout << "spi: selected SPI0" << std::endl;
            #endif

            break;
        case A10SPI::MODULE::SPI1:
            start  = A10MEMORY::SPI1_IO_BASE &  this->_page_mask;
            offset = A10MEMORY::SPI1_IO_BASE & ~this->_page_mask;

            // get pages count for SPIx register.
            this->_spix_size = ((unsigned int)(A10MEMORY::SPI0_IO_SIZE / this->_page_size)+1)*this->_page_size;

            #if DEBUG > 1
                std::cout << "spi: selected SPI1" << std::endl;
            #endif

            break;
        case A10SPI::MODULE::SPI2:
            start  = A10MEMORY::SPI2_IO_BASE &  this->_page_mask;
            offset = A10MEMORY::SPI2_IO_BASE & ~this->_page_mask;

            // get pages count for SPIx register.
            this->_spix_size = ((unsigned int)(A10MEMORY::SPI0_IO_SIZE / this->_page_size)+1)*this->_page_size;

            #if DEBUG > 1
                std::cout << "spi: selected SPI2" << std::endl;
            #endif

            break;
        case A10SPI::MODULE::SPI3:
            start  = A10MEMORY::SPI3_IO_BASE &  this->_page_mask;
            offset = A10MEMORY::SPI3_IO_BASE & ~this->_page_mask;

            // get pages count for SPIx register. (the sa
            this->_spix_size = ((unsigned int)(A10MEMORY::SPI0_IO_SIZE / this->_page_size)+1)*this->_page_size;

            #if DEBUG > 1
                std::cout << "spi: selected SPI3" << std::endl;
            #endif

            break;

        default:
            #if DEBUG > 1
                std::cout << "spi: module not valid." << std::endl;
            #endif

            break;
    }

    // save used module
    this->_module = module;

    #if DEBUG > 1
		std::cout << "spi: start " << (void*) start << std::endl;
		std::cout << "spi: offset " << (void*) offset << std::endl;
    #endif

    this->_map = (volatile void*) mmap( (void*) nullptr, this->_spix_size, (PROT_READ | PROT_WRITE), MAP_SHARED, mem_fd, start);
    //_map = (volatile void*) mmap( (void*)start, this->_spix_size, (PROT_READ | PROT_WRITE), MAP_SHARED, mem_fd, 0);


	if (MAP_FAILED == this->_map)
	{
		#if DEBUG > 1
			std::cout << "mmap failed" << std::endl;
		#endif

		return 2;
	}

	#if DEBUG > 1
		std::cout << "spi: mmap ok" << std::endl;
	#endif

    close(mem_fd);

	// SET SPIx offset ADDRESS.
	this->_spix_address = (volatile uintptr_t *) ( (uintptr_t)this->_map + offset);

	// DISPLAY VALUES
	#if DEBUG > 1
		std::cout << "spi: map " << (void*) this->_map << std::endl;
		std::cout << "spi: SPIx " << (void*) this->_spix_address  << std::endl;
	#endif

	this->_isInitialized = 1;

	return 0;
}

uint8_t  A10SPI::isInitialized()
{
	return this->_isInitialized;
}

void A10SPI::DebugSPI()
{
    std::bitset<32> b, c, d, e;

    volatile uint32_t * CTRL = this->_spix_address;

    for(int i = 2; i < 11; i++)
    {
        volatile uint32_t* data = (CTRL+i);
        std::cout << (void*) (data) << " " ;
        //CTRL = (volatile uint32_t *)((uint32_t)this->_spix_address + i*4);
        b = *data;
        c = *data;
        d = *data;
        e = *data;
        for(int j = 8; j > 0; j--)
        {
            std::cout << b[24-1+j];
        }
        std::cout << " ";
        for(int j = 8; j > 0; j--)
        {
            std::cout << b[16-1+j];
        }
        std::cout << " ";
        for(int j = 8; j > 0; j--)
        {
            std::cout << b[8-1+j];
        }
        std::cout << " ";
        for(int j = 8; j > 0; j--)
        {
            std::cout << b[-1+j];
        }
        std::cout << " " << *data << std::endl;
    }

    volatile uint32_t* data = (CTRL+10);
    std::cout << (void*) (data) << " TXFIFO: " << (*data >> 16) << " RXFIFO: " << (*data & 0x3F) << std::endl;;
}

void A10SPI::Write(uint8_t *data)
{
    // if not initialized cancel.
    if (!this->isInitialized())
        return;

    #if DEBUG > 1
        std::bitset<8> b;
        b = *data; //*(this->_spix_address + A10SPI::TXDATA);
        std::cout << "spi: writing data : " << b.to_string() << std::endl;
    #endif

    uint8_t* reg = ((uint8_t*)(this->_spix_address + A10SPI::TXDATA));

    *reg = *data;
}

void A10SPI::Read(uint8_t *data)
{
    // if not initialized cancel.
    if (!this->isInitialized())
        return;

    *data = *((uint8_t*) (this->_spix_address + A10SPI::RXDATA));

    #if DEBUG > 1
        std::bitset<8> b;
        b = *data;
        std::cout << "spi: data is: " << b.to_string() << std::endl;
    #endif
}

void A10SPI::Transfer()
{
    // if not initialized cancel.
    if (!this->isInitialized())
        return;

    this->_SetXCH(1);
}

uint32_t A10SPI::SetBurstCounter(uint32_t n)
{
    // if not initialized cancel.
    if (!this->isInitialized())
        return -1;

    if (n > 16777215)
        return -2;

      *(this->_spix_address + A10SPI::BC) = n;

    #if DEBUG > 1
        std::cout << "spi: set burts to " << (int) n << std::endl;
    #endif

    return 0;
}

uint32_t A10SPI::SetTransmitCouter(uint32_t n)
{
    // if not initialized cancel.
    if (!this->isInitialized())
        return -1;

    if (n > 16777215)
        return -2;

      *(this->_spix_address + A10SPI::TC) = n;

    #if DEBUG > 1
        std::cout << "spi: set transmit counter to " << (int) n << std::endl;
    #endif

    return 0;
}

void A10SPI::SetDiscardHashBurst()
{
    // if not initialized cancel.
    if (!this->isInitialized())
        return;

    this->_SetDHB(1);
}

void A10SPI::SetReciveAllBursts()
{
    // if not initialized cancel.
    if (!this->isInitialized())
        return;

    this->_SetDHB(0);
}

void A10SPI::Enable()
{
    if (!this->isInitialized())
        return;

    // set SPI pins
    switch (this->_module)
    {
        case A10SPI::MODULE::SPI0:
            this->_gpio->select(A10::PIN::PI10, A10::PINMODE::Alt1); //CS0
            this->_gpio->select(A10::PIN::PI11, A10::PINMODE::Alt1); //CLK
            this->_gpio->select(A10::PIN::PI12, A10::PINMODE::Alt1); //MOSI
            this->_gpio->select(A10::PIN::PI13, A10::PINMODE::Alt1); //MISO
            this->_gpio->select(A10::PIN::PI14, A10::PINMODE::Alt1); //CS1
        break;

        case A10SPI::MODULE::SPI1:
        break;

        case A10SPI::MODULE::SPI2:
        break;

        case A10SPI::MODULE::SPI3:
        break;

        default:
            #if DEBUG > 1
                std::cout << "spi: module not valid." << std::endl;
            #endif
            return;
        break;
    }

    volatile uint32_t* CTRL = (volatile uintptr_t *)((uint32_t) this->_spix_address );
    *(CTRL+2) |= 1;

    #if DEBUG > 1
        std::cout << "spi: enabled." << std::endl;
    #endif

    //this->_SetXCH(1);

//    // wpisz dane
//    *(CTRL+1) |= 255;
//
//    std::cout << "Add data to TX" << std::endl;
//    for(int i = 0; i < 11; i++)
//    {
//        //CTRL = (volatile uint32_t *)((uint32_t)this->_spix_address + i*4);
//        b = *(CTRL+i);
//        std::cout << (void*) (CTRL+i) << " " << b.to_string() << " " << *(CTRL+i) << std::endl;
//    }
//    *(CTRL+2) &= ~(1 << 16); // automatic output SS
//    *(CTRL+2) |= ( 1<<10); // start xch
//
//
//    std::cout << "After exchange" << std::endl;
//    for(int i = 0; i < 11; i++)
//    {
//        //CTRL = (volatile uint32_t *)((uint32_t)this->_spix_address + i*4);
//        b = *(CTRL+i);
//        std::cout << (void*) (CTRL+i) << " " << b.to_string() << " " << *(CTRL+i) << std::endl;
//    }
//
//    std::cout << "After burst couter cv" << std::endl;
//
//    std::cout << "After exchange" << std::endl;
}

void A10SPI::Disable()
{
    if (!this->isInitialized())
        return;

    // set SPI pins
    switch (this->_module)
    {
        case A10SPI::MODULE::SPI0:
            this->_gpio->select(A10::PIN::PI10, A10::PINMODE::Input); //CS0
            this->_gpio->select(A10::PIN::PI11, A10::PINMODE::Input); //CLK
            this->_gpio->select(A10::PIN::PI12, A10::PINMODE::Input); //MOSI
            this->_gpio->select(A10::PIN::PI13, A10::PINMODE::Input); //MISO
            this->_gpio->select(A10::PIN::PI14, A10::PINMODE::Input); //CS1
        break;

        case A10SPI::MODULE::SPI1:
        break;

        case A10SPI::MODULE::SPI2:
        break;

        case A10SPI::MODULE::SPI3:
        break;

        default:
            #if DEBUG > 1
                std::cout << "spi: module not valid." << std::endl;
            #endif
            return;
        break;
    }

    volatile uint32_t* CTRL = (volatile uint32_t *)( this->_spix_address );
    *(CTRL+2) &= ~1;
    #if DEBUG > 1
        std::cout << "spi: disabled." << std::endl;
    #endif
}

void A10SPI::SetAsMaster()
{
    this->_SetMODE(1);
}

void A10SPI::SetAsSlave()
{
    this->_SetMODE(0);
}

void A10SPI::SetPHA0()
{
    this->_SetPHA(0);
}

void A10SPI::SetPHA1()
{
    this->_SetPHA(1);
}

void A10SPI::SetPOL0()
{
    this->_SetPOL(0);
}

void A10SPI::SetSSPOL1()
{
    this->_SetSSPOL(1);
}

void A10SPI::SetSSPOL0()
{
    this->_SetSSPOL(0);
}

void A10SPI::SetSSCTLRemain()
{
    this->_SetSSCTL(0);
}

void A10SPI::SetSSCTLNegate()
{
    this->_SetSSCTL(1);
}

void A10SPI::SetDMANormal()
{
    this->_SetDMAMC(0);
}

void A10SPI::SetDMADedicated()
{
    this->_SetDMAMC(1);
}

void A10SPI::SetMTF()
{
    this->_SetLMTF(1);
}

void A10SPI::SetLTF()
{
    this->_SetLMTF(0);
}

void A10SPI::ResetRXFIFO()
{
    this->_SetRF_RST(1);
}

void A10SPI::ResetTXFIFO()
{
    this->_SetTF_RST(1);
}

void A10SPI::SetReadModeNormal()
{
    this->_SetRPSM(0);
}

void A10SPI::SetReadModeRapid()
{
    this->_SetRPSM(1);
}

void A10SPI::SetDummyBurstZero()
{
    this->_SetDDB(0);
}

void A10SPI::SetDummyBurstOne()
{
    this->_SetDDB(1);
}

void A10SPI::SetSSManual()
{
    this->_SetSS_CTRL(1);
}

void A10SPI::SetSSAutomatic()
{
    this->_SetSS_CTRL(0);
}

void A10SPI::SetSSHigh()
{
    this->_SetSS_LEVEL(1);
}

void A10SPI::SetSSLow()
{
    this->_SetSS_LEVEL(0);
}

void A10SPI::_SetMODE(uint8_t v)
{
    // if not initialized cancel.
    if (!this->isInitialized())
        return;

    // set value
    if (v > 0)
        *(this->_spix_address + A10SPI::CTRL) |= (0b1 << A10SPI::CTRL_REG__EN);
    else
        *(this->_spix_address + A10SPI::CTRL) &= ~(0b1 << A10SPI::CTRL_REG__EN);

}

void A10SPI::_SetPHA(uint8_t v)
{
    // if not initialized cancel.
    if (!this->isInitialized())
        return;

    // set value
    if (v > 0)
        *(this->_spix_address + A10SPI::CTRL) |= (0b1 << A10SPI::CTRL_REG__PHA);
    else
        *(this->_spix_address + A10SPI::CTRL) &= ~(0b1 << A10SPI::CTRL_REG__PHA);

}

void A10SPI::_SetPOL(uint8_t v)
{
    // if not initialized cancel.
    if (!this->isInitialized())
        return;

    // set value
    if (v > 0)
        *(this->_spix_address + A10SPI::CTRL) |= (0b1 << A10SPI::CTRL_REG__POL);
    else
        *(this->_spix_address + A10SPI::CTRL) &= ~(0b1 << A10SPI::CTRL_REG__POL);

}

void A10SPI::_SetSSPOL(uint8_t v)
{
    // if not initialized cancel.
    if (!this->isInitialized())
        return;

    // set value
    if (v > 0)
        *(this->_spix_address + A10SPI::CTRL) |= (0b1 << A10SPI::CTRL_REG__SSPOL);
    else
        *(this->_spix_address + A10SPI::CTRL) &= ~(0b1 << A10SPI::CTRL_REG__SSPOL);

}

void A10SPI::_SetDMAMC(uint8_t v)
{
    // if not initialized cancel.
    if (!this->isInitialized())
        return;

    // set value
    if (v > 0)
        *(this->_spix_address + A10SPI::CTRL) |= (0b1 << A10SPI::CTRL_REG__DMAMC);
    else
        *(this->_spix_address + A10SPI::CTRL) &= ~(0b1 << A10SPI::CTRL_REG__DMAMC);

}

void A10SPI::_SetLMTF(uint8_t v)
{
    // if not initialized cancel.
    if (!this->isInitialized())
        return;

    // set value
    if (v > 0)
        *(this->_spix_address + A10SPI::CTRL) |= (0b1 << A10SPI::CTRL_REG__LMTF);
    else
        *(this->_spix_address + A10SPI::CTRL) &= ~(0b1 << A10SPI::CTRL_REG__LMTF);

}

void A10SPI::_SetSSCTL(uint8_t v)
{
    // if not initialized cancel.
    if (!this->isInitialized())
        return;

    // set value
    if (v > 0)
        *(this->_spix_address + A10SPI::CTRL) |= (0b1 << A10SPI::CTRL_REG__SSCTL);
    else
        *(this->_spix_address + A10SPI::CTRL) &= ~(0b1 << A10SPI::CTRL_REG__SSCTL);

}

void A10SPI::_SetTF_RST(uint8_t v)
{
    // if not initialized cancel.
    if (!this->isInitialized())
        return;

    // set value
    if (v > 0)
        *(this->_spix_address + A10SPI::CTRL) |= (0b1 << A10SPI::CTRL_REG__TF_RST);
    else
        *(this->_spix_address + A10SPI::CTRL) &= ~(0b1 << A10SPI::CTRL_REG__TF_RST);

}

void A10SPI::_SetRF_RST(uint8_t v)
{
    // if not initialized cancel.
    if (!this->isInitialized())
        return;

    // set value
    if (v > 0)
        *(this->_spix_address + A10SPI::CTRL) |= (0b1 << A10SPI::CTRL_REG__RF_RST);
    else
        *(this->_spix_address + A10SPI::CTRL) &= ~(0b1 << A10SPI::CTRL_REG__RF_RST);

}

void A10SPI::_SetXCH(uint8_t v)
{
    // if not initialized cancel.
    if (!this->isInitialized())
        return;

    // set value
    if (v > 0)
        *(this->_spix_address + A10SPI::CTRL) |= (0b1 << A10SPI::CTRL_REG__XCH);
    else
        *(this->_spix_address + A10SPI::CTRL) &= ~(0b1 << A10SPI::CTRL_REG__XCH);

}

void A10SPI::_SetRPSM(uint8_t v)
{
    // if not initialized cancel.
    if (!this->isInitialized())
        return;

    // set value
    if (v > 0)
        *(this->_spix_address + A10SPI::CTRL) |= (0b1 << A10SPI::CTRL_REG__RPSM);
    else
        *(this->_spix_address + A10SPI::CTRL) &= ~(0b1 << A10SPI::CTRL_REG__RPSM);

}

void A10SPI::_SetSS(uint8_t v)
{
    // if not initialized cancel.
    if (!this->isInitialized())
        return;

    v &= 0b11;

    // set value
    if (v > 0)
        *(this->_spix_address + A10SPI::CTRL) |= (v << A10SPI::CTRL_REG__SS);
    else
        *(this->_spix_address + A10SPI::CTRL) &= ~(0b11 << A10SPI::CTRL_REG__SS);

}

void A10SPI::_SetDDB(uint8_t v)
{
    // if not initialized cancel.
    if (!this->isInitialized())
        return;

    // set value
    if (v > 0)
        *(this->_spix_address + A10SPI::CTRL) |= (0b1 << A10SPI::CTRL_REG__DDB);
    else
        *(this->_spix_address + A10SPI::CTRL) &= ~(0b1 << A10SPI::CTRL_REG__DDB);

}

void A10SPI::_SetDHB(uint8_t v)
{
    // if not initialized cancel.
    if (!this->isInitialized())
        return;

    // set value
    if (v > 0)
        *(this->_spix_address + A10SPI::CTRL) |= (0b1 << A10SPI::CTRL_REG__DHB);
    else
        *(this->_spix_address + A10SPI::CTRL) &= ~(0b1 << A10SPI::CTRL_REG__DHB);

}

void A10SPI::_SetSS_CTRL(uint8_t v)
{
    // if not initialized cancel.
    if (!this->isInitialized())
        return;

    // set value
    if (v > 0)
        *(this->_spix_address + A10SPI::CTRL) |= (0b1 << A10SPI::CTRL_REG__SS_CTRL);
    else
        *(this->_spix_address + A10SPI::CTRL) &= ~(0b1 << A10SPI::CTRL_REG__SS_CTRL);

}

void A10SPI::_SetSS_LEVEL(uint8_t v)
{
    // if not initialized cancel.
    if (!this->isInitialized())
        return;

    // set value
    if (v > 0)
        *(this->_spix_address + A10SPI::CTRL) |= (0b1 << A10SPI::CTRL_REG__SS_LEVEL);
    else
        *(this->_spix_address + A10SPI::CTRL) &= ~(0b1 << A10SPI::CTRL_REG__SS_LEVEL);

}

void A10SPI::_SetTP_EN(uint8_t v)
{
    // if not initialized cancel.
    if (!this->isInitialized())
        return;

    // set value
    if (v > 0)
        *(this->_spix_address + A10SPI::CTRL) |= (0b1 << A10SPI::CTRL_REG__TP_EN);
    else
        *(this->_spix_address + A10SPI::CTRL) &= ~(0b1 << A10SPI::CTRL_REG__TP_EN);

}

void A10SPI::_SetSDC(uint8_t v)
{
    // if not initialized cancel.
    if (!this->isInitialized())
        return;

    // set value
    if (v > 0)
        *(this->_spix_address + A10SPI::CTRL) |= (0b1 << A10SPI::CTRL_REG__SDC);
    else
        *(this->_spix_address + A10SPI::CTRL) &= ~(0b1 << A10SPI::CTRL_REG__SDC);

}

