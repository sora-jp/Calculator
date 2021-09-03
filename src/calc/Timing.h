#pragma once
#include <chrono>
#include <functional>
#include "OpmNum.hpp"

long double Time(std::function<OpmNum(const OpmNum&)> fn, const OpmNum& min, const OpmNum& max, uint32_t iters = 1000);