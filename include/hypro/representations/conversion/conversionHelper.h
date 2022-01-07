#pragma once

namespace hypro {

template <typename Number, typename OutSettings, typename In>
void convert( const In& in, BoxT<Number, Converter<Number>, OutSettings>& out ) {
	out = Converter<Number>::template toBox<OutSettings>( in );
}

template <typename Number, typename OutSettings, typename In>
void convert( const In& in, CarlPolytopeT<Number, Converter<Number>, OutSettings>& out ) {
	out = Converter<Number>::template toCarlPolytope<OutSettings>( in );
}

template <typename Number, typename OutSettings, typename In>
void convert( const In& in, ConstraintSetT<Number, OutSettings>& out ) {
	out = Converter<Number>::template toConstraintSet<OutSettings>( in );
}

template <typename Number, typename OutSettings, typename In>
void convert( const In& in, DifferenceBoundsT<Number, Converter<Number>, OutSettings>& out ) {
	out = Converter<Number>::template toDifferenceBounds<OutSettings>( in );
}

template <typename Number, typename OutSettings, typename In>
void convert( const In& in, HPolytopeT<Number, Converter<Number>, OutSettings>& out ) {
	out = Converter<Number>::template toHPolytope<OutSettings>( in );
}

template <typename Number, typename OutSettings, typename In>
void convert( const In& in, SupportFunctionT<Number, Converter<Number>, OutSettings>& out ) {
	out = Converter<Number>::template toSupportFunction<OutSettings>( in );
}

template <typename Number, typename OutSettings, typename In>
void convert( const In& in, VPolytopeT<Number, Converter<Number>, OutSettings>& out ) {
	out = Converter<Number>::template toVPolytope<OutSettings>( in );
}

template <typename Number, typename OutSettings, typename In>
void convert( const In& in, ZonotopeT<Number, Converter<Number>, OutSettings>& out ) {
	out = Converter<Number>::template toZonotope<OutSettings>( in );
}

template <typename Number, typename OutSettings, typename In>
void convert( const In& in, TemplatePolyhedronT<Number, Converter<Number>, OutSettings>& out ) {
	out = Converter<Number>::template toTemplatePolyhedron<OutSettings>( in );
}

// template<typename Number, typename OutSettings, typename In>
// void convert(const In& in, OrthoplexT<Number,Converter<Number>,OutSettings>& out) {
//	out = Converter<Number>::template toOrthoplex<OutSettings>(in);
// }

template <typename Number, typename OutSettings, typename In>
void convert( const In& in, SupportFunctionNewT<Number, Converter<Number>, OutSettings>& out ) {
	out = Converter<Number>::template toSupportFunctionNew<OutSettings>( in );
}

#ifdef HYPRO_USE_PPL
template <typename Number, typename OutSettings, typename In>
void convert( const In& in, PolytopeT<Number, Converter<Number>, OutSettings>& out ) {
	out = Converter<Number>::template toPolytope<OutSettings>( in );
}
#endif

 
template<typename Number, typename OutSettings, typename In>
void convert(const In& in, StarsetT<Number,Converter<Number>,OutSettings>& out) {
	out = Converter<Number>::template toStarset<OutSettings>(in); 
}

}  // namespace hypro
