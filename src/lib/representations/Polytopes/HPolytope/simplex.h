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
        // update table
        A(s,r) = 1/A(r,s);
        for(unsigned i = 1; i <= A.rows(); ++i)
        {
            A(i,r) = A(i,s)/A(r,s);
        }
        for(unsigned j = 1; j <= A.cols(); ++j)
        {
            A(s,j) = A(r,j)/A(r,s);
        }
        for(unsigned i = 1; i <= A.rows(); ++i)
        {
            for(unsigned j = 1; j <= A.cols(); ++j)
            {
                A(i,j) = A(i,j) - (A(i,s)*A(r,j)/A(r,s));
            }
        }
        // update basis and co-basis
        for(unsigned bPos = 0; bPos < B.size(); ++bPos)
        {
            if(B[bPos] == r)
            {
                B[bPos] = s;
                break;
            }
        }
        for(unsigned nPos = 0; nPos < N.size(); ++nPos)
        {
            if(N[nPos] == s)
            {
                N[nPos] = r;
                break;
            }
        }
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
    
    /**
     * Select next pivot according to dual Bland's rule.
     */
    template<typename Number>
    static bool selectPivot(const Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>& A, std::vector<unsigned> B, std::vector<unsigned> N, unsigned& i, unsigned& j, unsigned g, unsigned f)
    {
        // step 1
        unsigned r = 0;
        bool set = false;
        for(unsigned index = 0; index < B.size(); ++index)
        {
            if(B[index] < r && A(r,g) < 0)
            {
                r = B[index];
                set = true;
                if(set)
                {
                    Number delta;
                    bool secondset = false;
                    for(unsigned j = 0; j < N.size(); ++j)
                    {
                        if(N[j] != N[g] && A(r,j) > 0)
                        {
                            if(!secondset)
                            {
                                delta = -(A(f,j)/A(r,j));
                                secondset = true;
                            }
                            else
                            {
                                delta = -(A(f,j)/A(r,j)) < delta ? -(A(f,j)/A(r,j)) : delta;
                            }
                        }
                    }
                    assert(secondset);
                    return false;
                }
            }
        }
        
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
    }
    
    template<typename Number>
    static bool isReversePivot(std::vector<unsigned> B, std::vector<unsigned> N, Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> A, unsigned r, unsigned s, unsigned f, unsigned g)
    {
        Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> tmpA = A;
        std::vector<unsigned> tmpB = B;
        std::vector<unsigned> tmpN = N;
        unsigned tmpR = r;
        unsigned tmpS = s;
        pivot(tmpB, tmpN, tmpA, r, s);
        selectPivot(tmpA, tmpB, tmpN, tmpR, tmpS, f, g);
        if(tmpR == r && tmpS == s)
            return true;
        else
            return false;
    }
    
    template<typename Number>
    static void search(std::vector<unsigned> B, std::vector<unsigned> N, Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> A)
    {
        unsigned i = 2;
        unsigned j = 1;
        unsigned m = A.rows();
        unsigned n = A.cols();
        unsigned f = 1;
        unsigned g = n;
        do
        {
            while( i <= m && !isReversePivot(B,N,A,i,j,f,g))
            {
                increment(A,i,j);
            }
            
            if( i <= m )
            {
                pivot(B,N,A,i,j);
                if( lexMin(B,N,A) )
                {
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