/**
 * Wrapper class for mpfr values. Implements the number_t base type.
 * Author: Benedikt Seidl
 * Version: Septemper 2013
 */

#ifndef MPFR_WRAPPER_T_H_
#define MPFR_WRAPPER_T_H_

#include "HYPRO_FLOAT_T.h"
#include "mpfr.h"

namespace hypro
{
	class mpfr_wrapper_t : public HYPRO_FLOAT_T<mpfr_wrapper_t>
	{
	private:
		mpfr_t mpfr;
		mpfr_rnd_t rnd;
	public:
		mpfr_wrapper_t();
		mpfr_wrapper_t(mpfr_t & mpfr_number, mpfr_rnd_t rounding_mode = MPFR_RNDN);
		mpfr_wrapper_t(const double double_number, mpfr_rnd_t rounding_mode = MPFR_RNDN);
		virtual ~mpfr_wrapper_t();
		
		void get_mpfr(mpfr_t & result) const;
		void set_mpfr(const mpfr_t & m);
		void get_rnd(mpfr_rnd_t & result) const;
		void set_rnd(const mpfr_rnd_t & r);
		
		bool operator == (const mpfr_wrapper_t & m) const;
		bool operator != (const mpfr_wrapper_t & m) const;
		bool operator > (const mpfr_wrapper_t & m) const;
		bool operator < (const mpfr_wrapper_t & m) const;
		bool operator <= (const mpfr_wrapper_t & m) const;
		bool operator >= (const mpfr_wrapper_t & m) const;
		
		mpfr_wrapper_t & operator = (const mpfr_wrapper_t & m);
		mpfr_wrapper_t & operator += (const mpfr_wrapper_t & m);
		mpfr_wrapper_t & operator -= (const mpfr_wrapper_t & m);
		mpfr_wrapper_t & operator *= (const mpfr_wrapper_t & m);
		mpfr_wrapper_t & operator /= (const mpfr_wrapper_t & m);
		mpfr_wrapper_t & operator ++ ();
		mpfr_wrapper_t & operator -- ();
	
		const mpfr_wrapper_t operator + (const mpfr_wrapper_t & m) const;
		const mpfr_wrapper_t operator - (const mpfr_wrapper_t & m) const;
		const mpfr_wrapper_t operator * (const mpfr_wrapper_t & m) const;
		const mpfr_wrapper_t operator / (const mpfr_wrapper_t & m) const;
		
		void sqrt(mpfr_wrapper_t & result) const;
		void cbrt(mpfr_wrapper_t & result) const;
		void root(mpfr_wrapper_t & result, unsigned long int k) const;
		void pow(mpfr_wrapper_t & result, mpfr_wrapper_t & m) const;
		void abs(mpfr_wrapper_t & result) const;
		
		double to_double() const;
	};
}

#endif /*MPFR_WRAPPER_T_H_*/
