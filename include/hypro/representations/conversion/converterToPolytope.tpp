/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * Specialization of the converter to convert any representation into PPL polytopes.
 *
 * @file converterToPolytope.tpp
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @author Phillip Tse
 */

#include "Converter.h"

#ifndef INCL_FROM_CONVERTERHEADER
static_assert( false, "This file may only be included indirectly by Converter.h" );
#endif

namespace hypro {

// Conversion from ppl poly to ppl poly
    template<typename Number>
    template<typename PolytopeSetting, typename inSetting>
    PolytopeT <Number, Converter<Number>, PolytopeSetting>
    Converter<Number>::toPolytope(const PolytopeT <Number, Converter<Number>, inSetting> &source, const CONV_MODE) {
        return source;
    }

// Conversion from box to ppl poly
    template<typename Number>
    template<typename PolytopeSetting, typename inSetting>
    PolytopeT <Number, Converter<Number>, PolytopeSetting>
    Converter<Number>::toPolytope(const BoxT<Number, Converter<Number>, inSetting> &source, const CONV_MODE) {
        return PolytopeT<Number, Converter<Number>, PolytopeSetting>(source.matrix(), source.vector());
    }

// Conversion from constraintSet to ppl poly
    template<typename Number>
    template<typename PolytopeSetting, typename inSetting>
    PolytopeT <Number, Converter<Number>, PolytopeSetting>
    Converter<Number>::toPolytope(const ConstraintSetT<Number, inSetting> &source, const CONV_MODE) {
        return PolytopeT<Number, Converter<Number>, PolytopeSetting>(source.matrix(), source.vector());
    }

// Conversion from difference bounds to ppl poly
    template<typename Number>
    template<typename PolytopeSetting, typename inSetting>
    PolytopeT <Number, Converter<Number>, PolytopeSetting>
    Converter<Number>::toPolytope(const DifferenceBoundsT<Number, Converter<Number>, inSetting> &source,
                                  const CONV_MODE) {
        return toPolytope(toHPolytope(source));
    }

// Conversion from ellipsoid to ppl poly
    template<typename Number>
    template<typename PolytopeSetting>
    PolytopeT <Number, Converter<Number>, PolytopeSetting>
    Converter<Number>::toPolytope(const Ellipsoid &source, const CONV_MODE) {
        Converter<Number>::HPolytope tmp = Converter<Number>::toHPolytope(source);
        return PolytopeT<Number, Converter<Number>, PolytopeSetting>(tmp.matrix(), tmp.vector());
    }

// Conversion from hpoly to ppl poly
    template<typename Number>
    template<typename PolytopeSetting, typename inSetting>
    PolytopeT <Number, Converter<Number>, PolytopeSetting>
    Converter<Number>::toPolytope(const HPolytopeT<Number, Converter<Number>, inSetting> &source, const CONV_MODE) {
        return PolytopeT<Number, Converter<Number>, PolytopeSetting>(source.matrix(), source.vector());
    }

// Conversion from vpoly to ppl poly
    template<typename Number>
    template<typename PolytopeSetting, typename inSetting>
    PolytopeT <Number, Converter<Number>, PolytopeSetting>
    Converter<Number>::toPolytope(const VPolytopeT<Number, Converter<Number>, inSetting> &source, const CONV_MODE) {
        return PolytopeT<Number, Converter<Number>, PolytopeSetting>(source.vertices());
    }

// Conversion from supportfunction to ppl poly
    template<typename Number>
    template<typename PolytopeSetting, typename inSetting>
    PolytopeT <Number, Converter<Number>, PolytopeSetting>
    Converter<Number>::toPolytope(const SupportFunctionT<Number, Converter<Number>, inSetting> &source, const CONV_MODE,
                                  std::size_t numberOfDirections) {
        // First convert to HPolytope, afterwards to ppl Polytope
        Converter<Number>::HPolytope tmp = Converter<Number>::toHPolytope(source, std::vector<vector_t<Number>>(),
                                                                          CONV_MODE::EXACT, numberOfDirections);
        return PolytopeT<Number, Converter<Number>, PolytopeSetting>(tmp.matrix(), tmp.vector());
    }

// Conversion from zonotopoe to ppl poly
    template<typename Number>
    template<typename PolytopeSetting, typename inSetting>
    PolytopeT <Number, Converter<Number>, PolytopeSetting>
    Converter<Number>::toPolytope(const ZonotopeT<Number, Converter<Number>, inSetting> &source, const CONV_MODE) {
        return PolytopeT<Number, Converter<Number>, PolytopeSetting>(source.vertices());
    }

// Conversion from carlpoly to ppl poly
    template<typename Number>
    template<typename PolytopeSetting, typename inSetting>
    PolytopeT <Number, Converter<Number>, PolytopeSetting>
    Converter<Number>::toPolytope(const CarlPolytopeT<Number, Converter<Number>, inSetting> &source, const CONV_MODE) {
        return PolytopeT<Number, Converter<Number>, PolytopeSetting>(source.matrix(), source.vector());
    }

    template<typename Number>
    template<typename PolytopeSetting, typename inSetting>
    PolytopeT <Number, Converter<Number>, PolytopeSetting>
    Converter<Number>::toPolytope(const TemplatePolyhedronT<Number, Converter<Number>, inSetting> &source,
                                  const CONV_MODE) {
        return PolytopeT<Number, Converter<Number>, PolytopeSetting>(source.matrix(), source.vector());
    }

// template<typename Number>
// template<typename PolytopeSetting, typename inSetting>
// PolytopeT<Number,Converter<Number>,PolytopeSetting> Converter<Number>::toPolytope( const OrthoplexT<Number,Converter<Number>,inSetting>& source, const CONV_MODE ) {
//	return PolytopeT<Number,Converter<Number>,PolytopeSetting>();
// }

// Conversion from SFN to ppl poly
    template<typename Number>
    template<typename PolytopeSetting, typename inSetting>
    PolytopeT <Number, Converter, PolytopeSetting>
    Converter<Number>::toPolytope(const SupportFunctionNewT<Number, Converter<Number>, inSetting> &source,
                                  const CONV_MODE) {
        // First convert to HPolytope, afterwards to ppl Polytope
        Converter<Number>::HPolytope tmp = Converter<Number>::toHPolytope(source, std::vector<vector_t<Number>>(),
                                                                          CONV_MODE::EXACT, numberOfDirections);
        return PolytopeT<Number, Converter, PolytopeSetting>(tmp.matrix(), tmp.vector());
    }

    // namespace hypro

    template<typename Number>
    template<typename PolytopeSetting, typename inSetting>
    PolytopeT <Number, Converter<Number>, PolytopeSetting>
    Converter<Number>::toPolytope(const StarsetT<Number, Converter<Number>, inSetting> &source, const CONV_MODE) {
        return PolytopeT<Number, Converter<Number>, PolytopeSetting>();
    }
}
