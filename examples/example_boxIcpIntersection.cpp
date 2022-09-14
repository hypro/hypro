#include "datastructures/Halfspace.h"
#include "representations/GeometricObjectBase.h"

int main() {
	// use rational arithmetic.
	typedef mpq_class Number;

	// hypro::Box<Number> testbox(std::make_pair(hypro::Point<Number>({1,1}),
	// hypro::Point<Number>({2,2})));

	std::vector<carl::Interval<Number>> intervals;
	intervals.emplace_back( 1, 2 );
	intervals.emplace_back( 1, 2 );

	hypro::vector_t<Number> n1 = hypro::vector_t<Number>::Zero( 2 );
	n1 << 1, 1;

	// fully included
	hypro::Halfspace<Number> hsp1{ n1, Number( 2 ) };

	std::cout << "Intersect with " << hsp1 << std::endl;
	hypro::icpIntersectHalfspace( intervals, hsp1 );
	std::cout << "Result:" << std::endl;
	for ( const auto& i : intervals ) {
		std::cout << i << std::endl;
	}

	return 0;
}
