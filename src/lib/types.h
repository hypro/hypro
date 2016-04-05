#pragma once

#define SUPPORT_MPFR
/* #undef COMPARE_CDD */
/* #undef COMPARE_POLYMAKE */

#include <set>
#include <iostream>

#include <carl/numbers/FLOAT_T.h>
#include <carl/interval/Interval.h>
#include <carl/core/Variable.h>
#include <eigen3/Eigen/Dense>
#include <eigen3/unsupported/Eigen/src/MatrixFunctions/MatrixExponential.h>

static const unsigned TOLLERANCE_ULPS = 8192;

// global typedefs
namespace hypro {
    template <typename Number>
    using vector_t = Eigen::Matrix<Number, Eigen::Dynamic, 1>;

    template <typename Number>
    using matrix_t = Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>;

    template <typename Number>
    class Polytope;

    template <typename Number>
    using valuation_t = Polytope<Number>;

    template <typename Number>
    using vectorSet = std::set<vector_t<Number>>;
}

namespace Eigen {
    template <typename Number>
    struct NumTraits<carl::FLOAT_T<Number>> {
        enum {
                IsComplex = 0,
                IsInteger = 0,
                ReadCost = 1,
                AddCost = 1,
                MulCost = 1,
                IsSigned = 1,
                RequireInitialization = 1
        };

        using Real = carl::FLOAT_T<Number>;
        using NonInteger = carl::FLOAT_T<Number>;
		using Nested = carl::FLOAT_T<Number>;

        static inline Real epsilon() { return std::numeric_limits<Real>::epsilon(); }
        static inline Real dummy_precision() {
                // make sure to override this for floating-point types
                return Real( 0 );
        }
        static inline carl::FLOAT_T<Number> highest() { return carl::FLOAT_T<Number>::maxVal(); }
        static inline carl::FLOAT_T<Number> lowest() { return carl::FLOAT_T<Number>::minVal(); }
    };
}

// Hash function for Eigen matrix and vector.
// The code is from `hash_combine` function of the Boost library. See
// http://www.boost.org/doc/libs/1_55_0/doc/html/hash/reference.html#boost.hash_combine .
namespace std {
    template<typename Number>
    struct hash<hypro::matrix_t<Number>> {
        size_t operator()(hypro::matrix_t<Number> const& in) const {

            size_t seed = 0;

            carl::hash_combine(seed, in.rows());
            carl::hash_combine(seed, in.cols());

            for (unsigned int i = 0; i < in.size(); ++i) {
                auto elem = *(in.data());

                carl::hash_combine(seed, elem);
            }
            return seed;
        }
    };

    template<typename Number>
    struct hash<hypro::vector_t<Number>> {
        size_t operator()(hypro::vector_t<Number> const& in) const {

            size_t seed = 0;

            carl::hash_combine(seed, in.rows());

            for (unsigned int i = 0; i < in.size(); ++i) {
                auto elem = *(in.data());

                carl::hash_combine(seed, elem);
            }
            return seed;
        }
    };
}
