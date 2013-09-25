/**
 * Wrapper class for integer values.
 * Author: Benedikt Seidl
 * Version: Septemper 2013
 */

#pragma once

#include <cmath>
#include <string>
#include <sstream>

namespace hypro
{
//	class int_wrapper_t : public HYPRO_INT_T<int_wrapper_t>
	class int_wrapper_t
	{
	private:
		int mValue;
	public:
		int_wrapper_t();
		int_wrapper_t(const int _i);
		int_wrapper_t(const std::string & _s);
		virtual ~int_wrapper_t();

		bool operator == (const int_wrapper_t & _rhs) const;
		bool operator != (const int_wrapper_t & _rhs) const;
		bool operator > (const int_wrapper_t & _rhs) const;
		bool operator < (const int_wrapper_t & _rhs) const;
		bool operator <= (const int_wrapper_t & _rhs) const;
		bool operator >= (const int_wrapper_t & _rhs) const;

		int_wrapper_t & operator = (const int_wrapper_t & _rhs);
		int_wrapper_t & operator += (const int_wrapper_t & _rhs);
		int_wrapper_t & operator -= (const int_wrapper_t & _rhs);
		int_wrapper_t & operator *= (const int_wrapper_t & _rhs);
		int_wrapper_t & operator /= (const int_wrapper_t & _rhs);
		int_wrapper_t & operator ++ ();
		int_wrapper_t & operator -- ();

		const int_wrapper_t operator + (const int_wrapper_t & _rhs) const;
		const int_wrapper_t operator - (const int_wrapper_t & _rhs) const;
		const int_wrapper_t operator * (const int_wrapper_t & _rhs) const;
		const int_wrapper_t operator / (const int_wrapper_t & _rhs) const;

		int_wrapper_t sqrt() const;
		int_wrapper_t cbrt() const;						// Currently not supported
		int_wrapper_t root(unsigned long int k) const;	// Currently not supported
		int_wrapper_t pow(int_wrapper_t & _rhs) const;
		int_wrapper_t abs() const;

		int toInt() const;
		std::string toString() const;
	};
}