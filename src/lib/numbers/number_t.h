/**
 * Abstract representation of a number.
 * Author: Benedikt Seidl
 * Version: September 2013
 */

#ifndef NUMBER_T_H_
#define NUMBER_T_H_

namespace hypro
{
	template<class T>
	class number_t
	{
	public:
		// boolean operators
		virtual bool operator == (const T & m) const = 0;
		virtual bool operator != (const T & m) const = 0;
		virtual bool operator > (const T & m) const = 0;
		virtual bool operator < (const T & m) const = 0;
		virtual bool operator <= (const T & m) const = 0;
		virtual bool operator >= (const T & m) const = 0;

		// changing operators
		virtual T & operator = (const T & m) = 0;
		virtual T & operator += (const T & m) = 0;
		virtual T & operator -= (const T & m) = 0;
		virtual T & operator *= (const T & m) = 0;
		virtual T & operator /= (const T & m) = 0;
		virtual T & operator ++ () = 0;
		virtual T & operator -- () = 0;

		// returning value operators
		virtual const T operator + (const T & m) const = 0;
		virtual const T operator - (const T & m) const = 0;
		virtual const T operator * (const T & m) const = 0;
		virtual const T operator / (const T & m) const = 0;

		// more complex operators
		virtual void sqrt(T & result) const = 0;
		virtual void cbrt(T & result) const = 0;
		virtual void root(T & result, unsigned long int k) const = 0;
		virtual void pow(T & result, T & m) const = 0;
		virtual void abs(T & result) const = 0;

		// convertion with double
		virtual void from_double(const double d) = 0;
		virtual double to_double() const = 0;
	};
}

#endif /*NUMBER_T_H_*/
