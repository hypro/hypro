
#pragma once

#ifndef INCL_FROM_GOHEADER
	static_assert(false, "This file may only be included indirectly by GeometricObject.h");
#endif

#include "../../config.h"
#include "util.h"
#include "SupportFunctionContent.h"
#include "../../util/templateDirections.h"

namespace hypro {

/**
 * @brief      Class wrapping the support function content.
 * @tparam     Number     The used number type.
 * @tparam     Converter  The used converter.
 * \ingroup geoState @{
 */
template <typename Number, typename Converter>
class SupportFunctionT : public GeometricObject<Number, SupportFunctionT<Number,Converter>> {
private:
	std::shared_ptr<SupportFunctionContent<Number>> content;

	mutable matrix_t<Number> mMatrix;
	mutable vector_t<Number> mVector;
	mutable bool mTemplateSet = false;

	SupportFunctionT<Number,Converter> (const std::shared_ptr<SupportFunctionContent<Number>> _source);

public:
	SupportFunctionT ();
	SupportFunctionT (const SupportFunctionT<Number,Converter>& _orig);
	SupportFunctionT (SF_TYPE _type, Number _radius, unsigned dimension );
	SupportFunctionT (const std::vector<Point<Number>>& _vertices);
	SupportFunctionT (const matrix_t<Number>& _directions, const vector_t<Number>& _distances);
	SupportFunctionT (const std::vector<Halfspace<Number>>& _planes);
	SupportFunctionT (SupportFunctionT<Number,Converter>&& other);
	SupportFunctionT (const matrix_t<Number>& _shapeMatrix);

	virtual ~SupportFunctionT();

	SupportFunctionT<Number,Converter>& operator=(SupportFunctionT<Number,Converter> _orig );

	EvaluationResult<Number> evaluate( const vector_t<Number>& _direction, bool useExact = true ) const;
	std::vector<EvaluationResult<Number>> multiEvaluate( const matrix_t<Number>& _directions, bool useExact = true ) const;

	std::size_t dimension() const;
	std::size_t size() const { return 0; } // TODO: Better implementation?
	static representation_name type() { return representation_name::support_function; }
	SF_TYPE sfType() const;
	unsigned depth() const;
	unsigned operationCount() const;

	// getter for the union types
	sumContent<Number>* summands() const;
	scaleContent<Number>* scaleParameters() const;
	trafoContent<Number>* linearTrafoParameters() const;
	unionContent<Number>* unionParameters() const;
	intersectionContent<Number>* intersectionParameters() const;
	PolytopeSupportFunction<Number>* polytope() const;
	BallSupportFunction<Number>* ball() const;
	EllipsoidSupportFunction<Number>* ellipsoid() const;

	matrix_t<Number> matrix() const;
	vector_t<Number> vector() const;

	void removeRedundancy();
	void reduceNumberRepresentation() {}
	std::vector<Point<Number>> vertices( const matrix_t<Number>& = matrix_t<Number>::Zero(0,0) ) const;
	Number supremum() const;
	SupportFunctionT<Number,Converter> project(const std::vector<std::size_t>& dimensions) const;
	SupportFunctionT<Number,Converter> linearTransformation( const matrix_t<Number>& A ) const;
	SupportFunctionT<Number,Converter> affineTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const;
	SupportFunctionT<Number,Converter> minkowskiSum( const SupportFunctionT<Number,Converter>& _rhs ) const;
	SupportFunctionT<Number,Converter> intersect( const SupportFunctionT<Number,Converter>& _rhs ) const;
	SupportFunctionT<Number,Converter> intersectHalfspace( const Halfspace<Number>& hs ) const;
	SupportFunctionT<Number,Converter> intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const;
	bool contains( const Point<Number>& _point ) const;
	bool contains( const vector_t<Number>& _point ) const;
	bool contains( const SupportFunctionT<Number, Converter>& rhs, std::size_t directions = defaultTemplateDirectionCount ) const;
	SupportFunctionT<Number,Converter> unite( const SupportFunctionT<Number,Converter>& _rhs ) const;
	static SupportFunctionT<Number,Converter> unite( const std::vector<SupportFunctionT<Number,Converter>>& _rhs );
	SupportFunctionT<Number,Converter> scale( const Number& _factor = 1 ) const;
	std::pair<bool, SupportFunctionT> satisfiesHalfspace( const Halfspace<Number>& rhs ) const;
	std::pair<bool, SupportFunctionT> satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const;
	bool empty() const;
	void print() const;
    void swap(SupportFunctionT<Number,Converter>& first, SupportFunctionT<Number,Converter>& second);

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

    friend std::ostream& operator<<( std::ostream& lhs, const SupportFunctionT<Number, Converter>& rhs ) {
#ifdef HYPRO_LOGGING
    	lhs << rhs.content << std::endl;
#endif
    	return lhs;
	}

	friend bool operator==(const SupportFunctionT<Number,Converter>& lhs, const SupportFunctionT<Number,Converter>& rhs) {
		return lhs.content == rhs.content;
	}

	std::vector<std::size_t> collectProjections() const;

private:
	void evaluateTemplate() const;
};

/** @} */

} //namespace hypro
#include "SupportFunction.tpp"
