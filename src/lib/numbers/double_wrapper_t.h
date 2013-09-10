/**
 * Wrapper class for double values. Implements the number_t base type.
 * Author: Benedikt Seidl
 * Version: Septemper 2013
 */

#ifndef DOUBLE_T_H_
#define DOUBLE_T_H_

#include "number_t.h"
#include <cmath>

class double_wrapper_t : public number_t<double_wrapper_t>
{
private:
	double dou;
public:
	double_wrapper_t();
	double_wrapper_t(const double d);
	virtual ~double_wrapper_t();
	
	bool operator == (const double_wrapper_t & m) const;
	bool operator != (const double_wrapper_t & m) const;
	bool operator > (const double_wrapper_t & m) const;
	bool operator < (const double_wrapper_t & m) const;
	bool operator <= (const double_wrapper_t & m) const;
	bool operator >= (const double_wrapper_t & m) const;

	double_wrapper_t & operator = (const double_wrapper_t & m);
	double_wrapper_t & operator += (const double_wrapper_t & m);
	double_wrapper_t & operator -= (const double_wrapper_t & m);
	double_wrapper_t & operator *= (const double_wrapper_t & m);
	double_wrapper_t & operator /= (const double_wrapper_t & m);
	double_wrapper_t & operator ++ ();
	double_wrapper_t & operator -- ();

	const double_wrapper_t operator + (const double_wrapper_t & m) const;
	const double_wrapper_t operator - (const double_wrapper_t & m) const;
	const double_wrapper_t operator * (const double_wrapper_t & m) const;
	const double_wrapper_t operator / (const double_wrapper_t & m) const;
	
	void sqrt(double_wrapper_t & result) const;
	void cbrt(double_wrapper_t & result) const;		// Currently not supported
	void root(double_wrapper_t & result, unsigned long int k) const;	// Currently not supported
	void pow(double_wrapper_t & result, double_wrapper_t & m) const;
	void abs(double_wrapper_t & result) const;
	
	double to_double() const;
};

#endif /*DOUBLE_T_H_*/
