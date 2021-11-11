/*
 * Copyright (c) 2021.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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

// types
using Representation = hypro::Box<double>;
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
			coordinates( d ) = disc_dist( generator ) * dist( generator );
		}
		return hypro::Point<Number>{ coordinates };
	}

	hypro::Location<Number>* operator()( const hypro::HybridAutomaton<Number>& automaton ) {
		auto val = loc_dist( generator );
		return automaton.getLocations().at( val );
	}

	controller_update<Number> generateInput( hypro::Location<Number> const* loc ) {
		return { loc, this->operator()() };
	}

	std::mt19937 generator;
	std::uniform_int_distribution<int> loc_dist{ 0, 23 };
	std::uniform_real_distribution<Number> dist = std::uniform_real_distribution<Number>( 0, 0.0005 );
	std::discrete_distribution<int> disc_dist = std::discrete_distribution( { 50, 50 } );
};

template <typename Number>
struct simulator {
	std::vector<std::pair<hypro::Location<Number> const*, std::vector<Representation>>> simulate( bool updateBaseController ) {
		// augment last state with controller update (e.g. set u), set clock to zero
		// set mLastState as initial state of the model
		// run simulation for cycle time (here: 1), pointify to potential new states
		// return computed simulation trace, set mPotentialNewState & location
		// TODO what if the plant is non-deterministic?

		mIsBaseControllerSimulator = updateBaseController;

		controller_update<Number> ctrlInput;
		if ( updateBaseController ) {
			ctrlInput = mBaseController.generateInput( mLastLocation );
		} else {
			ctrlInput = mAdvancedController.generateInput( mLastLocation );
		}
		// augment state with controller input
		mLastState[2] = ctrlInput.val.at( 0 );

		// call simulation as reachability analysis for a maximal time duration of 1 (cycle time)
		// TODO add functionality to run reachability analysis for a bounded global time
		// Workaround: compute larger set, post-process: cutoff all nodes in the tree reachable via a controller-jump.

		/*
		std::vector<hypro::ReachTreeNode<Representation>> roots;
		auto initialBox = hypro::Condition<Number>{ interval };
		hypro::HybridAutomaton<Number>::locationConditionMap initialStates;
		initialStates[sim.mLastLocation] = initialBox;
		automaton.setInitialStates( initialStates );
		// store initial set in octree - we know its cycle-time is zero
		octrees.at(sim.mLastLocation).add( hypro::Box<Number>(intervals));
		// initialize reachtree
		roots = hypro::makeRoots<Representation>( automaton );
		// analysis
		auto reacher = hypro::reachability::Reach<Representation>( automaton, settings.fixedParameters(),
																   settings.strategy().front(), roots );
		auto result = reacher.computeForwardReachability();
		*/
	}

	void updateState( bool updateBaseController ) {
		if ( ( updateBaseController && mIsBaseControllerSimulator ) || ( !updateBaseController && !mIsBaseControllerSimulator ) ) {
			mLastState = mPotentialNewState;
			mLastLocation = mPotentialNewLocation;
		} else {
			simulate( updateBaseController );
			mLastState = mPotentialNewState;
			mLastLocation = mPotentialNewLocation;
		}
	}

	ctrl<Number>& mBaseController;
	ctrl<Number>& mAdvancedController;
	hypro::HybridAutomaton<Number>& mAutomaton;
	hypro::Settings mSettings;
	hypro::Point<Number> mLastState;
	hypro::Location<Number> const* mLastLocation;
	hypro::Point<Number> mPotentialNewState;
	hypro::Location<Number> const* mPotentialNewLocation;
	bool mIsBaseControllerSimulator = true;
};

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

