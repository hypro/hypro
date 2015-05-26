#pragma once



#include "../../datastructures/hybridAutomata/HybridAutomaton.h"
#include "../../config.h"
#include "util.h"

namespace hypro
{
    namespace forwardReachability
    {
    		template<typename Number>
    		using flowpipe_t = std::vector<hypro::valuation_t<Number>>;

    		/**
    		 * computes the reachability (= a flowpipe) for one location, based on an input valuation (a polytope)
    		 * @param _loc TODO
    		 * @param _val TODO
    		 * @return
    		 */
    		template<typename Number>
			static flowpipe_t<Number> computeForwardTimeClosure(hypro::Location<Number> _loc, hypro::valuation_t<Number> _val) {

				//[0,T] = [0,delta1] U [delta1, delta2] ...
				//note: interval size is constant
				double timeInterval = float(fReach_TIMEBOUND)/float(fReach_TIMEDISCRETIZATION);

#ifdef fReach_DEBUG
			   	std::cout <<  "Time Interval: " << timeInterval << std::endl;
#endif

				//Polytope that is defined by the invariant
				hypro::Polytope<Number> poly = hypro::Polytope<Number>(_loc.invariant().mat, _loc.invariant().vec);

#ifdef fReach_DEBUG
			   	std::cout << "invariant Polytope: ";
			    poly.print();
#endif

				//new empty Flowpipe
				flowpipe_t<Number> flowpipe;
				//add initial valuation
			    flowpipe.push_back(_val);

				//check if initial Valuation fulfills Invariant
#ifdef fReach_DEBUG
				std::cout << "Valuation fulfills Invariant?: ";
				std::cout << poly.contains(_val) << std::endl;
#endif

				if ( poly.contains(_val) ) {

					//approximate R_[0,delta](X0)
					//rest is acquired by linear Transformation
					//R_0(X0) is just the initial Polytope X0, since t=0 -> At is zero matrix -> e^(At) is 'Einheitsmatrix'
					hypro::matrix_t<Number> deltaMatrix(_loc.activityMat().rows(),_loc.activityMat().cols());
					deltaMatrix = _loc.activityMat() * timeInterval;

#ifdef fReach_DEBUG
				   	std::cout << "delta Matrix: " << std::endl;
				   	std::cout << deltaMatrix << std::endl;
				   	std::cout << "------" << std::endl;
#endif

					//e^(At) = resultMatrix
					hypro::matrix_t<Number> resultMatrix(deltaMatrix.rows(),deltaMatrix.cols());

					//---
					//Workaround for:
					//resultMatrix = deltaMatrix.exp();
					//-> convert FLOAT_T to double, compute .exp(), then convert back to FLOAT_T
					Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> doubleMatrix(deltaMatrix.rows(),deltaMatrix.cols());
					Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> expMatrix(deltaMatrix.rows(),deltaMatrix.cols());
					doubleMatrix = hypro::convertMatToDouble(deltaMatrix);
					expMatrix = doubleMatrix.exp();
					resultMatrix = hypro::convertMatToFloatT<Number>(expMatrix);

#ifdef fReach_DEBUG
				   	std::cout << "e^(deltaMatrix): " << std::endl;
				   	std::cout << resultMatrix << std::endl;
				   	std::cout << "------" << std::endl;
#endif

					//---

					//e^(At)*X0 = polytope at t=delta
					hypro::valuation_t<Number> deltaValuation = _val.linearTransformation(resultMatrix);

#ifdef fReach_DEBUG
				   	std::cout << "Polytope at t=delta: ";
				    deltaValuation.print();
#endif

					// R_0(X0) U R_delta(X0)
					hypro::valuation_t<Number> unitePolytope = _val.unite(deltaValuation);

#ifdef fReach_DEBUG
				   	std::cout << "Polytope after unite with R0: ";
				    unitePolytope.print();
#endif

					// CH( R_0(X0) U R_delta(X0) )
					hypro::valuation_t<Number> hullPolytope;
					hullPolytope = unitePolytope.hull();

#ifdef fReach_DEBUG
				   	std::cout << "Convex Hull (Polytope): ";
				    hullPolytope.print();
#endif

					//bloat hullPolytope (Hausdorff distance)
					hypro::valuation_t<Number> firstSegment;
					Number radius;
					radius = _val.hausdorffError(timeInterval, _loc.activityMat());

#ifdef fReach_DEBUG
					std::cout << "\n";
				   	std::cout << "Hausdorff Approximation: ";
				    std::cout << radius << std::endl;
#endif

					unsigned int dim;
					dim = hullPolytope.dimension();

					hypro::valuation_t<Number> hausPoly = hypro::computePolytope(dim, radius);

#ifdef fReach_DEBUG
					std::cout << "Hausdorff dimension: " << hausPoly.dimension() << std::endl;
					std::cout << "hullPolytope dimension: " << hullPolytope.dimension() << std::endl;
				   	std::cout << "Hausdorff Polytope (Box): ";
				    hausPoly.print();
#endif

					//hullPolytope +_minkowski hausPoly
					firstSegment = hullPolytope.minkowskiSum(hausPoly);

#ifdef fReach_DEBUG
				   	std::cout << "first Flowpipe Segment (after minkowski Sum): ";
				    firstSegment.print();
#endif

					//insert first Segment into the empty flowpipe
					flowpipe.push_back(firstSegment);

					//set the last segment of the flowpipe
					hypro::valuation_t<Number> lastSegment;
					lastSegment = firstSegment;

					//Polytope after linear transformation
					hypro::valuation_t<Number> resultPolytope;

#ifdef fReach_DEBUG
					std::cout << "--- Loop entered ---" << std::endl;
#endif

					//for each time interval perform linear Transformation
					for (double i=2*timeInterval; i<=fReach_TIMEBOUND; i+=timeInterval) {

#ifdef fReach_DEBUG
						std::cout << "i in Loop: " << i << std::endl;
#endif

						//perform linear transformation on the last segment of the flowpipe
						//lastSegment.linearTransformation(resultPolytope, tempResult);
						resultPolytope = lastSegment.linearTransformation(resultMatrix);

#ifdef fReach_DEBUG
					   	std::cout << "Next Flowpipe Segment: ";
					    resultPolytope.print();

						std::cout << "still within Invariant?: ";
						std::cout << poly.contains(resultPolytope) << std::endl;
#endif

						//extend flowpipe (only if still within Invariant of location)
						if (poly.contains(resultPolytope)) {
							flowpipe.push_back(resultPolytope);

							//update lastSegment
							lastSegment = resultPolytope;
						} else {
							break;
						}
					}

#ifdef fReach_DEBUG
					std::cout << "--- Loop left ---" << std::endl;
#endif

					return flowpipe;

				} else {
					//return an empty flowpipe
					return flowpipe;
				}

			}

