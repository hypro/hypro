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
		mValue = 0;
	}
	
	double_wrapper_t::double_wrapper_t(const double _d)
	{
		mValue = _d;
	}
	
	double_wrapper_t::double_wrapper_t(const std::string & _s)
	{
		// TODO
	}
	
	double_wrapper_t::~double_wrapper_t()
	{
	}
	
	bool double_wrapper_t::operator == (const double_wrapper_t & _rhs) const
	{
		return mValue == _rhs.mValue;
	}
	
	bool double_wrapper_t::operator != (const double_wrapper_t & _rhs) const
	{
		return mValue != _rhs.mValue;
	}
	
	bool double_wrapper_t::operator > (const double_wrapper_t & _rhs) const
	{
		return mValue > _rhs.mValue;
	}
	
	bool double_wrapper_t::operator < (const double_wrapper_t & _rhs) const
	{
		return mValue < _rhs.mValue;
	}
	
	bool double_wrapper_t::operator <= (const double_wrapper_t & _rhs) const
	{
		return mValue <= _rhs.mValue;
	}
	
	bool double_wrapper_t::operator >= (const double_wrapper_t & _rhs) const
	{
		return mValue >= _rhs.mValue;
	}
	
	double_wrapper_t & double_wrapper_t::operator = (const double_wrapper_t & _rhs)
	{
		if(this == &_rhs)
			return *this;	// check for self assmgnment
	
		mValue = _rhs.mValue;
		return *this;
	}
	
	double_wrapper_t & double_wrapper_t::operator += (const double_wrapper_t & _rhs)
	{
		mValue += _rhs.mValue;
		return *this;
	}
	
	double_wrapper_t & double_wrapper_t::operator -= (const double_wrapper_t & _rhs)
	{
		mValue -= _rhs.mValue;
		return *this;
	}
	
	double_wrapper_t & double_wrapper_t::operator *= (const double_wrapper_t & _rhs)
	{
		mValue *= _rhs.mValue;
		return *this;
	}
	
	double_wrapper_t & double_wrapper_t::operator /= (const double_wrapper_t & _rhs)
	{
		mValue /= _rhs.mValue;
		return *this;
	}
	
	double_wrapper_t & double_wrapper_t::operator ++ ()
	{
		mValue++;
		return *this;
	}
	
	double_wrapper_t & double_wrapper_t::operator -- ()
	{
		mValue--;
		return *this;
	}
	
	const double_wrapper_t double_wrapper_t::operator + (const double_wrapper_t & _rhs) const
	{
		double_wrapper_t result = *this;
		result += _rhs;
		return result;
	}
	
	const double_wrapper_t double_wrapper_t::operator - (const double_wrapper_t & _rhs) const
	{
		double_wrapper_t result = *this;
		result -= _rhs;
		return result;
	}
	
	const double_wrapper_t double_wrapper_t::operator * (const double_wrapper_t & _rhs) const
	{
		double_wrapper_t result = *this;
		result *= _rhs;
		return result;
	}
	
	const double_wrapper_t double_wrapper_t::operator / (const double_wrapper_t & _rhs) const
	{
		double_wrapper_t result = *this;
		result /= _rhs;
		return result;
	}
	
	double_wrapper_t double_wrapper_t::sqrt() const
	{
		return double_wrapper_t(std::sqrt(mValue));
	}
	
	double_wrapper_t double_wrapper_t::cbrt() const
	{
		//return double_wrapper_t(std::cbrt(mValue));
		throw "Not implemented";
	}
	
	double_wrapper_t double_wrapper_t::root(unsigned long int k) const
	{
		//return double_wrapper_t(std::root(mValue, k));
		throw "Not implemented";
	}
	
	double_wrapper_t double_wrapper_t::pow(double_wrapper_t & _rhs) const
	{
		return double_wrapper_t(std::pow(mValue, _rhs.mValue));
	}
	
	double_wrapper_t double_wrapper_t::abs() const
	{
		return double_wrapper_t(std::abs(mValue));
	}
	
	double double_wrapper_t::toDouble() const
	{
		return mValue;
	}
	
	std::string double_wrapper_t::toString() const
	{
		// TODO
		return "";
	}
}