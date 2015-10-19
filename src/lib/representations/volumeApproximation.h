/**
 *
 */

#include "../config.h"

namespace hypro {

	template<typename Number, typename Representation>
	static std::size_t approximateVolume<Number,Representation>(Representation _in, std::size_t sublevels = 0) {
		std::size_t pointCount = 0;

		// TODO, also figure out, if we need Number as a template parameter (I guess not)
		// TODO: where do we set the initial resolution? As a parameter with a default value specified as a constant in config.h maybe.

		return pointCount;
	}

}
