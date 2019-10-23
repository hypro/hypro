#pragma once
#include "GeneralizedStar.h"

namespace hypro {

	template<typename Number, typename Converter, typename Setting>
	GeneralizedStarT<Number,Converter,Setting>::GeneralizedStarT() {

	}

	template<typename Number, typename Converter, typename Setting>
	GeneralizedStarT<Number,Converter,Setting>::GeneralizedStarT( const GeneralizedStarT<Number,Converter,Setting>& orig ) {

	}

	template<typename Number, typename Converter, typename Setting>
	GeneralizedStarT<Number,Converter,Setting>::GeneralizedStarT( GeneralizedStarT<Number,Converter,Setting>&& orig ) {

	}

	template<typename Number, typename Converter, typename Setting>
	bool GeneralizedStarT<Number,Converter,Setting>::empty() const {
		assert(false && "Not implemented.");
		return true;
	}

	template<typename Number, typename Converter, typename Setting>
	Number GeneralizedStarT<Number,Converter,Setting>::supremum() const {

	}

	template<typename Number, typename Converter, typename Setting>
	std::vector<Point<Number>> GeneralizedStarT<Number,Converter,Setting>::vertices( const matrix_t<Number>& m ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	EvaluationResult<Number> GeneralizedStarT<Number,Converter,Setting>::evaluate( const vector_t<Number>& _direction, bool ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	std::vector<EvaluationResult<Number>> GeneralizedStarT<Number,Converter,Setting>::multiEvaluate( const matrix_t<Number>& _directions, bool useExact ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	std::size_t GeneralizedStarT<Number,Converter,Setting>::dimension() const {
		assert(false && "Not implemented.");
		return 0;
	}

	template<typename Number, typename Converter, typename Setting>
	void GeneralizedStarT<Number,Converter,Setting>::removeRedundancy() {

	}

	template<typename Number, typename Converter, typename Setting>
	std::size_t GeneralizedStarT<Number,Converter,Setting>::size() const {
		assert(false && "Not implemented.");
		return 0;
	}

	template<typename Number, typename Converter, typename Setting>
	const GeneralizedStarT<Number,Converter,Setting>& GeneralizedStarT<Number,Converter,Setting>::reduceNumberRepresentation() {

	}

	template<typename Number, typename Converter, typename Setting>
	std::pair<CONTAINMENT, GeneralizedStarT<Number,Converter,Setting>> GeneralizedStarT<Number,Converter,Setting>::satisfiesHalfspace( const Halfspace<Number>& rhs ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	std::pair<CONTAINMENT, GeneralizedStarT<Number,Converter,Setting>> GeneralizedStarT<Number,Converter,Setting>::satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	GeneralizedStarT<Number,Converter,Setting> GeneralizedStarT<Number,Converter,Setting>::project(const std::vector<std::size_t>& dimensions) const {

	}

	template<typename Number, typename Converter, typename Setting>
	GeneralizedStarT<Number,Converter,Setting> GeneralizedStarT<Number,Converter,Setting>::linearTransformation( const matrix_t<Number>& A ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	GeneralizedStarT<Number,Converter,Setting> GeneralizedStarT<Number,Converter,Setting>::affineTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	GeneralizedStarT<Number,Converter,Setting> GeneralizedStarT<Number,Converter,Setting>::minkowskiSum( const GeneralizedStarT<Number,Converter,Setting>& rhs ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	GeneralizedStarT<Number,Converter,Setting> GeneralizedStarT<Number,Converter,Setting>::intersect( const GeneralizedStarT<Number,Converter,Setting>& rhs ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	GeneralizedStarT<Number,Converter,Setting> GeneralizedStarT<Number,Converter,Setting>::intersectHalfspace( const Halfspace<Number>& hspace ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	GeneralizedStarT<Number,Converter,Setting> GeneralizedStarT<Number,Converter,Setting>::intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	bool GeneralizedStarT<Number,Converter,Setting>::contains( const Point<Number>& point ) const {
		assert(false && "Not implemented.");
		return false;
	}

	template<typename Number, typename Converter, typename Setting>
	bool GeneralizedStarT<Number,Converter,Setting>::contains( const GeneralizedStarT<Number,Converter,Setting>& GeneralizedStar ) const {
		assert(false && "Not implemented.");
		return false;
	}

	template<typename Number, typename Converter, typename Setting>
	GeneralizedStarT<Number,Converter,Setting> GeneralizedStarT<Number,Converter,Setting>::unite( const GeneralizedStarT<Number,Converter,Setting>& rhs ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	GeneralizedStarT<Number,Converter,Setting> GeneralizedStarT<Number,Converter,Setting>::unite( const std::vector<GeneralizedStarT<Number,Converter,Setting>>& GeneralizedStares ) {

	}

	template<typename Number, typename Converter, typename Setting>
	void GeneralizedStarT<Number,Converter,Setting>::reduceRepresentation() {

	}

	template<typename Number, typename Converter, typename Setting>
	void GeneralizedStarT<Number,Converter,Setting>::clear() {

	}

} // namespace hypro
