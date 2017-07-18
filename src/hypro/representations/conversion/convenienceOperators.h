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

	template<typename ...T, typename Number>
	auto getSet(boost::variant<T...>&& in, representation_name name) {
		switch(name) {
			case representation_name::box: {
				return boost::get<Box<Number>>(std::forward<boost::variant<T...>>(in));
			}
			case representation_name::constraint_set: {
				return boost::get<ConstraintSet<Number>>(std::forward<boost::variant<T...>>(in));
			}
			case representation_name::polytope_h: {
				return boost::get<HPolytope<Number>>(std::forward<boost::variant<T...>>(in));
			}
			case representation_name::polytope_v: {
				return boost::get<VPolytope<Number>>(std::forward<boost::variant<T...>>(in));
			}
			#ifdef HYPRO_USE_PPL
			case representation_name::ppl_polytope: {
				return boost::get<Polytope<Number>>(std::forward<boost::variant<T...>>(in));
			}
			#endif
			case representation_name::support_function: {
				return boost::get<SupportFunction<Number>>(std::forward<boost::variant<T...>>(in));
			}
			case representation_name::taylor_model: {
				assert(false);
				return in;
			}
			case representation_name::zonotope: {
				return boost::get<Zonotope<Number>>(std::forward<boost::variant<T...>>(in));
			}
			default:
				assert(false);
				return in;
		}
	}
}
