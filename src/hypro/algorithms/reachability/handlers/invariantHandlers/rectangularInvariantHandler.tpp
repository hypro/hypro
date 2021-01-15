#include "rectangularInvariantHandler.h"

namespace hypro {
template <typename Representation>
std::pair<CONTAINMENT, Representation> rectangularIntersectInvariant( const Representation& stateSet, const Location<typename Representation::NumberType>* loc ) {
	return intersect( stateSet, loc->getInvariant() );
}

}  // namespace hypro
