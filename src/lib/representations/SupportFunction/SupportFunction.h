/* This header implements the support functions defined by Girard et al.
 * @file   SupportFunction.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	2015-01-15
 * @version	2015-01-15
 */

#pragma once

#include "../../config.h"
#include "../../util/types.h"
#include "../../datastructures/Point.h"
#include "../GeometricObject.h"

namespace hypro {

// Eigen less operator for vectors
template<typename Number>
struct vecLess {
	bool operator() (const vector_t<Number>& lhs, const vector_t<Number>& rhs) const
	{
	assert(lhs.rows() == rhs.rows());
	unsigned pos = 0;
	while(pos < lhs.rows() && lhs(pos) == rhs(pos) )
		++pos;
	
	return (pos != lhs.rows() && lhs(pos) < rhs(pos) );
	}
	typedef vector_t<Number> first_argument_type;
	typedef vector_t<Number> second_argument_type;
	typedef bool result_type;
};

template<typename Number>
class SupportFunction : hypro::GeometricObject<Number> {
	public:
		typedef vector_t<Number> direction;
		typedef std::map<direction, Number, vecLess<Number>> directionValueMapping;
		typedef std::set<direction, vecLess<Number>> directionSet;
	private:
		directionValueMapping mDirections;

	public:
		SupportFunction();
		SupportFunction( const SupportFunction<Number>& _orig );
		SupportFunction( SupportFunction<Number>&& ) = default;
		
		SupportFunction<Number>& operator= ( const SupportFunction<Number>& ) = default;
		SupportFunction<Number>& operator= ( SupportFunction<Number>&& ) = default;
		
		virtual ~SupportFunction(){}
		
		directionValueMapping content() const;
		directionValueMapping& rContent();
		
		directionSet directions() const;
		std::pair<const Number&,bool> distance(const direction& _direction) const;
		bool hasDirection(const std::pair<direction,Number>& _directionPair) const;
		bool isEmpty() const;
		unsigned size() const;
		
		bool addDirection(const direction& _direction, const Number& _distance);
		bool addDirection(const Point<Number>& _direction, const Number& _distance);
		bool addDirection(const std::pair<direction,Number>& _directionPair);
		
		void clear();
		
		unsigned int dimension() const;
        bool linearTransformation(SupportFunction<Number>& _result, const matrix_t<Number>& _A, const vector_t<Number>& _b = vector_t<Number>()) const;
		bool minkowskiSum(SupportFunction<Number>& _result, const SupportFunction<Number>& _rhs) const;
        bool intersect(SupportFunction<Number>& _result, const SupportFunction<Number>& _rhs) const;
        bool hull(SupportFunction<Number>& _result) const;
        bool contains(const Point<Number>& _point) const;
        bool contains(const SupportFunction<Number>& _sf) const;
        bool unite(SupportFunction<Number>& _result, const SupportFunction<Number>& _rhs) const;
        void convexHull(std::vector<Point<Number>> _points);
};

template<typename Number>
inline bool operator==(const hypro::SupportFunction<Number>& _lhs, const hypro::SupportFunction<Number>& _rhs) {
	if(_lhs.size() != _rhs.size())
		return false;
	
	for(auto& directionPair : _lhs.content()) {
		if(!_rhs.hasDirection(directionPair))
			return false;
	}
	return true;
}

template<typename Number>
inline bool operator!=(const hypro::SupportFunction<Number>& _lhs, const hypro::SupportFunction<Number>& _rhs) {
	return !(_lhs == _rhs);
}

template<typename Number>
std::ostream& operator<<(std::ostream& _out, const hypro::SupportFunction<Number>& _in){
	_out << "( ";
	typename hypro::SupportFunction<Number>::directionValueMapping tmp = _in.content();
	if(!tmp.empty()) {
		for(auto tmpIt = tmp.begin(); tmpIt != --tmp.end(); ++tmpIt) {
			_out << tmpIt->first << ", " << tmpIt->second << "; " << std::endl;
		}
		_out << (--tmp.end())->first << ", " << (--tmp.end())->second;
	}
	_out << " )";
	return _out;
}

} // namespace
#include "SupportFunction.tpp"