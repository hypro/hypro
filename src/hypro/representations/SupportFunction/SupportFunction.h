/**
 * Wrapper class for SupportFunctionContent for easier use.
 * @file   SupportFunction.h
 * @author Simon Froitzheim
 *
 * @since      2015-11-23
 * @version    2015-12-16
 */

#pragma once

#ifndef INCL_FROM_GOHEADER
	static_assert(false, "This file may only be included indirectly by GeometricObject.h");
#endif

#include "util.h"
#include "SupportFunctionContent.h"
#include "../../util/helperFunctions.h"
#include "../../datastructures/hybridAutomata/Location.h"
#include "../../algorithms/convexHull/vertexEnumeration.h"
#include <list>

namespace hypro {

template <typename Number, typename Converter>
class SupportFunctionT {
private:
	std::shared_ptr<SupportFunctionContent<Number>> content;
	SupportFunctionT<Number,Converter> (const std::shared_ptr<SupportFunctionContent<Number>> _source);

	mutable matrix_t<Number> mMatrix;
	mutable vector_t<Number> mVector;
	mutable bool mTemplateSet = false;

public:
	SupportFunctionT ();
	SupportFunctionT (const SupportFunctionT<Number,Converter>& _orig);
	SupportFunctionT (SF_TYPE _type, Number _radius );
	SupportFunctionT (const std::vector<Point<Number>>& _vertices);
	SupportFunctionT (const matrix_t<Number>& _directions, const vector_t<Number>& _distances);
	SupportFunctionT (const std::vector<Halfspace<Number>>& _planes);
	SupportFunctionT (SupportFunctionT<Number,Converter>&& other);
	SupportFunctionT (const matrix_t<Number>& _shapeMatrix);

	virtual ~SupportFunctionT();

	SupportFunctionT<Number,Converter>& operator=(SupportFunctionT<Number,Converter> _orig );

	EvaluationResult<Number> evaluate( const vector_t<Number>& _direction ) const;
	std::vector<EvaluationResult<Number>> multiEvaluate( const matrix_t<Number>& _directions ) const;

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
	std::vector<Point<Number>> vertices(const Location<Number>* loc = nullptr) const;
	Number supremum() const;
	SupportFunctionT<Number,Converter> project(const std::vector<unsigned>& dimensions) const;
	SupportFunctionT<Number,Converter> linearTransformation( std::shared_ptr<lintrafoParameters<Number>> parameters ) const;
	SupportFunctionT<Number,Converter> minkowskiSum( const SupportFunctionT<Number,Converter>& _rhs ) const;
	SupportFunctionT<Number,Converter> intersect( SupportFunctionT<Number,Converter>& _rhs ) const;
	SupportFunctionT<Number,Converter> intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const;
	bool contains( const Point<Number>& _point ) const;
	bool contains( const vector_t<Number>& _point ) const;
	bool contains( const SupportFunctionT<Number, Converter>& rhs, unsigned directions = 8 ) const;
	SupportFunctionT<Number,Converter> unite( const SupportFunctionT<Number,Converter>& _rhs ) const;
	SupportFunctionT<Number,Converter> scale( const Number& _factor = 1 ) const;
	//std::pair<bool, SupportFunctionT> satisfiesHalfspace( const vector_t<Number>& normal, const Number& offset ) const;
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
    	lhs << rhs.content << std::endl;
    	return lhs;
	}

	friend bool operator==(const SupportFunctionT<Number,Converter>& lhs, const SupportFunctionT<Number,Converter>& rhs) {
		return lhs.content == rhs.content;
	}

	std::list<unsigned> collectProjections() const;

private:
	void evaluateTemplate() const;
};

} //namespace hypro
#include "SupportFunction.tpp"
