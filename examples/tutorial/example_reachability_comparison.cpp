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

using timeunit = std::chrono::microseconds;

template<typename Number, typename Representation>
static void plotResult(std::string plotFileName, const hypro::HybridAutomaton<Number> &automaton,
                       const std::vector<std::vector<Representation>> &flowpipes,
                       const hypro::Settings &settings) {

    using Automaton = hypro::HybridAutomaton<Number>;
    using clock = std::chrono::high_resolution_clock;

    if (settings.plotting().plotDimensions.size() > 0) {
        clock::time_point startPlotting = clock::now();

        auto &plotter = hypro::Plotter<Number>::getInstance();
        std::string extendedFilename = settings.plotting().plotFileNames.front();
        extendedFilename += "_" + plotFileName;
        switch (Representation::type()) {
            case hypro::representation_name::polytope_t: {
                extendedFilename += "_tpoly";
                break;
            }
            case hypro::representation_name::ppl_polytope: {
                extendedFilename += "_pplpoly";
                break;
            }
            case hypro::representation_name::difference_bounds: {
                extendedFilename += "_differenceBounds";
                break;
            }
            case hypro::representation_name::zonotope: {
                extendedFilename += "_zonotope";
                break;
            }
            case hypro::representation_name::support_function: {
                extendedFilename += "_supportFunction";
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
            case hypro::representation_name::box: {
                extendedFilename += "_box";
                break;
            }
            case hypro::representation_name::SFN: {
                extendedFilename += "_sfn";
                break;
            }
            default:
                extendedFilename += "_unknownRep";
        }
        std::cout << "filename is " << extendedFilename << std::endl;
        plotter.setFilename(extendedFilename);
        std::vector<std::size_t> plottingDimensions = settings.plotting().plotDimensions.at(0);
        std::cout << "plotting dimensions: " <<  std::endl;
        for(auto dim : plottingDimensions) {
            std::cout << dim << " ";
        }
        plotter.rSettings().dimensions.push_back(plottingDimensions.front());
        plotter.rSettings().dimensions.push_back(plottingDimensions.back());
        plotter.rSettings().cummulative = false;

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
            for (const auto &segment: flowpipe) {
                /**if(segment.empty()) {
                    continue;
                }**/
                plotter.addObject(segment.projectOn(plottingDimensions).vertices(), hypro::plotting::colors[cnt % 10]);
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

static void displayRuntime(const std::vector<timeunit> &runtimes) {
    double sum = 0;
    for (auto runtime : runtimes) {
        sum += runtime.count();
    }
    double average = sum / runtimes.size();
    std::cout << "Average runtime: " << average / 1000.0 << " ms" << std::endl;

    // print standard deviation
    double variance = 0;
    for (auto runtime : runtimes) {
        variance += pow(runtime.count() - average, 2);
    }
    variance /= runtimes.size();
    double standardDeviation = sqrt(variance);
    std::cout << "Standard deviation: " << standardDeviation / 1000.0 << " ms" << std::endl;
}

template<typename Number, typename Representation>
static void run_comparison_function(const std::string &filename,
                                   const hypro::representation_name &type, int number_iterations) {
    using Automaton = hypro::HybridAutomaton<Number>;
    using clock = std::chrono::high_resolution_clock;

    // do the reachability analysis for runtime measurement
    std::vector<timeunit> runtimes;
    for(int iteration = 0; iteration < number_iterations; iteration++) {
        auto [automaton_cur, parsedSettings_cur] = hypro::parseFlowstarFile<Number>(filename);
        std::cout << parsedSettings_cur << std::endl;

        hypro::Settings settings_cur = hypro::convert(parsedSettings_cur);
        hypro::AnalysisParameters analysisParams_cur = settings_cur.strategy().front();
        analysisParams_cur.setMinusAlgoUsed = 0;
        auto roots_cur = hypro::makeRoots<Representation, Automaton>(automaton_cur);
        hypro::reachability::ReachUrgency<Representation, Automaton> reacher_cur(automaton_cur, settings_cur.fixedParameters(),analysisParams_cur, roots_cur); 

        clock::time_point start = clock::now();
        auto result_cur = reacher_cur.computeForwardReachability();
        runtimes.push_back(std::chrono::duration_cast<timeunit>(clock::now() - start));
    }

    std::cout << "Statistic: setMinus2" << std::endl;
    displayRuntime(runtimes);

    // do the reachability analysis again for plotting
    auto [automaton, parsedSettings] = hypro::parseFlowstarFile<Number>(filename);
    std::cout << parsedSettings << std::endl;

    hypro::Settings settings = hypro::convert(parsedSettings);
    hypro::AnalysisParameters analysisParams = settings.strategy().front();
    analysisParams.setMinusAlgoUsed = 0;

    auto roots = hypro::makeRoots<Representation, Automaton>(automaton);
    hypro::reachability::ReachUrgency<Representation, Automaton> reacher(automaton, settings.fixedParameters(),analysisParams, roots); 
    auto result = reacher.computeForwardReachability();
    auto flowpipes = getFlowpipes(roots);

    // plotting
    plotResult<Number, Representation>("setMinus2", automaton, flowpipes, settings);

    // exit to test only the setMinus2 function
    exit(0);

    runtimes.clear();
    for(int iteration = 0; iteration < number_iterations; iteration++) {
        auto roots2_cur = hypro::makeRoots<Representation, Automaton>(automaton);
        hypro::AnalysisParameters analysisParams2 = settings.strategy().front();
        analysisParams2.setMinusAlgoUsed = 1;

        hypro::reachability::ReachUrgency<Representation, Automaton> reacher2_cur(automaton, settings.fixedParameters(),analysisParams2, roots2_cur); 

        clock::time_point start2 = clock::now();
        auto result2_cur = reacher2_cur.computeForwardReachability();

        runtimes.push_back(std::chrono::duration_cast<timeunit>(clock::now() - start2));
    }

    std::cout << "Statistic: setMinusCrossing" << std::endl;
    displayRuntime(runtimes);


    auto roots2 = hypro::makeRoots<Representation, Automaton>(automaton);
    hypro::AnalysisParameters analysisParams2 = settings.strategy().front();
    analysisParams2.setMinusAlgoUsed = 1;
    hypro::reachability::ReachUrgency<Representation, Automaton> reacher2(automaton, settings.fixedParameters(),analysisParams2, roots2); 
    auto result2 = reacher2.computeForwardReachability();
    auto flowpipes2 = getFlowpipes(roots2);
    plotResult<Number, Representation>("setMinusCrossing", automaton, flowpipes2, settings);
}

int main(int argc, char **argv) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <filename> <representation> <number_iteration>"  << std::endl;
        exit(1);
    }

    std::string filename = argv[1];

    char *p;
    int rep = strtol(argv[2], &p, 10);

    char *p1;
    int number_iterations = strtol(argv[3], &p1, 10);


    


#ifdef USE_CLN_NUMBERS
    using Number = cln::cl_RA;
#else
    // using Number = mpq_class;
    using Number = double;
#endif

    switch (rep) {
        case 2: {
            using Representation = hypro::VPolytope<Number>;
            std::cout << "Using a v-polytope representation." << std::endl;
            run_comparison_function<Number, Representation>(
                    filename, hypro::representation_name::polytope_v, number_iterations);
            break;
        }
        case 1: {
            using Representation = hypro::HPolytope<Number>;
            std::cout << "Using a h-polytope representation." << std::endl;
            run_comparison_function<Number, Representation>(
                    filename, hypro::representation_name::polytope_h, number_iterations);
            break;
        }
    }

    exit(0);
}
