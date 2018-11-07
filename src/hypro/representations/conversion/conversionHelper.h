#pragma once

namespace hypro
{

template<typename Number, typename OutSettings, typename In>
void convert(BoxT<Number,Converter<Number>,OutSettings>& out, const In& in) {
    out = Converter<Number>::template toBox<OutSettings>(in);
}

template<typename Number, typename OutSettings, typename In>
void convert(ConstraintSetT<Number,Converter<Number>,OutSettings>& out, const In& in) {
    out = Converter<Number>::template toConstraintSet<OutSettings>(in);
}

template<typename Number, typename OutSettings, typename In>
void convert(HPolytopeT<Number,Converter<Number>,OutSettings>& out, const In& in) {
    out = Converter<Number>::template toHPolytope<OutSettings>(in);
}

template<typename Number, typename OutSettings, typename In>
void convert(VPolytopeT<Number,Converter<Number>,OutSettings>& out, const In& in) {
    out = Converter<Number>::template toVPolytope<OutSettings>(in);
}

template<typename Number, typename OutSettings, typename In>
void convert(DifferenceBoundsT<Number,Converter<Number>,OutSettings>& out, const In& in) {
    out = Converter<Number>::template toDifferenceBounds<OutSettings>(in);
}

template<typename Number, typename OutSettings, typename In>
void convert(SupportFunctionT<Number,Converter<Number>,OutSettings>& out, const In& in) {
    out = Converter<Number>::template toSupportFunction<OutSettings>(in);
}

template<typename Number, typename OutSettings, typename In>
void convert(ZonotopeT<Number,Converter<Number>,OutSettings>& out, const In& in) {
    out = Converter<Number>::template toZonotope<OutSettings>(in);
}

} // hypro
