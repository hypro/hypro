/*
 * Copyright (c) 2023-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * This is an example on how to set up a rudimentary reachability analysis method.
 */

#include "hypro/algorithms/reachability/Reach.h"
#include "hypro/datastructures/HybridAutomaton/HybridAutomaton.h"
#include "hypro/datastructures/reachability/ReachTreev2Util.h"
#include "hypro/parser/antlr4-flowstar/ParserWrapper.h"
#include "hypro/representations/GeometricObjectBase.h"
#include "hypro/util/plotting/Plotter.h"
#include "hypro/util/statistics/statistics.h"

template<typename Number, typename Representation>
static void computeReachableStates(const std::string &filename) {
    using Automaton = hypro::HybridAutomaton<Number>;
    using clock = std::chrono::high_resolution_clock;
    using timeunit = std::chrono::microseconds;
    clock::time_point start = clock::now();

    auto [automaton, parsedSettings] = hypro::parseFlowstarFile<Number>(filename);

    std::cout << parsedSettings << std::endl;

    hypro::Settings settings = hypro::convert(parsedSettings);
    auto roots = hypro::makeRoots<Representation, Automaton>(automaton);

    hypro::AnalysisParameters analysisParams = settings.strategy().front();
    analysisParams.underapproxReach = true;

    hypro::reachability::Reach<Representation, Automaton> reacher(automaton, settings.fixedParameters(), analysisParams,
                                                                  roots);

    auto result = reacher.computeForwardReachability();
    auto flowpipes = getFlowpipes(roots);
    auto flowpipesUnderApprox = getFlowpipesUnderApprox(roots);


    std::cout
            << "Finished computation of reachable states: "
            << std::chrono::duration_cast<timeunit>(clock::now() - start).count() /
               1000.0
            << " ms" << std::endl;

    if (settings.plotting().plotDimensions.size() > 0) {
        clock::time_point startPlotting = clock::now();

        auto &plotter = hypro::Plotter<Number>::getInstance();
        std::string extendedFilename = settings.plotting().plotFileNames.front() + "_hpoly" ;


         
        std::cout << "filename is " << extendedFilename << std::endl;
        plotter.setFilename(extendedFilename);
        std::vector<std::size_t> plottingDimensions =
                settings.plotting().plotDimensions.at(0);
        plotter.rSettings().dimensions.push_back(plottingDimensions.front());
        plotter.rSettings().dimensions.push_back(plottingDimensions.back());
        plotter.rSettings().cummulative = false;
        plotter.rSettings().overwriteFiles = true;

        // bad states plotting
        typename hypro::HybridAutomaton<Number>::locationConditionMap
                badStateMapping = automaton.getLocalBadStates();
        for (const auto &state: badStateMapping) {
            auto matrix = state.second.getMatrix(0);
            auto vector = state.second.getVector(0);
            unsigned bs = plotter.addObject(
                    Representation(matrix, vector).projectOn(plottingDimensions).vertices(),
                    hypro::plotting::colors[hypro::plotting::red]);
        }

        unsigned cnt = 0;
        // segments plotting
        for (const auto &flowpipe: flowpipes) {
            std::cout << "Flowpipe size " << flowpipe.size() << std::endl;
            for (const auto &segment: flowpipe) {
                plotter.addObject(segment.projectOn(plottingDimensions).vertices(), hypro::plotting::colors[cnt % 10]);
            }
            ++cnt;
        }

        PRINT_STATS()

        std::cout << "Write to file." << std::endl;

        plotter.plot2d(hypro::PLOTTYPE::pdf);

        std::cout << "Finished plotting: "
                  << std::chrono::duration_cast<timeunit>(clock::now() -
                                                          startPlotting)
                             .count() /
                     1000.0
                  << " ms" << std::endl;
    
    
        ///////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////

        // plot under-approximative segments
        plotter.clear();
        extendedFilename += "_under_approx";
        plotter.setFilename(extendedFilename);

        for (const auto &state: badStateMapping) {
            auto matrix = state.second.getMatrix(0);
            auto vector = state.second.getVector(0);
            unsigned bs = plotter.addObject(
                    Representation(matrix, vector).projectOn(plottingDimensions).vertices(),
                    hypro::plotting::colors[hypro::plotting::red]);
        }

        cnt = 0;
        // segments plotting
        for (const auto &flowpipe: flowpipesUnderApprox) {
            std::cout << "Under-approx Flowpipe size " << flowpipe.size() << std::endl;
            for (const auto &segment: flowpipe) {
                plotter.addObject(segment.projectOn(plottingDimensions).vertices(), hypro::plotting::colors[cnt % 10]);
            }
            ++cnt;
        }
        plotter.plot2d(hypro::PLOTTYPE::pdf);
    
    }
}

int main(int argc, char **argv) {
    std::string filename = argv[1];
    
    // using Number = mpq_class;
    using Number = double;

    using Representation = hypro::HPolytope<Number>;
    computeReachableStates<Number, Representation>(filename);
     

    exit(0);
}
