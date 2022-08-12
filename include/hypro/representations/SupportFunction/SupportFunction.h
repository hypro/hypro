
#pragma once

#ifndef INCL_FROM_GOHEADER
static_assert( false, "This file may only be included indirectly by GeometricObjectBase.h" );
#endif

#include "../../config.h"
#include "../../util/templateDirections.h"
#include "SupportFunctionContent.h"
#include "SupportFunctionSetting.h"
#include "util.h"

namespace hypro {

/**
 * @brief      Class wrapping the support function content.
 * @tparam     Number     The used number type.
 * @tparam     Converter  The used converter.
 * \ingroup geoState @{
 */
template <typename Number, typename Converter, typename Setting>
class SupportFunctionT : private GeometricObjectBase {
  public:
	typedef Setting Settings;
	typedef Number NumberType;
	static constexpr auto type_enum = representation_name::support_function;

  private:
	std::shared_ptr<SupportFunctionContent<Number, Setting>> content;

	mutable matrix_t<Number> mMatrix;
	mutable vector_t<Number> mVector;
	mutable bool mTemplateSet = false;

	SupportFunctionT( const std::shared_ptr<SupportFunctionContent<Number, Setting>> _source );

  public:
	SupportFunctionT();
	SupportFunctionT( const SupportFunctionT& _orig );
	SupportFunctionT( SF_TYPE _type, Number _radius, unsigned dimension );
	SupportFunctionT( const std::vector<Point<Number>>& _vertices );
	SupportFunctionT( const matrix_t<Number>& _directions, const vector_t<Number>& _distances, bool overrideReduction = false );
	SupportFunctionT( const std::vector<Halfspace<Number>>& _planes );
	SupportFunctionT( SupportFunctionT&& other );
	SupportFunctionT( const matrix_t<Number>& _shapeMatrix );
	SupportFunctionT( const std::vector<carl::Interval<Number>>& inBox );

	virtual ~SupportFunctionT();

	SupportFunctionT<Number, Converter, Setting>& operator=( SupportFunctionT<Number, Converter, Setting> _orig );

	EvaluationResult<Number> evaluate( const vector_t<Number>& _direction, bool useExact = true ) const;
	std::vector<EvaluationResult<Number>> multiEvaluate( const matrix_t<Number>& _directions, bool useExact = true ) const;

	static SupportFunctionT Empty() {
		auto res = SupportFunctionT();
		res.setEmptyState( SETSTATE::EMPTY );
		return res;
	}

	std::size_t dimension() const;
	std::size_t size() const { return 0; }	// TODO: Better implementation?
	static representation_name type() { return representation_name::support_function; }
	SF_TYPE sfType() const;
	unsigned depth() const;
	unsigned operationCount() const;

	// getter for the union types
	sumContent<Number, Setting>* summands() const;
	scaleContent<Number, Setting>* scaleParameters() const;
	trafoContent<Number, Setting>* linearTrafoParameters() const;
	unionContent<Number, Setting>* unionParameters() const;
	intersectionContent<Number, Setting>* intersectionParameters() const;
	PolytopeSupportFunction<Number, Setting>* polytope() const;
	BallSupportFunction<Number>* ball() const;
	BoxSupportFunction<Number, Setting>* box() const;
	EllipsoidSupportFunction<Number>* ellipsoid() const;

	matrix_t<Number> matrix() const;
	vector_t<Number> vector() const;

	void removeRedundancy() const;
	void reduceNumberRepresentation() const {}
	std::vector<Point<Number>> vertices( const matrix_t<Number>& = matrix_t<Number>::Zero( 0, 0 ) ) const;
	std::vector<Point<Number>> vertices( const std::vector<vector_t<Number>>& additionalDirections ) const;
	Number supremum() const;
	SupportFunctionT projectOn( const std::vector<std::size_t>& dimensions ) const;
	SupportFunctionT assignIntervals( const std::map<std::size_t, carl::Interval<Number>>& ) const {
		WARN( "hypro", "Not implemented." );
		return *this;
	}
	SupportFunctionT linearTransformation( const matrix_t<Number>& A ) const;
	SupportFunctionT affineTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const;
	SupportFunctionT minkowskiSum( const SupportFunctionT& _rhs ) const;
	SupportFunctionT intersect( const SupportFunctionT& _rhs ) const;
	SupportFunctionT intersectHalfspace( const Halfspace<Number>& hs ) const;
	SupportFunctionT intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const;
	bool contains( const Point<Number>& _point ) const;
	bool contains( const vector_t<Number>& _point ) const;
	bool contains( const SupportFunctionT& rhs ) const;
	bool contains( const SupportFunctionT& rhs, std::size_t directions ) const;
	SupportFunctionT unite( const SupportFunctionT& _rhs ) const;
	static SupportFunctionT unite( const std::vector<SupportFunctionT>& _rhs );
	SupportFunctionT scale( const Number& _factor = 1 ) const;
	std::pair<CONTAINMENT, SupportFunctionT> satisfiesHalfspace( const Halfspace<Number>& rhs ) const;
	std::pair<CONTAINMENT, SupportFunctionT> satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const;
	/**
	 * @brief      Reduces the support function. This is Settings-dependent and can result in a templated evaluation.
	 */
	void reduceRepresentation();
	bool empty() const;
	void print() const;
	void swap( SupportFunctionT& first, SupportFunctionT& second );

	/**
	 * forces the topmost chain of linear transformations to be reduced to a single lin.trans
	 * @return reduced SF
	 */
	void forceLinTransReduction();

	/**
	 *
	 * @return number of mv multiplications needed for a single evaluation on the SF
	 */
	unsigned multiplicationsPerEvaluation() const;

	/**
	 * @brief      Cleans up optimizer context data when joining threads in a multithreaded environment.
	 * Used to avoid memory leaks when threads which created the support function are joined.
	 */
	void cleanUp() const;

	std::string getDotRepresentation() const;

	friend std::ostream& operator<<( std::ostream& lhs, const SupportFunctionT<Number, Converter, Setting>& rhs ) {
#ifdef HYPRO_LOGGING
		lhs << rhs.content << std::endl;
#endif
		return lhs;
	}

	friend bool operator==( const SupportFunctionT<Number, Converter, Setting>& lhs, const SupportFunctionT<Number, Converter, Setting>& rhs ) {
		return lhs.content == rhs.content;
	}

	std::vector<std::size_t> collectProjections() const;

	const SupportFunctionT& evaluateTemplate( std::size_t directionCount = defaultTemplateDirectionCount, bool force = false ) const;

  private:
	std::shared_ptr<SupportFunctionContent<Number, Setting>>& rGetContent() {
		return content;
	}
};

/** @} */

}  // namespace hypro
#include "SupportFunction.tpp"
