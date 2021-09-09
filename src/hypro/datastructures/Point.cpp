#include "hypro/datastructures/Point.h"

namespace hypro {
#ifdef EXTERNALIZE_CLASSES
template class Point<double>;
template class Point<mpq_class>;
#endif
}  // namespace hypro
