#pragma once

#ifndef INCL_FROM_GOHEADER
static_assert( false, "This file may only be included indirectly by GeometricObjectBase.h" );
#endif
#define INCL_FROM_CONVERTERHEADER true

#include "../../util/pca.h"
#include "../../util/templateDirections.h"
#include "../Box/Box.h"
#include "../ConstraintSet/ConstraintSet.h"
#include "../DifferenceBounds/DifferenceBounds.h"
#include "../Ellipsoids/Ellipsoid.h"
#include "../OrthogonalPolyhedron/OrthogonalPolyhedron.h"
#include "../Polytope/Polytope.h"
#include "../Polytopes/HPolytope/HPolytope.h"
#include "../Polytopes/VPolytope/VPolytope.h"
#include "../Polytopes/carlPolytope/carlPolytope.h"
#include "../Starset/Starset.h"
#include "../SupportFunction/SupportFunction.h"
#include "../SupportFunctionNew/SupportFunctionNew.h"
#include "../TemplatePolyhedron/TemplatePolyhedron.h"
#include "../Zonotope/Zonotope.h"

#include <hypro/flags.h>
//#include "../Orthoplex/Orthoplex.h"

namespace hypro {

/**
 * @brief      enum for differentiating between exact conversion and over-/underapproximation (some functions support an alternative computation method).
 */

enum CONV_MODE {
	EXACT,
	OVER,
	UNDER,
	ALTERNATIVE
};

template <typename Number>
class Converter {
  public:
	/* BEGIN typedefs (do not remove this comment!) */

	// using Orthoplex = OrthoplexT<Number,Converter,OrthoplexDefault>;
	using TemplatePolyhedron = TemplatePolyhedronT<Number, Converter, TemplatePolyhedronDefault>;
	using Box = BoxT<Number, Converter, BoxLinearOptimizationOn>;
	using CarlPolytope = CarlPolytopeT<Number, Converter, CarlPolytopeSetting>;
	using ConstraintSet = ConstraintSetT<Number, ConstraintSetSettings>;
	using Ellipsoid = EllipsoidT<Number, Converter>;
	using HPolytope = HPolytopeT<Number, Converter, HPolytopeSetting>;
	using HPolytopeCached = HPolytopeT<Number, Converter, HPolytopeBoundingBoxCaching>;
	using OrthogonalPolyhedron = OrthogonalPolyhedronT<Number, Converter, BoxLinearOptimizationOn>;
	using VPolytope = VPolytopeT<Number, Converter, VPolytopeSetting>;
	using DifferenceBounds = DifferenceBoundsT<Number, Converter, DifferenceBoundsSetting>;
#ifdef HYPRO_USE_PPL
	using Polytope = PolytopeT<Number, Converter, PolytopeSetting>;
#endif
	using Starset = StarsetT<Number, Converter, StarsetDefault>;
	using SupportFunction = SupportFunctionT<Number, Converter, SupportFunctionSetting>;
	using Zonotope = ZonotopeT<Number, Converter, ZonotopeSetting>;
	using SupportFunctionNew = SupportFunctionNewT<Number, Converter, SupportFunctionNewMorePrecision>;

	/* END typedefs (do not remove this comment!) */

	/* BEGIN Conversion (do not remove this comment!) */

