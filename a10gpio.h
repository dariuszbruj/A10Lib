/* 
 * File:   a10gpio.h
 * Author: dbruj
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/.
 *
 * Created on 18 październik 2013, 18:35
 */

#ifndef A10GPIO_H
#define	A10GPIO_H

#include "a10.h"

   /*
    * A GPIO Class.
    * */
   class A10GPIO
   {
      
   private:

          // a PIO pointer
          volatile uintptr_t* _gpio_address;

          // address of mapped memory
          volatile void*      _map;

          // is PIO initialized ?
          uint8_t             _isInitialized;
          
          // memory page size
          uint32_t            _page_size;

          // a page mask used to get an offset of main address
          uint32_t            _page_mask;

          // get pages size for this register.
          uint32_t            _gpio_size;

          // set friends
          friend class A10SPI;

   public:
      
          /*
           * Main constructor.
           * */
          A10GPIO();

          /*
           * Main destructor.
           * */
          ~A10GPIO();

          /*
           * Initialize GPIO.
           */
          uint32_t 	init();

          /*
           * Checks if this module is intiialized.
           * */
          uint8_t		isInitialized();

          /*
           * Single port.
           * */

          /*
           * Reads value of the pin from DAT register.
           * */
          uint8_t 	read  (A10::PIN portpin);

          /*
           * Write a pin's state into DAT register.
           * Value equal or more then 1 - sets 1 to register, otherwise sets 0.
           * */
          void 		write (A10::PIN portpin, uint8_t value);

          /*
           * Set pin to 0 in DAT register.
           * */
          void 		clear (A10::PIN portpin);

          /*
           * Changes state to opposite (1->0, 0->1).
           * */
          void       toggle(A10::PIN portpin);

          /*
           * Changes select mode for pin. Writes mode into CFG register.
           * */
          void 		select(A10::PIN portpin, A10::PINMODE mode);

   private:
          /*
           * Single port.
           * */
          uint8_t 	read  (uint16_t port, uint16_t number);
          void 		write (uint16_t port, uint16_t number, uint8_t value);
          void 		clear (uint16_t port, uint16_t number);
          void       toggle(uint16_t port, uint16_t number);
          void 		select(uint16_t port, uint16_t number, uint8_t mode);

          // NOT IMPLEMENTED
          void 		pull_level (uint8_t port, uint8_t number, uint8_t mode);
          void 		drive_level(uint8_t port, uint8_t number, uint8_t mode);

          // FAST TOGGLE
          void			toggle_f(volatile uint32_t *DATREG, uint32_t PIN);
          volatile uint32_t *	datareg(uint16_t port);
          volatile uint32_t *	datareg(A10::PIN portpin);

          // GET PORT OR PIN NUMBER FROM A10::PIN enum.
          uint16_t		portnum(A10::PIN portpin);
          uint16_t		pinnum(A10::PIN portpin);

      private:

          /*
           * Set SPI pins.
           * */

          // TODO: pins blocking
          //void SetSPI0();
          //void SetSPI1();
          //void SetSPI2();
          //void SetSPI3();
          //void SetSPIS(A10::PIN portpin ss, A10::PIN portpin clk, A10::PIN portpin mosi, A10::PIN portpin miso);

   };


#endif	/* A10GPIO_H */

