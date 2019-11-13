#pragma once
#include <boost/variant.hpp>
#include <iostream>
#include <map>
#include <string>

namespace hypro {

/**
 * @brief      Enum encapsulating all provided state set representations to be able to determine a type.
 */
enum representation_name { box = 0,
						   carl_polytope,
						   constraint_set,
						   polytope_h,
						   polytope_v,
						   ppl_polytope,
						   support_function,
						   taylor_model,
						   zonotope,
						   difference_bounds,
						   SFN,
						   UNDEF,
						   genStar };

}  // namespace hypro

namespace std {

/*
	ostream& operator<<(std::ostream& out, hypro::representation_name in) {
		switch(in){
			case(hypro::representation_name::box): { return out << "box"; }
			case(hypro::representation_name::constraint_set): { return out << "constraint_set"; }
			case(hypro::representation_name::polytope_h): { return out << "polytope_h"; }
			case(hypro::representation_name::polytope_v): { return out << "polytope_v"; }
			case(hypro::representation_name::ppl_polytope): { return out << "ppl_polytope"; }
			case(hypro::representation_name::support_function): { return out << "support_function"; }
			case(hypro::representation_name::taylor_model): { return out << "taylor_model"; }
			case(hypro::representation_name::zonotope): { return out << "zonotope"; }
			case(hypro::representation_name::difference_bounds): { return out << "difference_bounds"; }
			case(hypro::representation_name::UNDEF): { return out << "UNDEF"; }
			default: return out;
		}
	}
	*/

}  // namespace std