		template<typename StarsetSetting = typename Starset::Settings, typename inSetting>
		static StarsetT<Number,Converter<Number>,StarsetSetting> toStarset(const StarsetT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
		template<typename StarsetSetting = typename Starset::Settings, typename inSetting>
		static StarsetT<Number,Converter<Number>,StarsetSetting> toStarset(const TemplatePolyhedronT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
		template<typename StarsetSetting = typename Starset::Settings, typename inSetting>
		static StarsetT<Number,Converter<Number>,StarsetSetting> toStarset(const BoxT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
		template<typename StarsetSetting = typename Starset::Settings, typename inSetting>
		static StarsetT<Number,Converter<Number>,StarsetSetting> toStarset(const CarlPolytopeT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
		template<typename StarsetSetting = typename Starset::Settings, typename inSetting>
		static StarsetT<Number,Converter<Number>,StarsetSetting> toStarset(const ConstraintSetT<Number,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
		template<typename StarsetSetting = typename Starset::Settings>
		static StarsetT<Number,Converter<Number>,StarsetSetting> toStarset(const Ellipsoid& source, const CONV_MODE = CONV_MODE::EXACT);
		template<typename StarsetSetting = typename Starset::Settings, typename inSetting>
		static StarsetT<Number,Converter<Number>,StarsetSetting> toStarset(const HPolytopeT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
		template<typename StarsetSetting = typename Starset::Settings, typename inSetting>
		static StarsetT<Number,Converter<Number>,StarsetSetting> toStarset(const VPolytopeT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
		template<typename StarsetSetting = typename Starset::Settings, typename inSetting>
		static StarsetT<Number,Converter<Number>,StarsetSetting> toStarset(const DifferenceBoundsT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
		#ifdef HYPRO_USE_PPL
		template<typename StarsetSetting = typename Starset::Settings, typename inSetting>
		static StarsetT<Number,Converter<Number>,StarsetSetting> toStarset(const PolytopeT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
		#endif
		template<typename StarsetSetting = typename Starset::Settings, typename inSetting>
		static StarsetT<Number,Converter<Number>,StarsetSetting> toStarset(const SupportFunctionT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
		template<typename StarsetSetting = typename Starset::Settings, typename inSetting>
		static StarsetT<Number,Converter<Number>,StarsetSetting> toStarset(const ZonotopeT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
		template<typename StarsetSetting = typename Starset::Settings, typename inSetting>
		static StarsetT<Number,Converter<Number>,StarsetSetting> toStarset(const SupportFunctionNewT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
	/*
			template<typename OrthoplexSetting = typename Orthoplex::Settings, typename inSetting>
			static OrthoplexT<Number,Converter<Number>,OrthoplexSetting> toOrthoplex(const OrthoplexT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
			template<typename OrthoplexSetting = typename Orthoplex::Settings, typename inSetting>
			static OrthoplexT<Number,Converter<Number>,OrthoplexSetting> toOrthoplex(const TemplatePolyhedronT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
			template<typename OrthoplexSetting = typename Orthoplex::Settings, typename inSetting>
			static OrthoplexT<Number,Converter<Number>,OrthoplexSetting> toOrthoplex(const BoxT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
			template<typename OrthoplexSetting = typename Orthoplex::Settings, typename inSetting>
			static OrthoplexT<Number,Converter<Number>,OrthoplexSetting> toOrthoplex(const CarlPolytopeT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
			template<typename OrthoplexSetting = typename Orthoplex::Settings, typename inSetting>
			static OrthoplexT<Number,Converter<Number>,OrthoplexSetting> toOrthoplex(const ConstraintSetT<Number,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
			template<typename OrthoplexSetting = typename Orthoplex::Settings>
			static OrthoplexT<Number,Converter<Number>,OrthoplexSetting> toOrthoplex(const Ellipsoid& source, const CONV_MODE = CONV_MODE::EXACT);
			template<typename OrthoplexSetting = typename Orthoplex::Settings, typename inSetting>
			static OrthoplexT<Number,Converter<Number>,OrthoplexSetting> toOrthoplex(const HPolytopeT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
			template<typename OrthoplexSetting = typename Orthoplex::Settings, typename inSetting>
			static OrthoplexT<Number,Converter<Number>,OrthoplexSetting> toOrthoplex(const VPolytopeT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
			template<typename OrthoplexSetting = typename Orthoplex::Settings, typename inSetting>
			static OrthoplexT<Number,Converter<Number>,OrthoplexSetting> toOrthoplex(const DifferenceBoundsT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
			#ifdef HYPRO_USE_PPL
			template<typename OrthoplexSetting = typename Orthoplex::Settings, typename inSetting>
			static OrthoplexT<Number,Converter<Number>,OrthoplexSetting> toOrthoplex(const PolytopeT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
			#endif
			template<typename OrthoplexSetting = typename Orthoplex::Settings, typename inSetting>
			static OrthoplexT<Number,Converter<Number>,OrthoplexSetting> toOrthoplex(const SupportFunctionT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
			template<typename OrthoplexSetting = typename Orthoplex::Settings, typename inSetting>
			static OrthoplexT<Number,Converter<Number>,OrthoplexSetting> toOrthoplex(const SupportFunctionNewT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
			template<typename OrthoplexSetting = typename Orthoplex::Settings, typename inSetting>
			static OrthoplexT<Number,Converter<Number>,OrthoplexSetting> toOrthoplex(const ZonotopeT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
	*/

	template <typename TemplatePolyhedronSetting = typename TemplatePolyhedron::Settings, typename inSetting>
	static TemplatePolyhedronT<Number, Converter<Number>, TemplatePolyhedronSetting> toTemplatePolyhedron( const TemplatePolyhedronT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template<typename TemplatePolyhedronSetting = typename TemplatePolyhedron::Settings, typename inSetting>
	static TemplatePolyhedronT<Number,Converter<Number>,TemplatePolyhedronSetting> toTemplatePolyhedron(const StarsetT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
	// template<typename TemplatePolyhedronSetting = typename TemplatePolyhedron::Settings, typename inSetting>
	// static TemplatePolyhedronT<Number,Converter<Number>,TemplatePolyhedronSetting> toTemplatePolyhedron(const OrthoplexT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
	template <typename TemplatePolyhedronSetting = typename TemplatePolyhedron::Settings, typename inSetting>
	static TemplatePolyhedronT<Number, Converter<Number>, TemplatePolyhedronSetting> toTemplatePolyhedron( const BoxT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename TemplatePolyhedronSetting = typename TemplatePolyhedron::Settings, typename inSetting>
	static TemplatePolyhedronT<Number, Converter<Number>, TemplatePolyhedronSetting> toTemplatePolyhedron( const CarlPolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename TemplatePolyhedronSetting = typename TemplatePolyhedron::Settings, typename inSetting>
	static TemplatePolyhedronT<Number, Converter<Number>, TemplatePolyhedronSetting> toTemplatePolyhedron( const ConstraintSetT<Number, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename TemplatePolyhedronSetting = typename TemplatePolyhedron::Settings>
	static TemplatePolyhedronT<Number, Converter<Number>, TemplatePolyhedronSetting> toTemplatePolyhedron( const Ellipsoid& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename TemplatePolyhedronSetting = typename TemplatePolyhedron::Settings, typename inSetting>
	static TemplatePolyhedronT<Number, Converter<Number>, TemplatePolyhedronSetting> toTemplatePolyhedron( const HPolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename TemplatePolyhedronSetting = typename TemplatePolyhedron::Settings, typename inSetting>
	static TemplatePolyhedronT<Number, Converter<Number>, TemplatePolyhedronSetting> toTemplatePolyhedron( const VPolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename TemplatePolyhedronSetting = typename TemplatePolyhedron::Settings, typename inSetting>
	static TemplatePolyhedronT<Number, Converter<Number>, TemplatePolyhedronSetting> toTemplatePolyhedron( const DifferenceBoundsT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
#ifdef HYPRO_USE_PPL
	template <typename TemplatePolyhedronSetting = typename TemplatePolyhedron::Settings, typename inSetting>
	static TemplatePolyhedronT<Number, Converter<Number>, TemplatePolyhedronSetting> toTemplatePolyhedron( const PolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
#endif
	template <typename TemplatePolyhedronSetting = typename TemplatePolyhedron::Settings, typename inSetting>
	static TemplatePolyhedronT<Number, Converter<Number>, TemplatePolyhedronSetting> toTemplatePolyhedron( const SupportFunctionT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename TemplatePolyhedronSetting = typename TemplatePolyhedron::Settings, typename inSetting>
	static TemplatePolyhedronT<Number, Converter<Number>, TemplatePolyhedronSetting> toTemplatePolyhedron( const SupportFunctionNewT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename TemplatePolyhedronSetting = typename TemplatePolyhedron::Settings, typename inSetting>
	static TemplatePolyhedronT<Number, Converter<Number>, TemplatePolyhedronSetting> toTemplatePolyhedron( const ZonotopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );

	template <typename BoxSetting = typename Box::Settings, typename inSetting>
	static BoxT<Number, Converter<Number>, BoxSetting> toBox( const TemplatePolyhedronT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template<typename BoxSetting = typename Box::Settings, typename inSetting>
	static BoxT<Number,Converter<Number>,BoxSetting> toBox(const StarsetT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
	// template<typename BoxSetting = typename Box::Settings, typename inSetting>
	// static BoxT<Number,Converter<Number>,BoxSetting> toBox(const OrthoplexT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
	template <typename BoxSetting = typename Box::Settings, typename InSetting>
	static BoxT<Number, Converter<Number>, BoxSetting> toBox( const BoxT<Number, Converter<Number>, InSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename BoxSetting = typename Box::Settings, typename inSetting>
	static BoxT<Number, Converter<Number>, BoxSetting> toBox( const ConstraintSetT<Number, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename BoxSetting = typename Box::Settings>
	static BoxT<Number, Converter<Number>, BoxSetting> toBox( const Ellipsoid& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename BoxSetting = typename Box::Settings, typename inSetting>
	static BoxT<Number, Converter<Number>, BoxSetting> toBox( const HPolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::ALTERNATIVE );
	template <typename BoxSetting = typename Box::Settings, typename inSetting>
	static BoxT<Number, Converter<Number>, BoxSetting> toBox( const VPolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::OVER );
#ifdef HYPRO_USE_PPL
	template <typename BoxSetting = typename Box::Settings, typename inSetting>
	static BoxT<Number, Converter<Number>, BoxSetting> toBox( const PolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::OVER );
#endif
	template <typename BoxSetting = typename Box::Settings, typename inSetting>
	static BoxT<Number, Converter<Number>, BoxSetting> toBox( const SupportFunctionT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::OVER );
	template <typename BoxSetting = typename Box::Settings, typename inSetting>
	static BoxT<Number, Converter<Number>, BoxSetting> toBox( const ZonotopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::OVER );
	template <typename BoxSetting = typename Box::Settings, typename inSetting>
	static BoxT<Number, Converter<Number>, BoxSetting> toBox( const DifferenceBoundsT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::OVER );
	template <typename BoxSetting = typename Box::Settings, typename inSetting>
	static BoxT<Number, Converter<Number>, BoxSetting> toBox( const CarlPolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::OVER );
	template <typename BoxSetting = typename Box::Settings, typename inSetting>
	static BoxT<Number, Converter<Number>, BoxSetting> toBox( const SupportFunctionNewT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::OVER );

	template <typename CarlPolytopeSetting = typename CarlPolytope::Settings, typename inSetting>
	static CarlPolytopeT<Number, Converter<Number>, CarlPolytopeSetting> toCarlPolytope( const TemplatePolyhedronT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template<typename CarlPolytopeSetting = typename CarlPolytope::Settings, typename inSetting>
	static CarlPolytopeT<Number,Converter<Number>,CarlPolytopeSetting> toCarlPolytope(const StarsetT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
	// template<typename CarlPolytopeSetting = typename CarlPolytope::Settings, typename inSetting>
	// static CarlPolytopeT<Number,Converter<Number>,CarlPolytopeSetting> toCarlPolytope(const OrthoplexT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
	template <typename CarlPolytopeSetting = typename CarlPolytope::Settings, typename inSetting>
	static CarlPolytopeT<Number, Converter<Number>, CarlPolytopeSetting> toCarlPolytope( const BoxT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename CarlPolytopeSetting = typename CarlPolytope::Settings, typename inSetting>
	static CarlPolytopeT<Number, Converter<Number>, CarlPolytopeSetting> toCarlPolytope( const ConstraintSetT<Number, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename CarlPolytopeSetting = typename CarlPolytope::Settings>
	static CarlPolytopeT<Number, Converter<Number>, CarlPolytopeSetting> toCarlPolytope( const Ellipsoid& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename CarlPolytopeSetting = typename CarlPolytope::Settings, typename inSetting>
	static CarlPolytopeT<Number, Converter<Number>, CarlPolytopeSetting> toCarlPolytope( const HPolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename CarlPolytopeSetting = typename CarlPolytope::Settings, typename inSetting>
	static CarlPolytopeT<Number, Converter<Number>, CarlPolytopeSetting> toCarlPolytope( const VPolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
#ifdef HYPRO_USE_PPL
	template <typename CarlPolytopeSetting = typename CarlPolytope::Settings, typename inSetting>
	static CarlPolytopeT<Number, Converter<Number>, CarlPolytopeSetting> toCarlPolytope( const PolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
#endif
	template <typename CarlPolytopeSetting = typename CarlPolytope::Settings, typename inSetting>
	static CarlPolytopeT<Number, Converter<Number>, CarlPolytopeSetting> toCarlPolytope( const SupportFunctionT<Number, Converter<Number>, inSetting>& source, const std::vector<vector_t<Number>>& additionalDirections = std::vector<vector_t<Number>>(), const CONV_MODE = CONV_MODE::OVER, std::size_t numberOfDirections = defaultTemplateDirectionCount );
	template <typename CarlPolytopeSetting = typename CarlPolytope::Settings, typename inSetting>
	static CarlPolytopeT<Number, Converter<Number>, CarlPolytopeSetting> toCarlPolytope( const ZonotopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename CarlPolytopeSetting = typename CarlPolytope::Settings, typename inSetting>
	static CarlPolytopeT<Number, Converter<Number>, CarlPolytopeSetting> toCarlPolytope( const DifferenceBoundsT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename CarlPolytopeSetting = typename CarlPolytope::Settings, typename inSetting>
	static CarlPolytopeT<Number, Converter<Number>, CarlPolytopeSetting> toCarlPolytope( const CarlPolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename CarlPolytopeSetting = typename CarlPolytope::Settings, typename inSetting>
	static CarlPolytopeT<Number, Converter<Number>, CarlPolytopeSetting> toCarlPolytope( const SupportFunctionNewT<Number, Converter<Number>, inSetting>& _source, const std::vector<vector_t<Number>>& additionalDirections = std::vector<vector_t<Number>>(), const CONV_MODE = CONV_MODE::OVER, std::size_t numberOfDirections = defaultTemplateDirectionCount );

	template <typename CSSetting = typename ConstraintSet::Settings, typename inSetting>
	static ConstraintSetT<Number, CSSetting> toConstraintSet( const TemplatePolyhedronT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template<typename ConstraintSetSetting = typename ConstraintSet::Settings, typename inSetting>
	static ConstraintSetT<Number,ConstraintSetSetting> toConstraintSet(const StarsetT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
	// template<typename CSSetting = typename ConstraintSet::Settings, typename inSetting>
	// static ConstraintSetT<Number,CSSetting> toConstraintSet(const OrthoplexT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
	template <typename CSSetting = typename ConstraintSet::Settings, typename inSetting>
	static ConstraintSetT<Number, CSSetting> toConstraintSet( const BoxT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename CSSetting = typename ConstraintSet::Settings, typename inSetting>
	static ConstraintSetT<Number, CSSetting> toConstraintSet( const ConstraintSetT<Number, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename CSSetting = typename ConstraintSet::Settings>
	static ConstraintSetT<Number, CSSetting> toConstraintSet( const Ellipsoid& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename CSSetting = typename ConstraintSet::Settings, typename inSetting>
	static ConstraintSetT<Number, CSSetting> toConstraintSet( const HPolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::OVER );
	template <typename CSSetting = typename ConstraintSet::Settings, typename inSetting>
	static ConstraintSetT<Number, CSSetting> toConstraintSet( const VPolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::OVER );
#ifdef HYPRO_USE_PPL
	template <typename CSSetting = typename ConstraintSet::Settings, typename inSetting>
	static ConstraintSetT<Number, CSSetting> toConstraintSet( const PolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::OVER );
#endif
	template <typename CSSetting = typename ConstraintSet::Settings, typename inSetting>
	static ConstraintSetT<Number, CSSetting> toConstraintSet( const SupportFunctionT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::OVER );
	template <typename CSSetting = typename ConstraintSet::Settings, typename inSetting>
	static ConstraintSetT<Number, CSSetting> toConstraintSet( const ZonotopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::OVER );
	template <typename CSSetting = typename ConstraintSet::Settings, typename inSetting>
	static ConstraintSetT<Number, CSSetting> toConstraintSet( const DifferenceBoundsT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::OVER );
	template <typename CSSetting = typename ConstraintSet::Settings, typename inSetting>
	static ConstraintSetT<Number, CSSetting> toConstraintSet( const CarlPolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::OVER );
	template <typename CSSetting = typename ConstraintSet::Settings, typename inSetting>
	static ConstraintSetT<Number, CSSetting> toConstraintSet( const SupportFunctionNewT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::OVER );

	template <typename HPolySetting = typename HPolytope::Settings, typename inSetting>
	static HPolytopeT<Number, Converter<Number>, HPolySetting> toHPolytope( const TemplatePolyhedronT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename HPolySetting = typename HPolytopeCached::Settings, typename inSetting>
	static HPolytopeT<Number, Converter<Number>, HPolySetting> toHPolytope( const StarsetT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
	// template<typename HPolySetting = typename HPolytope::Settings, typename inSetting>
	// static HPolytopeT<Number,Converter<Number>,HPolySetting> toHPolytope(const OrthoplexT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
	template <typename HPolySetting = typename HPolytope::Settings, typename inSetting>
	static HPolytopeT<Number, Converter<Number>, HPolySetting> toHPolytope( const BoxT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename HPolySetting = typename HPolytope::Settings, typename inSetting>
	static HPolytopeT<Number, Converter<Number>, HPolySetting> toHPolytope( const ConstraintSetT<Number, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename HPolySetting = typename HPolytope::Settings>
	static HPolytopeT<Number, Converter<Number>, HPolySetting> toHPolytope( const Ellipsoid& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename HPolySetting = typename HPolytope::Settings, typename inSetting>
	static HPolytopeT<Number, Converter<Number>, HPolySetting> toHPolytope( const HPolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename HPolySetting = typename HPolytope::Settings, typename inSetting>
	static HPolytopeT<Number, Converter<Number>, HPolySetting> toHPolytope( const VPolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
#ifdef HYPRO_USE_PPL
	template <typename HPolySetting = typename HPolytope::Settings, typename inSetting>
	static HPolytopeT<Number, Converter<Number>, HPolySetting> toHPolytope( const PolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
#endif
	template <typename HPolySetting = typename HPolytope::Settings, typename inSetting>
	static HPolytopeT<Number, Converter<Number>, HPolySetting> toHPolytope( const SupportFunctionT<Number, Converter<Number>, inSetting>& source, const std::vector<vector_t<Number>>& additionalDirections = std::vector<vector_t<Number>>(), const CONV_MODE = CONV_MODE::OVER, std::size_t numberOfDirections = defaultTemplateDirectionCount );
	template <typename HPolySetting = typename HPolytope::Settings, typename inSetting>
	static HPolytopeT<Number, Converter<Number>, HPolySetting> toHPolytope( const ZonotopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename HPolySetting = typename HPolytope::Settings, typename inSetting>
	static HPolytopeT<Number, Converter<Number>, HPolySetting> toHPolytope( const DifferenceBoundsT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename HPolySetting = typename HPolytope::Settings, typename inSetting>
	static HPolytopeT<Number, Converter<Number>, HPolySetting> toHPolytope( const CarlPolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename HPolySetting = typename HPolytope::Settings, typename inSetting>
	static HPolytopeT<Number, Converter<Number>, HPolySetting> toHPolytope( const SupportFunctionNewT<Number, Converter<Number>, inSetting>& source, const std::vector<vector_t<Number>>& additionalDirections = std::vector<vector_t<Number>>(), const CONV_MODE = CONV_MODE::OVER, std::size_t numberOfDirections = defaultTemplateDirectionCount );

	template <typename VPolySetting = typename VPolytope::Settings, typename inSetting>
	static VPolytopeT<Number, Converter<Number>, VPolySetting> toVPolytope( const TemplatePolyhedronT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template<typename VPolytopeSetting = typename VPolytope::Settings, typename inSetting>
	static VPolytopeT<Number,Converter<Number>,VPolytopeSetting> toVPolytope(const StarsetT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
	// template<typename VPolySetting = typename VPolytope::Settings, typename inSetting>
	// static VPolytopeT<Number,Converter<Number>,VPolySetting> toVPolytope(const OrthoplexT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
	template <typename VPolySetting = typename VPolytope::Settings, typename inSetting>
	static VPolytopeT<Number, Converter<Number>, VPolySetting> toVPolytope( const BoxT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename VPolySetting = typename VPolytope::Settings, typename inSetting>
	static VPolytopeT<Number, Converter<Number>, VPolySetting> toVPolytope( const ConstraintSetT<Number, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename VPolySetting = typename VPolytope::Settings>
	static VPolytopeT<Number, Converter<Number>, VPolySetting> toVPolytope( const Ellipsoid& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename VPolySetting = typename VPolytope::Settings, typename inSetting>
	static VPolytopeT<Number, Converter<Number>, VPolySetting> toVPolytope( const HPolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename VPolySetting = typename VPolytope::Settings, typename inSetting>
	static VPolytopeT<Number, Converter<Number>, VPolySetting> toVPolytope( const VPolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
#ifdef HYPRO_USE_PPL
	template <typename VPolySetting = typename VPolytope::Settings, typename inSetting>
	static VPolytopeT<Number, Converter<Number>, VPolySetting> toVPolytope( const PolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
#endif
	template <typename VPolySetting = typename VPolytope::Settings, typename inSetting>
	static VPolytopeT<Number, Converter<Number>, VPolySetting> toVPolytope( const SupportFunctionT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::UNDER, std::size_t numberOfDirections = defaultTemplateDirectionCount );
	template <typename VPolySetting = typename VPolytope::Settings, typename inSetting>
	static VPolytopeT<Number, Converter<Number>, VPolySetting> toVPolytope( const ZonotopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename VPolySetting = typename VPolytope::Settings, typename inSetting>
	static VPolytopeT<Number, Converter<Number>, VPolySetting> toVPolytope( const DifferenceBoundsT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename VPolySetting = typename VPolytope::Settings, typename inSetting>
	static VPolytopeT<Number, Converter<Number>, VPolySetting> toVPolytope( const CarlPolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename VPolySetting = typename VPolytope::Settings, typename inSetting>
	static VPolytopeT<Number, Converter<Number>, VPolySetting> toVPolytope( const SupportFunctionNewT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::UNDER, std::size_t numberOfDirections = defaultTemplateDirectionCount );

	template <typename SFSetting = typename SupportFunction::Settings, typename inSetting>
	static SupportFunctionT<Number, Converter<Number>, SFSetting> toSupportFunction( const TemplatePolyhedronT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template<typename SupportFunctionSetting = typename SupportFunction::Settings, typename inSetting>
	static SupportFunctionT<Number,Converter<Number>,SupportFunctionSetting> toSupportFunction(const StarsetT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
	// template<typename SFSetting = typename SupportFunction::Settings, typename inSetting>
	// static SupportFunctionT<Number,Converter<Number>,SFSetting> toSupportFunction(const OrthoplexT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
	template <typename SFSetting = typename SupportFunction::Settings, typename inSetting>
	static SupportFunctionT<Number, Converter<Number>, SFSetting> toSupportFunction( const BoxT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename SFSetting = typename SupportFunction::Settings, typename inSetting>
	static SupportFunctionT<Number, Converter<Number>, SFSetting> toSupportFunction( const ConstraintSetT<Number, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename SFSetting = typename SupportFunction::Settings>
	static SupportFunctionT<Number, Converter<Number>, SFSetting> toSupportFunction( const Ellipsoid& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename SFSetting = typename SupportFunction::Settings, typename inSetting>
	static SupportFunctionT<Number, Converter<Number>, SFSetting> toSupportFunction( const HPolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename SFSetting = typename SupportFunction::Settings, typename inSetting>
	static SupportFunctionT<Number, Converter<Number>, SFSetting> toSupportFunction( const VPolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
#ifdef HYPRO_USE_PPL
	template <typename SFSetting = typename SupportFunction::Settings, typename inSetting>
	static SupportFunctionT<Number, Converter<Number>, SFSetting> toSupportFunction( const PolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
#endif
	template <typename SFSetting = typename SupportFunction::Settings, typename inSetting>
	static SupportFunctionT<Number, Converter<Number>, SFSetting> toSupportFunction( const SupportFunctionT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename SFSetting = typename SupportFunction::Settings, typename inSetting>
	static SupportFunctionT<Number, Converter<Number>, SFSetting> toSupportFunction( const ZonotopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename SFSetting = typename SupportFunction::Settings, typename inSetting>
	static SupportFunctionT<Number, Converter<Number>, SFSetting> toSupportFunction( const DifferenceBoundsT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename SFSetting = typename SupportFunction::Settings, typename inSetting>
	static SupportFunctionT<Number, Converter<Number>, SFSetting> toSupportFunction( const CarlPolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename SFSetting = typename SupportFunction::Settings, typename inSetting>
	static SupportFunctionT<Number, Converter<Number>, SFSetting> toSupportFunction( const SupportFunctionNewT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::UNDER );

	template <typename ZonotopeSetting = typename Zonotope::Settings, typename inSetting>
	static ZonotopeT<Number, Converter<Number>, ZonotopeSetting> toZonotope( const TemplatePolyhedronT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template<typename ZonotopeSetting = typename Zonotope::Settings, typename inSetting>
	static ZonotopeT<Number,Converter<Number>,ZonotopeSetting> toZonotope(const StarsetT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
	// template<typename ZonotopeSetting = typename Zonotope::Settings, typename inSetting>
	// static ZonotopeT<Number,Converter<Number>,ZonotopeSetting> toZonotope(const OrthoplexT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
	template <typename ZonotopeSetting = typename Zonotope::Settings, typename inSetting>
	static ZonotopeT<Number, Converter<Number>, ZonotopeSetting> toZonotope( const BoxT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename ZonotopeSetting = typename Zonotope::Settings, typename inSetting>
	static ZonotopeT<Number, Converter<Number>, ZonotopeSetting> toZonotope( const CarlPolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::OVER );
	template <typename ZonotopeSetting = typename Zonotope::Settings, typename inSetting>
	static ZonotopeT<Number, Converter<Number>, ZonotopeSetting> toZonotope( const ConstraintSetT<Number, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename ZonotopeSetting = typename Zonotope::Settings>
	static ZonotopeT<Number, Converter<Number>, ZonotopeSetting> toZonotope( const Ellipsoid& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename ZonotopeSetting = typename Zonotope::Settings, typename inSetting>
	static ZonotopeT<Number, Converter<Number>, ZonotopeSetting> toZonotope( const HPolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::OVER );
	template <typename ZonotopeSetting = typename Zonotope::Settings, typename inSetting>
	static ZonotopeT<Number, Converter<Number>, ZonotopeSetting> toZonotope( const VPolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::OVER );
#ifdef HYPRO_USE_PPL
	template <typename ZonotopeSetting = typename Zonotope::Settings, typename inSetting>
	static ZonotopeT<Number, Converter<Number>, ZonotopeSetting> toZonotope( const PolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
#endif
	template <typename ZonotopeSetting = typename Zonotope::Settings, typename inSetting>
	static ZonotopeT<Number, Converter<Number>, ZonotopeSetting> toZonotope( const SupportFunctionT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::OVER, std::size_t numberOfDirections = defaultTemplateDirectionCount );
	template <typename ZonotopeSetting = typename Zonotope::Settings, typename inSetting>
	static ZonotopeT<Number, Converter<Number>, ZonotopeSetting> toZonotope( const ZonotopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename ZonotopeSetting = typename Zonotope::Settings, typename inSetting>
	static ZonotopeT<Number, Converter<Number>, ZonotopeSetting> toZonotope( const DifferenceBoundsT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::OVER );
	template <typename ZonotopeSetting = typename Zonotope::Settings, typename inSetting>
	static ZonotopeT<Number, Converter<Number>, ZonotopeSetting> toZonotope( const SupportFunctionNewT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::OVER, std::size_t numberOfDirections = defaultTemplateDirectionCount );

#ifdef HYPRO_USE_PPL
	template <typename PolytopeSetting = typename Polytope::Settings, typename inSetting>
	static PolytopeT<Number, Converter<Number>, PolytopeSetting> toPolytope( const TemplatePolyhedronT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template<typename PolytopeSetting = typename Polytope::Settings, typename inSetting>
	static PolytopeT<Number,Converter<Number>,PolytopeSetting> toPolytope(const StarsetT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
	// template<typename PolytopeSetting = typename Polytope::Settings, typename inSetting>
	// static PolytopeT<Number,Converter<Number>,PolytopeSetting> toPolytope(const OrthoplexT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
	template <typename PolytopeSetting = typename Polytope::Settings, typename inSetting>
	static PolytopeT<Number, Converter<Number>, PolytopeSetting> toPolytope( const PolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename PolytopeSetting = typename Polytope::Settings, typename inSetting>
	static PolytopeT<Number, Converter<Number>, PolytopeSetting> toPolytope( const BoxT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename PolytopeSetting = typename Polytope::Settings, typename inSetting>
	static PolytopeT<Number, Converter<Number>, PolytopeSetting> toPolytope( const ConstraintSetT<Number, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename PolytopeSetting = typename Polytope::Settings>
	static PolytopeT<Number, Converter<Number>, PolytopeSetting> toPolytope( const Ellipsoid& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename PolytopeSetting = typename Polytope::Settings, typename inSetting>
	static PolytopeT<Number, Converter<Number>, PolytopeSetting> toPolytope( const HPolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename PolytopeSetting = typename Polytope::Settings, typename inSetting>
	static PolytopeT<Number, Converter<Number>, PolytopeSetting> toPolytope( const VPolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename PolytopeSetting = typename Polytope::Settings, typename inSetting>
	static PolytopeT<Number, Converter<Number>, PolytopeSetting> toPolytope( const SupportFunctionT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::OVER, std::size_t numberOfDirections = defaultTemplateDirectionCount );
	template <typename PolytopeSetting = typename Polytope::Settings, typename inSetting>
	static PolytopeT<Number, Converter<Number>, PolytopeSetting> toPolytope( const ZonotopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename PolytopeSetting = typename Polytope::Settings, typename inSetting>
	static PolytopeT<Number, Converter<Number>, PolytopeSetting> toPolytope( const DifferenceBoundsT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );  // TODO NOT IMPLEMENTED YET
	template <typename PolytopeSetting = typename Polytope::Settings, typename inSetting>
	static PolytopeT<Number, Converter<Number>, PolytopeSetting> toPolytope( const CarlPolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );  // TODO NOT IMPLEMENTED YET
	template <typename PolytopeSetting = typename Polytope::Settings, typename inSetting>
	static PolytopeT<Number, Converter<Number>, PolytopeSetting> toPolytope( const SupportFunctionNewT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );	 // TODO NOT IMPLEMENTED YET
#endif

	template <typename DBSetting = typename DifferenceBounds::Settings, typename inSetting>
	static DifferenceBoundsT<Number, Converter<Number>, DBSetting> toDifferenceBounds( const TemplatePolyhedronT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template<typename DifferenceBoundsSetting = typename DifferenceBounds::Settings, typename inSetting>
	static DifferenceBoundsT<Number,Converter<Number>,DifferenceBoundsSetting> toDifferenceBounds(const StarsetT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
	// template<typename DBSetting = typename DifferenceBounds::Settings, typename inSetting>
	// static DifferenceBoundsT<Number,Converter<Number>,DBSetting> toDifferenceBounds(const OrthoplexT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
	template <typename DBSetting = typename DifferenceBounds::Settings, typename inSetting>
	static DifferenceBoundsT<Number, Converter<Number>, DBSetting> toDifferenceBounds( const BoxT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename DBSetting = typename DifferenceBounds::Settings, typename inSetting>
	static DifferenceBoundsT<Number, Converter<Number>, DBSetting> toDifferenceBounds( const CarlPolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename DBSetting = typename DifferenceBounds::Settings, typename inSetting>
	static DifferenceBoundsT<Number, Converter<Number>, DBSetting> toDifferenceBounds( const ConstraintSetT<Number, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename DBSetting = typename DifferenceBounds::Settings>
	static DifferenceBoundsT<Number, Converter<Number>, DBSetting> toDifferenceBounds( const Ellipsoid& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename DBSetting = typename DifferenceBounds::Settings, typename inSetting>
	static DifferenceBoundsT<Number, Converter<Number>, DBSetting> toDifferenceBounds( const HPolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename DBSetting = typename DifferenceBounds::Settings, typename inSetting>
	static DifferenceBoundsT<Number, Converter<Number>, DBSetting> toDifferenceBounds( const VPolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
#ifdef HYPRO_USE_PPL
	template <typename DBSetting = typename DifferenceBounds::Settings, typename inSetting>
	static DifferenceBoundsT<Number, Converter<Number>, DBSetting> toDifferenceBounds( const PolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );	 // TODO NOT IMPLEMENTED YET
#endif
	template <typename DBSetting = typename DifferenceBounds::Settings, typename inSetting>
	static DifferenceBoundsT<Number, Converter<Number>, DBSetting> toDifferenceBounds( const SupportFunctionT<Number, Converter<Number>, inSetting>& source, const std::vector<vector_t<Number>>& additionalDirections = std::vector<vector_t<Number>>(), const CONV_MODE = CONV_MODE::OVER, std::size_t numberOfDirections = defaultTemplateDirectionCount );
	template <typename DBSetting = typename DifferenceBounds::Settings, typename inSetting>
	static DifferenceBoundsT<Number, Converter<Number>, DBSetting> toDifferenceBounds( const ZonotopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename DBSetting = typename DifferenceBounds::Settings, typename inSetting>
	static DifferenceBoundsT<Number, Converter<Number>, DBSetting> toDifferenceBounds( const DifferenceBoundsT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename DBSetting = typename DifferenceBounds::Settings, typename inSetting>
	static DifferenceBoundsT<Number, Converter<Number>, DBSetting> toDifferenceBounds( const SupportFunctionNewT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );

	template <typename SFNSetting = typename SupportFunctionNew::Settings, typename inSetting>
	static SupportFunctionNewT<Number, Converter<Number>, SFNSetting> toSupportFunctionNew( const TemplatePolyhedronT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	// template<typename SFNSetting = typename SupportFunctionNew::Settings, typename inSetting>
	// static SupportFunctionNewT<Number,Converter<Number>,SFNSetting> toSupportFunctionNew(const OrthoplexT<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);
	template <typename SFNSetting = typename SupportFunctionNew::Settings, typename inSetting>
	static SupportFunctionNewT<Number, Converter<Number>, SFNSetting> toSupportFunctionNew( const BoxT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename SFNSetting = typename SupportFunctionNew::Settings, typename inSetting>
	static SupportFunctionNewT<Number, Converter<Number>, SFNSetting> toSupportFunctionNew( const ConstraintSetT<Number, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename SFNSetting = typename SupportFunctionNew::Settings>
	static SupportFunctionNewT<Number, Converter<Number>, SFNSetting> toSupportFunctionNew( const Ellipsoid& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename SFNSetting = typename SupportFunctionNew::Settings, typename inSetting>
	static SupportFunctionNewT<Number, Converter<Number>, SFNSetting> toSupportFunctionNew( const HPolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename SFNSetting = typename SupportFunctionNew::Settings, typename inSetting>
	static SupportFunctionNewT<Number, Converter<Number>, SFNSetting> toSupportFunctionNew( const VPolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
#ifdef HYPRO_USE_PPL
	template <typename SFNSetting = typename SupportFunctionNew::Settings, typename inSetting>
	static SupportFunctionNewT<Number, Converter<Number>, SFNSetting> toSupportFunctionNew( const PolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
#endif
	template <typename SFNSetting = typename SupportFunctionNew::Settings, typename inSetting>
	static SupportFunctionNewT<Number, Converter<Number>, SFNSetting> toSupportFunctionNew( const SupportFunctionT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename SFNSetting = typename SupportFunctionNew::Settings, typename inSetting>
	static SupportFunctionNewT<Number, Converter<Number>, SFNSetting> toSupportFunctionNew( const ZonotopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename SFNSetting = typename SupportFunctionNew::Settings, typename inSetting>
	static SupportFunctionNewT<Number, Converter<Number>, SFNSetting> toSupportFunctionNew( const DifferenceBoundsT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename SFNSetting = typename SupportFunctionNew::Settings, typename inSetting>
	static SupportFunctionNewT<Number, Converter<Number>, SFNSetting> toSupportFunctionNew( const CarlPolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );
	template <typename SFNSetting = typename SupportFunctionNew::Settings, typename inSetting>
	static SupportFunctionNewT<Number, Converter<Number>, SFNSetting> toSupportFunctionNew( const SupportFunctionNewT<Number, Converter<Number>, inSetting>& source, const CONV_MODE = CONV_MODE::EXACT );

	/* END Conversion (do not remove this comment!) */
};

}  // namespace hypro

#include "typedefs.h"
//#include "converterToOrthoplex.tpp"
#include "converterToBox.tpp"
#include "converterToCarlPolytope.tpp"
#include "converterToConstraintSet.tpp"
#include "converterToHPolytope.tpp"
#include "converterToStarset.tpp"
#include "converterToSupportFunction.tpp"
#include "converterToTemplatePolyhedron.tpp"
#include "converterToVPolytope.tpp"
#include "converterToZonotope.tpp"
#include "typedefs.h"
#ifdef HYPRO_USE_PPL
#include "converterToPolytope.tpp"
#endif
#include "conversionHelper.h"
#include "converterToDifferenceBounds.tpp"
#include "converterToSupportFunctionNew.tpp"
