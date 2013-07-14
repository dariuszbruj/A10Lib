
/***
 * 
 * Author: Dariusz Bruj (dariusz.bruj@gmail.com)
 * 
 * This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/.
 * 
 * */

#include "a10.h"

A10::A10Lib::A10Lib()
{
	// set to uninitialized
	_isInitialized = 0;
}

A10::A10Lib::~A10Lib()
{
}

uint8_t A10::A10Lib::init()
{
	#if DEBUG
		std::cout << "A10Lib::init()" << std::endl;
	#endif
	
	uint8_t isSuccess = 0;

	if (this->_isInitialized)
		isSuccess = 1;

	// init GPIO.
	if (isSuccess == 0)
		if (!gpio.isInitialized())
			isSuccess |= gpio.init() << 1;

	
	if (isSuccess == 0)
	{
		_isInitialized = 1;
		#if DEBUG
			std::cout << "A10Lib::init() : Success." << std::endl;
		#endif
	} else {
		
		// TODO: ustawić funkcje odinicjującą.
		#if DEBUG
			std::cout << "A10Lib::init() : GPIO init status = " << (int) isSuccess << std::endl;
		#endif
	}
		
	
	// Successful.
	return isSuccess;
}
