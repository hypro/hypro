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
			//RepresentationCombinations<
			//	  CarlPolytopeT, CarlPolytopeSetting>,
			RepresentationCombinations<
				  HPolytopeT, HPolytopeSetting, HPolytopeOptimizerCaching>,
			RepresentationCombinations<
				  SupportFunctionT, SupportFunctionSetting, NoBoxReduction, NoBoxDetection, NoTrafoReduction, NoReduction, PolytopeSupportFunctionSetting>,
			RepresentationCombinations<
				  SupportFunctionNewT, SupportFunctionNewDefault, SupportFunctionNewMorePrecision, SupportFunctionNewNoReduction, SupportFunctionNewLeGuernic>,
			RepresentationCombinations<
				  TemplatePolyhedronT, TemplatePolyhedronDefault>
			>;

template <class Number, class Converter>
using DefaultDispatcher = Dispatcher<Number, Converter, DefaultRepresentations>;

}  // namespace hypro