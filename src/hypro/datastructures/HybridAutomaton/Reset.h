#pragma once
#include "../../types.h"
#include "../../representations/ConstraintSet/ConstraintSet.h"

namespace hypro {

template<typename Number>
class Reset {
protected:
	std::vector<ConstraintSetT<Number>> mResets;
    mutable std::size_t mHash = 0;

public:
	Reset() = default;
	Reset(const Reset& orig) = default;
	Reset(Reset&& orig) = default;
	Reset& operator=(const Reset<Number>& orig) = default;
	Reset& operator=(Reset<Number>&& orig) = default;
	Reset(const matrix_t<Number>& mat, const vector_t<Number>& vec);
	~Reset() {}

	bool empty() const { return mResets.empty(); }
	std::size_t size() const { return mResets.size(); }

	const vector_t<Number>& getVector(std::size_t I = 0) const { return mResets.at(I).vector(); }
	const matrix_t<Number>& getMatrix(std::size_t I = 0) const { return mResets.at(I).matrix(); }
	matrix_t<Number>& rGetMatrix(std::size_t I = 0) { return mResets[I].rMatrix(); }
	vector_t<Number>& rGetVector(std::size_t I = 0) { return mResets[I].rVector(); }

	ConstraintSetT<Number> getReset(std::size_t I = 0) const { return mResets.at(I); }
	ConstraintSetT<Number>& rGetReset(std::size_t I = 0) const { return mResets[I]; }
	const std::vector<ConstraintSetT<Number>>& getResetTransformations() const { return mResets; }

	void setVector(const vector_t<Number>& in, std::size_t I = 0);
	void setMatrix(const matrix_t<Number>& in, std::size_t I = 0);

	bool isIdentity() const;

    std::size_t hash() const;
     /**
    * decomposes reset
    */
    void decompose(std::vector<std::vector<size_t>> decomposition);

#ifdef HYPRO_LOGGING
    friend std::ostream& operator<<(std::ostream& ostr, const Reset<Number>& a)
#else
    friend std::ostream& operator<<(std::ostream& ostr, const Reset<Number>&)
#endif
    {
#ifdef HYPRO_LOGGING
    	ostr << "Resets: " << std::endl;
    	for(const auto& r : a.getResetTransformations()) {
    		ostr << r;
    	}
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

template<typename Number>
Reset<Number> combine(
    const Reset<Number>& lhs, const Reset<Number>& rhs,
    const std::vector<std::string> haVar, const std::vector<std::string> lhsVar, const std::vector<std::string> rhsVar);


} // namespace

namespace std {

    template<typename Number>
    struct hash<hypro::Reset<Number>>{
        std::size_t operator()(const hypro::Reset<Number>& reset) const {
            std::size_t seed = 0;
            for(auto conSet : reset.getResetTransformations()){
                carl::hash_add(seed, std::hash<hypro::matrix_t<Number>>()(conSet.matrix()));
                carl::hash_add(seed, std::hash<hypro::vector_t<Number>>()(conSet.vector()));
            }
            return seed;
        }
    };

}

#include "Reset.tpp"
