//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

#ifndef BLINKLED_H_
#define BLINKLED_H_

#include "stm32f7xx.h"
#include "stm32f7xx_hal.h"

#define IPORTA 0
#define IPORTB 1
#define IPORTC 2
#define IPORTD 3
#define IPORTE 4
#define IPORTF 5
#define IPORTG 6
#define IPORTH 7
#define IPORTI 8
#define IPORTJ 9
#define IPORTK 10

void init_port_output(int gpioNumber, int pinNumber);

void init_port_input(int gpioNumber, int pinNumber);

void configure_ports_output(int gpioNumber, uint16_t PinsMask);

void configure_ports_input(int gpioNumber, uint16_t PinsMask);

void blink_led_on(int gpioNumber, int pinNumber);

void blink_led_off(int gpioNumber, int pinNumber);

void blink_systick_handler();

void virtual_led_port(uint8_t vport);

uint8_t virtual_switch_port();

void virtual_led_init();

void virtual_led_port(uint8_t vport);

#endif // BLINKLED_H_
