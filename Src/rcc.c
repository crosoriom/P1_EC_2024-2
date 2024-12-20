#include "rcc.h"

#define RCC ((ResetClockControl_t *)0x40021000UL)

void gpio_activate(uint8_t gpio)
{
	if(gpio == 0xFF)
		return;
	RCC->AHB2ENR |= (0x1 << gpio);
}