/**
 * Abstract base class for all floating number types.
 * Autho: Benedikt Seidl
 * Version: September 2013
 */

#pragma once

#include "number_t.h"
#include "HYPRO_INT_T.h"
#include <string>

namespace hypro
{
	template<class FloatType>
	class HYPRO_FLOAT_T : public number_t<FloatType>
	{
            private:
                /**
                 * Member
                 */
                FloatType       mValue;
                
            public:
                /**
                 * Constructors & Destructors
                 */
                HYPRO_FLOAT_T();
                HYPRO_FLOAT_T(const double& _double);
                HYPRO_FLOAT_T(const std::string _str);
                HYPRO_FLOAT_T(const FloatType&);
                ~HYPRO_FLOAT_T();
                
                /**
                 * Operators
                 */
                
                // boolean operators
		bool inline operator == ( const HYPRO_FLOAT_T& _rhs) const
                {
                    return mValue == _rhs.mValue;
                }
                
		bool inline operator != ( const HYPRO_FLOAT_T& _rhs) const
                {
                    return mValue != _rhs.mValue;
                }
                
		bool inline operator > ( const HYPRO_FLOAT_T& _rhs) const
                {
                    return mValue > _rhs.mValue;
                }
                
		bool inline operator < ( const HYPRO_FLOAT_T& _rhs) const
                {
                    return mValue < _rhs.mValue;
                }
                
		bool inline operator <= ( const HYPRO_FLOAT_T& _rhs) const
                {
                    return mValue <= _rhs.mValue;
                }
                
		bool inline operator >= ( const HYPRO_FLOAT_T& _rhs) const
                {
                    return mValue >= _rhs.mValue;
                }

		// arithmetic operators
		HYPRO_FLOAT_T& operator = (const HYPRO_FLOAT_T& _rhs)
                {
                    mValue = _rhs.mValue;
                    return *this;
                }
                
		HYPRO_FLOAT_T& operator += (const HYPRO_FLOAT_T& _rhs)
                {
                    mValue += _rhs.mValue;
                    return *this;
                }
                
		HYPRO_FLOAT_T& operator -= (const HYPRO_FLOAT_T& _rhs)
                {
                    mValue -= _rhs.mValue;
                    return *this;
                }
                
		HYPRO_FLOAT_T& operator *= (const HYPRO_FLOAT_T& _rhs)
                {
                    mValue *= _rhs.mValue;
                    return *this;
                }
                
		HYPRO_FLOAT_T& operator /= (const HYPRO_FLOAT_T& _rhs)
                {
                    mValue /= _rhs.mValue;
                    return *this;
                }
                
		const HYPRO_FLOAT_T operator + (const HYPRO_FLOAT_T& _rhs) const
                {
                    HYPRO_FLOAT_T result = HYPRO_FLOAT_T(mValue + _rhs.mValue);
                    return result;
                }
                
		const HYPRO_FLOAT_T operator - (const HYPRO_FLOAT_T& _rhs) const
                {
                    HYPRO_FLOAT_T result = HYPRO_FLOAT_T(mValue - _rhs.mValue);
                    return result;
                }
                
		const HYPRO_FLOAT_T operator * (const HYPRO_FLOAT_T& _rhs) const
                {
                    HYPRO_FLOAT_T result = HYPRO_FLOAT_T(mValue * _rhs.mValue);
                    return result;
                }
                
		const HYPRO_FLOAT_T operator / (const HYPRO_FLOAT_T& _rhs) const
                {
                    HYPRO_FLOAT_T result = HYPRO_FLOAT_T(mValue / _rhs.mValue);
                    return result;
                }
		
		void sqrt(HYPRO_FLOAT_T& result) const
                {
                    result = HYPRO_FLOAT_T(mValue.sqrt());
                }
                
		void cbrt(HYPRO_FLOAT_T& result) const;
		void root(HYPRO_FLOAT_T& result, unsigned long int k) const;
                
		void pow(HYPRO_FLOAT_T& result, HYPRO_INT_T& _rhs) const
                {
                    result = HYPRO_FLOAT_T(mValue.pow(_rhs.mValue));
                }
		
                void abs(HYPRO_FLOAT_T& result) const
                {
                    result = HYPRO_FLOAT_T(mValue.abs());
                }

		// conversion operators
		void from_double(const double d);
		double to_double() const; 
	};
}
