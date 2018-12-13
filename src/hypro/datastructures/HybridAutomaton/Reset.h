#pragma once
#include "ResetTypes.h"
#include "decomposition/Decomposition.h"
#include "../../types.h"
#include "../../representations/ConstraintSet/ConstraintSet.h"
#include <boost/variant.hpp>
#include <functional>

namespace hypro {

namespace detail {

	template<typename ReturnType, typename Function>
	struct ResetVisitor : public boost::static_visitor<ReturnType> {
		Function function;

		ResetVisitor() = delete;
		ResetVisitor(const Function& c) : function(c) {}

		template<typename In>
		ReturnType operator()(In&& reset) {
			return function(std::forward<In>(reset));
		}

	};

	template<class Result, class Func>
	ResetVisitor<Result,  std::decay_t<Func> > make_reset_visitor(Func && func)
	{
		return {std::forward<Func>(func)};
	}

}

template<typename Number>
class Reset {
public: using ResetVariant = boost::variant<AffineTransformation<Number>, IntervalAssignment<Number>>;

protected:
	std::vector<ResetVariant> mResets;
    mutable std::size_t mHash = 0;
	bool mDecomposed = false;

public:
	Reset() = default;
	Reset(const Reset& orig) = default;
	Reset(Reset&& orig) = default;
	Reset& operator=(const Reset<Number>& orig) = default;
	Reset& operator=(Reset<Number>&& orig) = default;
	Reset(const matrix_t<Number>& mat, const vector_t<Number>& vec);
	Reset(const std::vector<carl::Interval<Number>>& intervals);
	~Reset() {}

	bool empty() const { return mResets.empty(); }
	std::size_t size() const { return mResets.size(); }

	const vector_t<Number>& getVector(std::size_t I = 0) const;
	const matrix_t<Number>& getMatrix(std::size_t I = 0) const;
	matrix_t<Number>& rGetMatrix(std::size_t I = 0);
	vector_t<Number>& rGetVector(std::size_t I = 0);
	const std::vector<carl::Interval<Number>>& getIntervals(std::size_t I = 0) const;
	std::vector<carl::Interval<Number>>& rGetIntervals(std::size_t I = 0);

	const ResetVariant& getReset(std::size_t I = 0) const;
	ResetVariant& rGetReset(std::size_t I = 0) const;
	const std::vector<ResetVariant>& getResetTransformations() const { return mResets; }

	void setVector(const vector_t<Number>& in, std::size_t I = 0);
	void setMatrix(const matrix_t<Number>& in, std::size_t I = 0);

	bool isIdentity() const;

    std::size_t hash() const;
     /**
    * decomposes reset
    */
    void decompose(const Decomposition& decomposition);

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
			auto visitor = hypro::detail::make_reset_visitor<void>([&seed](const auto& in){ carl::hash_add(seed,in); });
			for(const auto& conSet : reset.getResetTransformations()){
				boost::apply_visitor(visitor, conSet);
            }
            return seed;
        }
    };

}

#include "Reset.tpp"
