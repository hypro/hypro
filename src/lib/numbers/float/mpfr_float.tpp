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
        FLOAT_T(const double _double, precision _prec=53, const HYPRO_RND _rnd=HYPRO_RND::HYPRO_RNDN)
        {
            mpfr_init2(mValue,_prec);
            if( _double == 0)
            {
                mpfr_set_zero(mValue, 1);
            }
            else
            {
                mpfr_set_d(mValue,_double,mpfr_rnd_t((_rnd)));
            }
        }

        // Default precision is initially set to 53 bits in mpfr implementation
        FLOAT_T(const float _float, precision _prec=53, const HYPRO_RND _rnd=HYPRO_RND::HYPRO_RNDN)
        {
            mpfr_init2(mValue, _prec);
            if( _float == 0)
            {
                mpfr_set_zero(mValue, 1);
            }
            else
            {
                mpfr_set_flt(mValue, _float, mpfr_rnd_t(_rnd));
            }
        }

        // Default precision is initially set to 53 bits in mpfr implementation
        FLOAT_T(const int _int, precision _prec=53, const HYPRO_RND _rnd=HYPRO_RND::HYPRO_RNDN)
        {
            mpfr_init2(mValue,_prec);
            if( _int == 0)
            {
                mpfr_set_zero(mValue, 1);
            }
            else
            {
                mpfr_set_si(mValue,_int,mpfr_rnd_t(_rnd));
            }
        }
        
        FLOAT_T(const mpfr_t& _mpfrNumber)
        {
            mpfr_init2(mValue,mpfr_get_prec(_mpfrNumber));
            mpfr_set(mValue, _mpfrNumber, MPFR_RNDN);
        }

        FLOAT_T(const FLOAT_T<mpfr_t>& _float)
        {
            mpfr_init2(mValue, mpfr_get_prec(_float.mValue));
            mpfr_set(mValue, _float.mValue, MPFR_RNDN);
        }

        ~FLOAT_T()
        {
            mpfr_clear(mValue);
        }
        
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
        
        FLOAT_T<mpfr_t>& setPrec( const precision& _prec, const HYPRO_RND _rnd=HYPRO_RND::HYPRO_RNDN )
        {
            mpfr_prec_round(mValue, convPrec(_prec), mpfr_rnd_t(_rnd));
            return *this;
        }
        
        
        /*************
         * Operators *
         *************/
        
        FLOAT_T<mpfr_t>& operator = (const FLOAT_T<mpfr_t>& _rhs)
        {
            if(this == &_rhs)
                return *this;
        		
            mpfr_set(mValue, _rhs.mValue, MPFR_RNDN);
            return *this;
        }
        
        FLOAT_T<mpfr_t>& safeSet (const FLOAT_T<mpfr_t>& _rhs, const HYPRO_RND _rnd=HYPRO_RND::HYPRO_RNDN)
        {
            mpfr_set_prec(mValue, mpfr_get_prec(_rhs.mValue));
            mpfr_set(mValue, _rhs.mValue, mpfr_rnd_t(_rnd));
            return *this;
        }

        /**
         * Boolean operators 
         */

        bool operator == ( const FLOAT_T<mpfr_t>& _rhs) const
        {
            return mpfr_cmp(mValue,_rhs.mValue) == 0;
        }

        bool operator != ( const FLOAT_T<mpfr_t> & _rhs) const
        {
            return mpfr_equal_p(mValue, _rhs.mValue) == 0;
        }

        bool operator > ( const FLOAT_T<mpfr_t> & _rhs) const
        {
            return mpfr_greater_p(mValue, _rhs.mValue) != 0;
        }

        bool operator < ( const FLOAT_T<mpfr_t> & _rhs) const
        {
            return mpfr_less_p(mValue, _rhs.mValue) != 0;
        }

        bool operator <= ( const FLOAT_T<mpfr_t> & _rhs) const
        {
            return mpfr_lessequal_p(mValue, _rhs.mValue) != 0;
        }

        bool operator >= ( const FLOAT_T<mpfr_t> & _rhs) const
        {
            return mpfr_greaterequal_p(mValue, _rhs.mValue) != 0;
        }

        /**
         * arithmetic operations
         */

        FLOAT_T<mpfr_t>& add_assign( const FLOAT_T<mpfr_t>& _op2, HYPRO_RND _rnd )
        {
            mpfr_add(mValue, mValue, _op2.mValue, mpfr_rnd_t(_rnd));
            return *this;
        }

        void add( FLOAT_T<mpfr_t>& _result, const FLOAT_T<mpfr_t>& _op2, HYPRO_RND _rnd ) const
        {
            mpfr_add(_result.mValue, this->mValue, _op2.mValue, mpfr_rnd_t(_rnd));
        }

        FLOAT_T<mpfr_t>& sub_assign( const FLOAT_T<mpfr_t>& _op2, HYPRO_RND _rnd )
        {
            mpfr_sub(mValue, mValue, _op2.mValue, mpfr_rnd_t(_rnd));
            return *this;
        }

        void sub( FLOAT_T<mpfr_t>& _result, const FLOAT_T<mpfr_t>& _op2, HYPRO_RND _rnd ) const
        {
            mpfr_sub(_result.mValue, this->mValue, _op2.mValue, mpfr_rnd_t(_rnd));
        }

        FLOAT_T<mpfr_t>& mul_assign(const FLOAT_T<mpfr_t>& _op2, HYPRO_RND _rnd)
        {
            mpfr_mul(mValue, mValue, _op2.mValue, mpfr_rnd_t(_rnd));
            return *this;
        }

        void mul( FLOAT_T<mpfr_t>& _result, const FLOAT_T<mpfr_t>& _op2, HYPRO_RND _rnd) const
        {
            mpfr_mul(_result.mValue, this->mValue, _op2.mValue, mpfr_rnd_t(_rnd));
        }

        FLOAT_T<mpfr_t>& div_assign(const FLOAT_T<mpfr_t>& _op2, HYPRO_RND _rnd)
        {
            assert( mpfr_zero_p(_op2.mValue) != 0 );
            mpfr_div(mValue, mValue, _op2.mValue, mpfr_rnd_t(_rnd));
            return *this;
        }

        void div( FLOAT_T<mpfr_t>& _result, const FLOAT_T<mpfr_t>& _op2, HYPRO_RND _rnd) const
        {
            assert( mpfr_zero_p(_op2.mValue) != 0 );
            mpfr_div(_result.mValue, this->mValue, _op2.mValue, mpfr_rnd_t(_rnd));
        }

        /**
         * special operators
         */

        FLOAT_T<mpfr_t>& sqrt_assign(HYPRO_RND _rnd = HYPRO_RNDN)
        {
            mpfr_sqrt(mValue, mValue, mpfr_rnd_t(_rnd));
            return *this;
        }

        void sqrt(FLOAT_T<mpfr_t>& _result, HYPRO_RND _rnd = HYPRO_RNDN)
        {
            mpfr_sqrt(_result.mValue, mValue, mpfr_rnd_t(_rnd));
        }

        FLOAT_T<mpfr_t>& cbrt_assign(HYPRO_RND _rnd = HYPRO_RNDN)
        {
            mpfr_cbrt(mValue, mValue, mpfr_rnd_t(_rnd));
            return *this;
        }

        void cbrt(FLOAT_T<mpfr_t>& _result, HYPRO_RND _rnd = HYPRO_RNDN)
        {
            mpfr_cbrt(_result.mValue, mValue, mpfr_rnd_t(_rnd));
        }

        FLOAT_T<mpfr_t>& root_assign(unsigned long int _k, HYPRO_RND _rnd = HYPRO_RNDN)
        {
            mpfr_root(mValue, mValue, _k, mpfr_rnd_t(_rnd));
            return *this;
        }

        void root(FLOAT_T<mpfr_t>& _result, unsigned long int _k, HYPRO_RND _rnd = HYPRO_RNDN)
        {
            mpfr_root(_result.mValue, mValue, _k, mpfr_rnd_t(_rnd));
        }

        FLOAT_T<mpfr_t>& pow_assign(unsigned long int _exp, HYPRO_RND _rnd = HYPRO_RNDN)
        {
            mpfr_pow_ui(mValue, mValue, _exp, mpfr_rnd_t(_rnd));
            return *this;
        }

        void pow(FLOAT_T<mpfr_t>& _result, unsigned long int _exp, HYPRO_RND _rnd = HYPRO_RNDN)
        {
            mpfr_pow_ui(_result.mValue, mValue, _exp, mpfr_rnd_t(_rnd));
        }

        FLOAT_T<mpfr_t>& abs_assign(HYPRO_RND _rnd = HYPRO_RNDN)
        {
            mpfr_abs(mValue, mValue, mpfr_rnd_t(_rnd));
            return *this;
        }

        void abs(FLOAT_T<mpfr_t>& _result, HYPRO_RND _rnd = HYPRO_RNDN)
        {
            mpfr_abs(_result.mValue, mValue, mpfr_rnd_t(_rnd));
        }
        
        FLOAT_T<mpfr_t>& exp_assign(HYPRO_RND _rnd = HYPRO_RNDN)
        {
            mpfr_exp(mValue, mValue, mpfr_rnd_t(_rnd));
            return *this;
        }

        void exp(FLOAT_T<mpfr_t>& _result, HYPRO_RND _rnd = HYPRO_RNDN)
        {
            mpfr_exp(_result.mValue, mValue, mpfr_rnd_t(_rnd));
        }

        FLOAT_T<mpfr_t>& sin_assign(HYPRO_RND _rnd = HYPRO_RNDN)
        {
            mpfr_sin(mValue, mValue, mpfr_rnd_t(_rnd));
            return *this;
        }

        void sin(FLOAT_T<mpfr_t>& _result, HYPRO_RND _rnd = HYPRO_RNDN)
        {
            mpfr_sin(_result.mValue, mValue, mpfr_rnd_t(_rnd));
        }

        FLOAT_T<mpfr_t>& cos_assign(HYPRO_RND _rnd = HYPRO_RNDN)
        {
            mpfr_cos(mValue, mValue, mpfr_rnd_t(_rnd));
            return *this;
        }

        void cos(FLOAT_T<mpfr_t>& _result, HYPRO_RND _rnd = HYPRO_RNDN)
        {
            mpfr_cos(_result.mValue, mValue, mpfr_rnd_t(_rnd));
        }

        FLOAT_T<mpfr_t>& log_assign(HYPRO_RND _rnd = HYPRO_RNDN)
        {
            mpfr_log(mValue, mValue, mpfr_rnd_t(_rnd));
            return *this;
        }

        void log(FLOAT_T<mpfr_t>& _result, HYPRO_RND _rnd = HYPRO_RNDN)
        {
            mpfr_log(_result.mValue, mValue, mpfr_rnd_t(_rnd));
        }


        /**
         * conversion operators
         */

        double toDouble(HYPRO_RND _rnd=HYPRO_RND::HYPRO_RNDN) const
        {
            return mpfr_get_d(mValue, mpfr_rnd_t(_rnd));
        }
        
        friend std::ostream & operator<< (std::ostream& ostr, const FLOAT_T<mpfr_t> & p) {
            ostr << p.toString();
            return ostr;
        }
        
        /**
        * Operators
        */

        friend FLOAT_T<mpfr_t> operator +(const FLOAT_T<mpfr_t>& _lhs, const FLOAT_T<mpfr_t>& _rhs)
        {
            FLOAT_T<mpfr_t> res;
            mpfr_add(res.mValue, _lhs.mValue, _rhs.mValue, MPFR_RNDN);
            return res;
        }

        friend FLOAT_T<mpfr_t> operator -(const FLOAT_T<mpfr_t>& _lhs, const FLOAT_T<mpfr_t>& _rhs)
        {
            FLOAT_T<mpfr_t> res;
            mpfr_sub(res.mValue, _lhs.mValue, _rhs.mValue, MPFR_RNDN);
            return res;
        }

        friend FLOAT_T<mpfr_t> operator *(const FLOAT_T<mpfr_t>& _lhs, const FLOAT_T<mpfr_t>& _rhs)
        {
            FLOAT_T<mpfr_t> res;
            mpfr_mul(res.mValue, _lhs.mValue, _rhs.mValue, MPFR_RNDN);
            return res;
        }

        friend FLOAT_T<mpfr_t> operator /(const FLOAT_T<mpfr_t>& _lhs, const FLOAT_T<mpfr_t>& _rhs)
        {
            // TODO: mpfr_div results in infty when dividing by zero, although this should not be defined.
            FLOAT_T<mpfr_t> res;
            mpfr_div(res.mValue, _lhs.mValue, _rhs.mValue, MPFR_RNDN);
            return res;
        }
        
        friend FLOAT_T<mpfr_t>& operator++(FLOAT_T<mpfr_t>& _num)
        {
            mpfr_add_ui(_num.mValue, _num.mValue, 1, MPFR_RNDN);
            return _num;
        }
        
        friend FLOAT_T<mpfr_t>& operator--(FLOAT_T<mpfr_t>& _num)
        {
            mpfr_sub_ui(_num.mValue, _num.mValue, 1, MPFR_RNDN);
            return _num;
        }
        
        FLOAT_T<mpfr_t>& operator +=(const FLOAT_T<mpfr_t>& _rhs)
        {
            mpfr_add(mValue, mValue, _rhs.mValue, MPFR_RNDN);
            return *this;
        }

        FLOAT_T<mpfr_t>& operator -=(const FLOAT_T<mpfr_t>& _rhs)
        {
            mpfr_sub(mValue,mValue, _rhs.mValue, MPFR_RNDN);
            return *this;
        }

        FLOAT_T<mpfr_t>& operator *=(const FLOAT_T<mpfr_t>& _rhs)
        {
            mpfr_mul(mValue, mValue, _rhs.mValue, MPFR_RNDN);
            return *this;
        }

        FLOAT_T<mpfr_t>& operator /=(const FLOAT_T<mpfr_t>& _rhs)
        {
            // TODO: mpfr_div results in infty when dividing by zero, although this should not be defined.
            mpfr_div(mValue, mValue, _rhs.mValue, MPFR_RNDN);
            return *this;
        }
            
        /**
         * Auxiliary Functions
         */

        std::string toString() const
        {
            // TODO: Better rounding mode?
//            std::string out;
            char out[30];
//            str << mpfr_get_d(mValue, MPFR_RNDN);
            mpfr_sprintf(out, "%.10RDe", mValue);
            return std::string(out);
        }

    private:

        mpfr_rnd_t convRnd(HYPRO_RND _rnd) const
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
        
        mpfr_prec_t convPrec(precision _prec) const
        {
            return _prec;
        }
};
