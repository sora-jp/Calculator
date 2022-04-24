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
 * @file complex_additional_functions.hpp
 * @date 2007-04-09
 * Complex numbers additional functions:
 * acos, acosh, acot, acoth, asin, asinh, atan, atanh, cot, coth
 * INTERNAL HEADER ONLY, NOT TO BE USED DIRECTLY.
 */

#ifndef INCLUDED_BY_NACRE
    #error THIS IS AN INTERNAL HEADER ONLY, NOT TO BE USED DIRECTLY
#endif

#ifndef NACRE_COMPLEX_ADDITIONAL_FUNCTIONS
#define NACRE_COMPLEX_ADDITIONAL_FUNCTIONS

namespace nacre {
namespace complex {

/**
 * acos z = i acosh (z)
 */
template<typename T> inline Complex<T> acos (const Complex<T>& z) {
    Complex<T> x = acosh(z);
    return Complex<T>(-x.imag(), x.real());
}

/**
 * acosh (z) = log (z + sqrt(z^2-1) )
 */
template<typename T> inline Complex<T> acosh (const Complex<T>& z) {
    return log ( sqrt(z*z - T(1)) + z );
}

/**
 * acot z = i acoth (i z)
 */
template<typename T> inline Complex<T> acot (const Complex<T>& z) {
    Complex<T> x = acoth( Complex<T>(-z.imag(), z.real()) );
    return Complex<T>(-x.imag(), x.real());
}

/**
 * acoth (z) = 1/2 log (z+1)/(z-1)
 */
template<typename T> inline Complex<T> acoth (const Complex<T>& z) {
    return log ((z+T(1))/(z-T(1))) / T(2);
}

/**
 * asin z = -i asinh (i z)
 */
template<typename T> inline Complex<T> asin (const Complex<T>& z) {
    Complex<T> x = asinh( Complex<T>(-z.imag(), z.real()) );
    return Complex<T>(x.imag(), -x.real());
}

/**
 * asinh (z) = ln (z + sqrt(z^2+1) )
 */
template<typename T> inline Complex<T> asinh (const Complex<T>& z) {
    return log ( sqrt(z*z + T(1)) + z );
}

/**
 * atan z = -i atanh (i z)
 */
template<typename T> inline Complex<T> atan (const Complex<T>& z) {
    Complex<T> x = atanh( Complex<T>(-z.imag(), z.real()) );
    return Complex<T>(x.imag(), -x.real());
}

/**
 * atanh (z) = 1/2 log (1+z)/(1-z)
 */
template<typename T> inline Complex<T> atanh (const Complex<T>& z) {
    return log ((z+T(1))/(-z+T(1))) / T(2);
}

/**
 * cot z = cos (z) / sin (z)
 */
template<typename T> inline Complex<T> cot (const Complex<T>& z) {
    return cos(z) / sin(z);
}

/**
 * coth z = cosh (z) / sinh (z)
 */
template<typename T> inline Complex<T> coth (const Complex<T>& z) {
    return cosh(z) / sinh(z);
}

}     // namespace complex
}     // namespace nacre

#endif    // NACRE_COMPLEX_ADDITIONAL_FUNCTIONS
