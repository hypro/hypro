/** 
 * @file   box.h
 * Created on May 16, 2011
 * Last modified June 7, 2011
 * 
 * @author Sebastian Junges
 */

#ifndef BOX_H
#define	BOX_H

#include <iostream>
#include <set>
#include "settings.h"
#include "vertex.h"


namespace reachLin {
    class Box {
    public:
        Box(unsigned dimension);
        Box(std::vector<int> max, std::vector<int> min);
        Box(std::vector<int> max);
        virtual ~Box();

        
        /**
     * Calculates the bounding box around the Polyhedron to do some quick checks.
     *
     */
        template<typename ForwardIterator>
     void calculateBox(const ForwardIterator begin, const ForwardIterator end) {
         if (begin == end) {
            // Empty vertex
            return;
        }

        LOG4CPLUS_DEBUG(mLogger, "Update the Box");
        std::set<Vertex>::iterator it;

        mMax.resize(mDimension);
        mMin.resize(mDimension);

        it = begin;
        // Set the box to include the first vertex, so nothing goes wrong. (Before, we should make sure there is a first one)
        for (unsigned d = 0; d < mDimension; d++) {
            mMax[d] = it->getCoordinate(d);
            // TODO speed it up if origin is a vertex..
            mMin[d] = it->getCoordinate(d);
        }
        
        
        LOG4CPLUS_DEBUG(mLogger, "Extend the Box");

        //Extend the box
        for (unsigned d = 0; d < mDimension; d++) {
            it = begin;
            it++;
            for (; it != end; ++it) {
                if (it->getCoordinate(d) > mMax[d]) {
                    mMax[d] = it->getCoordinate(d);
                } else if (it->getCoordinate(d) < mMin[d]) {
                    mMin[d] = it->getCoordinate(d);
                }
            }
        }
    }
     
         bool isMember(const Point& pt) const;
         inline void clear() {
             mMin.clear();
             mMax.clear();
         }
         Point getMax() { return Point(mMax);}

         
         friend std::ostream& operator<<(std::ostream& ostr, const Box& box);

    private:
        unsigned mDimension;
        std::vector<int> mMin;
        std::vector<int> mMax;
        Logger mLogger;

    };
}
#endif	/* BOX_H */

