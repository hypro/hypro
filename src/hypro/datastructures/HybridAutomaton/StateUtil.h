#include "Reset.h"

namespace hypro {

    template<typename Number, typename Representation, typename ...Rargs>
	State<Number,Representation,Rargs...> applyReset(const State<Number,Representation,Rargs...>& inState, const Reset<Number>& reset) {
        TRACE("hydra.datastructures","inState #sets: " << inState.getNumberSets() << " and #resets: " << reset.size());
		assert(reset.empty() || inState.getNumberSets() == reset.size());
		if(reset.empty()) {
			DEBUG("hypro.datastructures","Reset is empty.");
			return inState;
		}
		auto res = inState;
		auto visitor = detail::make_reset_visitor<ResetType>([](const auto& in){ return detail::getType(in); });
		std::size_t pos = 0;
		for(const auto& reset : reset.getResetTransformations()) {
			DEBUG("hypro.datastructures","Apply reset for subspace " << pos);
			if(boost::apply_visitor(visitor, reset) == ResetType::affine ) {
				res = res.applyTransformation(boost::get<AffineTransformation<Number>>(reset).mTransformation, pos);
			}
			++pos;
		}

		return res;
    }

} // hypro
