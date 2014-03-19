

#ifndef CONFIG_H_
#define CONFIG_H_

#include <mpfr.h>
#include "carl/numbers/FLOAT_T.h"
#include "carl/core/MultivariatePolynomial.h"

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

typedef mpfr_t number;
typedef carl::FLOAT_T<number_t> number;
typedef carl::MultivariatePolynomial<number> Polynomial;

#endif
