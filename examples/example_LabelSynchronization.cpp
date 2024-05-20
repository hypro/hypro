/*
 * Copyright (c) 2023-2024.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * This is an example on how to perform reachaboility analysis with label synchronization on multiple rectangular automata.
 * 
 */

#include "hypro/datastructures/reachability/ReachTreev2Util.h"
#include "hypro/datastructures/HybridAutomaton/HybridAutomaton.h"
#include "hypro/util/plotting/Plotter.h"
#include "hypro/util/statistics/statistics.h"
#include <hypro/util/VariablePool.h>
#include <hypro/algorithms/reachability/analyzer/LabelSynchronization/RectangularSyncAnalyzer.h>
#include "hypro/algorithms/reachability/Reach.h"
#include "hypro/parser/antlr4-flowstar/ParserWrapper.h"
#include "hypro/representations/GeometricObjectBase.h"
#include <iostream>


template<typename Number, typename Representation>
static void computeReachableStates(const std::vector<std::string> filename,
                                   const hypro::representation_name &type) {
    using Automaton = hypro::HybridAutomaton<Number>;
    using clock = std::chrono::high_resolution_clock;
    using timeunit = std::chrono::microseconds;
    clock::time_point start = clock::now();

    // parse the input files and save them in a vector of automata
    std::vector<Automaton> automata;
    std::vector<hypro::Settings> settings;
    for (int i=0; i<filename.size(); i++) {
        auto [automaton, fileSettings] = hypro::parseFlowstarFile<Number>(filename[i]);
        settings.push_back( hypro::convert(fileSettings) );
        automaton.addTimeVariable();
        automata.push_back(automaton);

        hypro::VariablePool::getInstance().changeToPool(i+1);
    }

    hypro::VariablePool::getInstance().changeToPool(0);

    // we use the analysis settings from the first file only
    hypro::RectangularSyncAnalyzer<Representation, Automaton> analyzer{automata, settings[0] };

    auto result = analyzer.run();

    std::cout
            << std::endl
            << "Finished computation of reachable states: "
            << std::chrono::duration_cast<timeunit>(clock::now() - start).count() /
               1000.0
            << " ms" << std::endl;
    
    if (result == hypro::REACHABILITY_RESULT::UNKNOWN) {
        std::cout << "Could not verify safety." << std::endl;
    } else {
        std::cout << "The model is safe." << std::endl;
    }
    std::cout << std::endl;

    if (settings[0].plotting().plotDimensions.size() > 0) {
        clock::time_point startPlotting = clock::now();

        for (size_t i = 0; i < automata.size(); ++i) {
            auto &plotter = hypro::Plotter<Number>::getInstance();
            std::string extendedFilename = settings[i].plotting().plotFileNames.front();
            switch (Representation::type()) {
                case hypro::representation_name::polytope_t: {
                    extendedFilename += "_tpoly";
                    break;
                }
                case hypro::representation_name::polytope_v: {
                    extendedFilename += "_vpoly";
                    break;
                }
                case hypro::representation_name::polytope_h: {
                    extendedFilename += "_hpoly";
                    break;
                }
                default:
                    extendedFilename += "_unknownRep";
            }
            std::cout << "filename is " << extendedFilename << std::endl;
            plotter.setFilename(extendedFilename);
            // std::vector<std::size_t> plottingDimensions =
            //         settings[i].plotting().plotDimensions.at(0);
            // plotter.rSettings().dimensions.push_back(plottingDimensions.front());
            // plotter.rSettings().dimensions.push_back(plottingDimensions.back());
            plotter.rSettings().cummulative = false;
            
            // bad states plotting
            typename hypro::HybridAutomaton<Number>::locationConditionMap
                    badStateMapping = automata[i].getLocalBadStates();
            for (const auto &state: badStateMapping) {
                auto matrix = state.second.getMatrix(0);
                auto vector = state.second.getVector(0);
                unsigned bs = plotter.addObject(
                        Representation(matrix, vector).vertices(),
                        hypro::plotting::colors[hypro::plotting::red]);
            }

            unsigned cnt = 0;
            // segments plotting
            // auto flowpipes = getFlowpipes(roots);
            auto flowpipes = getFlowpipes( analyzer.getReachTreeForAutomaton(automata[i]).front() );
            for (const auto &flowpipe: flowpipes) {
                std::cout << "Flowpipe size " << flowpipe.size() << std::endl;
                for (const auto &segment: flowpipe) {
                    plotter.addObject(segment.vertices(), hypro::plotting::colors[cnt % 10]);
                }
                ++cnt;
            }
        
            PRINT_STATS()

            std::cout << "Write to file." << std::endl;

            plotter.plot2d(hypro::PLOTTYPE::pdf, true);

            std::cout << "Finished plotting: "
                    << std::chrono::duration_cast<timeunit>(clock::now() -
                                                            startPlotting)
                                .count() /
                        1000.0
                    << " ms" << std::endl;
        }

    }
}


int main(int argc, char **argv) {
    int rep = 0;
    std::vector<std::string> filename;
    for (int i = 1; i < argc-1; i++) {
        filename.push_back(argv[i]);
    }
    if (argc > 1) {
        char *p;
        rep = strtol(argv[argc-1], &p, 10);
    } else {
        std::cout << "Usage: " << argv[0] << " <filename1> (<filename2>)* <representation>" << std::endl;
        std::cout << "Representation: 2 for HPolytope or 3 for VPolytope" << std::endl;
        exit(1);
    }
    
    using Number = mpq_class;
    // using Number = double;

    switch (rep) {
        case 3: {
            using Representation = hypro::VPolytope<Number>;
            std::cout << "Using a v-polytope representation." << std::endl;
            computeReachableStates<Number, Representation>(
                    filename, hypro::representation_name::polytope_v);
            break;
        }
        case 2: {
            using Representation = hypro::HPolytope<Number>;
            std::cout << "Using a h-polytope representation." << std::endl;
            computeReachableStates<Number, Representation>(
                    filename, hypro::representation_name::polytope_h);
            break;
        }

        default: {
            using Representation = hypro::VPolytope<Number>;
            std::cout << "Using a v-polytope representation." << std::endl;
            computeReachableStates<Number, Representation>(
                    filename, hypro::representation_name::polytope_h);
        }
    }

    exit(0);
}