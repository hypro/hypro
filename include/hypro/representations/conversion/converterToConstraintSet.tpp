
/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "Converter.h"

#ifndef INCL_FROM_CONVERTERHEADER
static_assert( false, "This file may only be included indirectly by Converter.h" );
#endif

namespace hypro {

    template<typename Number>
    template<typename CSSetting, typename inSetting>
    ConstraintSetT<Number, CSSetting>
    Converter<Number>::toConstraintSet(const BoxT<Number, Converter<Number>, inSetting> &_source, const CONV_MODE) {
        return ConstraintSetT<Number, CSSetting>(_source.matrix(), _source.vector());
    }

    template<typename Number>
    template<typename CSSetting, typename inSetting>
    ConstraintSetT<Number, CSSetting>
    Converter<Number>::toConstraintSet(const CarlPolytopeT<Number, Converter<Number>, inSetting> &_source,
                                       const CONV_MODE) {
        return ConstraintSetT<Number, CSSetting>(_source.matrix(), _source.vector());
    }

    template<typename Number>
    template<typename CSSetting, typename inSetting>
    ConstraintSetT<Number, CSSetting>
    Converter<Number>::toConstraintSet(const ConstraintSetT<Number, inSetting> &_source, const CONV_MODE) {
        return _source;
    }

    template<typename Number>
    template<typename CSSetting>
    ConstraintSetT<Number, CSSetting> Converter<Number>::toConstraintSet(const Ellipsoid &_source, const CONV_MODE) {
        return ConstraintSetT<Number, CSSetting>(_source.matrix(), _source.vector());
    }

    template<typename Number>
    template<typename CSSetting, typename inSetting>
    ConstraintSetT<Number, CSSetting>
    Converter<Number>::toConstraintSet(const SupportFunctionT<Number, Converter<Number>, inSetting> &_source,
                                       const CONV_MODE) {
        return ConstraintSetT<Number, CSSetting>(_source.matrix(), _source.vector());
    }

    template<typename Number>
    template<typename CSSetting, typename inSetting>
    ConstraintSetT<Number, CSSetting>
    Converter<Number>::toConstraintSet(const VPolytopeT<Number, Converter<Number>, inSetting> &_source,
                                       const CONV_MODE) {
        auto tmp = toHPolytope(_source);
        return ConstraintSetT<Number, CSSetting>(tmp.matrix(), tmp.vector());
    }

    template<typename Number>
    template<typename CSSetting, typename inSetting>
    ConstraintSetT<Number, CSSetting>
    Converter<Number>::toConstraintSet(const HPolytopeT<Number, Converter<Number>, inSetting> &_source,
                                       const CONV_MODE) {
        return ConstraintSetT<Number, CSSetting>(_source.matrix(), _source.vector());
    }

#ifdef HYPRO_USE_PPL
    template <typename Number>
    template <typename CSSetting, typename inSetting>
    ConstraintSetT<Number, CSSetting> Converter<Number>::toConstraintSet( const PolytopeT<Number, Converter<Number>, inSetting>& _source, const CONV_MODE ) {
        auto tmp = toHPolytope( _source );
        return ConstraintSetT<Number, CSSetting>( tmp.matrix(), tmp.vector() );
    }
#endif

    template<typename Number>
    template<typename CSSetting, typename inSetting>
    ConstraintSetT<Number, CSSetting>
    Converter<Number>::toConstraintSet(const ZonotopeT<Number, Converter<Number>, inSetting> &, const CONV_MODE) {
        assert(false && "NotImplemented.");
        return ConstraintSetT<Number, CSSetting>();
    }

    template<typename Number>
    template<typename CSSetting, typename inSetting>
    ConstraintSetT<Number, CSSetting>
    Converter<Number>::toConstraintSet(const DifferenceBoundsT<Number, Converter<Number>, inSetting> &_source,
                                       const CONV_MODE mode) {
        return toConstraintSet(toHPolytope(_source, mode));
    }

    template<typename Number>
    template<typename ConstraintSetSetting, typename inSetting>
    ConstraintSetT<Number, ConstraintSetSetting>
    Converter<Number>::toConstraintSet(const TemplatePolyhedronT<Number, Converter<Number>, inSetting> &source,
                                       const CONV_MODE) {
        return ConstraintSetT<Number, ConstraintSetSetting>(source.matrix(), source.vector());
    }

// template<typename Number>
// template<typename ConstraintSetSetting, typename inSetting>
// ConstraintSetT<Number,ConstraintSetSetting> Converter<Number>::toConstraintSet( const OrthoplexT<Number,Converter<Number>,inSetting>& source, const CONV_MODE ) {
//	return ConstraintSetT<Number,ConstraintSetSetting>();
// }

    template<typename Number>
    template<typename CSSetting, typename inSetting>
    ConstraintSetT<Number, CSSetting>
    Converter<Number>::toConstraintSet(const SupportFunctionNewT<Number, Converter<Number>, inSetting> &_source,
                                       const CONV_MODE) {
        return ConstraintSetT<Number, CSSetting>(_source.matrix(), _source.vector());
    }

    // namespace hypro

    template<typename Number>
    template<typename ConstraintSetSetting, typename inSetting>
    ConstraintSetT<Number, ConstraintSetSetting>
    Converter<Number>::toConstraintSet(const StarsetT<Number, Converter<Number>, inSetting> &source, const CONV_MODE) {
        return ConstraintSetT<Number, ConstraintSetSetting>();
    }
}
