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
//	class mpfr_wrapper_t : public HYPRO_FLOAT_T<mpfr_wrapper_t>
	class mpfr_wrapper_t
	{
	private:
		mpfr_t mpfr;	// the mpfr number
		mpfr_rnd_t rnd;	// the rounding mode
	public:
		/**
		 * Constructor
		 */
		mpfr_wrapper_t();
		
		/**
		 * Constructor
		 * @param mpfr_number the mpfr number
		 * @param rounding_mode the rounding mode
		 * @param precision the precision
		 */
		mpfr_wrapper_t(mpfr_t & mpfr_number, mpfr_rnd_t rounding_mode = MPFR_RNDN, mpfr_prec_t precision = MPFR_PREC_MIN);
		
		/**
		 * Constructor
		 * @param double_number the double number
		 * @param rounding_mode the rounding mode
		 * @param precision the precision
		 */
		mpfr_wrapper_t(const double double_number, mpfr_rnd_t rounding_mode = MPFR_RNDN, mpfr_prec_t precision = MPFR_PREC_MIN);
		
		/**
		 * Destructor
		 */
		virtual ~mpfr_wrapper_t();
		
		
		/**
		 * Gets the mpfr number.
		 * @param result the result
		 */
		void get_mpfr(mpfr_t & result) const;
		
		/**
		 * Sets the mpfr number.
		 * @param mpfr_number the mpfr number
		 */
		void set_mpfr(const mpfr_t & mpfr_number);
		
		/**
		 * Gets the rounding mode.
		 * @param result the result
		 */
		void get_rnd(mpfr_rnd_t & result) const;
		
		/**
		 * Sets the rounding mode.
		 * @param rounding_mode the rounding mode
		 */
		void set_rnd(const mpfr_rnd_t & rounding_mode);
		
		/**
		 * Gets the precision
		 * @param result the result
		 */
		void get_prec(mpfr_prec_t & result) const;
		
		/**
		 * Sets the precision
		 * @param precision the precision
		 */
		void set_prec(const mpfr_prec_t & precicision);
		
		// boolean operators
		bool operator == (const mpfr_wrapper_t & m) const;
		bool operator != (const mpfr_wrapper_t & m) const;
		bool operator > (const mpfr_wrapper_t & m) const;
		bool operator < (const mpfr_wrapper_t & m) const;
		bool operator <= (const mpfr_wrapper_t & m) const;
		bool operator >= (const mpfr_wrapper_t & m) const;
		
		// changing operators
		mpfr_wrapper_t & operator = (const mpfr_wrapper_t & m);
		mpfr_wrapper_t & operator += (const mpfr_wrapper_t & m);
		mpfr_wrapper_t & operator -= (const mpfr_wrapper_t & m);
		mpfr_wrapper_t & operator *= (const mpfr_wrapper_t & m);
		mpfr_wrapper_t & operator /= (const mpfr_wrapper_t & m);
		mpfr_wrapper_t & operator ++ ();
		mpfr_wrapper_t & operator -- ();

		// returning value operators
		const mpfr_wrapper_t operator + (const mpfr_wrapper_t & m) const;
		const mpfr_wrapper_t operator - (const mpfr_wrapper_t & m) const;
		const mpfr_wrapper_t operator * (const mpfr_wrapper_t & m) const;
		const mpfr_wrapper_t operator / (const mpfr_wrapper_t & m) const;
		
		// more complex operators
		void sqrt(mpfr_wrapper_t & result) const;
		void cbrt(mpfr_wrapper_t & result) const;
		void root(mpfr_wrapper_t & result, unsigned long int k) const;
		void pow(mpfr_wrapper_t & result, mpfr_wrapper_t & m) const;
		void abs(mpfr_wrapper_t & result) const;
		
		// convertion with double
		void from_double(const double d);
		double to_double() const;
	};
}

#endif /*MPFR_WRAPPER_T_H_*/
