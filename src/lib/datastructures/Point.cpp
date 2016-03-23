#include "Point.h"

namespace hypro
{
    #ifdef EXTERNALIZE_CLASSES
    template class Point<double>;

    #ifdef USE_MPFR_FLOAT
    template class Point<carl::FLOAT_T<mpfr_t>>;
    #endif

    template class Point<carl::FLOAT_T<double>>;
    #endif
} // namespace hypro