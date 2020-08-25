#include "singularTimeEvolutionHandler.h"

namespace hypro {
template <typename StateSet>
StateSet singularApplyTimeEvolution( const StateSet& initialSet, const StateSet& flow ) {
	using Number = typename StateSet::NumberType;
	VPolytope<Number> initSetPolytope = hypro::Converter<Number>::toVPolytope( initialSet );
	VPolytope<Number> flowSetPolytope = hypro::Converter<Number>::toVPolytope( flow );
	VPolytope<Number> timeElapsePolytope{ initSetPolytope.vertices() };
	// set rays
	auto combinedRays = initSetPolytope.rays();
	// add rays from flow set
	combinedRays.insert( flowSetPolytope.rays().begin(), flowSetPolytope.rays().end() );
	// add rays originating from vertices of the flow set
	std::for_each( flowSetPolytope.vertices().begin(), flowSetPolytope.vertices().end(), [&]( const auto& point ) {
		combinedRays.insert( point.rawCoordinates() );
	} );

	timeElapsePolytope.setRays( combinedRays );

	// Convert back
	StateSet timeElapse;
	convert( timeElapsePolytope, timeElapse );
	return timeElapse;
}

template <typename StateSet>
StateSet singularApplyBoundedTimeEvolution( const StateSet& initialSet, const StateSet& flow, tNumber timeBound ) {
	using Number = typename StateSet::NumberType;
	VPolytope<Number> initSetPolytope = hypro::Converter<Number>::toVPolytope( initialSet );
	VPolytope<Number> flowSetPolytope = hypro::Converter<Number>::toVPolytope( flow );
	VPolytope<Number> timeElapsePolytope{ initSetPolytope.vertices() };
	// process rays: bound time, create new vertices
	typename VPolytope<Number>::pointVector newVertices;

	auto combinedRays = initSetPolytope.rays();
	// add rays from flow set
	combinedRays.insert( flowSetPolytope.rays().begin(), flowSetPolytope.rays().end() );
	// add rays originating from vertices of the flow set
	std::for_each( flowSetPolytope.vertices().begin(), flowSetPolytope.vertices().end(), [&]( const auto& point ) {
		combinedRays.insert( point.rawCoordinates() );
	} );

	for ( const auto& vertex : initSetPolytope.vertices() ) {
		for ( const auto& ray : combinedRays ) {
			std::cout << "VERTEX SIZE: " << vertex.rawCoordinates().rows() << ", " << vertex.rawCoordinates().cols() << "\n";
			std::cout << "RAY SIZE: " << ray.rows() << ", " << ray.cols() << "\n";
			newVertices.emplace_back( Point<Number>( vertex.rawCoordinates() + carl::convert<tNumber, Number>( timeBound ) * ray ) );
		}
	}

	// update vertices
	timeElapsePolytope.insert( newVertices.begin(), newVertices.end() );
	timeElapsePolytope.removeRedundancy();

	assert( timeElapsePolytope.rays().empty() );

	// Convert back
	StateSet timeElapse;
	convert( timeElapsePolytope, timeElapse );
	return timeElapse;
}

}  // namespace hypro
