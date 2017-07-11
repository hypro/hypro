/**
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 *
 */

#pragma once

#include "Location.h"
#include <carl/util/Singleton.h>
#include <hypro/types.h>

namespace hydra
{
class LocationManager : public carl::Singleton<LocationManager>
{
    friend carl::Singleton<LocationManager>;

  private:
    std::map<unsigned, Location*> mLocations;
    std::map<Location*, unsigned> mIds;
    unsigned mId;

  protected:
    /**
     * Default constructor and destructor
     */
    LocationManager() : mId(0) {}
  public:
    ~LocationManager() {}
    Location* create();
    Location* create(const Location* _loc);
    Location* create(const hypro::matrix_t<Number> _mat);
    Location* create(const hypro::matrix_t<Number> _mat, const typename Location::transitionSet _trans, const Condition& _inv);
    Location* create(const hypro::matrix_t<Number> _mat, const typename Location::transitionSet _trans, const Condition& _inv,
                     const hypro::matrix_t<Number> _extInputMat);

    unsigned id(Location* _loc) const;
    Location* location(unsigned _id) const;
    Location* location(std::string name) const;
};

}  // namespace hydra
