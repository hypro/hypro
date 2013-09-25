/**
 * Class for all floating number types.
 * Author: Benedikt Seidl
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
        
        HYPRO_FLOAT_T(const double _double)
        {
        	mValue = FloatType(_double);
        }
        
        HYPRO_FLOAT_T(const std::string & _str)
        {
        	mValue = FloatType(_str);
        }
        
        HYPRO_FLOAT_T(const FloatType& _float) : mValue(_float){}
        
        ~HYPRO_FLOAT_T(){}
        
        /**
         * Getter & Setter
         */
        
        FloatType& getValue()
        {
            return mValue;
        }
        
        void setValue(FloatType & _value)
        {
            mValue = _value;
        }
        
        /*************
         * Operators *
         *************/
        
        /**
         * boolean operators
         */
        
		bool inline operator == ( const HYPRO_FLOAT_T<FloatType>& _rhs) const
        {
            return mValue == _rhs.mValue;
        }
                
		bool inline operator != ( const HYPRO_FLOAT_T<FloatType> & _rhs) const
        {
            return mValue != _rhs.mValue;
        }
                
		bool inline operator > ( const HYPRO_FLOAT_T<FloatType> & _rhs) const
        {
            return mValue > _rhs.mValue;
        }
                
		bool inline operator < ( const HYPRO_FLOAT_T<FloatType> & _rhs) const
        {
            return mValue < _rhs.mValue;
        }
                
		bool inline operator <= ( const HYPRO_FLOAT_T<FloatType> & _rhs) const
        {
            return mValue <= _rhs.mValue;
        }
                
		bool inline operator >= ( const HYPRO_FLOAT_T<FloatType> & _rhs) const
        {
            return mValue >= _rhs.mValue;
        }

		/**
		 * arithmetic operators
		 */
		
		HYPRO_FLOAT_T<FloatType> & operator = (const HYPRO_FLOAT_T<FloatType> & _rhs)
        {
            mValue = _rhs.mValue;
            return *this;
        }
                
		HYPRO_FLOAT_T<FloatType> & operator += (const HYPRO_FLOAT_T<FloatType> & _rhs)
        {
            mValue += _rhs.mValue;
            return *this;
        }
                
		HYPRO_FLOAT_T<FloatType> & operator -= (const HYPRO_FLOAT_T<FloatType> & _rhs)
        {
            mValue -= _rhs.mValue;
            return *this;
        }
                
		HYPRO_FLOAT_T<FloatType> & operator *= (const HYPRO_FLOAT_T<FloatType> & _rhs)
        {
            mValue *= _rhs.mValue;
            return *this;
        }
                
		HYPRO_FLOAT_T<FloatType> & operator /= (const HYPRO_FLOAT_T<FloatType> & _rhs)
        {
            mValue /= _rhs.mValue;
            return *this;
        }
		
		HYPRO_FLOAT_T<FloatType> & operator ++ ()
		{
			++ mValue;
			return *this;
		}
		
		HYPRO_FLOAT_T<FloatType> & operator -- ()
		{
			-- mValue;
			return *this;
		}
                
		const HYPRO_FLOAT_T<FloatType> operator + (const HYPRO_FLOAT_T<FloatType> & _rhs) const
        {
            return HYPRO_FLOAT_T<FloatType>(mValue + _rhs.mValue);
        }
                
		const HYPRO_FLOAT_T<FloatType> operator - (const HYPRO_FLOAT_T<FloatType> & _rhs) const
        {
            return HYPRO_FLOAT_T<FloatType>(mValue - _rhs.mValue);
        }
                
		const HYPRO_FLOAT_T<FloatType> operator * (const HYPRO_FLOAT_T<FloatType> & _rhs) const
        {
            return HYPRO_FLOAT_T<FloatType>(mValue * _rhs.mValue);
        }
                
		const HYPRO_FLOAT_T<FloatType> operator / (const HYPRO_FLOAT_T<FloatType> & _rhs) const
        {
            return HYPRO_FLOAT_T<FloatType>(mValue / _rhs.mValue);
        }
		
		/**
		 * special operators
		 */
		
		HYPRO_FLOAT_T<FloatType> sqrt() const
        {
            return HYPRO_FLOAT_T<FloatType>(mValue.sqrt());
        }
                
		HYPRO_FLOAT_T<FloatType> cbrt() const
		{
			return HYPRO_FLOAT_T<FloatType>(mValue.cbrt());;
		}
		
		HYPRO_FLOAT_T<FloatType> root(unsigned long int k) const
		{
			return HYPRO_FLOAT_T<FloatType>(mValue.root(k));
		}
                
		HYPRO_FLOAT_T<FloatType> pow(unsigned long int _exp) const
        {
            return HYPRO_FLOAT_T<FloatType>(mValue.pow(_exp));
        }

		HYPRO_FLOAT_T<FloatType> abs() const
        {
            return HYPRO_FLOAT_T<FloatType>(mValue.abs());
        }

		/**
		 * conversion operators
		 */
		
		double toDouble() const
		{
			return mValue.toDouble();
		}
		
		std::string toString() const
		{
			return mValue.toString();
		}
	};
}
