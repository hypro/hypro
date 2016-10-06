#include "Halfspace.h"

namespace hypro
{
    #ifdef EXTERNALIZE_CLASSES
    template class Halfspace<mpq_class>;

    #ifdef USE_CLN_NUMBERS
    template class Halfspace<cln::cl_RA>;
    #endif
    #endif
}
