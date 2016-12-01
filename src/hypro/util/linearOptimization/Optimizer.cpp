#include "Optimizer.h"
#include "flags.h"
#ifdef USE_CLN_NUMBERS
#include <cln/cln.h>
#else
#include <gmp.h>
#include <gmpxx.h>
#endif

template<typename Number>
bool hypro::Optimizer<Number>::mWarnInexact = false;

#ifdef USE_CLN_NUMBERS
using Number = cln::cl_RA;
#else
using Number = mpq_class;
#endif

template class hypro::Optimizer<Number>;

template class hypro::Optimizer<double>;
