#pragma once
#include "../../../types.h"

#include <iostream>
#include <vector>

namespace hypro {

/**
 * @brief Struct representing a subspace decomposition of a hybrid automaton
 */
struct Decomposition {
	std::vector<std::vector<std::size_t>> subspaces;  ///< subsets of variables
	std::vector<DynamicType> subspaceTypes;			  ///< type of subspace
};

/// outstream operator
std::ostream& operator<<( std::ostream& out, const Decomposition& decomposition );

}  // namespace hypro
