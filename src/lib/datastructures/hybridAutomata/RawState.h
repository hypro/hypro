//
// Created by stefan on 01.07.16.
//

#pragma once

#include "types.h"

namespace hypro {

	template<typename Number>
	class Location;

	template<typename Number>
	using cPair = std::pair<hypro::matrix_t<Number>, hypro::vector_t<Number>>;

	template<typename Number>
	struct RawState {
		Location<Number>* location;
		cPair<Number> set;

		std::map<carl::Variable, carl::Interval<Number>> discreteAssignment;
		carl::Interval<Number> timestamp = carl::Interval<Number>::unboundedInterval();

		friend std::ostream& operator<<( std::ostream& _ostr, const RawState<Number>& s ) {
			_ostr << "Loc: " << s.location->id() << ", time: " << s.timestamp << std::endl;
			return _ostr;
		}

	};

} // namespace hypro
