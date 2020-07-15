#include "Decomposition.h"

namespace hypro {

std::ostream& operator<<( std::ostream& out, const Decomposition& decomposition ) {
	int i = 0;
	for ( auto bucket : decomposition.subspaces ) {
		out << "Decomposition " << i << ": " << std::endl;
		for ( auto var : bucket ) {
			out << "Var " << var << std::endl;
		}
		++i;
	}
	return out;
}

}  // namespace hypro
