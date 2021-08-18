/*
 * continuous.cpp
 *
 *  Created on: Dec 3, 2014
 *      Author: chen
 */

#include "continuous.h"

namespace hypro {

template <typename Number>
Flowpipe<Number>::Flowpipe() {
}

template <typename Number>
Flowpipe<Number>::Flowpipe( const TaylorModelVec<Number>& tmv_input, const Domain<Number>& domain_input ) {
	tmv = tmv_input;
	domain = domain_input;
}

template <typename Number>
Flowpipe<Number>::Flowpipe( const Flowpipe<Number>& flowpipe ) {
	tmvPre = flowpipe.tmvPre;
	tmv = flowpipe.tmv;
	domain = flowpipe.domain;
}

template <typename Number>
Flowpipe<Number>::~Flowpipe() {
}

template <typename Number>
void Flowpipe<Number>::clear() {
	tmvPre.clear();
	tmv.clear();
}

template <typename Number>
void Flowpipe<Number>::enclosure( Range<Number>& range ) {
	if ( tmvPre.isEmpty() ) {
		tmv.enclosure( range, domain );
	} else {
		exponent maxOrder = 0;

		for ( auto iter = tmv.tms.begin(); iter != tmv.tms.end(); ++iter ) {
			exponent order = iter->second.tmOrder();

			if ( order > maxOrder ) {
				maxOrder = order;
			}
		}

		TaylorModelVec<Number> tmvTemp = tmvPre.substitute( tmv, domain, maxOrder );
		tmvTemp.enclosure( range, domain );
	}
}

template <typename Number>
void Flowpipe<Number>::enclosure( Range<Number>& range, const exponent order ) {
	if ( tmvPre.isEmpty() ) {
		tmv.enclosure( range, domain );
	} else {
		TaylorModelVec<Number> tmvTemp = tmvPre.substitute( tmv, domain, order );
		tmvTemp.enclosure( range, domain );
	}
}

template <typename Number>
void Flowpipe<Number>::composition( TaylorModelVec<Number>& result, Domain<Number>& fp_domain, const exponent order ) {
	if ( tmvPre.isEmpty() ) {
		result = tmv;
		fp_domain = domain;
	} else {
		result = tmvPre.substitute( tmv, domain, order );
		fp_domain = domain;
	}
}

template <typename Number>
template <class Setting>
int Flowpipe<Number>::next_picard( Flowpipe<Number>& result, const PolynomialODE<Number>& ode, const carl::Variable& t,
								   const double stepsize, const exponent order, const Range<Number>& estimation ) {
	// evaluate the the local initial set Xl
	carl::Interval<Number> intStepEnd( stepsize );
	TaylorModel<Number> tmStepEnd( intStepEnd );

	carl::Interval<Number> intZero( 0 );
	carl::Interval<Number> intUnit( -1.0, 1.0 );

	TaylorModelVec<Number> Xl;

	if ( tmvPre.isEmpty() ) {
		TaylorModelVec<Number> evaluation;
		std::map<carl::Variable, carl::Interval<Number>>& domain_assignments = domain.get_assignments();

		for ( auto iter = domain_assignments.begin(); iter != domain_assignments.end(); ++iter ) {
			TaylorModel<Number> tmTemp( iter->first );
			evaluation.assign( iter->first, tmTemp );
		}

		evaluation.assign( t, tmStepEnd );

		Xl = tmv.substitute( evaluation, domain, order );
	} else {
		TaylorModelVec<Number> evaluation;
		Domain<Number> dummy_domain;

		for ( auto iter = tmv.tms.begin(); iter != tmv.tms.end(); ++iter ) {
			TaylorModel<Number> tmTemp( iter->first );
			evaluation.assign( iter->first, tmTemp );

			dummy_domain.assign( iter->first, intUnit );
		}

		evaluation.assign( t, tmStepEnd );

		Xl = tmvPre.substitute( evaluation, dummy_domain, order );
	}

	Range<Number> center_of_Xl;
	Xl.rmConstantTerm( center_of_Xl );

	TaylorModelVec<Number> tmvCenter( center_of_Xl );

	if ( !tmvPre.isEmpty() ) {
		Xl = Xl.substitute( tmv, domain, order );
	}

	Range<Number> range_of_Xl;
	Xl.enclosure( range_of_Xl, domain );

	// compute the preconditioning factors
	TaylorModelVec<Number> new_tmvPre;

	carl::Interval<Number> intStep( 0.0, stepsize );

	Domain<Number> localInitial;
	localInitial.assign( t, intStep );

	std::map<carl::Variable, carl::Interval<Number>>& assignments = range_of_Xl.get_assignments();

	auto iter1 = assignments.begin();
	auto iter2 = Xl.tms.begin();

	for ( ; iter1 != assignments.end(); ++iter1, ++iter2 ) {
		Number magnitude = iter1->second.magnitude();
		carl::Interval<Number> intMagnitude( magnitude );

		TaylorModel<Number> tmTemp( { (carl::Interval<Number>)intMagnitude * ( iter1->first ) } );

		new_tmvPre.assign( iter1->first, tmTemp );

		if ( !intMagnitude.contains( intZero ) ) {
			iter2->second.div_assign( intMagnitude );
		}

		localInitial.assign( iter1->first, intUnit );
	}

	result.tmv = Xl;

	TaylorModelVec<Number> x0;
	x0 = tmvCenter + new_tmvPre;

	// apply Picard iterations to obtain the Taylor expansion
	TaylorModelVec<Number> x = x0;

	for ( unsigned i = 1; i < order; ++i ) {
		x.Picard_assign( x0, ode, localInitial, t, intStep, i );
	}

	for ( auto iter = x.tms.begin(); iter != x.tms.end(); ++iter ) {
		carl::Interval<Number> intEst;
		estimation.find_assignment( intEst, iter->first );
		iter->second.remainder = intEst;
	}

	TaylorModelVec<Number> tmvTemp;
	tmvTemp = x.Picard( x0, ode, localInitial, t, intStep, order );

	bool bfound = true;

	auto iter_x = x.tms.begin();
	auto iter_xp = tmvTemp.tms.begin();

	for ( ; iter_x != x.tms.end(); ++iter_x, ++iter_xp ) {
		//		std::cout << iter_x->second.remainder << std::endl;
		//		std::cout << iter_xp->second.remainder << std::endl;

		if ( !( iter_x->second.remainder.contains( iter_xp->second.remainder ) ) ) {
			bfound = false;
			break;
		}
	}

	if ( !bfound ) {
		return 0;
	} else {
		iter_x = x.tms.begin();
		iter_xp = tmvTemp.tms.begin();

		for ( ; iter_x != x.tms.end(); ++iter_x, ++iter_xp ) {
			iter_x->second.remainder = iter_xp->second.remainder;
		}
	}

	// refine the remainder interval by Picard iteration
	bool bfinish = false;

	for ( int steps = 0; !bfinish && steps <= Setting::MAX_ITER_NUM; ++steps ) {
		bfinish = true;

		tmvTemp = x.Picard( x0, ode, localInitial, t, intStep, order );

		iter_x = x.tms.begin();
		iter_xp = tmvTemp.tms.begin();

		for ( ; iter_x != x.tms.end(); ++iter_x, ++iter_xp ) {
			Number w1 = iter_x->second.remainder.diameter();
			Number w2 = iter_xp->second.remainder.diameter();

			if ( bfinish && w2 / w1 < Number( Setting::STOP_RATIO ) ) {
				bfinish = false;
			}

			iter_x->second.remainder = iter_xp->second.remainder;
		}
	}

	result.tmvPre = x;
	result.domain = domain;

	result.domain.assign( t, intStep );

	return 1;
}

template <typename Number>
Flowpipe<Number>& Flowpipe<Number>::operator=( const Flowpipe<Number>& flowpipe ) {
	if ( this == &flowpipe ) return *this;

	tmvPre = flowpipe.tmvPre;
	tmv = flowpipe.tmv;
	domain = flowpipe.domain;

	return *this;
}

template <typename Number>
void Flowpipe<Number>::output( std::ostream& os, const exponent order ) {
	os << "{" << std::endl;

	TaylorModelVec<Number> tmvTemp;
	Domain<Number> fp_domain;
	composition( tmvTemp, fp_domain, order );

	os << tmvTemp << std::endl;

	os << fp_domain << std::endl;

	os << "}" << std::endl;
}

template <typename Number>
ContinuousSystem<Number>::ContinuousSystem() {
}

template <typename Number>
ContinuousSystem<Number>::ContinuousSystem( const PolynomialODE<Number>& ode_input,
											const Flowpipe<Number>& initialSet_input ) {
	ode = ode_input;
	initialSet = initialSet_input;
}

template <typename Number>
ContinuousSystem<Number>::ContinuousSystem( const ContinuousSystem<Number>& system ) {
	ode = system.ode;
	initialSet = system.initialSet;
}

template <typename Number>
ContinuousSystem<Number>::~ContinuousSystem() {
}

template <typename Number>
int ContinuousSystem<Number>::reach_picard( std::list<Flowpipe<Number>>& result, const carl::Variable& t, const double time,
											const double stepsize, const exponent order,
											const Range<Number>& estimation ) const {
	result.clear();

	Flowpipe<Number> flowpipe = initialSet;
	result.push_back( flowpipe );

	for ( double t_pass = 0.0; t_pass < time; ) {
		Flowpipe<Number> new_flowpipe;
		int res = flowpipe.next_picard<ContinuousSetting>( new_flowpipe, ode, t, stepsize, order, estimation );

		if ( res == 1 ) {
			result.push_back( new_flowpipe );
			flowpipe = new_flowpipe;

			t_pass += stepsize;

			printf( "time = %f,\t", t_pass );
			printf( "step = %f,\t", stepsize );
			printf( "order = %d\n", order );
		} else {
			fprintf( stdout, "Terminated -- The remainder estimation is not large enough.\n" );
			break;
		}
	}

	return 1;
}

template <typename Number>
ContinuousSystem<Number>& ContinuousSystem<Number>::operator=( const ContinuousSystem<Number>& system ) {
	if ( this == &system ) return *this;

	ode = system.ode;
	initialSet = system.initialSet;

	return *this;
}

template <typename Number>
void ContinuousSystem<Number>::output( std::ostream& os, const exponent order ) {
	os << "System Dynamics:" << std::endl;
	os << ode << std::endl
	   << std::endl;

	os << "Initial Set:" << std::endl;
	initialSet.output( os, order );
	os << std::endl;
}

template <typename Number>
void output_2D_interval_gnuplot( std::list<Flowpipe<Number>>& flowpipes, std::ofstream& os, const std::string& fileName,
								 const carl::Variable& axis_x, const carl::Variable& axis_y ) {
	os << "set terminal postscript" << std::endl;
	os << "set output " << '\'' << fileName << ".eps" << '\'' << std::endl;
	os << "set style line 1 linecolor rgb \"blue\"" << std::endl;
	os << "set autoscale" << std::endl;
	os << "unset label" << std::endl;
	os << "set xtic auto" << std::endl;
	os << "set ytic auto" << std::endl;
	os << "set xlabel " << '\"' << axis_x << '\"' << std::endl;
	os << "set ylabel " << '\"' << axis_y << '\"' << std::endl;
	os << "plot '-' notitle with lines ls 1" << std::endl;

	auto iter = flowpipes.begin();

	for ( ; iter != flowpipes.end(); ++iter ) {
		Range<Number> range;
		iter->enclosure( range );

		carl::Interval<Number> X;
		range.find_assignment( X, axis_x );

		carl::Interval<Number> Y;
		range.find_assignment( Y, axis_y );

		os << X.lower() << " " << Y.lower() << std::endl;
		os << X.upper() << " " << Y.lower() << std::endl;
		os << X.upper() << " " << Y.upper() << std::endl;
		os << X.lower() << " " << Y.upper() << std::endl;
		os << X.lower() << " " << Y.lower() << std::endl;
		os << std::endl;
		os << std::endl;
	}

	os << "e" << std::endl;
}

}  // namespace hypro