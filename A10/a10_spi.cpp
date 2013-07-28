#include "a10_spi.h"
#include "debug.h"

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
    if (!gpio->isInitialized())
        return 1;

    this->_gpio = gpio;

    // GET MEMORY FILE
	int mem_fd = -1;

	if ((mem_fd = open("/dev/mem", O_RDWR | O_SYNC) ) < 0)
    {
		#if DEBUG > 1
			std::cout << "mem_fd failed" << std::endl;
		#endif
		// Return error code.
		return 1;
    }

	#if DEBUG > 1
		std::cout << "mem_fd ok" << std::endl;
	#endif

	// MAP DATA
	unsigned int start, offset;

	start  = A10::PA_SPI0_IO_BASE &  this->_page_mask;
	offset = A10::PA_SPI0_IO_BASE & ~this->_page_mask;

	#if DEBUG > 1
		std::cout << "start: " << (void*) start << std::endl;
		std::cout << "offset: " << (void*) offset << std::endl;
	#endif

    // get pages count for SPIx register.
	this->_spix_size = ((unsigned int)(A10::PA_SPI0_IO_SIZE / this->_page_size)+1)*this->_page_size;

	_map = (volatile void*) mmap( 0, this->_spix_size, (PROT_READ | PROT_WRITE), MAP_SHARED, mem_fd, start);

	if (MAP_FAILED == _map)
	{
		#if DEBUG > 1
			std::cout << "mmap failed" << std::endl;
		#endif

		return 2;
	}

	#if DEBUG > 1
		std::cout << "mmap ok" << std::endl;
	#endif

    close(mem_fd);

	// SET GPIO offset ADDRESS.
	this->_spix_address = (volatile uintptr_t *) ( (uintptr_t)_map + offset);

	// DISPLAY VALUES
	#if DEBUG > 1
		std::cout << "map: " << (void*)_map << std::endl;
		std::cout << "SPIx: " << (void*) this->_spix_address  << std::endl;
	#endif

	this->_isInitialized = 1;

	return 0;

}

uint8_t  A10::SPI::isInitialized()
{
	return this->_isInitialized;
}

