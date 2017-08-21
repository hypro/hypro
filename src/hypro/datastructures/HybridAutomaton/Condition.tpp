#include "Condition.h"

namespace hypro {

template<typename Number>
Condition<Number>::Condition(const std::vector<boost::variant<ConstraintSet<Number>>>& sets)
{
	for(const auto& item : sets) {
		mConstraints.push_back(boost::get<ConstraintSet<Number>>(item));
	}
}

template<typename Number>
void Condition<Number>::setMatrix(const matrix_t<Number>& m, std::size_t I) {
	while (I >= mConstraints.size()) {
		mConstraints.push_back(ConstraintSet<Number>());
	}
	mConstraints[I].rMatrix() = m;
	DEBUG("hypro.datastructures","Set matrix at pos " << I << ", mConstraints.size() = " << mConstraints.size());
}

template<typename Number>
void Condition<Number>::setVector(const vector_t<Number>& v, std::size_t I) {
	while (I > mConstraints.size()) {
		mConstraints.push_back(ConstraintSet<Number>());
	}
	mConstraints[I].rVector() = v;
	DEBUG("hypro.datastructures","Set vector at pos " << I << ", mConstraints.size() = " << mConstraints.size());
}

//template<typename Number>
//template<typename Representation, typename ...Rargs>
//std::pair<bool,State<Number,Representation, Rargs...>> Condition<Number>::isSatisfiedBy(const State<Number,Representation, Rargs...>& inState) const {
//	#ifdef HYDRA_USE_LOGGING
//	DEBUG("hydra.datastructures","Checking condition.");
//	DEBUG("hydra.datastructures","State: " << inState);
//	#endif
//
//	// TODO: Overthink order here - it would be nice to test clocks first, then discrete assignments and continuous sets last.
//	State<Number,Representation> res(inState);
//	bool empty = false;
//	for(std::size_t i = 0; i < this->size(); ++i) {
//		if(mConstraints.at(i).first.rows() == 0) {
//			assert(mConstraints.at(i).second.rows() == 0);
//		} else {
//			//TRACE("hydra.datastructures","Check continuous condition, mat: " << mat << " and vector " << vec << " of state " << inState);
//			std::tuple_element<i, std::tuple<Representation, Rargs...>>::type> contSet = res.getSet<i>().satisfiesHalfspaces(mConstraints.at(i).first, mConstraints.at(i).second);
//			if(contSet.first) {
//				//TRACE("hydra.datastructures","Not empty, resulting set: ");
//				empty = false;
//				res.setSet<i>(contSet.second);
//				//TRACE("hydra.datastructures",res);
//			} else {
//				empty = true;
//				break;
//			}
//		}
//	}
//
//	//DEBUG("hydra.datastructures","Condition is satisfied: " << !empty);
//	return std::make_pair(!empty, res);
//}

} // namespace
