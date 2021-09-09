#include "intervalMethods.h"

namespace hypro {

void reduceIntervalsNumberRepresentation( std::vector<carl::Interval<mpq_class>>& intervals, unsigned limit ) {
	mpq_class limit2 = mpq_class( limit ) * mpq_class( limit );
	for ( unsigned d = 0; d < intervals.size(); ++d ) {
		// std::cout << "(Upper Bound) mpq_class: " << intervals[d].upper() << std::endl;
		if ( intervals[d].upper() != 0 ) {
			mpq_class numerator = carl::getNum( intervals[d].upper() );
			mpq_class denominator = carl::getDenom( intervals[d].upper() );
			mpq_class largest = carl::abs( numerator ) > carl::abs( denominator ) ? carl::abs( numerator ) : carl::abs( denominator );
			if ( largest > limit2 ) {
				mpq_class dividend = largest / mpq_class( limit );
				assert( largest / dividend == limit );
				mpq_class val = mpq_class( carl::ceil( numerator / dividend ) );
				mpq_class newDenom;
				if ( intervals[d].upper() > 0 ) {
					newDenom = mpq_class( carl::floor( denominator / dividend ) );
				} else {
					newDenom = mpq_class( carl::ceil( denominator / dividend ) );
				}
				if ( newDenom != 0 ) {
					val = val / newDenom;
					assert( val >= intervals[d].upper() );
					intervals[d].setUpper( mpq_class( val ) );
				}
				// std::cout << "Assert: " << val << " >= " << intervals[d].upper() << std::endl;
				// std::cout << "(Upper bound) Rounding Error: " << carl::convert<mpq_class,double>(val - intervals[d].upper()) << std::endl;
			}
		}

		// std::cout << "(Lower Bound) mpq_class: " << intervals[d].lower() << std::endl;
		if ( intervals[d].lower() != 0 ) {
			mpq_class numerator = carl::getNum( intervals[d].lower() );
			mpq_class denominator = carl::getDenom( intervals[d].lower() );
			mpq_class largest = carl::abs( numerator ) > carl::abs( denominator ) ? carl::abs( numerator ) : carl::abs( denominator );
			if ( largest > limit2 ) {
				mpq_class dividend = largest / mpq_class( limit );
				assert( largest / dividend == limit );
				mpq_class val = mpq_class( carl::floor( numerator / dividend ) );
				mpq_class newDenom;
				if ( intervals[d].lower() > 0 ) {
					newDenom = mpq_class( carl::ceil( denominator / dividend ) );
				} else {
					newDenom = mpq_class( carl::floor( denominator / dividend ) );
				}
				if ( newDenom != 0 ) {
					val = val / newDenom;
					assert( val <= intervals[d].lower() );
					intervals[d].setLower( val );
				}
				// std::cout << "Assert: " << val << " <= " << intervals[d].lower() << std::endl;
				// std::cout << "(Lower bound) Rounding Error: " << carl::convert<mpq_class,double>(val - intervals[d].lower()) << std::endl;
			}
		}
	}
}

}  // namespace hypro
