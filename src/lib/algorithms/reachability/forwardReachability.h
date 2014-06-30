#pragma once

#include "../../datastructures/hybridAutomata/HybridAutomaton.h"
#include "../../config.h"
#include "util.h"

namespace hypro
{
    namespace forwardReachability
    {
			//TODO maybe flowpipe is not a set, but union of segments (=polytopes)
    		template<typename Number>
    		using flowpipe_t = std::set<hypro::valuation_t<Number>>;

    		template<typename Number>
			static flowpipe_t<Number> computeForwardTimeClosure(hypro::Location<Number> _loc, hypro::valuation_t<Number> _val) {

				// [0,T] = [0,delta1] U [delta1, delta2] ...
				// TODO: at the moment only one constant interval size
				int timeInterval = fReach_TIMEBOUND/fReach_TIMEDISCRETIZATION;

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
					//e^(At) = resultMatrix
					resultMatrix = deltaMatrix.exp();

					//e^(At)*X0 = polytope at t=delta
					hypro::valuation_t<Number> deltaValuation;
					_val.linearTransformation(deltaValuation, resultMatrix);

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
					flowpipe_t<Number> flowpipe;
					flowpipe.insert(firstSegment);

					//for each time interval perform linear Transformation
					for (double i=2*timeInterval; i<=fReach_TIMEBOUND; i+=timeInterval) {

						//Polytope after linear transformation
						hypro::valuation_t<Number> resultPolytope;

						//e^(A*delta), where delta is dependent on i
						hypro::matrix_t<Number> tempResult;
						hypro::matrix_t<Number> tempDelta = _loc.activityMat() * i;

						tempResult = tempDelta.exp();

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
    		template<typename Number>
			static bool computePostCondition(const hypro::Transition<Number>& _trans, hypro::valuation_t<Number> _val, hypro::valuation_t<Number>& result) {
				//alternatively: checkGuard(_trans,_val)

				//Polytope that is defined by the guard
				hypro::Polytope<Number> guardPoly = hypro::Polytope<Number>(_trans.guard().mat, _trans.guard().vec);

				//intersection between valuation polytope and guard polytope
				hypro::Polytope<Number> intersectionPoly;
				_val.intersect(intersectionPoly, guardPoly);

				//check if the intersection is empty
				if (!intersectionPoly.isEmpty()) {
					hypro::vector_t<Number> translateVec = _trans.assignment().translationVec;
					hypro::matrix_t<Number> transformMat = _trans.assignment().transformMat;

					//perform translation + transformation on intersection polytope
					intersectionPoly.linearTransformation(result, transformMat, translateVec);
					return true;
				} else {
					return false;
				}
			}

    		template<typename Number>
			static std::set<flowpipe_t<Number>> computeReach(std::set<flowpipe_t<Number>> _init, hypro::HybridAutomaton<Number> _hybrid,
					std::map<flowpipe_t<Number>, hypro::Location<Number>>& _map) {

				std::set<flowpipe_t<Number>> reach;

				//for each flowpipe in _init
				for (typename std::set<flowpipe_t<Number>>::iterator it_pipe = _init.begin(); it_pipe != _init.end(); ++it_pipe) {

					//get the location that belongs to the flowpipe
					hypro::Location<Number> loc = _map[*it_pipe];

					//polytope that belongs to the locations invariant
					//hypro::Polytope<Number> loc_inv = hypro::Polytope<Number>(loc.invariant().mat, loc.invariant().vec);

					//for each outgoing transition of the location
					std::set<Transition<Number>*> loc_transSet = loc.transitions();
					for (typename std::set<Transition<Number*>>::iterator it_trans = loc_transSet.begin(); it_trans != loc_transSet.end(); ++it_trans) {
						hypro::Transition<Number> trans = *(*it_trans);

						//resulting Polytope in new location
						hypro::valuation_t<Number> targetValuation;

						//for each polytope that is part of the flowpipe
						for (typename hypro::valuation_t<Number>::iterator it_val = *it_pipe.begin(); it_val != *it_pipe.end(); ++it_val) {
							hypro::valuation_t<Number> postAssign;
							//check if guard of transition is enabled (if yes compute Post Assignment Valuation)
							if (computePostCondition(trans, *it_val, postAssign)) {

								//targetValuation = targetValuation U postAssign
								if (!targetValuation.isEmpty()) {
									targetValuation.unite(targetValuation, postAssign);
								} else {
									targetValuation = postAssign;
								}
							}
						}

						//compute convex hull over all united polytopes
						hypro::valuation_t<Number> hullPoly;
						targetValuation.hull(hullPoly);

						//compute new Flowpipe
						hypro::Location<Number> tarLoc = *trans.targetLoc();
						flowpipe_t<Number> newPipe = computeForwardTimeClosure(tarLoc, hullPoly);

						//expand reach
						reach.insert(newPipe);

						//keep map consistent
						_map.insert( std::make_pair(newPipe, tarLoc) );
					}
				}
				return reach;
			}


			//TODO: time & step boundaries
    		template<typename Number>
			static std::set<flowpipe_t<Number>> computeForwardsReachability(hypro::HybridAutomaton<Number> _hybrid) {

					std::set<flowpipe_t<Number>> R_new;
					std::set<flowpipe_t<Number>> R;

					std::map<flowpipe_t<Number>, hypro::Location<Number>> map;

					//R_new = initialState
					typename std::set<hypro::Location<Number>*>::iterator it = _hybrid.initialLocations().begin();
					hypro::Location<Number> initLoc = *(*it);
					flowpipe_t<Number> init = computeForwardTimeClosure(initLoc, _hybrid.valuation());
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
						std::set<flowpipe_t<Number>> R_temp = computeReach(R_new, _hybrid, map);
						std::set_difference(R_temp.begin(), R_temp.end(), R.begin(), R.end(),
											std::inserter(R_new, R_new.begin()));
					}
					return R;

			}

    };
}

