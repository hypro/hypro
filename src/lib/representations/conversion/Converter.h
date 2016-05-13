#pragma once

#include "util.h"
#include "representations/Box/Box.h"
#include "representations/Polytopes/HPolytope/HPolytope.h"
#include "representations/Polytopes/VPolytope/VPolytope.h"
#include "representations/SupportFunction/SupportFunction.h"
#include "representations/Zonotope/Zonotope.h"
#include "util/pca.h"
//#include "../../util/Plotter.h"
namespace hypro {

//enum for differentiating between exact conversion and over-/underapproximation (some functions support an alternative computation method).
enum CONV_MODE {EXACT, OVER, UNDER, ALTERNATIVE};

template<typename Number>
class Converter {
	public:

		using Box = BoxT<Number,Converter>;
		using HPolytope = HPolytopeT<Number,Converter>;
		using VPolytope = VPolytopeT<Number,Converter>;
		using SupportFunction = SupportFunctionT<Number,Converter>;
		using Zonotope = ZonotopeT<Number,Converter>;

		static Box toBox(const Box& source, const CONV_MODE = CONV_MODE::EXACT);
		static Box toBox(const HPolytope& source, const CONV_MODE = CONV_MODE::OVER);
		static Box toBox(const VPolytope& source, const CONV_MODE = CONV_MODE::OVER);
		static Box toBox(const SupportFunction& source, const CONV_MODE = CONV_MODE::OVER);
		static Box toBox(const Zonotope& source, const CONV_MODE = CONV_MODE::OVER);

		static HPolytope toHPolytope(const Box& source, const CONV_MODE = CONV_MODE::EXACT);
		static HPolytope toHPolytope(const HPolytope& source, const CONV_MODE = CONV_MODE::EXACT);
		static HPolytope toHPolytope(const VPolytope& source, const CONV_MODE = CONV_MODE::EXACT);
		static HPolytope toHPolytope(const SupportFunction& source, const CONV_MODE = CONV_MODE::OVER, unsigned numberOfDirections = defaultTemplateDirectionCount );
		static HPolytope toHPolytope(const Zonotope& source, const CONV_MODE = CONV_MODE::EXACT);

		static VPolytope toVPolytope(const Box& source, const CONV_MODE = CONV_MODE::EXACT);
		static VPolytope toVPolytope(const HPolytope& source, const CONV_MODE = CONV_MODE::EXACT);
		static VPolytope toVPolytope(const VPolytope& source, const CONV_MODE = CONV_MODE::EXACT);
		static VPolytope toVPolytope(const SupportFunction& source, const CONV_MODE = CONV_MODE::UNDER, unsigned numberOfDirections = defaultTemplateDirectionCount );
		static VPolytope toVPolytope(const Zonotope& source, const CONV_MODE = CONV_MODE::EXACT);

		static SupportFunction toSupportFunction(const Box& source, const CONV_MODE = CONV_MODE::EXACT);
		static SupportFunction toSupportFunction(const HPolytope& source, const CONV_MODE = CONV_MODE::EXACT);
		static SupportFunction toSupportFunction(const VPolytope& source, const CONV_MODE = CONV_MODE::EXACT);
		static SupportFunction toSupportFunction(const SupportFunction& source, const CONV_MODE = CONV_MODE::EXACT);
		static SupportFunction toSupportFunction(const Zonotope& source, const CONV_MODE = CONV_MODE::EXACT);

		static Zonotope toZonotope(const Box& source, const CONV_MODE = CONV_MODE::EXACT);
		static Zonotope toZonotope(const HPolytope& source, const CONV_MODE = CONV_MODE::OVER);
		static Zonotope toZonotope(const VPolytope& source, const CONV_MODE = CONV_MODE::OVER);
		static Zonotope toZonotope(const SupportFunction& source, const CONV_MODE = CONV_MODE::OVER, unsigned numberOfDirections = defaultTemplateDirectionCount );
		static Zonotope toZonotope(const Zonotope& source, const CONV_MODE = CONV_MODE::EXACT);
};

template<typename Number>
using Box = typename Converter<Number>::Box;

template<typename Number>
using HPolytope = typename Converter<Number>::HPolytope;

template<typename Number>
using VPolytope = typename Converter<Number>::VPolytope;

template<typename Number>
using SupportFunction = typename Converter<Number>::SupportFunction;

template<typename Number>
using Zonotope = typename Converter<Number>::Zonotope;

#include "converterToBox.tpp"
#include "converterToHPolytope.tpp"
#include "converterToVPolytope.tpp"
#include "converterToSupportFunction.tpp"
#include "converterToZonotope.tpp"

} // namespace

