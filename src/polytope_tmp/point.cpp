/** 
 * @file   point.cpp
 * Created on Mar 12, 2011
 * Last modified June 23, 2011
 * 
 * @author Sebastian Junges
 *
 */

#include "point.h"
#include <cmath>

namespace reachLin {
    
     /**
     * @brief gives the next point according to some (hardcoded) ordering.
     * @param bounds The grid lies between the origin and this point.
     *
     */
    void  Point::nextPointOnGrid(const Point& bounds) {
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
    

    double Point::getGaussianProbability(Point mean) const {

    }

    double Point::getDistanceDependentProbabiltity(Point mean, unsigned intlength, float rate) const {
        double dist;
        for (unsigned i = 0; i < getDimension(); i++) {
            dist += pow(mCoordinates[i] - mean[i], 2);
        }
        dist /= rate;
        if (dist < 1) return 1;
        return (((double) intlength * (double) getDimension()*(double) getDimension() / dist));
    }

    /**
     * @param parentheses Decides if the output is surrounded by parentheses. 
     * @return The coordinates of the point.
     */
    std::string Point::toString(bool parentheses) const {
        unsigned dimension = mCoordinates.size();
        std::string result;

        if (parentheses) {
            result += "(";
        }

        for (unsigned i = 0; i < dimension - 1; i++) {
            result += boost::lexical_cast<std::string > (mCoordinates[i]) + " ";
        }
        result += boost::lexical_cast<std::string > (mCoordinates[dimension - 1]);

        if (parentheses) {
            result += ")";
        }
        return result;

    }
    /**
     * @brief random move in one direction.
     */
    void Point::moveRandom() {
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
    void Point::setCoordinates(int coordinates[], unsigned dimension, unsigned offset) {
        mCoordinates.reserve(dimension + offset);
        for (unsigned i = 0; i < dimension; i++) {
            mCoordinates[i + offset] = coordinates[i];
        }
    }

    /**
     * 
     * @return the sum of all coordinates
     */
    unsigned Point::sum() const {
        unsigned sum = 0;
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
    void Point::insertCoordinates(std::vector<int> coordinates, unsigned offset ) {
        std::vector<int>::iterator it = mCoordinates.begin();
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
    Point Point::coordinateMax(const Point& p1, const Point p2) {
        Point p = Point(p1.getDimension());
        for (unsigned k = 0; k < p.getDimension(); k++) {
            (p1[k] > p2[k]) ? p[k] = p1[k] : p[k] = p2[k];
        }
        return p;
    }

    /**
     * @brief: function to calculate points in the neighborhood, with one fixed dimension.
     * @return std::vector with all points in the neighborhood, with a fixed dimension, and except the point itself.
     */
    std::vector<Point> Point::getAllNeighbours(bool pointself) const {
        std::vector<Point> neighbors = getAllNeighborsForAFixedDimension(0);
        unsigned nrneighbors = neighbors.size();
        //TODO comment!
        for (unsigned i = 0; i < nrneighbors; i++) {
            Point neighborpredecessor = Point(neighbors[i]).getPredecessorInDimension(0);
            neighbors.push_back(neighborpredecessor);
        }

        Point pointPredecessor = getPredecessorInDimension(0);
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
    std::vector<Point> Point::getAllNeighborsForAFixedDimension(int fixedDim) const {
        std::vector<Point> neighbors;
        unsigned dim = getDimension();

        // TODO comment
        int nrofNeighbors = (pow(2, (dim - 1)) - 1);
        neighbors.reserve(nrofNeighbors);

        std::vector<int> coordinates;
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
            Point neighbor = Point(coordinates);
            neighbors.push_back(neighbor);
        }
        return neighbors;
    }

} // end namespace