#pragma once
#include "REPRESENTATION.h"

namespace hypro {

template <typename Number, typename Converter, typename Setting>
REPRESENTATIONT<Number, Converter, Setting>::REPRESENTATIONT() {
}

template <typename Number, typename Converter, typename Setting>
REPRESENTATIONT<Number, Converter, Setting>::REPRESENTATIONT( const REPRESENTATIONT<Number, Converter, Setting>& orig ) {
}

template <typename Number, typename Converter, typename Setting>
REPRESENTATIONT<Number, Converter, Setting>::REPRESENTATIONT( REPRESENTATIONT<Number, Converter, Setting>&& orig ) {
}

template <typename Number, typename Converter, typename Setting>
bool REPRESENTATIONT<Number, Converter, Setting>::empty() const {
}

template <typename Number, typename Converter, typename Setting>
Number REPRESENTATIONT<Number, Converter, Setting>::supremum() const {
}

template <typename Number, typename Converter, typename Setting>
std::vector<Point<Number>> REPRESENTATIONT<Number, Converter, Setting>::vertices( const matrix_t<Number>& m ) const {
}

template <typename Number, typename Converter, typename Setting>
EvaluationResult<Number> REPRESENTATIONT<Number, Converter, Setting>::evaluate( const vector_t<Number>& _direction, bool ) const {
}

template <typename Number, typename Converter, typename Setting>
std::vector<EvaluationResult<Number>> REPRESENTATIONT<Number, Converter, Setting>::multiEvaluate( const matrix_t<Number>& _directions, bool useExact ) const {
}

template <typename Number, typename Converter, typename Setting>
std::size_t REPRESENTATIONT<Number, Converter, Setting>::dimension() const {
}

template <typename Number, typename Converter, typename Setting>
void REPRESENTATIONT<Number, Converter, Setting>::removeRedundancy() {
}

template <typename Number, typename Converter, typename Setting>
std::size_t REPRESENTATIONT<Number, Converter, Setting>::size() const {
}

template <typename Number, typename Converter, typename Setting>
const REPRESENTATIONT<Number, Converter, Setting>& REPRESENTATIONT<Number, Converter, Setting>::reduceNumberRepresentation() {
}

template <typename Number, typename Converter, typename Setting>
std::pair<CONTAINMENT, REPRESENTATIONT<Number, Converter, Setting>> REPRESENTATIONT<Number, Converter, Setting>::satisfiesHalfspace( const Halfspace<Number>& rhs ) const {
}

template <typename Number, typename Converter, typename Setting>
std::pair<CONTAINMENT, REPRESENTATIONT<Number, Converter, Setting>> REPRESENTATIONT<Number, Converter, Setting>::satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {
}

template <typename Number, typename Converter, typename Setting>
REPRESENTATIONT<Number, Converter, Setting> REPRESENTATIONT<Number, Converter, Setting>::projectOn( const std::vector<std::size_t>& dimensions ) const {
}

template <typename Number, typename Converter, typename Setting>
REPRESENTATIONT<Number, Converter, Setting> REPRESENTATIONT<Number, Converter, Setting>::linearTransformation( const matrix_t<Number>& A ) const {
}

template <typename Number, typename Converter, typename Setting>
REPRESENTATIONT<Number, Converter, Setting> REPRESENTATIONT<Number, Converter, Setting>::affineTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const {
}

template <typename Number, typename Converter, typename Setting>
REPRESENTATIONT<Number, Converter, Setting> REPRESENTATIONT<Number, Converter, Setting>::minkowskiSum( const REPRESENTATIONT<Number, Converter, Setting>& rhs ) const {
}

template <typename Number, typename Converter, typename Setting>
REPRESENTATIONT<Number, Converter, Setting> REPRESENTATIONT<Number, Converter, Setting>::intersect( const REPRESENTATIONT<Number, Converter, Setting>& rhs ) const {
}

template <typename Number, typename Converter, typename Setting>
REPRESENTATIONT<Number, Converter, Setting> REPRESENTATIONT<Number, Converter, Setting>::intersectHalfspace( const Halfspace<Number>& hspace ) const {
}

template <typename Number, typename Converter, typename Setting>
REPRESENTATIONT<Number, Converter, Setting> REPRESENTATIONT<Number, Converter, Setting>::intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {
}

template <typename Number, typename Converter, typename Setting>
bool REPRESENTATIONT<Number, Converter, Setting>::contains( const Point<Number>& point ) const {
}

template <typename Number, typename Converter, typename Setting>
bool REPRESENTATIONT<Number, Converter, Setting>::contains( const REPRESENTATIONT<Number, Converter, Setting>& REPRESENTATION ) const {
}

template <typename Number, typename Converter, typename Setting>
REPRESENTATIONT<Number, Converter, Setting> REPRESENTATIONT<Number, Converter, Setting>::unite( const REPRESENTATIONT<Number, Converter, Setting>& rhs ) const {
}

template <typename Number, typename Converter, typename Setting>
REPRESENTATIONT<Number, Converter, Setting> REPRESENTATIONT<Number, Converter, Setting>::unite( const std::vector<REPRESENTATIONT<Number, Converter, Setting>>& REPRESENTATIONes ) {
}

template <typename Number, typename Converter, typename Setting>
void REPRESENTATIONT<Number, Converter, Setting>::reduceRepresentation() {
}

template <typename Number, typename Converter, typename Setting>
void REPRESENTATIONT<Number, Converter, Setting>::clear() {
}

}  // namespace hypro
