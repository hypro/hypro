#pragma once
#include "Orthoplex.h"

namespace hypro {

template <typename Number, typename Converter, typename Setting>
OrthoplexT<Number, Converter, Setting>::OrthoplexT() {
}

template <typename Number, typename Converter, typename Setting>
OrthoplexT<Number, Converter, Setting>::OrthoplexT( const OrthoplexT<Number, Converter, Setting>& orig ) {
}

template <typename Number, typename Converter, typename Setting>
OrthoplexT<Number, Converter, Setting>::OrthoplexT( OrthoplexT<Number, Converter, Setting>&& orig ) {
}

template <typename Number, typename Converter, typename Setting>
bool OrthoplexT<Number, Converter, Setting>::empty() const {
	return false;
}

template <typename Number, typename Converter, typename Setting>
Number OrthoplexT<Number, Converter, Setting>::supremum() const {
	return Number( 0 );
}

template <typename Number, typename Converter, typename Setting>
std::vector<Point<Number>> OrthoplexT<Number, Converter, Setting>::vertices( const matrix_t<Number>& m ) const {
	return std::vector<Point<Number>>();
}

template <typename Number, typename Converter, typename Setting>
EvaluationResult<Number> OrthoplexT<Number, Converter, Setting>::evaluate( const vector_t<Number>& _direction, bool ) const {
	return EvaluationResult<Number>();
}

template <typename Number, typename Converter, typename Setting>
std::vector<EvaluationResult<Number>> OrthoplexT<Number, Converter, Setting>::multiEvaluate( const matrix_t<Number>& _directions, bool useExact ) const {
	return std::vector<EvaluationResult<Number>>();
}

template <typename Number, typename Converter, typename Setting>
std::size_t OrthoplexT<Number, Converter, Setting>::dimension() const {
	return std::size_t( 0 );
}

template <typename Number, typename Converter, typename Setting>
void OrthoplexT<Number, Converter, Setting>::removeRedundancy() {
}

template <typename Number, typename Converter, typename Setting>
std::size_t OrthoplexT<Number, Converter, Setting>::size() const {
	return std::size_t( 0 );
}

template <typename Number, typename Converter, typename Setting>
const OrthoplexT<Number, Converter, Setting>& OrthoplexT<Number, Converter, Setting>::reduceNumberRepresentation() {
	return *this;
}

template <typename Number, typename Converter, typename Setting>
std::pair<CONTAINMENT, OrthoplexT<Number, Converter, Setting>> OrthoplexT<Number, Converter, Setting>::satisfiesHalfspace( const Halfspace<Number>& rhs ) const {
	return std::pair<CONTAINMENT, OrthoplexT<Number, Converter, Setting>>();
}

template <typename Number, typename Converter, typename Setting>
std::pair<CONTAINMENT, OrthoplexT<Number, Converter, Setting>> OrthoplexT<Number, Converter, Setting>::satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {
	return std::pair<CONTAINMENT, OrthoplexT<Number, Converter, Setting>>();
}

template <typename Number, typename Converter, typename Setting>
OrthoplexT<Number, Converter, Setting> OrthoplexT<Number, Converter, Setting>::projectOn( const std::vector<std::size_t>& dimensions ) const {
	return *this;
}

template <typename Number, typename Converter, typename Setting>
OrthoplexT<Number, Converter, Setting> OrthoplexT<Number, Converter, Setting>::linearTransformation( const matrix_t<Number>& A ) const {
	return *this;
}

template <typename Number, typename Converter, typename Setting>
OrthoplexT<Number, Converter, Setting> OrthoplexT<Number, Converter, Setting>::affineTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const {
	return *this;
}

template <typename Number, typename Converter, typename Setting>
OrthoplexT<Number, Converter, Setting> OrthoplexT<Number, Converter, Setting>::minkowskiSum( const OrthoplexT<Number, Converter, Setting>& rhs ) const {
	return *this;
}

template <typename Number, typename Converter, typename Setting>
OrthoplexT<Number, Converter, Setting> OrthoplexT<Number, Converter, Setting>::intersect( const OrthoplexT<Number, Converter, Setting>& rhs ) const {
	return *this;
}

template <typename Number, typename Converter, typename Setting>
OrthoplexT<Number, Converter, Setting> OrthoplexT<Number, Converter, Setting>::intersectHalfspace( const Halfspace<Number>& hspace ) const {
	return *this;
}

template <typename Number, typename Converter, typename Setting>
OrthoplexT<Number, Converter, Setting> OrthoplexT<Number, Converter, Setting>::intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {
	return *this;
}

template <typename Number, typename Converter, typename Setting>
bool OrthoplexT<Number, Converter, Setting>::contains( const Point<Number>& point ) const {
	return false;
}

template <typename Number, typename Converter, typename Setting>
bool OrthoplexT<Number, Converter, Setting>::contains( const OrthoplexT<Number, Converter, Setting>& Orthoplex ) const {
	return false;
}

template <typename Number, typename Converter, typename Setting>
OrthoplexT<Number, Converter, Setting> OrthoplexT<Number, Converter, Setting>::unite( const OrthoplexT<Number, Converter, Setting>& rhs ) const {
	return *this;
}

template <typename Number, typename Converter, typename Setting>
OrthoplexT<Number, Converter, Setting> OrthoplexT<Number, Converter, Setting>::unite( const std::vector<OrthoplexT<Number, Converter, Setting>>& Orthoplexes ) {
	return *this;
}

template <typename Number, typename Converter, typename Setting>
void OrthoplexT<Number, Converter, Setting>::reduceRepresentation() {
}

template <typename Number, typename Converter, typename Setting>
void OrthoplexT<Number, Converter, Setting>::clear() {
}

}  // namespace hypro
