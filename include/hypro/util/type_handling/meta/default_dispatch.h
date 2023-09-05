/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../../representations/GeometricObjectBase.h"
#include "../representation_enums.h"
#include "../settings_enums.h"
#include "RepresentationCombinations.h"
#include "TypeList.h"
#include "dispatch_meta.h"

namespace hypro {

    using DefaultRepresentations =
            TypeList<
                    RepresentationCombinations<
                            BoxT, BoxLinearOptimizationOn, BoxLinearOptimizationOff, BoxIntervalArithmeticOff, BoxAllOff>,
                    // RepresentationCombinations<
                    //	  CarlPolytopeT, CarlPolytopeSetting>,
                    RepresentationCombinations<
                            HPolytopeT, HPolytopeSetting, HPolytopeOptimizerCaching>,
                    RepresentationCombinations<
                            VPolytopeT, VPolytopeSetting>,
                    RepresentationCombinations<
                            StarsetT, StarsetDefault>,
                    RepresentationCombinations<
                            SupportFunctionT, SupportFunctionSetting, NoBoxReduction, NoBoxDetection, NoTrafoReduction, NoReduction, PolytopeSupportFunctionSetting>,
                    RepresentationCombinations<
                            SupportFunctionNewT, SupportFunctionNewDefault, SupportFunctionNewMorePrecision, SupportFunctionNewNoReduction, SupportFunctionNewLeGuernic> /*,
			 RepresentationCombinations<
				   TemplatePolyhedronT, TemplatePolyhedronDefault, OctagonShape>*/
            >;

    using PolytopalRepresentations =
            TypeList<
                    // RepresentationCombinations<
                    //	  CarlPolytopeT, CarlPolytopeSetting>,
                    RepresentationCombinations<
                            HPolytopeT, HPolytopeSetting, HPolytopeOptimizerCaching>,
                    RepresentationCombinations<
                            VPolytopeT, VPolytopeSetting>
                    // RepresentationCombinations<
                    //	  TemplatePolyhedronT, TemplatePolyhedronDefault>
            >;

    using SetMinusRepresentations =
            TypeList<
                    RepresentationCombinations<
                            BoxT, BoxLinearOptimizationOn, BoxLinearOptimizationOff, BoxIntervalArithmeticOff, BoxAllOff>,
                    RepresentationCombinations<
                            HPolytopeT, HPolytopeSetting>>;

    template<class Number, class Converter>
    using RepresentationsList = flattenRepresentations<Number, Converter, DefaultRepresentations>;

    template<class Number, class Converter>
    using PolytopeTypesList = flattenRepresentations<Number, Converter, PolytopalRepresentations>;

    template<class Number, class Converter>
    using SetMinusTypesList = flattenRepresentations<Number, Converter, SetMinusRepresentations>;

    template<class Number, class Converter>
    using SetMinusDispatcher = Dispatcher<SetMinusTypesList<Number, Converter>>;

    template<class Number, class Converter>
    using DefaultDispatcher = Dispatcher<RepresentationsList<Number, Converter>>;

}  // namespace hypro
