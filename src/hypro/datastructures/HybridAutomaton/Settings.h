#pragma once
#include <carl/numbers/numbers.h>
#include <iostream>
#include <string>

namespace hypro
{
template <typename Number>
struct ReachabilitySettings {
    Number timeBound;
    int jumpDepth;
    Number timeStep;
    std::string fileName;
    unsigned long pplDenomimator;
    std::vector<std::vector<unsigned>> plotDimensions;
    bool uniformBloating = false;

    ReachabilitySettings<Number>() : timeBound(0), jumpDepth(0), timeStep(0), fileName("out"), pplDenomimator(0) {}
    ReachabilitySettings<Number>& operator=(const ReachabilitySettings<Number>& _rhs)
    {
        timeBound = _rhs.timeBound;
        jumpDepth = _rhs.jumpDepth;
        timeStep = _rhs.timeStep;
        fileName = _rhs.fileName;
        pplDenomimator = _rhs.pplDenomimator;
        plotDimensions = _rhs.plotDimensions;
        uniformBloating = _rhs.uniformBloating;
        return *this;
    }

    friend bool operator==(const ReachabilitySettings<Number>& lhs, const ReachabilitySettings<Number>& rhs) {
    	return (
    		lhs.timeBound == rhs.timeBound &&
    		lhs.jumpDepth == rhs.jumpDepth &&
    		lhs.timeStep == rhs.timeStep &&
    		lhs.fileName== rhs.fileName &&
    		lhs.pplDenomimator == rhs.pplDenomimator &&
    		lhs.plotDimensions == rhs.plotDimensions &&
    		lhs.uniformBloating == rhs.uniformBloating
    		);
    }

    friend std::ostream& operator<<(std::ostream& lhs, const ReachabilitySettings<Number>& rhs)
    {
        lhs << "Local time-horizon: " << carl::toDouble(rhs.timeBound) << std::endl;
        lhs << "Time-step size: " << carl::toDouble(rhs.timeStep) << std::endl;
        lhs << "Jump-depth: " << rhs.jumpDepth << std::endl;
        return lhs;
    }
};

}  // namespace hypro
