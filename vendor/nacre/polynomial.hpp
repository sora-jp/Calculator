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
 * @file polynomial.hpp
 * @date 2007-04-13
 * General polynomial class.
 * Chebyshev, Hermite, Laguerre, Legendre polynomials.
 */

#ifndef NACRE_POLYNOMIAL
#define NACRE_POLYNOMIAL

#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <limits>
#include <cmath>

namespace nacre {
namespace polynomial {

template<typename T>
struct div_t {
    div_t() : quot(T()), rem(T()) {}
    T quot;
    T rem;
};

/// P_n = sum_{i=0}^n c_i x^i

template<typename T>
class Polynomial {
protected:

    /// Coefficients { c_0; ...; c_n } :
    std::vector<T> coeffs_;

public:
    Polynomial (const T& = T(0));

    template<typename T2> Polynomial (const Polynomial<T2>&);

    /// basic
    size_t order () const;
    void order (size_t);

    /// remove leading zero coefficients
    void normalize ();

    /// evaluation
    T operator() (const T&) const;

    /// indexation
    T& operator[] (size_t);
    const T& operator[] (size_t) const;

    /// arithmetic
    Polynomial& operator=  (const T&);
    Polynomial& operator+= (const T&);
    Polynomial& operator-= (const T&);
    Polynomial& operator*= (const T&);
    Polynomial& operator/= (const T&);

    template<typename T2>
    Polynomial<T>& operator=  (const Polynomial<T2>&);
    template<typename T2>
    Polynomial<T>& operator+= (const Polynomial<T2>&);
    template<typename T2>
    Polynomial<T>& operator-= (const Polynomial<T2>&);
    template<typename T2>
    Polynomial<T>& operator*= (const Polynomial<T2>&);

    template<typename T2>
    div_t<Polynomial<T> >
    div (const Polynomial<T2>&) const;

    template<typename T2>
    Polynomial<T>& operator/= (const Polynomial<T2>&);
    template<typename T2>
    Polynomial<T>& operator%= (const Polynomial<T2>&);

