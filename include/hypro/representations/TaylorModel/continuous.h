/*
 * continuous.h
 *
 *  Created on: Dec 3, 2014
 *      Author: chen
 */

#pragma once

#include "ContinuousSetting.h"
#include "TaylorModel.h"

namespace hypro {

template <typename Number>
class Flowpipe {
  protected:
	TaylorModelVec<Number> tmvPre;
	TaylorModelVec<Number> tmv;
	Domain<Number> domain;

  public:
	Flowpipe();
	Flowpipe( const TaylorModelVec<Number>& tmv_input, const Domain<Number>& domain_input );
	Flowpipe( const Flowpipe<Number>& flowpipe );
	~Flowpipe();

	void clear();
	void enclosure( Range<Number>& range );
	void enclosure( Range<Number>& range, const exponent order );

	void composition( TaylorModelVec<Number>& result, Domain<Number>& fp_domain, const exponent order );

	template <class Setting>
	int next_picard( Flowpipe<Number>& result, const PolynomialODE<Number>& ode, const carl::Variable& t,
					 const double stepsize, const exponent order, const Range<Number>& estimation );

	Flowpipe<Number>& operator=( const Flowpipe<Number>& flowpipe );

	void output( std::ostream& os, const exponent order );
};

template <typename Number>
class ContinuousSystem {
  protected:
	PolynomialODE<Number> ode;
	Flowpipe<Number> initialSet;

  public:
	ContinuousSystem();
	ContinuousSystem( const PolynomialODE<Number>& ode_input, const Flowpipe<Number>& initialSet_input );
	ContinuousSystem( const ContinuousSystem<Number>& system );
	~ContinuousSystem();

	int reach_picard( std::list<Flowpipe<Number>>& result, const carl::Variable& t, const double time, const double stepsize,
					  const exponent order, const Range<Number>& estimation ) const;

	ContinuousSystem<Number>& operator=( const ContinuousSystem<Number>& system );

	void output( std::ostream& os, const exponent order );
};

template <typename Number>
void output_2D_interval_gnuplot( std::list<Flowpipe<Number>>& flowpipes, std::ofstream& os, const std::string& fileName,
								 const carl::Variable& axis_x, const carl::Variable& axis_y );

}  // namespace hypro

#include "continuous.tpp"