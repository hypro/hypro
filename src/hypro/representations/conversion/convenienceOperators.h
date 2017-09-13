/*
 * This file should only be included via Converter.h
 */
#include "../types.h"

namespace hypro {

	template<typename From, typename To, typename Number>
	To convert(const From& in) {
		switch(To::type()) {
			case representation_name::box: {
				return Converter<Number>::toBox(in);
			}
			case representation_name::constraint_set: {
				return Converter<Number>::toConstraintSet(in);
			}
			case representation_name::polytope_h: {
				return Converter<Number>::toHPolytope(in);
			}
			case representation_name::polytope_v: {
				return Converter<Number>::toVPolytope(in);
			}
			case representation_name::ppl_polytope: {
				assert(false);
				return To();
			}
			case representation_name::support_function: {
				return Converter<Number>::toSupportFunction(in);
			}
			case representation_name::taylor_model: {
				assert(false);
				return To();
			}
			case representation_name::zonotope: {
				return Converter<Number>::toZonotope(in);
			}
			default:
				assert(false);
				return To();
		}
	}

}
