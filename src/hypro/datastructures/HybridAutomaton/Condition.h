#pragma once
#include "State.h"
#include "Visitors.h"
#include "lib/utils/types.h"
#include <hypro/types.h>
#include <hypro/representations/GeometricObject.h>
#include <iostream>

namespace hydra {

class Condition {
private:
    hypro::vector_t<Number> vec;
    hypro::matrix_t<Number> mat;
    hypro::vector_t<Number> discreteVec;
    hypro::matrix_t<Number> discreteMat;
    hypro::vector_t<Number> clockVec;
    hypro::matrix_t<Number> clockMat;
    bool hasDiscreteConstraints = false;
    bool hasClockConstraints = false;

public:
	Condition() = default;
	Condition(const Condition& orig) = default;
	Condition(Condition&& orig) = default;
	Condition& operator=(const Condition& orig) = default;
	Condition& operator=(Condition&& orig) = default;
	~Condition() {}

	// Access
	const hypro::vector_t<Number>& getVector() const { return vec; }
	const hypro::matrix_t<Number>& getMatrix() const { return mat; }
	const hypro::vector_t<Number>& getDiscreteVector() const { return discreteVec; }
	const hypro::matrix_t<Number>& getDiscreteMatrix() const { return discreteMat; }
	const hypro::vector_t<Number>& getClockVector() const { return clockVec; }
	const hypro::matrix_t<Number>& getClockMatrix() const { return clockMat; }

	void setVector(const hypro::vector_t<Number>& v) { vec = v; }
	void setMatrix(const hypro::matrix_t<Number>& m) { mat = m; }
	void setDiscreteVector(const hypro::vector_t<Number>& v) { discreteVec = v; hasDiscreteConstraints = true; }
	void setDiscreteMatrix(const hypro::matrix_t<Number>& m) { discreteMat = m; hasDiscreteConstraints = true; }
	void setClockVector(const hypro::vector_t<Number>& v) { clockVec = v; hasClockConstraints = true; }
	void setClockMatrix(const hypro::matrix_t<Number>& m) { clockMat = m; hasClockConstraints = true; }

	// helper methods
	std::pair<bool,State> isSatisfiedBy(const State& inState) const;
	std::pair<bool,State> continuousIsSatisfiedBy(const State& inState) const;
	std::pair<bool,State> discreteIsSatisfiedBy(const State& inState) const;
	std::pair<bool,State> clockIsSatisfiedBy(const State& inState) const;

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
