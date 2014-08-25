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
    Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, Eigen::Dynamic> HPolytope<Number>::getOptimalDictionary(const Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, Eigen::Dynamic> A) const
    {
        // create matrix from HPlanes
        const unsigned numRows = mHPlanes.size() - mHPlanes.begin()->dimension();
        const unsigned numCols = mHPlanes.begin()->dimension() + 1;
        Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, Eigen::Dynamic> dictionary = Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, Eigen::Dynamic>(numRows, numCols);
        
        // Assumption: The last d equations of A are linear independent
        
        
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
        
        Polynomial constraint;
        
        for(auto& hplane : mHPlanes)
        {
            columCount = 0;
            for(auto& coordinate : hplane.normal())
            {
                std::cout << "Try to add monomial: " << coordinate.second*coordinate.first << std::endl;
                constraint += coordinate.second*coordinate.first;
                poly(rowCount, columCount) = coordinate.second;
                ++columCount;
            }
            poly(rowCount, columCount) = carl::FLOAT_T<Number>(hplane.offset());
            ++rowCount;
        }
        
        std::cout << "Poly Matrix: " << std::endl;
        std::cout << poly << std::endl;
        
        // get unique optimal first Dictionary
        Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, Eigen::Dynamic> dictionary = getOptimalDictionary(poly);
        
        std::cout << "Optimal dictionary:" << std::endl;
        std::cout << dictionary << std::endl;
        
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
