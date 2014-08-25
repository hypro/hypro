#include "HPolytope.h"
namespace hypro
{
    template<typename Number>
    HPolytope<Number>::HPolytope()
    {
        
    }
    
    template<typename Number>
    HPolytope<Number>::HPolytope(const HPolytope& orig)
    {
        
    }
    
    template<typename Number>
    HPolytope<Number>::HPolytope(const polytope::Hyperplane<Number>& plane)
    {
        mHPlanes.push_back(plane);
    }
    
    template<typename Number>
    HPolytope<Number>::HPolytope(unsigned dimension)
    {
        
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
    matrix HPolytope<Number>::getOptimalDictionary(const matrix A) const
    {
        // create matrix from HPlanes
        const unsigned numRows = mHPlanes.size() - mHPlanes.begin()->dimension();
        const unsigned numCols = mHPlanes.begin()->dimension() + 1;
        Eigen::Matrix<Number, numRows, numCols> dictionary;
        
        // Assumption: The last d equations of A are linear independent
        
        
        return dictionary;
    }
    
    template<typename Number>
    std::vector<Point<Number> > HPolytope<Number>::vertexEnumeration() const
    {
        std::vector<Point<Number> > solution;
        
        // create Matrix from hPlanes TODO: Recheck with page 299 of the paper
        matrix poly = Eigen::Matrix<Number,mHPlanes.size(), this->dimension()>();
        unsigned rowCount = 1;
        unsigned columCount = 1;
        for(auto& hplane : mHPlanes)
        {
            columCount = 1;
            for(auto& coordinate : hplane.normal())
            {
                poly(rowCount, columCount) = coordinate;
                ++columCount;
            }
            ++rowCount;
        }
        
        // get unique optimal first Dictionary
        matrix dictionary = getOptimalDictionary(poly);
        
        return solution;
    }
}
