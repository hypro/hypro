/**
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 *
 */

#pragma once

#include "Location.h"
#include <carl/util/Singleton.h>

namespace hypro {

template <typename Number>
class LocationManager : public carl::Singleton<LocationManager<Number>> {
	friend carl::Singleton<LocationManager>;

  private:
	std::map<unsigned, Location<Number>*> mLocations;
	std::map<Location<Number>*, unsigned> mIds;
	unsigned mId;

  protected:
	/**
	 * Default constructor and destructor
	 */
	LocationManager() : mId( 0 ) {}

  public:
	~LocationManager() {
		mIds.clear();
		for(auto mapIt = mLocations.begin(); mapIt != mLocations.end(); ++mapIt) {
			delete mapIt->second;
		}
		mLocations.clear();
	}

	Location<Number>* create();
	Location<Number>* create( const Location<Number>* _loc );
	Location<Number>* create( const hypro::matrix_t<Number> _mat );
	Location<Number>* create( const hypro::matrix_t<Number> _mat,
							  const typename Location<Number>::transitionSet _trans,
							  const struct Location<Number>::Invariant _inv );
	Location<Number>* create( const hypro::matrix_t<Number> _mat,
							  const typename Location<Number>::transitionSet _trans,
							  const struct Location<Number>::Invariant _inv,
							  const hypro::matrix_t<Number> _extInputMat );

	unsigned id(const Location<Number>* _loc) const;
	Location<Number>* location(unsigned _id) const;
};

}  // namespace

#include "LocationManager.tpp"
