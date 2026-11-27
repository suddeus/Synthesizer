#include <avr_lib/protocols/spi.hpp>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/power.h>

int main() {
    clock_prescale_set(clock_div_1);

    spi::Master spi;

    uint8_t counter = 1;
    while (1) {
        uint8_t data = rand();
        data <<= 4;

        data |= counter;
        ++counter;
        if (counter == 0x10) {
            counter = 0;
        }

        spi.transfer(data);
        _delay_ms(1000);
    }

    return 0;
}
