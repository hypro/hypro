/*
 * TaylorModel.h
 *
 *  Created on: Sep 8, 2014
 *      Author: chen
 */

#pragma once

#include <vector>

#include <carl/interval/Interval.h>
#include <carl/core/MultivariatePolynomial.h>
#include <carl/core/VariablePool.h>

using namespace carl;

namespace hypro {

template<typename Number>
class Domain
{
protected:
	std::map<Variable, Interval<Number>> assignments;
	typedef std::pair<const Variable, Interval<Number>> assignment_type;

public:
	Domain();
	Domain(const Domain<Number> & domain);
	~Domain();

	void assign(const Variable & v, const Interval<Number> & I);
	bool find_assignment(Interval<Number> & I, const Variable & v) const;
	void clear();

	std::map<Variable, Interval<Number>> & get_assignments();

	Domain<Number> & operator = (const Domain<Number> & domain);

	template <typename N>
	friend std::ostream& operator << (std::ostream & os, const Domain<N> & domain);
};

template<typename Number>
class TaylorModelVec;

template<typename Number>
class Flowpipe;

template<typename Number>
class PolynomialODE
{
protected:
	std::map<Variable, MultivariatePolynomial<Interval<Number>>> assignments;
	typedef std::pair<const Variable, MultivariatePolynomial<Interval<Number>>> assignment_type;

public:
	PolynomialODE();
	PolynomialODE(const PolynomialODE<Number> & ode);
	~PolynomialODE();

	void assign(const Variable & v, const MultivariatePolynomial<Interval<Number>> & rhs);
	bool find_assignment(MultivariatePolynomial<Interval<Number>> & rhs, const Variable & v) const;

	std::map<Variable, MultivariatePolynomial<Interval<Number>>> & get_assignments();

	PolynomialODE<Number> & operator = (const PolynomialODE<Number> & ode);

	template <typename N>
	friend std::ostream& operator << (std::ostream & os, const PolynomialODE<N> & ode);

	friend class TaylorModelVec<Number>;
};


template<typename Number>
class TaylorModel
{
private:
	MultivariatePolynomial<Interval<Number>> expansion;
	Interval<Number> remainder;

protected:
	typedef std::vector<Term<Interval<Number>>> TermsType;
	typedef std::shared_ptr<const Monomial> MonomialType;

public:
	TaylorModel();				// empty Taylor model
	~TaylorModel();

	TaylorModel(const MultivariatePolynomial<Interval<Number>> & p, const Interval<Number> & r);
	TaylorModel(const MultivariatePolynomial<Interval<Number>> & p);
	TaylorModel(const Interval<Number> & I);
	TaylorModel(const TaylorModel<Number> & tm);
	TaylorModel(const std::initializer_list<Term<Interval<Number>> > & terms);
	TaylorModel(const std::initializer_list<Term<Interval<Number>> > & terms, const Interval<Number> & r);
	TaylorModel(const Term<Interval<Number>> & term);
	TaylorModel(Variable::Arg v);

	bool isZero() const;
	bool isConstant() const;
	bool isLinear() const;

	Interval<Number> rmConstantTerm();

	exponent tmOrder() const;

	TaylorModel<Number> pow(unsigned exp, Domain<Number> & domain, const exponent order) const;

	void checkConsistency() const;
	bool has(Variable::Arg v) const;

	void cutoff(const Interval<Number> & threshold, Domain<Number> & domain);
	void cutoff_nr(const Interval<Number> & threshold, Domain<Number> & domain);

	void truncation(const exponent order, Domain<Number> & domain);
	void truncation_nr(const exponent order);

	void enclosure(Interval<Number> & I, Domain<Number> & domain) const;
	void poly_enclosure(Interval<Number> & I, Domain<Number> & domain) const;

	void normalize(Domain<Number> & domain);

	TaylorModel<Number> & operator = (const TaylorModel<Number> & tm);

	TaylorModel<Number> & operator += (const TaylorModel<Number> & tm);
	TaylorModel<Number> & operator -= (const TaylorModel<Number> & tm);

	const TaylorModel<Number> operator + (const TaylorModel<Number> & tm) const;
	const TaylorModel<Number> operator - (const TaylorModel<Number> & tm) const;

	TaylorModel<Number> multiply(const Interval<Number> & I) const;
	TaylorModel<Number> multiply(const TaylorModel<Number> & tm, Domain<Number> & domain, const exponent order) const;
	TaylorModel<Number> multiply(const Term<Interval<Number>> & term, Domain<Number> & domain, const exponent order) const;
	TaylorModel<Number> multiply(Variable::Arg v, Domain<Number> & domain, const exponent order) const;

	void multiply_assign(const Interval<Number> & I);
	void multiply_assign(const TaylorModel<Number> & tm, Domain<Number> & domain, const exponent order);
	void multiply_assign(const Term<Interval<Number>> & term, Domain<Number> & domain, const exponent order);
	void multiply_assign(Variable::Arg v, Domain<Number> & domain, const exponent order);

