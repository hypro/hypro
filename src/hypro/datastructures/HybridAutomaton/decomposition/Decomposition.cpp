#include "hypro/datastructures/HybridAutomaton/decomposition/Decomposition.h"

namespace hypro {

std::ostream& operator<<( std::ostream& out, const Decomposition& decomposition ) {
	int i = 0;
	for ( const auto& bucket : decomposition.subspaces ) {
		out << "Decomposition " << i << ": " << std::endl;
		for ( const auto& var : bucket ) {
			out << "Var " << var << std::endl;
		}
		++i;
	}
	return out;
}

}  // namespace hypro
