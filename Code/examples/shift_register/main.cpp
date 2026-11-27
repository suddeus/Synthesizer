#include <avr_lib/shift_register.hpp>

#include <util/delay.h>
#include <avr/power.h>

int main() {
    clock_prescale_set(clock_div_1);

    sr::ShiftRegister shift_register (
        {.port = utils::PORT::C, .bit = 5},
        {.port = utils::PORT::C, .bit = 4},
        {.port = utils::PORT::C, .bit = 3},
        {.port = utils::PORT::C, .bit = 2},
        {.port = utils::PORT::C, .bit = 1}
    );

    uint8_t index = 0;

    while (true) {
        index = (index == 7 ? 0 : index + 1);
        shift_register.writeByte(_BV(index));
        _delay_ms(100000);
    }

    __builtin_unreachable();
    // return 0;
}