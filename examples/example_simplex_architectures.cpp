/*
 * Copyright (c) 2021.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created by Stefan Schupp <stefan.schupp@tuwien.ac.at> on 28.10.21.
 */

#include <hypro/algorithms/reachability/Reach.h>
#include <hypro/algorithms/reachability/handlers/badStateHandlers/ltiBadStateHandler.h>
#include <hypro/datastructures/Hyperoctree.h>
#include <hypro/datastructures/reachability/ReachTreev2Util.h>
#include <hypro/parser/antlr4-flowstar/ParserWrapper.h>
#include <hypro/paths.h>
#include <hypro/util/linearOptimization/Optimizer.h>
#include <hypro/util/plotting/Plotter.h>
#include <random>
#include <string>

/* GENERAL ASSUMPTIONS */
// The model does *not* contain timelocks

// types
using Representation = hypro::Box<double>;
using Loc = hypro::Location<double> const*;
using Point = hypro::Point<double>;
using Box = hypro::Box<double>;
// global constants
static const std::vector<std::size_t> interesting_dimensions{ 0, 1, 3 };
static const std::vector<std::size_t> controller_dimensions{ 2 };

template <typename Number>
struct controller_update {
	hypro::Location<Number> const* loc = nullptr;
	hypro::Point<Number> val{};
};

/**
 * Controller-functor which allows to create random states (locations and variable valuations)
 * @tparam Number Used number type
 */
template <typename Number>
struct ctrl {
	hypro::Point<Number> operator()() {
		hypro::vector_t<double> coordinates = hypro::vector_t<double>::Zero( 1 );
		for ( std::size_t d = 0; d < 1; ++d ) {
			// value is with 50% probability zero and some value between 0 and 0.0005 otherwise
//			coordinates( d ) = disc_dist( generator ) * dist( generator );
			coordinates( d ) = 0.0;
		}
		return hypro::Point<Number>{ coordinates };
	}

	hypro::Location<Number>* operator()( const hypro::HybridAutomaton<Number>& automaton ) {
		auto val = loc_dist( generator );
		return automaton.getLocations().at( val );
	}

	controller_update<Number> generateInput() {
		return { nullptr, this->operator()() };
	}

	std::mt19937 generator;
	std::uniform_int_distribution<int> loc_dist{ 0, 23 };
	// std::uniform_real_distribution<Number> dist = std::uniform_real_distribution<Number>( 0, 0.0005 );
	std::uniform_real_distribution<Number> dist = std::uniform_real_distribution<Number>( 0.0003, 0.0005 );
	std::discrete_distribution<int> disc_dist = std::discrete_distribution( { 10, 90 } );
};

template <typename R>
void cutoffControllerJumps( hypro::ReachTreeNode<R>* node ) {
	auto children = node->getChildren();
	for ( auto childIt = children.begin(); childIt != children.end(); ++childIt ) {
		if ( !( *childIt )->getTransition()->getReset().getAffineReset().isIdentity( 4 ) ) {
			(*childIt)->eraseChildren();
			( *childIt )->getFlowpipe().clear();
		} else {
			cutoffControllerJumps( *childIt );
		}
	}
}

template <typename Number>
struct simulator {
	// Assumptions: Hidden state variables of the specification are always clocks, we keep only the minimum and maximum in case simulation allows several values

