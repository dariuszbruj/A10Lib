
/***
 *
 * Author: Dariusz Bruj (dariusz.bruj@gmail.com)
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/.
 *
 * */

#ifndef A10_H
#define A10_H

#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <cstdint>

#include "a10_gpio.h"
#include "a10_spi.h"
#include "a10_memorymap.h"

namespace A10
{
	class A10Lib
	{

		private:
			/// Is library initialized?
			uint8_t _isInitialized;

		public:
			/*
			 * Main constructor.
			 * */
			A10Lib();

			/*
			 * Main destructor.
			 * */
			virtual ~A10Lib();

			/*
			 * Initialize all interface modules
			 * */
			uint8_t init();

			/*
			 * A GPIO interface.
			 * */
			A10::GPIO* gpio;

			/*
			 * A SPI interface.
			 * */
			A10::SPI* spi0;

	};
}
#endif // A10_H
