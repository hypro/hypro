#include "Hyperplane.h"

namespace hypro
{
    #ifdef EXTERNALIZE_CLASSES
    template class Hyperplane<double>;
    
    #ifdef USE_MPFR_FLOAT
    template class Hyperplane<carl::FLOAT_T<mpfr_t>>;
    #endif
    
    template class Hyperplane<carl::FLOAT_T<double>>;
    #endif
}