	void pointify() {
		std::cout << "[Simulator] Pointify" << std::endl;
		std::map<Loc, Box> samplesBoxes;
		// create constraints which fix the observation
		hypro::matrix_t<Number> constraints = hypro::matrix_t<Number>::Zero( 2, 5 );
		hypro::vector_t<Number> constants = hypro::vector_t<Number>::Zero( 2 );
		// assign constraints: x1, x2 = observation, tick = cycle time
		/*
		// x1
		constraints( 0, 0 ) = 1;
		constraints( 1, 0 ) = -1;
		constants( 0 ) = observation.at( 0 );
		constants( 1 ) = -observation.at( 0 );
		// x2
		constraints( 2, 1 ) = 1;
		constraints( 3, 1 ) = -1;
		constants( 2 ) = observation.at( 1 );
		constants( 3 ) = -observation.at( 1 );
		 */
		// tick
		constraints( 0, 4 ) = 1;
		constraints( 1, 4 ) = -1;
//		constants( 0 ) = mCycleTime;
//		constants( 1 ) = -mCycleTime;
		constants( 0 ) = 0;
		constants( 1 ) = -0;
		// collect all leaf nodes that agree with the cycle time
		for ( auto& r : roots ) {
			for ( auto& n : hypro::preorder( r ) ) {
				if ( n.isLeaf() ) {
					// I don't think we really need this check. We only consider initial sets of nodes that where reached by resetting the clock to zero.
					auto [containment, result] = n.getInitialSet().satisfiesHalfspaces( constraints, constants );
					if ( containment != hypro::CONTAINMENT::NO ) {
						std::cout << "[Simulator] New sample: " << result << std::endl;
						if ( samplesBoxes.find( n.getLocation() ) != samplesBoxes.end() ) {
							samplesBoxes[n.getLocation()] = samplesBoxes[n.getLocation()].unite( result );
						} else {
							samplesBoxes[n.getLocation()] = result;
						}
					}
				}
			}
		}
		// create an artificial observation
		std::mt19937 generator;
		std::uniform_int_distribution<std::size_t> loc_dist{ 0, samplesBoxes.size() - 1 };
		std::size_t chosenloc = loc_dist( generator );
		Loc locptr = std::next( samplesBoxes.begin(), chosenloc )->first;
		Point observation = samplesBoxes.at( locptr ).vertices().front().projectOn( { 0, 1 } );
		std::cout << "[Simulator] Observation: " << observation << std::endl;
		// build constraints which represent the observation
		constraints = hypro::matrix_t<Number>::Zero( 4, 5 );
		constants = hypro::vector_t<Number>::Zero( 4 );
		// assign constraints: x1, x2 = observation
		// x1
		constraints( 0, 0 ) = 1;
		constraints( 1, 0 ) = -1;
		constants( 0 ) = observation.at( 0 );
		constants( 1 ) = -observation.at( 0 );
		// x2
		constraints( 2, 1 ) = 1;
		constraints( 3, 1 ) = -1;
		constants( 2 ) = observation.at( 1 );
		constants( 3 ) = -observation.at( 1 );
		// filter sample boxes for observation
		for ( auto& [_, box] : samplesBoxes ) {
			box = box.intersectHalfspaces( constraints, constants );
		}

		// collect concrete samples from samplesboxes
		mLastStates.clear();
		for ( auto& [loc, box] : samplesBoxes ) {
			auto tmp = box.vertices();
			if ( !tmp.empty() ) {
				mLastStates[loc] = std::set<Point>( tmp.begin(), tmp.end() );
				std::cout << "[Simulator] Add samples " << mLastStates[loc] << " to mLastStates (location: " << loc->getName() << ")" << std::endl;
				assert( mLastStates[loc].size() <= 2 );
			}
		}
	}

