#include "LocationManager.h"

namespace hypro
{
template<typename Number>
Location *LocationManager<Number>::create()
{
    Location *loc = new Location(mId++);
    mLocations[mId - 1] = loc;
    mIds[loc] = mId - 1;
    return loc;
}

template<typename Number>
Location *LocationManager<Number>::create(const Location *_loc)
{
    Location *loc = new Location(mId++, *_loc);
    mLocations[mId - 1] = loc;
    mIds[loc] = mId - 1;
    return loc;
}

template<typename Number>
Location *LocationManager<Number>::create(const hypro::matrix_t<Number> _mat)
{
    Location *loc = new Location(mId++, _mat);
    mLocations[mId - 1] = loc;
    mIds[loc] = mId - 1;
    return loc;
}

template<typename Number>
Location *LocationManager<Number>::create(const hypro::matrix_t<Number> _mat, const typename Location::transitionSet _trans, const Condition& _inv)
{
    Location *loc = new Location(mId++, _mat, _trans, _inv);
    mLocations[mId - 1] = loc;
    mIds[loc] = mId - 1;
    return loc;
}

template<typename Number>
Location *LocationManager<Number>::create(const hypro::matrix_t<Number> _mat, const typename Location::transitionSet _trans, const Condition& _inv,
                                  const hypro::matrix_t<Number> _extInputMat)
{
    Location *loc = new Location(mId++, _mat, _trans, _inv, _extInputMat);
    mLocations[mId - 1] = loc;
    mIds[loc] = mId - 1;
    return loc;
}

template<typename Number>
unsigned LocationManager<Number>::id(Location *_loc) const
{
    assert(mIds.find(_loc) != mIds.end());
    return mIds.at(_loc);
}

template<typename Number>
Location *LocationManager<Number>::location(unsigned _id) const
{
    assert(mLocations.find(_id) != mLocations.end());
    return mLocations.at(_id);
}

template<typename Number>
Location *LocationManager<Number>::location(std::string name) const
{
	for(auto locIt = mLocations.begin(); locIt != mLocations.end(); ++ locIt) {
		if((*locIt).second->getName() == name) {
			return (*locIt).second;
		}
	}
    return nullptr;
}

}  // namespace hydra
