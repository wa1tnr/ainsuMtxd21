#include "common.h"
#include "getKey.h"
#include "driver_examples.h"

uint8_t pos = 0;

void printing(void) {
    uint8_t ch_read = (uint32_t) ch[0];

    if (ch_read == 13) {
        _spc(); // do not print a cr here!
    } else {
        if (ch_read != 32) { // a space delimiter
            io_write(io, (uint8_t *) ch, 1);
        } else { // it's a space
            _spc();
        }
    }
}

void throw_(void) { }

uint8_t reading(void) {
    getKey();
    printing();
    uint8_t ch_read = (uint32_t) ch[0];
    if (ch_read == '\r') return 0; // return 0: move onto the next word
    if (ch_read == ' ')  return 0;
    if (ch_read == '\010') { // backspace
        _spc();
        io_write(io, (uint8_t *) "\010", 1);
        return 1; // return 1: make the 'while (reading())' last a while longer!
    }
    return 1; // ain't done yett..
}

void readword(void) {
    pos = 0;
    tib[0] = 0;
    while (reading());
}