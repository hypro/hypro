#pragma once
//#include "State.h"
#include "functors.h"
#include "../../representations/GeometricObject.h"
#include "../../representations/types.h"
#include <iostream>

namespace hypro {

template<typename Number>
class Condition {
private:
	std::vector<std::pair<matrix_t<Number>, vector_t<Number>>> mConstraints;
public:
	Condition() = default;
	Condition(const matrix_t<Number>& mat, const vector_t<Number>& vec) : mConstraints( {std::make_pair(mat,vec)} ) {}
	Condition(const Condition& orig) = default;
	Condition(Condition&& orig) = default;
	Condition& operator=(const Condition& orig) = default;
	Condition& operator=(Condition&& orig) = default;
	~Condition() {}

	// Access
	std::size_t size() const { return mConstraints.size(); }

	const matrix_t<Number>& getMatrix(std::size_t I = 0) const { return mConstraints.at(I).first; }
	const vector_t<Number>& getVector(std::size_t I = 0) const { return mConstraints.at(I).second; }

	void setMatrix(const matrix_t<Number>& m, std::size_t I = 0) { mConstraints[I].first = m; }
	void setVector(const vector_t<Number>& v, std::size_t I = 0) { mConstraints[I].second = v; }

	const std::vector<std::pair<matrix_t<Number>, vector_t<Number>>>& constraints() const { return mConstraints; }

	// helper methods
	//template<typename Representation, typename ...Rargs>
	//std::pair<bool,State<Number,Representation, Rargs...>> isSatisfiedBy(const State<Number,Representation, Rargs...>& inState) const;

	friend bool operator==(const Condition& lhs, const Condition& rhs) {
		if (lhs.size() != rhs.size()) {
			return false;
		}

		for(std::size_t i = 0; i < lhs.size(); ++i) {
			if ((lhs.getVector(i) != rhs.getVector(i)) || (lhs.getMatrix(i) != rhs.getMatrix(i))) {
				return false;
			}
		}
		return true;
	}

	friend bool operator!=(const Condition& lhs, const Condition& rhs) {
		return !(lhs == rhs);
	}

	friend std::ostream& operator<<(std::ostream& out, const Condition& in) {
#ifdef HYDRA_USE_LOGGING
		std::size_t i = 0;
		for(const auto& pair : in.constraints()) {
			out << "Constraint " << i << ": " << pair.first << " constants: " << pair.second << std::endl;
			++i;
		}
#endif
		return out;
	}
};

} // namespace

#include "Condition.tpp"
