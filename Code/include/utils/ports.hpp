#pragma once
#include <avr/io.h>

namespace utils {
    enum class PORT : uint8_t {
        B, C, D
    };

    enum class PINMODE : bool {
        IN, OUT
    };


    inline volatile uint8_t& getPortDDR(const PORT& port) {
        if (port == PORT::B) {
            return DDRB;
        }
        if (port == PORT::C) {
            return DDRC;
        }
        if (port == PORT::D) {
            return DDRD;
        }
        __builtin_unreachable();
    }

    inline volatile uint8_t& getPortPORT(const PORT& port) {
        if (port == PORT::B) {
            return PORTB;
        }
        if (port == PORT::C) {
            return PORTC;
        }
        if (port == PORT::D) {
            return PORTD;
        }
        __builtin_unreachable();
    }

    inline volatile uint8_t& getPortPIN(const PORT& port) {
        if (port == PORT::B) {
            return PINB;
        }
        if (port == PORT::C) {
            return PINC;
        }
        if (port == PORT::D) {
            return PIND;
        }
        __builtin_unreachable();
    }

    // Pin is a pair (PORT, BIT). For example, (PORTB, 3) stands for PB3
    struct IOPin {
        PORT port;
        uint8_t bit;
    };

    inline void setPinMode(const IOPin& pin, const PINMODE& mode) {
        if (mode == PINMODE::OUT) {
            getPortDDR(pin.port) |= _BV(pin.bit);
        } else {
            getPortDDR(pin.port) &= ~_BV(pin.bit);
        }
    }

}
