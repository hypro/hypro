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
		mpfr_set_d(mpfr, 0, MPFR_RNDN);
		rnd = MPFR_RNDN;
	}
	
	mpfr_wrapper_t::mpfr_wrapper_t(const mpfr_t & mpfr_number, const mpfr_rnd_t rounding_mode, const mpfr_prec_t precision)
	{
		mpfr_init2(mpfr, precision);
		mpfr_set(mpfr, mpfr_number, rounding_mode);
		rnd = rounding_mode;
	}
	
	mpfr_wrapper_t::mpfr_wrapper_t(const double double_number, const mpfr_rnd_t rounding_mode, const mpfr_prec_t precision)
	{
		mpfr_init2(mpfr, precision);
		mpfr_set_d(mpfr, double_number, rounding_mode);
		rnd = rounding_mode;
	}
	
	mpfr_wrapper_t::mpfr_wrapper_t(const std::string & string_number, const mpfr_rnd_t rounding_mode, const mpfr_prec_t precision)
	{
		mpfr_init2(mpfr, precision);
		mpfr_set_str(mpfr, string_number.c_str(), 0, rounding_mode);	//  base == 0 to detect base
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
	
	mpfr_wrapper_t mpfr_wrapper_t::sqrt() const
	{
		mpfr_wrapper_t result;
		mpfr_sqrt(result.mpfr, mpfr, rnd);
		return result;
	}
	
	mpfr_wrapper_t mpfr_wrapper_t::cbrt() const
	{
		mpfr_wrapper_t result;
		mpfr_cbrt(result.mpfr, mpfr, rnd);
		return result;
	}
	
	mpfr_wrapper_t mpfr_wrapper_t::root(unsigned long int k) const
	{
		mpfr_wrapper_t result;
		mpfr_root(result.mpfr, mpfr, k, rnd);
		return result;
	}
	
	mpfr_wrapper_t mpfr_wrapper_t::pow(mpfr_wrapper_t & m) const
	{
		mpfr_wrapper_t result;
		mpfr_pow(result.mpfr, mpfr, m.mpfr, rnd);
		return result;
	}
	
	mpfr_wrapper_t mpfr_wrapper_t::abs() const
	{
		mpfr_wrapper_t result;
		mpfr_abs(result.mpfr, mpfr, rnd);
		return result;
	}
	
	double mpfr_wrapper_t::toDouble() const
	{
		return mpfr_get_d(mpfr, rnd);
	}
	
	std::string mpfr_wrapper_t::toString() const
	{
		// TODO: perhaps not the best method
		std::stringstream str;
		str << toDouble();   
		return str.str();
	}
}