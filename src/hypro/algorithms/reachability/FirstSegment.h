#pragma once
#include "../../datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../datastructures/HybridAutomaton/State.h"
#include "../../representations/GeometricObjectBase.h"
#include "../../util/adaptions_eigen/adaptions_eigen.h"
#include "util.h"

#include <tuple>

namespace hypro {
namespace reachability {

template <typename Number>
matrix_t<Number> computeTrafoMatrix( const Location<Number>* _loc, Number timeStep ) {
	auto flowMatrix = _loc->getLinearFlow().getFlowMatrix();
	matrix_t<Number> deltaMatrix = flowMatrix * timeStep;

	TRACE( "hypro.reachability", "Flowmatrix:\n"
									   << flowMatrix << "\nmultiplied with time step: " << timeStep );
	TRACE( "hypro.reachability", "delta Matrix: " << std::endl );
	TRACE( "hypro.reachability", deltaMatrix << std::endl );
	TRACE( "hypro.reachability", "------" << std::endl );

	return matrixExponential( deltaMatrix );
}

namespace detail {

template <typename VariantType, typename Number>
class bloatBoxVisitor {
  protected:
	const Box<Number>& box;

  public:
	bloatBoxVisitor() = delete;
	bloatBoxVisitor( const Box<Number>& box )
		: box( box ) {}

