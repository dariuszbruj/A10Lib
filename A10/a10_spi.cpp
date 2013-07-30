#include "a10_spi.h"
#include "debug.h"

#include <bitset>

A10::SPI::SPI()
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

A10::SPI::~SPI()
{
    //dtor
}

uint8_t A10::SPI::init(A10::GPIO *gpio)
{
	return this->init(gpio, A10::SPI::Module::SPI0);
}

uint8_t A10::SPI::init(A10::GPIO *gpio, A10::SPI::Module module)
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
        case A10::SPI::Module::SPI0:
            start  = A10::PA_SPI0_IO_BASE &  this->_page_mask;
            offset = A10::PA_SPI0_IO_BASE & ~this->_page_mask;

            // get pages count for SPIx register.
            this->_spix_size = ((unsigned int)(A10::PA_SPI0_IO_SIZE / this->_page_size)+1)*this->_page_size;

            #if DEBUG > 1
                std::cout << "spi: selected SPI0" << std::endl;
            #endif

            break;
        case A10::SPI::Module::SPI1:
            start  = A10::PA_SPI1_IO_BASE &  this->_page_mask;
            offset = A10::PA_SPI1_IO_BASE & ~this->_page_mask;

            // get pages count for SPIx register.
            this->_spix_size = ((unsigned int)(A10::PA_SPI0_IO_SIZE / this->_page_size)+1)*this->_page_size;

            #if DEBUG > 1
                std::cout << "spi: selected SPI1" << std::endl;
            #endif

            break;
        case A10::SPI::Module::SPI2:
            start  = A10::PA_SPI2_IO_BASE &  this->_page_mask;
            offset = A10::PA_SPI2_IO_BASE & ~this->_page_mask;

            // get pages count for SPIx register.
            this->_spix_size = ((unsigned int)(A10::PA_SPI0_IO_SIZE / this->_page_size)+1)*this->_page_size;

            #if DEBUG > 1
                std::cout << "spi: selected SPI2" << std::endl;
            #endif

            break;
        case A10::SPI::Module::SPI3:
            start  = A10::PA_SPI3_IO_BASE &  this->_page_mask;
            offset = A10::PA_SPI3_IO_BASE & ~this->_page_mask;

            // get pages count for SPIx register. (the sa
            this->_spix_size = ((unsigned int)(A10::PA_SPI0_IO_SIZE / this->_page_size)+1)*this->_page_size;

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

	_map = (volatile void*) mmap( 0, this->_spix_size, (PROT_READ | PROT_WRITE), MAP_SHARED, mem_fd, start);

	if (MAP_FAILED == _map)
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
	this->_spix_address = (volatile uintptr_t *) ( (uintptr_t)_map + offset);

	// DISPLAY VALUES
	#if DEBUG > 1
		std::cout << "spi: map " << (void*)_map << std::endl;
		std::cout << "spi: SPIx " << (void*) this->_spix_address  << std::endl;
	#endif

	this->_isInitialized = 1;

	return 0;
}

uint8_t  A10::SPI::isInitialized()
{
	return this->_isInitialized;
}

void A10::SPI::Enable()
{
    if (!this->isInitialized())
        return;

    // set SPI pins
    switch (this->_module)
    {
        case A10::SPI::Module::SPI0:
            this->_gpio->select(A10::GPIO::Pin::PI10, A10::GPIO::PinSelect::Alt1); //CS0
            this->_gpio->select(A10::GPIO::Pin::PI11, A10::GPIO::PinSelect::Alt1); //CLK
            this->_gpio->select(A10::GPIO::Pin::PI12, A10::GPIO::PinSelect::Alt1); //MOSI
            this->_gpio->select(A10::GPIO::Pin::PI13, A10::GPIO::PinSelect::Alt1); //MISO
            this->_gpio->select(A10::GPIO::Pin::PI14, A10::GPIO::PinSelect::Alt1); //CS1
        break;

        case A10::SPI::Module::SPI1:
        break;

        case A10::SPI::Module::SPI2:
        break;

        case A10::SPI::Module::SPI3:
        break;

        default:
            #if DEBUG > 1
                std::cout << "spi: module not valid." << std::endl;
            #endif
            return;
        break;
    }

    //
    volatile uintptr_t* SPI_CTRL = (volatile uintptr_t *)((uint32_t)this->_spix_address + this->_SPI_CTRL);

    std::cout << " SPI_CTRL " << (void*) SPI_CTRL << std::endl;
    std::cout << " SPI_CTRL " << *((uint32_t*) SPI_CTRL) << std::endl;

    std::bitset<32> b(*SPI_CTRL);

    for(int i = 0; i < 16; i++)
    {
        SPI_CTRL = (volatile uint32_t *)((uint32_t)this->_spix_address + i*4);
        b = *SPI_CTRL;

        std::cout << (void*) SPI_CTRL << " " << b.to_string() << std::endl;
    }

    //std::cout << b.to_string() << std::endl;

}

void A10::SPI::Disable()
{
    if (!this->isInitialized())
        return;

    // set SPI pins
    switch (this->_module)
    {
        case A10::SPI::Module::SPI0:
            this->_gpio->select(A10::GPIO::Pin::PI10, A10::GPIO::PinSelect::Input); //CS0
            this->_gpio->select(A10::GPIO::Pin::PI11, A10::GPIO::PinSelect::Input); //CLK
            this->_gpio->select(A10::GPIO::Pin::PI12, A10::GPIO::PinSelect::Input); //MOSI
            this->_gpio->select(A10::GPIO::Pin::PI13, A10::GPIO::PinSelect::Input); //MISO
            this->_gpio->select(A10::GPIO::Pin::PI14, A10::GPIO::PinSelect::Input); //CS1
        break;

        case A10::SPI::Module::SPI1:
        break;

        case A10::SPI::Module::SPI2:
        break;

        case A10::SPI::Module::SPI3:
        break;

        default:
            #if DEBUG > 1
                std::cout << "spi: module not valid." << std::endl;
            #endif
            return;
        break;
    }

    //std::cout << b.to_string() << std::endl;

}
