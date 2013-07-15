
/***
 * 
 * Author: Dariusz Bruj (dariusz.bruj@gmail.com)
 * 
 * This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/.
 * 
 * */

#include "debug.h"

#include "a10_gpio.h"
#include "a10_memorymap.h"

A10::GPIO::GPIO()
{

	// Set to uninitialized
	this->_isInitialized = 0;

	// Set default pointer
	_gpio_address = nullptr;

	// get platform page size 
	this->_page_size = sysconf(_SC_PAGESIZE);
	// get platform page mask
	this->_page_mask  = (~(this->_page_size-1));
    // get pages size for this register.
	this->_gpio_size = ((unsigned int)(PA_PORTC_IO_SIZE / this->_page_size)+1)*this->_page_size;
}

A10::GPIO::~GPIO()
{

	// UNMAP MEMORY
	munmap((void*) this->_map, _gpio_size);//
    _map = MAP_FAILED;

    //set to uninitialized.
    this->_isInitialized = 0;

	#if DEBUG > 1
		std::cout << "unmap ok" << std::endl;
	#endif
}

uint32_t A10::GPIO::init()
{
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

	start  = PA_PORTC_IO_BASE &  this->_page_mask;
	offset = PA_PORTC_IO_BASE & ~this->_page_mask;

	#if DEBUG > 1
		std::cout << "start: " << (void*) start << std::endl;
		std::cout << "offset: " << (void*) offset << std::endl;
	#endif

	_map = (volatile void*) mmap( 0, this->_gpio_size, (PROT_READ | PROT_WRITE), MAP_SHARED, mem_fd, start);

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
	this->_gpio_address = (volatile uintptr_t *) ( (uintptr_t)_map + offset);
	
	// DISPLAY VALUES
	#if DEBUG > 1
		std::cout << "map: " << (void*)_map << std::endl;
		std::cout << "GPIO: " << (void*) this->_gpio_address  << std::endl;
	#endif
	
	this->_isInitialized = 1;

	return 0;
}

uint8_t  A10::GPIO::isInitialized()
{
	return this->_isInitialized;
}

void 	 A10::GPIO::toggle(uint8_t port, uint8_t number)
{
	if (!this->_isInitialized)
		return;
	
	volatile uintptr_t* DAT = this->_gpio_address + port*9 + 4; 		// port*0x24 + 0x10

	#if DEBUG
		// display address
		std::cout << "TOOGLE " << (int)port << ":" << (int)number << std::endl;
		std::cout << "DAT: " << (void*) DAT << std::endl;
	#endif

	// toogle bit.
	*DAT ^= 1 << number;

}

void 	 A10::GPIO::toggle(A10::GPIO::PortPin portpin)
{
	if (!this->_isInitialized)
		return;
		
    this->toogle((uint16_t) portpin >> 8, (uint16_t) portpin & 0xFF);
}


void 	 A10::GPIO::toggle_f(volatile uint32_t *DATREG, uint32_t PIN)
{
	// Toggle port.
	*DATREG ^= PIN;	
}

volatile uint32_t *	A10::GPIO::datareg(uint8_t port)
{
	// Get DAT register for selected port.
	return this->_gpio_address + port*9 + 4; 
}

volatile uint32_t *	A10::GPIO::datareg(A10::GPIO::PortPin portpin)
{
	// Get DAT register for selected port.
	return this->datareg(this->portnum(portpin)); 
}

uint8_t		A10::GPIO::portnum(PortPin portpin)
{
	return ((uint8_t) portpin >> 8);
}

uint8_t		A10::GPIO::pinnum(PortPin portpin)
{
	return ((uint8_t) portpin & 0xFF);
}


uint8_t  A10::GPIO::read(uint8_t port, uint8_t number)
{
	if (!this->_isInitialized)
		return -1;
		
	volatile uintptr_t* DAT = this->_gpio_address + port*9 + 4; 		// port*0x24 + 0x10

	#if DEBUG
		// display address
		std::cout << "READ " << (int)port << ":" << (int)number << std::endl;
		std::cout << "DAT: " << (void*) DAT << std::endl;
	#endif

	// toogle bit.
    return (*DAT & ( 1 << number) ) >> number;
}

uint8_t  A10::GPIO::read(A10::GPIO::PortPin portpin)
{
	if (!this->_isInitialized)
		return -1;
		
	return this->read((uint16_t) portpin >> 8, (uint16_t) portpin & 0xFF);
}

void 	 A10::GPIO::write(uint8_t port, uint8_t number, uint8_t value)
{
	if (!this->_isInitialized)
		return;
		
	volatile uintptr_t* DAT = this->_gpio_address + port*9 + 4; 		// port*0x24 + 0x10

	#if DEBUG
		// display address
		std::cout << "WRITE " << (int)port << ":" << (int)number << std::endl;
		std::cout << "DAT: " << (void*) DAT << std::endl;
	#endif

    if (value > 0)
        // set 1
        *DAT |= 1 << number;
    else
        // set 0
        *DAT &= ~(1 << number);
}

void 	 A10::GPIO::write(A10::GPIO::PortPin portpin, uint8_t value)
{
	if (!this->_isInitialized)
		return;
		
    this->write((uint16_t) portpin >> 8, (uint16_t) portpin & 0xFF, value);
}

void	 A10::GPIO::clear(uint8_t port, uint8_t number)
{
	if (!this->_isInitialized)
		return;
		
	volatile uintptr_t* DAT = this->_gpio_address + port*9 + 4; 		// port*0x24 + 0x10

	#if DEBUG
		// display address
		std::cout << "CLEAR " << (int)port << ":" << (int)number << std::endl;
		std::cout << "DAT: " << (void*) DAT << std::endl;
	#endif

	*DAT &= ~(1 << number);
}

void	 A10::GPIO::clear(A10::GPIO::PortPin portpin)
{
	if (!this->_isInitialized)
		return;
		
	this->clear((uint16_t) portpin >> 8, (uint16_t) portpin & 0xFF);
}

void 	 A10::GPIO::select(uint8_t port, uint8_t number, uint8_t mode)
{
	if (!this->_isInitialized)
		return;
		
	volatile uintptr_t* CFG = this->_gpio_address + port*9 + 4*(number%8); 		// port*0x24 + offset (0x0, 0x4, 0x8, 0xC)

	#if DEBUG
		// display address
		std::cout << "SELECT " << (int)port << ":" << (int)number << std::endl;
		std::cout << "CFG: " << (void*) CFG << std::endl;
	#endif

	*CFG &= ~( 0x7 << (number%8)*4);
	*CFG |= mode << (number%8)*4;
}

void 	 A10::GPIO::select(A10::GPIO::PortPin portpin, PinSelect mode)
{
	if (!this->_isInitialized)
		return;
		
    this->select((uint16_t) portpin >> 8, (uint16_t) portpin & 0xFF, (uint8_t) mode);
}
