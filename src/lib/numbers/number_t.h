/**
 * Abstract representation of a number.
 * Author: Benedikt Seidl
 * Version: September 2013
 */

#ifndef NUMBER_FloatType_H_
#define NUMBER_FloatType_H_

namespace hypro
{
	template<class FloatType>
	class number_t
	{
	public:
		// boolean operators
		bool operator == (const FloatType& m) const;
		bool operator != (const FloatType& m) const;
		bool operator > (const FloatType& m) const;
		bool operator < (const FloatType& m) const;
		bool operator <= (const FloatType& m) const;
		bool operator >= (const FloatType& m) const;

		// changing operators
		FloatType& operator = (const FloatType& m);
		FloatType& operator += (const FloatType& m);
		FloatType& operator -= (const FloatType& m);
		FloatType& operator *= (const FloatType& m);
		FloatType& operator /= (const FloatType& m);
		FloatType& operator ++ ();
		FloatType& operator -- ();

		// returning value operators
		const FloatType operator + (const FloatType& m) const;
		const FloatType operator - (const FloatType& m) const;
		const FloatType operator * (const FloatType& m) const;
		const FloatType operator / (const FloatType& m) const;

		// more complex operators
		void sqrt(FloatType& result) const;
		void cbrt(FloatType& result) const;
		void root(FloatType& result, unsigned long int k) const;
		void pow(FloatType& result, FloatType& m) const;
		void abs(FloatType& result) const;

		// convertion with double
		void from_double(const double d);
		double to_double() const;
	};
}

#endif /*NUMBER_FloatType_H_*/
