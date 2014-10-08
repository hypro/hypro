#include "HPolytope.h"
namespace hypro
{
    template<typename Number>
    HPolytope<Number>::HPolytope() :
    mFanSet(false),
    mDimension(0)
    {}
    
    template<typename Number>
    HPolytope<Number>::HPolytope(const HPolytope& orig) :
    mHPlanes(orig.mHPlanes),
    mFanSet(orig.mFanSet),
    mFan(orig.mFan),
    mDimension(orig.mDimension)
    {}
    
    template<typename Number>
    HPolytope<Number>::HPolytope(const polytope::Hyperplane<Number>& plane)
    {
        mHPlanes.push_back(plane);
        mFanSet = false;
        mDimension = plane.dimension();
    }
    
    template<typename Number>
    HPolytope<Number>::HPolytope(unsigned dimension)
    {
        mDimension = dimension;
    }
    
    template<typename Number>
    HPolytope<Number>::HPolytope(const matrix& A, const vector& b)
    {
        
    }
    
    template<typename Number>
    HPolytope<Number>::HPolytope(const matrix& A)
    {
        
    }
    
    template<typename Number>
    HPolytope<Number>::~HPolytope()
    {}
    
    /*
     * Getters and setters
     */
 
    /*
     * Operators
     */
    
    template<typename Number>
    polytope::Hyperplane<Number> HPolytope<Number>::operator[](unsigned i) const
    {
        return mHPlanes.at(i);
    }
    
    template<typename Number>
    HPolytope<Number>& HPolytope<Number>::operator= (const HPolytope<Number>& rhs)
    {
        if(this != &rhs)
        {
            HPolytope<Number> tmp(rhs);
            std::swap(*this, tmp);
        }
        return *this;
    }
    
    /*
     * Auxiliary functions
     */
    
    template<typename Number>
    Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, Eigen::Dynamic> HPolytope<Number>::getOptimalDictionary(
        const Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, Eigen::Dynamic> A, 
        unsigned dimension, 
        std::vector<unsigned>& B, 
        std::vector<unsigned>& N) const
    {
        typedef Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, Eigen::Dynamic> matrix_t;
        typedef Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, 1> vector_t;
        typedef Eigen::Matrix<carl::FLOAT_T<Number>, 1, Eigen::Dynamic> row_t;
        // create matrix from HPlanes
        const unsigned numRows = mHPlanes.size() - mHPlanes.begin()->dimension();
        const unsigned numCols = mHPlanes.begin()->dimension() + 1;
        matrix_t dictionary = matrix_t(numRows, numCols);
        
        // Assumption: The last d equations of A are linear independent
        auto bottom = A.bottomRows(dimension);
        auto top = A.topRows(A.rows()-dimension);
        auto varBlock = bottom.rightCols(dimension);
        auto constPart = bottom.leftCols(1);
        
        matrix_t tmp = matrix_t(varBlock);
        vector_t b = vector_t(constPart);
        
        matrix_t a(tmp.rows(), 2*dimension+1);
        a << tmp, -b, matrix_t::Identity(dimension,dimension);
        
        //normalize rows for each variable and forward insertion
        for(unsigned rowIndex = 0; rowIndex < a.rows()-1; ++rowIndex)
        {
            a.row(rowIndex) = a.row(rowIndex)/a(rowIndex,rowIndex);
            a.row(rowIndex+1) = a.row(rowIndex+1) - (a.row(rowIndex)*a(rowIndex+1, rowIndex));
        }
        
        // backward insertion
        for(unsigned rowIndex = a.rows()-1; rowIndex > 0; --rowIndex)
        {
            if(a(rowIndex,rowIndex) != 1)
            {
                a.row(rowIndex) = a.row(rowIndex) / a(rowIndex,rowIndex);
            }
            a.row(rowIndex-1) = a.row(rowIndex-1) - (a.row(rowIndex)*a(rowIndex-1, rowIndex));
        }
        
        auto substitutionBlock = a.rightCols(dimension+1);
        
        for(unsigned rI = 0; rI < top.rows(); ++rI)
        {
            dictionary(rI,0) = top(rI,0);
            
            for(unsigned dI = 1; dI < top.cols(); ++dI)
            {
                dictionary.row(rI) = dictionary.row(rI) + (top(rI,dI) * substitutionBlock.row(dI-1));
            }
        }
        
        // Augment dictionary by a row of -1s
        dictionary.conservativeResize(numRows+1,Eigen::NoChange_t());
        
        row_t allOnes = matrix_t::Constant(1,numCols, carl::FLOAT_T<Number>(-1));
        allOnes(0) = carl::FLOAT_T<Number>(0);
        dictionary.row(numRows) = allOnes;
        
        //std::cout << "Optimal dictionary: " << dictionary << std::endl;
        for(unsigned index = 0; index < mHPlanes.size() - dimension; ++index)
            B.push_back(index);
        //B.push_back(mHPlanes.size()+1);
        
        for(unsigned index = 1 ; index < dictionary.cols() ; ++index)
            N.push_back(index);
        
        return dictionary;
    }
    
    template<typename Number>
    std::vector<Point<Number> > HPolytope<Number>::vertexEnumeration() const
    {
        std::vector<Point<Number> > solution;
        
        // create Matrix from hPlanes TODO: Recheck with page 299 of the paper
        const unsigned rows = mHPlanes.size();
        const unsigned colums = this->dimension()+1;
        Eigen::Matrix<carl::FLOAT_T<Number>,Eigen::Dynamic, Eigen::Dynamic> poly = Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, Eigen::Dynamic>(rows,colums);
        unsigned rowCount = 0;
        unsigned columCount = 0;
        
        for(auto& hplane : mHPlanes)
        {
            columCount = 0;
            poly(rowCount, columCount) = carl::FLOAT_T<double>(hplane.offset());
            vector normal = hplane.normal();
            for(unsigned index = 0; index < normal.rows(); ++index)
            {
                ++columCount;
                poly(rowCount, columCount) = -normal(index);
            }
            ++rowCount;
        }
        
        // get unique optimal first Dictionary
        std::vector<unsigned> basis;
        std::vector<unsigned> coBasis;
        Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, Eigen::Dynamic> dictionary = getOptimalDictionary(poly,this->dimension(), basis, coBasis);
        
        std::cout << "Optimal dictionary:" << std::endl << dictionary << std::endl;
        
        std::cout << "Basis: ";
        for(auto& val : basis)
            std::cout << val;
        std::cout << std::endl;
        
        std::cout << "CoBasis: ";
        for(auto& val : coBasis)
            std::cout << val;
        std::cout << std::endl;
        
        // Note: f and g mark the indices, not the enumeration as stored in B and N
        unsigned f = dictionary.rows();
        unsigned g = 0;

        unsigned m = mHPlanes.size() - dimension() +1;
        unsigned n = mHPlanes.size() +2;
        
        hpolytope::search(basis, coBasis, dictionary);
        
        return solution;
    }
}

    template<typename Number>
    std::ostream& operator<<(std::ostream& lhs, const hypro::HPolytope<Number>& rhs)
    {
        lhs << "[ ";
        for(unsigned i = 0; i < rhs.constraints().size()-1; ++i)
        {
            lhs << rhs[i] << "," << std::endl;
        }
        lhs << rhs[rhs.constraints().size()-1] << " ]";
        return lhs;
    }
