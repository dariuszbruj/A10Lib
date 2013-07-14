
/***
 * 
 * Author: Dariusz Bruj (dariusz.bruj@gmail.com)
 * 
 * This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/.
 * 
 * */

#ifndef A10_GPIO_H
#define A10_GPIO_H

#include "a10_memorymap.h"

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

	class GPIO
	{
		private:
	
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

			// get pages size for this register.
			uint32_t       _gpio_size;


		public:

			/*
			 * Main constructor.
			 * */
			GPIO();

			/*
			 * Main destructor.
			 * */
			~GPIO();

			/*
			 * Initialize GPIO.
			 */
			uint32_t 	init();

			/*
			 * Checks if this module is intiialized.
			 * */
			uint8_t		isInitialized();

			/*
			 * Available ports on this chips.
			 * */
			enum class Port : uint8_t {
				PA = 0,
				PB = 1,
				PC = 2,
				PD = 3,
				PE = 4,
				PF = 4,
				PG = 6,
				PH = 7,
				PI = 8
			 };

			/*
			 * Available pins on this chip.
			 * */
			enum class PortPin  : uint16_t {
				PA0 = 0b0000000000000000,
				PA1 = 0b0000000000000001,
				PA2 = 0b0000000000000010,
				PA3 = 0b0000000000000011,
				PA4 = 0b0000000000000100,
				PA5 = 0b0000000000000101,
				PA6 = 0b0000000000000110,
				PA7 = 0b0000000000000111,
				PA8 = 0b0000000000001000,
				PA9 = 0b0000000000001001,
				PA10 = 0b0000000000001010,
				PA11 = 0b0000000000001011,
				PA12 = 0b0000000000001100,
				PA13 = 0b0000000000001101,
				PA14 = 0b0000000000001110,
				PA15 = 0b0000000000001111,
				PA16 = 0b0000000000010000,
				PA17 = 0b0000000000010001,
				PB0 = 0b0000000100000000,
				PB1 = 0b0000000100000001,
				PB2 = 0b0000000100000010,
				PB3 = 0b0000000100000011,
				PB4 = 0b0000000100000100,
				PB5 = 0b0000000100000101,
				PB6 = 0b0000000100000110,
				PB7 = 0b0000000100000111,
				PB8 = 0b0000000100001000,
				PB9 = 0b0000000100001001,
				PB10 = 0b0000000100001010,
				PB11 = 0b0000000100001011,
				PB12 = 0b0000000100001100,
				PB13 = 0b0000000100001101,
				PB14 = 0b0000000100001110,
				PB15 = 0b0000000100001111,
				PB16 = 0b0000000100010000,
				PB17 = 0b0000000100010001,
				PB18 = 0b0000000100010010,
				PB19 = 0b0000000100010011,
				PB20 = 0b0000000100010100,
				PB21 = 0b0000000100010101,
				PB22 = 0b0000000100010110,
				PB23 = 0b0000000100010111,
				PC0 = 0b0000001000000000,
				PC1 = 0b0000001000000001,
				PC2 = 0b0000001000000010,
				PC3 = 0b0000001000000011,
				PC4 = 0b0000001000000100,
				PC5 = 0b0000001000000101,
				PC6 = 0b0000001000000110,
				PC7 = 0b0000001000000111,
				PC8 = 0b0000001000001000,
				PC9 = 0b0000001000001001,
				PC10 = 0b0000001000001010,
				PC11 = 0b0000001000001011,
				PC12 = 0b0000001000001100,
				PC13 = 0b0000001000001101,
				PC14 = 0b0000001000001110,
				PC15 = 0b0000001000001111,
				PC16 = 0b0000001000010000,
				PC17 = 0b0000001000010001,
				PC18 = 0b0000001000010010,
				PC19 = 0b0000001000010011,
				PC20 = 0b0000001000010100,
				PC21 = 0b0000001000010101,
				PC22 = 0b0000001000010110,
				PC23 = 0b0000001000010111,
				PC24 = 0b0000001000011000,
				PD0 = 0b0000001100000000,
				PD1 = 0b0000001100000001,
				PD2 = 0b0000001100000010,
				PD3 = 0b0000001100000011,
				PD4 = 0b0000001100000100,
				PD5 = 0b0000001100000101,
				PD6 = 0b0000001100000110,
				PD7 = 0b0000001100000111,
				PD8 = 0b0000001100001000,
				PD9 = 0b0000001100001001,
				PD10 = 0b0000001100001010,
				PD11 = 0b0000001100001011,
				PD12 = 0b0000001100001100,
				PD13 = 0b0000001100001101,
				PD14 = 0b0000001100001110,
				PD15 = 0b0000001100001111,
				PD16 = 0b0000001100010000,
				PD17 = 0b0000001100010001,
				PD18 = 0b0000001100010010,
				PD19 = 0b0000001100010011,
				PD20 = 0b0000001100010100,
				PD21 = 0b0000001100010101,
				PD22 = 0b0000001100010110,
				PD23 = 0b0000001100010111,
				PD24 = 0b0000001100011000,
				PD25 = 0b0000001100011001,
				PD26 = 0b0000001100011010,
				PD27 = 0b0000001100011011,
				PE0 = 0b0000010000000000,
				PE1 = 0b0000010000000001,
				PE2 = 0b0000010000000010,
				PE3 = 0b0000010000000011,
				PE4 = 0b0000010000000100,
				PE5 = 0b0000010000000101,
				PE6 = 0b0000010000000110,
				PE7 = 0b0000010000000111,
				PE8 = 0b0000010000001000,
				PE9 = 0b0000010000001001,
				PE10 = 0b0000010000001010,
				PE11 = 0b0000010000001011,
				PF0 = 0b0000010100000000,
				PF1 = 0b0000010100000001,
				PF2 = 0b0000010100000010,
				PF3 = 0b0000010100000011,
				PF4 = 0b0000010100000100,
				PF5 = 0b0000010100000101,
				PG0 = 0b0000011000000000,
				PG1 = 0b0000011000000001,
				PG2 = 0b0000011000000010,
				PG3 = 0b0000011000000011,
				PG4 = 0b0000011000000100,
				PG5 = 0b0000011000000101,
				PG6 = 0b0000011000000110,
				PG7 = 0b0000011000000111,
				PG8 = 0b0000011000001000,
				PG9 = 0b0000011000001001,
				PG10 = 0b0000011000001010,
				PG11 = 0b0000011000001011,
				PH0 = 0b0000011100000000,
				PH1 = 0b0000011100000001,
				PH2 = 0b0000011100000010,
				PH3 = 0b0000011100000011,
				PH4 = 0b0000011100000100,
				PH5 = 0b0000011100000101,
				PH6 = 0b0000011100000110,
				PH7 = 0b0000011100000111,
				PH8 = 0b0000011100001000,
				PH9 = 0b0000011100001001,
				PH10 = 0b0000011100001010,
				PH11 = 0b0000011100001011,
				PH12 = 0b0000011100001100,
				PH13 = 0b0000011100001101,
				PH14 = 0b0000011100001110,
				PH15 = 0b0000011100001111,
				PH16 = 0b0000011100010000,
				PH17 = 0b0000011100010001,
				PH18 = 0b0000011100010010,
				PH19 = 0b0000011100010011,
				PH20 = 0b0000011100010100,
				PH21 = 0b0000011100010101,
				PH22 = 0b0000011100010110,
				PH23 = 0b0000011100010111,
				PH24 = 0b0000011100011000,
				PH25 = 0b0000011100011001,
				PH26 = 0b0000011100011010,
				PH27 = 0b0000011100011011,
				PI0 = 0b0000100000000000,
				PI1 = 0b0000100000000001,
				PI2 = 0b0000100000000010,
				PI3 = 0b0000100000000011,
				PI4 = 0b0000100000000100,
				PI5 = 0b0000100000000101,
				PI6 = 0b0000100000000110,
				PI7 = 0b0000100000000111,
				PI8 = 0b0000100000001000,
				PI9 = 0b0000100000001001,
				PI10 = 0b0000100000001010,
				PI11 = 0b0000100000001011,
				PI12 = 0b0000100000001100,
				PI13 = 0b0000100000001101,
				PI14 = 0b0000100000001110,
				PI15 = 0b0000100000001111,
				PI16 = 0b0000100000010000,
				PI17 = 0b0000100000010001,
				PI18 = 0b0000100000010010,
				PI19 = 0b0000100000010011,
				PI20 = 0b0000100000010100,
				PI21 = 0b0000100000010101
			};

			/*
			 * Available select modes for pins
			 * */
			enum class PinSelect : uint8_t {
				Input  	= 0, // 000
				Output  = 1, // 001
				Alt1	= 2, // 010
				Alt2	= 3, // 011
				Alt3	= 4, // 100
				Alt4	= 5, // 101
				Alt5	= 6, // 110
				Alt6	= 7  // 111
			};

			/*
			 * Single port.
			 * */

			/*
			 * Reads value of the pin from DAT register.
			 * */
			uint8_t 	read  (PortPin portpin);

			/*
			 * Write a pin's state into DAT register.
			 * Value equal or more then 1 - sets 1 to register, otherwise sets 0.
			 * */
			void 		write (PortPin portpin, uint8_t value);

			/*
			 * Set pin to 0 in DAT register.
			 * */
			void 		clear (PortPin portpin);

			/*
			 * Changes state to opposite (1->0, 0->1).
			 * */
			void		toogle(PortPin portpin);

			/*
			 * Changes select mode for pin. Writes mode into CFG register.
			 * */
			void 		select(PortPin portpin, PinSelect mode);

			/*
			 * Single port.
			 * */
			uint8_t 	read  (uint8_t port, uint8_t number);
			void 		write (uint8_t port, uint8_t number, uint8_t value);
			void 		clear (uint8_t port, uint8_t number);
			void		toogle(uint8_t port, uint8_t number);
			void 		select(uint8_t port, uint8_t number, uint8_t mode);

			void 		pull_level (uint8_t port, uint8_t number, uint8_t mode);
			void 		drive_level(uint8_t port, uint8_t number, uint8_t mode);

	};

}
#endif
