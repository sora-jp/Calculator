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

inline uint64_t MultiplyByteWide(const uint32_t a, const uint32_t b) {
    return static_cast<uint64_t>(MultiplyByte(static_cast<uint8_t>(a) & 0xff, static_cast<uint8_t>(b) & 0xff));
}