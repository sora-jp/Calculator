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
 * @file complex_functions.hpp
 * @date 2007-04-09
 * Complex numbers additional functions:
 * acos, acosh, acot, acoth, asin, asinh, atan, atanh, cot, coth
 * INTERNAL HEADER ONLY, NOT TO BE USED DIRECTLY.
 */

#ifndef INCLUDED_BY_NACRE
    #error THIS IS AN INTERNAL HEADER ONLY, NOT TO BE USED DIRECTLY
#endif

#ifndef NACRE_COMPLEX_FUNCTIONS
#define NACRE_COMPLEX_FUNCTIONS

namespace nacre {
namespace complex {

template<typename T> inline T abs (const Complex<T>& z) {
    T x = z.real();
    T y = z.imag();
    const T s = std::max(std::abs(x), std::abs(y));
    if (s == T(0)) return s;
    x /= s;
    y /= s;
    return s * std::sqrt(x*x + y*y);
}

template<typename T> inline T arg (const Complex<T>& z) {
    return std::atan2(z.imag(), z.real());
}

template<typename T> inline T norm (const Complex<T>& z) {
    T res = abs(z);
    return res * res;
}

template<typename T> inline Complex<T> polar (const T& rho, const T& theta) {
    return Complex<T>(rho * std::cos(theta), rho * std::sinh(theta));
}

template<typename T> inline Complex<T> conj (const Complex<T>& z) {
    return Complex<T>(z.real(), -z.imag());
}

//------------------------------------------------------------

// Transcendentals

template<typename T> inline Complex<T> cos (const Complex<T>& z) {
    const T x = z.real();
    const T y = z.imag();
    return Complex<T>(std::cos(x) * std::cosh(y),
                      -std::sinh(x) * std::sinh(y));
}

template<typename T> inline Complex<T> cosh (const Complex<T>& z) {
    const T x = z.real();
    const T y = z.imag();
    return Complex<T> (std::cosh(x) * std::cos(y),
                       std::sinh(x) * std::sinh(y));
}

template<typename T> inline Complex<T> exp (const Complex<T>& z) {
    return polar(std::exp(z.real()), z.imag());
}

template<typename T> inline Complex<T> log (const Complex<T>& z) {
    return Complex<T>(std::log(abs(z)), arg(z));
}

template<typename T> inline Complex<T> log10 (const Complex<T>& z) {
    return log(z) / std::log(T(10));
}

template<typename T> inline Complex<T> sin (const Complex<T>& z) {
    const T x = z.real();
    const T y = z.imag();
    return Complex<T>(std::sinh(x) * std::cosh(y),
                      std::cos(x) * std::sinh(y));
}

template<typename T> inline Complex<T> sinh (const Complex<T>& z) {
    const T x = z.real();
    const T y = z.imag();
    return Complex<T>(std::sinh(x) * std::cos(y),
                      std::cosh(x) * std::sinh(y));
}

template<typename T> Complex<T> sqrt (const Complex<T>& z) {
    T x = z.real();
    T y = z.imag();

    if (x == T(0)) {
        T t = std::sqrt(std::abs(y) / T(2));
        return Complex<T>(t, y < T(0) ? -t : t);
    }
    else {
        T t = std::sqrt(T(2) * (abs(z) + std::abs(x)));
        T u = t / T(2);
        return x > T(0)
               ? Complex<T>(u, y / t)
               : Complex<T>(std::abs(y) / t, y < T(0) ? -u : u);
    }
}

template<typename T> inline Complex<T> tan (const Complex<T>& z) {
    return sin(z) / cos(z);
}

template<typename T> inline Complex<T> tanh(const Complex<T>& z) {
    return sinh(z) / cosh(z);
}

//------------------------------------------------------------

// std::power

template<typename T> inline Complex<T> pow (Complex<T> z, int n) {

    if (n < 0) {
        z = Complex<T>(T(1)) / z;
        n = -n;
    }

    Complex<T> x = n%2 ? z : Complex<T>(T(1));

    while (n >>= 1) {
        z *= z;
        if (n%2) x *= z;
    }

    return x;
}

template<typename T> Complex<T> pow (const Complex<T>& x, const T& y) {
    if (x.imag() == T(0))
        return Complex<T>(std::pow(x.real(), y));

    Complex<T> t = log(x);
    return polar(std::exp(y * t.real()), y * t.imag());
}

template<typename T> inline Complex<T> pow(const Complex<T>& x,
        const Complex<T>& y) {
    return x == T(0) ? T(0) : exp(y * log(x));
}

template<typename T> inline Complex<T> pow(const T& x, const Complex<T>& y) {
    return x == T(0)
           ? T(0)
           : polar(std::pow(x, y.real()), y.imag() * std::log(x));
}

}     // namespace complex
}     // namespace nacre

