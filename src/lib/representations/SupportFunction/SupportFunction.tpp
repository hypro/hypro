/* 
 * @file   SupportFunction.tpp
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	2015-01-15
 * @version	2015-01-15
 */

#pragma once
#include "SupportFunction.h"

namespace hypro {
	template<typename Number>
	SupportFunction<Number>::SupportFunction() {
		
	}
	
	template<typename Number>
	SupportFunction<Number>::SupportFunction( const SupportFunction<Number>& _orig ) : 
		mDirections(_orig.content())
	{}
	
	template<typename Number>
	typename SupportFunction<Number>::directionValueMapping SupportFunction<Number>::content() const{
		return mDirections;
	}
	
	template<typename Number>
	typename SupportFunction<Number>::directionValueMapping& SupportFunction<Number>::rContent() {
		return mDirections;
	}
		
	template<typename Number>
	typename SupportFunction<Number>::directionSet SupportFunction<Number>::directions() const {
		directionSet directions;
		for(const auto& directionPair : mDirections) {
			directions.insert(directionPair.first);
		}
		return directions;
	}
	
	template<typename Number>
	std::pair<const Number&,bool> SupportFunction<Number>::distance(const direction& _direction) const {
		// Todo: What if _direction is not a direction of this supportfunction? -> evaluate?
		typename directionValueMapping::const_iterator pos = mDirections.find(_direction);
		if(pos != mDirections.end()) 
			return std::make_pair(pos->second,true);
	
		// TODO
		assert(false);
	}
		
	template<typename Number>
	void SupportFunction<Number>::addDirection(const direction& _direction, const Number& _distance) {
		
	}
	
	template<typename Number>
	void SupportFunction<Number>::addDirection(const Point<Number>& _direction, const Number& _distance) {
		
	}
} // namespace