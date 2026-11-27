#include <avr_lib/shift_register.hpp>

namespace sr {
    ShiftRegister::ShiftRegister(
        const utils::IOPin ser,
        const utils::IOPin oe,
        const utils::IOPin rclk,
        const utils::IOPin srclk,
        const utils::IOPin srclr)
        : _ser(ser), _oe(oe), _rclk(rclk), _srclk(srclk), _srclr(srclr) {
        init();
    }

    void ShiftRegister::clear() const {
        utils::getPortPORT(_srclr.port) &= ~_BV(_srclr.bit);
        utils::getPortPORT(_srclr.port) |= _BV(_srclr.bit);
    }

    void ShiftRegister::writeByte(uint8_t data) const {
        for (int i = 0; i < 8; ++i) {
            data & 1
                ? getPortPORT(_ser.port) |= _BV(_ser.bit)
                : getPortPORT(_ser.port) &= ~_BV(_ser.bit);
            data >>= 1;
            utils::getPortPORT(_srclk.port) |= _BV(_srclk.bit);
            utils::getPortPORT(_srclk.port) &= ~_BV(_srclk.bit);
        }
        utils::getPortPORT(_rclk.port) |= _BV(_rclk.bit);
        utils::getPortPORT(_rclk.port) &= ~_BV(_rclk.bit);
    }

    void ShiftRegister::init() const {
        utils::setPinMode(_ser, utils::PINMODE::OUT);
        utils::setPinMode(_oe, utils::PINMODE::OUT);
        utils::setPinMode(_rclk, utils::PINMODE::OUT);
        utils::setPinMode(_srclk, utils::PINMODE::OUT);
        utils::setPinMode(_srclr, utils::PINMODE::OUT);

        clear();

        utils::getPortPORT(_oe.port) &= ~_BV(_oe.bit);
    }
}