	bool simulate( bool updateBaseController ) {
		// augment last state with controller update (e.g. set u), set clock to zero
		// set mLastState as initial state of the model
		// run simulation for cycle time (here: 1), pointify to potential new states
		// return computed simulation trace, set mPotentialNewState & location
		// TODO what if the plant is non-deterministic?

		controller_update<Number> ctrlInput;
		if ( updateBaseController ) {
			// ctrlInput = mBaseController.generateInput();
			//  TODO add assertion which checks that all controller locations are the same in the samples
			auto locName = mLastStates.begin()->first->getName();
			ctrlInput.loc = mLastStates.begin()->first;
			if ( locName.find( "_open_" ) != std::string::npos ) {
				ctrlInput.val = Point( hypro::vector_t<Number>::Ones( 1 ) * 0.0002 );
			} else {
				ctrlInput.val = Point( hypro::vector_t<Number>::Zero( 1 ) );
			}
			std::cout << "[Simulator] Generated output for base controller, u = " << ctrlInput.val << std::endl;
		} else {
			ctrlInput = mAdvancedController.generateInput();
			std::cout << "[Simulator] Generated output for advanced controller, u = " << ctrlInput.val << std::endl;
		}

		// cleanup roots for new simulation run
		roots.clear();

		for ( const auto& [loc, samples] : mLastStates ) {
			for ( auto sample : samples ) {
				// augment state with controller input
				sample.at( 2 ) = ctrlInput.val.at( 0 );
				// create intervals representing the initial state
				std::vector<carl::Interval<Number>> intervals;
				for ( Eigen::Index i = 0; i < sample.dimension(); ++i ) {
					intervals.emplace_back( carl::Interval<Number>( sample.at( i ) ) );
				}
				auto initialBox = hypro::Condition<Number>{ intervals };
				typename hypro::HybridAutomaton<Number>::locationConditionMap initialStates;
				initialStates[loc] = initialBox;
				mAutomaton.setInitialStates( initialStates );
				auto sampleRoots = hypro::makeRoots<Representation>( mAutomaton );
				// add roots for this sample to global reachtree
				for ( auto&& sr : sampleRoots ) {
					roots.emplace_back( std::move( sr ) );
				}
				std::cout << "[Simulator] Add sample " << sample << " for simulation." << std::endl;
			}
		}

		// call simulation as reachability analysis for a maximal time duration of 1 (cycle time)
		// copy settings to adjust jump depth etc.
		mSettings.rFixedParameters().localTimeHorizon = carl::convert<double, hypro::tNumber>( mCycleTime );
		mSettings.rFixedParameters().jumpDepth = 2 * std::ceil( mCycleTime / carl::convert<hypro::tNumber, double>( mSettings.strategy().front().timeStep ) );
		// analysis
		auto reacher = hypro::reachability::Reach<Representation>( mAutomaton, mSettings.fixedParameters(),
																   mSettings.strategy().front(), roots );
		auto result = reacher.computeForwardReachability();

        // cutoff after cycle time
        // TODO add functionality to run reachability analysis for a bounded global time
        // Workaround: compute larger set, post-process: cutoff all nodes in the tree reachable via a controller-jump.
        // note: in the system there is no trajectory with lenght longer than cycle time since the controller is definitely invoked after this time on any execution path.
        for (auto &root: roots) {
            cutoffControllerJumps(&root);
        }

        // return safety result
        // dbg
        std::cout << "[Simulator] simulate safety result: " << result << std::endl;
        return (result == hypro::REACHABILITY_RESULT::SAFE);
    }

	ctrl<Number>& mBaseController;
	ctrl<Number>& mAdvancedController;
	hypro::HybridAutomaton<Number>& mAutomaton;
	hypro::Settings mSettings;
	double mCycleTime = 1.0;
	std::vector<hypro::ReachTreeNode<Representation>> roots;
	std::map<Loc, std::set<Point>> mLastStates;
};

template <typename N>
static Point generateObservation( const simulator<N>& sim ) {
	std::mt19937 generator;
	std::uniform_int_distribution<std::size_t> loc_dist{ 0, sim.mLastStates.size() - 1 };
	std::size_t chosenloc = loc_dist( generator );
	Loc locptr = std::next( sim.mLastStates.begin(), chosenloc )->first;
	std::uniform_int_distribution<std::size_t> point_dist{ 0, sim.mLastStates.at( locptr ).size() - 1 };
	return std::next( sim.mLastStates.at( locptr ).begin(), point_dist( generator ) )->projectOn( { 0, 1 } );
}

template <typename Number>
std::vector<carl::Interval<Number>> widenSample( const hypro::Point<Number>& sample, Number targetWidth ) {
	std::vector<carl::Interval<Number>> intervals = std::vector<carl::Interval<Number>>( 5, carl::Interval<Number>( 0 ) );
	Number range = targetWidth / 2;
	for ( std::size_t i = 0; i < sample.dimension(); ++i ) {
		if ( std::find( interesting_dimensions.begin(), interesting_dimensions.end(), i ) != interesting_dimensions.end() ) {
			intervals[i] = carl::Interval<Number>( sample.at( i ) - range, sample.at( i ) + range );
		} else {
			intervals[i] = carl::Interval<Number>( sample.at( i ) );
		}
	}
	return intervals;
}

