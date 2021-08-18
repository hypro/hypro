/**
 *
 */

#pragma once
#include "../../datastructures/Halfspace.h"

#include <memory>
#include <vector>

namespace hypro {

template <typename Number>
using vectorSet = std::set<vector_t<Number>>;

template <typename Number>
bool operator<( std::shared_ptr<Halfspace<Number>> _lhs, std::shared_ptr<Halfspace<Number>> _rhs ) {
	return ( *_lhs.get() < *_rhs.get() );
}

template <typename Number>
class Cone {
  public:
	using planeVector = std::vector<std::shared_ptr<Halfspace<Number>>>;

  private:
	planeVector mPlanes;

  public:
	Cone();
	Cone( const Cone& _orig );
	Cone( const planeVector& _planes );
	~Cone();

	/*
	 * Getters & setters
	 */

	const typename Cone<Number>::planeVector& planes() const;
	vectorSet<Number> vectors() const;
	unsigned dimension() const;
	unsigned size() const;

	void add( std::shared_ptr<Halfspace<Number>> _plane );
	void add( vector_t<Number> _vector );

	Cone<Number> linearTransformation( const matrix_t<Number> A ) const;
	Cone<Number> affineTransformation( const matrix_t<Number> A, const vector_t<Number>& b ) const;
	Cone<Number> minkowskiSum( const Cone& _rhs ) const;
	Point<Number> getUnitAverageVector() const;

	bool contains( const vector_t<Number>& _vector ) const;
	bool contains( const vector_t<Number>& _vector, planeVector& _insidePlanes,
				   std::set<std::shared_ptr<Halfspace<Number>>>& _outsidePlanes ) const;
	bool contains( const Point<Number>* _vector ) const;

	Cone<Number> operator=( const Cone<Number>& _rhs );
};

template <typename Number>
std::ostream& operator<<( std::ostream& _out, Cone<Number>& _cone ) {
	_out << "Cone [ " << std::endl;
	for ( const auto& plane : _cone.planes() ) {
		_out << *plane << ", " << std::endl;
	}
	_out << " ]" << std::endl;
	return _out;
}

}  // namespace hypro

#include "Cone.tpp"
