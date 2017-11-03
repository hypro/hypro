#pragma once
#include "util.h"
#include "../../representations/GeometricObject.h"
#include <boost/tuple/tuple.hpp>

namespace hypro{
namespace reachability{

template <typename Number>
matrix_t<Number> computeTrafoMatrix(const Location<Number>* _loc, Number timeStep)
{
    matrix_t<Number> deltaMatrix(_loc->getFlow().rows(), _loc->getFlow().cols());
    deltaMatrix = _loc->getFlow() * timeStep;

    TRACE("hypro.reachability", "Flowmatrix:\n" << _loc->getFlow() << "\nmultiplied with time step: " << timeStep);
    TRACE("hypro.reachability", "delta Matrix: " << std::endl);
    TRACE("hypro.reachability", deltaMatrix << std::endl);
    TRACE("hypro.reachability", "------" << std::endl);

    // e^(At) = resultMatrix
    matrix_t<Number> resultMatrix(deltaMatrix.rows(), deltaMatrix.cols());

    //---
    // Workaround for:
    // resultMatrix = deltaMatrix.exp();
    //-> convert FLOAT_T to double, compute .exp(), then convert back to FLOAT_T
    matrix_t<double> doubleMatrix(deltaMatrix.rows(), deltaMatrix.cols());
    matrix_t<double> expMatrix(deltaMatrix.rows(), deltaMatrix.cols());
    doubleMatrix = convert<Number, double>(deltaMatrix);

    TRACE("hypro.reachability","transformed matrix: " << doubleMatrix);

    expMatrix = doubleMatrix.exp();

    TRACE("hypro.reachability","exp matrix: " << expMatrix);

    resultMatrix = convert<double, Number>(expMatrix);

	TRACE("hypro.reachability","transformed matrix: " << resultMatrix);

    return resultMatrix;
}

template<typename Number, typename State>
void bloatBox(State& in, const Box<Number>& bloatBox) {
	switch(in.getSetType(0)) {
		case representation_name::box: {
			in.setSetDirect(boost::get<Box<Number>>(in.getSet(0)).minkowskiSum(Converter<Number>::toBox(bloatBox)));
			break;
		}
		case representation_name::polytope_h: {
			in.setSetDirect(boost::get<HPolytope<Number>>(in.getSet(0)).minkowskiSum(Converter<Number>::toHPolytope(bloatBox)));
			break;
		}
		case representation_name::polytope_v: {
			in.setSetDirect(boost::get<VPolytope<Number>>(in.getSet(0)).minkowskiSum(Converter<Number>::toVPolytope(bloatBox)));
			break;
		}
		case representation_name::zonotope: {
			in.setSetDirect(boost::get<Zonotope<Number>>(in.getSet(0)).minkowskiSum(Converter<Number>::toZonotope(bloatBox)));
			break;
		}
		case representation_name::support_function: {
			in.setSetDirect(boost::get<SupportFunction<Number>>(in.getSet(0)).minkowskiSum(Converter<Number>::toSupportFunction(bloatBox)));
			break;
		}
		case representation_name::ppl_polytope: {
			assert(false && "CONVERSION TO PPL POLYTOPE NOT YET IMPLEMENTED.");
			break;
		}
		case representation_name::constraint_set:{
			assert(false && "CANNOT CONVERT TO TYPE ConstraintSet<Number>.");
			break;
		}
		case representation_name::taylor_model:{
			assert(false && "CANNOT CONVERT TO TYPE TAYLOR MODEL.");
			break;
		}
	}
}

template <typename Number, typename State>
boost::tuple<CONTAINMENT, State, matrix_t<Number>, vector_t<Number>> computeFirstSegment(const State& _state, Number timeStep)
{
    assert(!_state.getTimestamp().isEmpty());
    // check if initial Valuation fulfills Invariant
    assert(_state.getLocation() != nullptr);
    DEBUG("hypro.reachability","Check invariant: " << _state.getLocation()->getInvariant() << " for set " << _state);
    std::pair<CONTAINMENT,State> initialPair = _state.satisfies(_state.getLocation()->getInvariant());

    #ifdef HYPRO_LOGGING
    //Box<Number> tmp3 = boost::get<>(boost::apply_visitor(genericConversionVisitor<typename State::repVariant,Number>(representation_name::box),initialPair.second.getSet(0)));
    //TRACE("hypro.reachability","Initial pair segment: " << tmp3);
    #endif

    if (initialPair.first) {

    	// if the location has no flow, stop computation and exit.
        if (_state.getLocation()->getFlow() == matrix_t<Number>::Zero(_state.getLocation()->getFlow(0).rows(), _state.getLocation()->getFlow(0).cols())) {
            // TRACE("Avoid further computation as the flow is zero." << std::endl);
            int rows =_state.getLocation()->getFlow(0).rows();
            return boost::tuple<CONTAINMENT, State, matrix_t<Number>, vector_t<Number>>(initialPair.first, initialPair.second, matrix_t<Number>::Identity(rows,rows), vector_t<Number>::Zero(rows));
        }

        // approximate R_[0,delta](X0)
        // R_0(X0) is just the initial Polytope X0, since t=0 -> At is zero matrix -> e^(At) is unit matrix.
        matrix_t<Number> trafoMatrix = computeTrafoMatrix(_state.getLocation(), timeStep);

        #ifdef HYPRO_LOGGING
        TRACE("hypro.reachability", "e^(deltaMatrix): " << std::endl);
        TRACE("hypro.reachability", trafoMatrix << std::endl);
        TRACE("hypro.reachability", "------" << std::endl);
        #endif

        // e^(At)*X0 = polytope at t=delta
        unsigned rows = trafoMatrix.rows();
        unsigned cols = trafoMatrix.cols();
        vector_t<Number> translation = trafoMatrix.col(cols - 1);
        matrix_t<Number> trafoMatrixResized = matrix_t<Number>(rows - 1, cols - 1);
        trafoMatrixResized = trafoMatrix.block(0, 0, rows - 1, cols - 1);
        translation.conservativeResize(rows - 1);

        State deltaValuation = initialPair.second.partiallyApplyTimeStep(ConstraintSet<Number>(trafoMatrixResized, translation), timeStep,0);

        #ifdef HYPRO_LOGGING
        TRACE("hypro.reachability", "Polytope at t=delta: " << deltaValuation);
        #endif

        State firstSegment(_state.getLocation());
        unsigned dimension = initialPair.second.getDimension(0);
        Box<Number> externalInput(std::make_pair(Point<Number>(vector_t<Number>::Zero(dimension+1)),
                                                        Point<Number>(vector_t<Number>::Zero(dimension+1))));
        std::vector<Box<Number>> errorBoxVector =
              errorBoxes(Number(timeStep), _state.getLocation()->getFlow(), initialPair.second, trafoMatrix, externalInput);

        firstSegment = deltaValuation.unite(initialPair.second);

        if (!errorBoxVector.empty()) {
        	#ifdef HYPRO_LOGGING
            TRACE("hypro.reachability", "Errorbox X_0: " << errorBoxVector[0] << " with dimension " << errorBoxVector[0].dimension() << " and d: " << dimension);
            #endif

            //firstSegment.setSet(bloatBox<Number, Representation>(boost::get<Representation>(firstSegment.getSet()), Number(Number(1) / Number(4)) * errorBoxVector[0]));

            bloatBox<Number,State>(firstSegment, Number(Number(1) / Number(4)) * errorBoxVector[2]);

            TRACE("hypro.reachability","Epsilon errorbox: " << errorBoxVector[2]);

            // assert(firstSegment.contains(unitePolytope));
            //assert(firstSegment.contains(initialPair.second));
            //assert(firstSegment.contains(deltaValuation));

            #ifdef HYPRO_LOGGING
            TRACE("hypro.reachability", "first Flowpipe Segment (after minkowski Sum): " << firstSegment);
            #endif
        } else {
            return boost::tuple<CONTAINMENT, State, matrix_t<Number>, vector_t<Number>>(CONTAINMENT::NO);
        }

// (use_reduce_memory==true) apply clustering and reduction on segments for memory reduction
// (use_reduce_time==true) apply reduction on firstSegment for time reduction
#ifdef USE_REDUCTION
        unsigned CONVEXHULL_CONST = 20, REDUCE_CONST = 8;
        std::vector<vector_t<Number>> directions = computeTemplate<Number>(2, REDUCE_CONST);

        bool use_reduce_memory = false, use_reduce_time = true;

        // obejcts for use_reduce_memory
        unsigned segment_count = 0;
        std::vector<Point<Number>> points_convexHull;

        for (auto vertex : firstSegment.vertices()) {  // cover firstSegment in clustering
            if (std::find(points_convexHull.begin(), points_convexHull.end(), vertex) == points_convexHull.end()) {
                points_convexHull.push_back(vertex);
            }
        }

        // option 1: use uniform distirbution of REDUCE_CONST directions in all dimension-pairs (use_reduce_memory or use_reduce_time)
        // option 2: use directions of guards and invariants (use_reduce_time)
        // option 3: use uniform distirbution of firstSegment.size/2 directions in all dimension-pairs (use_reduce_time)

        if (use_reduce_time) {
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

            firstSegment = firstSegment.reduce_directed(directions, HPolytope<Number>::REDUCTION_STRATEGY::DIRECTED_TEMPLATE);

            // option 3
            // int reduce_calculated = ceil(firstSegment.size()/2);
            // if(reduce_calculated>2){
            //	firstSegment = firstSegment.reduce_directed(computeTemplate<Number>(2, reduce_calculated),
            //Box<Number>::REDUCTION_STRATEGY::DIRECTED_TEMPLATE);
            //}
        }
#endif
        firstSegment.removeRedundancy();

        // set the last segment of the flowpipe. Note that intersection with the invariants cannot result in an empty set due to previous checks.
        TRACE("hypro.reachability","Check invariant.");
        std::pair<CONTAINMENT, State> fullSegment = firstSegment.satisfies(_state.getLocation()->getInvariant());
        TRACE("hypro.reachability","Check invariant - done.");
        if (fullSegment.first) {
        	fullSegment.second.setTimestamp(carl::Interval<Number>(Number(0), timeStep));
        	#ifdef HYPRO_LOGGING
        	// DBG
	        //Box<Number> tmp = Converter<Number>::toBox(boost::get<Box<Number>>(boost::apply_visitor(genericConversionVisitor<typename State::repVariant,Number>(representation_name::box),fullSegment.second.getSet())));
	        //TRACE("hypro.reachability","First segment: " << tmp);
	        #endif

            return boost::tuple<CONTAINMENT, State, matrix_t<Number>, vector_t<Number>>(fullSegment.first, fullSegment.second, trafoMatrixResized,
                                                                                                       translation);
        } else {
            return boost::tuple<CONTAINMENT, State, matrix_t<Number>, vector_t<Number>>(CONTAINMENT::NO);
        }
    }  // if set does not satisfy the invariant, return false
    else {
        return boost::tuple<CONTAINMENT, State, matrix_t<Number>, vector_t<Number>>(CONTAINMENT::NO);
    }
}

}  // namespace reachability
}  // namespace hypro
