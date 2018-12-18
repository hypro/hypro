#pragma once

namespace hypro
{
/*
template<typename Number, typename OutSettings, typename In>
void convert(BoxT<Number,Converter<Number>,OutSettings>& out, const In& in) {
    out = Converter<Number>::template toBox<OutSettings>(in);
}
*/

template<typename Number, typename OutSettings, typename In>
void convert(const In& in, BoxT<Number,Converter<Number>,OutSettings>& out) {
    out = Converter<Number>::template toBox<OutSettings>(in);
}

template<typename Number, typename OutSettings, typename In>
void convert(const In& in, CarlPolytopeT<Number,Converter<Number>,OutSettings>& out) {
    out = Converter<Number>::template toCarlPolytope<OutSettings>(in);
}

template<typename Number, typename OutSettings, typename In>
void convert(const In& in, ConstraintSetT<Number,OutSettings>& out) {
    out = Converter<Number>::template toConstraintSet<OutSettings>(in);
}

template<typename Number, typename OutSettings, typename In>
void convert(const In& in, DifferenceBoundsT<Number,Converter<Number>,OutSettings>& out) {
    out = Converter<Number>::template toDifferenceBounds<OutSettings>(in);
}

template<typename Number, typename OutSettings, typename In>
void convert(const In& in, HPolytopeT<Number,Converter<Number>,OutSettings>& out) {
    out = Converter<Number>::template toHPolytope<OutSettings>(in);
}

template<typename Number, typename OutSettings, typename In>
void convert(const In& in, SupportFunctionT<Number,Converter<Number>,OutSettings>& out) {
    out = Converter<Number>::template toSupportFunction<OutSettings>(in);
}

template<typename Number, typename OutSettings, typename In>
void convert(const In& in, VPolytopeT<Number,Converter<Number>,OutSettings>& out) {
    out = Converter<Number>::template toVPolytope<OutSettings>(in);
}

template<typename Number, typename OutSettings, typename In>
void convert(const In& in, ZonotopeT<Number,Converter<Number>,OutSettings>& out) {
    out = Converter<Number>::template toZonotope<OutSettings>(in);
}


} // hypro
