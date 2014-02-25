/** 
 * @file   box.cpp
 * Created on May 16, 2011
 * Last modified June 7, 2011
 * 
 * @author Sebastian Junges
 */
#include <map>

#include "box.h"

using namespace log4cplus;

namespace reachLin {

    Box::Box(unsigned dimension) {
        mDimension = dimension;
        mMax.resize(mDimension,0);
        mMin.resize(mDimension,0);
        mLogger = Logger::getInstance("reachLin.Box");
        
    }
    
    Box::Box(std::vector<int> max) {
        mMax = max;
        mDimension = mMax.size();
        mMin.resize(mDimension, 0);
        mLogger = Logger::getInstance("reachLin.Box");
        
        if (mMax.size() != mDimension) {
            LOG4CPLUS_WARN(mLogger, "Dimensions in Box are not correctly set.");
        }
    }
    
    Box::Box(std::vector<int> max, std::vector<int> min) {
        mMin = min;
        mMax = max;
        mDimension = mMin.size();
        mLogger = Logger::getInstance("reachLin.Box");
        
        if (mMax.size() != mDimension) {
            LOG4CPLUS_WARN(mLogger, "Dimensions in Box are not correctly set.");
        }
    }

    Box::~Box() {
    }

    
    bool Box::isMember(const Point& pt) const {   
        for (unsigned i = 0; i < mDimension; i++) {
            //could be >= instead of >, but this only works with full dimensions.
            if (pt[i] < mMin[i] || pt[i] > mMax[i])
                return false;
        }
        return true;
    }
    
    
     std::ostream& operator<<(std::ostream& ostr, const Box& box) {
        for (unsigned i = 0; i < box.mDimension - 1; i++) {
            ostr << "[" << box.mMin[i] << "," << box.mMax[i] << "] X ";
        }
        ostr << "[" << box.mMin[box.mDimension - 1] << "," << box.mMax[box.mDimension - 1] << "]";
    return ostr;
    }
    
}