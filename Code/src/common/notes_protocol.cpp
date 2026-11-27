#include <common/notes_protocol.hpp>

namespace notes {
    KeyEvent getKeyEvent(const bool pressed, const uint8_t octave, const uint8_t note) {
        KeyEvent result = 0;

        result |= pressed ? 0x80 : 0;
        result |= (octave & 0x07) << 4;
        result |= (note & 0x0F);

        return result;
    }
}