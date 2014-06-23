#pragma once

#include "../../datastructures/hybridAutomata/HybridAutomaton.h"
#include "../../config.h"
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
                                        deltaMatrix.exp();
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

			}

			//basically: execute assignment (if guard is fulfilled)
			bool computePostCondition(hypro::Transition<Number> _trans, hypro::valuation_t<Number> _val, hypro::valuation_t<Number>& result) {
				//alternatively: checkGuard(_trans,_val)

				//Polytope that is defined by the guard
				hypro::Polytope<Number> poly = hypro::Polytope<Number>(_trans.guard().mat, _trans.guard().vec);

				if (poly.contains(_val)) {
					result = _trans.assignment();
					return true;
				} else {
					return false;
				}
			}


			std::set<flowpipe_t> computeReach(std::set<flowpipe_t> _init, hypro::HybridAutomaton<Number> _hybrid, double _timeBound, double _timeDiscretizationFactor,
					std::map<flowpipe_t, hypro::Location<Number>> _map) {

				std::set<flowpipe_t> reach;

				//for each flowpipe in _init
				for (typename std::set<flowpipe_t>::iterator it_pipe = _init.begin(); it_pipe != _init.end(); ++it_pipe) {

					//get the location that belongs to the flowpipe
					hypro::Location<Number> loc = _map[*it_pipe];

					//polytope that belongs to the locations invariant
					hypro::Polytope<Number> loc_inv = hypro::Polytope<Number>(loc.invariant().mat, loc.invariant().vec);

					//for each outgoing transition of the location
					std::set<Transition<Number>*> loc_transSet = loc.transitions();
					for (typename std::set<Transition<Number*>>::iterator it_trans = loc_transSet.begin(); it_trans != loc_transSet.end(); ++it_trans) {
						hypro::Transition<Number> trans = *(*it_trans);

						//for each polytope that is part of the flowpipe
						for (typename hypro::valuation_t<Number>::iterator it_val = *it_pipe.begin(); it_val != *it_pipe.end(); ++it_val) {
							hypro::valuation_t<Number> postAssign;
							//check if guard of transition is fulfilled
							if (computePostCondition(trans, *it_val, postAssign)) {
								hypro::Location<Number> tarLoc = *trans.targetLoc();
								flowpipe_t newPipe = computeForwardTimeClosure(tarLoc, postAssign, _timeBound, _timeDiscretizationFactor);

								//expand reach
								reach.insert(newPipe);

								//keep map consistent
								_map.insert( std::make_pair(newPipe, tarLoc) );

								//TODO to break or not to break? depends if assignment is always the same or not
								break;
							}
						}
					}
				}
				return reach;
			}


			//TODO: time & step boundaries
			std::set<flowpipe_t> computeForwardsReachability(hypro::HybridAutomaton<Number> _hybrid, double _timeBound, double _timeDiscretizationFactor) {

					std::set<flowpipe_t> R_new;
					std::set<flowpipe_t> R;

					std::map<flowpipe_t, hypro::Location<Number>> map;

					//R_new = initialState
					typename std::set<hypro::Location<Number>*>::iterator it = _hybrid.initialLocations().begin();
					hypro::Location<Number> initLoc = *(*it);
					flowpipe_t init = computeForwardTimeClosure(initLoc, _hybrid.valuation(), _timeBound, _timeDiscretizationFactor);
					R_new.insert(init);

					map.insert( std::make_pair(init, initLoc) );

					while (!R_new.empty()) {
						//R = R U R_new
						if (!R.empty()) {
							std::set_union(R.begin(), R.end(),
										   R_new.begin(), R_new.end(),
										   std::inserter(R, R.begin()));			//alternative?: std::back_inserter(R);
						} else {
							R = R_new;
						}

						//R_new = Reach(R_new)/R
						std::set<flowpipe_t> R_temp = computeReach(R_new, _hybrid, _timeBound, _timeDiscretizationFactor, map);
						std::set_difference(R_temp.begin(), R_temp.end(), R.begin(), R.end(),
											std::inserter(R_new, R_new.begin()));
					}
					return R;

			}

    };
}

