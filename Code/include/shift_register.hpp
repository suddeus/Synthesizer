// For 74HC595

#pragma once

#include <stdint.h>
#include <utils/ports.hpp>

namespace sr {

    class ShiftRegister {
    public:
        ShiftRegister() = delete;

        ShiftRegister(utils::IOPin ser, utils::IOPin oe, utils::IOPin rclk, utils::IOPin srclk, utils::IOPin srclr);

        void clear() const;

        void writeByte(uint8_t data) const;

    private:
        utils::IOPin _ser;   // Serial input
        utils::IOPin _oe;    // Output enable
        utils::IOPin _rclk;  // Register clock
        utils::IOPin _srclk; // Serial clock
        utils::IOPin _srclr; // Serial clear

        void init() const;
    };

}