int main() {
	using Number = double;
	// settings
	// TODO make command line
	std::size_t maxJumps = 15;
	Number widening = 0.1;
	bool training = true;
	std::string filename{ "21_simplex_watertanks_deterministic_monitor_small_init.model" };
	// constraints for cycle-time equals zero, encodes t <= 0 && -t <= -0
	hypro::matrix_t<Number> constraints = hypro::matrix_t<Number>::Zero( 2, 5 );
	hypro::vector_t<Number> constants = hypro::vector_t<Number>::Zero( 2, 5 );
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
	plt.setFilename( "simplex_watertanks_loop" );
	// main loop which alternatingly invokels the controller and if necessary the analysis (training phase) for a bounded number of iterations
	std::size_t iterations{ 10 };
	// initialize system
	sim.mLastState = automaton.getInitialStates().begin()->second.getInternalPoint().value();
	sim.mLastLocation = automaton.getInitialStates().begin()->first;
	// initial first reachability analysis for the initial point
	// new reachability analysis
	// reachability tree
	std::vector<hypro::ReachTreeNode<Representation>> roots;
	// update initial states - set to small box around sample
	auto intervals = widenSample( sim.mLastState, widening );
	auto initialBox = hypro::Condition<Number>{ intervals };
	hypro::HybridAutomaton<Number>::locationConditionMap initialStates;
	initialStates[sim.mLastLocation] = initialBox;
	automaton.setInitialStates( initialStates );
	// store initial set in octree - we know its cycle-time is zero
	octrees.at( sim.mLastLocation ).add( hypro::Box<Number>( intervals ) );
	// initialize reachtree
	roots = hypro::makeRoots<Representation>( automaton );
	// analysis
	auto reacher = hypro::reachability::Reach<Representation>( automaton, settings.fixedParameters(),
															   settings.strategy().front(), roots );
	auto result = reacher.computeForwardReachability();
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

	while ( iterations ) {
		--iterations;

		// 1 simulation advanced controller, starting from initialvalue & location
		auto simulationSets = sim.simulate( false );

		// if all safe & last point in reach set, pointify resulting set, update initialstate, update monitor (current point)
		bool advControllerUnsafe = false;
		for ( auto it = simulationSets.begin(); it != simulationSets.end(); ) {
			for ( auto sit = it->second.begin(); sit != it->second.end(); ) {
				auto [containment, _] = hypro::ltiIntersectBadStates( *sit, it->first, automaton );
				if ( containment != hypro::CONTAINMENT::NO ) {
					// bad state reached -> use base controller
					advControllerUnsafe = true;
					break;
				}
			}
			if ( advControllerUnsafe ) {
				break;
			}
		}
		if ( advControllerUnsafe ) {
			// use base controller as fallback since the advanced controller seem to be unsafe
			sim.updateState( true );
			continue;
		}
		// at this point simulationSets is safe, the simulator knows the new initial state
		if ( octrees.at( sim.mPotentialNewLocation ).contains( sim.mPotentialNewState ) ) {
			// if no new states have been discovered by simulation, continue, i.e., write new state from advanced controller as initial state of the simulator for the next iteration
			sim.updateState( false );
		} else {
			if ( training ) {
				// if not in reach set: take new part, run base controller reachability analysis on this part
				// TODO This all only works, if the plant is deterministic

				initialStates.clear();
				initialStates[sim.mPotentialNewLocation] = hypro::Condition<Number>( widenSample( sim.mPotentialNewState, widening ) );
				automaton.setInitialStates( initialStates );
				// initialize reachtree
				roots = hypro::makeRoots<Representation>( automaton );
				// analysis
				auto reacher = hypro::reachability::Reach<Representation>( automaton, settings.fixedParameters(),
																		   settings.strategy().front(), roots );
				auto result = reacher.computeForwardReachability();
				// post processing
				if ( result != hypro::REACHABILITY_RESULT::SAFE ) {
					//// else switch to base controller, continue: simulate base controller, update sample (use monitor for this)
					// write new state - effectively simulates and uses base controller
					sim.updateState( true );
				} else {
					//// if resulting analysis is safe, continue with advanced controller (pointify sample, update initial states), add to octree
					sim.updateState( false );
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
				sim.updateState( true );
			}
		}
	}

	/*
	for ( const auto& node : hypro::preorder( roots ) ) {
		for ( const auto& segment : node.getFlowpipe() ) {
			if ( node.hasFixedPoint() == TRIBOOL::TRUE ) {
				plt.addObject( segment.projectOn( { 0, 1 } ).vertices(),
							   hypro::plotting::colors[hypro::plotting::blue] );
			} else if ( node.hasFixedPoint() == TRIBOOL::FALSE ) {
				plt.addObject( segment.projectOn( { 0, 1 } ).vertices(),
							   hypro::plotting::colors[hypro::plotting::orange] );
			} else {
				plt.addObject( segment.projectOn( { 0, 1 } ).vertices() );
			}
		}
	}
	 */

	plt.plot2d( hypro::PLOTTYPE::png );
	plt.plot2d( hypro::PLOTTYPE::gen );
	plt.plot2d( hypro::PLOTTYPE::tex );
	return 0;
}