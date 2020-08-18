#include "singularTimeEvolutionHandler.h"

namespace hypro {
template <typename StateSet>
StateSet singularApplyTimeEvolution( const StateSet& initialSet, const StateSet& flow ) {
	using Number = typename StateSet::NumberType;
	VPolytope<Number> initSet = hypro::Converter<Number>::toVPolytope( initialSet );
	VPolytope<Number> flowSet = hypro::Converter<Number>::toVPolytope( flow );
	VPolytope<Number> timeElapse{ initSet.vertices() };
	// set rays
	auto combinedRays = initSet.rays();
	// add rays from flow set
	combinedRays.insert( flowSet.rays().begin(), flowSet.rays().end() );
	// add rays originating from vertices of the flow set
	std::for_each( flowSet.vertices().begin(), flowSet.vertices().end(), [&]( const auto& point ) {
		combinedRays.insert( point.rawCoordinates() );
	} );

	timeElapse.setRays( combinedRays );

	return timeElapse;
}

template <typename StateSet>
StateSet singularApplyBoundedTimeEvolution( const StateSet& initialSet, const StateSet& flow, tNumber timeBound ) {
	using Number = typename StateSet::NumberType;
	VPolytope<Number> initSet = hypro::Converter<Number>::toVPolytope( initialSet );
	VPolytope<Number> flowSet = hypro::Converter<Number>::toVPolytope( flow );
	VPolytope<Number> timeElapse{ initSet.vertices() };
	// process rays: bound time, create new vertices
	typename VPolytope<Number>::pointVector newVertices;

	auto combinedRays = initSet.rays();
	// add rays from flow set
	combinedRays.insert( flowSet.rays().begin(), flowSet.rays().end() );
	// add rays originating from vertices of the flow set
	std::for_each( flowSet.vertices().begin(), flowSet.vertices().end(), [&]( const auto& point ) {
		combinedRays.insert( point.rawCoordinates() );
	} );

	for ( const auto& vertex : initSet.vertices() ) {
		for ( const auto& ray : combinedRays ) {
			newVertices.emplace_back( Point<Number>( vertex.rawCoordinates() + carl::convert<tNumber, Number>( timeBound ) * ray ) );
		}
	}

	// update vertices
	timeElapse.insert( newVertices.begin(), newVertices.end() );
	timeElapse.removeRedundancy();

	assert( timeElapse.rays().empty() );
	return timeElapse;
}

}  // namespace hypro
