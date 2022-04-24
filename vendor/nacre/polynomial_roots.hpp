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
 * @file polynomial_roots.hpp
 * @date 2007-04-13
 * Find roots of polynomial with Muller method.
 * INTERNAL HEADER ONLY, NOT TO BE USED DIRECTLY.
 */

#ifndef INCLUDED_BY_NACRE
    #error THIS IS AN INTERNAL HEADER ONLY, NOT TO BE USED DIRECTLY
#endif

#ifndef NACRE_POLYNOMIAL_ROOTS
#define NACRE_POLYNOMIAL_ROOTS

#include <cmath>
#include <vector>
#include <stdexcept>
#include <limits>

namespace nacre {
namespace polynomial {

class TooManyIterations : public std::exception {
public:
    const char* what () const throw() { return "too many iterations"; }
};

template<class F, typename T, typename Cplx>
Cplx MullerRoot
(const F& f,
 Cplx x0, Cplx x1, Cplx x2,
 const T& eps, size_t maxIter) {

    if (std::abs(f(x0)) < eps) return x0;
    if (std::abs(f(x1)) < eps) return x1;

    for (size_t i = 0; i <= maxIter; i++) {

        if (std::abs(f(x2)) < eps ||
            std::abs(x2-x1) < std::numeric_limits<T>::epsilon()) return x2;

        Cplx q = (x2-x1)/(x1-x0);

        Cplx A = q*f(x2) - q*(T(1)+q)*f(x1) + q*q*f(x0);
        Cplx B = (T(2)*q+T(1))*f(x2) - (T(1)+q)*(T(1)+q)*f(x1) + q*q*f(x0);
        Cplx C = (T(1)+q)*f(x2);

        Cplx r = std::sqrt (B*B-T(4)*A*C);
        Cplx D = std::abs(B+r) > std::abs(B-r) ? B+r : B-r;

        // something wrong:
        if (std::abs(D) < std::numeric_limits<T>::epsilon()) return x2;

        Cplx x3 = x2 - (x2-x1) * (T(2)*C)/D;

        x0 = x1; x1 = x2; x2 = x3;
    }

    throw TooManyIterations();
    return x2;
}

template<typename Cplx> class RealGt {
public:
    bool operator () (const Cplx &a, const Cplx &b) {
        return a.real() < b.real();
    }
};

template<typename T, typename Cplx>
std::vector<Cplx> PolynomialRoots
(const nacre::polynomial::Polynomial<Cplx>& P,
 const T& eps, size_t maxIter) {
    nacre::polynomial::Polynomial<Cplx> TP = P;
    std::vector<Cplx> roots;

    for (unsigned int i = 1; i <= P.order(); i++) {
        Cplx z = MullerRoot(TP,
                            Cplx(-1), Cplx(0), Cplx(1),
                            eps, maxIter);
        roots.push_back(z);
        nacre::polynomial::Polynomial<Cplx> L;
        L.order(1);
        L[0] = -z; L[1] = Cplx(1);
        TP /= L;
    }

    sort (roots.begin(), roots.end(), RealGt<Cplx>());
    return roots;
}

//------------------------------------------------------

} // namespace polynomial
} // namespace nacre

#endif    // NACRE_POLYNOMIAL_ROOTS
