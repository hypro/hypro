/*---
  Flow*: A Taylor Model Based Flowpipe analyzer.
  Authors: Xin Chen, Erika Abraham and Sriram Sankaranarayanan.
  Email: Xin Chen <xin.chen@cs.rwth-aachen.de> if you have questions or comments.

  The code is released as is under the GNU General Public License (GPL). Please consult the file LICENSE.txt for
  further information.
---*/

#include "TaylorModel.h"

ParseSetting parseSetting;
ParseResult parseResult;

// class TaylorModel

TaylorModel::TaylorModel() {
}

TaylorModel::TaylorModel( const Interval& I, const int numVars ) {
	Interval intZero;
	Polynomial polyTemp( I, numVars );
	expansion = polyTemp;
	remainder = intZero;
}

TaylorModel::TaylorModel( const Polynomial& polyExp, const Interval& I )
	: expansion( polyExp )
	, remainder( I ) {
}

TaylorModel::TaylorModel( const RowVector& coefficients ) {
	Interval intZero;
	Polynomial polyTemp( coefficients );
	expansion = polyTemp;
	remainder = intZero;
}

TaylorModel::TaylorModel( const RowVector& coefficients, const Interval& I ) {
	Polynomial polyTemp( coefficients );
	expansion = polyTemp;
	remainder = I;
}

TaylorModel::TaylorModel( const vector<Interval>& coefficients ) {
	Interval intZero;
	Polynomial polyTemp( coefficients );
	expansion = polyTemp;
	remainder = intZero;
}

TaylorModel::TaylorModel( const vector<Interval>& coefficients, const Interval& I ) {
	Polynomial polyTemp( coefficients );
	expansion = polyTemp;
	remainder = I;
}

TaylorModel::TaylorModel( const TaylorModel& tm )
	: expansion( tm.expansion )
	, remainder( tm.remainder ) {
}

TaylorModel::~TaylorModel() {
	expansion.clear();
}

void TaylorModel::clear() {
	Interval intZero;
	expansion.clear();
	remainder = intZero;
}

void TaylorModel::dump_interval( FILE* fp, vector<string> const& varNames ) const {
	expansion.dump_interval( fp, varNames );
	fprintf( fp, " + " );
	remainder.dump( fp );
	fprintf( fp, "\n" );
}

void TaylorModel::dump_constant( FILE* fp, vector<string> const& varNames ) const {
	expansion.dump_constant( fp, varNames );
	fprintf( fp, " + " );
	remainder.dump( fp );
	fprintf( fp, "\n" );
}

void TaylorModel::constant( Interval& result ) const {
	expansion.constant( result );
}

void TaylorModel::intEval( Interval& result, const vector<Interval>& domain ) const {
	expansion.intEval( result, domain );
	result += remainder;
}

void TaylorModel::intEvalNormal( Interval& result, const vector<Interval>& step_exp_table ) const {
	expansion.intEvalNormal( result, step_exp_table );
	result += remainder;
}

void TaylorModel::ctrunc( const vector<Interval>& domain, const int order ) {
	Interval intTemp;
	expansion.ctrunc( intTemp, domain, order );
	remainder += intTemp;
}

void TaylorModel::nctrunc( const int order ) {
	expansion.nctrunc( order );
}

void TaylorModel::ctrunc_normal( const vector<Interval>& step_exp_table, const int order ) {
	Interval intTemp;
	expansion.ctrunc_normal( intTemp, step_exp_table, order );
	remainder += intTemp;
}

void TaylorModel::inv( TaylorModel& result ) const {
	expansion.inv( result.expansion );
	remainder.inv( result.remainder );
}

void TaylorModel::inv_assign() {
	expansion.inv_assign();
	remainder.inv_assign();
}

void TaylorModel::add( TaylorModel& result, const TaylorModel& tm ) const {
	result.expansion = expansion + tm.expansion;
	result.remainder = remainder + tm.remainder;
}

void TaylorModel::sub( TaylorModel& result, const TaylorModel& tm ) const {
	result.expansion = expansion - tm.expansion;
	result.remainder = remainder - tm.remainder;
}

void TaylorModel::add_assign( const TaylorModel& tm ) {
	expansion += tm.expansion;
	remainder += tm.remainder;
}

void TaylorModel::sub_assign( const TaylorModel& tm ) {
	expansion -= tm.expansion;
	remainder -= tm.remainder;
}

void TaylorModel::mul_ctrunc( TaylorModel& result, const TaylorModel& tm, const vector<Interval>& domain, const int order ) const {
	Interval intZero;
	Polynomial P1xP2;
	Interval P1xI2, P2xI1, I1xI2;

	P1xP2 = expansion * tm.expansion;

	if ( !tm.remainder.subseteq( intZero ) ) {
		expansion.intEval( P1xI2, domain );
		P1xI2 *= tm.remainder;
	}

	if ( !remainder.subseteq( intZero ) ) {
		tm.expansion.intEval( P2xI1, domain );
		P2xI1 *= remainder;
	}

	I1xI2 = remainder * tm.remainder;

	result.expansion = P1xP2;

	result.remainder = I1xI2;
	result.remainder += P2xI1;
	result.remainder += P1xI2;

	result.ctrunc( domain, order );

	result.cutoff( domain );
}

void TaylorModel::mul_ctrunc_normal( TaylorModel& result, const TaylorModel& tm, const vector<Interval>& step_exp_table, const int order ) const {
	Interval intZero;
	Polynomial P1xP2;
	Interval P1xI2, P2xI1, I1xI2;

	P1xP2 = expansion * tm.expansion;

	if ( !tm.remainder.subseteq( intZero ) ) {
		expansion.intEvalNormal( P1xI2, step_exp_table );
		P1xI2 *= tm.remainder;
	}

	if ( !remainder.subseteq( intZero ) ) {
		tm.expansion.intEvalNormal( P2xI1, step_exp_table );
		P2xI1 *= remainder;
	}

	I1xI2 = remainder * tm.remainder;

	result.expansion = P1xP2;

	result.remainder = I1xI2;
	result.remainder += P2xI1;
	result.remainder += P1xI2;

	result.ctrunc_normal( step_exp_table, order );

	result.cutoff_normal( step_exp_table );
}

void TaylorModel::mul_no_remainder( TaylorModel& result, const TaylorModel& tm, const int order ) const {
	result.expansion = expansion * tm.expansion;
	result.expansion.nctrunc( order );

	result.expansion.cutoff();
}

void TaylorModel::mul_no_remainder_no_rounding( TaylorModel& result, const TaylorModel& tm, const int order ) const {
	result.expansion = expansion * tm.expansion;
	result.expansion.nctrunc( order );
}

void TaylorModel::mul( TaylorModel& result, const Interval& I ) const {
	expansion.mul( result.expansion, I );
	result.remainder = remainder * I;
}

void TaylorModel::mul_ctrunc_assign( const TaylorModel& tm, const vector<Interval>& domain, const int order ) {
	TaylorModel result;
	mul_ctrunc( result, tm, domain, order );
	*this = result;
}

void TaylorModel::mul_ctrunc_normal_assign( const TaylorModel& tm, const vector<Interval>& step_exp_table, const int order ) {
	TaylorModel result;
	mul_ctrunc_normal( result, tm, step_exp_table, order );
	*this = result;
}

void TaylorModel::mul_no_remainder_assign( const TaylorModel& tm, const int order ) {
	TaylorModel result;
	mul_no_remainder( result, tm, order );
	*this = result;
}

void TaylorModel::mul_no_remainder_no_rounding_assign( const TaylorModel& tm, const int order ) {
	TaylorModel result;
	mul_no_remainder_no_rounding( result, tm, order );
	*this = result;
}

void TaylorModel::mul_assign( const Interval& I ) {
	TaylorModel result;
	mul( result, I );
	*this = result;
}

void TaylorModel::mul_insert( TaylorModel& result, const TaylorModel& tm, const Interval& tmPolyRange, const vector<Interval>& domain ) const {
	Interval intZero;
	Polynomial P1xP2;
	Interval P1xI2, P2xI1, I1xI2;

	P1xP2 = expansion * tm.expansion;

	if ( !tm.remainder.subseteq( intZero ) ) {
		expansion.intEval( P1xI2, domain );
		P1xI2 *= tm.remainder;
	}

	if ( !remainder.subseteq( intZero ) ) {
		P2xI1 = tmPolyRange * remainder;
	}

	I1xI2 = remainder * tm.remainder;

	result.expansion = P1xP2;

	result.remainder = I1xI2;
	result.remainder += P2xI1;
	result.remainder += P1xI2;

	result.cutoff( domain );
}

void TaylorModel::mul_insert_normal( TaylorModel& result, const TaylorModel& tm, const Interval& tmPolyRange, const vector<Interval>& step_exp_table ) const {
	Interval intZero;
	Polynomial P1xP2;
	Interval P1xI2, P2xI1, I1xI2;

	P1xP2 = expansion * tm.expansion;

	if ( !tm.remainder.subseteq( intZero ) ) {
		expansion.intEvalNormal( P1xI2, step_exp_table );
		P1xI2 *= tm.remainder;
	}

	if ( !remainder.subseteq( intZero ) ) {
		P2xI1 = tmPolyRange * remainder;
	}

	I1xI2 = remainder * tm.remainder;

	result.expansion = P1xP2;

	result.remainder = I1xI2;
	result.remainder += P2xI1;
	result.remainder += P1xI2;

	result.cutoff_normal( step_exp_table );
}

void TaylorModel::mul_insert_ctrunc( TaylorModel& result, const TaylorModel& tm, const Interval& tmPolyRange, const vector<Interval>& domain, const int order ) const {
	Interval intZero;
	Polynomial P1xP2;
	Interval P1xI2, P2xI1, I1xI2;

	P1xP2 = expansion * tm.expansion;

	if ( !tm.remainder.subseteq( intZero ) ) {
		expansion.intEval( P1xI2, domain );
		P1xI2 *= tm.remainder;
	}

	if ( !remainder.subseteq( intZero ) ) {
		P2xI1 = tmPolyRange * remainder;
	}

	I1xI2 = remainder * tm.remainder;

	result.expansion = P1xP2;

	result.remainder = I1xI2;
	result.remainder += P2xI1;
	result.remainder += P1xI2;

	result.ctrunc( domain, order );
	result.cutoff( domain );
}

void TaylorModel::mul_insert_ctrunc_normal( TaylorModel& result, const TaylorModel& tm, const Interval& tmPolyRange, const vector<Interval>& step_exp_table, const int order ) const {
	Interval intZero;
	Polynomial P1xP2;
	Interval P1xI2, P2xI1, I1xI2;

	P1xP2 = expansion * tm.expansion;

	if ( !tm.remainder.subseteq( intZero ) ) {
		expansion.intEvalNormal( P1xI2, step_exp_table );
		P1xI2 *= tm.remainder;
	}

	if ( !remainder.subseteq( intZero ) ) {
		P2xI1 = tmPolyRange * remainder;
	}

	I1xI2 = remainder * tm.remainder;

	result.expansion = P1xP2;

	result.remainder = I1xI2;
	result.remainder += P2xI1;
	result.remainder += P1xI2;

	result.ctrunc_normal( step_exp_table, order );
	result.cutoff_normal( step_exp_table );
}

