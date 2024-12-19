#include <stdint.h>
#include "systick.h"
#include "syscfg.h"
#include "gpio.h"
#include "exti.h"

uint8_t state = 0;

int main(void)
{
    int actual_tick = 0;
    int blinkCounter = 0;
    systick_init(4000);
    configure_gpio_input(GPIOC, PIN_13);
    configure_gpio_input(GPIOC, PIN_12);
    configure_gpio_input(GPIOC, PIN_10);
    gpio_interrupt_enable(PIN_13, FALLING_EDGE);
    gpio_interrupt_enable(PIN_12, FALLING_EDGE);
    gpio_interrupt_enable(PIN_10, FALLING_EDGE);
    configure_gpio_output(GPIOA, PIN_5);
    configure_gpio_output(GPIOC, PIN_8);
    configure_gpio_output(GPIOC, PIN_6);
    exti_map();
    // configure_uart();

    while(1)
    {
        if(systick_getTick() - actual_tick >= 250) {
            gpio_toggle_level(GPIOA, PIN_5);
            actual_tick = systick_getTick();
        }
        switch (state) {
        case 0:
            gpio_set_lowLevel(GPIOC, PIN_8);
            gpio_set_lowLevel(GPIOC, PIN_6);
            break;
        case 1:
            if(systick_getTick() >= 500){
                gpio_toggle_level(GPIOC, PIN_8);
                gpio_toggle_level(GPIOC, PIN_6);
                systick_reset();
            }
            break;
        case 2:
            if(systick_getTick() >= 500){
                gpio_toggle_level(GPIOC, PIN_6);
                systick_reset();
            }
            break;
        case 3:
            if(systick_getTick() >= 500){
                gpio_toggle_level(GPIOC, PIN_8);
                systick_reset();
            }
            break;
        }
    }
}

void EXTI15_10_IRQHandler(void)
{
    if (EXTI->PR1 & (1 << 15))
        EXTI->PR1 = (1 << 15);
    if (EXTI->PR1 & (1 << 14))
        EXTI->PR1 = (1 << 14);
    if (EXTI->PR1 & (1 << 13)) {
        if(state != 1) {
            gpio_set_lowLevel(GPIOC, PIN_8);
            gpio_set_lowLevel(GPIOC, PIN_6);
            state = 1;
        }
        else
            state = 0;
        EXTI->PR1 = (1 << 13);
    }
    if (EXTI->PR1 & (1 << 12)) {
        if(state == 0)
            state = 2;
        else
            state = 0;
        EXTI->PR1 = (1 << 12);
    }
    if (EXTI->PR1 & (1 << 11))
        EXTI->PR1 = (1 << 11);
    if (EXTI->PR1 & (1 << 10)) {
        if(state == 0)
            state = 3;
        else
            state = 0;
        EXTI->PR1 = (1 << 10);
    }
}