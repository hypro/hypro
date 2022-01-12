/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created by stefan on 04.08.21.
 */

#include <benchmark/benchmark.h>
#include <hypro/algorithms/reachability/Reach.h>
#include <hypro/datastructures/HybridAutomaton/PathUtil.h>
#include <hypro/datastructures/Hyperoctree.h>
#include <hypro/datastructures/reachability/ReachTreev2Util.h>
#include <hypro/parser/antlr4-flowstar/ParserWrapper.h>
#include <hypro/paths.h>
#include <hypro/util/logging/Logger.h>
#include <hypro/util/plotting/Plotter.h>
#include <random>
#include <string>

namespace hypro::benchmark {

void plotRecursive( const hypro::Hyperoctree<double>& octree, hypro::Plotter<double>& plt ) {
	if ( octree.isCovered() ) {
		plt.addObject( octree.getContainer().projectOn( { 0, 1 } ).vertices(),
					   hypro::plotting::colors[hypro::plotting::green] );
	} else {
        if (!octree.getChildren().empty()) {
            for (const auto &child: octree.getChildren()) {
                plotRecursive(*child, plt);
            }
        } else {
            plt.addObject(octree.getContainer().projectOn({0, 1}).vertices(),
                          hypro::plotting::colors[hypro::plotting::red]);
        }
    }
}

    template<typename R>
    void addPathChronologously(const hypro::ReachTreeNode<R> *node, hypro::Plotter<typename R::NumberType> &plt) {
        if (node != nullptr) {
            // recursive call to keep order
            addPathChronologously(node->getParent(), plt);
            // add segments of the current node
            for (const auto &seg: node->getFlowpipe()) {
                plt.addObject(seg.projectOn({0, 1}).vertices());
            }
        }
    }

