#pragma once

#include <stdint.h>

namespace notes {

    typedef uint8_t KeyEvent;

    /* Pressed — 1/0; Octave — 0–7, Note — 0–11
     * So we have 1 byte for event type, 3 bytes for octave and 4 bytes for note */
    KeyEvent getKeyEvent(bool pressed, uint8_t octave, uint8_t note);


}