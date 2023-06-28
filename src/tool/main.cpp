/*
 * Copyright (c) 2021-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "cli/cli.h"
#include "cli/settingsProcessing.h"
#include "preprocessing/preprocessing.h"
#include "reachability/analysis.h"

#include <hypro/datastructures/HybridAutomaton/StateUtil.h>
#include <hypro/parser/antlr4-flowstar/ParserWrapper.h>
#include <hypro/util/logging/Logger.h>
#include <hypro/util/plotting/Plotter.h>

using namespace hydra;
using namespace hypro;

int main(int argc, char const *argv[]) {
    // parse command line arguments
    START_BENCHMARK_OPERATION("Parsing");
    auto options = hydra::handleCMDArguments(argc, argv);

    // parse model file
    if (!options.count("silent") or !options["silent"].as<bool>()) {
        COUT("Passed model file: " << options["model"].as<std::string>() << std::endl);
    }

    auto [automaton, reachSettings] = hypro::parseFlowstarFile<hydra::Number>(
            options["model"].as<std::string>());

    // combine parsed settings and cli flags
    auto settings = hydra::processSettings(reachSettings, options);

    settings.rStrategy().front().detectContinuousFixedPointsLocally = false;
    settings.rStrategy().front().detectFixedPointsByCoverage = false;
    settings.rStrategy().front().detectJumpFixedPoints = false;

    EVALUATE_BENCHMARK_RESULT("Parsing");

    // perform preprocessing
    START_BENCHMARK_OPERATION("Preprocess");
    auto preprocessingInformation = hydra::preprocessing::preprocess(automaton,
                                                                     options["decompose"].as<bool>(),
                                                                     options["singularSubspaceSize"].as<std::size_t>(),
                                                                     options["clockCount"].as<std::size_t>());
    STOP_BENCHMARK_OPERATION("Preprocess");

    // run reachability analysis
    auto result = hydra::reachability::analyze(automaton, settings, preprocessingInformation,
                                               options["urgency_cegar"].as<bool>());

    // call to plotting.
    START_BENCHMARK_OPERATION("Plotting");

    auto const &plotSettings = settings.plotting();
    auto &plt = Plotter<Number>::getInstance();
    for (std::size_t pic = 0; pic < plotSettings.plotDimensions.size(); ++pic) {
        assert(plotSettings.plotDimensions[pic].size() == 2);
        std::cout << "Prepare plot "
                  << "(" << pic + 1 << "/" << plotSettings.plotDimensions.size() << ") for dimensions "
                  << plotSettings.plotDimensions[pic].front() << ", " << plotSettings.plotDimensions[pic].back() << "."
                  << std::endl;
        plt.setFilename(plotSettings.plotFileNames[pic]);
        std::size_t segmentCount = 0;

        for (auto &segment: result.plotData) {
            if (true || segmentCount % 100 == 0)
                std::cout << "\r" << segmentCount << "/" << result.plotData.size() << "..." << std::flush;
            segmentCount += 1;
            auto vertices = segment.sets.projectOn(plotSettings.plotDimensions[pic]).vertices();
            if (vertices.front().dimension() != 2) {
                INFO("hypro.plotter", "broken vertices:\n"
                        << vertices)
                INFO("hypro.plotter", "from:\n"
                        << printSet(segment.sets));
                continue;
            }
            plt.addObject(vertices);
        }
        std::cout << "\r" << segmentCount << "/" << result.plotData.size() << "..."
                  << "\n";

        plt.plot2d(plotSettings.plottingFileType, true);    // writes to .plt file for pdf creation
    }
    EVALUATE_BENCHMARK_RESULT("Plotting");

    PRINT_STATS();

    return 0;
}