    		/**
    		 * checks if the given valuation fulfills the guard of the given transition, if yes, executes the reset (that belongs to the transition)
    		 */
    		template<typename Number>
			static bool computePostCondition(const hypro::Transition<Number>& _trans, hypro::valuation_t<Number> _val, hypro::valuation_t<Number>& result) {
                    
				//Polytope that is defined by the guard
				hypro::Polytope<Number> guardPoly = hypro::Polytope<Number>(_trans.guard().mat, _trans.guard().vec);

				//intersection between valuation polytope and guard polytope
				hypro::Polytope<Number> intersectionPoly = _val.intersect(guardPoly);

				//check if the intersection is empty
				if (!intersectionPoly.isEmpty()) {
					hypro::vector_t<Number> translateVec = _trans.assignment().translationVec;
					hypro::matrix_t<Number> transformMat = _trans.assignment().transformMat;

					//perform translation + transformation on intersection polytope
					result = intersectionPoly.linearTransformation(transformMat, translateVec);
					return true;
				} else {
					return false;
				}
			}

    		/**
    		 * given a set of flowpipes, computes the reachability from this set (considering available transitions)
    		 * to do so, each flowpipe segment of all flowpipes is checked individually for each outgoing transition
    		 */
    		template<typename Number>
			static std::vector<flowpipe_t<Number>> computeReach(std::vector<flowpipe_t<Number>> _init, hypro::HybridAutomaton<Number, flowpipe_t<Number>> _hybrid,
					std::map<flowpipe_t<Number>, hypro::Location<Number>>& _map) {

				std::vector<flowpipe_t<Number>> reach;

				//for each flowpipe in _init
				for (typename std::vector<flowpipe_t<Number>>::iterator it_pipe = _init.begin(); it_pipe != _init.end(); ++it_pipe) {

					//get the location that belongs to the flowpipe
					hypro::Location<Number> loc = _map[*it_pipe];

					//for each outgoing transition of the location
					std::vector<Transition<Number>*> loc_transSet = loc.transitions();
					for (typename std::vector<Transition<Number*>>::iterator it_trans = loc_transSet.begin(); it_trans != loc_transSet.end(); ++it_trans) {
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
									targetValuation = targetValuation.unite(postAssign);
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

						//if new Flowpipe is not empty
						if (!newPipe.empty()) {
							//expand reach
							reach.push_back(newPipe);

							//keep map consistent
							_map.insert( std::make_pair(newPipe, tarLoc) );
						}
					}
				}
				return reach;
			}


    		/**
    		 * main algorithm that is called on a given hybrid automaton
    		 * computes the reachability on basis of polytopes
    		 * TODO: add time/step boundaries to guarantee termination (might be necessary for some automata)
    		 */
    		template<typename Number>
			static std::vector<flowpipe_t<Number>> computeForwardsReachability(hypro::HybridAutomaton<Number, flowpipe_t<Number>> _hybrid) {

					std::vector<flowpipe_t<Number>> R_new;
					std::vector<flowpipe_t<Number>> R;

					//map that stores which flowpipe belongs to which location
					std::map<flowpipe_t<Number>, hypro::Location<Number>> map;

					//R_new := flowpipe for the initial location, computed based on input valuation
					typename std::vector<hypro::Location<Number>*>::iterator it = _hybrid.initialLocations().begin();
					hypro::Location<Number> initLoc = *(*it);
					flowpipe_t<Number> init = computeForwardTimeClosure(initLoc, _hybrid.valuation());

					if (!init.empty()) {
						R_new.push_back(init);
					} else {
						//TODO return error
						//the initial valuation was not valid (with respect to the initial locations invariant)
					}

					map.insert( std::make_pair(init, initLoc) );

					while (!R_new.empty()) {
						//R = R U R_new
						if (!R.empty()) {
							std::set_union(R.begin(), R.end(),
										   R_new.begin(), R_new.end(),
										   std::inserter(R, R.begin()));
						} else {
							R = R_new;
						}

						//R_new = Reach(R_new)\R
						std::vector<flowpipe_t<Number>> R_temp = computeReach(R_new, _hybrid, map);
						std::set_difference(R_temp.begin(), R_temp.end(), R.begin(), R.end(),
											std::inserter(R_new, R_new.begin()));
					}
					return R;

			}

    };
}