	TaylorModel<Number> div(const Interval<Number> & I) const;
	void div_assign(const Interval<Number> & I);

	TaylorModel<Number> substitute(const std::map<Variable, TaylorModel<Number>> & substitutions, Domain<Number> & domain, const exponent order) const;
	TaylorModel<Number> substitute(const TaylorModelVec<Number> & substitutions, Domain<Number> & domain, const exponent order) const;

	TaylorModel<Number> derivative(Variable::Arg v, unsigned nth=1) const;
	void derivative_assign(Variable::Arg v, unsigned nth=1);

	TaylorModel<Number> LieDerivative(const PolynomialODE<Number> & ode) const;
	void LieDerivative_assign(const PolynomialODE<Number> & ode);

	TaylorModel<Number> integration(Variable::Arg v, const Interval<Number> & range_of_v);
	void integration_assign(Variable::Arg v, const Interval<Number> & range_of_v);

	template<typename N>
	friend std::ostream & operator << (std::ostream & os, const TaylorModel<N> & tm);

	friend class Flowpipe<Number>;
};



template<typename Number>
class Range
{
protected:
	std::map<Variable, Interval<Number>> assignments;
	typedef std::pair<const Variable, Interval<Number>> assignment_type;

public:
	Range();
	Range(const Range<Number> & range);
	~Range();

	void assign(const Variable & v, const Interval<Number> & I);
	bool find_assignment(Interval<Number> & I, const Variable & v) const;
	void clear();

	std::map<Variable, Interval<Number>> & get_assignments();

	Range<Number> & operator = (const Range<Number> & range);

	template <typename N>
	friend std::ostream& operator << (std::ostream & os, const Range<N> & range);
};

template<typename Number>
class Flowpipe;

// A vector of Taylor models, each component corresponds to a state variable.

template<typename Number>
class TaylorModelVec
{
//protected:
public:
	std::map<Variable, TaylorModel<Number>> tms;
	typedef std::pair<const Variable, TaylorModel<Number>> assignment_type;

public:
	TaylorModelVec();
	TaylorModelVec(const std::map<Variable, TaylorModel<Number>> & assignments);
	TaylorModelVec(Range<Number> & range);
	TaylorModelVec(const TaylorModelVec & tmv);
	~TaylorModelVec();

	void assign(const Variable & v, const TaylorModel<Number> & tm);
	bool find_assignment(TaylorModel<Number> & tm, const Variable & v) const;
	bool isEmpty() const;
	void clear();

	void rmConstantTerm(Range<Number> & constant);

	void cutoff(const Interval<Number> & threshold, Domain<Number> & domain);
	void cutoff_nr(const Interval<Number> & threshold, Domain<Number> & domain);

	void truncation(const exponent order, Domain<Number> & domain);
	void truncation_nr(const exponent order);

	void enclosure(Range<Number> & range, Domain<Number> & domain) const;

	TaylorModelVec<Number> & operator = (const TaylorModelVec<Number> & tmv);

	TaylorModelVec<Number> & operator += (const TaylorModelVec<Number> & tmv);
	TaylorModelVec<Number> & operator -= (const TaylorModelVec<Number> & tmv);

	const TaylorModelVec<Number> operator + (const TaylorModelVec<Number> & tmv) const;
	const TaylorModelVec<Number> operator - (const TaylorModelVec<Number> & tmv) const;

	TaylorModelVec<Number> substitute(const std::map<Variable, TaylorModel<Number>> & substitutions, Domain<Number> & domain, const exponent order) const;
	TaylorModelVec<Number> substitute(const TaylorModelVec<Number> & substitutions, Domain<Number> & domain, const exponent order) const;

	TaylorModelVec<Number> derivative(Variable::Arg v, unsigned nth=1) const;
	void derivative_assign(Variable::Arg v, unsigned nth=1);

	TaylorModelVec<Number> LieDerivative(const PolynomialODE<Number> & ode) const;
	void LieDerivative_assign(const PolynomialODE<Number> & ode);

	TaylorModelVec<Number> integration(Variable::Arg v, const Interval<Number> & range_of_v);
	void integration_assign(Variable::Arg v, const Interval<Number> & range_of_v);


	TaylorModelVec<Number> Picard(const TaylorModelVec<Number> & x0, const PolynomialODE<Number> & ode, Domain<Number> & domain, Variable::Arg t, const Interval<Number> & range_of_t, const exponent order) const;
	void Picard_assign(const TaylorModelVec<Number> & x0, const PolynomialODE<Number> & ode, Domain<Number> & domain, Variable::Arg t, const Interval<Number> & range_of_t, const exponent order);


	template<typename N>
	friend std::ostream & operator << (std::ostream & os, const TaylorModelVec<N> & tmv);

	friend class TaylorModel<Number>;
	friend class Flowpipe<Number>;
};

} // namespace

#include "TaylorModel.tpp"