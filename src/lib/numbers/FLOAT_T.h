/**
 * General class for floating point numbers with different formats. Extend to
 * other types if necessary.
 * 
 * @file FLOAT_T.h
 * @author  Stefan Schupp
 * @since   2013-10-14
 * @version 2013-10-14
 */

#pragma once

#include <string>
#include <iostream>
#include <stdexcept>

namespace hypro
{
    enum RND{N=0, Z=1, U=2, D=3, A=4}; // nearest, towards zero, towards infty, towards -infty, away from zero
    typedef unsigned long precision;
    
    template<typename FloatType>
    class FLOAT_T;
    
    template<typename T1, typename T2>
    struct FloatConv
    {
        FLOAT_T<T1> operator() ( const FLOAT_T<T2>& _op2 ) const
        {
            return FLOAT_T<T1>(_op2.toDouble());
        }
    };
    
    template<typename FloatType>
    class FLOAT_T
    {
        private:
            FloatType mValue;		// mpfr_t
        
        public:
    	
            /**
             * Constructors & Destructors
             */

            FLOAT_T<FloatType>()
            {
                mValue = 0;
            }
            
            FLOAT_T<FloatType>(const double _double)
            {
                mValue = _double;
            }
            
            FLOAT_T<FloatType>(const float _float)
            {
                mValue = _float;
            }
            
            FLOAT_T<FloatType>(const int _int)
            {
                mValue = _int;
            }

            FLOAT_T<FloatType>(const double _double, precision _prec){}

//            template<>
//            FLOAT_T<double>(const double _double, RND _rnd, precision _prec)
//            {
//                // TODO: What if a lesser precision than the default double precision is chosen? -> truncate with respect to _rnd!
//                mValue = _double;
//            }
            
            ~FLOAT_T(){}

            
            /*******************
            * Getter & Setter *
            *******************/

           const FloatType& getValue() const
           {
               return mValue;
           }

           const precision getPrec() const
           {
               // TODO
               return 0;
           }

           FLOAT_T<FloatType>& setPrec( const precision& _prec, const RND _rnd=RND::N )
           {
               // TODO
               return *this;
           }
            
            /*************
             * Operators *
             *************/
            
            FLOAT_T<FloatType>& operator = (const FLOAT_T<FloatType> & _rhs)
            {
                mValue = _rhs.mValue;
                return *this;
            }
            
            /**
             * Boolean operators 
             */
            
            // TODO
            
            /**
             * arithmetic operations
             */
            
            FLOAT_T& add( const FLOAT_T<FloatType>& _op2, RND _rnd )
            {
                // TODO: Include rounding
                mValue = mValue + _op2.mValue;
                return *this;
            }
            
            FLOAT_T& add(const FLOAT_T& _op1, const FLOAT_T& _op2, RND _rnd)
            {
                // TODO: Include rounding
                mValue = _op1.mValue + _op2.mValue;
                return *this;
            }

            FLOAT_T& sub(const FLOAT_T& _op2, RND _rnd)
            {
                // TODO: Include rounding
                mValue = mValue - _op2.mValue;
                return *this;
            }
            
            FLOAT_T& sub(const FLOAT_T& _op1, const FLOAT_T& _op2, RND _rnd)
            {
                // TODO: Include rounding
                mValue = _op1.mValue - _op2.mValue;
                return *this;
            }
            
            FLOAT_T& mul_assign(const FLOAT_T& _op2, RND _rnd)
            {
                // TODO: Include rounding
                mValue = mValue * _op2.mValue;
                return *this;
            }
            
            void mul(FLOAT_T& result, const FLOAT_T& _op2, RND _rnd) const
            {
                // TODO: Include rounding
                result.mValue = mValue * _op2.mValue;
                return *this;
            }
            
            FLOAT_T& div(const FLOAT_T& _op2, RND _rnd) throw (std::invalid_argument)
            {
                if( _op2 == 0 ) throw ( std::invalid_argument( "Division by zero not allowed." ) );
                // TODO: Include rounding
                mValue = mValue - _op2.mValue;
                return *this;
            }
            
            FLOAT_T& div(const FLOAT_T& _op1, const FLOAT_T& _op2, RND _rnd) throw (std::invalid_argument)
            {
                if( _op2 == 0 ) throw ( std::invalid_argument( "Division by zero not allowed." ) );
                // TODO: Include rounding
                mValue = _op1.mValue - _op2.mValue;
                return *this;
            }
            
            /**
             * special operators
             */

            FLOAT_T& sqrt()
            {
                mValue = sqrt(mValue);
                return *this;
            }

            FLOAT_T& cbrt()
            {
                mValue = cbrt(mValue);
                return *this;
            }

            FLOAT_T& root(unsigned long int _k)
            {
                // TODO
                return *this;
            }

            FLOAT_T& pow(unsigned long int _exp)
            {
                mValue = pow(mValue, _exp);
                return *this;
            }

            FLOAT_T& abs( RND _rnd)
            {
                mValue = abs(mValue);
                return *this;
            }

            /**
             * conversion operators
             */
            double toDouble(RND _rnd=RND::N) const
            {
                return (double) mValue;
            }
            

            friend std::ostream & operator<< (std::ostream& ostr, const FLOAT_T<FloatType>& p) {
                ostr << p.toString();
                return ostr;
            }
            
            friend bool operator== (const FLOAT_T<FloatType>& _lhs, const FLOAT_T<FloatType>& _rhs)
            {
                return _lhs.mValue == _rhs.mValue;
            }
            
            /**
             * Overloaded operators
             */
            
            friend FLOAT_T<FloatType> operator +(const FLOAT_T<FloatType>& _lhs, const FLOAT_T<FloatType>& _rhs)
            {
                return FLOAT_T<FloatType>(_lhs.mValue + _rhs.mValue);
            }
            
            friend FLOAT_T<FloatType> operator -(const FLOAT_T<FloatType>& _lhs, const FLOAT_T<FloatType>& _rhs)
            {
                return _lhs - _rhs;
            }
            
            friend FLOAT_T<FloatType> operator *(const FLOAT_T<FloatType>& _lhs, const FLOAT_T<FloatType>& _rhs)
            {
                return _lhs * _rhs;
            }
            
            friend FLOAT_T<FloatType> operator /(const FLOAT_T<FloatType>& _lhs, const FLOAT_T<FloatType>& _rhs)
            {
                return _lhs / _rhs;
            }
            
            /**
             * Auxiliary Functions
             */
            
            std::string toString() const
            {
                std::stringstream str;
                str << mValue;   
                return str.str();
            }
    };
    
    #include "float/mpfr_float.tpp"
}
