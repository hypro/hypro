/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

namespace hypro {

    template<typename Number, typename OutSettings, typename In>
    void convert(const In &in, BoxT<Number, Converter<Number>, OutSettings> &out) {
        out = Converter<Number>::template toBox<OutSettings>(in);
    }

    template<typename Number, typename OutSettings, typename In>
    void convert(const In &in, CarlPolytopeT<Number, Converter<Number>, OutSettings> &out) {
        out = Converter<Number>::template toCarlPolytope<OutSettings>(in);
    }

    template<typename Number, typename OutSettings, typename In>
    void convert(const In &in, ConstraintSetT<Number, OutSettings> &out) {
        out = Converter<Number>::template toConstraintSet<OutSettings>(in);
    }

    template<typename Number, typename OutSettings, typename In>
    void convert(const In &in, DifferenceBoundsT<Number, Converter<Number>, OutSettings> &out) {
        out = Converter<Number>::template toDifferenceBounds<OutSettings>(in);
    }

    template<typename Number, typename OutSettings, typename In>
    void convert(const In &in, HPolytopeT<Number, Converter<Number>, OutSettings> &out) {
        out = Converter<Number>::template toHPolytope<OutSettings>(in);
    }

    template<typename Number, typename OutSettings, typename In>
    void convert(const In &in, SupportFunctionT<Number, Converter<Number>, OutSettings> &out) {
        out = Converter<Number>::template toSupportFunction<OutSettings>(in);
    }

    template<typename Number, typename OutSettings, typename In>
    void convert(const In &in, VPolytopeT<Number, Converter<Number>, OutSettings> &out) {
        out = Converter<Number>::template toVPolytope<OutSettings>(in);
    }

    template<typename Number, typename OutSettings, typename In>
    void convert(const In &in, ZonotopeT<Number, Converter<Number>, OutSettings> &out) {
        out = Converter<Number>::template toZonotope<OutSettings>(in);
    }

    template<typename Number, typename OutSettings, typename In>
    void convert(const In &in, TemplatePolyhedronT<Number, Converter<Number>, OutSettings> &out) {
        out = Converter<Number>::template toTemplatePolyhedron<OutSettings>(in);
    }

// template<typename Number, typename OutSettings, typename In>
// void convert(const In& in, OrthoplexT<Number,Converter<Number>,OutSettings>& out) {
//	out = Converter<Number>::template toOrthoplex<OutSettings>(in);
// }

    template<typename Number, typename OutSettings, typename In>
    void convert(const In &in, SupportFunctionNewT<Number, Converter<Number>, OutSettings> &out) {
        out = Converter<Number>::template toSupportFunctionNew<OutSettings>(in);
    }

#ifdef HYPRO_USE_PPL
    template <typename Number, typename OutSettings, typename In>
    void convert( const In& in, PolytopeT<Number, Converter<Number>, OutSettings>& out ) {
        out = Converter<Number>::template toPolytope<OutSettings>( in );
    }
#endif


    template<typename Number, typename OutSettings, typename In>
    void convert(const In &in, StarsetT<Number, Converter<Number>, OutSettings> &out) {
        out = Converter<Number>::template toStarset<OutSettings>(in);
    }

}  // namespace hypro
