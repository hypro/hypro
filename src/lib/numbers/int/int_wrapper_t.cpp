/**
 * Wrapper class for double values. Implements the number_t base type.
 * Author: Benedikt Seidl
 * Version: Septemper 2013
 */

#include "int_wrapper_t.h"

namespace hypro
{
	int_wrapper_t::int_wrapper_t()
	{
		mValue = 0;
	}
	
	int_wrapper_t::int_wrapper_t(const int _i)
	{
		mValue = _i;
	}
	
	int_wrapper_t::int_wrapper_t(const std::string & _s)
	{
		// TODO
	}
	
	int_wrapper_t::~int_wrapper_t()
	{
	}
	
	bool int_wrapper_t::operator == (const int_wrapper_t & _rhs) const
	{
		return mValue == _rhs.mValue;
	}
	
	bool int_wrapper_t::operator != (const int_wrapper_t & _rhs) const
	{
		return mValue != _rhs.mValue;
	}
	
	bool int_wrapper_t::operator > (const int_wrapper_t & _rhs) const
	{
		return mValue > _rhs.mValue;
	}
	
	bool int_wrapper_t::operator < (const int_wrapper_t & _rhs) const
	{
		return mValue < _rhs.mValue;
	}
	
	bool int_wrapper_t::operator <= (const int_wrapper_t & _rhs) const
	{
		return mValue <= _rhs.mValue;
	}
	
	bool int_wrapper_t::operator >= (const int_wrapper_t & _rhs) const
	{
		return mValue >= _rhs.mValue;
	}
	
	int_wrapper_t & int_wrapper_t::operator = (const int_wrapper_t & _rhs)
	{
		if(this == &_rhs)
			return *this;	// check for self assmgnment
	
		mValue = _rhs.mValue;
		return *this;
	}
	
	int_wrapper_t & int_wrapper_t::operator += (const int_wrapper_t & _rhs)
	{
		mValue += _rhs.mValue;
		return *this;
	}
	
	int_wrapper_t & int_wrapper_t::operator -= (const int_wrapper_t & _rhs)
	{
		mValue -= _rhs.mValue;
		return *this;
	}
	
	int_wrapper_t & int_wrapper_t::operator *= (const int_wrapper_t & _rhs)
	{
		mValue *= _rhs.mValue;
		return *this;
	}
	
	int_wrapper_t & int_wrapper_t::operator /= (const int_wrapper_t & _rhs)
	{
		mValue /= _rhs.mValue;
		return *this;
	}
	
	int_wrapper_t & int_wrapper_t::operator ++ ()
	{
		mValue++;
		return *this;
	}
	
	int_wrapper_t & int_wrapper_t::operator -- ()
	{
		mValue--;
		return *this;
	}
	
	const int_wrapper_t int_wrapper_t::operator + (const int_wrapper_t & _rhs) const
	{
		int_wrapper_t result = *this;
		result += _rhs;
		return result;
	}
	
	const int_wrapper_t int_wrapper_t::operator - (const int_wrapper_t & _rhs) const
	{
		int_wrapper_t result = *this;
		result -= _rhs;
		return result;
	}
	
	const int_wrapper_t int_wrapper_t::operator * (const int_wrapper_t & _rhs) const
	{
		int_wrapper_t result = *this;
		result *= _rhs;
		return result;
	}
	
	const int_wrapper_t int_wrapper_t::operator / (const int_wrapper_t & _rhs) const
	{
		int_wrapper_t result = *this;
		result /= _rhs;
		return result;
	}
	
	int_wrapper_t int_wrapper_t::sqrt() const
	{
		return int_wrapper_t(std::sqrt(mValue));
	}
	
	int_wrapper_t int_wrapper_t::cbrt() const
	{
		//return int_wrapper_t(std::cbrt(mValue));
		throw "Not implemented";
	}
	
	int_wrapper_t int_wrapper_t::root(unsigned long int k) const
	{
		//return int_wrapper_t(std::root(mValue, k));
		throw "Not implemented";
	}
	
	int_wrapper_t int_wrapper_t::pow(int_wrapper_t & _rhs) const
	{
		return int_wrapper_t(std::pow(mValue, _rhs.mValue));
	}
	
	int_wrapper_t int_wrapper_t::abs() const
	{
		return int_wrapper_t(std::abs(mValue));
	}
	
	int int_wrapper_t::toInt() const
	{
		return mValue;
	}
	
	std::string int_wrapper_t::toString() const
	{
		// TODO
		return "";
	}
}