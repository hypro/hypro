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
#include <assert.h>

#include <math.h>
#include <mpfr.h>

namespace hypro
{
		// nearest, towards zero, towards infty, towards -infty, away from zero
    enum HYPRO_RND
    {
        HYPRO_RNDN=0,
        HYPRO_RNDZ=1,
        HYPRO_RNDU=2,
        HYPRO_RNDD=3,
        HYPRO_RNDA=4
    };

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
            FloatType mValue;
        
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
//            FLOAT_T<double>(const double _double, HYPRO_RND _rnd, precision _prec)
//            {
//                // TODO: What if a lesser precision than the default double precision is chosen? -> truncate with respect to _rnd!
//                mValue = _double;
//            }
            
            FLOAT_T<FloatType>(const FLOAT_T<FloatType>& _float) : mValue(_float.mValue)
            {}
            
            ~FLOAT_T()
            {
            	// TODO: clear mValue if needed
            }

            
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

           FLOAT_T<FloatType>& setPrec( const precision& _prec, const HYPRO_RND _rnd=HYPRO_RND::HYPRO_RNDN )
           {
               // TODO
               return *this;
           }
            
            /*************
             * Operators *
             *************/
            
            inline FLOAT_T<FloatType>& operator = (const FLOAT_T<FloatType> & _rhs)
            {
                mValue = _rhs.mValue;
                return *this;
            }
            
            /**
             * Boolean operators 
             */
            
            inline bool operator == ( const FLOAT_T<FloatType>& _rhs) const
            {
                return mValue == _rhs.mValue;
            }

            inline bool operator != ( const FLOAT_T<FloatType> & _rhs) const
            {
                return mValue != _rhs.mValue;
            }

            inline bool operator > ( const FLOAT_T<FloatType> & _rhs) const
            {
                return mValue > _rhs.mValue;
            }

            inline bool operator < ( const FLOAT_T<FloatType> & _rhs) const
            {
                return mValue < _rhs.mValue;
            }

            inline bool operator <= ( const FLOAT_T<FloatType> & _rhs) const
            {
                return mValue <= _rhs.mValue;
            }

            inline bool operator >= ( const FLOAT_T<FloatType> & _rhs) const
            {
                return mValue >= _rhs.mValue;
            }
            
            /**
             * arithmetic operations
             */
            
            inline FLOAT_T& add_assign( const FLOAT_T<FloatType>& _op2, HYPRO_RND _rnd )
            {
                // TODO: Include rounding
                mValue = mValue + _op2.mValue;
                return *this;
            }
            
            inline void add( FLOAT_T& _result, const FLOAT_T& _op2, HYPRO_RND _rnd) const
            {
                // TODO: Include rounding
                _result.mValue = mValue + _op2.mValue;
            }

            inline FLOAT_T& sub_assign(const FLOAT_T& _op2, HYPRO_RND _rnd)
            {
                // TODO: Include rounding
                mValue = mValue - _op2.mValue;
                return *this;
            }
            
            inline void sub(FLOAT_T& _result, const FLOAT_T& _op2, HYPRO_RND _rnd) const
            {
                // TODO: Include rounding
                _result.mValue = mValue - _op2.mValue;
            }
            
            inline FLOAT_T& mul_assign(const FLOAT_T& _op2, HYPRO_RND _rnd)
            {
                // TODO: Include rounding
                mValue = mValue * _op2.mValue;
                // mValue.mul_assign(_op2.mValue, _rnd);
                return *this;
            }
            
            inline void mul(FLOAT_T& _result, const FLOAT_T& _op2, HYPRO_RND _rnd) const
            {
                // TODO: Include rounding
                _result.mValue = mValue * _op2.mValue;
            }
            
            inline FLOAT_T& div_assign(const FLOAT_T& _op2, HYPRO_RND _rnd)
            {
                assert( _op2 != 0 );
                // TODO: Include rounding
                mValue = mValue / _op2.mValue;
                return *this;
            }
            
            inline void div(FLOAT_T& _result, const FLOAT_T& _op2, HYPRO_RND _rnd) const
            {
                assert( _op2 != 0 );
                // TODO: Include rounding
                _result.mValue = mValue / _op2.mValue;
            }
            
            /**
             * special operators
             */

            inline FLOAT_T& sqrt_assign(HYPRO_RND _rnd = HYPRO_RNDN)
            {
                mValue = sqrt(mValue);
                return *this;
            }
            
            inline void sqrt(FLOAT_T& _result, HYPRO_RND _rnd = HYPRO_RNDN)
            {
            	_result.mValue = sqrt(mValue);
            }

            inline FLOAT_T& cbrt_assign(HYPRO_RND _rnd = HYPRO_RNDN)
            {
                mValue = cbrt(mValue);
                return *this;
            }
            
            inline FLOAT_T& cbrt(FLOAT_T& _result, HYPRO_RND _rnd = HYPRO_RNDN)
            {
            	_result.mValue = cbrt(mValue);
            }

            inline FLOAT_T& root_assign(unsigned long int _k, HYPRO_RND _rnd = HYPRO_RNDN)
            {
                // TODO
                return *this;
            }
            
