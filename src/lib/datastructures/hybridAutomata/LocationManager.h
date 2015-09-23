/**
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 *
 */

#pragma once

#include <carl/util/Singleton.h>
#include "Location.h"

namespace hypro {

template <typename Number>
class LocationManager : public carl::Singleton<LocationManager<Number>> {
	friend carl::Singleton<LocationManager>;

  private:
	std::map<unsigned, Location<Number>*> mLocations;
	unsigned mId;

  protected:
	/**
	 * Default constructor and destructor
	 */
	LocationManager() : mId( 0 ) {}

  public:
	~LocationManager() {}

	Location<Number>* create();
	Location<Number>* create( const Location<Number>* _loc );
	Location<Number>* create( const hypro::matrix_t<Number> _mat, const hypro::vector_t<Number> _vec,
							  const typename Location<Number>::transitionSet _trans,
							  const struct Location<Number>::Invariant _inv );
	Location<Number>* create( const hypro::matrix_t<Number> _mat, const hypro::vector_t<Number> _vec,
							  const typename Location<Number>::transitionSet _trans,
							  const struct Location<Number>::Invariant _inv,
							  const hypro::matrix_t<Number> _extInputMat );
};

}  // namespace

#include "LocationManager.tpp"
