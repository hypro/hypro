#include "linearTimeEvolutionHandler.h"

namespace hypro {
template <typename StateSet>
StateSet linearApplyTimeEvolution( const StateSet& initialSet, const StateSet& flow ) {
	using Number = typename StateSet::NumberType;
	VPolytope<Number> initSet = hypro::Converter<Number>::toVPolytope( initialSet );
	VPolytope<Number> flowSet = hypro::Converter<Number>::toVPolytope( flow );
	VPolytope<Number> timeElapse{ initSet.vertices() };
	// set rays
	auto combinedRays = initSet.rays();
	// add rays from flow set
	std::remove_copy_if( flowSet.rays().begin(), flowSet.rays().end(), combinedRays.end(), [&]( const auto& ray ) { return std::find( combinedRays.begin(), combinedRays.end(), ray ) != combinedRays.end(); } );
	// add rays originating from vertices of the flow set
	std::for_each( flowSet.vertices().begin(), flowSet.vertices().end(), [&]( const auto& point ) {
		if ( std::find( combinedRays.begin(), combinedRays.end(), point.rawCoordinates() ) != combinedRays.end() ) {
			combinedRays.push_back( point.rawCoordinates() );
		}
	} );

	timeElapse.setRays( combinedRays );

	return timeElapse;
}

template <typename StateSet>
StateSet linearApplyBoundedTimeEvolution( const StateSet& initialSet, const StateSet& flow, tNumber timeBound ) {
	using Number = typename StateSet::NumberType;
	VPolytope<Number> initSet = hypro::Converter<Number>::toVPolytope( initialSet );
	VPolytope<Number> flowSet = hypro::Converter<Number>::toVPolytope( flow );
	VPolytope<Number> timeElapse{ initSet.vertices() };
	// process rays: bound time, create new vertices
	VPolytope<Number>::pointVector newVertices;

	auto combinedRays = initSet.rays();
	// add rays from flow set
	std::remove_copy_if( flowSet.rays().begin(), flowSet.rays().end(), combinedRays.end(), [&]( const auto& ray ) { return std::find( combinedRays.begin(), combinedRays.end(), ray ) != combinedRays.end(); } );
	// add rays originating from vertices of the flow set
	std::for_each( flowSet.vertices().begin(), flowSet.vertices().end(), [&]( const auto& point ) {
		if ( std::find( combinedRays.begin(), combinedRays.end(), point.rawCoordinates() ) != combinedRays.end() ) {
			combinedRays.push_back( point.rawCoordinates() );
		}
	} );

	for ( const auto& vertex : initSet.vertices() ) {
		for ( const auto& ray : combinedRays ) {
			newVertices.emplace_back( { vertex.rawCoordinates() + carl::convert<tNumber, Number>( timeBound ) * ray } );
		}
	}

	// update vertices
	timeElapse.addVertices( newVertices );
	timeElapse.removeRedundancy();

	assert( timeElapse.rays().empty() );
	return timeElapse;
}

}  // namespace hypro
