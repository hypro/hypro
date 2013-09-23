/**
 * Wrapper class for double values.
 * Author: Benedikt Seidl
 * Version: Septemper 2013
 */

#ifndef DOUBLE_WRAPPER_T_H_
#define DOUBLE_WRAPPER_T_H_

#include <cmath>
#include <string>

namespace hypro
{
//	class double_wrapper_t : public HYPRO_FLOAT_T<double_wrapper_t>
	class double_wrapper_t
	{
	private:
		double mValue;
	public:
		double_wrapper_t();
		double_wrapper_t(const double _d);
		double_wrapper_t(const std::string & _s);
		virtual ~double_wrapper_t();

		bool operator == (const double_wrapper_t & _rhs) const;
		bool operator != (const double_wrapper_t & _rhs) const;
		bool operator > (const double_wrapper_t & _rhs) const;
		bool operator < (const double_wrapper_t & _rhs) const;
		bool operator <= (const double_wrapper_t & _rhs) const;
		bool operator >= (const double_wrapper_t & _rhs) const;

		double_wrapper_t & operator = (const double_wrapper_t & _rhs);
		double_wrapper_t & operator += (const double_wrapper_t & _rhs);
		double_wrapper_t & operator -= (const double_wrapper_t & _rhs);
		double_wrapper_t & operator *= (const double_wrapper_t & _rhs);
		double_wrapper_t & operator /= (const double_wrapper_t & _rhs);
		double_wrapper_t & operator ++ ();
		double_wrapper_t & operator -- ();

		const double_wrapper_t operator + (const double_wrapper_t & _rhs) const;
		const double_wrapper_t operator - (const double_wrapper_t & _rhs) const;
		const double_wrapper_t operator * (const double_wrapper_t & _rhs) const;
		const double_wrapper_t operator / (const double_wrapper_t & _rhs) const;

		double_wrapper_t sqrt() const;
		double_wrapper_t cbrt() const;						// Currently not supported
		double_wrapper_t root(unsigned long int k) const;	// Currently not supported
		double_wrapper_t pow(double_wrapper_t & _rhs) const;
		double_wrapper_t abs() const;

		double toDouble() const;
		std::string toString() const;
	};
}

#endif /*DOUBLE_WRAPPER_T_H_*/
