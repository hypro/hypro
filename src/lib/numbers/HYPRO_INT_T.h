/**
 * Class for all integer number types.
 * Author: Benedikt Seidl
 * Version: September 2013
 */

#pragma once

#include <string>
#include <iostream>

namespace hypro
{
	template<class IntType>
	class HYPRO_INT_T
	{
    private:
        /**
         * Member
         */
        IntType       mValue;
        
    public:
    	
        /**
         * Constructors & Destructors
         */
    	
        HYPRO_INT_T() : mValue(){}
        
        HYPRO_INT_T(const int _int)
        {
        	mValue = IntType(_int);
        }
        
        HYPRO_INT_T(const std::string & _str)
        {
        	mValue = IntType(_str);
        }
        
        HYPRO_INT_T(const IntType& _float) : mValue(_float){}
        
        ~HYPRO_INT_T(){}
        
        /**
         * Getter & Setter
         */
        
        IntType& getValue()
        {
            return mValue;
        }
        
        void setValue(IntType & _value)
        {
            mValue = _value;
        }
        
        /*************
         * Operators *
         *************/
        
        /**
         * boolean operators
         */
        
		bool inline operator == ( const HYPRO_INT_T<IntType> & _rhs) const
        {
            return mValue == _rhs.mValue;
        }
                
		bool inline operator != ( const HYPRO_INT_T<IntType> & _rhs) const
        {
            return mValue != _rhs.mValue;
        }
                
		bool inline operator > ( const HYPRO_INT_T<IntType> & _rhs) const
        {
            return mValue > _rhs.mValue;
        }
                
		bool inline operator < ( const HYPRO_INT_T<IntType> & _rhs) const
        {
            return mValue < _rhs.mValue;
        }
                
		bool inline operator <= ( const HYPRO_INT_T<IntType> & _rhs) const
        {
            return mValue <= _rhs.mValue;
        }
                
		bool inline operator >= ( const HYPRO_INT_T<IntType> & _rhs) const
        {
            return mValue >= _rhs.mValue;
        }

		/**
		 * arithmetic operators
		 */
		
		HYPRO_INT_T<IntType> & operator = (const HYPRO_INT_T<IntType> & _rhs)
        {
            mValue = _rhs.mValue;
            return *this;
        }
                
		HYPRO_INT_T<IntType> & operator += (const HYPRO_INT_T<IntType> & _rhs)
        {
            mValue += _rhs.mValue;
            return *this;
        }
                
		HYPRO_INT_T<IntType> & operator -= (const HYPRO_INT_T<IntType> & _rhs)
        {
            mValue -= _rhs.mValue;
            return *this;
        }
                
		HYPRO_INT_T<IntType> & operator *= (const HYPRO_INT_T<IntType> & _rhs)
        {
            mValue *= _rhs.mValue;
            return *this;
        }
                
		HYPRO_INT_T<IntType> & operator /= (const HYPRO_INT_T<IntType> & _rhs)
        {
            mValue /= _rhs.mValue;
            return *this;
        }
                
		const HYPRO_INT_T<IntType> operator + (const HYPRO_INT_T<IntType> & _rhs) const
        {
            return HYPRO_INT_T<IntType>(mValue + _rhs.mValue);
        }
                
		const HYPRO_INT_T<IntType> operator - (const HYPRO_INT_T<IntType> & _rhs) const
        {
            return HYPRO_INT_T<IntType>(mValue - _rhs.mValue);
        }
                
		const HYPRO_INT_T<IntType> operator * (const HYPRO_INT_T<IntType> & _rhs) const
        {
            return HYPRO_INT_T<IntType>(mValue * _rhs.mValue);
        }
                
		const HYPRO_INT_T<IntType> operator / (const HYPRO_INT_T<IntType> & _rhs) const
        {
            return HYPRO_INT_T<IntType>(mValue / _rhs.mValue);
        }
		
		HYPRO_INT_T<IntType> & operator ++ ()
		{
			mValue++;
			return *this;
		}
		
		HYPRO_INT_T<IntType> & operator -- ()
		{
			mValue--;
			return *this;
		}
		
		/**
		 * special operators
		 */
		
		HYPRO_INT_T<IntType> sqrt() const
        {
            return HYPRO_INT_T<IntType>(mValue.sqrt());
        }
                
		HYPRO_INT_T<IntType> cbrt() const
		{
			return HYPRO_INT_T<IntType>(mValue.cbrt());;
		}
		
		HYPRO_INT_T<IntType> root(unsigned long int k) const
		{
			return HYPRO_INT_T<IntType>(mValue.root(k));
		}
                
		HYPRO_INT_T<IntType> pow(unsigned long int _exp) const
        {
            return HYPRO_INT_T<IntType>(mValue.pow(_exp));
        }

		HYPRO_INT_T<IntType> abs() const
        {
            return HYPRO_INT_T<IntType>(mValue.abs());
        }

		/**
		 * conversion operators
		 */
		
		double toInt() const
		{
			return mValue.toInt();
		}
		
		std::string toString() const
		{
			return mValue.toString();
		}

        /**
         *
         * @param ostr
         * @param p
         * @return
         */
        friend std::ostream & operator<< (std::ostream& ostr, const HYPRO_INT_T<IntType> & p) {
            ostr << p.toString();
            return ostr;
        }
	};
}
