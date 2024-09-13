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
#include <cstdio>
#include <cstdlib>
#include <iostream>

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
        plotter.rSettings().dimensions.push_back(plottingDimensions.front());
        plotter.rSettings().dimensions.push_back(plottingDimensions.back());
        plotter.rSettings().cummulative = false;


        std::cout << "Plotting." << std::endl;
        bool useBadStates = false;
        if(useBadStates) {

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
        }
        unsigned cnt = 0;
        // segments plotting
        for (const auto &flowpipe: flowpipes) {
            for (const auto &segment: flowpipe) {
                if(segment.empty()) {
                    continue;
                }
                plotter.addObject(segment.projectOn(plottingDimensions).vertices(), hypro::plotting::colors[cnt % 10]);
                //plotter.addObject(segment.projectOut({2, 3}).vertices(), hypro::plotting::colors[cnt % 10]);
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

static void writeRuntime(const std::vector<timeunit> &runtimes, const std::string &filename, const std::string &titel, bool newFile) {
    if (newFile) {
        std::remove(filename.c_str());
    }
    std::ofstream file(filename, std::ios::app);
    file << titel << std::endl;
    for (auto runtime : runtimes) {
        file << runtime.count()/1000.0 << ","; 
    }
    file << std::endl;
    file.close();
    std::cout << "Write runtime to file: " << filename << std::endl;
}

std::string extractFilenameWithoutExtension(const std::string& filepath) {
    // Find the position of the last directory separator
    size_t lastSlashPos = filepath.find_last_of("/\\");
    std::string filename = filepath.substr(lastSlashPos + 1);

    // Find the position of the last dot in the filename
    size_t lastDotPos = filename.find_last_of(".");
    if (lastDotPos != std::string::npos) {
        filename = filename.substr(0, lastDotPos);
    }

    return filename;
}

template<typename Number, typename Representation>
static void run_comparison_function(const std::string &filename,
                                   const hypro::representation_name &type, int number_iterations) {
    using Automaton = hypro::HybridAutomaton<Number>;
    using clock = std::chrono::high_resolution_clock;

    // do the reachability analysis for runtime measurement
    std::vector<timeunit> runtimes;
    auto outputFilename = "runtime_" + extractFilenameWithoutExtension(filename) + ".txt";
    bool run_setMinus2 = true; 
    if (run_setMinus2) {
        // calculate runtimes
        for(int iteration = 0; iteration < number_iterations; iteration++) {
            auto [automaton_cur, parsedSettings_cur] = hypro::parseFlowstarFile<Number>(filename);

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

        bool plotsetMinus2 = false;
        if(plotsetMinus2){
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
        }
        
    }
    writeRuntime(runtimes, outputFilename, "setMinus2", true);

    // exit to test only the setMinus2 function
    //exit(0);

    runtimes.clear();

    bool run_setMinusCrossing = true;
    if (run_setMinusCrossing) {
        for(int iteration = 0; iteration < number_iterations; iteration++) {
            auto [automaton_cur, parsedSettings_cur] = hypro::parseFlowstarFile<Number>(filename);
            hypro::Settings settings_cur = hypro::convert(parsedSettings_cur);
            hypro::AnalysisParameters analysisParams_cur = settings_cur.strategy().front();
            analysisParams_cur.setMinusAlgoUsed = 1;
            auto roots_cur = hypro::makeRoots<Representation, Automaton>(automaton_cur);
            hypro::reachability::ReachUrgency<Representation, Automaton> reacher_cur(automaton_cur, settings_cur.fixedParameters(),analysisParams_cur, roots_cur); 

            clock::time_point start = clock::now();
            auto result_cur = reacher_cur.computeForwardReachability();
            runtimes.push_back(std::chrono::duration_cast<timeunit>(clock::now() - start));
        }
        std::cout << "Statistic: setMinusCrossing" << std::endl;
        displayRuntime(runtimes);

        bool plotsetMinusCrossing = false;
        if(plotsetMinusCrossing){
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
            plotResult<Number, Representation>("setMinusCrossing", automaton, flowpipes, settings);
        }
    }
    writeRuntime(runtimes, outputFilename, "setMinusCrossing", false);
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
    // using Number = mpq_class; // it oly works with double
    using Number = double;
#endif

    switch (rep) {
        case 2: {// V representation doesn't work
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
