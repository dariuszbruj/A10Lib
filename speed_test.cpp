
/***
 * 
 * Author: Dariusz Bruj (dariusz.bruj@gmail.com)
 * 
 * This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/.
 * 
 * */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>

#include <iostream>
#include <bitset>

//#include "A10/A10.h"


int main2(int argc, char **argv)
{
	// GET MEMORY FILE
	int mem_fd = -1;

	if ((mem_fd = open("/dev/mem", O_RDWR | O_SYNC) ) < 0)
    {
		fprintf(stderr, "A10.init: Unable to open /dev/mem: %s\n", strerror(errno)) ;

		std::cout << "mem_fd failed" << std::endl;
		//exit(-1);
    }
	std::cout << "mem_fd ok" << std::endl;

	// MAP DATA
	unsigned int start, offset;
	unsigned int PageSize, PageMask;

	PageSize = sysconf(_SC_PAGESIZE);
	PageMask = (~(PageSize-1));

	start  = 0x01c20800 &  PageMask;
	offset = 0x01c20800 & ~PageMask;

	std::cout << "start: " << (void*) start << std::endl;
	std::cout << "offset: " << (void*) offset << std::endl;

	volatile unsigned int*  map = (volatile unsigned int*) mmap( 0 , PageSize*2 , (PROT_READ | PROT_WRITE), MAP_SHARED, mem_fd , start);

	if (MAP_FAILED == map)
	{
		std::cout << "mmap failed" << std::endl;
		exit(-2);
	}

	std::cout << "mmap ok" << std::endl;

    close(mem_fd);

	// DISPLAY VALUES
	std::cout << "map: " << (void*) map << std::endl;
	volatile unsigned int *GPIO = (volatile unsigned int *) ( (unsigned int)map + offset);

	// print GPIO to screen
	std::cout << "GPIO: " << (void*) GPIO << std::endl;

	// Set PD0 config and data
	volatile unsigned int *PD_CFG0 = (volatile unsigned int *)(GPIO + 27); // 6c = 108/sizeof(int)= 124/4 = 27
	volatile unsigned int *PD_DAT  = (volatile unsigned int *)(GPIO + 31); // 7c = 124; 124/sizeof(int)= 124/4 = 31

	// Set bitsets
	std::bitset<3> c = (uint32_t)PD_CFG0 & ~(0x7);
	std::bitset<1> d = (uint32_t)PD_DAT  & ~(0x1);

	// Display data
	std::cout << "Address: " << (void*) PD_CFG0 << " PD0 config: " << c.to_string() << " status: " << d.to_string() << std::endl;
	std::cout << "Address: " << (void*) PD_DAT  << " PD0 config: " << c.to_string() << " status: " << d.to_string() << std::endl;

    int n =0;
	unsigned int DATA_PIN_N = (0x1 << n);

	// Set PD0 As output.
	*PD_CFG0 &= ~(0x7); // Clear bits.
	*PD_CFG0 |= 0x1;	// Set as output.

	// Test changes.
	//for(;;)
	{
	    char a;
        (*PD_DAT) |=   DATA_PIN_N;		// Ustaw pin
        std::cin >> a;
   		(*PD_DAT) &= ~(DATA_PIN_N);		// Skasuj pin
    }

	// UNMAP MEMORY
	munmap((void*) map, 4096);//
    //map = MAP_FAILED;

	std::cout << "unmap ok" << std::endl;
	return 0;

}
