#pragma once
#include "Simplex.h"

namespace hypro {

	template<typename Number, typename Converter, typename Setting>
	SimplexT<Number,Converter,Setting>::SimplexT() {

	}

	template<typename Number, typename Converter, typename Setting>
	SimplexT<Number,Converter,Setting>::SimplexT( const SimplexT<Number,Converter,Setting>& orig ) {

	}

	template<typename Number, typename Converter, typename Setting>
	SimplexT<Number,Converter,Setting>::SimplexT( SimplexT<Number,Converter,Setting>&& orig ) {

	}

	template<typename Number, typename Converter, typename Setting>
	bool SimplexT<Number,Converter,Setting>::empty() const {

	}

	template<typename Number, typename Converter, typename Setting>
	Number SimplexT<Number,Converter,Setting>::supremum() const {

	}

	template<typename Number, typename Converter, typename Setting>
	std::vector<Point<Number>> SimplexT<Number,Converter,Setting>::vertices( const matrix_t<Number>& m ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	EvaluationResult<Number> SimplexT<Number,Converter,Setting>::evaluate( const vector_t<Number>& _direction, bool ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	std::vector<EvaluationResult<Number>> SimplexT<Number,Converter,Setting>::multiEvaluate( const matrix_t<Number>& _directions, bool useExact ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	std::size_t SimplexT<Number,Converter,Setting>::dimension() const {

	}

	template<typename Number, typename Converter, typename Setting>
	void SimplexT<Number,Converter,Setting>::removeRedundancy() {

	}

	template<typename Number, typename Converter, typename Setting>
	std::size_t SimplexT<Number,Converter,Setting>::size() const {

	}

	template<typename Number, typename Converter, typename Setting>
	const SimplexT<Number,Converter,Setting>& SimplexT<Number,Converter,Setting>::reduceNumberRepresentation() {

	}

	template<typename Number, typename Converter, typename Setting>
	std::pair<CONTAINMENT, SimplexT<Number,Converter,Setting>> SimplexT<Number,Converter,Setting>::satisfiesHalfspace( const Halfspace<Number>& rhs ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	std::pair<CONTAINMENT, SimplexT<Number,Converter,Setting>> SimplexT<Number,Converter,Setting>::satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	SimplexT<Number,Converter,Setting> SimplexT<Number,Converter,Setting>::project(const std::vector<std::size_t>& dimensions) const {

	}

	template<typename Number, typename Converter, typename Setting>
	SimplexT<Number,Converter,Setting> SimplexT<Number,Converter,Setting>::linearTransformation( const matrix_t<Number>& A ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	SimplexT<Number,Converter,Setting> SimplexT<Number,Converter,Setting>::affineTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	SimplexT<Number,Converter,Setting> SimplexT<Number,Converter,Setting>::minkowskiSum( const SimplexT<Number,Converter,Setting>& rhs ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	SimplexT<Number,Converter,Setting> SimplexT<Number,Converter,Setting>::intersect( const SimplexT<Number,Converter,Setting>& rhs ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	SimplexT<Number,Converter,Setting> SimplexT<Number,Converter,Setting>::intersectHalfspace( const Halfspace<Number>& hspace ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	SimplexT<Number,Converter,Setting> SimplexT<Number,Converter,Setting>::intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	bool SimplexT<Number,Converter,Setting>::contains( const Point<Number>& point ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	bool SimplexT<Number,Converter,Setting>::contains( const SimplexT<Number,Converter,Setting>& Simplex ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	SimplexT<Number,Converter,Setting> SimplexT<Number,Converter,Setting>::unite( const SimplexT<Number,Converter,Setting>& rhs ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	SimplexT<Number,Converter,Setting> SimplexT<Number,Converter,Setting>::unite( const std::vector<SimplexT<Number,Converter,Setting>>& Simplexes ) {

	}

	template<typename Number, typename Converter, typename Setting>
	void SimplexT<Number,Converter,Setting>::reduceRepresentation() {

	}

	template<typename Number, typename Converter, typename Setting>
	void SimplexT<Number,Converter,Setting>::clear() {

	}

} // namespace hypro
