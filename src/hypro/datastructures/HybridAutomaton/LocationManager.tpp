#include "LocationManager.h"

namespace hypro
{
template<typename Number>
Location<Number> *LocationManager<Number>::create()
{
    Location<Number> *loc = new Location<Number>(mId++);
    //mLocations[mId - 1] = loc;
    //mIds[loc] = mId - 1;
    mLocations.insert(std::make_pair(mId-1,loc));
    mIds.insert(std::make_pair(loc,mId-1));
    return loc;
}

template<typename Number>
Location<Number> *LocationManager<Number>::create(const Location<Number> *_loc)
{
    Location<Number> *loc = new Location<Number>(mId++, *_loc);
    std::cout << "locMan kreiert loc " << mId << std::endl; 
    //mLocations[mId - 1] = loc;
    //mIds[loc] = mId - 1;
    mLocations.insert(std::make_pair(mId-1,loc));
    mIds.insert(std::make_pair(loc,mId-1));
    return loc;
}

template<typename Number>
Location<Number> *LocationManager<Number>::create(const std::unique_ptr<Location<Number>>& _loc)
{
    //Copying: When creating a new location via copying, the location will get the same ide as the original loc
    std::unique_ptr<Location<Number>> loc(Location<Number>(mId, *_loc));
    std::cout << "locMan kreiert loc " << mId << std::endl; 
    //mLocations.insert(std::make_pair(mId, loc));
    //mIds.insert(std::make_pair(loc,mId));
    mLocations.insert(std::make_pair(mId-1,loc));
    mIds.insert(std::make_pair(loc,mId-1));
    return loc.get();
}

template<typename Number>
Location<Number> *LocationManager<Number>::create(const matrix_t<Number> _mat)
{
    Location<Number> *loc = new Location<Number>(mId++, _mat);
    //mLocations[mId - 1] = loc;
    //mIds[loc] = mId - 1;
    mLocations.insert(std::make_pair(mId-1,loc));
    mIds.insert(std::make_pair(loc,mId-1));
    return loc;
}

template<typename Number>
Location<Number> *LocationManager<Number>::create(const matrix_t<Number> _mat, const typename Location<Number>::transitionSet _trans, const Condition<Number>& _inv)
{
    Location<Number> *loc = new Location<Number>(mId++, _mat, _trans, _inv);
    //mLocations[mId - 1] = loc;
    //mIds[loc] = mId - 1;
    mLocations.insert(std::make_pair(mId-1,loc));
    mIds.insert(std::make_pair(loc,mId-1));
    return loc;
}

template<typename Number>
Location<Number> *LocationManager<Number>::create(const matrix_t<Number> _mat, const typename Location<Number>::transitionSet _trans, const Condition<Number>& _inv,
                                  const matrix_t<Number> _extInputMat)
{
    Location<Number> *loc = new Location<Number>(mId++, _mat, _trans, _inv, _extInputMat);
    //mLocations[mId - 1] = loc;
    //mIds[loc] = mId - 1;
    mLocations.insert(std::make_pair(mId-1,loc));
    mIds.insert(std::make_pair(loc,mId-1));
    return loc;
}

//Returns the id of the given location.
//If _loc has been inserted several times, all copies have the same id 
template<typename Number>
unsigned LocationManager<Number>::id(Location<Number>* _loc) const
{
    assert(mIds.find(_loc) != mIds.end());
    //return mIds.at(_loc);
    return (*(mIds.find(loc))).first;

}

//Returns the last inserted location with the given id
template<typename Number>
Location<Number>* LocationManager<Number>::location(unsigned _id) const
{
    assert(mLocations.find(_id) != mLocations.end());
    std::pair<auto,auto> allLocsWithGivenId = mLocations.equal_range(_id);
    //All locations found with same id are equal, but the least inserted one is the one 
    //that has been inserted last. Thus we select this version. 
    assert(allLocsWithGivenId.first != mLocations.end());
    return *(allLocsWithGivenId.second - 1);
    //return mLocations.at(_id);
}

template<typename Number>
std::vector<Location<Number>*> LocationManager<Number>::location(std::string name) const
{
    std::vector<Location<Number>*> allLocsWithGivenName;
	for(auto locIt = mLocations.begin(); locIt != mLocations.end(); ++ locIt) {
		if((*locIt).second->getName() == name) {
	       	return (*locIt).second;
            //allLocsWithGivenName.insert(*locIt->second);
		}
	}
    return nullptr;
    //return allLocsWithGivenName;
}

//Returns the last inserted location with the given id
template<typename Number>
std::vector<Location<Number>*> LocationManager<Number>::locations(unsigned _id) const
{
    assert(mLocations.find(_id) != mLocations.end());
    std::pair<auto,auto> allLocsWithGivenId = mLocations.equal_range(_id);
    //All locations found with same id are equal, but the least inserted one is the one 
    //that has been inserted last. Thus we select this version. 
    assert(allLocsWithGivenId.first != mLocations.end());
    return allLocsWithGivenId.second;
    //return mLocations.at(_id);
}

template<typename Number>
std::vector<Location<Number>*> LocationManager<Number>::locations(std::string name) const
{
    std::vector<Location<Number>*> allLocsWithGivenName;
    for(auto locIt = mLocations.begin(); locIt != mLocations.end(); ++ locIt) {
        if((*locIt).second->getName() == name) {
            //return (*locIt).second;
            allLocsWithGivenName.insert(*locIt->second);
        }
    }
    //return nullptr;
    return allLocsWithGivenName;
}

template<typename Number>
void LocationManager<Number>::erase(unsigned _id) {
    auto locationMapPtr = mLocations.find(_id);
    if(locationMapPtr != mLocations.end()) {
        TRACE("hypro.locationManager", "Erase location " << _id);
        mLocations.erase(locationMapPtr);
    }
}

}  // namespace hypro
