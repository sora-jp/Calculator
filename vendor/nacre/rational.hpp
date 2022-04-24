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
 * @file rational.hpp
 * @date 2007-04-12
 * General rational class.
 */

#ifndef NACRE_RATIONAL
#define NACRE_RATIONAL

#include <cmath>

namespace nacre {
namespace rational {

template<typename I> I GcdEuclid (I u, I v) {
    I r;
    for (;;) {
        if (v == static_cast<I>(0)) return u;
        r = u%v; u=v; v=r;
    }
}

//------------------------------------------------------

template<typename T> class Rational {

    T num_, den_;
    void normalize ();

public:

    Rational ();
    template<typename I> Rational (const I& num, const I& den = T(1));
    template<typename I> Rational (const Rational<I>&);

    const T& num () const;
    const T& den () const;
    T& num ();
    T& den ();

    template<typename F> operator F () const;

    template<typename I> Rational<T>& operator+= (const I&);
    template<typename I> Rational<T>& operator-= (const I&);
    template<typename I> Rational<T>& operator*= (const I&);
    template<typename I> Rational<T>& operator/= (const I&);

    template<typename I> Rational<T>& operator=  (const Rational<I>&);
    template<typename I> Rational<T>& operator+= (const Rational<I>&);
    template<typename I> Rational<T>& operator-= (const Rational<I>&);
    template<typename I> Rational<T>& operator*= (const Rational<I>&);
    template<typename I> Rational<T>& operator/= (const Rational<I>&);
};

//------------------------------------------------------

template<typename T> Rational<T>::Rational ()
        : num_ (T(0)), den_ (T(1)) {}

template<typename T> template<typename I>
Rational<T>::Rational (const I& num, const I& den)
        : num_ (T(num)), den_ (T(den)) {
    normalize();
}

template<typename T> template<typename I>
Rational<T>::Rational (const Rational<I>& r)
        : num_ (T(r.num())), den_ (T(r.den())) {}

//------------------------------------------------------

template<typename T> const T& Rational<T>::num () const {
    return num_;
}
template<typename T> const T& Rational<T>::den () const {
    return den_;
}
template<typename T> T& Rational<T>::num () {
    return num_;
}
template<typename T> T& Rational<T>::den () {
    return den_;
}

//------------------------------------------------------

template<typename T> template<typename F> Rational<T>::operator F () const {
    return F(num())/F(den());
}

//------------------------------------------------------

template<typename T> template<typename I>
Rational<T>& Rational<T>::operator+= (const I& n) {
    den() = n*den() + num();
    normalize();
    return *this;
}

template<typename T> template<typename I>
Rational<T>& Rational<T>::operator-= (const I& n) {
    den() = n*den() - num();
    normalize();
    return *this;
}

template<typename T> template<typename I>
Rational<T>& Rational<T>::operator*= (const I& n) {
    den() *= n;
    normalize();
    return *this;
}

template<typename T> template<typename I>
Rational<T>& Rational<T>::operator/= (const I& n) {
    den() /= n;
    normalize();
    return *this;
}

//------------------------------------------------------

template<typename T> template<typename I>
Rational<T>& Rational<T>::operator= (const Rational<I>& r) {
    num() = r.num();
    den() = r.den();
    return *this;
}

template<typename T> template<typename I>
Rational<T>& Rational<T>::operator+= (const Rational<I>& r) {
    num() = num()*r.den() + r.num()*den();
    den() *= r.den();
    normalize();
    return *this;
}

template<typename T> template<typename I>
Rational<T>& Rational<T>::operator-= (const Rational<I>& r) {
    num() = num()*r.den() - r.num()*den();
    den() *= r.den();
    normalize();
    return *this;
}

template<typename T> template<typename I>
Rational<T>& Rational<T>::operator*= (const Rational<I>& r) {
    num() *= r.num();
    den() *= r.den();
    normalize();
    return *this;
}

template<typename T> template<typename I>
Rational<T>& Rational<T>::operator/= (const Rational<I>& r) {
    num() *= r.den();
    den() *= r.num();
    normalize();
    return *this;
}

//------------------------------------------------------

template<typename T> inline Rational<T> operator+(const Rational<T>& r1,
        const Rational<T>& r2) {
    return Rational<T> (r1) += r2;
}

template<typename T> inline Rational<T> operator+(const Rational<T>& r,
        const T& n) {
    return Rational<T> (r) += n;
}

template<typename T> inline Rational<T> operator+(const T& n,
        const Rational<T>& r) {
    return Rational<T> (r) += n;
}

template<typename T> inline Rational<T> operator-(const Rational<T>& r1,
        const Rational<T>& r2) {
    return Rational<T> (r1) -= r2;
}

template<typename T> inline Rational<T> operator-(const Rational<T>& r,
        const T& n) {
    return Rational<T> (r) -= n;
}

template<typename T> inline Rational<T> operator-(const T& n,
        const Rational<T>& r) {
    return Rational<T> (n) -= r;
}

template<typename T> inline Rational<T> operator*(const Rational<T>& r1,
        const Rational<T>& r2) {
    return Rational<T> (r1) *= r2;
}

template<typename T> inline Rational<T> operator*(const Rational<T>& r,
        const T& n) {
    return Rational<T> (r) *= n;
}

template<typename T> inline Rational<T> operator*(const T& n,
        const Rational<T>& r) {
    return Rational<T> (r) *= n;
}

template<typename T> inline Rational<T> operator/(const Rational<T>& r1,
        const Rational<T>& r2) {
    return Rational<T> (r1) /= r2;
}

template<typename T> inline Rational<T> operator/(const Rational<T>& r,
        const T& n) {
    return Rational<T> (r) /= n;
}

template<typename T> inline Rational<T> operator/(const T& n,
        const Rational<T>& r) {
    return Rational<T> (n) /= r;
}

template<typename T> inline Rational<T> operator+(const Rational<T>& r) {
    return r;
}

template<typename T> inline Rational<T> operator-(const Rational<T>& r) {
    return Rational<T>(-r.num(), r.den());
}

//------------------------------------------------------

template<typename T>
bool operator== (const Rational<T>& r1, const Rational<T>& r2) {
    return r1.num() == r2.num() && r1.den() == r2.den();
}

template<typename T>
bool operator!= (const Rational<T>& r1, const Rational<T>& r2) {
    return r1.num() != r2.num() || r1.den() != r2.den();
}

template<typename T>
bool operator> (const Rational<T>& r1, const Rational<T>& r2) {
    return r1.num()*r2.den() > r1.den()*r2.num();
}

template<typename T>
bool operator>= (const Rational<T>& r1, const Rational<T>& r2) {
    return r1.num()*r2.den() >= r1.den()*r2.num();
}

template<typename T>
bool operator< (const Rational<T>& r1, const Rational<T>& r2) {
    return r1.num()*r2.den() < r1.den()*r2.num();
}

template<typename T>
bool operator<= (const Rational<T>& r1, const Rational<T>& r2) {
    return r1.num()*r2.den() <= r1.den()*r2.num();
}

//------------------------------------------------------

/**
 * "Normalization"
 * n/d; n -> n/gcd(n,d), d -> d/gcd(n,d).
 */

template<typename T> void Rational<T>::normalize () {
    if (den_ < T(0)) {
        num_ *= T(-1);
        den_ *= T(-1);
    }
    if (num_ == T(0) && den_ != T(1) && den_ != T(0))
        den_ = T(1);
    else if (den_ == T(0)) num_ = T(0);
    else {
        T g = GcdEuclid (std::abs(num_), den_);
        if (g != T(1)) num_/=g, den_/=g;
    }
}

//------------------------------------------------------

template<typename T, class CharT, class Traits>
std::basic_ostream<CharT, Traits>& operator <<
(std::basic_ostream<CharT, Traits>& s, const Rational<T>& q) {
    if (q.num() < T(0)) s << "-";
    s << std::abs(q.num());
    if ( q.num() != T(0) && q.den() != T(0) && q.den() != 1)
        s << "/" << q.den();
    return s;
}

template<typename T> Rational<T> abs (const Rational<T>& r) {
    return Rational<T> (std::abs(r.num()),r.den());
}

template<typename T> Rational<T> pow (Rational<T> r, int n) {
    if (n < 0) {
        r = Rational<T>(T(1)) / r;
        n = -n;
    }

    Rational<T> r2 = n%2 ? r : Rational<T>(T(1));

    while (n >>= 1) {
        r *= r;
        if (n%2) r2 *= r;
    }

    return r2;
}

//------------------------------------------------------

}    // namespace rational
}    // namespace nacre

namespace std {

template<typename T> nacre::rational::Rational<T>
abs (const nacre::rational::Rational<T>& r) {
    return nacre::rational::abs(r);
}

template<typename T> nacre::rational::Rational<T>
pow (nacre::rational::Rational<T> r, int n) {
    return nacre::rational::pow(r,n);
}

}    // namespace std

#endif    // NACRE_RATIONAL