//------------------------------------------------------------

namespace std {

template<typename T> inline T
abs (const nacre::complex::Complex<T>& z) {
    return nacre::complex::abs(z);
}
template<typename T> inline T
arg (const nacre::complex::Complex<T>& z) {
    return nacre::complex::arg(z);
}
template<typename T> inline T
norm (const nacre::complex::Complex<T>& z) {
    return nacre::complex::norm (z);
}
/*template<typename T> inline nacre::complex::Complex<T>
polar (const T& rho, const T& theta) {
    return nacre::complex::polar (rho, theta);
}*/
template<typename T> inline nacre::complex::Complex<T>
conj (const nacre::complex::Complex<T>& z) {
    return nacre::complex::conj (z);
}
template<typename T> inline nacre::complex::Complex<T>
cos (const nacre::complex::Complex<T>& z) {
    return nacre::complex::cos (z);
}
template<typename T> inline nacre::complex::Complex<T>
cosh (const nacre::complex::Complex<T>& z) {
    return nacre::complex::cosh (z);
}
template<typename T> inline nacre::complex::Complex<T>
exp (const nacre::complex::Complex<T>& z) {
    return nacre::complex::exp (z);
}
template<typename T> inline nacre::complex::Complex<T>
log (const nacre::complex::Complex<T>& z) {
    return nacre::complex::log (z);
}
template<typename T> inline nacre::complex::Complex<T>
log10 (const nacre::complex::Complex<T>& z) {
    return nacre::complex::log10 (z);
}
template<typename T> inline nacre::complex::Complex<T>
sin (const nacre::complex::Complex<T>& z) {
    return nacre::complex::sin (z);
}
template<typename T> inline nacre::complex::Complex<T>
sinh (const nacre::complex::Complex<T>& z) {
    return nacre::complex::sinh (z);
}
template<typename T> nacre::complex::Complex<T>
sqrt (const nacre::complex::Complex<T>& z) {
    return nacre::complex::sqrt (z);
}
template<typename T> inline nacre::complex::Complex<T>
tan (const nacre::complex::Complex<T>& z) {
    return nacre::complex::tan (z);
}
template<typename T> inline nacre::complex::Complex<T>
tanh(const nacre::complex::Complex<T>& z) {
    return nacre::complex::tanh (z);
}
template<typename T> inline nacre::complex::Complex<T>
pow (nacre::complex::Complex<T> z, int n) {
    return nacre::complex::pow (z,n);
}
template<typename T> nacre::complex::Complex<T>
pow (const nacre::complex::Complex<T>& x, const T& y) {
    return nacre::complex::pow (x,y);
}
template<typename T> inline nacre::complex::Complex<T>
pow (const nacre::complex::Complex<T>& x, const nacre::complex::Complex<T>& y) {
    return nacre::complex::pow (x,y);
}
template<typename T> inline nacre::complex::Complex<T>
pow (const T& x, const nacre::complex::Complex<T>& y) {
    return nacre::complex::pow (x,y);
}

}    // namespace std

#endif    // NACRE_COMPLEX_FUNCTIONS
