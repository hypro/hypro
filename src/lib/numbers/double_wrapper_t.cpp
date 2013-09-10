/**
 * Wrapper class for double values. Implements the number_t base type.
 * Author: Benedikt Seidl
 * Version: Septemper 2013
 */

#include "double_wrapper_t.h"

namespace hypro
{
	double_wrapper_t::double_wrapper_t()
	{
		dou = 0;
	}
	
	double_wrapper_t::double_wrapper_t(const double d)
	{
		dou = d;
	}
	
	double_wrapper_t::~double_wrapper_t()
	{
	}
	
	bool double_wrapper_t::operator == (const double_wrapper_t & d) const
	{
		return dou == d.dou;
	}
	
	bool double_wrapper_t::operator != (const double_wrapper_t & d) const
	{
		return dou != d.dou;
	}
	
	bool double_wrapper_t::operator > (const double_wrapper_t & d) const
	{
		return dou > d.dou;
	}
	
	bool double_wrapper_t::operator < (const double_wrapper_t & d) const
	{
		return dou < d.dou;
	}
	
	bool double_wrapper_t::operator <= (const double_wrapper_t & d) const
	{
		return dou <= d.dou;
	}
	
	bool double_wrapper_t::operator >= (const double_wrapper_t & d) const
	{
		return dou >= d.dou;
	}
	
	double_wrapper_t & double_wrapper_t::operator = (const double_wrapper_t & d)
	{
		if(this == &d)
			return *this;	// check for self assmgnment
	
		dou = d.dou;
	
		return *this;
	}
	
	double_wrapper_t & double_wrapper_t::operator += (const double_wrapper_t & d)
	{
		dou += d.dou;
	
		return *this;
	}
	
	double_wrapper_t & double_wrapper_t::operator -= (const double_wrapper_t & d)
	{
		dou -= d.dou;
	
		return *this;
	}
	
	double_wrapper_t & double_wrapper_t::operator *= (const double_wrapper_t & d)
	{
		dou *= d.dou;
	
		return *this;
	}
	
	double_wrapper_t & double_wrapper_t::operator /= (const double_wrapper_t & d)
	{
		dou /= d.dou;
		
		return *this;
	}
	
	double_wrapper_t & double_wrapper_t::operator ++ ()
	{
		dou++;
	
		return *this;
	}
	
	double_wrapper_t & double_wrapper_t::operator -- ()
	{
		dou--;
	
		return *this;
	}
	
	const double_wrapper_t double_wrapper_t::operator + (const double_wrapper_t & d) const
	{
		double_wrapper_t result = *this;
		result += d;
		return result;
	}
	
	const double_wrapper_t double_wrapper_t::operator - (const double_wrapper_t & d) const
	{
		double_wrapper_t result = *this;
		result -= d;
		return result;
	}
	
	const double_wrapper_t double_wrapper_t::operator * (const double_wrapper_t & d) const
	{
		double_wrapper_t result = *this;
		result *= d;
		return result;
	}
	
	const double_wrapper_t double_wrapper_t::operator / (const double_wrapper_t & d) const
	{
		double_wrapper_t result = *this;
		result /= d;
		return result;
	}
	
	void double_wrapper_t::sqrt(double_wrapper_t & result) const
	{
		result.dou = std::sqrt(dou);
	}
	
	void double_wrapper_t::cbrt(double_wrapper_t & result) const
	{
		//result.dou = std::cbrt(dou);
		throw "Not implemented";
	}
	
	void double_wrapper_t::root(double_wrapper_t & result, unsigned long int k) const
	{
		//result.dou = std::root(dou, k);
		throw "Not implemented";
	}
	
	void double_wrapper_t::pow(double_wrapper_t & result, double_wrapper_t & d) const
	{
		result.dou = std::pow(dou, d.dou);
	}
	
	void double_wrapper_t::abs(double_wrapper_t & result) const
	{
		result.dou = std::abs(dou);
	}
	
	double double_wrapper_t::to_double() const
	{
		return dou;
	}
}