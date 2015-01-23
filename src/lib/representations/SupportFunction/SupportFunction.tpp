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
	bool SupportFunction<Number>::hasDirection(const std::pair<direction,Number>& _directionPair) const {
		return (mDirections.find(_directionPair.first) != mDirections.end() && mDirections.at(_directionPair.first) == _directionPair.second);
	}
	
	template<typename Number>
	bool SupportFunction<Number>::isEmpty() const {
		return mDirections.empty();
	}
	
	template<typename Number>
	unsigned SupportFunction<Number>::size() const {
		return mDirections.size();
	}
		
	template<typename Number>
	bool SupportFunction<Number>::addDirection(const direction& _direction, const Number& _distance) {
		return mDirections.insert(std::make_pair(_direction, _distance)).second;
	}
	
	template<typename Number>
	bool SupportFunction<Number>::addDirection(const Point<Number>& _direction, const Number& _distance) {
		return mDirections.insert(std::make_pair(createVector<Number>(_direction), _distance) ).second;
	}
	
	template<typename Number>
	bool SupportFunction<Number>::addDirection(const std::pair<direction,Number>& _directionPair) {
		return mDirections.insert(_directionPair).second;
	}
	
	template<typename Number>
	void SupportFunction<Number>::clear() {
		mDirections.clear();
	}
	
	template<typename Number>
	unsigned int SupportFunction<Number>::dimension() const {
		return (mDirections.begin())->first.rows();
	}
	
	template<typename Number>
    bool SupportFunction<Number>::linearTransformation(SupportFunction<Number>& _result, const matrix_t<Number>& _A, const vector_t<Number>& _b) const {
		matrix_t<Number> transposed = _A.transpose();
		if(!_result.isEmpty())
			_result.clear();
		
		for(auto& directionPair : mDirections) {
			_result.addDirection(transposed*directionPair.first, directionPair.second);
		}
	}
	
	template<typename Number>
	bool SupportFunction<Number>::minkowskiSum(SupportFunction<Number>& _result, const SupportFunction<Number>& _rhs) const {
		if(!_result.isEmpty())
			_result.clear();
		
		for(auto& directionPair : mDirections)
			_result.addDirection(directionPair);
		
		for(auto& directionPair : _rhs.content())
			_result.addDirection(directionPair);
		
		return true;
	}
	
	template<typename Number>
	bool SupportFunction<Number>::intersect(SupportFunction<Number>& _result, const SupportFunction<Number>& _rhs) const {
		
	}
	
	template<typename Number>
	bool SupportFunction<Number>::hull(SupportFunction<Number>& _result) const {
		
	}
	
	template<typename Number>
	bool SupportFunction<Number>::contains(const Point<Number>& _point) const {
		
	}
	
	template<typename Number>
	bool SupportFunction<Number>::contains(const SupportFunction<Number>& _poly) const {
		
	}
	
	template<typename Number>
	bool SupportFunction<Number>::unite(SupportFunction<Number>& _result, const SupportFunction<Number>& _rhs) const {
		
	}
	
	template<typename Number>
	void SupportFunction<Number>::convexHull(std::vector<Point<Number>> _points) {
		
	}
} // namespace