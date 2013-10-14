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

namespace hypro
{
    enum RND{N=0, Z=1, U=2, D=3, A=4}; // nearest, towards zero, towards infty, towards -infty, away from zero
    typedef int precision;
    
    template<typename FloatType>
    class FLOAT_T
    {
        private:
            FloatType mValue;
        
        public:
    	
            /**
             * Constructors & Destructors
             */

            FLOAT_T<FloatType>(const double _double)
            {
            }

//            template<>
//            FLOAT_T<double>(const double _double)
//            {
//                mValue = _double;
//            }

            FLOAT_T<FloatType>(const double _double, precision _prec){}

//            template<>
//            FLOAT_T<double>(const double _double, RND _rnd, precision _prec)
//            {
//                // TODO: What if a lesser precision than the default double precision is chosen? -> truncate with respect to _rnd!
//                mValue = _double;
//            }

            FLOAT_T(const FloatType& _float){}

            template<typename DifferentType>
            FLOAT_T(const DifferentType& _float)
            {
                // TODO: Write specialized conversion operators here.
            }

            ~FLOAT_T(){}
            // TODO: Do we require specialized destructors?

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
            
            void add(FLOAT_T& _res, const FLOAT_T& _op1, const FLOAT_T& _op2, RND _rnd )
            {
                
            }
            
            FLOAT_T<FloatType> add(const FLOAT_T& _op1, const FLOAT_T& _op2, RND _rnd)
            {
                
            }

            /**
             * special operators
             */

//            FLOAT_T<FloatType> sqrt() const
//            {
//                return FLOAT_T<FloatType>(mValue.sqrt());
//            }
//
//            FLOAT_T<FloatType> cbrt() const
//            {
//                    return FLOAT_T<FloatType>(mValue.cbrt());;
//            }
//
//            FLOAT_T<FloatType> root(unsigned long int k) const
//            {
//                    return FLOAT_T<FloatType>(mValue.root(k));
//            }
//
//            FLOAT_T<FloatType> pow(unsigned long int _exp) const
//            {
//                return FLOAT_T<FloatType>(mValue.pow(_exp));
//            }
//
//            FLOAT_T<FloatType> abs() const
//            {
//                return FLOAT_T<FloatType>(mValue.abs());
//            }

            /**
             * conversion operators
             */

//            double toDouble() const
//            {
//                    return mValue.toDouble();
//            }
//
//            std::string toString() const
//            {
//                    return mValue.toString();
//            }
//
            friend std::ostream & operator<< (std::ostream& ostr, const FLOAT_T<FloatType> & p) {
                ostr << p.toString();
                return ostr;
            }
    };
    
    template<>
    class FLOAT_T<mpfr_t>
    {
        private:
            mpfr_t mValue;
        
        public:
    	
            /**
             * Constructors & Destructors
             */
            
            FLOAT_T()
            {
                mpfr_init(mValue);
            }
            
            FLOAT_T(const double _double, RND _rnd)
            {
                mpfr_init(mValue);
                mpfr_set_d(mValue,_double,convRnd(_rnd));
            }

            FLOAT_T<mpfr_t>(const double _double, precision _prec){}

            FLOAT_T<mpfr_t>(const double _double, RND _rnd, precision _prec)
            {
                mpfr_init2(mValue,_prec);
                mpfr_set_d(mValue,_double,convRnd(_rnd));
            }

            FLOAT_T(const FLOAT_T<mpfr_t>& _float) : mValue( _float.mValue ){}

            template<typename DifferentType>
            FLOAT_T(const DifferentType& _float)
            {
                // TODO: Write specialized conversion operators here.
            }

            ~FLOAT_T(){}
            // TODO: Do we require specialized destructors?

            /*************
             * Operators *
             *************/
            
//            FLOAT_T<mpfr_t>& operator = (const FLOAT_T<mpfr_t>& _rhs)
//            {
//                mValue = _rhs.mValue;
//                return *this;
//            }
            
            /**
             * Boolean operators 
             */
            
            // TODO
            
            /**
             * arithmetic operations
             */
            
            void add(mpfr_t& _res, const mpfr_t& _op1, const mpfr_t& _op2, RND _rnd )
            {
                mpfr_add(_res, _op1, _op2, convRnd(_rnd));
            }

            FLOAT_T<mpfr_t> add(const mpfr_t& _op1, const mpfr_t& _op2, RND _rnd)
            {
                FLOAT_T<mpfr_t> res;
                mpfr_add(res.mValue, _op1, _op2, convRnd(_rnd));
                return res;
            }

            /**
             * special operators
             */

//            FLOAT_T<FloatType> sqrt() const
//            {
//                return FLOAT_T<FloatType>(mValue.sqrt());
//            }
//
//            FLOAT_T<FloatType> cbrt() const
//            {
//                    return FLOAT_T<FloatType>(mValue.cbrt());;
//            }
//
//            FLOAT_T<FloatType> root(unsigned long int k) const
//            {
//                    return FLOAT_T<FloatType>(mValue.root(k));
//            }
//
//            FLOAT_T<FloatType> pow(unsigned long int _exp) const
//            {
//                return FLOAT_T<FloatType>(mValue.pow(_exp));
//            }
//
//            FLOAT_T<FloatType> abs() const
//            {
//                return FLOAT_T<FloatType>(mValue.abs());
//            }

            /**
             * conversion operators
             */

//            double toDouble() const
//            {
//                    return mValue.toDouble();
//            }
//
//            std::string toString() const
//            {
//                    return mValue.toString();
//            }
//
            friend std::ostream & operator<< (std::ostream& ostr, const FLOAT_T<mpfr_t> & p) {
                ostr << p.toString();
                return ostr;
            }
            
            std::string toString() const
            {
                // TODO: Better rounding mode?
                std::stringstream str;
		str << mpfr_get_d(mValue, convRnd(RND::N));   
		return str.str();
            }
            
        private:
            
            mpfr_rnd_t convRnd(RND _rnd) const
            {
                switch(_rnd)
                {
                    case 0:
                        return MPFR_RNDN;
                        break;
                    case 1:
                        return MPFR_RNDZ;
                        break;
                    case 2:
                        return MPFR_RNDU;
                        break;
                    case 3:
                        return MPFR_RNDD;
                        break;
                    case 4:
                        return MPFR_RNDA;
                        break;
                    default:
                        return MPFR_RNDNA;
                }
            }
    };
}
