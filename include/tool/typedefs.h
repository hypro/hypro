/*
 * Copyright (c) 2021.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once
#include <hypro/datastructures/HybridAutomaton/State.h>
#include <hypro/types.h>

namespace hydra {

using Number = double;
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
using StarsetType = hypro::Starset<Number>;

#ifdef HYPRO_USE_PPL
using PolytopeType = hypro::Polytope<Number>;
#endif

using State = hypro::State_t<Number>;
}  // namespace hydra
