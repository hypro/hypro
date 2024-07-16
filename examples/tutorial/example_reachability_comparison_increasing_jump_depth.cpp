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
#include <filesystem>

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
        // clear the plotter, i.e., remove all stored objects to create a fresh canvas
        plotter.clear();
        std::string extendedFilename = plotFileName;
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

                auto vertices = segment.projectOn(plottingDimensions).vertices();
                for (auto &vertex : vertices) {
                    if(vertex.dimension() != 2) {
                        using Converter = hypro::Converter<Number>;
                        std::cout<< "Vertex size: " << vertex.dimension() << std::endl;
                        std::cout << "vertices" << std::endl << vertices << std::endl;
                        std::cout << "projected segment" << std::endl << segment.projectOn(plottingDimensions) << std::endl;
                        std::cout << "Segment" << std::endl << segment << std::endl;
                        std::cout << "v-segment" << std::endl << Converter::toVPolytope(segment) << std::endl;
                    }
                }
                plotter.addObject(segment.projectOn(plottingDimensions).vertices(), hypro::plotting::colors[cnt % 8]);
                //plotter.addObject(segment.projectOut({2, 3}).vertices(), hypro::plotting::colors[cnt % 10]);
            }
            ++cnt;
        }

        PRINT_STATS()
        plotter.plot2d(hypro::PLOTTYPE::pdf, true);

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

    namespace fs = std::filesystem;

    // do the reachability analysis for runtime measurement

    fs::remove_all("./JumpDepths");
    fs::create_directories("./JumpDepths");

    auto outputFilename = "runtime_jumpdepth_" + extractFilenameWithoutExtension(filename) + ".txt";
    writeRuntime(std::vector<timeunit>(), outputFilename, "", true);

    bool use_model_settings = false;

    const int max_jump_depth = 10;
    const int time_horizon = 20;
    for(int current_jump_depth = 0; current_jump_depth <= max_jump_depth; current_jump_depth++) {
        std::cout << "Running jump depth: " << current_jump_depth << std::endl;
        fs::create_directories("./JumpDepths/Depth" + std::to_string(current_jump_depth));
        std::vector<timeunit> runtimes;
        bool run_setMinus2 = true; 
        if (run_setMinus2) {
            std::cout << "Running setMinus2" << std::endl;
            for(int iteration = 0; iteration < number_iterations; iteration++) {
                auto [automaton_cur, parsedSettings_cur] = hypro::parseFlowstarFile<Number>(filename);
                hypro::Settings settings_cur = hypro::convert(parsedSettings_cur);

                hypro::FixedAnalysisParameters fixedParameters_cur;
                hypro::AnalysisParameters analysisParams_cur;

                if(use_model_settings){
                    analysisParams_cur = settings_cur.strategy().front();
                    analysisParams_cur.setMinusAlgoUsed = 0;
                    
                    fixedParameters_cur = settings_cur.fixedParameters();
                    fixedParameters_cur.jumpDepth = current_jump_depth;
                    fixedParameters_cur.localTimeHorizon = time_horizon;
                }else{
                    fixedParameters_cur.jumpDepth = current_jump_depth;
                    fixedParameters_cur.localTimeHorizon = time_horizon;
                    fixedParameters_cur.fixedTimeStep = Number(1) / Number(3);

                    analysisParams_cur.setMinusAlgoUsed = 0;
                    analysisParams_cur.timeStep = Number(1) / Number(3);
                    analysisParams_cur.aggregation = hypro::AGG_SETTING::NO_AGG;
                    analysisParams_cur.representation_type = hypro::representation_name::polytope_h;
                }

                auto roots_cur = hypro::makeRoots<Representation, Automaton>(automaton_cur);
                hypro::reachability::ReachUrgency<Representation, Automaton> reacher_cur(automaton_cur, fixedParameters_cur, analysisParams_cur, roots_cur); 

                clock::time_point start = clock::now();
                auto result_cur = reacher_cur.computeForwardReachability();

                
                runtimes.push_back(std::chrono::duration_cast<timeunit>(clock::now() - start));

                if(iteration == 0){
                    std::string plotname = "./JumpDepths/Depth" + std::to_string(current_jump_depth) + "/" + "SetMinus2";
                    plotResult(plotname, automaton_cur, hypro::getFlowpipes(roots_cur), settings_cur);
                }
            }
            std::cout << "setMinus2 finished" << std::endl;
        }
        writeRuntime(runtimes, outputFilename, "setMinus2", false);

        //std::cin.get();

        runtimes.clear();
        bool run_setMinusCrossing = true; 

        if (run_setMinusCrossing) {
        std::cout << "Running setMinusCrossing" << std::endl;
        for(int iteration = 0; iteration < number_iterations; iteration++) {
            auto [automaton_cur, parsedSettings_cur] = hypro::parseFlowstarFile<Number>(filename);
                hypro::Settings settings_cur = hypro::convert(parsedSettings_cur);
                hypro::FixedAnalysisParameters fixedParameters_cur;
                hypro::AnalysisParameters analysisParams_cur;

                if(use_model_settings){
                    analysisParams_cur = settings_cur.strategy().front();
                    analysisParams_cur.setMinusAlgoUsed = 1;
                    
                    fixedParameters_cur = settings_cur.fixedParameters();
                    fixedParameters_cur.jumpDepth = current_jump_depth;
                    fixedParameters_cur.localTimeHorizon = time_horizon;
                }else{
                    fixedParameters_cur.jumpDepth = current_jump_depth;
                    fixedParameters_cur.localTimeHorizon = time_horizon;
                    fixedParameters_cur.fixedTimeStep = Number(1) / Number(3);

                    analysisParams_cur.setMinusAlgoUsed = 1;
                    analysisParams_cur.timeStep = Number(1) / Number(3);
                    analysisParams_cur.aggregation = hypro::AGG_SETTING::NO_AGG;
                    analysisParams_cur.representation_type = hypro::representation_name::polytope_h;
                }

            auto roots_cur = hypro::makeRoots<Representation, Automaton>(automaton_cur);
            hypro::reachability::ReachUrgency<Representation, Automaton> reacher_cur(automaton_cur, fixedParameters_cur, analysisParams_cur, roots_cur); 

            clock::time_point start = clock::now();
            auto result_cur = reacher_cur.computeForwardReachability();

            runtimes.push_back(std::chrono::duration_cast<timeunit>(clock::now() - start));

            if(iteration == 0){
                std::string plotname = "./JumpDepths/Depth" + std::to_string(current_jump_depth) + "/" + "SetMinusCrossing";
                plotResult(plotname, automaton_cur, hypro::getFlowpipes(roots_cur), settings_cur);
            }

        }
        std::cout << "setMinusCrossing finished" << std::endl;

        }
        writeRuntime(runtimes, outputFilename, "setMinusCrossing", false);
        //std::cin.get();
    }
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
    using Number = mpq_class;
    // using Number = double;
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