    template<class Representation>
    static void Simplex_Watertanks_Reachability(::benchmark::State &state) {
        // store arguments
        std::size_t maxJumps = state.range(0);
        // clear statistics
        RESET_STATS();
        // Perform setup here
        using Number = double;
        std::string filename{"21_simplex_watertanks_deterministic_monitor_dbg_init_ticks.model"};
	auto& plt = hypro::Plotter<Number>::getInstance();

	auto [automaton, reachSettings] = hypro::parseFlowstarFile<Number>( getCSModelsPath() + filename );

	auto settings = hypro::convert( reachSettings );
    settings.rStrategy().front().detectJumpFixedPoints = true;
    settings.rStrategy().front().detectFixedPointsByCoverage = true;
    settings.rStrategy().front().detectContinuousFixedPointsLocally = true;
    settings.rFixedParameters().localTimeHorizon = 20;
    settings.rFixedParameters().jumpDepth = maxJumps;
    settings.rStrategy().begin()->aggregation = AGG_SETTING::AGG;
    std::vector<std::pair<const hypro::Path<Number>, hypro::ReachTreeNode<Representation> const *>> last_paths{};

    std::vector<ReachTreeNode<Representation>> roots;

    // artificially bloat dimensions 0,1,3 to a width of 0.01
    auto initialStates = automaton.getInitialStates();
    for (auto &[loc, condition]: initialStates) {
        auto box = hypro::Box<Number>(condition.getMatrix(), condition.getVector());
        auto intervals = box.intervals();
        for (std::size_t i = 0; i < 5; ++i) {
            if (i == 0 || i == 1 || i == 3) {
                intervals[i] = carl::Interval<Number>(intervals[i].lower() - 0.05, intervals[i].upper() + 0.05);
            }
        }
        condition = hypro::Condition<Number>(intervals);
    }
    automaton.setInitialStates(initialStates);

    for (auto _: state) {
        // This code gets timed
        last_paths.clear();
        roots = hypro::makeRoots<Representation>(automaton);
        auto reacher = hypro::reachability::Reach<Representation>(automaton, settings.fixedParameters(),
                                                                  settings.strategy().front(), roots);
        auto result = reacher.computeForwardReachability();
        INFO("hypro.casestudies", "System is safe: " << result);

        // statistics
        auto finished_leaves = std::size_t(0);
        auto unfinished_leaves = std::size_t(0);
        auto timelock_leaves = std::size_t(0);
        auto leaves = std::size_t(0);
        auto nodes = std::size_t(0);
        auto cyclic_path_count = std::size_t(0);
        auto segments = std::size_t(0);
        std::optional<hypro::Path<Number>> shortest{std::nullopt};
        const hypro::ReachTreeNode<Representation> *shortest_node{nullptr};
        std::optional<hypro::Path<Number>> shortest_timelock{std::nullopt};
        const hypro::ReachTreeNode<Representation> *shortest_timelock_node{nullptr};
        std::optional<hypro::Path<Number>> shortest_cycle{std::nullopt};
        const hypro::ReachTreeNode<Representation> *shortest_cycle_node{nullptr};

        for (const ReachTreeNode<Representation> &node: hypro::preorder(roots)) {
            ++nodes;
            segments += node.getFlowpipe().size();
            if (node.getChildren().empty()) {
                if (node.hasFixedPoint() == TRIBOOL::TRUE) {
                    ++finished_leaves;
                } else if (node.hasTimelock()) {
                    ++timelock_leaves;
                    if (!shortest_timelock || node.getPath().elements.size() < shortest_timelock.value().elements.size()) {
                        shortest_timelock = node.getPath();
                        shortest_timelock_node = &node;
                    }
                } else {
                    ++unfinished_leaves;
                    last_paths.push_back(std::make_pair(node.getPath(), &node));
                    if (has_discrete_cycle(node.getPath())) {
                        //INFO("hypro.casestudies", "Path " << node.getPath() << " is cyclic.");
                        ++cyclic_path_count;
                        if (!shortest_cycle ||
                            node.getPath().elements.size() < shortest_cycle.value().elements.size()) {
                            shortest_cycle = node.getPath();
                            shortest_cycle_node = &node;
                        }
                    } else {
                        //INFO("hypro.casestudies", "Path " << node.getPath() << " is truly unfinished.");
                        if (!shortest || node.getPath().elements.size() < shortest.value().elements.size()) {
                            shortest = node.getPath();
                            shortest_node = &node;
                        }
                    }
                }
                ++leaves;
                COUNT("leaves");
            }
        }
        // state.counters["fin.leaves"] = double( double( finished_leaves ) / double( leaves ) );
        // state.counters["nfin.leaves"] = double( double( unfinished_leaves ) / double( leaves ) );
        state.counters["#fin.leaves"] = ::benchmark::Counter(finished_leaves, ::benchmark::Counter::kAvgIterations);
        state.counters["#nfin.leaves"] =
                ::benchmark::Counter(unfinished_leaves, ::benchmark::Counter::kAvgIterations);
        state.counters["#timelock.leaves"] =
                ::benchmark::Counter(timelock_leaves, ::benchmark::Counter::kAvgIterations);
        state.counters["leaves"] = ::benchmark::Counter(leaves, ::benchmark::Counter::kAvgIterations);
        state.counters["jumps"] = ::benchmark::Counter(maxJumps, ::benchmark::Counter::kAvgIterations);
        state.counters["nodes"] = ::benchmark::Counter(nodes, ::benchmark::Counter::kAvgIterations);
        state.counters["cycles"] = ::benchmark::Counter(cyclic_path_count, ::benchmark::Counter::kAvgIterations);
        state.counters["segments"] = ::benchmark::Counter(segments, ::benchmark::Counter::kAvgIterations);
#ifdef HYPRO_STATISTICS
        state.counters["fp-cov"] = hypro::Statistician::getInstance().getCounter( "FP-by-coverage" ).val;
#endif
        if (shortest) {
            std::cout << "Shortest non-cyclic, unfinished path (length " << shortest.value().elements.size() << "): " << shortest.value() << std::endl;
            plt.clear();
            plt.rSettings().overwriteFiles = true;
            plt.rSettings().cummulative = false;
            plt.setFilename("shortest_unfinished_path_" + std::to_string(maxJumps) + "_jumps");
            addPathChronologously(shortest_node, plt);
            plt.plot2d(hypro::PLOTTYPE::pdf);
        }
		if ( shortest_cycle ) {
            std::cout << "Shortest cyclic, unfinished path (length " << shortest_cycle.value().elements.size() << "): " << shortest_cycle.value() << std::endl;
            std::cout << "Initial set of the last node (@" << shortest_cycle_node << "): " << shortest_cycle_node->getInitialSet() << std::endl;
            auto[containment, segment] = intersect(shortest_cycle_node->getInitialSet(), shortest_cycle_node->getLocation()->getInvariant());
            std::cout << "Initial set is in the invariant: " << containment << ", resulting set: " << segment << std::endl;
            std::cout << "Node depth: " << shortest_cycle_node->getDepth() << std::endl;
            std::cout << "FLAGS: fixed-point: " << (shortest_cycle_node->hasFixedPoint() == TRIBOOL::TRUE) << ", is on Zeno-cycle: " << shortest_cycle_node->isOnZenoCycle() << ", has timelock: " <<
                      shortest_cycle_node->hasTimelock() << ", bad states visited: " << shortest_cycle_node->intersectedUnsafeRegion() << std::endl;
            std::cout << "Flowpipe of the last node:\n";
            for (const auto &seg: shortest_cycle_node->getFlowpipe()) {
                std::cout << seg << "\n";
            }
            std::cout << std::endl;
            plt.clear();
            plt.rSettings().overwriteFiles = true;
            plt.rSettings().cummulative = true;
            plt.setFilename("shortest_cyclic_path");
            addPathChronologously(shortest_cycle_node, plt);
            plt.plot2d(hypro::PLOTTYPE::pdf);
            plt.plot2d(hypro::PLOTTYPE::gen);
        }
        if (shortest_timelock) {
            std::cout << "Shortest timelock path (length " << shortest_timelock.value().elements.size() << "): " << shortest_timelock.value() << std::endl;
            plt.clear();
            plt.rSettings().overwriteFiles = true;
            plt.rSettings().cummulative = true;
            plt.setFilename("shortest_timelock_path");
            addPathChronologously(shortest_timelock_node, plt);
            plt.plot2d(hypro::PLOTTYPE::pdf);
            plt.plot2d(hypro::PLOTTYPE::gen);
        }
    }

	// only plot the last run
	// plottingtrue
	plt.clear();
	plt.rSettings().overwriteFiles = true;
	plt.rSettings().cummulative = false;
	plt.setFilename( "simplex_watertanks" );

	/*
	// create hyperoctree
	auto bbox = computeBoundingBox( roots ).projectOn( { 0, 1 } );
	// widen dimensions until they are integer to increase stability
	for ( auto& interval : bbox.rIntervals() ) {
		interval = carl::Interval<double>( std::floor( interval.lower() ), std::ceil( interval.upper() ) );
	}

	hypro::Hyperoctree<Number> octree{ 2, 6, bbox };
	// add to hyperoctree
	for ( const auto& r : roots ) {
		auto segments = getSegments( r );
		for ( const auto& s : segments ) {
			octree.add( s.projectOn( { 0, 1 } ) );
		}
	}

	// test some random points

	std::mt19937 generator;
	std::uniform_real_distribution<double> dist = std::uniform_real_distribution<double>( 0, 1 );
	for ( std::size_t i = 0; i < 100; ++i ) {
		hypro::vector_t<double> coordinates = hypro::vector_t<double>( 2 );
		for ( std::size_t d = 0; d < 2; ++d ) {
			coordinates( d ) = dist( generator );
		}
		hypro::Point<double> point{ coordinates };
		if ( octree.contains( point ) ) {
			plt.addPoint( point, hypro::plotting::colors[hypro::plotting::green] );
		} else {
			plt.addPoint( point, hypro::plotting::colors[hypro::plotting::red] );
		}
	}
	 */

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

	// plot octree
	// plotRecursive( octree, plt );

	plt.plot2d( hypro::PLOTTYPE::png );
	plt.plot2d( hypro::PLOTTYPE::pdf );
	plt.plot2d( hypro::PLOTTYPE::gen );
	plt.plot2d( hypro::PLOTTYPE::tex );

	// output unfinished paths
	std::string channel =
		  "benchmark.paths." +
		  std::to_string( carl::convert<tNumber, double>( settings.strategy().begin()->timeStep ) ) + "_delta." +
		  std::to_string( carl::convert<hypro::tNumber, double>( settings.fixedParameters().localTimeHorizon ) ) +
		  "_TH." + std::to_string( state.range( 0 ) ) + "_jumps";
	TRACE( channel, "#################################################" );
	*/
	std::cout << "Start plotting, " << std::to_string( last_paths.size() ) << " paths." << std::endl;
	std::size_t path_count{ 0 };
	for ( auto [path, leaf] : last_paths ) {
        // TRACE( channel, path );
        plt.clear();
        plt.rSettings().overwriteFiles = true;
        plt.rSettings().cummulative = false;
        plt.setFilename("unfinished_" + std::to_string(maxJumps) + "_jumps_" + std::to_string(path_count));
        std::ofstream filestream;
        filestream.open("unfinished_" + std::to_string(maxJumps) + "_jumps_" + std::to_string(path_count) + ".txt");
        filestream << path << std::endl;
        filestream.close();
        addPathChronologously(leaf, plt);
        plt.plot2d(hypro::PLOTTYPE::png);
        //std::cout << "Plotted path " << std::to_string( path_count ) << std::endl;
        ++path_count;
    }
	PRINT_STATS()
}
// Register the function as a benchmark
// BENCHMARK_TEMPLATE( Simplex_Watertanks_Reachability, hypro::SupportFunction<double> )->DenseRange(1, 3, 1);
BENCHMARK_TEMPLATE( Simplex_Watertanks_Reachability, hypro::Box<double> )
        ->DenseRange(30, 30, 1)
	  ->Unit( ::benchmark::kSecond );

}  // namespace hypro::benchmark
