#include <avr_lib/protocols/spi.hpp>

namespace spi {
    Master::Master() {
        init();
    }

    void Master::init() const {
        utils::getPortPORT(_cs.port) |= _BV(_cs.bit); // Disable chip select

        utils::setPinMode(_cs, utils::PINMODE::OUT);
        utils::setPinMode(_mosi, utils::PINMODE::OUT);
        utils::setPinMode(_sck, utils::PINMODE::OUT);
        utils::setPinMode(_miso, utils::PINMODE::IN);

        SPSR = 0; // Disable double speed
        SPCR = _BV(SPE) | _BV(MSTR) | _BV(SPR0);  // CPU clock / 16.
    }


    uint8_t Master::transfer(const uint8_t data) const {
        utils::getPortPORT(_cs.port) &= ~_BV(_cs.bit); // Enable chip select

        SPDR = data;
        while (!(SPSR & _BV(SPIF))) {} // Wait until sending
        const uint8_t result = SPDR;

        utils::getPortPORT(_cs.port) |= _BV(_cs.bit); // Disable chip select

        return result;
    }
}
