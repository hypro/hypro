/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef INCL_FROM_CONVERTERHEADER
static_assert(false, "This file may only be included indirectly by Converter.h");
#endif

namespace hypro {

    template<typename Number>
    template<typename StarsetSetting, typename inSetting>
    StarsetT<Number, Converter<Number>, StarsetSetting>
    Converter<Number>::toStarset(const StarsetT<Number, Converter<Number>, inSetting> &_source, const CONV_MODE) {
        return _source;
    }

    template<typename Number>
    template<typename StarsetSetting, typename inSetting>
    StarsetT<Number, Converter<Number>, StarsetSetting>
    Converter<Number>::toStarset(const TemplatePolyhedronT<Number, Converter<Number>, inSetting> &_source,
                                 const CONV_MODE) {

        return StarsetT<Number, Converter<Number>, StarsetSetting>();

    }

    template<typename Number>
    template<typename StarsetSetting, typename inSetting>
    StarsetT<Number, Converter<Number>, StarsetSetting>
    Converter<Number>::toStarset(const BoxT<Number, Converter<Number>, inSetting> &_source, const CONV_MODE) {
        StarsetT<Number, Converter<Number>, StarsetSetting> ccc = StarsetT<Number, Converter<Number>, StarsetSetting>(
                _source.matrix(), _source.vector());

        return ccc;
    }

    template<typename Number>
    template<typename StarsetSetting, typename inSetting>
    StarsetT<Number, Converter<Number>, StarsetSetting>
    Converter<Number>::toStarset(const CarlPolytopeT<Number, Converter<Number>, inSetting> &_source, const CONV_MODE) {
        return StarsetT<Number, Converter<Number>, StarsetSetting>();
    }

    template<typename Number>
    template<typename StarsetSetting, typename inSetting>
    StarsetT<Number, Converter<Number>, StarsetSetting>
    Converter<Number>::toStarset(const ConstraintSetT<Number, inSetting> &_source, const CONV_MODE) {
        return StarsetT<Number, Converter<Number>, StarsetSetting>();
    }

    template<typename Number>
    template<typename StarsetSetting>
    StarsetT<Number, Converter<Number>, StarsetSetting>
    Converter<Number>::toStarset(const Ellipsoid &_source, const CONV_MODE) {
        return StarsetT<Number, Converter<Number>, StarsetSetting>();
    }

    template<typename Number>
    template<typename StarsetSetting, typename inSetting>
    StarsetT<Number, Converter<Number>, StarsetSetting>
    Converter<Number>::toStarset(const HPolytopeT<Number, Converter<Number>, inSetting> &_source, const CONV_MODE) {
        return StarsetT<Number, Converter<Number>, StarsetSetting>(_source.matrix(), _source.vector());
    }


    template<typename Number>
    template<typename StarsetSetting, typename inSetting>
    StarsetT<Number, Converter<Number>, StarsetSetting>
    Converter<Number>::toStarset(const VPolytopeT<Number, Converter<Number>, inSetting> &_source, const CONV_MODE) {
        return StarsetT<Number, Converter<Number>, StarsetSetting>();
    }

    template<typename Number>
    template<typename StarsetSetting, typename inSetting>
    StarsetT<Number, Converter<Number>, StarsetSetting>
    Converter<Number>::toStarset(const DifferenceBoundsT<Number, Converter<Number>, inSetting> &_source,
                                 const CONV_MODE) {
        return StarsetT<Number, Converter<Number>, StarsetSetting>();
    }

#ifdef HYPRO_USE_PPL
    template<typename Number>
    template<typename StarsetSetting, typename inSetting>
    StarsetT<Number,Converter<Number>,StarsetSetting> Converter<Number>::toStarset( const PolytopeT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
        return StarsetT<Number,Converter<Number>,StarsetSetting>();
    }
#endif

    template<typename Number>
    template<typename StarsetSetting, typename inSetting>
    StarsetT<Number, Converter<Number>, StarsetSetting>
    Converter<Number>::toStarset(const SupportFunctionT<Number, Converter<Number>, inSetting> &_source,
                                 const CONV_MODE) {
        return StarsetT<Number, Converter<Number>, StarsetSetting>();
    }

    template<typename Number>
    template<typename StarsetSetting, typename inSetting>
    StarsetT<Number, Converter<Number>, StarsetSetting>
    Converter<Number>::toStarset(const ZonotopeT<Number, Converter<Number>, inSetting> &_source, const CONV_MODE) {
        return StarsetT<Number, Converter<Number>, StarsetSetting>();
    }

    template<typename Number>
    template<typename StarsetSetting, typename inSetting>
    StarsetT<Number, Converter<Number>, StarsetSetting>
    Converter<Number>::toStarset(const SupportFunctionNewT<Number, Converter<Number>, inSetting> &_source,
                                 const CONV_MODE) {
        return StarsetT<Number, Converter<Number>, StarsetSetting>();
    }

} //namespace hypro
