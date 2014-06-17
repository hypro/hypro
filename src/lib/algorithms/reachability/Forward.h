#pragma once

#include "../../datastructures/hybridAutomata/HybridAutomaton.h"
#include "util.h"

namespace hypro
{
    template<typename Number>
    class Forward
    {
    	private:
			//TODO maybe flowpipe is not a set, but union of segments (=polytopes)
    		typedef std::set<hypro::valuation_t<Number>> flowpipe_t;

		public:

			flowpipe_t computeForwardTimeClosure(hypro::Location<Number> _loc, hypro::valuation_t<Number> _val,
				double _timeBound, double _timeDiscretizationFactor) {

				// [0,T] = [0,delta1] U [delta1, delta2] ...
				// TODO: at the moment only one constant interval size
				Number timeInterval = _timeBound/_timeDiscretizationFactor;

				//Polytope that is defined by the invariant
				hypro::Polytope<Number> poly = hypro::Polytope<Number>(_loc.invariant().mat, _loc.invariant().vec);

				//check if initial Valuation fulfills Invariant
				//alternatively: checkInvariant(_loc,_val)
				if ( poly.contains(_val) ) {

					//approximate R_[0,delta](X0)
					//rest is acquired by linear Transformation
					//R_0(X0) is just the initial Polytope X0, since t=0 -> At is 0 matrix -> e^(At) is Einheitsmatrix
					hypro::matrix_t<Number> deltaMatrix = _loc.activityMat() * timeInterval;

					//TODO check types (pointer)
					hypro::matrix_t<Number> resultMatrix;
					//TODO MatrixExponential
					//Eigen::MatrixExponential<hypro::matrix_t<Number>> expMatrix = Eigen::MatrixExponential<hypro::matrix_t<Number>>(deltaMatrix);
					//result is stored in resultMatrix
					//expMatrix.compute(resultMatrix);

					//e^(At)*X0 = polytope at t=delta
					hypro::valuation_t<Number> deltaValuation = deltaMatrix * _val;

					// R_0(X0) U R_delta(X0)
					hypro::valuation_t<Number> unitePolytope;
					_val.unite(unitePolytope, deltaValuation);

					// CH( R_0(X0) U R_delta(X0) )
					hypro::valuation_t<Number> hullPolytope;
					unitePolytope.hull(hullPolytope);

					//bloat hullPolytope (Hausdorff distance)
					hypro::valuation_t<Number> firstSegment;
					Number radius;
					radius = hullPolytope.hausdorffError(timeInterval);

					unsigned int dim;
					dim = hullPolytope.dimension();

					/*
					 * Box
					hypro::Box<Number> hausBox = hypro::computeBox(dim,radius);

					// B + hullPolytope -> Konstruktor needed for Ball instead of Polytope?
					hullPolytope.minkowskiSum(firstSegment, hausBox);
					*/

					hypro::valuation_t<Number> hausPoly = hypro::computePolytope(dim, radius);

					//hullPolytope +_minkowski hausPoly
					hullPolytope.minkowskiSum(firstSegment, hausPoly);

					//empty Flowpipe
					flowpipe_t flowpipe;
					flowpipe.insert(firstSegment);

					//for each time interval perform linear Transformation
					for (double i=2*timeInterval; i<=_timeBound; i+=timeInterval) {

						//Polytope after linear transformation
						hypro::valuation_t<Number> resultPolytope;

						//e^(A*delta), where delta is dependent on i
						hypro::matrix_t<Number> tempResult;
						hypro::matrix_t<Number> tempDelta = _loc.activityMat() * i;
						//TODO MatrixExponential
						//Eigen::MatrixExponential<hypro::matrix_t<Number>> tempMatrix = Eigen::MatrixExponential<hypro::matrix_t<Number>>(tempDelta);
						//tempMatrix.compute(tempResult);

						//perform linear transformation
						firstSegment.linearTransformation(resultPolytope, tempResult);

						//extend flowpipe
						flowpipe.insert(resultPolytope);
					}

					return flowpipe;

				} else {
					//throw error, initValuation invalid
				}

				//TODO outdated
				//idea: create new valuation set, add _val initially
				//then check invariant for upper bounds for variables -> FUNCTION: rückgabe jeweils ein t für eine var -> min suchen! -> obere grenze des intervals gegeben!
				//compute all reachable valuations up to these bounds (details? script -> solve set of linear constraints)
				//add to set, return set
			}

			//basically: execute assignment (if guard is fulfilled)
			hypro::valuation_t<Number> computePostCondition(hypro::Transition<Number> _trans, hypro::valuation_t<Number> _val) {
				//alternatively: checkGuard(_trans,_val)

				//Polytope that is defined by the invariant
				hypro::Polytope<Number> poly = hypro::Polytope<Number>(_trans.guard().mat, _trans.guard().vec);

				if (poly.contains(_val)) {
						return _trans.assignment();
				} else {
					//TODO
					//maybe throw error: transition may not be taken
					return _val;
				}
			}

			//TODO: time & step boundaries
			std::set<flowpipe_t> computeForwardsReachability(hypro::HybridAutomaton<Number> _hybrid) {
					//idea: alternate between time & discrete steps until boundary is reached
					//start at initial location with initial valuation

					//while (boundary not reached) {
					//computeForwardTimeClosure(_hybrid.initialLocations().begin());
					//if transition shall be taken (when? which one?)
					// if (_hybrid.transitions().begin().startLoc() == _hybrid.initialLocations().begin()) ...
					// TODO: umständlich -> bei Locations die ausgehenden Transitions speichern?
					//computePostCondition(_hybrid. ..)
			}

    };
}

