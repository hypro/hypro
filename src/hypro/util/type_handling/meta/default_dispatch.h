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
static constexpr auto TypeEnum<BoxT<T...>> = representation_name::box;
template <class... T>
static constexpr auto TypeEnum<SupportFunctionT<T...>> = representation_name::support_function;

template <>
static constexpr int TypeEnum<BoxLinearOptimizationOn> = boxSetting_name::BoxLinearOptimizationOn;
template <>
static constexpr int TypeEnum<BoxLinearOptimizationOff> = boxSetting_name::BoxLinearOptimizationOff;
template <>
static constexpr int TypeEnum<BoxIntervalArithmeticOff> = boxSetting_name::BoxIntervalArithmeticOff;
template <>
static constexpr int TypeEnum<BoxAllOff> = boxSetting_name::BoxAllOff;

template <>
static constexpr int TypeEnum<SupportFunctionSetting> = supportFunctionSetting_name::SupportFunctionSetting;
template <>
static constexpr int TypeEnum<NoBoxReduction> = supportFunctionSetting_name::NoBoxReduction;
template <>
static constexpr int TypeEnum<NoBoxDetection> = supportFunctionSetting_name::NoBoxDetection;
template <>
static constexpr int TypeEnum<NoTrafoReduction> = supportFunctionSetting_name::NoTrafoReduction;
template <>
static constexpr int TypeEnum<NoReduction> = supportFunctionSetting_name::NoReduction;
template <>
static constexpr int TypeEnum<PolytopeSupportFunctionSetting> = supportFunctionSetting_name::PolytopeSupportFunctionSetting;

template <class Number, class Converter>
using DefaultDispatcher = Dispatcher<Number, Converter, DefaultRepresentations>;

}  // namespace hypro