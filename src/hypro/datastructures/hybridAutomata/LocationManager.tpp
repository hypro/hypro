#include "LocationManager.h"

namespace hypro {
template <typename Number>
Location<Number> *LocationManager<Number>::create() {
	Location<Number> *loc = new Location<Number>( mId++ );
	mLocations[mId - 1] = loc;
	mIds[loc] = mId - 1;
	return loc;
}

template <typename Number>
Location<Number> *LocationManager<Number>::create( const Location<Number> *_loc ) {
	Location<Number> *loc = new Location<Number>( mId++, _loc );
	mLocations[mId - 1] = loc;
	mIds[loc] = mId - 1;
	return loc;
}

template<typename Number>
Location<Number>* LocationManager<Number>::create( const matrix_t<Number> _mat )
{
	Location<Number> *loc = new Location<Number>( mId++, _mat );
	mLocations[mId - 1] = loc;
	mIds[loc] = mId - 1;
	return loc;
}

template <typename Number>
Location<Number> *LocationManager<Number>::create( const matrix_t<Number> _mat,
												   const typename Location<Number>::transitionSet _trans,
												   const struct Location<Number>::Invariant _inv ) {
	Location<Number> *loc = new Location<Number>( mId++, _mat, _trans, _inv );
	mLocations[mId - 1] = loc;
	mIds[loc] = mId - 1;
	return loc;
}

template <typename Number>
Location<Number> *LocationManager<Number>::create( const matrix_t<Number> _mat,
												   const typename Location<Number>::transitionSet _trans,
												   const struct Location<Number>::Invariant _inv,
												   const matrix_t<Number> _extInputMat ) {
	Location<Number> *loc = new Location<Number>( mId++, _mat, _trans, _inv, _extInputMat );
	mLocations[mId - 1] = loc;
	mIds[loc] = mId - 1;
	return loc;
}

template <typename Number>
unsigned LocationManager<Number>::id(const Location<Number>* _loc) const {
	assert(mIds.find(_loc) != mIds.end());
	return mIds.at(_loc);
}

template<typename Number>
Location<Number>* LocationManager<Number>::location(unsigned _id) const {
	assert(mLocations.find(_id) != mLocations.end());
	return mLocations.at(_id);
}

} // namespace hypro
