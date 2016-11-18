
#pragma once

#include "RawState.h"
#include "../../representations/GeometricObject.h"
#include "boost/variant.hpp"

namespace hypro {

	class are_strict_equals
    : public boost::static_visitor<bool>
	{
	public:

	    template <typename T, typename U>
	    bool operator()( const T &, const U & ) const
	    {
	        return false; // cannot compare different types
	    }

	    template <typename T>
	    bool operator()( const T & lhs, const T & rhs ) const
	    {
	        return lhs == rhs;
	    }

	};

	// forward declarations
	template<typename Number>
	class Location;

	template<typename Number>
	struct State {
		Location<Number>* location;
		boost::variant<cPair<Number>,
			VPolytope<Number>,
			HPolytope<Number>,
			Polytope<Number>,
			Box<Number>,
			SupportFunction<Number>,
			Zonotope<Number>> set;

		std::map<carl::Variable, carl::Interval<Number>> discreteAssignment;
		carl::Interval<Number> timestamp = carl::Interval<Number>::unboundedInterval();

		bool operator==(const State<Number>& rhs) const {
			// compare location
			if(this->location->id() != rhs.location->id()) {
				return false;
			}

			// compare discrete assignment
			for(const auto variableAssignmentPair : discreteAssignment) {
				if(rhs.discreteAssignment.find(variableAssignmentPair.first) == rhs.discreteAssignment.end()) {
					return false;
				} else {
					if(rhs.discreteAssignment.at(variableAssignmentPair.first) != variableAssignmentPair.second) {
						return false;
					}
				}
			}

			// compare continuous assignment
			return boost::apply_visitor(are_strict_equals(), this->set, rhs.set);
		}

		friend std::ostream& operator<<( std::ostream& _ostr, const State<Number>& s ) {
			_ostr << "Loc: " << s.location->id() << ", time: " << s.timestamp << std::endl;
			return _ostr;
		}

	};
} // namespace


