#pragma once

#include <mpfr.h>
#include <set>
#include <map>
#include <carl/numbers/FLOAT_T.h>
#include <carl/core/MultivariatePolynomial.h>
#include <carl/core/Variable.h>
#include <eigen3/Eigen/Dense>


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
typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> matrix;
typedef Eigen::Matrix<double, Eigen::Dynamic, 1> vector;

