#include "Halfspace.h"

namespace hypro
{
    #ifdef EXTERNALIZE_CLASSES
    template class Halfspace<double>;

    #ifdef USE_MPFR_FLOAT
    template class Halfspace<carl::FLOAT_T<mpfr_t>>;
    #endif

    template class Halfspace<carl::FLOAT_T<double>>;
    #endif
}
