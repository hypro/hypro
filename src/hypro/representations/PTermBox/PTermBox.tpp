#include "PTermBox.h"

namespace hypro {

template <typename Number>
PTermBox<Number>::PTermBox()
{}

template <typename Number>
PTermBox<Number>::PTermBox( const PTermBox& orig )
{}

template <typename Number>
PTermBox<Number>::PTermBox( const carl::Interval<Number>& val )
{}

template <typename Number>
PTermBox<Number>::PTermBox( const std::vector<carl::Interval<Number>>& _intervals )
{}

template <typename Number>
PTermBox<Number>::PTermBox( const std::set<Point<Number>>& _points )
{}

template <typename Number>
PTermBox<Number>::PTermBox( const std::vector<Point<Number>>& _points )
{}

template <typename Number>
PTermBox<Number>::~PTermBox()
{}

/***************************************************************************
 * Getters & setters
 **************************************************************************/

template <typename Number>
PTermBox<Number> PTermBox<Number>::Empty(std::size_t dimension)
{
	return PTermBox<Number>();
}

template <typename Number>
void PTermBox<Number>::insert( const carl::Interval<Number>& val )
{}

template <typename Number>
void PTermBox<Number>::insert( const std::vector<carl::Interval<Number>>& boundaries )
{}

template <typename Number>
std::size_t PTermBox<Number>::dimension() const
{
	return 0;
}

template <typename Number>
bool PTermBox<Number>::empty() const
{
	return false;
}

template <typename Number>
Point<Number> PTermBox<Number>::max() const
{
	return Point<Number>();
}

template <typename Number>
Point<Number> PTermBox<Number>::min() const
{
	return Point<Number>();
}

template <typename Number>
std::vector<Point<Number>> PTermBox<Number>::vertices() const
{
	return std::vector<Point<Number>>();
}

template <typename Number>
std::vector<carl::Interval<Number>> PTermBox<Number>::boundaries() const
{
	return std::vector<carl::Interval<Number>>();
}

template <typename Number>
PTermBox<Number>& PTermBox<Number>::operator=( const PTermBox<Number>& rhs )
{
	return *this;
}

template <typename Number>
void PTermBox<Number>::print() const
{}

template <typename Number>
const carl::Interval<Number>& PTermBox<Number>::operator[]( std::size_t i ) const
{
	return carl::Interval<Number>();
}

template <typename Number>
carl::Interval<Number>& PTermBox<Number>::operator[]( std::size_t i )
{
	return carl::Interval<Number>();
}

template <typename Number>
void PTermBox<Number>::clear()
{}

template <typename Number>
PTermBox<Number> PTermBox<Number>::linearTransformation( const matrix_t<Number> &A, const vector_t<Number> &b ) const {
	PTermBox<Number> result;
	return result;
}

template <typename Number>
PTermBox<Number> PTermBox<Number>::minkowskiSum( const PTermBox<Number> &rhs ) const {
	PTermBox<Number> result;
	return result;
}

template <typename Number>
PTermBox<Number> PTermBox<Number>::intersect( const PTermBox<Number> &rhs ) const {
	PTermBox<Number> result;
	return result;
}

template <typename Number>
bool PTermBox<Number>::contains( const Point<Number> &point ) const {
	return false;
}

template <typename Number>
bool PTermBox<Number>::contains( const PTermBox<Number> &box ) const {
	return false;
}

template <typename Number>
PTermBox<Number> PTermBox<Number>::unite( const PTermBox<Number> &rhs ) const {
	PTermBox<Number> result;
	return result;
}

}  // namespace
