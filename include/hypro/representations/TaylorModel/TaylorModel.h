/*
 * TaylorModel.h
 *
 *  Created on: Sep 8, 2014
 *      Author: chen
 */

#pragma once

#include <carl/core/MultivariatePolynomial.h>
#include <carl/core/VariablePool.h>
#include <carl/interval/Interval.h>
#include <carl/interval/set_theory.h>
#include <vector>

using namespace carl;

namespace hypro {

template <typename Number>
class Domain {
  protected:
	std::map<carl::Variable, carl::Interval<Number>> assignments;
	using assignment_type = std::pair<const carl::Variable, carl::Interval<Number>>;

  public:
	Domain();
	Domain( const Domain<Number>& domain );
	~Domain();

	void assign( const carl::Variable& v, const carl::Interval<Number>& I );
	bool find_assignment( carl::Interval<Number>& I, const carl::Variable& v ) const;
	void clear();

	std::map<carl::Variable, carl::Interval<Number>>& get_assignments();

	Domain<Number>& operator=( const Domain<Number>& domain );

	template <typename N>
	friend std::ostream& operator<<( std::ostream& os, const Domain<N>& domain );
};

template <typename Number>
class TaylorModelVec;

template <typename Number>
class Flowpipe;

template <typename Number>
class PolynomialODE {
  protected:
	std::map<carl::Variable, MultivariatePolynomial<carl::Interval<Number>>> assignments;
	using assignment_type = std::pair<const carl::Variable, MultivariatePolynomial<carl::Interval<Number>>>;

  public:
	PolynomialODE();
	PolynomialODE( const PolynomialODE<Number>& ode );
	~PolynomialODE();

	void assign( const carl::Variable& v, const MultivariatePolynomial<carl::Interval<Number>>& rhs );
	bool find_assignment( MultivariatePolynomial<carl::Interval<Number>>& rhs, const carl::Variable& v ) const;

	std::map<carl::Variable, MultivariatePolynomial<carl::Interval<Number>>>& get_assignments();

	PolynomialODE<Number>& operator=( const PolynomialODE<Number>& ode );

	template <typename N>
	friend std::ostream& operator<<( std::ostream& os, const PolynomialODE<N>& ode );

	friend class TaylorModelVec<Number>;
};

template <typename Number>
class TaylorModel {
  private:
	MultivariatePolynomial<carl::Interval<Number>> expansion;
	carl::Interval<Number> remainder;

  protected:
	using TermsType = std::vector<Term<carl::Interval<Number>>>;
	using MonomialType = std::shared_ptr<const Monomial>;

  public:
	TaylorModel();	// empty Taylor model
	~TaylorModel();

	TaylorModel( const MultivariatePolynomial<carl::Interval<Number>>& p, const carl::Interval<Number>& r );
	explicit TaylorModel( const MultivariatePolynomial<carl::Interval<Number>>& p );
	explicit TaylorModel( const carl::Interval<Number>& I );
	explicit TaylorModel( const TaylorModel<Number>& tm );
	explicit TaylorModel( const std::initializer_list<Term<carl::Interval<Number>>>& terms );
	TaylorModel( const std::initializer_list<Term<carl::Interval<Number>>>& terms, const carl::Interval<Number>& r );
	explicit TaylorModel( const Term<carl::Interval<Number>>& term );
	explicit TaylorModel( carl::Variable::Arg v );

	bool isZero() const;
	bool isConstant() const;
	bool isLinear() const;

	carl::Interval<Number> rmConstantTerm();

	exponent tmOrder() const;

	TaylorModel<Number> pow( unsigned exp, Domain<Number>& domain, const exponent order ) const;

	void checkConsistency() const;
	bool has( carl::Variable::Arg v ) const;

	void cutoff( const carl::Interval<Number>& threshold, Domain<Number>& domain );
	void cutoff_nr( const carl::Interval<Number>& threshold, Domain<Number>& domain );

	void truncation( const exponent order, Domain<Number>& domain );
	void truncation_nr( const exponent order );

	void enclosure( carl::Interval<Number>& I, Domain<Number>& domain ) const;
	void poly_enclosure( carl::Interval<Number>& I, Domain<Number>& domain ) const;

	void normalize( Domain<Number>& domain );

	TaylorModel<Number>& operator=( const TaylorModel<Number>& tm );

	TaylorModel<Number>& operator+=( const TaylorModel<Number>& tm );
	TaylorModel<Number>& operator-=( const TaylorModel<Number>& tm );

	const TaylorModel<Number> operator+( const TaylorModel<Number>& tm ) const;
	const TaylorModel<Number> operator-( const TaylorModel<Number>& tm ) const;

	TaylorModel<Number> multiply( const carl::Interval<Number>& I ) const;
	TaylorModel<Number> multiply( const TaylorModel<Number>& tm, Domain<Number>& domain, const exponent order ) const;
	TaylorModel<Number> multiply( const Term<carl::Interval<Number>>& term, Domain<Number>& domain,
								  const exponent order ) const;
	TaylorModel<Number> multiply( carl::Variable::Arg v, Domain<Number>& domain, const exponent order ) const;

	void multiply_assign( const carl::Interval<Number>& I );
	void multiply_assign( const TaylorModel<Number>& tm, Domain<Number>& domain, const exponent order );
	void multiply_assign( const Term<carl::Interval<Number>>& term, Domain<Number>& domain, const exponent order );
	void multiply_assign( carl::Variable::Arg v, Domain<Number>& domain, const exponent order );

