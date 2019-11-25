
//#pragma once
#include "../types.h"

#ifndef INCL_FROM_CONVERTERHEADER
static_assert( false, "This file may only be included indirectly by Converter.h" );
#endif

namespace hypro {

/*
	template<typename Number, typename From, representation_name::box>
	static auto convert(const From& in) -> (decltype(Converter<Number>::toBox(in)))
	{
		return Converter<Number>::toBox(in);
	}
	*/

/*
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
	*/

}  // namespace hypro
