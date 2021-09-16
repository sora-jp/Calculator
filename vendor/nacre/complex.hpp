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
 * @file complex.hpp
 * @date 2007-04-09
 * Complex numbers implementation.
 * Based on the GNU ISO C++ Library implementation by Gabriel Dos Reis.
 */

#ifndef NACRE_COMPLEX
#define NACRE_COMPLEX

#define NACRE_STD_COMPLEX_CONVERSION

#ifdef NACRE_STD_COMPLEX_CONVERSION
    #include <complex>
#endif

#include <iostream>

namespace nacre {
namespace complex {

template<typename T> class Complex {
private:
    T re_, im_;

public:
    Complex (const T& = T(), const T& = T());
    template<typename T2> Complex(const Complex<T2>&);

#ifdef NACRE_STD_COMPLEX_CONVERSION
    template<typename T2> Complex(const std::complex<T2>&);
    template<typename T2> operator std::complex<T2>() const;
#endif

    T real() const;
    T imag() const;

    Complex& operator=  (const T&);
    Complex& operator+= (const T&);
    Complex& operator-= (const T&);
    Complex& operator*= (const T&);
    Complex& operator/= (const T&);

    template<typename T2> Complex<T>& operator=  (const Complex<T2>&);
    template<typename T2> Complex<T>& operator+= (const Complex<T2>&);
    template<typename T2> Complex<T>& operator-= (const Complex<T2>&);
    template<typename T2> Complex<T>& operator*= (const Complex<T2>&);
    template<typename T2> Complex<T>& operator/= (const Complex<T2>&);
};

//------------------------------------------------------------

template<typename T> inline T Complex<T>::real() const { return re_; }
template<typename T> inline T Complex<T>::imag() const { return im_; }

//------------------------------------------------------------

template<typename T> inline Complex<T>::Complex (const T& re, const T& im)
        : re_(re), im_(im) {}

template<typename T> template<typename T2>
Complex<T>::Complex(const Complex<T2>& z)
        : re_(z.real()), im_(z.imag()) {}

//------------------------------------------------------------

#ifdef NACRE_STD_COMPLEX_CONVERSION
template<typename T> template<typename T2> inline
Complex<T>::Complex(const std::complex<T2>& z)
        : re_(z.real()), im_(z.imag()) {}
template<typename T> template<typename T2>
Complex<T>::operator std::complex<T2>() const {
    return std::complex<T2> (real(), imag());
}
#endif

//------------------------------------------------------------

template<typename T> Complex<T>& Complex<T>::operator=(const T& t) {
    re_ = t;
    im_ = T(0);
    return *this;
}

template<typename T> inline Complex<T>& Complex<T>::operator+=(const T& t) {
    re_ += t;
    return *this;
}

template<typename T> inline Complex<T>& Complex<T>::operator-=(const T& t) {
    re_ -= t;
    return *this;
}

template<typename T> inline Complex<T>& Complex<T>::operator*=(const T& t) {
    re_ *= t;
    im_ *= t;
    return *this;
}

template<typename T> inline Complex<T>& Complex<T>::operator/=(const T& t) {
    re_ /= t;
    im_ /= t;
    return *this;
}

//------------------------------------------------------------

template<typename T> template<typename T2>
Complex<T>& Complex<T>::operator=(const Complex<T2>& z) {
    re_ = z.real();
    im_ = z.imag();
    return *this;
}

template<typename T> template<typename T2>
Complex<T>& Complex<T>::operator+=(const Complex<T2>& z) {
    re_ += z.real();
    im_ += z.imag();
    return *this;
}

template<typename T> template<typename T2>
Complex<T>& Complex<T>::operator-=(const Complex<T2>& z) {
    re_ -= z.real();
    im_ -= z.imag();
    return *this;
}

template<typename T> template<typename T2>
Complex<T>& Complex<T>::operator*=(const Complex<T2>& z) {
    const T r = re_ * z.real() - im_ * z.imag();
    im_ = re_ * z.imag() + im_ * z.real();
    re_ = r;
    return *this;
}

template<typename T> template<typename T2>
Complex<T>& Complex<T>::operator/=(const Complex<T2>& z) {
    const T r =  re_ * z.real() + im_ * z.imag();
    const T n = norm(z);
    im_ = (im_ * z.real() - re_ * z.imag()) / n;
    re_ = r / n;
    return *this;
}

//------------------------------------------------------------

template<typename T> inline Complex<T> operator+(const Complex<T>& x,
        const Complex<T>& y) {
    return Complex<T> (x) += y;
}

template<typename T> inline Complex<T> operator+(const Complex<T>& x,
        const T& y) {
    return Complex<T> (x) += y;
}

template<typename T> inline Complex<T> operator+(const T& x,
        const Complex<T>& y) {
    return Complex<T> (y) += x;
}

template<typename T> inline Complex<T> operator-(const Complex<T>& x,
        const Complex<T>& y) {
    return Complex<T> (x) -= y;
}

template<typename T> inline Complex<T> operator-(const Complex<T>& x,
        const T& y) {
    return Complex<T> (x) -= y;
}

template<typename T> inline Complex<T> operator-(const T& x,
        const Complex<T>& y) {
    return Complex<T> (x) -= y;
}

template<typename T> inline Complex<T> operator*(const Complex<T>& x,
        const Complex<T>& y) {
    return Complex<T> (x) *= y;
}

template<typename T> inline Complex<T> operator*(const Complex<T>& x,
        const T& y) {
    return Complex<T> (x) *= y;
}

template<typename T> inline Complex<T> operator*(const T& x,
        const Complex<T>& y) {
    return Complex<T> (y) *= x;
}

template<typename T> inline Complex<T> operator/(const Complex<T>& x,
        const Complex<T>& y) {
    return Complex<T> (x) /= y;
}

template<typename T> inline Complex<T> operator/(const Complex<T>& x,
        const T& y) {
    return Complex<T> (x) /= y;
}

template<typename T> inline Complex<T> operator/(const T& x,
        const Complex<T>& y) {
    return Complex<T> (x) /= y;
}

template<typename T> inline Complex<T> operator+(const Complex<T>& x) {
    return x;
}

template<typename T> inline Complex<T> operator-(const Complex<T>& x) {
    return Complex<T>(-x.real(), -x.imag());
}

//------------------------------------------------------------

template<typename T> inline bool operator==(const Complex<T>& x,
        const Complex<T>& y) {
    return x.real() == y.real() && x.imag() == y.imag();
}

template<typename T> inline bool operator==(const Complex<T>& x, const T& y) {
    return x.real() == y && x.imag() == T(0);
}

template<typename T> inline bool operator==(const T& x, const Complex<T>& y) {
    return x == y.real() && T(0) == y.imag();
}

template<typename T> inline bool operator!=(const Complex<T>& x,
        const Complex<T>& y) {
    return x.real() != y.real() || x.imag() != y.imag();
}

template<typename T> inline bool operator!=(const Complex<T>& x, const T& y) {
    return x.real() != y || x.imag() != T(0);
}

template<typename T> inline bool operator!= (const T& x, const Complex<T>& y) {
    return x != y.real() || T(0) != y.imag();
}

//------------------------------------------------------------

template<typename T, typename CharT, class Traits>
std::basic_istream<CharT, Traits>&
operator>>(std::basic_istream<CharT, Traits>& is, Complex<T>& x) {
    T re_x, im_x;
    CharT ch;
    is >> ch;
    if (ch == '(') {
        is >> re_x >> ch;
        if (ch == ',') {
            is >> im_x >> ch;
            if (ch == ')')
                x = Complex<T>(re_x, im_x);
            else
                is.setstate(std::ios_base::failbit);
        }
        else if (ch == ')')
            x = Complex<T>(re_x, T(0));
        else
            is.setstate(std::ios_base::failbit);
    }
    else {
        is.putback(ch);
        is >> re_x;
        x = Complex<T>(re_x, T(0));
    }
    return is;
}

template<typename T, typename CharT, class Traits>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, const Complex<T>& x) {
    std::basic_ostringstream<CharT, Traits> s;
    s.flags(os.flags());
    s.imbue(os.getloc());
    s.precision(os.precision());
    s << '(' << x.real() << ',' << x.imag() << ')';
    return os << s.str();
}

//------------------------------------------------------------

template<typename T> inline T real (const Complex<T>& z) {
    return z.real();
}

template<typename T> inline T imag (const Complex<T>& z) {
    return z.imag();
}

//------------------------------------------------------------

}     // namespace complex
}     // namespace nacre

#define INCLUDED_BY_NACRE
    #include "complex_functions.hpp"
    #include "complex_additional_functions.hpp"
#undef INCLUDED_BY_NACRE

#endif    // NACRE_COMPLEX
