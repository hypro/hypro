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
class [[deprecated("Use now public Location constructors instead")]] LocationManager : public carl::Singleton<LocationManager<Number>>
//class LocationManager : public carl::Singleton<LocationManager<Number>>
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
        //for(auto tupel : mLocations){
        //  std::cout << "name of loc with id " << tupel.first << " is: " << tupel.second->getName() << " with hash " << tupel.second->getHash() << std::endl;
        //}
        Location<Number>* toDelete = mLocations.begin()->second;
        if(toDelete != nullptr){
          mLocations.erase(mLocations.begin());
          
          //std::cout << "Now deleting " << toDelete->getName() << " with id " << toDelete->getId() << " and hash " << toDelete->getHash() << std::endl;
          //size_t deleteCount = mLocations.erase(toDelete->getId());
          //std::cout << "Deleted " << deleteCount << " times\n";
          delete toDelete;  
        }
      }
    }

    Location<Number>* create();
    Location<Number>* create(const Location<Number>* _loc);
    Location<Number>* create(const matrix_t<Number> _mat);
    Location<Number>* create(const matrix_t<Number> _mat, const typename Location<Number>::transitionSet _trans, const Condition<Number>& _inv);
    Location<Number>* create(const matrix_t<Number> _mat, const typename Location<Number>::transitionSet _trans, const Condition<Number>& _inv,
                     const matrix_t<Number> _extInputMat);

    unsigned id(Location<Number>* _loc) const;
    Location<Number>* location(unsigned _id) const;
    Location<Number>* location(std::string name) const;

    void erase(unsigned _id);
};

}  // namespace hydra

#include "LocationManager.tpp"
