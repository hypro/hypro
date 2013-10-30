#include "../FLOAT_T.h"

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
            mpfr_set_zero(mValue, 1);
        }

        FLOAT_T(const double _double, RND _rnd)
        {
            mpfr_init(mValue);
            if( _double == 0)
            {
                mpfr_set_zero(mValue, 1);
            }
            else
            {
                mpfr_set_d(mValue,_double,convRnd(_rnd));
            }
        }

        FLOAT_T(const double _double, precision _prec){}

        FLOAT_T(const double _double, RND _rnd, precision _prec)
        {
            mpfr_init2(mValue,_prec);
            if( _double == 0)
            {
                mpfr_set_zero(mValue, 1);
            }
            else
            {
                mpfr_set_d(mValue,_double,convRnd(_rnd));
            }
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

        FLOAT_T<mpfr_t>& add( const FLOAT_T<mpfr_t>& _op2, RND _rnd )
        {
            mpfr_add(mValue, mValue, _op2.mValue, convRnd(_rnd));
            return *this;
        }

        FLOAT_T<mpfr_t>& add( const FLOAT_T<mpfr_t>& _op1, const FLOAT_T<mpfr_t>& _op2, RND _rnd )
        {

            mpfr_add(mValue, _op1.mValue, _op2.mValue, convRnd(_rnd));
            return *this;
        }

        FLOAT_T<mpfr_t>& sub( const FLOAT_T<mpfr_t>& _op2, RND _rnd )
        {
            mpfr_sub(mValue, mValue, _op2.mValue, convRnd(_rnd));
            return *this;
        }

        FLOAT_T<mpfr_t>& sub( const FLOAT_T<mpfr_t>& _op1, const FLOAT_T<mpfr_t>& _op2, RND _rnd )
        {
            mpfr_sub(mValue, _op1.mValue, _op2.mValue, convRnd(_rnd));
            return *this;
        }

        FLOAT_T<mpfr_t>& mul(const FLOAT_T<mpfr_t>& _op2, RND _rnd)
        {
            mpfr_mul(mValue, mValue, _op2.mValue, convRnd(_rnd));
            return *this;
        }

        FLOAT_T<mpfr_t>& mul(const FLOAT_T<mpfr_t>& _op1, const FLOAT_T<mpfr_t>& _op2, RND _rnd)
        {
            mpfr_mul(mValue, _op1.mValue, _op2.mValue, convRnd(_rnd));
            return *this;
        }

        FLOAT_T<mpfr_t>& div(const FLOAT_T<mpfr_t>& _op2, RND _rnd) throw (std::invalid_argument)
        {
            if( mpfr_zero_p(_op2.mValue) != 0 ) throw ( std::invalid_argument( "Division by zero not allowed." ) );
            mpfr_div(mValue, mValue, _op2.mValue, convRnd(_rnd));
            return *this;
        }

        FLOAT_T<mpfr_t>& div(const FLOAT_T<mpfr_t>& _op1, const FLOAT_T<mpfr_t>& _op2, RND _rnd) throw (std::invalid_argument)
        {
            if( mpfr_zero_p(_op2.mValue) != 0 ) throw ( std::invalid_argument( "Division by zero not allowed." ) );
            mpfr_div(mValue, _op1.mValue, _op2.mValue, convRnd(_rnd));
            return *this;
        }

        /**
         * special operators
         */

        FLOAT_T<mpfr_t>& sqrt(RND _rnd)
        {
            mpfr_sqrt(mValue, mValue, convRnd(_rnd));
            return *this;
        }

        FLOAT_T<mpfr_t>& cbrt(RND _rnd)
        {
            mpfr_cbrt(mValue, mValue, convRnd(_rnd));
            return *this;
        }

        FLOAT_T<mpfr_t>& root(unsigned long int _k, RND _rnd)
        {
            mpfr_root(mValue, mValue, _k, convRnd(_rnd));
            return *this;
        }

        FLOAT_T<mpfr_t>& pow(unsigned long int _exp, RND _rnd)
        {
            mpfr_pow_ui(mValue, mValue, _exp, convRnd(_rnd));
            return *this;
        }

//        FLOAT_T<mpfr_t>& abs(RND _rnd) const
//        {
//            mpfr_abs(mValue, mValue, convRnd(_rnd));
//            return *this;
//        }

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