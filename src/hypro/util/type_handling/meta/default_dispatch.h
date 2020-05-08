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
			RepresentationCombinations<
				  SupportFunctionT, SupportFunctionSetting, NoBoxReduction, NoBoxDetection, NoTrafoReduction, NoReduction, PolytopeSupportFunctionSetting>>;

//Mapping of types to enum values. May also be done in the classes themselves.
template <class... T>
constexpr auto TypeEnum<BoxT<T...>> = representation_name::box;
template <class... T>
constexpr auto TypeEnum<SupportFunctionT<T...>> = representation_name::support_function;

template <>
constexpr int TypeEnum<BoxLinearOptimizationOn> = boxSetting_name::BoxLinearOptimizationOn;
template <>
constexpr int TypeEnum<BoxLinearOptimizationOff> = boxSetting_name::BoxLinearOptimizationOff;
template <>
constexpr int TypeEnum<BoxIntervalArithmeticOff> = boxSetting_name::BoxIntervalArithmeticOff;
template <>
constexpr int TypeEnum<BoxAllOff> = boxSetting_name::BoxAllOff;

template <>
constexpr int TypeEnum<SupportFunctionSetting> = supportFunctionSetting_name::SupportFunctionSetting;

template <class Number, class Converter>
using DefaultDispatcher = Dispatcher<Number, Converter, DefaultRepresentations>;

}  // namespace hypro