#pragma once
#include "SupportFunctionNew.h"

namespace hypro {

	template<typename Number, typename Converter, typename Setting>
	SupportFunctionNewT<Number,Converter,Setting>::SupportFunctionNewT() {

	}

	template<typename Number, typename Converter, typename Setting>
	SupportFunctionNewT<Number,Converter,Setting>::SupportFunctionNewT( const SupportFunctionNewT<Number,Converter,Setting>& orig ) {

	}

	template<typename Number, typename Converter, typename Setting>
	SupportFunctionNewT<Number,Converter,Setting>::SupportFunctionNewT( SupportFunctionNewT<Number,Converter,Setting>&& orig ) {

	}

	template<typename Number, typename Converter, typename Setting>
	bool SupportFunctionNewT<Number,Converter,Setting>::empty() const {
		return true;
	}

	template<typename Number, typename Converter, typename Setting>
	Number SupportFunctionNewT<Number,Converter,Setting>::supremum() const {

	}

	template<typename Number, typename Converter, typename Setting>
	std::vector<Point<Number>> SupportFunctionNewT<Number,Converter,Setting>::vertices( const matrix_t<Number>& m ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	EvaluationResult<Number> SupportFunctionNewT<Number,Converter,Setting>::evaluate( const vector_t<Number>& _direction, bool ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	std::vector<EvaluationResult<Number>> SupportFunctionNewT<Number,Converter,Setting>::multiEvaluate( const matrix_t<Number>& _directions, bool useExact ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	std::size_t SupportFunctionNewT<Number,Converter,Setting>::dimension() const {
		return std::size_t(1);
	}

	template<typename Number, typename Converter, typename Setting>
	void SupportFunctionNewT<Number,Converter,Setting>::removeRedundancy() {

	}

	template<typename Number, typename Converter, typename Setting>
	std::size_t SupportFunctionNewT<Number,Converter,Setting>::size() const {
		return std::size_t(1);
	}

	template<typename Number, typename Converter, typename Setting>
	const SupportFunctionNewT<Number,Converter,Setting>& SupportFunctionNewT<Number,Converter,Setting>::reduceNumberRepresentation() {

	}

	template<typename Number, typename Converter, typename Setting>
	std::pair<CONTAINMENT, SupportFunctionNewT<Number,Converter,Setting>> SupportFunctionNewT<Number,Converter,Setting>::satisfiesHalfspace( const Halfspace<Number>& rhs ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	std::pair<CONTAINMENT, SupportFunctionNewT<Number,Converter,Setting>> SupportFunctionNewT<Number,Converter,Setting>::satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	SupportFunctionNewT<Number,Converter,Setting> SupportFunctionNewT<Number,Converter,Setting>::project(const std::vector<std::size_t>& dimensions) const {

	}

	template<typename Number, typename Converter, typename Setting>
	SupportFunctionNewT<Number,Converter,Setting> SupportFunctionNewT<Number,Converter,Setting>::linearTransformation( const matrix_t<Number>& A ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	SupportFunctionNewT<Number,Converter,Setting> SupportFunctionNewT<Number,Converter,Setting>::affineTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	SupportFunctionNewT<Number,Converter,Setting> SupportFunctionNewT<Number,Converter,Setting>::minkowskiSum( const SupportFunctionNewT<Number,Converter,Setting>& rhs ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	SupportFunctionNewT<Number,Converter,Setting> SupportFunctionNewT<Number,Converter,Setting>::intersect( const SupportFunctionNewT<Number,Converter,Setting>& rhs ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	SupportFunctionNewT<Number,Converter,Setting> SupportFunctionNewT<Number,Converter,Setting>::intersectHalfspace( const Halfspace<Number>& hspace ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	SupportFunctionNewT<Number,Converter,Setting> SupportFunctionNewT<Number,Converter,Setting>::intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	bool SupportFunctionNewT<Number,Converter,Setting>::contains( const Point<Number>& point ) const {
		return true;
	}

	template<typename Number, typename Converter, typename Setting>
	bool SupportFunctionNewT<Number,Converter,Setting>::contains( const SupportFunctionNewT<Number,Converter,Setting>& SupportFunctionNew ) const {
		return true;
	}

	template<typename Number, typename Converter, typename Setting>
	SupportFunctionNewT<Number,Converter,Setting> SupportFunctionNewT<Number,Converter,Setting>::unite( const SupportFunctionNewT<Number,Converter,Setting>& rhs ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	SupportFunctionNewT<Number,Converter,Setting> SupportFunctionNewT<Number,Converter,Setting>::unite( const std::vector<SupportFunctionNewT<Number,Converter,Setting>>& SupportFunctionNewes ) {

	}

	template<typename Number, typename Converter, typename Setting>
	void SupportFunctionNewT<Number,Converter,Setting>::reduceRepresentation() {

	}

	template<typename Number, typename Converter, typename Setting>
	void SupportFunctionNewT<Number,Converter,Setting>::clear() {

	}

} // namespace hypro
