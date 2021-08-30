#pragma once

//#include "pgmspace.h"
#include <cstdint>
#include <utility>

extern const uint16_t _mulTable[];
extern const uint16_t _mtRowStarts[];

inline uint16_t MultiplyByte(const uint8_t a, const uint8_t b) {
    if (!a || !b) return 0;
    uint8_t na = a, nb = b;
    if (na > nb) std::swap(na, nb);
    return _mulTable[_mtRowStarts[na] + nb - na];
}