#pragma once
#include "State.h"
#include "Visitors.h"
//#include <hypro/types.h>
#include "../../types.h"

namespace hypro {

template<typename Number>
class Reset {
protected:
    hypro::vector_t<Number> continuousVec;  // Translation Vector
    hypro::matrix_t<Number> continuousMat;  // Transformation Matrix
    hypro::vector_t<Number> discreteVec;  // Translation Vector
    hypro::matrix_t<Number> discreteMat;  // Transformation Matrix
	hypro::vector_t<Number> clockVec;  // Translation Vector
    hypro::matrix_t<Number> clockMat;  // Transformation Matrix
    bool hasContinuousReset = false;
    bool hasDiscreteReset = false;
    bool hasClockReset = false;

public:
	Reset() = default;
	Reset(const Reset& orig) = default;
	Reset(Reset&& orig) = default;
	Reset& operator=(const Reset& orig) = default;
	Reset& operator=(Reset&& orig) = default;
	~Reset() {}

	const hypro::vector_t<Number>& getContinuousResetVector() const { return continuousVec; }
	const hypro::matrix_t<Number>& getContinuousResetMatrix() const { return continuousMat; }
	const hypro::vector_t<Number>& getDiscreteResetVector() const { return discreteVec; }
	const hypro::matrix_t<Number>& getDiscreteResetMatrix() const { return discreteMat; }
	const hypro::vector_t<Number>& getClockResetVector() const { return clockVec; }
	const hypro::matrix_t<Number>& getClockResetMatrix() const { return clockMat; }

	void setContinuousResetVector(const hypro::vector_t<Number>& in) { continuousVec = in; hasContinuousReset = true; }
	void setContinuousResetMatrix(const hypro::matrix_t<Number>& in) { continuousMat = in; hasContinuousReset = true; }
	void setDiscreteResetVector(const hypro::vector_t<Number>& in) { discreteVec = in; hasDiscreteReset = true; }
	void setDiscreteResetMatrix(const hypro::matrix_t<Number>& in) { discreteMat = in; hasDiscreteReset = true; }
	void setClockResetVector(const hypro::vector_t<Number>& in) { clockVec = in; hasClockReset = true; }
	void setClockResetMatrix(const hypro::matrix_t<Number>& in) { clockMat = in; hasClockReset = true; }

	State applyReset(const State& inState) const;
	State applyDiscreteReset(const State& inState) const;

    friend std::ostream& operator<<(std::ostream& ostr, const Reset& a)
    {
#ifdef HYDRA_USE_LOGGING
        ostr << "Continuous transformation: " << a.continuousMat << " and const " << a.continuousVec;
        ostr << "Discrete transformation: " << a.discreteMat << " and const " << a.discreteVec;
        ostr << "Clock transformation: " << a.clockMat << " and const " << a.clockVec;
#endif
        return ostr;
    }

    friend bool operator==(const Reset& lhs, const Reset& rhs) {
    	return (lhs.continuousVec == rhs.continuousVec && lhs.continuousMat == rhs.continuousMat &&
    			lhs.discreteVec == rhs.discreteVec && lhs.discreteMat == rhs.discreteMat &&
    			lhs.clockVec == rhs.clockVec && lhs.clockMat == rhs.clockMat);
    }

    friend bool operator!=(const Reset& lhs, const Reset& rhs) {
    	return !(lhs == rhs);
    }
};

} // namespace

#include "Reset.tpp"