            inline void root(FLOAT_T& _result, unsigned long int _k, HYPRO_RND _rnd = HYPRO_RNDN)
            {
            	// TODO
            }

            inline FLOAT_T& pow_assign(unsigned long int _exp, HYPRO_RND _rnd = HYPRO_RNDN)
            {
                mValue = pow(mValue, _exp);
                return *this;
            }
            
            inline void pow(FLOAT_T& _result, unsigned long int _exp, HYPRO_RND _rnd = HYPRO_RNDN)
            {
            	_result.mValue = pow(mValue, _exp);
            }

            inline FLOAT_T& abs_assign(HYPRO_RND _rnd = HYPRO_RNDN)
            {
                mValue = abs(mValue);
                return *this;
            }
            
            inline void abs(FLOAT_T& _result, HYPRO_RND _rnd = HYPRO_RNDN)
            {
            	_result.mValue = abs(mValue);
            }
            
            inline FLOAT_T& exp_assign(HYPRO_RND _rnd = HYPRO_RNDN)
            {
                mValue = exp(mValue);
                return *this;
            }
            
            inline void exp(FLOAT_T& _result, HYPRO_RND _rnd = HYPRO_RNDN)
            {
                _result.mValue = exp(mValue);
            }
            
            inline FLOAT_T& sin_assign(HYPRO_RND _rnd = HYPRO_RNDN)
            {
                mValue = sin(mValue);
                return *this;
            }
            
            inline void sin(FLOAT_T& _result, HYPRO_RND _rnd = HYPRO_RNDN)
            {
                _result.mValue = sin(mValue);
            }
            
            inline FLOAT_T& cos_assign(HYPRO_RND _rnd = HYPRO_RNDN)
            {
                mValue = cos(mValue);
                return *this;
            }
            
            inline void cos(FLOAT_T& _result, HYPRO_RND _rnd = HYPRO_RNDN)
            {
                _result.mValue = cos(mValue);
            }
            
            inline FLOAT_T& log_assign(HYPRO_RND _rnd = HYPRO_RNDN)
            {
                mValue = log(mValue);
                return *this;
            }
            
            inline void log(FLOAT_T& _result, HYPRO_RND _rnd = HYPRO_RNDN)
            {
                _result.mValue = log(mValue);
            }

            /**
             * conversion operators
             */
            inline double toDouble(HYPRO_RND _rnd=HYPRO_RND::HYPRO_RNDN) const
            {
                return (double) mValue;
            }
            

            inline friend std::ostream & operator<< (std::ostream& ostr, const FLOAT_T<FloatType>& p) {
                ostr << p.toString();
                return ostr;
            }
            
//            inline friend bool operator== (const FLOAT_T<FloatType>& _lhs, const FLOAT_T<FloatType>& _rhs)
//            {
//                return _lhs.mValue == _rhs.mValue;
//            }
            
            /**
             * Operators
             */
            
            inline friend FLOAT_T<FloatType> operator +(const FLOAT_T<FloatType>& _lhs, const FLOAT_T<FloatType>& _rhs)
            {
                return FLOAT_T<FloatType>(_lhs.mValue + _rhs.mValue);
            }
            
            inline friend FLOAT_T<FloatType> operator -(const FLOAT_T<FloatType>& _lhs, const FLOAT_T<FloatType>& _rhs)
            {
                return FLOAT_T<FloatType>(_lhs.mValue - _rhs.mValue);
            }
            
            inline friend FLOAT_T<FloatType> operator *(const FLOAT_T<FloatType>& _lhs, const FLOAT_T<FloatType>& _rhs)
            {
                return FLOAT_T<FloatType>(_lhs.mValue * _rhs.mValue);
            }
            
            inline friend FLOAT_T<FloatType> operator /(const FLOAT_T<FloatType>& _lhs, const FLOAT_T<FloatType>& _rhs)
            {
                return FLOAT_T<FloatType>(_lhs.mValue / _rhs.mValue);
            }
            
            inline friend FLOAT_T<FloatType>& operator ++(FLOAT_T<FloatType>& _num)
            {
                _num.mValue +=1;
                return _num;
            }
            
            inline friend FLOAT_T<FloatType>& operator --(FLOAT_T<FloatType>& _num)
            {
                _num.mValue -=1;
                return _num;
            }
            
            inline FLOAT_T<FloatType>& operator +=(const FLOAT_T<FloatType>& _rhs)
            {
                mValue + _rhs.mValue;
                return *this;
            }
            
            inline FLOAT_T<FloatType>& operator -=(const FLOAT_T<FloatType>& _rhs)
            {
                mValue - _rhs.mValue;
                return *this;
            }
            
            inline FLOAT_T<FloatType>& operator *=(const FLOAT_T<FloatType>& _rhs)
            {
                mValue * _rhs.mValue;
                return *this;
            }
            
            inline FLOAT_T<FloatType>& operator /=(const FLOAT_T<FloatType>& _rhs)
            {
                mValue / _rhs.mValue;
                return *this;
            }
            
            /**
             * Auxiliary Functions
             */
            
            inline std::string toString() const
            {
//                std::stringstream str;
//                str << mValue;   
//                return str.str();
                return std::to_string(mValue);
            }
    };
    
    #include "float/mpfr_float.tpp"
}
