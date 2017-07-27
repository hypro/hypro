#include "State.h"

namespace hypro
{

template<typename Number, typename Representation, typename ...Rargs>
const boost::variant<Representation,Rargs...>& State<Number,Representation,Rargs...>::getSet(std::size_t i) const {
	assert(mTypes.size() == mSets.size());
	return mSets.at(i);
//	switch(mTypes.at(i)) {
//		case representation_name::box: {
//			return boost::get<Box<Number>>(mSets.at(i));
//		}
//		case representation_name::constraint_set: {
//			return boost::get<ConstraintSet<Number>>(mSets.at(i));
//		}
//		case representation_name::polytope_h: {
//			return boost::get<HPolytope<Number>>(mSets.at(i));
//		}
//		case representation_name::polytope_v: {
//			return boost::get<VPolytope<Number>>(mSets.at(i));
//		}
//		#ifdef HYPRO_USE_PPL
//		case representation_name::ppl_polytope: {
//			return boost::get<Polytope<Number>>(mSets.at(i));
//		}
//		#endif
//		case representation_name::support_function: {
//			return boost::get<SupportFunction<Number>>(mSets.at(i));
//		}
//		case representation_name::zonotope: {
//			return boost::get<Zonotope<Number>>(mSets.at(i));
//		}
//		default:
//			assert(false);
//	}
}

template<typename Number, typename Representation, typename ...Rargs>
boost::variant<Representation,Rargs...>& State<Number,Representation,Rargs...>::rGetSet(std::size_t i) {
	assert(mTypes.size() == mSets.size());
	return mSets.at(i);
}


template<typename Number, typename Representation, typename ...Rargs>
void State<Number,Representation,Rargs...>::addTimeToClocks(Number t) {
	//TRACE("hydra.datastructures","Add timestep of size " << t << " to clocks.");
	//if(mHasClocks) {
	//	matrix_t<Number> identity = matrix_t<Number>::Identity(mClockAssignment.dimension(), mClockAssignment.dimension());
	//	vector_t<Number> clockShift = vector_t<Number>::Ones(mClockAssignment.dimension());
	//	clockShift = clockShift * t;
	//	mClockAssignment = mClockAssignment.affineTransformation(identity,clockShift);
	//}
	mTimestamp += t;
}

template<typename Number, typename Representation, typename ...Rargs>
State<Number,Representation,Rargs...> State<Number,Representation,Rargs...>::aggregate(const State<Number,Representation,Rargs...>& in) const {
	State<Number,Representation,Rargs...> res(*this);

	//TRACE("hydra.datastructures","Aggregation of " << res << " and " << in);

	// element-wise union.
	assert(mSets.size() == in.getSets().size());
	for(std::size_t i = 0; i < mSets.size(); ++i) {
		res.setSet(mSets.at(i).unite(in.getSet(i)), i);
	}

	//TRACE("hydra.datastructures","After continuous aggregation " << res );

	res.setTimestamp(mTimestamp.convexHull(in.getTimestamp()));
	return res;
}

template<typename Number, typename Representation, typename ...Rargs>
std::pair<bool,State<Number,Representation,Rargs...>> State<Number,Representation,Rargs...>::satisfies(const Condition<Number>& in) const {
	//DEBUG("hydra.datastructures","this rep name: " << mSetRepresentationName << " vs " << in.getSetRepresentation());
	//assert(mSetRepresentationName == in.getSetRepresentation());

	assert(in.size() == mSets.size());
	State<Number,Representation,Rargs...> res(*this);
	bool empty = false;

	for(std::size_t i = 0; i < mSets.size(); ++i) {
		auto resultPair = mSets.at(i).satisfiesHalfspaces(in.getMatrix(i), in.getVector(i));
		res.setSet(resultPair.second,i);
		if(!resultPair.first) {
			empty = true;
			break;
		}
	}


	//std::pair<bool,Representation> contPair = mSet.satisfiesHalfspaces(in.getSet().matrix(), in.getSet().vector());
	//if(contPair.first) {
	//	empty = false;
	//	res.setSet(contPair.second);
	//}

	//// clock sets.
	//if(mHasClocks && !empty) {
	//	std::pair<bool,clockSetRepresentation> clockPair = mClockAssignment.satisfiesHalfspaces(in.getClockAssignment().matrix(), in.getClockAssignment().vector());
	//	if(clockPair.first) {
	//		empty = false;
	//		res.setClockAssignment(clockPair.second);
	//	}
	//}
//
//	//// discrete sets.
//	//if(mHasDiscreteVariables && !empty) {
//	//	std::pair<bool,discreteSetRepresentation> discretePair = mDiscreteAssignment.satisfiesHalfspaces(in.getDiscreteAssignment().matrix(), in.getDiscreteAssignment().vector());
//	//	if(discretePair.first) {
//	//		empty = false;
//	//		res.setDiscreteAssignment(discretePair.second);
//	//	}
	//}

	return std::make_pair(!empty, res);
}

template<typename Number, typename Representation, typename ...Rargs>
std::pair<bool,State<Number,Representation,Rargs...>> State<Number,Representation,Rargs...>::partiallySatisfies(const Condition<Number>& in, std::size_t I) const {
	assert(in.size() == mSets.size());
	State<Number,Representation,Rargs...> res(*this);

	auto resultPair = mSets.at(I).satisfiesHalfspaces(in.getMatrix(I), in.getVector(I));
	res.setSet(resultPair.second,I);

	return std::make_pair(!resultPair.first, res);
}


template<typename Number, typename Representation, typename ...Rargs>
State<Number,Representation,Rargs...> State<Number,Representation,Rargs...>::applyTimeStep(const std::vector<std::pair<const matrix_t<Number>&, const vector_t<Number>&>>& flows, Number timeStepSize ) const {
	State<Number,Representation,Rargs...> res(*this);
	//TRACE("hydra.datastructures","Apply timestep of size " << timeStepSize);
	//res.setSet(mSet.affineTransformation(trafoMatrix,trafoVector));
	assert(flows.size() == mSets.size());
	for(std::size_t i = 0; i < mSets.size(); ++i) {
		res.setSet(mSets.at(i).affineTransformation(flows.at(i).first, flows.at(i).second));
	}
	res.addTimeToClocks(timeStepSize);
	return res;
}

template<typename Number, typename Representation, typename ...Rargs>
State<Number,Representation,Rargs...> State<Number,Representation,Rargs...>::partiallyApplyTimeStep(const ConstraintSet<Number>& flow, Number timeStepSize, std::size_t I ) const {
	State<Number,Representation,Rargs...> res(*this);
	assert(I < mSets.size());
	res.setSet(mSets.at(I).affineTransformation(flow.getMatrix(), flow.getVector()));

	res.addTimeToClocks(timeStepSize);
	return res;
}

template<typename Number, typename Representation, typename ...Rargs>
State<Number,Representation,Rargs...> State<Number,Representation,Rargs...>::applyTransformation(const std::vector<ConstraintSet<Number>>& trafos ) const {
	State<Number,Representation,Rargs...> res(*this);
	//TRACE("hydra.datastructures","Apply timestep of size " << timeStepSize);
	//res.setSet(mSet.affineTransformation(trafoMatrix,trafoVector));
	assert(trafos.size() == mSets.size());
	for(std::size_t i = 0; i < mSets.size(); ++i) {
		res.setSet(mSets.at(i).affineTransformation(trafos.at(i).getMatrix(), trafos.at(i).getVector()));
	}
	return res;
}


template<typename Number, typename Representation, typename ...Rargs>
State<Number,Representation,Rargs...> State<Number,Representation,Rargs...>::partiallyApplyTransformation(const std::vector<ConstraintSet<Number>>& trafos, const std::vector<std::size_t>& sets ) const {
	State<Number,Representation,Rargs...> res(*this);
	assert(trafos.size() == sets.size());
	for(std::size_t i = 0; i < sets.size(); ++i) {
		assert(sets.at(i) < mSets.size());
		res.setSet(mSets.at(sets.at(i)).affineTransformation(trafos.at(i).getMatrix(), trafos.at(i).getVector()));
	}
	return res;
}

template<typename Number, typename Representation, typename ...Rargs>
State<Number,Representation,Rargs...> State<Number,Representation,Rargs...>::partiallyApplyTransformation(const ConstraintSet<Number>& trafo, std::size_t setIndex ) const {
	State<Number,Representation,Rargs...> res(*this);
	assert(setIndex < mSets.size());
	res.setSet(mSets.at(setIndex).affineTransformation(trafo.getMatrix(), trafo.getVector()));
	return res;
}

}
