#include <stdint.h>
#include "systick.h"
#include "gpio.h"

int main(void)
{
    uint8_t state = 0;
    systick_init(4000);
    // configure_gpio_input(GPIOC, PIN_13);
    configure_gpio_output(GPIOA, PIN_5);
    // configure_uart();

    while(1)
    {
        switch(state) {
        case 0:
            if(systick_getTick() >= 500)
                state = 1;
            break;
        case 1:
            gpio_toggle_level(GPIOA, PIN_5);
            systick_reset();
            state = 0;
            break;
        }
    }
}
