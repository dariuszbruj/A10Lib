/* 
 * File:   main.cpp
 * Author: dbruj
 *
 * Created on 18 październik 2013, 17:34
 * 
 * skrzaty są super!
 */

#include <cstdlib>
#include <iostream>

#include "a10.h"
#include "a10gpio.h"

using namespace std;

/*
 * Main function.
 */
int main(int argc, char** argv) {

    // Zadeklaruj zmienną.
    A10* a10;
    
    // Utwórz zmienną
    a10 = new A10;
    
    // Zainicjum A10.
    a10->init();
    
    //a10->gpio->select(A10::PIN::PD10, A10::PINMODE::Output);
    a10->gpio->toggle(A10::PIN::PH21);
    a10->gpio->toggle(A10::PIN::PH20);
    
    // Usuń nieużywaną już zmienną.
    delete a10;
    
    return 0;
}

