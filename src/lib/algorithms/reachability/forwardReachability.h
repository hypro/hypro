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
    		using flowpipe_t = std::vector<hypro::valuation_t<Number>>;

    		template<typename Number>
			static flowpipe_t<Number> computeForwardTimeClosure(hypro::Location<Number> _loc, hypro::valuation_t<Number> _val) {

				// [0,T] = [0,delta1] U [delta1, delta2] ...
				// TODO: at the moment only one constant interval size
				double timeInterval = float(fReach_TIMEBOUND)/float(fReach_TIMEDISCRETIZATION);

				//TODO remove
				std::cout << "fReach_Timebound: " << fReach_TIMEBOUND << std::endl;
				std::cout << "fReach_Timedisecretization: " << fReach_TIMEDISCRETIZATION << std::endl;
			   	std::cout <<  "Time Interval: ";
			   	std::cout << timeInterval << std::endl;

				//Polytope that is defined by the invariant
				hypro::Polytope<Number> poly = hypro::Polytope<Number>(_loc.invariant().mat, _loc.invariant().vec);

				//TODO remove
			   	std::cout << "invariant Polytope: ";
			    poly.print();

				//empty Flowpipe
				flowpipe_t<Number> flowpipe;

				//check if initial Valuation fulfills Invariant
				//alternatively: checkInvariant(_loc,_val)

				//TODO remove
				std::cout << "Valuation fulfills Invariant?: ";
				std::cout << poly.contains(_val) << std::endl;
				if ( poly.contains(_val) ) {

					//approximate R_[0,delta](X0)
					//rest is acquired by linear Transformation
					//R_0(X0) is just the initial Polytope X0, since t=0 -> At is 0 matrix -> e^(At) is Einheitsmatrix
					hypro::matrix_t<Number> deltaMatrix(_loc.activityMat().rows(),_loc.activityMat().cols());
					deltaMatrix = _loc.activityMat() * timeInterval;

					//TODO remove
				   	std::cout << "delta Matrix: " << std::endl;
				   	std::cout << deltaMatrix << std::endl;
				   	std::cout << "------" << std::endl;

					//e^(At) = resultMatrix
					hypro::matrix_t<Number> resultMatrix(deltaMatrix.rows(),deltaMatrix.cols());

					//---
					//TODO Workaround for:
					//resultMatrix = deltaMatrix.exp();
					//-> convert FLOAT_T to double, compute .exp(), then convert back to FLOAT_T

					Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> doubleMatrix(deltaMatrix.rows(),deltaMatrix.cols());
					Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> expMatrix(deltaMatrix.rows(),deltaMatrix.cols());
					doubleMatrix = hypro::convertMatToDouble(deltaMatrix);
					expMatrix = doubleMatrix.exp();
					resultMatrix = hypro::convertMatToFloatT(expMatrix);

					//TODO remove
				   	std::cout << "e^(deltaMatrix): " << std::endl;
				   	std::cout << resultMatrix << std::endl;
				   	std::cout << "------" << std::endl;

					//---

					//e^(At)*X0 = polytope at t=delta
					hypro::valuation_t<Number> deltaValuation;
					_val.linearTransformation(deltaValuation, resultMatrix);

					//TODO remove
				   	std::cout << "Polytope at t=delta: ";
				    deltaValuation.print();

					// R_0(X0) U R_delta(X0)
					hypro::valuation_t<Number> unitePolytope;
					_val.unite(unitePolytope, deltaValuation);

					//TODO remove
				   	std::cout << "Polytope after unite with R0: ";
				    unitePolytope.print();

					// CH( R_0(X0) U R_delta(X0) )
					hypro::valuation_t<Number> hullPolytope;
					unitePolytope.hull(hullPolytope);

					//TODO remove
				   	std::cout << "Convex Hull (Polytope): ";
				    hullPolytope.print();

					//bloat hullPolytope (Hausdorff distance)
					hypro::valuation_t<Number> firstSegment;
					Number radius;
					radius = _val.hausdorffError(timeInterval, _loc.activityMat());

				   	//TODO REMOVE
				   	radius = 1;

					//TODO remove
					std::cout << "\n";
				   	std::cout << "Hausdorff Approximation: ";
				    std::cout << radius << std::endl;

					unsigned int dim;
					dim = hullPolytope.dimension();

					//TODO remove
				   	std::cout << "Hull Polytope Dimension: " << hullPolytope.dimension() << std::endl;
				   	std::cout << "Delta Polytope Dimension: " << deltaValuation.dimension() << std::endl;
				   	std::cout << "Input Box Dimension: " << _val.dimension() << std::endl;

					/*
					 * Box
					hypro::Box<Number> hausBox = hypro::computeBox(dim,radius);

					// B + hullPolytope -> Konstruktor needed for Ball instead of Polytope?
					hullPolytope.minkowskiSum(firstSegment, hausBox);
					*/

					hypro::valuation_t<Number> hausPoly = hypro::computePolytope(dim, radius);

					//TODO remove
				   	std::cout << "Hausdorff Polytope (Box): ";
				    hausPoly.print();

					//hullPolytope +_minkowski hausPoly
					hullPolytope.minkowskiSum(firstSegment, hausPoly);

					//TODO remove
				   	std::cout << "first Flowpipe Segment (after minkowski Sum): ";
				    firstSegment.print();

					//insert first Segment into the empty flowpipe
					flowpipe.push_back(firstSegment);

					//set the last segment of the flowpipe
					hypro::valuation_t<Number> lastSegment;
					lastSegment = firstSegment;

					//for each time interval perform linear Transformation
					for (double i=2*timeInterval; i<=fReach_TIMEBOUND; i+=timeInterval) {

						std::cout << "i in Loop: " << i << std::endl;

						//Polytope after linear transformation
						hypro::valuation_t<Number> resultPolytope;

						/*
						//TODO remove
						std::cout << "--- Loop entered ---" << std::endl;
					   	std::cout << "in loop: delta: " << i << std::endl;

						//e^(A*delta), where delta is dependent on i
						hypro::matrix_t<Number> tempDelta(_loc.activityMat().rows(),_loc.activityMat().cols());
						//TODO check if this is correct
						tempDelta = _loc.activityMat() * i;
						hypro::matrix_t<Number> tempResult(tempDelta.rows(),tempDelta.cols());

						//TODO remove
					   	std::cout << "in loop: deltaMatrix: " << std::endl;
					   	std::cout << tempDelta << std::endl;
					   	std::cout << "------" << std::endl;

						//---
						//TODO Workaround for:
						//tempResult = tempDelta.exp();
						//-> convert FLOAT_T to double, compute .exp(), then convert back to FLOAT_T

						Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> tDoubleMatrix(tempDelta.rows(),tempDelta.cols());
						Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> tExpMatrix(tempDelta.rows(),tempDelta.cols());
						tDoubleMatrix = hypro::convertMatToDouble(tempDelta);
						tExpMatrix = tDoubleMatrix.exp();
						tempResult = hypro::convertMatToFloatT(tExpMatrix);

						//TODO remove
					   	std::cout << "in loop: e^(deltaMatrix): " << std::endl;
					   	std::cout << tempResult << std::endl;
					   	std::cout << "------" << std::endl;

						//---
						*/

						//perform linear transformation on the last segment of the flowpipe
						//lastSegment.linearTransformation(resultPolytope, tempResult);
						//TODO check: is this correct? e^(delta*A) never changes this way
						lastSegment.linearTransformation(resultPolytope, resultMatrix);

						//TODO remove
					   	std::cout << "Next Flowpipe Segment: ";
					    resultPolytope.print();

						//TODO remove
						std::cout << "still within Invariant?: ";
						std::cout << poly.contains(resultPolytope) << std::endl;

						//extend flowpipe (only if still within Invariant of location)
						if (poly.contains(resultPolytope)) {
							flowpipe.push_back(resultPolytope);

							//update lastSegment
							lastSegment = resultPolytope;
						} else {
							break;
						}
					}

					//TODO remove
					std::cout << "--- Loop left ---" << std::endl;

					return flowpipe;

				} else {
					//return an empty flowpipe
					return flowpipe;
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

                //TODO remove
                //std::cout << "Dimension: " << _val.dimension() << "(" << _val.rawPolyhedron().space_dimension() << ")" << std::endl;
                                
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
			static std::vector<flowpipe_t<Number>> computeReach(std::vector<flowpipe_t<Number>> _init, hypro::HybridAutomaton<Number> _hybrid,
					std::map<flowpipe_t<Number>, hypro::Location<Number>>& _map) {

				std::vector<flowpipe_t<Number>> reach;

				//for each flowpipe in _init
				for (typename std::vector<flowpipe_t<Number>>::iterator it_pipe = _init.begin(); it_pipe != _init.end(); ++it_pipe) {

					//get the location that belongs to the flowpipe
					hypro::Location<Number> loc = _map[*it_pipe];

					//polytope that belongs to the locations invariant
					//hypro::Polytope<Number> loc_inv = hypro::Polytope<Number>(loc.invariant().mat, loc.invariant().vec);

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

						//if new Flowpipe is not empty
						//(it is empty if even the first valuation/polytope does not satisfy the locations invariant)
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


			//TODO: time & step boundaries
    		template<typename Number>
			static std::vector<flowpipe_t<Number>> computeForwardsReachability(hypro::HybridAutomaton<Number> _hybrid) {

					std::vector<flowpipe_t<Number>> R_new;
					std::vector<flowpipe_t<Number>> R;

					std::map<flowpipe_t<Number>, hypro::Location<Number>> map;

					//R_new = initialState
					typename std::vector<hypro::Location<Number>*>::iterator it = _hybrid.initialLocations().begin();
					hypro::Location<Number> initLoc = *(*it);
					flowpipe_t<Number> init = computeForwardTimeClosure(initLoc, _hybrid.valuation());

					if (!init.empty()) {
						R_new.push_back(init);
					} else {
						//TODO
						//the initial Valuation for the polytope was not valid (with respect to the Initial Locations Invariant)
					}

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
						std::vector<flowpipe_t<Number>> R_temp = computeReach(R_new, _hybrid, map);
						std::set_difference(R_temp.begin(), R_temp.end(), R.begin(), R.end(),
											std::inserter(R_new, R_new.begin()));
					}
					return R;

			}

    };
}

