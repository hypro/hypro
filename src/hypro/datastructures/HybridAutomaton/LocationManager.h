/**
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 */

#pragma once

#include "Location.h"
#include <carl/util/Singleton.h>
#include "../../types.h"

namespace hypro
{
template<typename Number>
class LocationManager : public carl::Singleton<LocationManager<Number>>
{
    friend carl::Singleton<LocationManager<Number>>;

  private:
    std::map<unsigned, Location<Number>*> mLocations;
    std::map<Location<Number>*, unsigned> mIds;
    unsigned mId;

  protected:
    /**
     * Default constructor and destructor
     */
    LocationManager() : mId(0) {}
  public:
    //LocationManager() : mId(0) {}
    ~LocationManager() {
      while(!mLocations.empty()) {
        Location<Number>* toDelete = mLocations.begin()->second;
        if(toDelete != nullptr){
          mLocations.erase(mLocations.begin());
          delete toDelete;
        }
      }
    }

    [[deprecated("Use now public Location constructors instead")]]
    Location<Number>* create();
    [[deprecated("Use now public Location constructors instead")]]
    Location<Number>* create(const Location<Number>* _loc);
    [[deprecated("Use now public Location constructors instead")]]
    Location<Number>* create(const matrix_t<Number> _mat);
    [[deprecated("Use now public Location constructors instead")]]
    Location<Number>* create(const matrix_t<Number> _mat, const typename Location<Number>::transitionSet _trans, const Condition<Number>& _inv);
    [[deprecated("Use now public Location constructors instead")]]
    Location<Number>* create(const matrix_t<Number> _mat, const typename Location<Number>::transitionSet _trans, const Condition<Number>& _inv,
                     const matrix_t<Number> _extInputMat);

    [[deprecated("The id of a location is no longer used for identification, use hash() for locations.")]]
    unsigned id(Location<Number>* _loc) const;
    [[deprecated("The id of a location is no longer used for identification, use hash() for locations.")]]
    Location<Number>* location(unsigned _id) const;
    Location<Number>* location(std::string name) const;

    void erase(unsigned _id);
};

}  // namespace hydra

#include "LocationManager.tpp"
