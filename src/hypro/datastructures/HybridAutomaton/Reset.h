#pragma once
#include "State.h"
#include "Visitors.h"
#include "../../types.h"

namespace hypro {

template<typename Number>
class Reset {
protected:
	std::vector<ConstraintSet<Number>> mResets;

public:
	Reset() = default;
	Reset(const Reset& orig) = default;
	Reset(Reset&& orig) = default;
	Reset& operator=(const Reset<Number>& orig) = default;
	Reset& operator=(Reset<Number>&& orig) = default;
	~Reset() {}

	std::size_t size() const { return mResets.size(); }

	const vector_t<Number>& getVector(std::size_t I = 0) const { return mResets.at(I).matrix(); }
	const matrix_t<Number>& getMatrix(std::size_t I = 0) const { return mResets.at(I).vector(); }
	matrix_t<Number>& rGetMatrix(std::size_t I = 0) const { return mResets[I].rMatrix(); }
	vector_t<Number>& rGetVector(std::size_t I = 0) const { return mResets[I].rVector(); }

	const ConstraintSet<Number>& getReset(std::size_t I = 0) const { return mResets.at(I); }
	ConstraintSet<Number>& rGetReset(std::size_t I = 0) const { return mResets[I]; }

	void setVector(const vector_t<Number>& in, std::size_t I = 0);
	void setMatrix(const matrix_t<Number>& in, std::size_t I = 0);

	template<typename Representation>
	State<Number,Representation> applyReset(const State<Number,Representation>& inState) const;

    friend std::ostream& operator<<(std::ostream& ostr, const Reset<Number>& a)
    {
#ifdef HYPRO_USE_LOGGING
        //ostr << "Continuous transformation: " << a.continuousMat << " and const " << a.continuousVec;
        //ostr << "Discrete transformation: " << a.discreteMat << " and const " << a.discreteVec;
        //ostr << "Clock transformation: " << a.clockMat << " and const " << a.clockVec;
#endif
        return ostr;
    }

    friend bool operator==(const Reset<Number>& lhs, const Reset<Number>& rhs) {
    	if(lhs.size() != rhs.size()) {
    		return false;
    	}

    	for(std::size_t i = 0; i < lhs.size(); ++i) {
    		if(lhs.getReset(i) != rhs.getReset(i)) {
    			return false;
    		}
    	}
    	return true;
    }

    friend bool operator!=(const Reset<Number>& lhs, const Reset<Number>& rhs) {
    	return !(lhs == rhs);
    }
};

} // namespace

#include "Reset.tpp"
