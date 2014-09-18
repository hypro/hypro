/* 
 * File:   simplex.h
 * Author: stefan
 *
 * Created on August 20, 2014, 2:07 PM
 */

#include "../../../config.h"
#include <cassert>

namespace hypro
{
namespace hpolytope
{
    template<typename Number>
    static void pivot(std::vector<unsigned> B, std::vector<unsigned> N, Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>& A, unsigned r, unsigned s)
    {
        /*
        std::cout << __func__ << std::endl << A << ", r:" << r << ", s:" << s;
        std::cout << ", B= ";
        for(auto& item : B)
            std::cout << item << " ";
             
        std::cout << ", N= ";
        for(auto& item : N)
            std::cout << item << " ";
        
        std::cout << std::endl;
        */
        
        // set pivoting row first, assuming r,s = row, colum
        A.row(r) = A.row(r)/A(r,s);
        A.row(r) = -A.row(r);
        
        for(unsigned row = 0; row < A.rows(); ++row)
        {
            if(row != r)
            {
                carl::FLOAT_T<Number> coeff = A(row,s);
                A.row(row) = A.row(row) + (coeff * A.row(r));
                A(row,s) = A(r,s)*coeff;
            }
        }
        
        std::cout << __func__ << " Res: " << std::endl << A << std::endl;
    }
    
    template<typename Number>
    static bool lexMin(std::vector<unsigned> B, std::vector<unsigned> N, Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>& A)
    {
        unsigned tmp = B[0];
        for(auto& index : B)
        {
            if(tmp > index)
                return false;
            tmp = index;
        }
        return true;
    }
    
    /**
     * Returns whether the variable is primal or dual feasible, depending on the parameters.
     * @param B The set of indices forming the basis
     * @param A The coefficients
     * @param f
     * @param g
     * @param i The index of the variable
     * @return true, if the variable is primal or dual feasible
     */
    template<typename Number>
    static bool isFeasible(std::vector<unsigned> B, Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> A, unsigned f, unsigned g, unsigned i)
    {
        for(auto& index : B)
        {
            if(i == index && i != f && A(i,g) >= 0)
                return true;
        }
        return false;
    }
    
    template<typename Number>
    static bool isPrimalFeasible(Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> A)
    {
        
    }
    
    /**
     * Select next pivot according to Bland's rule.
     */
    template<typename Number>
    static bool selectPivot(const Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>& A, std::vector<unsigned> B, std::vector<unsigned> N, unsigned& i, unsigned& j, unsigned g, unsigned f)
    {
        // step 1
        unsigned r = 0;
        unsigned s = 0;
        carl::FLOAT_T<Number> min = A.maxCoeff();
        bool secondSet = false;
        for(; s < B.size(); ++s)
        {
            if(A(f,B.at(s)) > 0)
            {
                for( ; r < B.size(); ++r)
                {
                    if(A(r,s)<0 && -(A(r,g)/A(r,s)) < min)
                    {
                        secondSet = true;
                        break;
                    }
                }
            }
            if(secondSet)
                break;
        }
        i = r;
        j = s;
        return true;
    }
    
    template<typename Number>
    static void increment(const Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>& A, unsigned& i, unsigned& j)
    {
        j++;
        if(j == (A.cols() - A.rows()))
        {
            j = 1;
            i++;
        }
        std::cout << __func__ << " New i: " << i << ", New j: " << j << std::endl;
    }
    
    template<typename Number>
    static bool isReversePivot(std::vector<unsigned> B, std::vector<unsigned> N, Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> A, unsigned r, unsigned s, unsigned f, unsigned g)
    {
        Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> tmpA = A;
        std::vector<unsigned> tmpB = B;
        std::vector<unsigned> tmpN = N;
        unsigned tmpR = r;
        unsigned tmpS = s;
        
        //std::cout << __func__ << " Check(A, r,s): " << std::endl << tmpA << r << ", " << s << ": ";
         
        pivot(tmpB, tmpN, tmpA, s, r);
        selectPivot(tmpA, tmpB, tmpN, tmpR, tmpS, f, g);
        if(tmpR == r && tmpS == s)
        {
            std::cout << __func__ <<  ": true" << std::endl;
            return true;
        }
        else
        {
            std::cout << __func__ << ": false" << std::endl;
            return false;
        }
    }
    
    template<typename Number>
    static void search(std::vector<unsigned> B, std::vector<unsigned> N, Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> A)
    {
        unsigned i = 1;
        unsigned j = 0;
        unsigned m = A.rows();
        unsigned n = A.cols();
        unsigned f = 1;
        unsigned g = n;
        do
        {
            std::cout << __func__ << ": I: " << i << ", J: " << j << std::endl;
            while( i <= m && !isReversePivot(B,N,A,i,j,f,g))
            {
                increment(A,i,j);
            }
            
            std::cout << __func__ << ": Incremented to I: " << i << ", J: " << j << std::endl;
            
            if( i <= m )
            {
                pivot(B,N,A,i,j);
                if( lexMin(B,N,A) )
                {
                    std::cout << __func__ << ": Found dictionary: " << std::endl << A << std::endl;
                    // generate output
                }
                i = 2;
                j = 1;
            }
            else
            {
                selectPivot(A,B,N,i,j,g,f);
                pivot(B,N,A,i,j);
                increment(A,i,j);
            }
        } while( i<=m || B[m] != m);
    }
    
    
}
}