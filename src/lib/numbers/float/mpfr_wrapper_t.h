/**
 * Wrapper class for mpfr values. Implements the number_t base type.
 * Author: Benedikt Seidl
 * Version: Septemper 2013
 */

#pragma once

#include "mpfr.h"
#include <string>
#include <sstream>

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
		mpfr_wrapper_t(const mpfr_t & mpfr_number, const mpfr_rnd_t rounding_mode = MPFR_RNDN, const mpfr_prec_t precision = MPFR_PREC_MIN);
		
		/**
		 * Constructor
		 * @param double_number the double number
		 * @param rounding_mode the rounding mode
		 * @param precision the precision
		 */
		mpfr_wrapper_t(const double double_number, const mpfr_rnd_t rounding_mode = MPFR_RNDN, const mpfr_prec_t precision = MPFR_PREC_MIN);
		
		/**
		 * Constructor
		 * @param string_number the string number
		 * @param rounding_mode the rounding mode
		 * @param precision the precision
		 */
		mpfr_wrapper_t(const std::string & string_number, const mpfr_rnd_t rounding_mode = MPFR_RNDN, const mpfr_prec_t precision = MPFR_PREC_MIN);
		
		/**
		 * Destructor
		 */
		~mpfr_wrapper_t();
		
		
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
		mpfr_wrapper_t sqrt() const;
		mpfr_wrapper_t cbrt() const;
		mpfr_wrapper_t root(unsigned long int k) const;
		mpfr_wrapper_t pow(mpfr_wrapper_t & m) const;
		mpfr_wrapper_t abs() const;
		
		// convertion with double
		double toDouble() const;
		std::string toString() const;
	};
}
