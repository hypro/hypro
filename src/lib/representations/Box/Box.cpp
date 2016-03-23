#include "Box.h"

namespace hypro
{
    #ifdef EXTERNALIZE_CLASSES_ONLY_TO_TEST
    template class Box<double>;

    #ifdef USE_MPFR_FLOAT
    template class Box<carl::FLOAT_T<mpfr_t>>;
    #endif

    template class Box<carl::FLOAT_T<double>>;
    #endif
} // namespace hypro