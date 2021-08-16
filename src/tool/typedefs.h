#pragma once
#include <hypro/datastructures/HybridAutomaton/State.h>
#include <hypro/types.h>

namespace hydra {

using Number = mpq_class;
using tNumber = hypro::tNumber;

using SFType = hypro::SupportFunctionT<Number, hypro::Converter<Number>,
									   hypro::SupportFunctionSetting>;
using CarlPolytopeType = hypro::CarlPolytopeT<Number, hypro::Converter<Number>,
											  hypro::CarlPolytopeSetting>;
using BoxType = hypro::Box<Number>;
using HPolyType = hypro::HPolytope<Number>;
using VPolyType = hypro::VPolytope<Number>;
using ZonotopeType = hypro::Zonotope<Number>;
using ConstraintSetType = hypro::ConstraintSet<Number>;
using DifferenceBoundsType = hypro::DifferenceBounds<Number>;
#ifdef HYPRO_USE_PPL
using PolytopeType = hypro::Polytope<Number>;
#endif

using State = hypro::State_t<Number>;
}  // namespace hydra
