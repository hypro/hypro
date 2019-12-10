
#pragma once

#ifndef INCL_FROM_GOHEADER
static_assert( false, "This file may only be included indirectly by GeometricObject.h" );
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
class SupportFunctionT : public GeometricObject<Number, SupportFunctionT<Number, Converter, Setting>> {
  public:
	typedef Setting Settings;

  private:
	std::shared_ptr<SupportFunctionContent<Number, Setting>> content;

	mutable matrix_t<Number> mMatrix;
	mutable vector_t<Number> mVector;
	mutable bool mTemplateSet = false;

	SupportFunctionT<Number, Converter, Setting>( const std::shared_ptr<SupportFunctionContent<Number, Setting>> _source );

  public:
	SupportFunctionT();
	SupportFunctionT( const SupportFunctionT<Number, Converter, Setting>& _orig );
	SupportFunctionT( SF_TYPE _type, Number _radius, unsigned dimension );
	SupportFunctionT( const std::vector<Point<Number>>& _vertices );
	SupportFunctionT( const matrix_t<Number>& _directions, const vector_t<Number>& _distances, bool overrideReduction = false );
	SupportFunctionT( const std::vector<Halfspace<Number>>& _planes );
	SupportFunctionT( SupportFunctionT<Number, Converter, Setting>&& other );
	SupportFunctionT( const matrix_t<Number>& _shapeMatrix );
	SupportFunctionT( const std::vector<carl::Interval<Number>>& inBox );

	virtual ~SupportFunctionT();

	SupportFunctionT<Number, Converter, Setting>& operator=( SupportFunctionT<Number, Converter, Setting> _orig );

	EvaluationResult<Number> evaluate( const vector_t<Number>& _direction, bool useExact = true ) const;
	std::vector<EvaluationResult<Number>> multiEvaluate( const matrix_t<Number>& _directions, bool useExact = true ) const;

	std::size_t dimension() const;
	std::size_t size() const { return 0; }  // TODO: Better implementation?
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

	void removeRedundancy();
	void reduceNumberRepresentation() {}
	std::vector<Point<Number>> vertices( const matrix_t<Number>& = matrix_t<Number>::Zero( 0, 0 ) ) const;
	std::vector<Point<Number>> vertices( const std::vector<vector_t<Number>>& additionalDirections ) const;
	Number supremum() const;
	SupportFunctionT<Number, Converter, Setting> project( const std::vector<std::size_t>& dimensions ) const;
	SupportFunctionT<Number, Converter, Setting> linearTransformation( const matrix_t<Number>& A ) const;
	SupportFunctionT<Number, Converter, Setting> affineTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const;
	SupportFunctionT<Number, Converter, Setting> minkowskiSum( const SupportFunctionT<Number, Converter, Setting>& _rhs ) const;
	SupportFunctionT<Number, Converter, Setting> intersect( const SupportFunctionT<Number, Converter, Setting>& _rhs ) const;
	SupportFunctionT<Number, Converter, Setting> intersectHalfspace( const Halfspace<Number>& hs ) const;
	SupportFunctionT<Number, Converter, Setting> intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const;
	bool contains( const Point<Number>& _point ) const;
	bool contains( const vector_t<Number>& _point ) const;
	bool contains( const SupportFunctionT<Number, Converter, Setting>& rhs ) const;
	bool contains( const SupportFunctionT<Number, Converter, Setting>& rhs, std::size_t directions ) const;
	SupportFunctionT<Number, Converter, Setting> unite( const SupportFunctionT<Number, Converter, Setting>& _rhs ) const;
	static SupportFunctionT<Number, Converter, Setting> unite( const std::vector<SupportFunctionT<Number, Converter, Setting>>& _rhs );
	SupportFunctionT<Number, Converter, Setting> scale( const Number& _factor = 1 ) const;
	std::pair<CONTAINMENT, SupportFunctionT> satisfiesHalfspace( const Halfspace<Number>& rhs ) const;
	std::pair<CONTAINMENT, SupportFunctionT> satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const;
	/**
	 * @brief      Reduces the support function. This is Settings-dependent and can result in a templated evaluation.
	 */
	void reduceRepresentation();
	bool empty() const;
	void print() const;
	void swap( SupportFunctionT<Number, Converter, Setting>& first, SupportFunctionT<Number, Converter, Setting>& second );

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

	const SupportFunctionT<Number, Converter, Setting>& evaluateTemplate( std::size_t directionCount = defaultTemplateDirectionCount, bool force = false ) const;

  private:
	std::shared_ptr<SupportFunctionContent<Number, Setting>>& rGetContent() {
		return content;
	}
};

/** @} */

}  //namespace hypro
#include "SupportFunction.tpp"
