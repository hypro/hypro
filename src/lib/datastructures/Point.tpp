#include "Point.h"
#include "PointFactoryManager.h"

namespace hypro
{
    template<typename Number>
    Point<Number>::~Point() 
    {
        mCoordinates.clear();
    }

    template<typename Number>
    typename Point<Number>::coordinateValues Point<Number>::coordinates() const 
    {
        return mCoordinates;
    }

    template<typename Number>
    typename Point<Number>::coordinateValues& Point<Number>::rCoordinates()
    {
        return mCoordinates;
    }

    template<typename Number>
    unsigned Point<Number>::factory() const
    {
        return mFactoryId;
    }

    template<typename Number>
    carl::FLOAT_T<Number> Point<Number>::coordinate(unsigned _index) const
    {
        return mCoordinates.at(_index);
    }
    
    template<typename Number>
    carl::FLOAT_T<Number> Point<Number>::coordinate(carl::Variable _var) const
    {
        return mCoordinates.at(PointFactoryManager::instance().factory(mFactoryId)->variableIndex(_var));
    }

    template<typename Number>
    inline void Point<Number>::setCoordinate(unsigned _index, carl::FLOAT_T<Number> value)
    {
        mCoordinates[_index] = value;
    }

    template<typename Number>
    typename Point<Number>::coordinateValues::const_iterator Point<Number>::begin() const
    {
        return mCoordinates.begin();
    }

    template<typename Number>
    typename Point<Number>::coordinateValues::const_iterator Point<Number>::end() const
    {
        return mCoordinates.end();
    }

    template<typename Number>
    unsigned Point<Number>::dimension() const 
    {
        return mCoordinates.size();
    }

    template<typename Number>
    std::vector<carl::FLOAT_T<Number>> Point<Number>::polarCoordinates( const Point<Number>& origin,  bool radians) const
    {
        Point<Number> base = *this - origin;
        std::cout << "Point: " << base << std::endl;


        std::vector<carl::FLOAT_T<Number>> result;

        // 1st component of the result is the radial part, the following components are the angles.
        carl::FLOAT_T<Number> radialCoordinate;
        for(auto dimension : base.mCoordinates)
        {
            carl::FLOAT_T<Number> square;
            dimension.second.pow(square, 2);
            radialCoordinate += square;
        }
        radialCoordinate.sqrt_assign();
        result.insert(result.begin(), radialCoordinate);

        std::cout << "Radial coordinate: " << radialCoordinate << std::endl;

        // compute polar angles
        carl::FLOAT_T<Number> angle;
        for(auto dimension = base.mCoordinates.begin(); dimension != --base.mCoordinates.end(); ++dimension)
        {
            std::cout << "Processing: " << (*dimension).first << "->" << (*dimension).second << std::endl;
            angle = 0;
            for(auto dimension2 = dimension; dimension2 != base.mCoordinates.end(); ++dimension2)
            {
                carl::FLOAT_T<Number> square;
                angle += (*dimension2).second.pow(square, 2);
            }
            std::cout << "Summed squares: " << angle << std::endl;
            angle.sqrt_assign();
            angle = (*dimension).second / angle;
            std::cout << "After division: " << angle << std::endl;
            angle.acos_assign();
            std::cout << "After acos: " << angle << std::endl;
            if(!radians)
            {
                angle /= 2*PI_DN ;
                angle *= 360;
            }
            result.insert(result.end(), angle);
            std::cout << "Angle: " << angle << std::endl;
        }
        if((*base.mCoordinates.rbegin()).second < 0)
        {
            std::cout << "Correct last angle: ";
            carl::FLOAT_T<Number> tmp = result.back();
            result.pop_back();
            if(!radians)
            {
                tmp = 360 - tmp;
            }
            else
            {
                tmp = -1* tmp;
            }
            std::cout << tmp << std::endl;
            result.push_back(tmp);
        }

        assert(result.size() == this->dimension());
        return result;
    }

    template<typename Number>
    bool Point<Number>::move(const Point<Number>& p) 
    {
        bool negative = false;
        for(auto pointIt = p.begin(); pointIt != p.end(); ++pointIt)
        {
            if(mCoordinates.count((*pointIt).first) > 0)
            {
                mCoordinates[(*pointIt).first] += (*pointIt).second;
            }
            else
            {
                mCoordinates[(*pointIt).first] = (*pointIt).second;
            }
            if (mCoordinates.at((*pointIt).first) < 0) negative = true;
        }
        return negative;
    }

    template<typename Number>
    void Point<Number>::nextPointOnGrid(const Point<Number>& bounds) 
    {
        for(auto pointIt : mCoordinates)
        {
            if ((*pointIt).second < bounds.coordinate((*pointIt).first))
            {
                ++mCoordinates[(*pointIt).first];
                return;
            }
            else 
            {
                mCoordinates[(*pointIt).first] = 0; //TODO: sure to set it to zero instead of setting it to bounds[i-1] ?
            }
        }
    }

    template<typename Number>
    carl::FLOAT_T<Number> Point<Number>::getGaussianProbability(Point<Number> & mean) const{
        return 0;
    }

