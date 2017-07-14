#pragma once
#include "State.h"
#include "Visitors.h"
#include "../../representations/GeometricObject.h"
#include "../../representations/types.h"
#include <iostream>

namespace hypro {

template<typename Number>
class Condition {
private:
    vector_t<Number> vec;
    matrix_t<Number> mat;
    vector_t<Number> discreteVec;
    matrix_t<Number> discreteMat;
    vector_t<Number> clockVec;
    matrix_t<Number> clockMat;
    bool hasDiscreteConstraints = false;
    bool hasClockConstraints = false;

public:
	Condition() = default;
	Condition(const matrix_t<Number>& mat, const vector_t<Number>& vec) : mat(mat), vec(vec) {}
	Condition(const Condition& orig) = default;
	Condition(Condition&& orig) = default;
	Condition& operator=(const Condition& orig) = default;
	Condition& operator=(Condition&& orig) = default;
	~Condition() {}

	// Access
	const vector_t<Number>& getVector() const { return vec; }
	const matrix_t<Number>& getMatrix() const { return mat; }
	const vector_t<Number>& getDiscreteVector() const { return discreteVec; }
	const matrix_t<Number>& getDiscreteMatrix() const { return discreteMat; }
	const vector_t<Number>& getClockVector() const { return clockVec; }
	const matrix_t<Number>& getClockMatrix() const { return clockMat; }

	void setVector(const vector_t<Number>& v) { vec = v; }
	void setMatrix(const matrix_t<Number>& m) { mat = m; }
	void setDiscreteVector(const vector_t<Number>& v) { discreteVec = v; hasDiscreteConstraints = true; }
	void setDiscreteMatrix(const matrix_t<Number>& m) { discreteMat = m; hasDiscreteConstraints = true; }
	void setClockVector(const vector_t<Number>& v) { clockVec = v; hasClockConstraints = true; }
	void setClockMatrix(const matrix_t<Number>& m) { clockMat = m; hasClockConstraints = true; }

	// helper methods
	template<typename Representation>
	std::pair<bool,State<Number,Representation>> isSatisfiedBy(const State<Number,Representation>& inState) const;
	template<typename Representation>
	std::pair<bool,State<Number,Representation>> continuousIsSatisfiedBy(const State<Number,Representation>& inState) const;
	template<typename Representation>
	std::pair<bool,State<Number,Representation>> discreteIsSatisfiedBy(const State<Number,Representation>& inState) const;
	template<typename Representation>
	std::pair<bool,State<Number,Representation>> clockIsSatisfiedBy(const State<Number,Representation>& inState) const;

	friend bool operator==(const Condition& lhs, const Condition& rhs) {
		return (lhs.vec == rhs.vec && lhs.mat == rhs.mat &&
				lhs.discreteVec == rhs.discreteVec && lhs.discreteMat == rhs.discreteMat &&
				lhs.clockVec == rhs.clockVec && lhs.clockMat == rhs.clockMat
				);
	}

	friend bool operator!=(const Condition& lhs, const Condition& rhs) {
		return !(lhs == rhs);
	}

	friend std::ostream& operator<<(std::ostream& out, const Condition& in) {
#ifdef HYDRA_USE_LOGGING
		out << "Cont. Mat: " << in.mat << std::endl;
		out << "Cont. Vec: " << in.vec << std::endl;
		out << "Disc. Mat: " << in.discreteMat << std::endl;
		out << "Disc. Vec: " << in.discreteVec << std::endl;
		out << "Clck. Mat: " << in.clockMat << std::endl;
		out << "Clck. Vec: " << in.clockVec << std::endl;
#endif
		return out;
	}
};

} // namespace

#include "Condition.tpp"
