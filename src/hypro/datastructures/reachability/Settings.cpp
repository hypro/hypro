/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created by Stefan Schupp <stefan.schupp@tuwien.ac.at> on 02.08.21.
 */

#include "include/hypro/datastructures/reachability/Settings.h"

namespace hypro {

    Settings convert(const ReachabilitySettings &r_settings) {
        // general settings
        hypro::FixedAnalysisParameters fixedParameters{};
        fixedParameters.jumpDepth = static_cast<size_t>( r_settings.jumpDepth );
        fixedParameters.localTimeHorizon = r_settings.timeBound;

        // plotting
        hypro::PlottingSettings plotting{};
        plotting.plotDimensions = r_settings.plotDimensions;
        plotting.plotFileNames = std::vector<std::string>(plotting.plotDimensions.size(), r_settings.fileName);
        plotting.plottingFileType = hypro::PLOTTYPE::nset;

        // analysis parameters
        hypro::AnalysisParameters parameters{};
        parameters.timeStep = r_settings.timeStep;
        parameters.aggregation = hypro::AGG_SETTING::MODEL;
        parameters.clustering = r_settings.clustering;
        parameters.uniformBloating = r_settings.uniformBloating;
        // parameters.representation_type = cliOptions["representation"].as<hypro::representation_name>();
        // parameters.representation_setting = hypro::stringToSetting( cliOptions["setting"].as<std::string>() );

        return hypro::Settings{plotting, fixedParameters, {parameters}};
    }

}  // namespace hypro