void plotOctree( const hypro::Hyperoctree<double>& octree, hypro::Plotter<double>& plt ) {
	if ( octree.isCovered() ) {
		plt.addObject( octree.getContainer().projectOn( { 0, 1 } ).vertices(),
					   hypro::plotting::colors[hypro::plotting::green] );
	} else {
		if ( !octree.getChildren().empty() ) {
			for ( const auto& child : octree.getChildren() ) {
				plotOctree( *child, plt );
			}
		} else {
			plt.addObject( octree.getContainer().projectOn( { 0, 1 } ).vertices(),
						   hypro::plotting::colors[hypro::plotting::red] );
		}
	}
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnreachableCode"
int main() {
	using Number = double;
	// settings
	// TODO make command line
	std::size_t iterations{ 50 };
	std::size_t iteration_count{ 0 };
	std::size_t maxJumps = 75;
	Number widening = 0.1;
	bool training = true;
	std::string filename{ "21_simplex_watertanks_deterministic_monitor_dbg_init_ticks.model" };
	// constraints for cycle-time equals zero, encodes t <= 0 && -t <= -0
	hypro::matrix_t<Number> constraints = hypro::matrix_t<Number>::Zero( 2, 5 );
	hypro::vector_t<Number> constants = hypro::vector_t<Number>::Zero( 2 );
	constraints( 0, 4 ) = 1;
	constraints( 1, 4 ) = -1;
	// parse model
	auto [automaton, reachSettings] = hypro::parseFlowstarFile<Number>( hypro::getCSModelsPath() + filename );
	// reachability analysis settings
	auto settings = hypro::convert( reachSettings );
	settings.rStrategy().front().detectJumpFixedPoints = true;
	settings.rStrategy().front().detectFixedPointsByCoverage = false;
	settings.rStrategy().front().detectContinuousFixedPointsLocally = false;
	settings.rFixedParameters().localTimeHorizon = 100;
	settings.rFixedParameters().jumpDepth = maxJumps;
	settings.rStrategy().begin()->aggregation = hypro::AGG_SETTING::AGG;
	// random controller
	ctrl<Number> baseCtrl;
	ctrl<Number> advCtrl;
	// monitor
	simulator<Number> sim{ baseCtrl, advCtrl, automaton, settings };
	// we store one octree per location
	std::map<const hypro::Location<Number>*, hypro::Hyperoctree<Number>> octrees;
	for ( const auto* locPtr : automaton.getLocations() ) {
		// octree to store reachable sets, here fixed to [0,1] in each dimension
		octrees.emplace( locPtr, hypro::Hyperoctree<Number>( 2, 6, hypro::Box<Number>{ std::vector<carl::Interval<Number>>{ carl::Interval<Number>{ 0, 1 }, carl::Interval<Number>{ 0, 1 }, carl::Interval<Number>{ 0, 15 } } } ) );
	}
	// maintain an instance of the plotter
	auto& plt = hypro::Plotter<Number>::getInstance();
	plt.clear();
	plt.rSettings().overwriteFiles = true;
	plt.rSettings().cummulative = false;
	plt.rSettings().xPlotInterval = carl::Interval<double>( 0, 1 );
	plt.rSettings().yPlotInterval = carl::Interval<double>( 0, 1 );
	// initialize system
	auto intialLocation = automaton.getInitialStates().begin()->first;
	auto initialValuation = automaton.getInitialStates().begin()->second.getInternalPoint().value();
	sim.mLastStates[intialLocation] = { initialValuation };
	// initial first reachability analysis for the initial point
	// new reachability analysis
	// reachability tree
	std::vector<hypro::ReachTreeNode<Representation>> roots;
	// update initial states - set to small box around sample
	auto intervals = widenSample( initialValuation, widening );
	auto initialBox = hypro::Condition<Number>{ intervals };
	hypro::HybridAutomaton<Number>::locationConditionMap initialStates;
	initialStates[intialLocation] = initialBox;
	automaton.setInitialStates( initialStates );
	// store initial set in octree - we know its cycle-time is zero
	octrees.at( intialLocation ).add( hypro::Box<Number>( intervals ) );
	// initialize reachtree
	roots = hypro::makeRoots<Representation>( automaton );
	// analysis
	auto reacher = hypro::reachability::Reach<Representation>( automaton, settings.fixedParameters(),
															   settings.strategy().front(), roots );
	std::cout << "Run initial analysis ... " << std::flush;
	auto result = reacher.computeForwardReachability();
    std::cout << "done, result: " << result << std::endl;
	// post processing
	if ( result != hypro::REACHABILITY_RESULT::SAFE ) {
		std::cout << "System is initially not safe, need to deal with this." << std::endl;
		exit( 1 );
	} else {
		// update octree
		for ( const auto& r : roots ) {
			for ( const auto& node : hypro::preorder( r ) ) {
				for ( const auto& s : node.getFlowpipe() ) {
					// only store segments which contain states where the cycle time is zero
					if ( s.satisfiesHalfspaces( constraints, constants ).first != hypro::CONTAINMENT::NO ) {
						octrees.at( node.getLocation() ).add( s.projectOn( interesting_dimensions ) );
					}
				}
			}
		}
	}

	/* PLOTTING AFTER FIRST INIT */
	for ( const auto& node : hypro::preorder( roots ) ) {
		for ( const auto& segment : node.getFlowpipe() ) {
			if ( node.hasFixedPoint() == hypro::TRIBOOL::TRUE ) {
				plt.addObject( segment.projectOn( { 0, 1 } ).vertices(),
							   hypro::plotting::colors[hypro::plotting::blue] );
			} else if ( node.hasFixedPoint() == hypro::TRIBOOL::FALSE ) {
				plt.addObject( segment.projectOn( { 0, 1 } ).vertices(),
							   hypro::plotting::colors[hypro::plotting::orange] );
			} else {
				plt.addObject( segment.projectOn( { 0, 1 } ).vertices() );
			}
		}
	}
	plt.setFilename( "simplex_watertanks_loop_" + std::to_string( iteration_count ) );
	plt.plot2d( hypro::PLOTTYPE::png );
	plt.clear();

	// main loop which alternatingly invokels the controller and if necessary the analysis (training phase) for a bounded number of iterations
	while ( iteration_count < iterations ) {
		++iteration_count;
		std::cout << "Iteration " << iteration_count << std::endl;

		// 1 simulation advanced controller, starting from initialvalue & location
		std::cout << "Start advanced controller simulation." << std::endl;
		bool advControllerSafe = sim.simulate( false );

		// if all safe & last point in reach set, pointify resulting set, update initialstate, update monitor (current point)
		if ( !advControllerSafe ) {
			// use base controller as fallback since the advanced controller seem to be unsafe
			std::cout << "Advanced controller is not safe, simulate base-controller, continue with next iteration." << std::endl;
			sim.simulate( true );
			sim.pointify();
			continue;
		}
		std::cout << "Advanced controller is safe, check if resulting simulation traces are in the octree." << std::endl;
		// at this point simulationSets is safe, the simulator knows the new initial state
		std::map<Loc, std::vector<Box>> unknownSamples;
		for ( const auto& r : sim.roots ) {
			for ( const auto& n : hypro::preorder( r ) ) {
				if ( n.isLeaf() && !octrees.at( n.getLocation() ).contains( n.getInitialSet().projectOn( interesting_dimensions ) ) ) {
					unknownSamples[n.getLocation()].push_back( n.getInitialSet() );
				}
			}
		}
		if ( unknownSamples.empty() ) {
			// if no new states have been discovered by simulation, continue, i.e., write new state from advanced controller as initial state of the simulator for the next iteration
			std::cout << "Advanced controller traces are in the octree." << std::endl;
			sim.pointify();
		} else {
			std::cout << "Advanced controller traces are not all in the octree." << std::endl;
			if ( training ) {
				std::cout << "Start training with " << unknownSamples.size() << " locations." << std::endl;
//				std::cout << "Start training with samples: " << unknownSamples << std::endl;
				// if not in reach set: take new part, run base controller reachability analysis on this part

				// initialize reachtree
				roots.clear();
				std::size_t initialstateCount{ 0 };
				for ( const auto& [loc, boxes] : unknownSamples ) {
					for ( const auto& box : boxes ) {
						initialStates.clear();
						// initialStates[loc] = hypro::Condition<Number>( widenSample( sim.mPotentialNewState, widening ) );
						// set sample u-value to the correct value (corresponding to the value the base controller would have chosen, this can be obtained from the location name)
						auto newintervals = box.intervals();
						if ( loc->getName().find( "_open_" ) != std::string::npos ) {
							newintervals[2] = carl::Interval<Number>( 0.0002 );
						} else {
							newintervals[2] = carl::Interval<Number>( 0.0 );
						}
						initialStates[loc] = hypro::Condition<Number>( newintervals );
						automaton.setInitialStates( initialStates );
						auto tmp = hypro::makeRoots<Representation>( automaton );
						std::for_each( std::begin( tmp ), std::end( tmp ), [&roots]( auto&& node ) { roots.emplace_back( std::move( node ) ); } );
						++initialstateCount;
					}
				}
				std::cout << "Set " << initialstateCount << " initial states for training, start analysis ... " << std::flush;

				// analysis
				auto reacher = hypro::reachability::Reach<Representation>( automaton, settings.fixedParameters(),
																		   settings.strategy().front(), roots );
				auto result = reacher.computeForwardReachability();
                std::cout << " done, result: " << result << std::endl;
				// post processing
				if ( result != hypro::REACHABILITY_RESULT::SAFE ) {
					//// else switch to base controller, continue: simulate base controller, update sample (use monitor for this)
					// write new state - effectively simulates and uses base controller
					// TODO this is ovely conservative, we could at least store results for samples (roots) that were safe.
					std::cout << "Advanced controller is not safe on the long run, simulate base-controller, continue with next iteration." << std::endl;
					sim.simulate( true );
					sim.pointify();
				} else {
					//// if resulting analysis is safe, continue with advanced controller (pointify sample, update initial states), add to octree
					std::cout << "Advanced controller is safe on the long run, update octree with new sets, continue with next iteration." << std::endl;
					sim.pointify();
					// update octree
					for ( const auto& r : roots ) {
						for ( const auto& node : hypro::preorder( r ) ) {
							for ( const auto& s : node.getFlowpipe() ) {
								// only store segments which contain states where the cycle time is zero
								if ( s.satisfiesHalfspaces( constraints, constants ).first != hypro::CONTAINMENT::NO ) {
									octrees.at( node.getLocation() ).add( s.projectOn( interesting_dimensions ) );
								}
							}
						}
					}
				}
			} else {
				// we are not training and the sample is not yet known to be safe, switch to base controller
				std::cout << "We are not training, simulate base controller, continue with next iteration." << std::endl;
				sim.simulate( true );
				sim.pointify();
			}
		}

		for ( const auto& node : hypro::preorder( roots ) ) {
			for ( const auto& segment : node.getFlowpipe() ) {
				if ( node.hasFixedPoint() == hypro::TRIBOOL::TRUE ) {
					plt.addObject( segment.projectOn( { 0, 1 } ).vertices(),
								   hypro::plotting::colors[hypro::plotting::blue] );
				} else if ( node.hasFixedPoint() == hypro::TRIBOOL::FALSE ) {
					plt.addObject( segment.projectOn( { 0, 1 } ).vertices(),
								   hypro::plotting::colors[hypro::plotting::orange] );
				} else {
					plt.addObject( segment.projectOn( { 0, 1 } ).vertices() );
				}
			}
		}
		plt.setFilename( "simplex_watertanks_loop_" + std::to_string( iteration_count ) );
		plt.plot2d( hypro::PLOTTYPE::png );
		plt.clear();
	}

	return 0;
}
#pragma clang diagnostic pop