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
 * @file polynomial_orthogonal.hpp
 * @date 2007-04-11
 * Chebyshev, Hermite, Laguerre, Legendre polynomials.
 * INTERNAL HEADER ONLY, NOT TO BE USED DIRECTLY.
 */

#ifndef INCLUDED_BY_NACRE
    #error THIS IS AN INTERNAL HEADER ONLY, NOT TO BE USED DIRECTLY
#endif

#ifndef NACRE_POLYNOMIAL_ORTHOGONAL
#define NACRE_POLYNOMIAL_ORTHOGONAL

namespace nacre {
namespace polynomial {

namespace internal {
template<typename T>
static Polynomial<T> X () {
    static Polynomial<T> x;
    static bool cached = false;
    if (!cached) {
        x.order(1);
        x[0] = T(0);
        x[1] = T(1);
        cached = true;
    }
    return x;
}
}

template<typename T>
class BuildChebyshevPolynomial {
public:
    BuildChebyshevPolynomial() {}

    Polynomial<T> operator()
    (size_t n, std::vector<Polynomial<T> >& cache) {
        if (n < cache.size())
            return cache.at(n);

        if (n == 0 || n == 1) { // T_0 = 1, T_1 (x) = x
            cache.push_back(Polynomial<T> (T(1)));
            cache.push_back(internal::X<T>());
            return cache.at(n);
        }

        // T_{n+1} (x) = 2 x T_n(x) - T_{n-1}(x)
        cache.push_back( T(2)*internal::X<T>()*(*this)(n-1, cache) -
                         (*this)(n-2, cache) );

        return cache.at(n);
    }

};

//------------------------------------------------------

template<typename T>
class BuildLegendrePolynomial {
public:
    BuildLegendrePolynomial() {}
    Polynomial<T> operator() (size_t n, std::vector<Polynomial<T> >& cache) {
        if (n < cache.size())
            return cache.at(n);

        if (n == 0 || n == 1) { // P_0 = 1, P_1 = x
            cache.push_back(Polynomial<T> (T(1)));
            cache.push_back(internal::X<T>());
            return cache.at(n);
        }

        // (n+1) P_{n+1} (x) = (2n+1) x P_{n} (x) - n P_{n-1} (x)
        cache.push_back( (T(2*n-1)*internal::X<T>()*(*this)(n-1, cache) -
                          T(n-1) * (*this) (n-2, cache)) / T(n) );

        return cache.at(n);
    }
};

//------------------------------------------------------

template<typename T>
class BuildLaguerrePolynomial {
public:
    BuildLaguerrePolynomial() {}

    Polynomial<T> operator() (size_t n, std::vector<Polynomial<T> >& cache) {
        if (n < cache.size())
            return cache.at(n);

        if (n == 0 || n == 1) { // L_0 = 1, L_1 (x) = -x + 1
            cache.push_back(Polynomial<T> (T(1)));
            cache.push_back(-internal::X<T>() + T(1));
            return cache.at(n);
        }

        // L_{n+1} (x) = (2n + 1 - x) L_{n} (x) - n^2 P_{n-1} (x)
        cache.push_back ( (T(2*n-1) - internal::X<T>())*(*this)(n-1, cache) -
                          T(n-1)*T(n-1) * (*this) (n-2, cache) );
        return cache.at(n);
    }
};

//------------------------------------------------------

template<typename T>
class BuildHermitePolynomial {
public:
    BuildHermitePolynomial() {}
    Polynomial<T> operator()
    (size_t n, std::vector<Polynomial<T> >& cache) {

        if (n < cache.size())
            return cache.at(n);

        if (n == 0 || n == 1) { // H_0 = 1, H_1 (x) = 2 x
            cache.push_back(Polynomial<T> (T(1)));
            cache.push_back(T(2) * internal::X<T>());
            return cache.at(n);
        }

        // H_{n+1} (x) = 2 x H_n(x) - 2 n H (n-1) (x)
        cache.push_back ( T(2) * internal::X<T>() * (*this) (n-1, cache) -
                          T(2*(n-1)) * (*this) (n-2, cache) );
        return cache.at(n);
    }
};

//------------------------------------------------------

template<typename T, class Builder>
class OrthogonalPolynomial : public Polynomial<T> {
    static std::vector<Polynomial<T> > cache_;
    static Builder b_;
public:
    OrthogonalPolynomial (size_t n)
            : Polynomial<T> (b_(n, cache_)) {}
    static void clearTable() {
        cache_.erase(cache_.begin(), cache_.end());
    }
    static T weightFunction (const T& x) {
        return T(0);
    }
    static T orthogonalityIntervalLB () {
        return T(0);
    }
    static T orthogonalityIntervalUB () {
        return T(0);
    }
    virtual ~OrthogonalPolynomial() {}
};

template<typename T, class Builder>
std::vector<Polynomial<T> >
OrthogonalPolynomial<T, Builder>::cache_ = std::vector<Polynomial<T> >();

template<typename T, class Builder>
Builder
OrthogonalPolynomial<T, Builder>::b_ = Builder();

//------------------------------------------------------

template<typename T>
class ChebyshevPolynomial
    : public OrthogonalPolynomial<T, BuildChebyshevPolynomial<T> > {
public:
    ChebyshevPolynomial (size_t n)
            : OrthogonalPolynomial<T, BuildChebyshevPolynomial<T> > (n) {}
    static T weightFunction (const T& x) {
        return T(1)/std::sqrt(T(1)-x*x);
    }
    inline static T orthogonalityIntervalLB () {
        return T(-1);
    }
    inline static T orthogonalityIntervalUB () {
        return T(1);
    }
};

//------------------------------------------------------

template<typename T>
class LegendrePolynomial
    : public OrthogonalPolynomial<T, BuildLegendrePolynomial<T> > {
public:
    LegendrePolynomial (size_t n)
            : OrthogonalPolynomial<T, BuildLegendrePolynomial<T> > (n) {}
    inline static T weightFunction (const T&) {
        return T(1);
    }
    inline static T orthogonalityIntervalLB () {
        return T(-1);
    }
    inline static T orthogonalityIntervalUB () {
        return T(1);
    }
};

//------------------------------------------------------

template<typename T>
class LaguerrePolynomial
    : public OrthogonalPolynomial<T, BuildLaguerrePolynomial<T> > {
public:
    LaguerrePolynomial (size_t n)
            : OrthogonalPolynomial<T, BuildLaguerrePolynomial<T> > (n) {}
    static T weightFunction (const T& x) {
        return std::exp(-x);
    }
    inline static T orthogonalityIntervalLB () {
        return T(0);
    }
    inline static T orthogonalityIntervalUB () {
        return std::numeric_limits<T>::infinity();
    }
};

//------------------------------------------------------

template<typename T>
class HermitePolynomial
    : public OrthogonalPolynomial<T, BuildHermitePolynomial<T> > {
public:
    HermitePolynomial (size_t n)
            : OrthogonalPolynomial<T, BuildHermitePolynomial<T> > (n) {}
    static T weightFunction (const T& x) {
        return std::exp(-x*x);
    }
    inline static T orthogonalityIntervalLB () {
        return -std::numeric_limits<T>::infinity();
    }
    inline static T orthogonalityIntervalUB () {
        return std::numeric_limits<T>::infinity();
    }
};

//------------------------------------------------------

} // namespace polynomial
} // namespace nacre

#endif    // NACRE_POLYNOMIAL_ORTHOGONAL
