/**
 * Wrapper class for SupportFunctionContent for easier use.
 * @file   SupportFunction.h
 * @author Simon Froitzheim
 *
 * @since      2015-11-23
 * @version    2015-12-16
 */

#pragma once

#include "SupportFunctionContent.h"

namespace hypro {

template <typename Number, typename Converter>
class SupportFunctionT {
    private:
           std::shared_ptr<SupportFunctionContent<Number>> content;
           SupportFunctionT<Number,Converter> (const std::shared_ptr<SupportFunctionContent<Number>> _source);


    public:
        SupportFunctionT ();
        SupportFunctionT (const SupportFunctionT<Number,Converter>& _orig);
        SupportFunctionT (SF_TYPE _type, Number _radius );
        SupportFunctionT (SF_TYPE _type, const matrix_t<Number>& _directions, const vector_t<Number>& _distances);
        SupportFunctionT (SF_TYPE _type, const std::vector<Hyperplane<Number>>& _planes);
        SupportFunctionT (SupportFunctionT<Number,Converter>&& other);


        virtual ~SupportFunctionT();

        SupportFunctionT<Number,Converter>& operator=(SupportFunctionT<Number,Converter> _orig );

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

	SupportFunctionT<Number,Converter> linearTransformation( const matrix_t<Number>& _A, const vector_t<Number>& _b ) const;
	SupportFunctionT<Number,Converter> minkowskiSum( SupportFunctionT<Number,Converter>& _rhs ) const;
	SupportFunctionT<Number,Converter> intersect( SupportFunctionT<Number,Converter>& _rhs ) const;
	bool contains( const Point<Number>& _point ) const;
	bool contains( const vector_t<Number>& _point ) const;
	SupportFunctionT<Number,Converter> unite( SupportFunctionT<Number,Converter>& _rhs ) const;

	SupportFunctionT<Number,Converter> scale( const Number& _factor = 1 ) const;
	bool empty() const;

	void print() const;

    void swap(SupportFunctionT<Number,Converter>& first, SupportFunctionT<Number,Converter>& second);

};

} //namespace

#include "SupportFunction.tpp"