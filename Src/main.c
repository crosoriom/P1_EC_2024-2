#include <stdint.h>
#include "systick.h"
#include "gpio.h"

int main(void)
{
    systick_init(3999);
    configure_gpio_input(GPIOC, PIN_13);
    configure_gpio_output(GPIOA, PIN_5);
    // configure_uart();

    // while(1){
    //     gpio_set_highLevel(GPIOA, PIN_5);
    // }
}
