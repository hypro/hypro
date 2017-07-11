#pragma once
#include "State.h"
#include "Visitors.h"
#include "../../types.h"

namespace hypro {

template<typename Number>
class Reset {
protected:
    vector_t<Number> continuousVec;  // Translation Vector
    matrix_t<Number> continuousMat;  // Transformation Matrix
    vector_t<Number> discreteVec;  // Translation Vector
    matrix_t<Number> discreteMat;  // Transformation Matrix
	vector_t<Number> clockVec;  // Translation Vector
    matrix_t<Number> clockMat;  // Transformation Matrix
    bool hasContinuousReset = false;
    bool hasDiscreteReset = false;
    bool hasClockReset = false;

public:
	Reset() = default;
	Reset(const Reset& orig) = default;
	Reset(Reset&& orig) = default;
	Reset& operator=(const Reset<Number>& orig) = default;
	Reset& operator=(Reset<Number>&& orig) = default;
	~Reset() {}

	const vector_t<Number>& getContinuousResetVector() const { return continuousVec; }
	const matrix_t<Number>& getContinuousResetMatrix() const { return continuousMat; }
	const vector_t<Number>& getDiscreteResetVector() const { return discreteVec; }
	const matrix_t<Number>& getDiscreteResetMatrix() const { return discreteMat; }
	const vector_t<Number>& getClockResetVector() const { return clockVec; }
	const matrix_t<Number>& getClockResetMatrix() const { return clockMat; }

	void setContinuousResetVector(const vector_t<Number>& in) { continuousVec = in; hasContinuousReset = true; }
	void setContinuousResetMatrix(const matrix_t<Number>& in) { continuousMat = in; hasContinuousReset = true; }
	void setDiscreteResetVector(const vector_t<Number>& in) { discreteVec = in; hasDiscreteReset = true; }
	void setDiscreteResetMatrix(const matrix_t<Number>& in) { discreteMat = in; hasDiscreteReset = true; }
	void setClockResetVector(const vector_t<Number>& in) { clockVec = in; hasClockReset = true; }
	void setClockResetMatrix(const matrix_t<Number>& in) { clockMat = in; hasClockReset = true; }

	State applyReset(const State<Number>& inState) const;
	State applyDiscreteReset(const State<Number>& inState) const;

    friend std::ostream& operator<<(std::ostream& ostr, const Reset<Number>& a)
    {
#ifdef HYPRO_USE_LOGGING
        ostr << "Continuous transformation: " << a.continuousMat << " and const " << a.continuousVec;
        ostr << "Discrete transformation: " << a.discreteMat << " and const " << a.discreteVec;
        ostr << "Clock transformation: " << a.clockMat << " and const " << a.clockVec;
#endif
        return ostr;
    }

    friend bool operator==(const Reset<Number>& lhs, const Reset<Number>& rhs) {
    	return (lhs.continuousVec == rhs.continuousVec && lhs.continuousMat == rhs.continuousMat &&
    			lhs.discreteVec == rhs.discreteVec && lhs.discreteMat == rhs.discreteMat &&
    			lhs.clockVec == rhs.clockVec && lhs.clockMat == rhs.clockMat);
    }

    friend bool operator!=(const Reset<Number>& lhs, const Reset<Number>& rhs) {
    	return !(lhs == rhs);
    }
};

} // namespace

#include "Reset.tpp"
