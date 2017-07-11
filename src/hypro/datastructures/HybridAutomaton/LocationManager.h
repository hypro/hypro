/**
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 *
 */

#pragma once

#include "Location.h"
#include <carl/util/Singleton.h>
//#include <hypro/types.h>
#include "../../types.h"

namespace hypro
{
template<typename Number>
class LocationManager : public carl::Singleton<LocationManager>
{
    friend carl::Singleton<LocationManager>;

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
    ~LocationManager() {}
    Location<Number>* create();
    Location<Number>* create(const Location<Number>* _loc);
    Location<Number>* create(const hypro::matrix_t<Number> _mat);
    Location<Number>* create(const hypro::matrix_t<Number> _mat, const typename Location::transitionSet _trans, const Condition<Number>& _inv);
    Location<Number>* create(const hypro::matrix_t<Number> _mat, const typename Location::transitionSet _trans, const Condition<Number>& _inv,
                     const hypro::matrix_t<Number> _extInputMat);

    unsigned id(Location<Number>* _loc) const;
    Location<Number>* location(unsigned _id) const;
    Location<Number>* location(std::string name) const;
};

}  // namespace hydra

#include "LocationManager.tpp"