    template<typename Number>
    carl::FLOAT_T<Number> Point<Number>::getDistanceDependentProbabiltity(Point<Number> & mean, unsigned intlength, carl::FLOAT_T<Number> rate) const
    {
        carl::FLOAT_T<Number> dist;
        for (auto pointIt : mCoordinates)
                        {
            dist += ( (*pointIt).second - mean.coordinate((*pointIt).first) ).pow(carl::FLOAT_T<Number>(2));
        }
        dist /= rate; //TODO: use proper rounding?
        if (dist < 1) return 1;
        return (((carl::FLOAT_T<Number>) intlength * (carl::FLOAT_T<Number>) dimension()*(carl::FLOAT_T<Number>) dimension() / dist));
    }

    template<typename Number>
    carl::FLOAT_T<Number> Point<Number>::sum() const
    {
        carl::FLOAT_T<Number> sum = 0;
        for (auto pointIt : mCoordinates)
        {
            sum += (pointIt).second;
        }
        return sum;
    }

    template<typename Number>
    std::vector<Point<Number> > Point<Number>::getAllNeighborsForAFixedDimension(const carl::Variable& fixedDim) const
    {
        std::vector<Point<Number> > neighbors;
        unsigned dim = dimension();

        // TODO comment
        int nrofNeighbors = (pow(2, (dim - 1)) - 1);

        coordinateValues coordinates;

        for (int neighborNr = 1; neighborNr <= nrofNeighbors; neighborNr++) {
            //calculate the next neighbor we going to check
            for (auto pointIt : mCoordinates)
            {
                if ((*pointIt).first > fixedDim)
                {
                    coordinates[(*pointIt).first] = (*pointIt).second - ((neighborNr >> (dim - (*pointIt).first - 1)) & 1);
                } else if ( (*pointIt).first == fixedDim)
                {
                    coordinates[(*pointIt).first] = (*pointIt).second;
                } else 
                { // k < fixed
                    coordinates[(*pointIt).first] = (*pointIt).second - ((neighborNr >> (dim - (*pointIt).first - 1 - 1)) & 1);
                }
            }
            Point<Number> neighbor = Point<Number>(coordinates);
            neighbors.push_back(neighbor);
        }
        return neighbors;
    }

    template<typename Number>
    std::vector<Point<Number> > Point<Number>::getAllNeighbours(bool pointself) const
    {
        std::vector<Point<Number> > neighbors = getAllNeighborsForAFixedDimension(0);
        unsigned nrneighbors = neighbors.size();
        //TODO comment!
        for (unsigned i = 0; i < nrneighbors; i++) 
        {
            Point<Number> neighborpredecessor = Point(neighbors[i]).getPredecessorInDimension(0);
            neighbors.push_back(neighborpredecessor);
        }

        Point<Number> pointPredecessor = getPredecessorInDimension(0);
        neighbors.push_back(pointPredecessor);

        if (pointself) 
        {
            neighbors.push_back(*this);
        }

        return neighbors;
    }

    template<typename Number>
    void Point<Number>::incrementInFixedDim(const carl::Variable& d)
    {
        ++(mCoordinates.at(d));
    }

    template<typename Number>
    void Point<Number>::incrementInAllDim(const carl::FLOAT_T<Number>& val)
    {
        for (auto pointIt : mCoordinates)
        {
            mCoordinates[(pointIt).first] += val;
        }
    }

    template<typename Number>
    void Point<Number>::decrementInFixedDim(const carl::Variable& d)
    {
        --(mCoordinates.at(d));
    }

    template<typename Number>
    Point<Number>& Point<Number>::getPredecessorInDimension(const carl::Variable& d) const
    {
        Point<Number> pred = Point(*this);
        pred.DecrementInFixedDim(d);
        return pred;
    }

    template<typename Number>
    bool Point<Number>::isInBoundary(const Point<Number>& boundary) const 
    {
        for (auto pointIt : mCoordinates)
        {
            if(!boundary.hasDimension(pointIt.first))
            {
                continue;
            }
            if (pointIt.second > boundary.at(pointIt.first)) return false;
        }
        return true;
    }

    template<typename Number>
    bool Point<Number>::hasDimension(const carl::Variable& i) const
    {
        return (mCoordinates.find(i) != mCoordinates.end());
    }

    template<typename Number>
    bool Point<Number>::haveEqualCoordinate(const Point<Number>& p2) const 
    {
        if( dimension() == p2.dimension() )
        {
            for (auto pointIt : mCoordinates)
            {
                if ( p2.hasDimension(pointIt.first))
                {
                    if ( pointIt.second == p2.mCoordinates.at(pointIt.first) ) return true;
                }
            }
        }
        return false;
    }

    template<typename Number>
    bool Point<Number>::haveSameDimensions(const Point<Number>& p) const
    {
        if (dimension() != p.dimension())
        {
            return false;
        }
        for (auto pointIt : mCoordinates)
        {
            if ( !p.hasDimension(pointIt.first))
            {
                return false;
            }
        }
        return true;
    }

    template<typename Number>
    carl::FLOAT_T<Number>& Point<Number>::operator[] (const carl::Variable& i)
    {
        return mCoordinates[i];
    }

    template<typename Number>
    carl::FLOAT_T<Number> Point<Number>::at(const carl::Variable& i) const
    {
        return mCoordinates.at(i);
    }
}