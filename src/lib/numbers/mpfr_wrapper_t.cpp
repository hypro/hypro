/**
 * Wrapper class for mpfr values. Implements the number_t base type.
 * Author: Benedikt Seidl
 * Version: Septemper 2013
 */

#include "mpfr_wrapper_t.h"

namespace hypro
{
	mpfr_wrapper_t::mpfr_wrapper_t()
	{
		mpfr_init2(mpfr, MPFR_PREC_MIN);
		rnd = MPFR_RNDN;
	}
	
	mpfr_wrapper_t::mpfr_wrapper_t(mpfr_t & mpfr_number, mpfr_rnd_t rounding_mode, mpfr_prec_t precision)
	{
		mpfr_init2(mpfr, precision);
		mpfr_set(mpfr, mpfr_number, rounding_mode);
		rnd = rounding_mode;
	}
	
	mpfr_wrapper_t::mpfr_wrapper_t(double double_number, mpfr_rnd_t rounding_mode, mpfr_prec_t precision)
	{
		mpfr_init2(mpfr, precision);
		mpfr_set_d(mpfr, double_number, rounding_mode);
		rnd = rounding_mode;
	}
	
	mpfr_wrapper_t::~mpfr_wrapper_t()
	{
		mpfr_clear(mpfr);
	}
	
	void mpfr_wrapper_t::get_mpfr(mpfr_t & result) const
	{
		mpfr_set(result, mpfr, rnd);
	}
	
	void mpfr_wrapper_t::set_mpfr(const mpfr_t & mpfr_number)
	{
		mpfr_set(mpfr, mpfr_number, rnd);
	}
	
	void mpfr_wrapper_t::get_rnd(mpfr_rnd_t & result) const
	{
		result = rnd;
	}
	
	void mpfr_wrapper_t::set_rnd(const mpfr_rnd_t & rounding_mode)
	{
		rnd = rounding_mode;
	}
	
	void mpfr_wrapper_t::get_prec(mpfr_prec_t & result) const
	{
		result = mpfr_get_prec(mpfr);
	}
	
	void mpfr_wrapper_t::set_prec(const mpfr_prec_t & precision)
	{
		mpfr_set_prec(mpfr, precision);
	}
	
	bool mpfr_wrapper_t::operator == (const mpfr_wrapper_t & m) const
	{
		return mpfr_cmp(mpfr, m.mpfr) == 0;
	}
	
	bool mpfr_wrapper_t::operator != (const mpfr_wrapper_t & m) const
	{
		return mpfr_cmp(mpfr, m.mpfr) != 0;
	}
	
	bool mpfr_wrapper_t::operator > (const mpfr_wrapper_t & m) const
	{
		return mpfr_cmp(mpfr, m.mpfr) > 0;
	}
	
	bool mpfr_wrapper_t::operator < (const mpfr_wrapper_t & m) const
	{
		return mpfr_cmp(mpfr, m.mpfr) < 0;
	}
	
	bool mpfr_wrapper_t::operator <= (const mpfr_wrapper_t & m) const
	{
		return mpfr_cmp(mpfr, m.mpfr) <= 0;
	}
	
	bool mpfr_wrapper_t::operator >= (const mpfr_wrapper_t & m) const
	{
		return mpfr_cmp(mpfr, m.mpfr) >= 0;
	}
	
	mpfr_wrapper_t & mpfr_wrapper_t::operator = (const mpfr_wrapper_t & m)
	{
		if(this == &m)
			return *this;	// check for self assmgnment
	
		mpfr_set(mpfr, m.mpfr, rnd);
	
		return *this;
	}
	
	mpfr_wrapper_t & mpfr_wrapper_t::operator += (const mpfr_wrapper_t & m)
	{
		mpfr_add(mpfr, mpfr, m.mpfr, rnd);
	
		return *this;
	}
	
	mpfr_wrapper_t & mpfr_wrapper_t::operator -= (const mpfr_wrapper_t & m)
	{
		mpfr_sub(mpfr, mpfr, m.mpfr, rnd);
	
		return *this;
	}
	
	mpfr_wrapper_t & mpfr_wrapper_t::operator *= (const mpfr_wrapper_t & m)
	{
		mpfr_mul(mpfr, mpfr, m.mpfr, rnd);
	
		return *this;
	}
	
	mpfr_wrapper_t & mpfr_wrapper_t::operator /= (const mpfr_wrapper_t & m)
	{
		mpfr_div(mpfr, mpfr, m.mpfr, rnd);
		
		return *this;
	}
	
	mpfr_wrapper_t & mpfr_wrapper_t::operator ++ ()
	{
		mpfr_add_ui(mpfr, mpfr, 1L, rnd);
	
		return *this;
	}
	
	mpfr_wrapper_t & mpfr_wrapper_t::operator -- ()
	{
		mpfr_sub_ui(mpfr, mpfr, 1L, rnd);
	
		return *this;
	}
	
	const mpfr_wrapper_t mpfr_wrapper_t::operator + (const mpfr_wrapper_t & m) const
	{
		mpfr_wrapper_t result = *this;
		result += m;
		return result;
	}
	
	const mpfr_wrapper_t mpfr_wrapper_t::operator - (const mpfr_wrapper_t & m) const
	{
		mpfr_wrapper_t result = *this;
		result -= m;
		return result;
	}
	
	const mpfr_wrapper_t mpfr_wrapper_t::operator * (const mpfr_wrapper_t & m) const
	{
		mpfr_wrapper_t result = *this;
		result *= m;
		return result;
	}
	
	const mpfr_wrapper_t mpfr_wrapper_t::operator / (const mpfr_wrapper_t & m) const
	{
		mpfr_wrapper_t result = *this;
		result /= m;
		return result;
	}
	
	void mpfr_wrapper_t::sqrt(mpfr_wrapper_t & result) const
	{
		mpfr_sqrt(result.mpfr, mpfr, result.rnd);
	}
	
	void mpfr_wrapper_t::cbrt(mpfr_wrapper_t & result) const
	{
		mpfr_cbrt(result.mpfr, mpfr, result.rnd);
	}
	
	void mpfr_wrapper_t::root(mpfr_wrapper_t & result, unsigned long int k) const
	{
		mpfr_root(result.mpfr, mpfr, k, result.rnd);
	}
	
	void mpfr_wrapper_t::pow(mpfr_wrapper_t & result, mpfr_wrapper_t & m) const
	{
		mpfr_pow(result.mpfr, mpfr, m.mpfr, result.rnd);
	}
	
	void mpfr_wrapper_t::abs(mpfr_wrapper_t & result) const
	{
		mpfr_abs(result.mpfr, mpfr, result.rnd);
	}
	
	void mpfr_wrapper_t::from_double(const double d)
	{
		mpfr_set_d(mpfr, d, rnd);
	}
	
	double mpfr_wrapper_t::to_double() const
	{
		return mpfr_get_d(mpfr, rnd);
	}
}