#pragma once

#include <stdint.h>
#include <avr/io.h>
#include <avr_lib/utils/ports.hpp>

namespace spi {

    // Use PB3 as MOSI, PB4 as MISO, PB5 as SCK and PB2 as CS
    class Master {
    public:
        Master();

        uint8_t transfer(uint8_t data) const;
    private:
        utils::IOPin _cs{.port = utils::PORT::B, .bit = 2};
        utils::IOPin _mosi{.port = utils::PORT::B, .bit = 3};
        utils::IOPin _miso{.port = utils::PORT::B, .bit = 4};
        utils::IOPin _sck{.port = utils::PORT::B, .bit = 5};

        void init() const;
    };

}