void TaylorModel::mul_insert_ctrunc_normal( TaylorModel& result, Interval& tm1, Interval& intTrunc, const TaylorModel& tm, const Interval& tmPolyRange, const vector<Interval>& step_exp_table, const int order ) const {
	Polynomial P1xP2;
	Interval P1xI2, P2xI1, I1xI2;

	P1xP2 = expansion * tm.expansion;

	Interval intZero;
	tm1 = intZero;
	intTrunc = intZero;

	if ( !tm.remainder.subseteq( intZero ) ) {
		expansion.intEvalNormal( P1xI2, step_exp_table );
		tm1 = P1xI2;
		P1xI2 *= tm.remainder;
	}

	if ( !remainder.subseteq( intZero ) ) {
		P2xI1 = tmPolyRange * remainder;
	}

	I1xI2 = remainder * tm.remainder;

	result.expansion = P1xP2;

	result.remainder = I1xI2;
	result.remainder += P2xI1;
	result.remainder += P1xI2;

	result.expansion.ctrunc_normal( intTrunc, step_exp_table, order );

	Interval intRound;
	result.expansion.cutoff_normal( intRound, step_exp_table );
	intTrunc += intRound;

	result.remainder += intTrunc;
}

void TaylorModel::mul_insert_assign( const TaylorModel& tm, const Interval& tmPolyRange, const vector<Interval>& domain ) {
	TaylorModel result;
	mul_insert( result, tm, tmPolyRange, domain );
	*this = result;
}

void TaylorModel::mul_insert_normal_assign( const TaylorModel& tm, const Interval& tmPolyRange, const vector<Interval>& step_exp_table ) {
	TaylorModel result;
	mul_insert_normal( result, tm, tmPolyRange, step_exp_table );
	*this = result;
}

void TaylorModel::mul_insert_ctrunc_assign( const TaylorModel& tm, const Interval& tmPolyRange, const vector<Interval>& domain, const int order ) {
	TaylorModel result;
	mul_insert_ctrunc( result, tm, tmPolyRange, domain, order );
	*this = result;
}

void TaylorModel::mul_insert_ctrunc_normal_assign( const TaylorModel& tm, const Interval& tmPolyRange, const vector<Interval>& step_exp_table, const int order ) {
	TaylorModel result;
	mul_insert_ctrunc_normal( result, tm, tmPolyRange, step_exp_table, order );
	*this = result;
}

void TaylorModel::mul_insert_ctrunc_normal_assign( Interval& tm1, Interval& intTrunc, const TaylorModel& tm, const Interval& tmPolyRange, const vector<Interval>& step_exp_table, const int order ) {
	TaylorModel result;
	mul_insert_ctrunc_normal( result, tm1, intTrunc, tm, tmPolyRange, step_exp_table, order );
	*this = result;
}

void TaylorModel::div( TaylorModel& result, const Interval& I ) const {
	expansion.div( result.expansion, I );
	result.remainder = remainder / I;
}

void TaylorModel::div_assign( const Interval& I ) {
	expansion.div_assign( I );
	remainder /= I;
}

void TaylorModel::derivative( TaylorModel& result, const int varIndex ) const {
	Interval intZero;
	result = *this;

	list<Monomial>::iterator iter;

	for ( iter = result.expansion.monomials.begin(); iter != result.expansion.monomials.end(); ) {
		if ( iter->degrees[varIndex] > 0 ) {
			double tmp = iter->degrees[varIndex];
			iter->degrees[varIndex] -= 1;
			iter->d -= 1;
			iter->coefficient.mul_assign( tmp );
			++iter;
		} else {
			iter = result.expansion.monomials.erase( iter );
		}
	}

	result.remainder = intZero;
}

void TaylorModel::LieDerivative_no_remainder( TaylorModel& result, const TaylorModelVec& f, const int order ) const {
	derivative( result, 0 );

	int rangeDim = f.tms.size();

	for ( int i = 0; i < rangeDim; ++i ) {
		TaylorModel tmTemp;
		derivative( tmTemp, i + 1 );
		tmTemp.mul_no_remainder_assign( f.tms[i], order );
		result.add_assign( tmTemp );
	}
}

void TaylorModel::integral( TaylorModel& result, const Interval& I ) const {
	result = *this;

	list<Monomial>::iterator iter;

	for ( iter = result.expansion.monomials.begin(); iter != result.expansion.monomials.end(); ++iter ) {
		if ( iter->degrees[0] > 0 ) {
			iter->degrees[0] += 1;
			iter->d += 1;
			double tmp = iter->degrees[0];
			iter->coefficient.div_assign( tmp );
		} else {
			iter->degrees[0] += 1;
			iter->d += 1;
		}
	}

	result.remainder *= I;
}

void TaylorModel::integral_no_remainder( TaylorModel& result ) const {
	result = *this;

	list<Monomial>::iterator iter;

	for ( iter = result.expansion.monomials.begin(); iter != result.expansion.monomials.end(); ++iter ) {
		if ( iter->degrees[0] > 0 ) {
			iter->degrees[0] += 1;
			iter->d += 1;
			double tmp = iter->degrees[0];
			iter->coefficient.div_assign( tmp );
		} else {
			iter->degrees[0] += 1;
			iter->d += 1;
		}
	}
}

void TaylorModel::linearCoefficients( vector<Interval>& result ) const {
	expansion.linearCoefficients( result );
}

void TaylorModel::toHornerForm( HornerForm& result, Interval& I ) const {
	expansion.toHornerForm( result );
	I = remainder;
}

void TaylorModel::insert( TaylorModel& result, const TaylorModelVec& vars, const vector<Interval>& varsPolyRange, const vector<Interval>& domain ) const {
	if ( vars.tms.size() == 0 ) {
		result = *this;

		list<Monomial>::iterator iter;

		for ( iter = result.expansion.monomials.begin(); iter != result.expansion.monomials.end(); ) {
			if ( ( ( iter->d ) - ( iter->degrees[0] ) ) > 0 ) {
				iter = result.expansion.monomials.erase( iter );
			} else {
				++iter;
			}
		}
	} else {
		HornerForm hf;
		expansion.toHornerForm( hf );

		hf.insert( result, vars, varsPolyRange, domain );
		result.remainder += remainder;
	}
}

void TaylorModel::insert_ctrunc( TaylorModel& result, const TaylorModelVec& vars, const vector<Interval>& varsPolyRange, const vector<Interval>& domain, const int order ) const {
	if ( vars.tms.size() == 0 ) {
		result = *this;

		list<Monomial>::iterator iter;

		for ( iter = result.expansion.monomials.begin(); iter != result.expansion.monomials.end(); ) {
			if ( ( ( iter->d ) - ( iter->degrees[0] ) ) > 0 ) {
				iter = result.expansion.monomials.erase( iter );
			} else {
				++iter;
			}
		}
	} else {
		HornerForm hf;
		expansion.toHornerForm( hf );

		hf.insert_ctrunc( result, vars, varsPolyRange, domain, order );
		result.remainder += remainder;
	}
}

void TaylorModel::insert_no_remainder( TaylorModel& result, const TaylorModelVec& vars, const int numVars, const int order ) const {
	if ( vars.tms.size() == 0 ) {
		result = *this;

		list<Monomial>::iterator iter;

		for ( iter = result.expansion.monomials.begin(); iter != result.expansion.monomials.end(); ) {
			if ( ( ( iter->d ) - ( iter->degrees[0] ) ) > 0 ) {
				iter = result.expansion.monomials.erase( iter );
			} else {
				++iter;
			}
		}
	} else {
		HornerForm hf;
		expansion.toHornerForm( hf );

		hf.insert_no_remainder( result, vars, numVars, order );
	}
}

void TaylorModel::insert_no_remainder_no_rounding( TaylorModel& result, const TaylorModelVec& vars, const int numVars, const int order ) const {
	if ( vars.tms.size() == 0 ) {
		result = *this;

		list<Monomial>::iterator iter;

		for ( iter = result.expansion.monomials.begin(); iter != result.expansion.monomials.end(); ) {
			if ( ( ( iter->d ) - ( iter->degrees[0] ) ) > 0 ) {
				iter = result.expansion.monomials.erase( iter );
			} else {
				++iter;
			}
		}
	} else {
		HornerForm hf;
		expansion.toHornerForm( hf );

		hf.insert_no_remainder_no_rounding( result, vars, numVars, order );
	}
}

void TaylorModel::insert_ctrunc_normal( TaylorModel& result, const TaylorModelVec& vars, const vector<Interval>& varsPolyRange, const vector<Interval>& step_exp_table, const int numVars, const int order ) const {
	if ( vars.tms.size() == 0 ) {
		result = *this;

		list<Monomial>::iterator iter;

		for ( iter = result.expansion.monomials.begin(); iter != result.expansion.monomials.end(); ) {
			if ( ( ( iter->d ) - ( iter->degrees[0] ) ) > 0 ) {
				iter = result.expansion.monomials.erase( iter );
			} else {
				++iter;
			}
		}
	} else {
		HornerForm hf;
		expansion.toHornerForm( hf );

		hf.insert_ctrunc_normal( result, vars, varsPolyRange, step_exp_table, numVars, order );
		result.remainder += remainder;
	}
}

void TaylorModel::evaluate_t( TaylorModel& result, const vector<Interval>& step_exp_table ) const {
	result.expansion.clear();
	result.remainder = remainder;

	if ( expansion.monomials.size() == 0 )
		return;

	list<Monomial>::const_iterator iter;
	Interval intZero;

	if ( step_exp_table[1].subseteq( intZero ) )  // t = 0
	{
		for ( iter = expansion.monomials.begin(); iter != expansion.monomials.end(); ++iter ) {
			if ( iter->degrees[0] == 0 ) {
				result.expansion.add_assign( *iter );
			}
		}
	} else {
		for ( iter = expansion.monomials.begin(); iter != expansion.monomials.end(); ++iter ) {
			Monomial monoTemp = *iter;
			int tmp = monoTemp.degrees[0];

			if ( tmp > 0 ) {
				monoTemp.coefficient *= step_exp_table[tmp];
				monoTemp.d -= tmp;
				monoTemp.degrees[0] = 0;
			}

			result.expansion.add_assign( monoTemp );
		}
	}
}

void TaylorModel::mul( TaylorModel& result, const int varIndex, const int degree ) const {
	result = *this;
	result.mul_assign( varIndex, degree );
}

void TaylorModel::mul_assign( const int varIndex, const int degree ) {
	expansion.mul_assign( varIndex, degree );
}

void TaylorModel::rmConstant() {
	expansion.rmConstant();
}

void TaylorModel::cutoff_normal( const vector<Interval>& step_exp_table ) {
	Interval intRem;
	expansion.cutoff_normal( intRem, step_exp_table );
	remainder += intRem;
}

void TaylorModel::cutoff( const vector<Interval>& domain ) {
	Interval intRem;
	expansion.cutoff( intRem, domain );
	remainder += intRem;
}

void TaylorModel::cutoff() {
	expansion.cutoff();
}

int TaylorModel::degree() const {
	return expansion.degree();
}

