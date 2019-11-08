#include "Point.h"

namespace hypro
{
#ifdef EXTERNALIZE_CLASSES
    template class Point<mpq_class>;

#ifdef USE_CLN_NUMBERS
    template class Point<cln::cl_RA>;
#endif

#endif
} // namespace hypro
