#pragma once
#include "../Config.h"
#include "../OpmNum.hpp"

// THIS FILE WAS AUTOMATICALLY GENERATED
// CHANGES WILL BE LOST UPON REGENERATION

namespace Constants {
extern const OpmNum ln10;
extern const OpmNum ln2;
extern const OpmNum e;
extern const OpmNum pi;
extern const OpmNum half_pi;
extern const OpmNum quart_pi;
extern const OpmNum tau;
extern const OpmNum one;
extern const OpmNum one_half;
constexpr OpmNum nan = OpmNum(false, true, false);
constexpr OpmNum inf = OpmNum(false, false, true);
constexpr OpmNum ninf = OpmNum(true, false, true);
}
namespace Tables {
extern const OpmNum lnTable[];
extern const OpmNum atanTable[];
}
