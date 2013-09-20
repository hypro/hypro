/**
 * Abstract base class for all floating number types.
 * Autho: Benedikt Seidl
 * Version: September 2013
 */

#pragma once

#include <string>

namespace hypro
{
	template<class FloatType>
	class HYPRO_FLOAT_T
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
                HYPRO_FLOAT_T() : mValue(){}
                
                HYPRO_FLOAT_T(const double& _double)
                {
//                    mValue = FloatType.fromDouble(_double);
                }
                
                HYPRO_FLOAT_T(const std::string _str)
                {
//                    mValue = FloatType.fromString(_str);
                }
                
                HYPRO_FLOAT_T(const FloatType& _float) : mValue(_float){}
                
                ~HYPRO_FLOAT_T(){}
                
                /**
                 * Getter & Setter
                 */
                FloatType& rValue()
                {
                    return mValue;
                }
                
                void setValue(FloatType _value)
                {
                    mValue = _value;
                }
                
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
                
		void pow(HYPRO_FLOAT_T& result, unsigned long int _exp) const
                {
                    result = HYPRO_FLOAT_T(mValue.pow(_exp));
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
