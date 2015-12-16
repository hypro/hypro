/**
 * Wrapper class for SupportFunctionContent for easier use.
 * @file   SupportFunction.h
 * @author Simon Froitzheim
 *
 * @since      2015-11-23
 * @version    2015-11-23
 */

#pragma once


#include "SupportFunctionContent.h"

namespace hypro {




template <typename Number>
class SupportFunction {
    private:
           std::shared_ptr<SupportFunctionContent<Number>> content;
           SupportFunction<Number> (const std::shared_ptr<SupportFunctionContent<Number>> _source);
           

    public:
        SupportFunction ();
        SupportFunction (const SupportFunction<Number>& _orig);
        SupportFunction (SF_TYPE _type, Number _radius );
        SupportFunction (SF_TYPE _type, const matrix_t<Number>& _directions, const vector_t<Number>& _distances);
        SupportFunction (SF_TYPE _type, const std::vector<Hyperplane<Number>>& _planes);
        SupportFunction (SupportFunction<Number>&& other);


        virtual ~SupportFunction();

        SupportFunction<Number>& operator=(SupportFunction<Number> _orig );

        evaluationResult<Number> evaluate( const vector_t<Number>& _direction ) const;
	vector_t<Number> multiEvaluate( const matrix_t<Number>& _directions ) const;

	std::size_t dimension() const;
	SF_TYPE type() const;

	// getter for the union types
	sumContent<Number>* summands() const;
	scaleContent<Number>* scaleParameters() const;
	trafoContent<Number>* linearTrafoParameters() const;
	unionContent<Number>* unionParameters() const;
	intersectionContent<Number>* intersectionParameters() const;
	PolytopeSupportFunction<Number>* polytope() const;
	BallSupportFunction<Number>* ball() const;

	SupportFunction<Number> linearTransformation( const matrix_t<Number>& _A, const vector_t<Number>& _b ) const;
	SupportFunction<Number> minkowskiSum( SupportFunction<Number>& _rhs ) const;
	SupportFunction<Number> intersect( SupportFunction<Number>& _rhs ) const;
	bool contains( const Point<Number>& _point ) const;
	bool contains( const vector_t<Number>& _point ) const;
	SupportFunction<Number> unite( SupportFunction<Number>& _rhs ) const;

	SupportFunction<Number> scale( const Number& _factor = 1 ) const;
	bool empty() const;

	void print() const;
        
        void swap(SupportFunction<Number>& first, SupportFunction<Number>& second);

};





} //namespace

#include "SupportFunction.tpp"