#include "hypro/representations/Box/intervalMethods.h"

namespace hypro {

void reduceIntervalsNumberRepresentation( std::vector<carl::Interval<mpq_class>>& intervals, unsigned limit ) {
	mpq_class limit2 = mpq_class( limit ) * mpq_class( limit );
	for ( auto& interval : intervals ) {
		// std::cout << "(Upper Bound) mpq_class: " << intervals[d].upper() << std::endl;
		if ( interval.upper() != 0 ) {
			mpq_class numerator = carl::getNum( interval.upper() );
			mpq_class denominator = carl::getDenom( interval.upper() );
			mpq_class largest = carl::abs( numerator ) > carl::abs( denominator ) ? carl::abs( numerator ) : carl::abs( denominator );
			if ( largest > limit2 ) {
				mpq_class dividend = largest / mpq_class( limit );
				assert( largest / dividend == limit );
				mpq_class val = mpq_class( carl::ceil( numerator / dividend ) );
				mpq_class newDenom;
				if ( interval.upper() > 0 ) {
					newDenom = mpq_class( carl::floor( denominator / dividend ) );
				} else {
					newDenom = mpq_class( carl::ceil( denominator / dividend ) );
				}
				if ( newDenom != 0 ) {
					val = val / newDenom;
					assert( val >= interval.upper() );
					interval.setUpper( mpq_class( val ) );
				}
				// std::cout << "Assert: " << val << " >= " << interval.upper() << std::endl;
				// std::cout << "(Upper bound) Rounding Error: " << carl::convert<mpq_class,double>(val - interval.upper()) << std::endl;
			}
		}

		// std::cout << "(Lower Bound) mpq_class: " << interval.lower() << std::endl;
		if ( interval.lower() != 0 ) {
			mpq_class numerator = carl::getNum( interval.lower() );
			mpq_class denominator = carl::getDenom( interval.lower() );
			mpq_class largest = carl::abs( numerator ) > carl::abs( denominator ) ? carl::abs( numerator ) : carl::abs( denominator );
			if ( largest > limit2 ) {
				mpq_class dividend = largest / mpq_class( limit );
				assert( largest / dividend == limit );
				mpq_class val = mpq_class( carl::floor( numerator / dividend ) );
				mpq_class newDenom;
				if ( interval.lower() > 0 ) {
					newDenom = mpq_class( carl::ceil( denominator / dividend ) );
				} else {
					newDenom = mpq_class( carl::floor( denominator / dividend ) );
				}
				if ( newDenom != 0 ) {
					val = val / newDenom;
					assert( val <= interval.lower() );
					interval.setLower( val );
				}
				// std::cout << "Assert: " << val << " <= " << interval.lower() << std::endl;
				// std::cout << "(Lower bound) Rounding Error: " << carl::convert<mpq_class,double>(val - interval.lower()) << std::endl;
			}
		}
	}
}

}  // namespace hypro
