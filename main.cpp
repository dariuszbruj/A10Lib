/***
 *
 * Author: Dariusz Bruj (dariusz.bruj@gmail.com)
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/.
 *
 * */

#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <string.h>

#include "A10/debug.h"
#include "A10/a10.h"

int main(int argc, char **argv)
{

	// Set max priority (will make system choke, but you get signal more stable ~1.85Mhz).

    //struct sched_param sp;
	//memset(&sp, 0, sizeof(sp));
	//sp.sched_priority = sched_get_priority_max(SCHED_FIFO);
	//sched_setscheduler(0, SCHED_FIFO, &sp);
	//mlockall(MCL_CURRENT | MCL_FUTURE);


    // Displaying welcome text.
	std::cout << "A10Lib ver. 0.1" << std::endl;

	// Create object.
	A10::A10Lib a10;

	// Initialize all modules.
	if (a10.init() > 0)
	{
		std::cout << " Cannot initialize A10::A10Lib." << std::endl;
		return 1;
	}

	std::cout << " Select PD0 as an output." << std::endl;
	// Set pin as an output.
	a10.gpio->select(A10::GPIO::Pin::PD0, A10::GPIO::PinSelect::Output);

	// Fast toggle
	std::cout << " Toggle PD0 pin." << std::endl;
	volatile uint32_t* 	DAT = a10.gpio->datareg(A10::GPIO::Pin::PD0);
	uint32_t 			PIN = 0x1 << a10.gpio->pinnum(A10::GPIO::Pin::PD0);

//    for(;;)
//        //a10.gpio.toggle_f(DAT, PIN); // or more directly
//        *DAT ^= PIN;

    a10.spi0->Enable();

    a10.spi0->Disable();


	return 0;

}