	TaylorModel<Number> div( const carl::Interval<Number>& I ) const;
	void div_assign( const carl::Interval<Number>& I );

	TaylorModel<Number> substitute( const std::map<carl::Variable, TaylorModel<Number>>& substitutions,
									Domain<Number>& domain, const exponent order ) const;
	TaylorModel<Number> substitute( const TaylorModelVec<Number>& substitutions, Domain<Number>& domain,
									const exponent order ) const;

	TaylorModel<Number> derivative( carl::Variable::Arg v, unsigned nth = 1 ) const;
	void derivative_assign( carl::Variable::Arg v, unsigned nth = 1 );

	TaylorModel<Number> LieDerivative( const PolynomialODE<Number>& ode ) const;
	void LieDerivative_assign( const PolynomialODE<Number>& ode );

	TaylorModel<Number> integration( carl::Variable::Arg v, const carl::Interval<Number>& range_of_v );
	void integration_assign( carl::Variable::Arg v, const carl::Interval<Number>& range_of_v );

	template <typename N>
	friend std::ostream& operator<<( std::ostream& os, const TaylorModel<N>& tm );

	friend class Flowpipe<Number>;
};

template <typename Number>
class Range {
  protected:
	std::map<carl::Variable, carl::Interval<Number>> assignments;
	using assignment_type = std::pair<const carl::Variable, carl::Interval<Number>>;

  public:
	Range();
	Range( const Range<Number>& range );
	~Range();

	void assign( const carl::Variable& v, const carl::Interval<Number>& I );
	bool find_assignment( carl::Interval<Number>& I, const carl::Variable& v ) const;
	void clear();

	std::map<carl::Variable, carl::Interval<Number>>& get_assignments();

	Range<Number>& operator=( const Range<Number>& range );

	template <typename N>
	friend std::ostream& operator<<( std::ostream& os, const Range<N>& range );
};

template <typename Number>
class Flowpipe;

// A vector of Taylor models, each component corresponds to a state variable.

template <typename Number>
class TaylorModelVec {
	// protected:
  public:
	std::map<carl::Variable, TaylorModel<Number>> tms;
	using assignment_type = std::pair<const carl::Variable, TaylorModel<Number>>;

  public:
	TaylorModelVec();
	TaylorModelVec( const std::map<carl::Variable, TaylorModel<Number>>& assignments );
	TaylorModelVec( Range<Number>& range );
	TaylorModelVec( const TaylorModelVec& tmv );
	~TaylorModelVec();

	void assign( const carl::Variable& v, const TaylorModel<Number>& tm );
	bool find_assignment( TaylorModel<Number>& tm, const carl::Variable& v ) const;
	bool isEmpty() const;
	void clear();

	void rmConstantTerm( Range<Number>& constant );

	void cutoff( const carl::Interval<Number>& threshold, Domain<Number>& domain );
	void cutoff_nr( const carl::Interval<Number>& threshold, Domain<Number>& domain );

	void truncation( const exponent order, Domain<Number>& domain );
	void truncation_nr( const exponent order );

	void enclosure( Range<Number>& range, Domain<Number>& domain ) const;

	TaylorModelVec<Number>& operator=( const TaylorModelVec<Number>& tmv );

	TaylorModelVec<Number>& operator+=( const TaylorModelVec<Number>& tmv );
	TaylorModelVec<Number>& operator-=( const TaylorModelVec<Number>& tmv );

	const TaylorModelVec<Number> operator+( const TaylorModelVec<Number>& tmv ) const;
	const TaylorModelVec<Number> operator-( const TaylorModelVec<Number>& tmv ) const;

	TaylorModelVec<Number> substitute( const std::map<carl::Variable, TaylorModel<Number>>& substitutions,
									   Domain<Number>& domain, const exponent order ) const;
	TaylorModelVec<Number> substitute( const TaylorModelVec<Number>& substitutions, Domain<Number>& domain,
									   const exponent order ) const;

	TaylorModelVec<Number> derivative( carl::Variable::Arg v, unsigned nth = 1 ) const;
	void derivative_assign( carl::Variable::Arg v, unsigned nth = 1 );

	TaylorModelVec<Number> LieDerivative( const PolynomialODE<Number>& ode ) const;
	void LieDerivative_assign( const PolynomialODE<Number>& ode );

	TaylorModelVec<Number> integration( carl::Variable::Arg v, const carl::Interval<Number>& range_of_v );
	void integration_assign( carl::Variable::Arg v, const carl::Interval<Number>& range_of_v );

	TaylorModelVec<Number> Picard( const TaylorModelVec<Number>& x0, const PolynomialODE<Number>& ode,
								   Domain<Number>& domain, carl::Variable::Arg t, const carl::Interval<Number>& range_of_t,
								   const exponent order ) const;
	void Picard_assign( const TaylorModelVec<Number>& x0, const PolynomialODE<Number>& ode, Domain<Number>& domain,
						carl::Variable::Arg t, const carl::Interval<Number>& range_of_t, const exponent order );

	template <typename N>
	friend std::ostream& operator<<( std::ostream& os, const TaylorModelVec<N>& tmv );

	friend class TaylorModel<Number>;
	friend class Flowpipe<Number>;
};

}  // namespace hypro

#include "TaylorModel.tpp"
