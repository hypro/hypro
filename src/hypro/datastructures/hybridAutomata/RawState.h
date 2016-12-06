/**
 * @file RawState.h
 */

#pragma once

#include "types.h"

namespace hypro {

	template<typename Number>
	class Location;

	template<typename Number>
	using cPair = std::pair<matrix_t<Number>, vector_t<Number>>;

	/**
	 * @brief      Struct holding the raw information about a state.
 	 * @details 		This struct is required for parsing and can directly be accessed
	 * by the parser. A state for the reachability analysis is contained in the file State.h.
	 *
	 * @tparam     Number  The used number type.
	 */
	template<typename Number>
	struct RawState {
		Location<Number>* location = nullptr;
		cPair<Number> set;

		std::map<carl::Variable, carl::Interval<Number>> discreteAssignment;
		carl::Interval<Number> timestamp = carl::Interval<Number>::unboundedInterval();

		RawState() = delete;
		RawState(Location<Number>* location, const cPair<Number>& set) : location(location), set(set) {}
		RawState(Location<Number>* location) : location(location), set() {}

		void addArtificialDimension() {
			matrix_t<Number> newConstraints = matrix_t<Number>::Zero(set.first.rows(), set.first.cols()+1);
			newConstraints.block(0,0,set.first.rows(), set.first.cols()) = set.first;
			set.first = newConstraints;
		}

		bool operator==( const RawState<Number>& rhs) const {
			return( *location == *rhs.location &&
					set == rhs.set &&
					discreteAssignment == rhs.discreteAssignment &&
					timestamp == rhs.timestamp );
		}

		friend std::ostream& operator<<( std::ostream& _ostr, const RawState<Number>& s ) {
			if(s.location != nullptr) {
				_ostr << "Loc: " << s.location->id() << ", time: " << s.timestamp << std::endl;
			}
			return _ostr;
		}

	};

} // namespace hypro