	template <typename ConcreteType>
	inline VariantType operator()( const ConcreteType& set ) {
		ConcreteType tmp;
		convert( box, tmp );
		return set.minkowskiSum( tmp );
	}
};

}  // namespace detail

template <typename Number, typename State>
void bloatBox( State& in, const Box<Number>& bloatBox ) {
	// bloat per visitor, use setSetDirect, as the type does not change.
	in.setSetDirect( std::visit( hypro::reachability::detail::bloatBoxVisitor<typename State::repVariant, Number>( bloatBox ), in.getSet( 0 ) ) );
}

template <typename Number, typename State>
std::tuple<CONTAINMENT, State, matrix_t<Number>, vector_t<Number>, Box<Number>> computeFirstSegment( const State& _state, tNumber timeStep ) {
	assert( !_state.getTimestamp().isEmpty() );
	// check if initial Valuation fulfills Invariant
	assert( _state.getLocation() != nullptr );

#ifdef HYPRO_LOGGING
	TRACE( "hypro.reachability", "Location: " << _state.getLocation()->getName() << std::endl );
	double convertedTimeStep = carl::convert<tNumber, double>( timeStep );
	TRACE( "hypro.reachability", "Time step size: " << timeStep << "(" << convertedTimeStep << ")" << std::endl );
	TRACE( "hypro.reachability", "------" << std::endl );
#endif

	DEBUG( "hypro.reachability", "Check invariant: " << _state.getLocation()->getInvariant() << " for set " << _state );
	std::pair<CONTAINMENT, State> initialPair = _state.satisfies( _state.getLocation()->getInvariant() );

	if ( initialPair.first != CONTAINMENT::NO ) {
		// if the location has no flow, stop computation and exit.
		if ( _state.getLocation()->getLinearFlow( 0 ).isDiscrete() ) {
			// TRACE("Avoid further computation as the flow is zero." << std::endl);
			int rows = _state.getLocation()->getLinearFlow( 0 ).dimension();
			//std::cout << "Attention, external input not yet captured in locations with no flow." << std::endl;
			unsigned dimension = initialPair.second.getDimension( 0 );
			Box<Number> externalInputTmp( std::make_pair( Point<Number>( vector_t<Number>::Zero( dimension + 1 ) ),
														  Point<Number>( vector_t<Number>::Zero( dimension + 1 ) ) ) );
			return std::tuple<CONTAINMENT, State, matrix_t<Number>, vector_t<Number>, Box<Number>>( initialPair.first, initialPair.second, matrix_t<Number>::Identity( rows, rows ), vector_t<Number>::Zero( rows ), externalInputTmp );
		}

		// approximate R_[0,delta](X0)
		// R_0(X0) is just the initial Polytope X0, since t=0 -> At is zero matrix -> e^(At) is unit matrix.
		matrix_t<Number> trafoMatrix = computeTrafoMatrix( _state.getLocation(), carl::convert<tNumber, Number>( timeStep ) );

#ifdef HYPRO_LOGGING
		TRACE( "hypro.reachability", "e^(deltaMatrix): " << std::endl );
		TRACE( "hypro.reachability", trafoMatrix << std::endl );
		TRACE( "hypro.reachability", "------" << std::endl );
#endif

		// e^(At)*X0 = polytope at t=delta
		unsigned rows = trafoMatrix.rows();
		unsigned cols = trafoMatrix.cols();
		vector_t<Number> translation = trafoMatrix.col( cols - 1 );
		matrix_t<Number> trafoMatrixResized = matrix_t<Number>( rows - 1, cols - 1 );
		trafoMatrixResized = trafoMatrix.block( 0, 0, rows - 1, cols - 1 );
		translation.conservativeResize( rows - 1 );

		State deltaValuation = initialPair.second.partiallyApplyTimeStep( ConstraintSet<Number>( trafoMatrixResized, translation ), timeStep, 0 );

#ifdef HYPRO_LOGGING
		TRACE( "hypro.reachability", "Polytope at t=delta: " << deltaValuation );
#endif

		State firstSegment( _state.getLocation() );
		unsigned dimension = initialPair.second.getDimension( 0 );

		std::vector<Box<Number>> errorBoxVector;

		if ( _state.getLocation()->getExternalInput().empty() ) {
			Box<Number> externalInputTmp( std::make_pair( Point<Number>( vector_t<Number>::Zero( dimension ) ),
														  Point<Number>( vector_t<Number>::Zero( dimension ) ) ) );
			errorBoxVector = errorBoxes( carl::convert<tNumber, Number>( timeStep ), _state.getLocation()->getLinearFlow(), initialPair.second, trafoMatrix, externalInputTmp );
		} else {
			//std::cout << "Model has external input: " << _state.getLocation()->getExternalInput() << std::endl;
			errorBoxVector = errorBoxes( carl::convert<tNumber, Number>( timeStep ), _state.getLocation()->getLinearFlow(), initialPair.second, trafoMatrix, Box<Number>{ _state.getLocation()->getExternalInput() } );
		}

		firstSegment = deltaValuation.unite( initialPair.second );
		assert( firstSegment.satisfies( _state.getLocation()->getInvariant() ).first != CONTAINMENT::NO );

		if ( !errorBoxVector.empty() ) {
#ifdef HYPRO_LOGGING
			TRACE( "hypro.reachability", "Errorbox X_0: " << errorBoxVector[0] << " with dimension " << errorBoxVector[0].dimension() << " and d: " << dimension );
#endif

			//firstSegment.setSet(bloatBox<Number, Representation>(std::get<Representation>(firstSegment.getSet()), Number(Number(1) / Number(4)) * errorBoxVector[0]));

			bloatBox<Number, State>( firstSegment, Number( Number( 1 ) / Number( 4 ) ) * errorBoxVector[2] );

			TRACE( "hypro.reachability", "Epsilon errorbox: " << errorBoxVector[2] );

			// assert(firstSegment.contains(unitePolytope));
			//assert(firstSegment.contains(initialPair.second));
			//assert(firstSegment.contains(deltaValuation));

#ifdef HYPRO_LOGGING
			TRACE( "hypro.reachability", "first Flowpipe Segment (after minkowski Sum): " << firstSegment );
#endif
		} else {
			return std::make_tuple( CONTAINMENT::NO, State{}, matrix_t<Number>{}, vector_t<Number>{}, Box<Number>{} );
		}

// (use_reduce_memory==true) apply clustering and reduction on segments for memory reduction
// (use_reduce_time==true) apply reduction on firstSegment for time reduction
#ifdef USE_REDUCTION
		unsigned CONVEXHULL_CONST = 20, REDUCE_CONST = 8;
		std::vector<vector_t<Number>> directions = computeTemplate<Number>( 2, REDUCE_CONST );

		bool use_reduce_memory = false, use_reduce_time = true;

		// obejcts for use_reduce_memory
		unsigned segment_count = 0;
		std::vector<Point<Number>> points_convexHull;

		for ( auto vertex : firstSegment.vertices() ) {	 // cover firstSegment in clustering
			if ( std::find( points_convexHull.begin(), points_convexHull.end(), vertex ) == points_convexHull.end() ) {
				points_convexHull.push_back( vertex );
			}
		}

		// option 1: use uniform distirbution of REDUCE_CONST directions in all dimension-pairs (use_reduce_memory or use_reduce_time)
		// option 2: use directions of guards and invariants (use_reduce_time)
		// option 3: use uniform distirbution of firstSegment.size/2 directions in all dimension-pairs (use_reduce_time)

		if ( use_reduce_time ) {
			// option 2

			// for(auto transition: _state.location->transitions()){	// reduction memory guard mode
			//	auto guard= transition->guard();
			//	for(unsigned i=0; i<guard.mat.rows(); i++){
			//		vector_t<Number> guard_vector = vector_t<Number>(2);
			//		guard_vector(0)=guard.mat(i,0);
			//		guard_vector(1)=guard.mat(i,1);
			//		directions.push_back(guard_vector);
			//	}
			//}
			// for(unsigned inv_index=0; inv_index<invariant.size(); ++inv_index){ // reduction memory invariant mode
			//	directions.push_back(invariant.constraints().at(inv_index).normal());
			//}

			firstSegment = firstSegment.reduce_directed( directions, HPolytope<Number>::REDUCTION_STRATEGY::DIRECTED_TEMPLATE );

			// option 3
			// int reduce_calculated = ceil(firstSegment.size()/2);
			// if(reduce_calculated>2){
			//	firstSegment = firstSegment.reduce_directed(computeTemplate<Number>(2, reduce_calculated),
			//Box<Number>::REDUCTION_STRATEGY::DIRECTED_TEMPLATE);
			//}
		}
#endif
		assert( firstSegment.satisfies( _state.getLocation()->getInvariant() ).first != CONTAINMENT::NO );
		firstSegment.removeRedundancy();
		assert( firstSegment.satisfies( _state.getLocation()->getInvariant() ).first != CONTAINMENT::NO );

		// set the last segment of the flowpipe. Note that intersection with the invariants cannot result in an empty set due to previous checks.
		TRACE( "hypro.reachability", "Check invariant." );
		std::pair<CONTAINMENT, State> fullSegment = firstSegment.satisfies( _state.getLocation()->getInvariant() );
		TRACE( "hypro.reachability", "Check invariant - done." );
		if ( fullSegment.first != CONTAINMENT::NO ) {
			//fullSegment.second.setTimestamp(carl::Interval<tNumber>(fullSegment.second.getTimestamp().lower(),fullSegment.second.getTimestamp().upper() + timeStep));
#ifdef HYPRO_LOGGING
			// DBG
			//Box<Number> tmp = Converter<Number>::toBox(std::get<Box<Number>>(std::visit(genericConversionVisitor<typename State::repVariant,Number>(representation_name::box),fullSegment.second.getSet())));
			//TRACE("hypro.reachability","First segment: " << tmp);
#endif

			assert( fullSegment.second.getLocation() != nullptr );

			return std::tuple<CONTAINMENT, State, matrix_t<Number>, vector_t<Number>, Box<Number>>( fullSegment.first, fullSegment.second, trafoMatrixResized, translation, errorBoxVector[1] );
		} else {
			TRACE( "hypro.reachability", "First segment does not satisfy the invariant." );
			std::cout << "HyPro: First Segment does not satisfy the invariant." << std::endl;
			return std::make_tuple( CONTAINMENT::NO, State{}, matrix_t<Number>{}, vector_t<Number>{}, Box<Number>{} );
		}
	}  // if set does not satisfy the invariant, return false
	else {
		TRACE( "hypro.reachability", "Initial set does not satisfy the invariant." );
		std::cout << "Initial set " << _state << " does not satisfy the invariant." << std::endl;
		return std::make_tuple( CONTAINMENT::NO, State{}, matrix_t<Number>{}, vector_t<Number>{}, Box<Number>{} );
	}
}

}  // namespace reachability
}  // namespace hypro