bool TaylorModel::isZero() const {
	Interval intZero;

	if ( expansion.isZero() ) {
		if ( remainder.subseteq( intZero ) ) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

void TaylorModel::normalize( vector<Interval>& domain ) {
	int domainDim = domain.size();

	// compute the center of the original domain and make it origin-centered
	vector<Interval> intVecCenter;
	for ( int i = 1; i < domainDim; ++i )  // we omit the time dimension
	{
		Interval M;
		domain[i].remove_midpoint( M );
		intVecCenter.push_back( M );
	}

	// compute the scalars
	Interval intZero;
	vector<vector<Interval> > coefficients;
	vector<Interval> row;

	for ( int i = 0; i < domainDim; ++i ) {
		row.push_back( intZero );
	}

	for ( int i = 0; i < domainDim - 1; ++i ) {
		coefficients.push_back( row );
	}

	for ( int i = 1; i < domainDim; ++i ) {
		Interval M;
		domain[i].mag( M );
		coefficients[i - 1][i] = M;
	}

	TaylorModelVec newVars( coefficients );
	for ( int i = 0; i < domainDim - 1; ++i ) {
		TaylorModel tmTemp( intVecCenter[i], domainDim );
		newVars.tms[i].add_assign( tmTemp );
	}

	Interval intUnit( -1, 1 );
	for ( int i = 1; i < domainDim; ++i ) {
		domain[i] = intUnit;
	}

	TaylorModel tmTemp;
	insert_no_remainder_no_rounding( tmTemp, newVars, domainDim, degree() );
	expansion = tmTemp.expansion;
}

void TaylorModel::polyRange( Interval& result, const vector<Interval>& domain ) const {
	expansion.intEval( result, domain );
}

void TaylorModel::polyRangeNormal( Interval& result, const vector<Interval>& step_exp_table ) const {
	expansion.intEvalNormal( result, step_exp_table );
}

void TaylorModel::exp_taylor( TaylorModel& result, list<Interval>& ranges, const vector<Interval>& step_exp_table, const int numVars, const int order ) const {
	Interval const_part;

	TaylorModel tmF = *this;

	// remove the center point of tm
	tmF.constant( const_part );
	tmF.rmConstant();  // F = tm - c

	const_part.exp_assign();  // exp(c)

	if ( tmF.isZero() )	 // tm = c
	{
		TaylorModel tmExp( const_part, numVars );
		result = tmExp;

		Interval invalid( 1, -1 );
		ranges.push_back( invalid );

		return;
	}

	ranges.push_back( const_part );	 // keep the unchanged part

	Interval I( 1 );
	TaylorModel tmOne( I, numVars );

	// to compute the expression 1 + F + (1/2!)F^2 + ... + (1/k!)F^k,
	// we evaluate its Horner form (...((1/(k-1))((1/k)*F+1)*F + 1) ... + 1)

	result = tmOne;
	Interval tmFPolyRange;
	tmF.polyRangeNormal( tmFPolyRange, step_exp_table );

	for ( int i = order; i > 0; --i ) {
		Interval intFactor( 1 );
		intFactor.div_assign( (double)i );

		result.mul_assign( intFactor );

		Interval tm1Poly, intTrunc;
		result.mul_insert_ctrunc_normal_assign( tm1Poly, intTrunc, tmF, tmFPolyRange, step_exp_table, order );

		ranges.push_back( tm1Poly );	   // keep the unchanged part
		ranges.push_back( tmFPolyRange );  // keep the unchanged part
		ranges.push_back( intTrunc );	   // keep the unchanged part

		result.add_assign( tmOne );
	}

	result.mul_assign( const_part );

	Interval intRound;
	result.expansion.cutoff_normal( intRound, step_exp_table );
	ranges.push_back( intRound );  // keep the unchanged part
	result.remainder += intRound;

	Interval rem, tmRange;
	ranges.push_back( tmFPolyRange );  // keep the unchanged part
	tmRange = tmFPolyRange + tmF.remainder;
	exp_taylor_remainder( rem, tmRange, order + 1 );

	result.remainder += const_part * rem;
}

void TaylorModel::rec_taylor( TaylorModel& result, list<Interval>& ranges, const vector<Interval>& step_exp_table, const int numVars, const int order ) const {
	Interval const_part;

	TaylorModel tmF = *this;

	// remove the center point of tm
	tmF.constant( const_part );
	tmF.rmConstant();  // F = tm - c

	const_part.rec_assign();  // 1/c

	if ( tmF.isZero() )	 // tm = c
	{
		TaylorModel tmRec( const_part, numVars );
		result = tmRec;

		Interval invalid( 1, -1 );
		ranges.push_back( invalid );

		return;
	}

	Interval I( 1 );
	TaylorModel tmOne( I, numVars );
	TaylorModel tmF_c;

	ranges.push_back( const_part );	 // keep the unchanged part
	tmF.mul( tmF_c, const_part );

	// to compute the expression 1 - F/c + (F/c)^2 - ... + (-1)^k (F/c)^k,
	// we evaluate its Horner form (-1)*(...((-1)*(-F/c + 1)*F/c + 1)...) + 1

	result = tmOne;
	Interval tmF_cPolyRange;
	tmF_c.polyRangeNormal( tmF_cPolyRange, step_exp_table );

	for ( int i = order; i > 0; --i ) {
		result.inv_assign();

		Interval tm1Poly, intTrunc;
		result.mul_insert_ctrunc_normal_assign( tm1Poly, intTrunc, tmF_c, tmF_cPolyRange, step_exp_table, order );

		ranges.push_back( tm1Poly );		 // keep the unchanged part
		ranges.push_back( tmF_cPolyRange );	 // keep the unchanged part
		ranges.push_back( intTrunc );		 // keep the unchanged part

		result.add_assign( tmOne );
	}

	result.mul_assign( const_part );

	Interval intRound;
	result.expansion.cutoff_normal( intRound, step_exp_table );
	ranges.push_back( intRound );  // keep the unchanged part
	result.remainder += intRound;

	Interval rem, tmF_cRange;
	ranges.push_back( tmF_cPolyRange );	 // keep the unchanged part
	tmF_cRange = tmF_cPolyRange + tmF_c.remainder;

	rec_taylor_remainder( rem, tmF_cRange, order + 1 );

	result.remainder += rem * const_part;
}

void TaylorModel::sin_taylor( TaylorModel& result, list<Interval>& ranges, const vector<Interval>& step_exp_table, const int numVars, const int order ) const {
	Interval const_part;

	TaylorModel tmF = *this;

	// remove the center point of tm
	tmF.constant( const_part );
	tmF.rmConstant();  // F = tm - c

	if ( tmF.isZero() )	 // tm = c
	{
		const_part.sin_assign();
		TaylorModel tmSin( const_part, numVars );
		result = tmSin;

		Interval invalid( 1, -1 );
		ranges.push_back( invalid );

		return;
	}

	ranges.push_back( const_part );	 // keep the unchanged part

	Interval sinc, cosc, msinc, mcosc;
	sinc = const_part.sin();
	cosc = const_part.cos();
	sinc.inv( msinc );
	cosc.inv( mcosc );

	TaylorModel tmTemp( sinc, numVars );
	result = tmTemp;

	Interval tmFPolyRange;
	tmF.polyRangeNormal( tmFPolyRange, step_exp_table );

	int k = 1;
	Interval I( 1 );

	TaylorModel tmPowerTmF( I, numVars );

	for ( int i = 1; i <= order; ++i, ++k ) {
		k %= 4;

		I.div_assign( (double)i );

		switch ( k ) {
			case 0: {
				Interval tm1Poly, intTrunc;
				tmPowerTmF.mul_insert_ctrunc_normal_assign( tm1Poly, intTrunc, tmF, tmFPolyRange, step_exp_table, order );

				ranges.push_back( tm1Poly );	   // keep the unchanged part
				ranges.push_back( tmFPolyRange );  // keep the unchanged part
				ranges.push_back( intTrunc );	   // keep the unchanged part

				tmTemp = tmPowerTmF;

				Interval intTemp = I * sinc;
				ranges.push_back( intTemp );  // keep the unchanged part
				tmTemp.mul_assign( intTemp );

				result.add_assign( tmTemp );

				break;
			}
			case 1: {
				Interval tm1Poly, intTrunc;
				tmPowerTmF.mul_insert_ctrunc_normal_assign( tm1Poly, intTrunc, tmF, tmFPolyRange, step_exp_table, order );

				ranges.push_back( tm1Poly );	   // keep the unchanged part
				ranges.push_back( tmFPolyRange );  // keep the unchanged part
				ranges.push_back( intTrunc );	   // keep the unchanged part

				tmTemp = tmPowerTmF;

				Interval intTemp = I * cosc;
				ranges.push_back( intTemp );  // keep the unchanged part
				tmTemp.mul_assign( intTemp );

				result.add_assign( tmTemp );

				break;
			}
			case 2: {
				Interval tm1Poly, intTrunc;
				tmPowerTmF.mul_insert_ctrunc_normal_assign( tm1Poly, intTrunc, tmF, tmFPolyRange, step_exp_table, order );

				ranges.push_back( tm1Poly );	   // keep the unchanged part
				ranges.push_back( tmFPolyRange );  // keep the unchanged part
				ranges.push_back( intTrunc );	   // keep the unchanged part

				tmTemp = tmPowerTmF;

				Interval intTemp = I * msinc;
				ranges.push_back( intTemp );  // keep the unchanged part
				tmTemp.mul_assign( intTemp );

				result.add_assign( tmTemp );

				break;
			}
			case 3: {
				Interval tm1Poly, intTrunc;
				tmPowerTmF.mul_insert_ctrunc_normal_assign( tm1Poly, intTrunc, tmF, tmFPolyRange, step_exp_table, order );

				ranges.push_back( tm1Poly );	   // keep the unchanged part
				ranges.push_back( tmFPolyRange );  // keep the unchanged part
				ranges.push_back( intTrunc );	   // keep the unchanged part

				tmTemp = tmPowerTmF;

				Interval intTemp = I * mcosc;
				ranges.push_back( intTemp );  // keep the unchanged part
				tmTemp.mul_assign( intTemp );

				result.add_assign( tmTemp );

				break;
			}
		}
	}

	Interval intRound;
	result.expansion.cutoff_normal( intRound, step_exp_table );
	ranges.push_back( intRound );  // keep the unchanged part
	result.remainder += intRound;

	// evaluate the remainder
	Interval tmRange, rem;
	tmRange = tmFPolyRange + tmF.remainder;

	ranges.push_back( tmFPolyRange );  // keep the unchanged part
	sin_taylor_remainder( rem, const_part, tmRange, order + 1 );

	result.remainder += rem;
}

void TaylorModel::cos_taylor( TaylorModel& result, list<Interval>& ranges, const vector<Interval>& step_exp_table, const int numVars, const int order ) const {
	Interval const_part;

	TaylorModel tmF = *this;

	// remove the center point of tm
	tmF.constant( const_part );
	tmF.rmConstant();  // F = tm - c

	if ( tmF.isZero() )	 // tm = c
	{
		const_part.cos_assign();
		TaylorModel tmCos( const_part, numVars );
		result = tmCos;

		Interval invalid( 1, -1 );
		ranges.push_back( invalid );

		return;
	}

	ranges.push_back( const_part );	 // keep the unchanged part

	Interval sinc, cosc, msinc, mcosc;
	sinc = const_part.sin();
	cosc = const_part.cos();
	sinc.inv( msinc );
	cosc.inv( mcosc );

	TaylorModel tmTemp( cosc, numVars );
	result = tmTemp;

	Interval tmFPolyRange;
	tmF.polyRangeNormal( tmFPolyRange, step_exp_table );

	int k = 1;
	Interval I( 1 );

	TaylorModel tmPowerTmF( I, numVars );

	for ( int i = 1; i <= order; ++i, ++k ) {
		k %= 4;

		I.div_assign( (double)i );

		switch ( k ) {
			case 0: {
				Interval tm1Poly, intTrunc;
				tmPowerTmF.mul_insert_ctrunc_normal_assign( tm1Poly, intTrunc, tmF, tmFPolyRange, step_exp_table, order );

				ranges.push_back( tm1Poly );	   // keep the unchanged part
				ranges.push_back( tmFPolyRange );  // keep the unchanged part
				ranges.push_back( intTrunc );	   // keep the unchanged part

				tmTemp = tmPowerTmF;

				Interval intTemp = I * cosc;
				ranges.push_back( intTemp );  // keep the unchanged part
				tmTemp.mul_assign( intTemp );

				result.add_assign( tmTemp );

				break;
			}
			case 1: {
				Interval tm1Poly, intTrunc;
				tmPowerTmF.mul_insert_ctrunc_normal_assign( tm1Poly, intTrunc, tmF, tmFPolyRange, step_exp_table, order );

				ranges.push_back( tm1Poly );	   // keep the unchanged part
				ranges.push_back( tmFPolyRange );  // keep the unchanged part
				ranges.push_back( intTrunc );	   // keep the unchanged part

				tmTemp = tmPowerTmF;

				Interval intTemp = I * msinc;
				ranges.push_back( intTemp );  // keep the unchanged part
				tmTemp.mul_assign( intTemp );

				result.add_assign( tmTemp );

				break;
			}
			case 2: {
				Interval tm1Poly, intTrunc;
				tmPowerTmF.mul_insert_ctrunc_normal_assign( tm1Poly, intTrunc, tmF, tmFPolyRange, step_exp_table, order );

				ranges.push_back( tm1Poly );	   // keep the unchanged part
				ranges.push_back( tmFPolyRange );  // keep the unchanged part
				ranges.push_back( intTrunc );	   // keep the unchanged part

				tmTemp = tmPowerTmF;

				Interval intTemp = I * mcosc;
				ranges.push_back( intTemp );  // keep the unchanged part
				tmTemp.mul_assign( intTemp );

				result.add_assign( tmTemp );

				break;
			}
			case 3: {
				Interval tm1Poly, intTrunc;
				tmPowerTmF.mul_insert_ctrunc_normal_assign( tm1Poly, intTrunc, tmF, tmFPolyRange, step_exp_table, order );

				ranges.push_back( tm1Poly );	   // keep the unchanged part
				ranges.push_back( tmFPolyRange );  // keep the unchanged part
				ranges.push_back( intTrunc );	   // keep the unchanged part

				tmTemp = tmPowerTmF;

				Interval intTemp = I * sinc;
				ranges.push_back( intTemp );  // keep the unchanged part
				tmTemp.mul_assign( intTemp );

				result.add_assign( tmTemp );

				break;
			}
		}
	}

	Interval intRound;
	result.expansion.cutoff_normal( intRound, step_exp_table );
	ranges.push_back( intRound );  // keep the unchanged part
	result.remainder += intRound;

	// evaluate the remainder
	Interval tmRange, rem;
	tmRange = tmFPolyRange + tmF.remainder;

	ranges.push_back( tmFPolyRange );  // keep the unchanged part
	cos_taylor_remainder( rem, const_part, tmRange, order + 1 );

	result.remainder += rem;
}

void TaylorModel::log_taylor( TaylorModel& result, list<Interval>& ranges, const vector<Interval>& step_exp_table, const int numVars, const int order ) const {
	Interval const_part;

	TaylorModel tmF = *this;

	// remove the center point of tm
	tmF.constant( const_part );
	tmF.rmConstant();  // F = tm - c

	Interval C = const_part;
	ranges.push_back( const_part );	 // keep the unchanged part

	const_part.log_assign();  // log(c)

	if ( tmF.isZero() )	 // tm = c
	{
		TaylorModel tmLog( const_part, numVars );
		result = tmLog;

		Interval invalid( 1, -1 );
		ranges.push_back( invalid );

		return;
	}

	TaylorModel tmF_c;
	tmF.div( tmF_c, C );

	result = tmF_c;

	Interval I( (double)order );
	result.div_assign( I );	 // F/c * (1/order)

	Interval tmF_cPolyRange;
	tmF_c.polyRangeNormal( tmF_cPolyRange, step_exp_table );

	for ( int i = order; i >= 2; --i ) {
		Interval J( 1 );
		J.div_assign( (double)( i - 1 ) );
		TaylorModel tmJ( J, numVars );

		result.sub_assign( tmJ );
		result.inv_assign();

		Interval tm1Poly, intTrunc;
		result.mul_insert_ctrunc_normal_assign( tm1Poly, intTrunc, tmF_c, tmF_cPolyRange, step_exp_table, order );

		ranges.push_back( tm1Poly );		 // keep the unchanged part
		ranges.push_back( tmF_cPolyRange );	 // keep the unchanged part
		ranges.push_back( intTrunc );		 // keep the unchanged part
	}

	TaylorModel const_part_tm( const_part, numVars );
	result.add_assign( const_part_tm );

	Interval intRound;
	result.expansion.cutoff_normal( intRound, step_exp_table );
	ranges.push_back( intRound );  // keep the unchanged part
	result.remainder += intRound;

	Interval rem, tmF_cRange;
	ranges.push_back( tmF_cPolyRange );	 // keep the unchanged part
	tmF_cRange = tmF_cPolyRange + tmF_c.remainder;

	log_taylor_remainder( rem, tmF_cRange, order + 1 );

	result.remainder += rem;
}

void TaylorModel::sqrt_taylor( TaylorModel& result, list<Interval>& ranges, const vector<Interval>& step_exp_table, const int numVars, const int order ) const {
	Interval const_part;

	TaylorModel tmF = *this;

	// remove the center point of tm
	tmF.constant( const_part );
	tmF.rmConstant();  // F = tm - c

	Interval C = const_part;
	ranges.push_back( const_part );	 // keep the unchanged part

	const_part.sqrt_assign();  // log(c)

	if ( tmF.isZero() )	 // tm = c
	{
		TaylorModel tmSqrt( const_part, numVars );
		result = tmSqrt;

		Interval invalid( 1, -1 );
		ranges.push_back( invalid );

		return;
	}

	TaylorModel tmF_2c;
	tmF.div( tmF_2c, C );

	Interval intTwo( 2 );
	tmF_2c.div_assign( intTwo );  // F/2c

	Interval intOne( 1 );
	TaylorModel tmOne( intOne, numVars );

	result = tmF_2c;

	Interval K( 1 ), J( 1 );

	Interval tmF_2cPolyRange;
	tmF_2c.polyRangeNormal( tmF_2cPolyRange, step_exp_table );

	for ( int i = order, j = 2 * order - 3; i >= 2; --i, j -= 2 ) {
		// i
		Interval K( (double)i );

		// j = 2*i-3
		Interval J( (double)j );

		result.inv_assign();
		result.mul_assign( J / K );

		result.add_assign( tmOne );

		Interval tm1Poly, intTrunc;
		result.mul_insert_ctrunc_normal_assign( tm1Poly, intTrunc, tmF_2c, tmF_2cPolyRange, step_exp_table, order );

		ranges.push_back( tm1Poly );		  // keep the unchanged part
		ranges.push_back( tmF_2cPolyRange );  // keep the unchanged part
		ranges.push_back( intTrunc );		  // keep the unchanged part
	}

	result.add_assign( tmOne );

	result.mul_assign( const_part );

	Interval intRound;
	result.expansion.cutoff_normal( intRound, step_exp_table );
	ranges.push_back( intRound );  // keep the unchanged part
	result.remainder += intRound;

	Interval rem, tmF_cRange = tmF_2cPolyRange;
	tmF_cRange.mul_assign( 2.0 );

	ranges.push_back( tmF_cRange );	 // keep the unchanged part

	Interval tmF_c_remainder = tmF_2c.remainder;
	tmF_c_remainder.mul_assign( 2.0 );
	tmF_cRange += tmF_c_remainder;

	sqrt_taylor_remainder( rem, tmF_cRange, order + 1 );

	result.remainder += rem * const_part;
}

Interval TaylorModel::getRemainder() const {
	return remainder;
}

void TaylorModel::getExpansion( Polynomial& P ) const {
	P = expansion;
}

TaylorModel& TaylorModel::operator=( const TaylorModel& tm ) {
	if ( this == &tm )
		return *this;

	expansion = tm.expansion;
	remainder = tm.remainder;
	return *this;
}

// class TaylorModelVec

TaylorModelVec::TaylorModelVec() {
}

TaylorModelVec::TaylorModelVec( const vector<TaylorModel>& tms_input )
	: tms( tms_input ) {
}

TaylorModelVec::TaylorModelVec( const Matrix& coefficients ) {
	int cols = coefficients.cols();
	RowVector rowVec( cols );

	int rows = coefficients.rows();

	for ( int i = 0; i < rows; ++i ) {
		coefficients.row( rowVec, i );
		TaylorModel tmTemp( rowVec );
		tms.push_back( tmTemp );
	}
}

TaylorModelVec::TaylorModelVec( const Matrix& coefficients, const vector<Interval>& remainders ) {
	int cols = coefficients.cols();
	RowVector rowVec( cols );

	int rows = coefficients.rows();

	for ( int i = 0; i < rows; ++i ) {
		coefficients.row( rowVec, i );
		TaylorModel tmTemp( rowVec, remainders[i] );
		tms.push_back( tmTemp );
	}
}

TaylorModelVec::TaylorModelVec( const vector<Interval>& constants, const int numVars ) {
	for ( int i = 0; i < constants.size(); ++i ) {
		TaylorModel tmTemp( constants[i], numVars );
		tms.push_back( tmTemp );
	}
}

TaylorModelVec::TaylorModelVec( const vector<vector<Interval> >& coefficients ) {
	for ( int i = 0; i < coefficients.size(); ++i ) {
		TaylorModel tmTemp( coefficients[i] );
		tms.push_back( tmTemp );
	}
}

TaylorModelVec::TaylorModelVec( const vector<vector<Interval> >& coefficients, const vector<Interval>& remainders ) {
	for ( int i = 0; i < coefficients.size(); ++i ) {
		TaylorModel tmTemp( coefficients[i], remainders[i] );
		tms.push_back( tmTemp );
	}
}

TaylorModelVec::TaylorModelVec( const vector<Interval>& intVec, vector<Interval>& domain ) {
	int rangeDim = intVec.size();
	domain = intVec;
	Interval intZero;
	domain.insert( domain.begin(), intZero );

	vector<Interval> intVecCenter;
	for ( int i = 0; i < rangeDim; ++i )  // we omit the time dimension
	{
		double center = intVec[i].midpoint();
		Interval intTemp( center );
		intVecCenter.push_back( intTemp );
		domain[i + 1].sub_assign( center );
	}

	// compute the scalars
	Matrix coefficients( rangeDim, rangeDim + 1 );
	for ( int i = 0; i < rangeDim; ++i ) {
		coefficients.set( domain[i + 1].sup(), i, i + 1 );
	}

	TaylorModelVec tmvTemp( coefficients );
	tms = tmvTemp.tms;

	for ( int i = 0; i < rangeDim; ++i ) {
		TaylorModel tmTemp( intVecCenter[i], rangeDim + 1 );
		tms[i].add_assign( tmTemp );
	}

	Interval intUnit( -1, 1 );
	for ( int i = 0; i < rangeDim; ++i ) {
		domain[i + 1] = intUnit;
	}
}

TaylorModelVec::TaylorModelVec( const TaylorModelVec& tmv )
	: tms( tmv.tms ) {
}

TaylorModelVec::~TaylorModelVec() {
	tms.clear();
}

void TaylorModelVec::clear() {
	tms.clear();
}

void TaylorModelVec::dump_interval( FILE* fp, const vector<string>& stateVarNames, const vector<string>& tmVarNames ) const {
	for ( int i = 0; i < tms.size(); ++i ) {
		fprintf( fp, "%s = ", stateVarNames[i].c_str() );
		tms[i].dump_interval( fp, tmVarNames );
		fprintf( fp, "\n" );
	}

	fprintf( fp, "\n" );
}

void TaylorModelVec::dump_constant( FILE* fp, const vector<string>& stateVarNames, const vector<string>& tmVarNames ) const {
	for ( int i = 0; i < tms.size(); ++i ) {
		fprintf( fp, "%s = ", stateVarNames[i].c_str() );
		tms[i].dump_constant( fp, tmVarNames );
		fprintf( fp, "\n" );
	}

	fprintf( fp, "\n" );
}

void TaylorModelVec::constant( vector<Interval>& result ) const {
	result.clear();

	for ( int i = 0; i < tms.size(); ++i ) {
		Interval I;
		tms[i].constant( I );
		result.push_back( I );
	}
}

void TaylorModelVec::intEval( vector<Interval>& result, const vector<Interval>& domain ) const {
	result.clear();
	for ( int i = 0; i < tms.size(); ++i ) {
		Interval I;
		tms[i].intEval( I, domain );
		result.push_back( I );
	}
}

void TaylorModelVec::intEvalNormal( vector<Interval>& result, const vector<Interval>& step_exp_table ) const {
	result.clear();
	for ( int i = 0; i < tms.size(); ++i ) {
		Interval I;
		tms[i].intEvalNormal( I, step_exp_table );
		result.push_back( I );
	}
}

void TaylorModelVec::ctrunc( const vector<Interval>& domain, const int order ) {
	for ( int i = 0; i < tms.size(); ++i )
		tms[i].ctrunc( domain, order );
}

void TaylorModelVec::nctrunc( const int order ) {
	for ( int i = 0; i < tms.size(); ++i )
		tms[i].nctrunc( order );
}

void TaylorModelVec::ctrunc_normal( const vector<Interval>& step_exp_table, const int order ) {
	for ( int i = 0; i < tms.size(); ++i )
		tms[i].ctrunc_normal( step_exp_table, order );
}

void TaylorModelVec::ctrunc( const vector<Interval>& domain, const vector<int>& orders ) {
	for ( int i = 0; i < tms.size(); ++i )
		tms[i].ctrunc( domain, orders[i] );
}

void TaylorModelVec::nctrunc( const vector<int>& orders ) {
	for ( int i = 0; i < tms.size(); ++i )
		tms[i].nctrunc( orders[i] );
}

void TaylorModelVec::ctrunc_normal( const vector<Interval>& step_exp_table, const vector<int>& orders ) {
	for ( int i = 0; i < tms.size(); ++i )
		tms[i].ctrunc_normal( step_exp_table, orders[i] );
}

void TaylorModelVec::inv( TaylorModelVec& result ) const {
	result.clear();
	for ( int i = 0; i < tms.size(); ++i ) {
		TaylorModel tmTemp;
		tms[i].inv( tmTemp );
		result.tms.push_back( tmTemp );
	}
}

void TaylorModelVec::add( TaylorModelVec& result, const TaylorModelVec& tmv ) const {
	result.clear();

	if ( tms.size() != tmv.tms.size() ) {
		printf( "Dimensions do not coincide.\n" );
		return;
	}

	for ( int i = 0; i < tms.size(); ++i ) {
		TaylorModel tmTemp;
		tms[i].add( tmTemp, tmv.tms[i] );
		result.tms.push_back( tmTemp );
	}
}

void TaylorModelVec::sub( TaylorModelVec& result, const TaylorModelVec& tmv ) const {
	result.clear();

	if ( tms.size() != tmv.tms.size() ) {
		printf( "Dimensions do not coincide.\n" );
		return;
	}

	for ( int i = 0; i < tms.size(); ++i ) {
		TaylorModel tmTemp;
		tms[i].sub( tmTemp, tmv.tms[i] );
		result.tms.push_back( tmTemp );
	}
}

void TaylorModelVec::add_assign( const TaylorModelVec& tmv ) {
	TaylorModelVec result;
	add( result, tmv );
	*this = result;
}

void TaylorModelVec::sub_assign( const TaylorModelVec& tmv ) {
	TaylorModelVec result;
	sub( result, tmv );
	*this = result;
}

void TaylorModelVec::mul( TaylorModelVec& result, const Interval& I ) const {
	result.clear();

	for ( int i = 0; i < tms.size(); ++i ) {
		TaylorModel tmTemp;
		tms[i].mul( tmTemp, I );
		result.tms.push_back( tmTemp );
	}
}

void TaylorModelVec::mul_assign( const Interval& I ) {
	TaylorModelVec result;
	mul( result, I );
	*this = result;
}

void TaylorModelVec::div( TaylorModelVec& result, const Interval& I ) const {
	result.clear();

	for ( int i = 0; i < tms.size(); ++i ) {
		TaylorModel tmTemp;
		tms[i].div( tmTemp, I );
		result.tms.push_back( tmTemp );
	}
}

void TaylorModelVec::div_assign( const Interval& I ) {
	TaylorModelVec result;
	div( result, I );
	*this = result;
}

void TaylorModelVec::derivative( TaylorModelVec& result, const int varIndex ) const {
	result.clear();
	for ( int i = 0; i < tms.size(); ++i ) {
		TaylorModel tmTemp;
		tms[i].derivative( tmTemp, varIndex );
		result.tms.push_back( tmTemp );
	}
}

void TaylorModelVec::LieDerivative_no_remainder( TaylorModelVec& result, const TaylorModelVec& f, const int order ) const {
	result.clear();
	for ( int i = 0; i < tms.size(); ++i ) {
		TaylorModel tmTemp;
		tms[i].LieDerivative_no_remainder( tmTemp, f, order );
		result.tms.push_back( tmTemp );
	}
}

void TaylorModelVec::LieDerivative_no_remainder( TaylorModelVec& result, const TaylorModelVec& f, const vector<int>& orders ) const {
	result.clear();
	for ( int i = 0; i < tms.size(); ++i ) {
		TaylorModel tmTemp;
		tms[i].LieDerivative_no_remainder( tmTemp, f, orders[i] );
		result.tms.push_back( tmTemp );
	}
}

void TaylorModelVec::integral( TaylorModelVec& result, const Interval& I ) const {
	result.clear();
	for ( int i = 0; i < tms.size(); ++i ) {
		TaylorModel tmTemp;
		tms[i].integral( tmTemp, I );
		result.tms.push_back( tmTemp );
	}
}

void TaylorModelVec::integral_no_remainder( TaylorModelVec& result ) const {
	result.clear();
	for ( int i = 0; i < tms.size(); ++i ) {
		TaylorModel tmTemp;
		tms[i].integral_no_remainder( tmTemp );
		result.tms.push_back( tmTemp );
	}
}

void TaylorModelVec::linearCoefficients( vector<vector<Interval> >& result ) const {
	for ( int i = 0; i < tms.size(); ++i )
		tms[i].linearCoefficients( result[i] );
}

void TaylorModelVec::insert( TaylorModelVec& result, const TaylorModelVec& vars, const vector<Interval>& varsPolyRange, const vector<Interval>& domain ) const {
	result.clear();

	for ( int i = 0; i < tms.size(); ++i ) {
		TaylorModel tmTemp;
		tms[i].insert( tmTemp, vars, varsPolyRange, domain );
		result.tms.push_back( tmTemp );
	}
}

void TaylorModelVec::insert_ctrunc( TaylorModelVec& result, const TaylorModelVec& vars, const vector<Interval>& varsPolyRange, const vector<Interval>& domain, const int order ) const {
	result.clear();

	for ( int i = 0; i < tms.size(); ++i ) {
		TaylorModel tmTemp;
		tms[i].insert_ctrunc( tmTemp, vars, varsPolyRange, domain, order );
		result.tms.push_back( tmTemp );
	}
}

void TaylorModelVec::insert_no_remainder( TaylorModelVec& result, const TaylorModelVec& vars, const int numVars, const int order ) const {
	result.clear();

	for ( int i = 0; i < tms.size(); ++i ) {
		TaylorModel tmTemp;
		tms[i].insert_no_remainder( tmTemp, vars, numVars, order );
		result.tms.push_back( tmTemp );
	}
}

void TaylorModelVec::insert_ctrunc_normal( TaylorModelVec& result, const TaylorModelVec& vars, const vector<Interval>& varsPolyRange, const vector<Interval>& step_exp_table, const int numVars, const int order ) const {
	result.clear();

	for ( int i = 0; i < tms.size(); ++i ) {
		TaylorModel tmTemp;
		tms[i].insert_ctrunc_normal( tmTemp, vars, varsPolyRange, step_exp_table, numVars, order );
		result.tms.push_back( tmTemp );
	}
}

void TaylorModelVec::insert_ctrunc( TaylorModelVec& result, const TaylorModelVec& vars, const vector<Interval>& varsPolyRange, const vector<Interval>& domain, const vector<int>& orders ) const {
	result.clear();

	for ( int i = 0; i < tms.size(); ++i ) {
		TaylorModel tmTemp;
		tms[i].insert_ctrunc( tmTemp, vars, varsPolyRange, domain, orders[i] );
		result.tms.push_back( tmTemp );
	}
}

void TaylorModelVec::insert_no_remainder( TaylorModelVec& result, const TaylorModelVec& vars, const int numVars, const vector<int>& orders ) const {
	result.clear();

	for ( int i = 0; i < tms.size(); ++i ) {
		TaylorModel tmTemp;
		tms[i].insert_no_remainder( tmTemp, vars, numVars, orders[i] );
		result.tms.push_back( tmTemp );
	}
}

void TaylorModelVec::insert_ctrunc_normal( TaylorModelVec& result, const TaylorModelVec& vars, const vector<Interval>& varsPolyRange, const vector<Interval>& step_exp_table, const int numVars, const vector<int>& orders ) const {
	result.clear();

	for ( int i = 0; i < tms.size(); ++i ) {
		TaylorModel tmTemp;
		tms[i].insert_ctrunc_normal( tmTemp, vars, varsPolyRange, step_exp_table, numVars, orders[i] );
		result.tms.push_back( tmTemp );
	}
}

void TaylorModelVec::evaluate_t( TaylorModelVec& result, const vector<Interval>& step_exp_table ) const {
	result.clear();

	for ( int i = 0; i < tms.size(); ++i ) {
		TaylorModel tmTemp;
		tms[i].evaluate_t( tmTemp, step_exp_table );
		result.tms.push_back( tmTemp );
	}
}

void TaylorModelVec::mul( TaylorModelVec& result, const int varIndex, const int degree ) const {
	result.clear();

	for ( int i = 0; i < tms.size(); ++i ) {
		TaylorModel tmTemp;
		tms[i].mul( tmTemp, varIndex, degree );
		result.tms.push_back( tmTemp );
	}
}

void TaylorModelVec::mul_assign( const int varIndex, const int degree ) {
	for ( int i = 0; i < tms.size(); ++i )
		tms[i].mul_assign( varIndex, degree );
}

void TaylorModelVec::linearTrans( TaylorModelVec& result, const Matrix& A ) const {
	result.clear();
	if ( tms.size() != A.cols() ) {
		printf( "Dimensions do not coincide.\n" );
		return;
	}

	int rows = A.rows();
	for ( int i = 0; i < rows; ++i ) {
		TaylorModel tm1;

		for ( int j = 0; j < A.cols(); ++j ) {
			TaylorModel tm2;
			Interval I( A.get( i, j ) );
			tms[j].mul( tm2, I );
			tm1.add_assign( tm2 );
		}

		result.tms.push_back( tm1 );
	}
}

void TaylorModelVec::linearTrans_assign( const Matrix& A ) {
	TaylorModelVec result;
	linearTrans( result, A );
	*this = result;
}

void TaylorModelVec::rmConstant() {
	for ( int i = 0; i < tms.size(); ++i )
		tms[i].rmConstant();
}

void TaylorModelVec::cutoff_normal( const vector<Interval>& step_exp_table ) {
	for ( int i = 0; i < tms.size(); ++i )
		tms[i].cutoff_normal( step_exp_table );
}

void TaylorModelVec::cutoff( const vector<Interval>& domain ) {
	for ( int i = 0; i < tms.size(); ++i )
		tms[i].cutoff( domain );
}

void TaylorModelVec::cutoff() {
	for ( int i = 0; i < tms.size(); ++i )
		tms[i].cutoff();
}

void TaylorModelVec::Picard_no_remainder( TaylorModelVec& result, const TaylorModelVec& x0, const vector<HornerForm>& ode, const int numVars, const int order ) const {
	TaylorModelVec tmvTemp;

	if ( order <= 1 ) {
		for ( int i = 0; i < ode.size(); ++i ) {
			TaylorModel tmTemp;
			ode[i].insert_no_remainder( tmTemp, *this, numVars, 0 );
			tmvTemp.tms.push_back( tmTemp );
		}
	} else {
		for ( int i = 0; i < ode.size(); ++i ) {
			TaylorModel tmTemp;
			ode[i].insert_no_remainder( tmTemp, *this, numVars, order - 1 );
			tmvTemp.tms.push_back( tmTemp );
		}
	}

	TaylorModelVec tmvTemp2;
	tmvTemp.integral_no_remainder( tmvTemp2 );

	x0.add( result, tmvTemp2 );
}

void TaylorModelVec::Picard_no_remainder_assign( const TaylorModelVec& x0, const vector<HornerForm>& ode, const int numVars, const int order ) {
	TaylorModelVec result;
	Picard_no_remainder( result, x0, ode, numVars, order );
	*this = result;
}

void TaylorModelVec::Picard_ctrunc_normal( TaylorModelVec& result, const TaylorModelVec& x0, const vector<Interval>& polyRange, const vector<HornerForm>& ode, const vector<Interval>& step_exp_table, const int numVars, const int order ) const {
	TaylorModelVec tmvTemp;

	if ( order <= 1 ) {
		for ( int i = 0; i < ode.size(); ++i ) {
			TaylorModel tmTemp;
			ode[i].insert_ctrunc_normal( tmTemp, *this, polyRange, step_exp_table, numVars, 0 );
			tmvTemp.tms.push_back( tmTemp );
		}
	} else {
		for ( int i = 0; i < ode.size(); ++i ) {
			TaylorModel tmTemp;
			ode[i].insert_ctrunc_normal( tmTemp, *this, polyRange, step_exp_table, numVars, order - 1 );
			tmvTemp.tms.push_back( tmTemp );
		}
	}

	TaylorModelVec tmvTemp2;
	tmvTemp.integral( tmvTemp2, step_exp_table[1] );

	x0.add( result, tmvTemp2 );
}

void TaylorModelVec::Picard_ctrunc_normal_assign( const TaylorModelVec& x0, const vector<Interval>& polyRange, const vector<HornerForm>& ode, const vector<Interval>& step_exp_table, const int numVars, const int order ) {
	TaylorModelVec result;
	Picard_ctrunc_normal( result, x0, polyRange, ode, step_exp_table, numVars, order );
	*this = result;
}

void TaylorModelVec::Picard_ctrunc_normal( TaylorModelVec& result, vector<RangeTree*>& trees, const TaylorModelVec& x0, const vector<Interval>& polyRange, const vector<HornerForm>& ode, const vector<Interval>& step_exp_table, const int numVars, const int order ) const {
	TaylorModelVec tmvTemp;

	trees.clear();
	for ( int i = 0; i < ode.size(); ++i ) {
		trees.push_back( NULL );
	}

	if ( order <= 1 ) {
		for ( int i = 0; i < ode.size(); ++i ) {
			TaylorModel tmTemp;
			ode[i].insert_ctrunc_normal( tmTemp, trees[i], *this, polyRange, step_exp_table, numVars, 0 );
			tmvTemp.tms.push_back( tmTemp );
		}
	} else {
		for ( int i = 0; i < ode.size(); ++i ) {
			TaylorModel tmTemp;
			ode[i].insert_ctrunc_normal( tmTemp, trees[i], *this, polyRange, step_exp_table, numVars, order - 1 );
			tmvTemp.tms.push_back( tmTemp );
		}
	}

	TaylorModelVec tmvTemp2;
	tmvTemp.integral( tmvTemp2, step_exp_table[1] );

	x0.add( result, tmvTemp2 );
}

void TaylorModelVec::Picard_ctrunc_normal( TaylorModelVec& result, vector<RangeTree*>& trees, const TaylorModelVec& x0, const vector<Interval>& polyRange, const vector<HornerForm>& ode, const vector<Interval>& step_exp_table, const int numVars, const vector<int>& orders ) const {
	TaylorModelVec tmvTemp;

	trees.clear();
	for ( int i = 0; i < ode.size(); ++i ) {
		trees.push_back( NULL );
	}

	for ( int i = 0; i < ode.size(); ++i ) {
		if ( orders[i] <= 1 ) {
			TaylorModel tmTemp;
			ode[i].insert_ctrunc_normal( tmTemp, trees[i], *this, polyRange, step_exp_table, numVars, 0 );
			tmvTemp.tms.push_back( tmTemp );
		} else {
			TaylorModel tmTemp;
			ode[i].insert_ctrunc_normal( tmTemp, trees[i], *this, polyRange, step_exp_table, numVars, orders[i] - 1 );
			tmvTemp.tms.push_back( tmTemp );
		}
	}

	TaylorModelVec tmvTemp2;
	tmvTemp.integral( tmvTemp2, step_exp_table[1] );

	x0.add( result, tmvTemp2 );
}

void TaylorModelVec::Picard_only_remainder( vector<Interval>& result, vector<RangeTree*>& trees, const TaylorModelVec& x0, const vector<HornerForm>& ode, const Interval& timeStep ) const {
	result.clear();

	for ( int i = 0; i < ode.size(); ++i ) {
		Interval intTemp;
		ode[i].insert_only_remainder( intTemp, trees[i], *this, timeStep );
		intTemp *= timeStep;
		result.push_back( intTemp );
	}
}

void TaylorModelVec::Picard_no_remainder( TaylorModelVec& result, const TaylorModelVec& x0, const vector<HornerForm>& ode, const int numVars, const vector<int>& orders, const vector<bool>& bIncreased ) const {
	result = *this;

	for ( int i = 0; i < ode.size(); ++i ) {
		if ( bIncreased[i] ) {
			TaylorModel tmTemp;
			if ( orders[i] <= 1 ) {
				ode[i].insert_no_remainder( tmTemp, *this, numVars, 0 );
			} else {
				ode[i].insert_no_remainder( tmTemp, *this, numVars, orders[i] - 1 );
			}

			TaylorModel tmTemp2;
			tmTemp.integral_no_remainder( tmTemp2 );
			x0.tms[i].add( result.tms[i], tmTemp2 );
		}
	}
}

void TaylorModelVec::Picard_no_remainder_assign( const TaylorModelVec& x0, const vector<HornerForm>& ode, const int numVars, const vector<int>& orders, const vector<bool>& bIncreased ) {
	TaylorModelVec result;
	Picard_no_remainder( result, x0, ode, numVars, orders, bIncreased );
	*this = result;
}

void TaylorModelVec::Picard_ctrunc_normal( TaylorModelVec& result, const TaylorModelVec& x0, const vector<Interval>& polyRange, const vector<HornerForm>& ode, const vector<Interval>& step_exp_table, const int numVars, const vector<int>& orders ) const {
	TaylorModelVec tmvTemp;

	for ( int i = 0; i < ode.size(); ++i ) {
		TaylorModel tmTemp;
		if ( orders[i] <= 1 ) {
			ode[i].insert_ctrunc_normal( tmTemp, *this, polyRange, step_exp_table, numVars, 0 );
		} else {
			ode[i].insert_ctrunc_normal( tmTemp, *this, polyRange, step_exp_table, numVars, orders[i] - 1 );
		}
		tmvTemp.tms.push_back( tmTemp );
	}

	TaylorModelVec tmvTemp2;
	tmvTemp.integral( tmvTemp2, step_exp_table[1] );

	x0.add( result, tmvTemp2 );
}

void TaylorModelVec::Picard_ctrunc_normal_assign( const TaylorModelVec& x0, const vector<Interval>& polyRange, const vector<HornerForm>& ode, const vector<Interval>& step_exp_table, const int numVars, const vector<int>& orders ) {
	TaylorModelVec result;
	Picard_ctrunc_normal( result, x0, polyRange, ode, step_exp_table, numVars, orders );
	*this = result;
}

// using Taylor approximation
void TaylorModelVec::Picard_non_polynomial_taylor_no_remainder( TaylorModelVec& result, const TaylorModelVec& x0, const vector<string>& strOde, const int order, const vector<Interval>& uncertainty_centers ) const {
	TaylorModelVec tmvTemp;
	Interval intZero;
	int rangeDim = strOde.size();

	string prefix( str_prefix_taylor_polynomial );
	string suffix( str_suffix );

	parseSetting.clear();

	parseSetting.flowpipe = *this;

	if ( order <= 1 ) {
		parseSetting.order = 0;
	} else {
		parseSetting.order = order - 1;
	}

	for ( int i = 0; i < strOde.size(); ++i ) {
		parseSetting.strODE = prefix + strOde[i] + suffix;

		parseODE();	 // call the parser

		TaylorModel tmTemp( parseResult.expansion, intZero );

		if ( !uncertainty_centers[i].subseteq( intZero ) ) {
			TaylorModel tmCenter( uncertainty_centers[i], rangeDim + 1 );
			tmTemp.add_assign( tmCenter );
		}

		tmvTemp.tms.push_back( tmTemp );
	}

	TaylorModelVec tmvTemp2;
	tmvTemp.integral_no_remainder( tmvTemp2 );

	x0.add( result, tmvTemp2 );
}

void TaylorModelVec::Picard_non_polynomial_taylor_no_remainder_assign( const TaylorModelVec& x0, const vector<string>& strOde, const int order, const vector<Interval>& uncertainty_centers ) {
	TaylorModelVec result;
	Picard_non_polynomial_taylor_no_remainder( result, x0, strOde, order, uncertainty_centers );
	*this = result;
}

void TaylorModelVec::Picard_non_polynomial_taylor_no_remainder( TaylorModelVec& result, const TaylorModelVec& x0, const vector<string>& strOde, const vector<int>& orders, const vector<bool>& bIncreased, const vector<Interval>& uncertainty_centers ) const {
	result = *this;

	Interval intZero;
	int rangeDim = strOde.size();

	string prefix( str_prefix_taylor_polynomial );
	string suffix( str_suffix );

	parseSetting.clear();

	parseSetting.flowpipe = *this;

	for ( int i = 0; i < strOde.size(); ++i ) {
		if ( bIncreased[i] ) {
			if ( orders[i] <= 1 ) {
				parseSetting.order = 0;
			} else {
				parseSetting.order = orders[i] - 1;
			}

			parseSetting.strODE = prefix + strOde[i] + suffix;

			parseODE();	 // call the parser

			TaylorModel tmTemp( parseResult.expansion, intZero );

			if ( !uncertainty_centers[i].subseteq( intZero ) ) {
				TaylorModel tmCenter( uncertainty_centers[i], rangeDim + 1 );
				tmTemp.add_assign( tmCenter );
			}

			TaylorModel tmTemp2;
			tmTemp.integral_no_remainder( tmTemp2 );
			x0.tms[i].add( result.tms[i], tmTemp2 );
		}
	}
}

void TaylorModelVec::Picard_non_polynomial_taylor_no_remainder_assign( const TaylorModelVec& x0, const vector<string>& strOde, const vector<int>& orders, const vector<bool>& bIncreased, const vector<Interval>& uncertainty_centers ) {
	TaylorModelVec result;
	Picard_non_polynomial_taylor_no_remainder( result, x0, strOde, orders, bIncreased, uncertainty_centers );
	*this = result;
}

void TaylorModelVec::Picard_non_polynomial_taylor_ctrunc_normal( TaylorModelVec& result, const TaylorModelVec& x0, const vector<string>& strOde, const vector<Interval>& step_exp_table, const int order, const vector<Interval>& uncertainty_centers ) const {
	TaylorModelVec tmvTemp;
	Interval intZero;
	int rangeDim = strOde.size();

	string prefix( str_prefix_taylor_picard );
	string suffix( str_suffix );

	parseSetting.clear();

	parseSetting.flowpipe = *this;
	parseSetting.step_exp_table = step_exp_table;

	if ( order <= 1 ) {
		parseSetting.order = 0;
	} else {
		parseSetting.order = order - 1;
	}

	for ( int i = 0; i < strOde.size(); ++i ) {
		parseSetting.strODE = prefix + strOde[i] + suffix;

		parseODE();	 // call the parser

		TaylorModel tmTemp( parseResult.expansion, parseResult.remainder );

		if ( !uncertainty_centers[i].subseteq( intZero ) ) {
			TaylorModel tmCenter( uncertainty_centers[i], rangeDim + 1 );
			tmTemp.add_assign( tmCenter );
		}

		tmvTemp.tms.push_back( tmTemp );
	}

	TaylorModelVec tmvTemp2;
	tmvTemp.integral( tmvTemp2, step_exp_table[1] );

	x0.add( result, tmvTemp2 );
}

void TaylorModelVec::Picard_non_polynomial_taylor_ctrunc_normal_assign( const TaylorModelVec& x0, const vector<string>& strOde, const vector<Interval>& step_exp_table, const int order, const vector<Interval>& uncertainty_centers ) {
	TaylorModelVec result;
	Picard_non_polynomial_taylor_ctrunc_normal( result, x0, strOde, step_exp_table, order, uncertainty_centers );
	*this = result;
}

void TaylorModelVec::Picard_non_polynomial_taylor_ctrunc_normal( TaylorModelVec& result, const TaylorModelVec& x0, const vector<string>& strOde, const vector<Interval>& step_exp_table, const vector<int>& orders, const vector<Interval>& uncertainty_centers ) const {
	TaylorModelVec tmvTemp;
	Interval intZero;
	int rangeDim = strOde.size();

	string prefix( str_prefix_taylor_picard );
	string suffix( str_suffix );

	parseSetting.clear();

	parseSetting.flowpipe = *this;
	parseSetting.step_exp_table = step_exp_table;

	for ( int i = 0; i < strOde.size(); ++i ) {
		if ( orders[i] <= 1 ) {
			parseSetting.order = 0;
		} else {
			parseSetting.order = orders[i] - 1;
		}

		parseSetting.strODE = prefix + strOde[i] + suffix;

		parseODE();	 // call the parser

		TaylorModel tmTemp( parseResult.expansion, parseResult.remainder );

		if ( !uncertainty_centers[i].subseteq( intZero ) ) {
			TaylorModel tmCenter( uncertainty_centers[i], rangeDim + 1 );
			tmTemp.add_assign( tmCenter );
		}

		tmvTemp.tms.push_back( tmTemp );
	}

	TaylorModelVec tmvTemp2;
	tmvTemp.integral( tmvTemp2, step_exp_table[1] );

	x0.add( result, tmvTemp2 );
}

void TaylorModelVec::Picard_non_polynomial_taylor_ctrunc_normal_assign( const TaylorModelVec& x0, const vector<string>& strOde, const vector<Interval>& step_exp_table, const vector<int>& orders, const vector<Interval>& uncertainty_centers ) {
	TaylorModelVec result;
	Picard_non_polynomial_taylor_ctrunc_normal( result, x0, strOde, step_exp_table, orders, uncertainty_centers );
	*this = result;
}

void TaylorModelVec::Picard_non_polynomial_taylor_only_remainder( vector<Interval>& result, const TaylorModelVec& x0, const vector<string>& strOde, const Interval& timeStep, const int order ) const {
	result.clear();

	string prefix( str_prefix_taylor_remainder );
	string suffix( str_suffix );

	parseSetting.flowpipe = *this;
	parseSetting.iterRange = parseSetting.ranges.begin();

	if ( order <= 1 ) {
		parseSetting.order = 0;
	} else {
		parseSetting.order = order - 1;
	}

	for ( int i = 0; i < strOde.size(); ++i ) {
		Interval intTemp;

		parseSetting.strODE = prefix + strOde[i] + suffix;

		parseODE();	 // call the parser

		intTemp = parseResult.remainder * timeStep;
		result.push_back( intTemp );
	}
}

void TaylorModelVec::Picard_non_polynomial_taylor_only_remainder( vector<Interval>& result, const TaylorModelVec& x0, const vector<string>& strOde, const Interval& timeStep, const vector<int>& orders ) const {
	result.clear();

	string prefix( str_prefix_taylor_remainder );
	string suffix( str_suffix );

	parseSetting.flowpipe = *this;
	parseSetting.iterRange = parseSetting.ranges.begin();

	for ( int i = 0; i < strOde.size(); ++i ) {
		if ( orders[i] <= 1 ) {
			parseSetting.order = 0;
		} else {
			parseSetting.order = orders[i] - 1;
		}

		Interval intTemp;

		parseSetting.strODE = prefix + strOde[i] + suffix;

		parseODE();	 // call the parser

		intTemp = parseResult.remainder * timeStep;
		result.push_back( intTemp );
	}
}

void TaylorModelVec::normalize( vector<Interval>& domain ) {
	int domainDim = domain.size();
	int rangeDim = tms.size();

	// compute the center of the original domain and make it origin-centered
	vector<Interval> intVecCenter;
	for ( int i = 1; i < domainDim; ++i )  // we omit the time dimension
	{
		Interval intTemp;
		domain[i].remove_midpoint( intTemp );
		intVecCenter.push_back( intTemp );
	}

	// compute the scalars
	Interval intZero;
	vector<vector<Interval> > coefficients;
	vector<Interval> row;

	for ( int i = 0; i < domainDim; ++i ) {
		row.push_back( intZero );
	}

	for ( int i = 0; i < domainDim - 1; ++i ) {
		coefficients.push_back( row );
	}

	for ( int i = 1; i < domainDim; ++i ) {
		Interval M;
		domain[i].mag( M );
		coefficients[i - 1][i] = M;
	}

	TaylorModelVec newVars( coefficients );
	for ( int i = 0; i < domainDim - 1; ++i ) {
		TaylorModel tmTemp( intVecCenter[i], domainDim );
		newVars.tms[i].add_assign( tmTemp );
	}

	Interval intUnit( -1, 1 );
	for ( int i = 1; i < domainDim; ++i ) {
		domain[i] = intUnit;
	}

	for ( int i = 0; i < tms.size(); ++i ) {
		TaylorModel tmTemp;
		tms[i].insert_no_remainder_no_rounding( tmTemp, newVars, domainDim, tms[i].degree() );
		tms[i].expansion = tmTemp.expansion;
	}
}

void TaylorModelVec::polyRange( vector<Interval>& result, const vector<Interval>& domain ) const {
	result.clear();

	for ( int i = 0; i < tms.size(); ++i ) {
		Interval intTemp;
		tms[i].polyRange( intTemp, domain );
		result.push_back( intTemp );
	}
}

void TaylorModelVec::polyRangeNormal( vector<Interval>& result, const vector<Interval>& step_exp_table ) const {
	result.clear();

	for ( int i = 0; i < tms.size(); ++i ) {
		Interval intTemp;
		tms[i].polyRangeNormal( intTemp, step_exp_table );
		result.push_back( intTemp );
	}
}

TaylorModelVec& TaylorModelVec::operator=( const TaylorModelVec& tmv ) {
	if ( this == &tmv )
		return *this;

	tms = tmv.tms;
	return *this;
}

ParseSetting::ParseSetting() {
	iterRange = ranges.begin();
	order = 0;
}

ParseSetting::ParseSetting( const ParseSetting& setting ) {
	strODE = setting.strODE;

	ranges = setting.ranges;
	iterRange = setting.iterRange;

	step_exp_table = setting.step_exp_table;
	flowpipe = setting.flowpipe;
	order = setting.order;
}

ParseSetting::~ParseSetting() {
	ranges.clear();
	step_exp_table.clear();
}

void ParseSetting::clear() {
	ranges.clear();
	iterRange = ranges.begin();

	step_exp_table.clear();
}

ParseSetting& ParseSetting::operator=( const ParseSetting& setting ) {
	if ( this == &setting )
		return *this;

	strODE = setting.strODE;

	ranges = setting.ranges;
	iterRange = setting.iterRange;

	step_exp_table = setting.step_exp_table;
	flowpipe = setting.flowpipe;
	order = setting.order;

	return *this;
}

ParseResult::ParseResult() {
}

ParseResult::ParseResult( const ParseResult& result ) {
	expansion = result.expansion;
	remainder = result.remainder;
}

ParseResult::~ParseResult() {
}

ParseResult& ParseResult::operator=( const ParseResult& result ) {
	if ( this == &result )
		return *this;

	expansion = result.expansion;
	remainder = result.remainder;

	return *this;
}

void exp_taylor_remainder( Interval& result, const Interval& tmRange, const int order ) {
	Interval intProd = tmRange;

	for ( int i = 2; i <= order; ++i ) {
		intProd *= tmRange;
	}

	Interval J( 0, 1 );
	J *= tmRange;
	J.exp_assign();

	result = factorial_rec[order] * intProd * J;
}

void rec_taylor_remainder( Interval& result, const Interval& tmRange, const int order ) {
	Interval J( 0, 1 ), intOne( 1 ), intMOne( -1 );
	J *= tmRange;
	J += intOne;
	J.rec_assign();

	Interval intProd = J;
	intProd *= tmRange;
	intProd *= intMOne;

	result = intProd;

	for ( int i = 2; i <= order; ++i ) {
		result *= intProd;
	}

	result *= J;
}

void sin_taylor_remainder( Interval& result, const Interval& C, const Interval& tmRange, const int order ) {
	Interval intProd( tmRange );

	for ( int i = 2; i <= order; ++i ) {
		intProd *= tmRange;
	}

	Interval J( 0, 1 );
	J *= tmRange;
	J += C;

	int k = order % 4;

	switch ( k ) {
		case 0:
			J.sin_assign();
			break;
		case 1:
			J.cos_assign();
			break;
		case 2:
			J.sin_assign();
			J.inv_assign();
			break;
		case 3:
			J.cos_assign();
			J.inv_assign();
			break;
	}

	result = factorial_rec[order] * intProd * J;
}

void cos_taylor_remainder( Interval& result, const Interval& C, const Interval& tmRange, const int order ) {
	Interval intProd( tmRange );

	for ( int i = 2; i <= order; ++i ) {
		intProd *= tmRange;
	}

	Interval J( 0, 1 );
	J *= tmRange;
	J += C;

	int k = order % 4;

	switch ( k ) {
		case 0:
			J.cos_assign();
			break;
		case 1:
			J.sin_assign();
			J.inv_assign();
			break;
		case 2:
			J.cos_assign();
			J.inv_assign();
			break;
		case 3:
			J.sin_assign();
			break;
	}

	result = factorial_rec[order] * intProd * J;
}

void log_taylor_remainder( Interval& result, const Interval& tmRange, const int order ) {
	Interval J( 0, 1 );
	J *= tmRange;
	J.add_assign( 1.0 );
	J.rec_assign();

	Interval I = tmRange;
	I *= J;

	result = I;

	for ( int i = 2; i <= order; ++i ) {
		result *= I;
	}

	result.div_assign( (double)order );

	if ( ( order + 1 ) % 2 == 1 )  // order+1 is odd
	{
		result.inv_assign();
	}
}

void sqrt_taylor_remainder( Interval& result, const Interval& tmRange, const int order ) {
	Interval I( 0, 1 );
	I *= tmRange;
	I.add_assign( 1.0 );
	I.rec_assign();

	Interval intTemp;
	I.sqrt( intTemp );

	I *= tmRange;
	I.div_assign( 2.0 );

	Interval intProd = I;

	int n = order - 1;
	for ( int i = 2; i <= n; ++i ) {
		intProd *= I;
	}

	intProd /= intTemp;
	intProd *= tmRange;
	intProd.div_assign( 2.0 );

	result = double_factorial[2 * order - 3] * factorial_rec[order] * intProd;

	if ( order % 2 == 0 ) {
		result.inv_assign();
	}
}

void exp_taylor_only_remainder( Interval& result, const Interval& remainder, list<Interval>::iterator& iterRange, const int order ) {
	Interval intZero;
	result = intZero;

	if ( !iterRange->valid() ) {
		++iterRange;
		return;
	}

	Interval const_part = *iterRange;
	++iterRange;

	for ( int i = order; i > 0; --i ) {
		Interval intFactor( 1 );
		intFactor.div_assign( (double)i );

		result *= intFactor;

		Interval intTemp;
		intTemp = ( *iterRange ) * remainder;  // P1 x I2
		++iterRange;
		intTemp += ( *iterRange ) * result;	 // P2 x I1
		intTemp += remainder * result;		 // I2 x I1
		++iterRange;
		intTemp += ( *iterRange );	// truncation
		++iterRange;

		result = intTemp;
	}

	result *= const_part;

	result += ( *iterRange );  // cutoff error
	++iterRange;

	Interval tmRange = ( *iterRange ) + remainder;
	++iterRange;

	Interval rem;
	exp_taylor_remainder( rem, tmRange, order + 1 );
	result += const_part * rem;
}

void rec_taylor_only_remainder( Interval& result, const Interval& remainder, list<Interval>::iterator& iterRange, const int order ) {
	Interval intZero;
	result = intZero;

	if ( !iterRange->valid() ) {
		++iterRange;
		return;
	}

	Interval const_part = *iterRange;
	++iterRange;

	Interval tmF_c_remainder = remainder * const_part;

	for ( int i = order; i > 0; --i ) {
		result.inv_assign();

		Interval intTemp;
		intTemp = ( *iterRange ) * tmF_c_remainder;	 // P1 x I2
		++iterRange;
		intTemp += ( *iterRange ) * result;	  // P2 x I1
		intTemp += tmF_c_remainder * result;  // I2 x I1
		++iterRange;
		intTemp += ( *iterRange );	// truncation
		++iterRange;

		result = intTemp;
	}

	result *= const_part;

	result += ( *iterRange );  // cutoff error
	++iterRange;

	Interval rem, tmF_cRange;
	tmF_cRange = ( *iterRange ) + tmF_c_remainder;
	++iterRange;

	rec_taylor_remainder( rem, tmF_cRange, order + 1 );

	result += rem * const_part;
}

void sin_taylor_only_remainder( Interval& result, const Interval& remainder, list<Interval>::iterator& iterRange, const int order ) {
	Interval intZero;
	result = intZero;

	if ( !iterRange->valid() ) {
		++iterRange;
		return;
	}

	Interval const_part = *iterRange;
	++iterRange;

	Interval tmPowerTmF_remainder;

	for ( int i = 1; i <= order; ++i ) {
		Interval intTemp;
		intTemp = ( *iterRange ) * remainder;  // P1 x I2
		++iterRange;
		intTemp += ( *iterRange ) * tmPowerTmF_remainder;  // P2 x I1
		intTemp += remainder * tmPowerTmF_remainder;	   // I2 x I1
		++iterRange;
		intTemp += ( *iterRange );	// truncation
		++iterRange;

		tmPowerTmF_remainder = intTemp;

		Interval intTemp2 = tmPowerTmF_remainder;

		intTemp2 *= ( *iterRange );
		++iterRange;

		result += intTemp2;
	}

	result += ( *iterRange );  // cutoff error
	++iterRange;

	Interval tmRange, rem;
	tmRange = ( *iterRange ) + remainder;
	++iterRange;

	sin_taylor_remainder( rem, const_part, tmRange, order + 1 );

	result += rem;
}

void cos_taylor_only_remainder( Interval& result, const Interval& remainder, list<Interval>::iterator& iterRange, const int order ) {
	Interval intZero;
	result = intZero;

	if ( !iterRange->valid() ) {
		++iterRange;
		return;
	}

	Interval const_part = *iterRange;
	++iterRange;

	int k = 1;

	Interval tmPowerTmF_remainder;

	for ( int i = 1; i <= order; ++i, ++k ) {
		Interval intTemp;
		intTemp = ( *iterRange ) * remainder;  // P1 x I2
		++iterRange;
		intTemp += ( *iterRange ) * tmPowerTmF_remainder;  // P2 x I1
		intTemp += remainder * tmPowerTmF_remainder;	   // I2 x I1
		++iterRange;
		intTemp += ( *iterRange );	// truncation
		++iterRange;

		tmPowerTmF_remainder = intTemp;

		Interval intTemp2 = tmPowerTmF_remainder;

		intTemp2 *= ( *iterRange );
		++iterRange;

		result += intTemp2;
	}

	result += ( *iterRange );  // cutoff error
	++iterRange;

	Interval tmRange, rem;
	tmRange = ( *iterRange ) + remainder;
	++iterRange;

	cos_taylor_remainder( rem, const_part, tmRange, order + 1 );

	result += rem;
}

void log_taylor_only_remainder( Interval& result, const Interval& remainder, list<Interval>::iterator& iterRange, const int order ) {
	Interval intZero;
	result = intZero;

	if ( !iterRange->valid() ) {
		++iterRange;
		return;
	}

	Interval C = *iterRange;
	++iterRange;

	Interval const_part = C;
	const_part.log_assign();

	Interval tmF_c_remainder = remainder / C;

	result = tmF_c_remainder;
	result.div_assign( (double)order );

	for ( int i = order; i >= 2; --i ) {
		result.inv_assign();

		Interval intTemp;
		intTemp = ( *iterRange ) * tmF_c_remainder;	 // P1 x I2
		++iterRange;
		intTemp += ( *iterRange ) * result;	  // P2 x I1
		intTemp += tmF_c_remainder * result;  // I2 x I1
		++iterRange;
		intTemp += ( *iterRange );	// truncation
		++iterRange;

		result = intTemp;
	}

	result += ( *iterRange );  // cutoff error
	++iterRange;

	Interval rem, tmF_cRange;
	tmF_cRange = ( *iterRange ) + tmF_c_remainder;
	++iterRange;

	log_taylor_remainder( rem, tmF_cRange, order + 1 );

	result += rem;
}

void sqrt_taylor_only_remainder( Interval& result, const Interval& remainder, list<Interval>::iterator& iterRange, const int order ) {
	Interval intZero;
	result = intZero;

	if ( !iterRange->valid() ) {
		++iterRange;
		return;
	}

	Interval C = *iterRange;
	++iterRange;

	Interval const_part = C;
	const_part.sqrt_assign();

	Interval intTwo( 2 );
	Interval tmF_2c_remainder = ( remainder / C ) / intTwo;

	result = tmF_2c_remainder;

	Interval K( 1 ), J( 1 );

	for ( int i = order, j = 2 * order - 3; i >= 2; --i, j -= 2 ) {
		// i
		Interval K( (double)i );

		// j = 2*i-3
		Interval J( (double)j );

		result.inv_assign();
		result *= J / K;

		Interval intTemp;
		intTemp = ( *iterRange ) * tmF_2c_remainder;  // P1 x I2
		++iterRange;
		intTemp += ( *iterRange ) * result;	   // P2 x I1
		intTemp += tmF_2c_remainder * result;  // I2 x I1
		++iterRange;
		intTemp += ( *iterRange );	// truncation
		++iterRange;

		result = intTemp;
	}

	result *= const_part;

	result += ( *iterRange );  // cutoff error
	++iterRange;

	Interval rem, tmF_cRange;
	tmF_cRange = ( *iterRange );
	++iterRange;

	tmF_cRange += tmF_2c_remainder * intTwo;

	sqrt_taylor_remainder( rem, tmF_cRange, order + 1 );

	result += rem * const_part;
}
