#pragma once
#include <chrono>
#include <functional>
#include "OpmNum.hpp"

std::chrono::duration<double, std::milli> Time(std::function<OpmNum(const OpmNum&)> fn, const OpmNum& min, const OpmNum& max, uint32_t iters = 1000);