    virtual ~Polynomial () {}
};

//------------------------------------------------------

template<typename T>
Polynomial<T>::Polynomial (const T& x)
        : coeffs_ () {
    order(0);
    (*this)[0] = x;
}

template<typename T> template<typename T2>
Polynomial<T>::Polynomial (const Polynomial<T2>& P) : coeffs_ () {
    order(P.order());
    for (size_t i = 0; i <= P.order(); i++)
        (*this)[i] = T(P[i]);
}

//------------------------------------------------------

template<typename T>
size_t Polynomial<T>::order () const {
    return coeffs_.size() - 1;
}

template<typename T>
void Polynomial<T>::order (size_t n) {
    coeffs_.resize(n+1);
}

//------------------------------------------------------

/// indexation
template<typename T>
T& Polynomial<T>::operator[] (size_t i) {
    return coeffs_.at(i);
}

template<typename T>
const T& Polynomial<T>::operator[] (size_t i) const {
    return coeffs_.at(i);
}

//------------------------------------------------------

template<typename T>
void Polynomial<T>::normalize () {
    size_t z = 0;
    for (size_t i = order(); i > 1; i--)
        if ((*this)[i] == T(0)) z++;
        else break;
    if (z != 0) order(order() - z);
}

//------------------------------------------------------

/// evaluation
template<typename T>
T Polynomial<T>::operator() (const T& x) const {
    T result = (*this)[order()];
    for (int i = order()-1; i >= 0; i--)
        result = result*x + (*this)[i];
    return result;
}

//------------------------------------------------------

/// arithmetic
template<typename T>
Polynomial<T>& Polynomial<T>::operator=  (const T& x) {
    order(0);
    (*this)[0] = x;
    return *this;
}

template<typename T>
Polynomial<T>& Polynomial<T>::operator+= (const T& x) {
    (*this)[0] += x;
    return *this;
}

template<typename T>
Polynomial<T>& Polynomial<T>::operator-= (const T& x) {
    (*this)[0] -= x;
    return *this;
}

template<typename T>
Polynomial<T>& Polynomial<T>::operator*= (const T& x) {
    for (size_t i = 0; i <= order(); i++ )
        (*this)[i] *= x;
    return *this;
}

template<typename T>
Polynomial<T>& Polynomial<T>::operator/= (const T& x) {
    for (size_t i = 0; i <= order(); i++)
        (*this)[i] /= x;
    return *this;
}

template<typename T>
template<typename T2>
Polynomial<T>& Polynomial<T>::operator= (const Polynomial<T2>& P) {
    order(P.order());
    for (size_t i = 0; i <= order(); i++)
        (*this)[i] = P[i];
    return *this;
}

template<typename T>
template<typename T2>
Polynomial<T>& Polynomial<T>::operator+= (const Polynomial<T2>& P) {
    order ( std::max( order(), P.order() ) );
    for (size_t i = 0; i <= P.order(); i++)
        (*this)[i] += P[i];
    normalize();
    return *this;
}

template<typename T>
template<typename T2>
Polynomial<T>& Polynomial<T>::operator-= (const Polynomial<T2>& P) {
    order ( std::max( order(), P.order() ) );
    for (size_t i = 0; i <= P.order(); i++)
        (*this)[i] -= P[i];
    normalize();
    return *this;
}

template<typename T>
template<typename T2>
Polynomial<T>& Polynomial<T>::operator*= (const Polynomial<T2>& P) {
    if (P.order() == 0)
        return *this *= P[0];

    Polynomial<T> product;
    product.order (order() + P.order());

    for (size_t i = 0; i <= order(); i++)
        for (size_t j = 0; j <= P.order(); j++)
            product[i+j] += (*this)[i]*P[j];

    *this = product;
    normalize();
    return *this;
}

template<typename T>
template<typename T2>
div_t<Polynomial<T> >
Polynomial<T>::div (const Polynomial<T2>& P) const {
    div_t<Polynomial<T> > qr;
    qr.quot.order(order());
    for (size_t i = 0; i<= order(); i++) qr.quot[i] = T(0);

    qr.rem = *this;

    for (int k = order() - P.order(); k>=0; k--) {
        qr.quot[k] = qr.rem[P.order()+k] / P[P.order()];
        for (int j = P.order()+k-1; j>=k; j--)
            qr.rem[j] -= qr.quot[k] * P[j-k];
    }

    for (unsigned int j = P.order(); j <= order(); j++)
        qr.rem[j] = T(0);

    qr.quot.normalize();
    qr.rem.normalize();

    return qr;
}

template<typename T>
template<typename T2>
Polynomial<T>& Polynomial<T>::operator/= (const Polynomial<T2>& P) {
    return *this = div (P).quot;
}

template<typename T>
template<typename T2>
Polynomial<T>& Polynomial<T>::operator%= (const Polynomial<T2>& P) {
    return *this = div (P).rem;
}

//------------------------------------------------------------

template<typename T>
inline Polynomial<T>
operator+(const Polynomial<T>& P1, const Polynomial<T>& P2) {
    return Polynomial<T> (P1) += P2;
}

template<typename T>
inline Polynomial<T>
operator+(const Polynomial<T>& P, const T& x) {
    return Polynomial<T> (x) += P;
}

template<typename T>
inline Polynomial<T>
operator+(const T& x, const Polynomial<T>& P) {
    return Polynomial<T> (P) += x;
}

template<typename T>
inline Polynomial<T>
operator-(const Polynomial<T>& P1, const Polynomial<T>& P2) {
    return Polynomial<T> (P1) -= P2;
}

template<typename T>
inline Polynomial<T>
operator-(const Polynomial<T>& P1, const T& x) {
    return Polynomial<T> (P1) -= x;
}

template<typename T>
inline Polynomial<T>
operator-(const T& x, const Polynomial<T>& P) {
    return Polynomial<T> (x) -= P;
}

template<typename T>
inline Polynomial<T>
operator*(const Polynomial<T>& P1, const Polynomial<T>& P2) {
    return Polynomial<T> (P1) *= P2;
}

template<typename T>
inline Polynomial<T>
operator*(const Polynomial<T>& P, const T& x) {
    return Polynomial<T> (P) *= x;
}

template<typename T>
inline Polynomial<T>
operator*(const T& x, const Polynomial<T>& P) {
    return Polynomial<T> (P) *= x;
}

template<typename T>
inline Polynomial<T>
operator/(const Polynomial<T>& P1, const Polynomial<T>& P2) {
    return Polynomial<T> (P1) /= P2;
}

template<typename T>
inline Polynomial<T>
operator/(const Polynomial<T>& P, const T& x) {
    return Polynomial<T> (P) /= x;
}

template<typename T>
inline Polynomial<T>
operator/(const T& x, const Polynomial<T>& P) {
    return Polynomial<T> (x) /= P;
}

template<typename T>
inline Polynomial<T>
operator%(const Polynomial<T>& P1, const Polynomial<T>& P2) {
    return Polynomial<T> (P1) %= P2;
}

template<typename T>
inline Polynomial<T>
operator%(const Polynomial<T>& P, const T& x) {
    return Polynomial<T> (P) %= x;
}

template<typename T>
inline Polynomial<T>
operator%(const T& x, const Polynomial<T>& P) {
    return Polynomial<T> (x) %= P;
}

template<typename T>
inline Polynomial<T>
operator+(const Polynomial<T>& P) {
    return P;
}

template<typename T>
inline Polynomial<T> operator-(const Polynomial<T>& P) {
    Polynomial<T> mP = Polynomial<T>(P);
    for (size_t i = 0; i <= mP.order(); i++)
        mP[i] = -mP[i];
    return mP;
}

//------------------------------------------------------------

template<typename T>
inline bool operator==(const Polynomial<T>& P1, const Polynomial<T>& P2) {
    if (P1.order() != P2.order())
        return false;
    for (size_t i = 0; i <= P1.order(); i++)
        if (P1[i] != P2[i])
            return false;
    return true;
}

template<typename T>
inline bool operator==(const Polynomial<T>& P, const T& x) {
    return P.order() == 0 && P[0] == x;
}

template<typename T>
inline bool operator== (const T& x, const Polynomial<T>& P) {
    return P.order() == 0 && P[0] == x;
}

template<typename T>
inline bool operator!=(const Polynomial<T>& P1, const Polynomial<T>& P2) {
    if (P1.order() != P2.order())
        return true;
    for (size_t i = 0; i <= P1.order(); i++)
        if (P1[i] != P2[i])
            return true;
    return false;
}

template<typename T>
inline bool operator!=(const Polynomial<T>& P, const T& x) {
    return P.order() != 0 || P[0] != x;
}

template<typename T>
inline bool operator!= (const T& x, const Polynomial<T>& P) {
    return P.order() != 0 || P[0] != x;
}

//------------------------------------------------------

template<typename T>
Polynomial<T> pow (Polynomial<T> P, size_t n) {
    Polynomial<T> P1 = n%2 ? P : Polynomial<T>(1);
    while (n >>= 1) {
        P *= P;
        if (n%2) P1 *= P;
    }
    return P1;
}

template<typename T>
inline Polynomial<T> operator^ (Polynomial<T> P, size_t n) {
    return pow (P, n);
}

//------------------------------------------------------

template<typename T> Polynomial<T> diff (Polynomial<T> P) {
    if (P.order() == 0) return Polynomial<T>();
    Polynomial<T> D;
    D.order(P.order()-1);
    for (size_t i=0; i<=D.order(); i++)
        D[i] = P[i+1]*T(i+1);
    D.normalize();
    return D;
}

template<typename T> Polynomial<T> integrate (Polynomial<T> P) {
    if (P.order() == 0) return Polynomial<T>();
    Polynomial<T> I;
    I.order(P.order()+1);
    for (size_t i=0; i<=P.order(); i++)
        I[i+1] = P[i]/T(i+1);
    I.normalize();
    return I;
}

//------------------------------------------------------

template<typename T, typename CharT, class Traits>
std::basic_ostream<CharT, Traits>& operator <<
( std::basic_ostream<CharT, Traits>& os,
  const Polynomial<T>& P ) {
    std::basic_ostringstream<CharT, Traits> s;
    s.flags(os.flags());
    s.imbue(os.getloc());
    s.precision(os.precision());

    if (P.order() == 0) return os << P[0];

    for (int n=P.order(); n>=0; n--) {
        if (P[n] != T(0)) {
            /*if (!std::numeric_limits<T>::is_signed) {*/
            if (n!=P.order())
                s << " + ";
            if (P[n]!=T(1) || n==0)
                s << P[n];
            if (P[n]!=T(1) && n!=0)
                s << '*';
            /*} else {
                if (P[n] < T(0)) {
                    if (n != P.order())
                        s << ' ';
                    s << '-';
                    if (n != P.order())
                        s << ' ';
                } else if (n != P.order())
                    s << " + ";
                if (std::abs(P[n])!=T(1) || n==0)
                    s << std::abs(P[n]);
                if (std::abs(P[n])!=T(1) && n!=0)
                    s << '*';
            }*/

            if (n!=0 && n!=1)
                s << "x^" << n;
            if (n!=0 && n==1)
                s << 'x';
        }
    }

    return os << s.str();
}

//------------------------------------------------------

} // namespace polynomial
} // namespace nacre

#define INCLUDED_BY_NACRE
    #include "polynomial_orthogonal.hpp"
    #include "polynomial_roots.hpp"
#undef INCLUDED_BY_NACRE

#endif    // NACRE_POLYNOMIAL
