/* This file is part of the NACRE Library.

  Copyright (c) 2006 -- 2007 Alexey V. Beshenov <bav.272304@gmail.com>.

  The NACRE Library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation; either version 2.1 of the
  License, or (at your option) any later version.

  The NACRE Library is distributed in the hope that it will be
  useful, but WITHOUT ANY WARRANTY; without even the implied warranty
  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with the NACRE Library; see the file COPYING.LIB. If
  not, write to the Free Software Foundation, Inc., 51 Franklin Street,
  Fifth Floor, Boston, MA 02110-1301, USA. */

/**
 * @file fp_comparator.hpp
 * @date 2007-04-09
 * Comparison of two floating point numbers respecting to some epsilon,
 * machine epsilon by default.
 * OPTIONAL HEADER, INCLUDE ONLY IF NEEDED.
 */

#ifndef NACRE_FP_COMPARATOR
#define NACRE_FP_COMPARATOR

#include <cmath> // std::numeric_limits<T>::epsilon()
#include <limits> // std::abs(epsilon)

namespace nacre {
namespace comparator {

/**
 * Comparison of two floating point numbers
 * respecting to some epsilon, machine epsilon by default.
 */

template<typename T> class FpComparator {
    T epsilon_;

public:
    FpComparator (const T& epsilon = std::numeric_limits<T>::epsilon())
    throw () : epsilon_(std::abs(epsilon)) {}

    T& getEpsilon () throw() { return epsilon_; }
    const T& getEpsilon () const throw() { return epsilon_; }

    void setEpsilon (const T& epsilon) throw() {
        epsilon_ = std::abs(epsilon);
    }

    /**
     * Ternary.
     * +1 if x > y,
     *  0 if x = y,
     * -1 if x < y.
     */
    int operator () (const T& x, const T& y) {
        T diff = x - y;
        if (std::abs(diff) >= epsilon_) {
            return diff > T(0) ? 1 : -1;
        }
        return 0; // std::abs(diff) < epsilon_
    }
};

}     // namespace comparator
}     // namespace nacre

#endif    // NACRE_FP_COMPARATOR
