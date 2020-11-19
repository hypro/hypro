#include "singularTimeEvolutionHandler.h"
#define SINGULAR_TIME_EVOL_USE_HPOLYTOPE

namespace hypro {
template <typename StateSet>
StateSet singularApplyTimeEvolution( const StateSet& initialSet, const std::vector<Point<typename StateSet::NumberType>>& flowVertices ) {
	using Number = typename StateSet::NumberType;
	VPolytope<Number> initSetPolytope = hypro::Converter<Number>::toVPolytope( initialSet );
	VPolytope<Number> flowSetPolytope{ flowVertices };
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
StateSet singularApplyBoundedTimeEvolution( const StateSet& initialSet, const std::vector<Point<typename StateSet::NumberType>>& flowVertices, tNumber timeBound ) {
#ifdef SINGULAR_TIME_EVOL_USE_HPOLYTOPE
	using Number = typename StateSet::NumberType;
	HPolytope<Number> initSetHPol = hypro::Converter<Number>::toHPolytope( initialSet );
	VPolytope<Number> flowShiftVPol( { carl::convert<tNumber, Number>( timeBound ) * flowVertices[0], Point<Number>::Zero( initSetHPol.dimension() ) } );
	HPolytope<Number> flowShiftHPol = hypro::Converter<Number>::toHPolytope( flowShiftVPol );

	auto timeElapseHPol = initSetHPol.minkowskiSum( flowShiftHPol );
	StateSet timeElapse;
	convert( timeElapseHPol, timeElapse );
	timeElapse.removeRedundancy();
	return timeElapse;

#else
	using Number = typename StateSet::NumberType;
	VPolytope<Number> initSetPolytope = hypro::Converter<Number>::toVPolytope( initialSet );
	VPolytope<Number> flowSetPolytope{ flowVertices };
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
			newVertices.emplace_back( Point<Number>( vertex.rawCoordinates() + carl::convert<tNumber, Number>( timeBound ) * ray ) );
		}
	}

	// update vertices
	timeElapsePolytope.insert( newVertices.begin(), newVertices.end() );

	assert( timeElapsePolytope.rays().empty() );

	// Convert back
	StateSet timeElapse;
	convert( timeElapsePolytope, timeElapse );
	timeElapse.removeRedundancy();
	return timeElapse;
#endif
}

template <typename StateSet>
StateSet singularApplyTimeStep( const StateSet& initialSet, const std::vector<Point<typename StateSet::NumberType>>& flowVertices, tNumber timeStart, tNumber timeBound ) {
#ifdef SINGULAR_TIME_EVOL_USE_HPOLYTOPE
	using Number = typename StateSet::NumberType;
	HPolytope<Number> initSetHPol = hypro::Converter<Number>::toHPolytope( initialSet );
	VPolytope<Number> flowShiftVPol( { carl::convert<tNumber, Number>( timeBound ) * flowVertices[0], carl::convert<tNumber, Number>( timeStart ) * flowVertices[0] } );
	HPolytope<Number> flowShiftHPol = hypro::Converter<Number>::toHPolytope( flowShiftVPol );

	auto timeElapseHPol = initSetHPol.minkowskiSum( flowShiftHPol );
	StateSet timeElapse;
	convert( timeElapseHPol, timeElapse );
	timeElapse.removeRedundancy();
	return timeElapse;

#else
	using Number = typename StateSet::NumberType;
	VPolytope<Number> initSetPolytope = hypro::Converter<Number>::toVPolytope( initialSet );
	VPolytope<Number> flowSetPolytope{ flowVertices };
	VPolytope<Number> shiftPol( flowVertices[0] * carl::convert<tNumber, Number>(timeStart) );
	VPolytope<Number> timeElapsePolytope{ initSetPolytope.vertices() };
	timeElapsePolytope = timeElapsePolytope.minkowskiSum( shiftPol );
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
			newVertices.emplace_back( Point<Number>( vertex.rawCoordinates() + carl::convert<tNumber, Number>( timeBound ) * ray ) );
		}
	}

	// update vertices
	timeElapsePolytope.insert( newVertices.begin(), newVertices.end() );

	assert( timeElapsePolytope.rays().empty() );

	// Convert back
	StateSet timeElapse;
	convert( timeElapsePolytope, timeElapse );
	timeElapse.removeRedundancy();
	return timeElapse;
#endif
}

}  // namespace hypro
