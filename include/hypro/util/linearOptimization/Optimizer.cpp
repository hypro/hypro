#include "Optimizer.h"

#include <hypro/flags.h>
#ifdef USE_CLN_NUMBERS
#include <cln/cln.h>
#endif
#include <gmp.h>
#include <gmpxx.h>

// template<typename Number>
// bool hypro::Optimizer<Number>::warnInexact = false;

#ifdef USE_CLN_NUMBERS
template class hypro::Optimizer<cln::cl_RA>;
#endif

template class hypro::Optimizer<mpq_class>;

template class hypro::Optimizer<double>;
