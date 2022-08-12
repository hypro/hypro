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

template <class Number, class Converter>
using RepresentationsList = flattenRepresentations<Number, Converter, DefaultRepresentations>;

template <class Number, class Converter>
using PolytopeTypesList = flattenRepresentations<Number, Converter, PolytopalRepresentations>;

template <class Number, class Converter>
using SetMinusTypesList = flattenRepresentations<Number, Converter, SetMinusRepresentations>;

template <class Number, class Converter>
using SetMinusDispatcher = Dispatcher<SetMinusTypesList<Number, Converter>>;

template <class Number, class Converter>
using DefaultDispatcher = Dispatcher<RepresentationsList<Number, Converter>>;

}  // namespace hypro