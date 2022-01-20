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
#include <hypro/datastructures/HybridAutomaton/PathUtil.h>
#include <hypro/datastructures/Hyperoctree.h>
#include <hypro/datastructures/reachability/ReachTreev2Util.h>
#include <hypro/parser/antlr4-flowstar/ParserWrapper.h>
#include <hypro/paths.h>
#include <hypro/util/plotting/Plotter.h>
#include <random>
#include <string>

/**
 * Controller-functor which allows to create random states (locations and variable valuations)
 * @tparam Number Used number type
 */
template <typename Number>
struct ctrl {
	hypro::Point<Number> operator()( std::size_t dimension ) {
		hypro::vector_t<double> coordinates = hypro::vector_t<double>( dimension );
		for ( std::size_t d = 0; d < dimension; ++d ) {
			// coordinates( d ) = dist( generator );
			coordinates( d ) = 0.5;
		}
		return hypro::Point<Number>{ coordinates };
	}

	hypro::Location<Number>* operator()( const hypro::HybridAutomaton<Number>& automaton ) {
		// std::uniform_int_distribution<int> loc_dist{ int(automaton.getLocations().size()) };
		std::uniform_int_distribution<int> loc_dist{ 2 };
		return automaton.getLocations()[0];
	}

	// std::mt19937 generator{};
	// std::uniform_real_distribution<Number> dist = std::uniform_real_distribution<Number>( 0, 1 );
};

template <typename Number>
hypro::Condition<Number> widenSample( const hypro::Point<Number>& sample, Number targetWidth ) {
	std::vector<carl::Interval<Number>> intervals;
	Number range = targetWidth / 2;
	for ( std::size_t i = 0; i < sample.dimension(); ++i ) {
		intervals.emplace_back( sample.at( i ) - range, sample.at( i ) + range );
	}
	return hypro::Condition<Number>{ intervals };
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
	// types
	using Number = double;
	using Representation = hypro::Box<Number>;
	// settings
	// TODO make command line
	std::size_t maxJumps = 15;
	Number widening = 0.1;
	std::string filename{ "21_simplex_watertanks_deterministic_monitor_small_init.model" };
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
	ctrl<Number> controller;
	// we store one octree per location
	std::map<const hypro::Location<Number>*, hypro::Hyperoctree<Number>> octrees;
	for ( const auto* locPtr : automaton.getLocations() ) {
		// octree to store reachable sets, here fixed to [0,1] in each dimension
		octrees.emplace( locPtr, hypro::Hyperoctree<Number>( 2, 6, hypro::Box<Number>{ std::vector<carl::Interval<Number>>{ carl::Interval<Number>{ 0, 1 }, carl::Interval<Number>{ 0, 1 } } } ) );
	}
	// maintain an instance of the plotter
	auto& plt = hypro::Plotter<Number>::getInstance();
	plt.clear();
	plt.rSettings().overwriteFiles = true;
	plt.rSettings().cummulative = true;
	plt.setFilename( "simplex_watertanks" );
	// main loop which alternatingly invokels the controller and if necessary the analysis (training phase) for a bounded number of iterations
	std::size_t iterations{ 10 };
	while ( iterations ) {
		--iterations;
		// create new controller point
		auto valuation = controller( 2 );
		auto* location = controller( automaton );
		COUT( "Chose sample " << valuation << " for location " << location->getName() << std::endl );
		// check containment, if not contained, update set of reachable states
		// TODO this still uses the projected set, need to figure this out.
		if ( !octrees.at( location ).contains( valuation.projectOn( { 0, 1 } ) ) ) {
			COUT( "Valuation not yet contained, run reachability analysis" << std::endl );
			// update plot
			plt.addPoint( valuation, hypro::plotting::colors[hypro::plotting::red] );
			// new reachability analysis
			// reachability tree
			std::vector<hypro::ReachTreeNode<Representation>> roots;
			// update initial states - set to small box around sample
			auto initialBox = widenSample( valuation, widening );
			// TODO: hardcoded
			hypro::matrix_t<Number> constraints = hypro::matrix_t<Number>::Zero( 4, 4 );
			hypro::vector_t<Number> constants = hypro::vector_t<Number>::Zero( 4 );
			constraints( 0, 0 ) = 1;
			constraints( 1, 0 ) = -1;
			constraints( 2, 1 ) = 1;
			constraints( 3, 1 ) = -1;
			constants( 0 ) = 0.0002;
			constants( 1 ) = -0.0002;
			constants( 2 ) = 0;
			constants( 3 ) = 0;
			initialBox.addConstraints( hypro::Condition<Number>( constraints, constants ) );
			hypro::HybridAutomaton<Number>::locationConditionMap initialStates;
			initialStates[location] = initialBox;
			automaton.setInitialStates( initialStates );
			// initialize reachtree
			roots = hypro::makeRoots<Representation>( automaton );
			// analysis
			auto reacher = hypro::reachability::Reach<Representation>( automaton, settings.fixedParameters(),
																	   settings.strategy().front(), roots );
			auto result = reacher.computeForwardReachability();
			// post processing
			if ( result != hypro::REACHABILITY_RESULT::SAFE ) {
				// TODO What now?
				std::cout << "System is not safe, need to deal with this." << std::endl;
				exit( 1 );
			} else {
				// update octree
				for ( const auto& r : roots ) {
					auto segments = getSegments( r );
					for ( const auto& s : segments ) {
						octrees.at( r.getLocation() ).add( s.projectOn( { 0, 1 } ) );
					}
				}
				assert( octrees.at( location ).contains( valuation.projectOn( { 0, 1 } ) ) );
				// update plot of the octree
				for ( const auto& [_, octree] : octrees ) {
					plotOctree( octree, plt );
				}
			}
		} else {
			plt.addPoint( valuation, hypro::plotting::colors[hypro::plotting::green] );
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
	plt.plot2d( hypro::PLOTTYPE::pdf );
	plt.plot2d( hypro::PLOTTYPE::gen );
	plt.plot2d( hypro::PLOTTYPE::tex );
	return 0;
}