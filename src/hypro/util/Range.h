#pragma once

namespace hypro {
template <typename T>
struct Range {
	typename T::const_iterator begin = nullptr;
	typename T::const_iterator end = nullptr;

	Range( typename T::const_iterator b, typename T::const_iterator e )
		: begin( b )
		, end( e ) {}

	bool isEmpty() const {
		return begin == end;
	}

	explicit operator T() const {
		return T( begin, end );
	}
};

template <typename T>
T toContainer( Range<T>& r ) {
	return T( r );
}

template <typename T>
Range<T> selectFirstConsecutiveRange( const T& in, std::function<bool( typename T::value_type )> cmp ) {
	auto b = in.begin();
	// search for beginnig of range
	while ( b != in.end() && !cmp( *b ) ) {
		++b;
	}
	// if not found, return empty range
	if ( b == in.end() ) {
		return Range<T>( in.end(), in.end() );
	}
	// find end of range
	auto e = b;
	++e;
	while ( e != in.end() && cmp( *e ) ) {
		++e;
	}
	return Range<T>( b, e );
}

}  // namespace hypro
