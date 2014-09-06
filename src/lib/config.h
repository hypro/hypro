#pragma once

#include <mpfr.h>
#include <set>
#include <map>
#include "util/VariablePool.h"
#include <carl/numbers/FLOAT_T.h>
#include <carl/core/MultivariatePolynomial.h>
#include <carl/core/Variable.h>
#include <carl/util/SFINAE.h>
//#include "util/eigenTypetraits.h"
#include <eigen3/Eigen/Dense>
#include <eigen3/unsupported/Eigen/src/MatrixFunctions/MatrixExponential.h>


#define reachLin_VERSION_MAJOR 0
#define reachLin_VERSION_MINOR 1

#define DEBUG 1

//#define LOG4CPLUS_DISABLE_TRACE


#define DEFAULT_DIM 5
#define MAXIMAL_DIMENSION 5

// Do we eliminate dimensions according to a dynamic heuristic.
#define DYNAMICHEURISTIC 0
#define reachLin_PRIMITIVES_LOCATION "../polyhedra/"
#define reachLin_NR_PRIMITIVES 100

#define PI_UP 3.141592655
#define PI_DN 3.141592654

typedef double number_t;
typedef carl::FLOAT_T<number_t> number;
typedef carl::MultivariatePolynomial<number> Polynomial;
typedef std::map<carl::Variable, unsigned> varIdMap;
typedef std::set<carl::Variable> variableSet;
typedef Eigen::Matrix<carl::FLOAT_T<number_t>, Eigen::Dynamic, Eigen::Dynamic> matrix;
typedef Eigen::Matrix<carl::FLOAT_T<number_t>, Eigen::Dynamic, 1> vector;

//author: ckugler
//defines for Forward Reachability
#define fReach_TIMEBOUND 10
#define fReach_TIMEDISCRETIZATION 10
#define fReach_DENOMINATOR 1000000

//defines for Fukuda's Minkowski Sum
#define EPSILON 0.000001
#define POS_CONSTANT 100

namespace Eigen
{
    template<> struct NumTraits<number>
    {
        enum
        {
            IsComplex = 0,
            IsInteger = 0,
            ReadCost = 1,
            AddCost = 1,
            MulCost = 1, 
            IsSigned = 1,
            RequireInitialization = 1
        };

        typedef number Real;
        typedef number NonInteger;
        typedef number Nested;

        static inline Real epsilon() { return Real(0); }
        static inline Real dummy_precision()
        {
            // make sure to override this for floating-point types
            return Real(0);
        }
        //static inline number highest() { return number::maxVal(); }
        //static inline number lowest()  { return number::minVal(); }
    };
}
