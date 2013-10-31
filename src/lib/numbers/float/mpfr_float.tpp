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

        // Default precision is initially set to 53 bits in mpfr implementation
        FLOAT_T(const double _double, precision _prec=53, const RND _rnd=RND::N)
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

        // Default precision is initially set to 53 bits in mpfr implementation
        FLOAT_T(const float _float, precision _prec=53, const RND _rnd=RND::N)
        {
            mpfr_init2(mValue, _prec);
            if( _float == 0)
            {
                mpfr_set_zero(mValue, 1);
            }
            else
            {
                mpfr_set_flt(mValue, _float, convRnd(_rnd));
            }
        }

        // Default precision is initially set to 53 bits in mpfr implementation
        FLOAT_T(const int _int, precision _prec=53, const RND _rnd=RND::N)
        {
            mpfr_init2(mValue,_prec);
            if( _int == 0)
            {
                mpfr_set_zero(mValue, 1);
            }
            else
            {
                mpfr_set_si(mValue,_int,convRnd(_rnd));
            }
        }
        
        FLOAT_T(const mpfr_t& _mpfrNumber)
        {
            mpfr_init2(mValue,mpfr_get_prec(_mpfrNumber));
            mpfr_set(mValue, _mpfrNumber, MPFR_RNDN);
        }

        FLOAT_T(const FLOAT_T<mpfr_t>& _float) : mValue( _float.mValue ){}

        ~FLOAT_T(){}

        
        /*******************
         * Getter & Setter *
         *******************/
        
        const mpfr_t& getValue() const
        {
            return mValue;
        }
        
        const precision getPrec() const
        {
            return mpfr_get_prec(mValue);
        }
        
        FLOAT_T<mpfr_t>& setPrec( const precision& _prec, const RND _rnd=RND::N )
        {
            mpfr_prec_round(mValue, convPrec(_prec), convRnd(_rnd));
            return *this;
        }
        
        
        /*************
         * Operators *
         *************/
        
        FLOAT_T<mpfr_t>& operator = (const FLOAT_T<mpfr_t>& _rhs)
        {
            mpfr_set(mValue, _rhs.mValue, MPFR_RNDN);
            return *this;
        }
        
        FLOAT_T<mpfr_t>& safeSet (const FLOAT_T<mpfr_t>& _rhs, const RND _rnd=RND::N)
        {
            mpfr_set_prec(mValue, mpfr_get_prec(_rhs.mValue));
            mpfr_set(mValue, _rhs.mValue, convRnd(_rnd));
            return *this;
        }

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

        double toDouble(RND _rnd=RND::N) const
        {
            return mpfr_get_d(mValue, convRnd(_rnd));
        }
        
        friend std::ostream & operator<< (std::ostream& ostr, const FLOAT_T<mpfr_t> & p) {
            ostr << p.toString();
            return ostr;
        }
        
        friend bool operator== (const FLOAT_T<mpfr_t>& _lhs, const FLOAT_T<mpfr_t>& _rhs)
        {
            return mpfr_cmp(_lhs.mValue,_rhs.mValue) == 0;
        }

        std::string toString() const
        {
            // TODO: Better rounding mode?
            std::stringstream str;
            str << mpfr_get_d(mValue, convRnd(RND::N));   
            return str.str();
        }

    private:

        inline mpfr_rnd_t convRnd(RND _rnd) const
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
        
        inline mpfr_prec_t convPrec(precision _prec) const
        {
            return _prec;
        }
};