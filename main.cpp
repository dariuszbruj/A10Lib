
/***
 * 
 * Author: Dariusz Bruj (dariusz.bruj@gmail.com)
 * 
 * This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/.
 * 
 * */

#include <iostream>

#include "A10/debug.h"
#include "A10/a10.h"

int main(int argc, char **argv)
{

	std::cout << "A10Lib ver. 0.1" << std::endl;

	// Create object.
	A10::A10Lib a10;

	// Initialize all modules.
	if (a10.init() > 0)
	{
		std::cout << " Cannot initialize A10::A10Lib." << std::endl;
		return 1;
	}

	// Ustaw jako output.
	a10.gpio.select(A10::GPIO::PortPin::PD0, A10::GPIO::PinSelect::Output);

    for(;;)
        a10.gpio.toogle(A10::GPIO::PortPin::PD0);

	return 0;

}
