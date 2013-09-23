/** 
 * @file   point.cpp
 * Created on Mar 12, 2011
 * Last modified June 23, 2011
 * 
 * @author Sebastian Junges
 *
 */

#include "point.h"

namespace hypro {
    
     /**
     * @brief gives the next point according to some (hardcoded) ordering.
     * @param bounds The grid lies between the origin and this point.
     *
     */
	template<class NumberType>
    void Point<NumberType>::nextPointOnGrid (const Point<NumberType> & bounds) {
        for(unsigned i=getDimension(); i>0.; i--) {
            if (mCoordinates[i-1] < bounds[i-1]) {
                mCoordinates[i-1]++;
                return;
            }
            else {
                mCoordinates[i-1] = 0;
            }
        }
    }
    
    template<class NumberType>
    NumberType Point<NumberType>::getGaussianProbability(Point<NumberType> & mean) const {
    	return 0;
    }

    template<class NumberType>
    NumberType Point<NumberType>::getDistanceDependentProbabiltity(Point<NumberType> & mean, unsigned intlength, float rate) const {
        NumberType dist;
        for (unsigned i = 0; i < getDimension(); i++) {
            dist += (mCoordinates[i] - mean[i]).pow(NumberType(2));
        }
        dist /= rate;
        if (dist < 1) return 1;
        return (((NumberType) intlength * (NumberType) getDimension()*(NumberType) getDimension() / dist));
    }

    /**
     * @param parentheses Decides if the output is surrounded by parentheses. 
     * @return The coordinates of the point.
     */
    template<class NumberType>
    std::string Point<NumberType>::toString(bool parentheses) const {
        unsigned dimension = mCoordinates.size();
        std::string result;

        if (parentheses) {
            result += "(";
        }

        for (unsigned i = 0; i < dimension - 1; i++) {
            result += mCoordinates[i].toString() + " ";
        }
        result += mCoordinates[dimension - 1].toString();

        if (parentheses) {
            result += ")";
        }
        return result;

    }
    
    /**
     * @brief random move in one direction.
     */
    // TODO !!! rand() doesn't work here
    template<class NumberType>
    void Point<NumberType>::moveRandom() {
        unsigned dim = getDimension();
        unsigned value = rand();
        unsigned dir = value%dim;
        bool neg = (rand() & 1);
        if (neg) mCoordinates[dir]--;
        else mCoordinates[dir]++;
    }

    /**
     * Set dimension coordinates, beginning at offset.
     * @param coordinates
     * @param dimension the dimension of the setted point.
     * @param offset first coordinate that is set.
     */
    template<class NumberType>
    void Point<NumberType>::setCoordinates(NumberType coordinates[], unsigned dimension, unsigned offset) {
        mCoordinates.reserve(dimension + offset);
        for (unsigned i = 0; i < dimension; i++) {
            mCoordinates[i + offset] = coordinates[i];
        }
    }

    /**
     * 
     * @return the sum of all coordinates
     */
    template<class NumberType>
    NumberType Point<NumberType>::sum() const {
        NumberType sum = 0;
        for (unsigned i = 0; i < getDimension(); i++) {
            sum += mCoordinates[i];
        }
        return sum;
    }

    /**
     * 
     * @param coordinates
     * @param offset
     */
    template<class NumberType>
    void Point<NumberType>::insertCoordinates(std::vector<NumberType> coordinates, unsigned offset ) {
        typename std::vector<NumberType>::iterator it = mCoordinates.begin();
        mCoordinates.reserve(coordinates.size());
        while (offset > 0) {
            it++;
            offset--;
        }
        mCoordinates.insert(it, coordinates.begin(), coordinates.end());
    }

    /**
     * 
     * @param p1 One point
     * @param p2 Other point
     * @return A point with the coordinate-wise maximum of p1 and p2.
     */
    template<class NumberType>
    Point<NumberType> Point<NumberType>::coordinateMax(const Point<NumberType> & p1, const Point<NumberType> & p2) {
        Point<NumberType> p = Point<NumberType>(p1.getDimension());
        for (unsigned k = 0; k < p.getDimension(); k++) {
            (p1[k] > p2[k]) ? p[k] = p1[k] : p[k] = p2[k];
        }
        return p;
    }

    /**
     * @brief: function to calculate points in the neighborhood, with one fixed dimension.
     * @return std::vector with all points in the neighborhood, with a fixed dimension, and except the point itself.
     */
    template<class NumberType>
    std::vector<Point<NumberType> > Point<NumberType>::getAllNeighbours(bool pointself) const {
        std::vector<Point<NumberType> > neighbors = getAllNeighborsForAFixedDimension(0);
        unsigned nrneighbors = neighbors.size();
        //TODO comment!
        for (unsigned i = 0; i < nrneighbors; i++) {
            Point<NumberType> neighborpredecessor = Point(neighbors[i]).getPredecessorInDimension(0);
            neighbors.push_back(neighborpredecessor);
        }

        Point<NumberType> pointPredecessor = getPredecessorInDimension(0);
        neighbors.push_back(pointPredecessor);
        
        if (pointself) {
            neighbors.push_back(*this);
        }

        return neighbors;
    }
    

    /**
     *
     * @param fixedDim
     * @return Vector filled with neighbours with coordinate[fixedDim] equal to the points coordinate.
     *  point is not an element of the returned vector.
     */
    template<class NumberType>
    std::vector<Point<NumberType> > Point<NumberType>::getAllNeighborsForAFixedDimension(int fixedDim) const {
        std::vector<Point<NumberType> > neighbors;
        unsigned dim = getDimension();

        // TODO comment
        int nrofNeighbors = (pow(2, (dim - 1)) - 1);
        neighbors.reserve(nrofNeighbors);

        std::vector<NumberType> coordinates;
        coordinates.resize(dim);

        for (int neighborNr = 1; neighborNr <= nrofNeighbors; neighborNr++) {
            //calculate the next neighbor we going to check
            for (int k = dim - 1; k >= 0; k--) {
                if (k > fixedDim) {
                    coordinates[k] = mCoordinates[k] - ((neighborNr >> (dim - k - 1)) & 1);
                } else if (k == fixedDim) {
                    coordinates[k] = mCoordinates[k];
                } else { // k < fixed
                    coordinates[k] = mCoordinates[k] - ((neighborNr >> (dim - k - 1 - 1)) & 1);
                }
            }
            Point<NumberType> neighbor = Point<NumberType>(coordinates);
            neighbors.push_back(neighbor);
        }
        return neighbors;
    }
} // end namespace