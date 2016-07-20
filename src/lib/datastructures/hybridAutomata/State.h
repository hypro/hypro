
#pragma once

#include "RawState.h"
#include "../../representations/GeometricObject.h"
#include "boost/variant.hpp"

namespace hypro {

	// forward declarations
	template<typename Number>
	class Location;

	template<typename Number>
	struct State {
		Location<Number>* location;
		boost::variant<cPair<Number>,
			VPolytope<Number>,
			HPolytope<Number>,
			Box<Number>,
			SupportFunction<Number>,
			Zonotope<Number>> set;

		std::map<carl::Variable, carl::Interval<Number>> discreteAssignment;
		carl::Interval<Number> timestamp = carl::Interval<Number>::unboundedInterval();

		friend std::ostream& operator<<( std::ostream& _ostr, const State<Number>& s ) {
			_ostr << "Loc: " << s.location->id() << ", time: " << s.timestamp << std::endl;
			return _ostr;
		}

	};
} // namespace


