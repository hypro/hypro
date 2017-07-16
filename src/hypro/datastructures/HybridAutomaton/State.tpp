#include "State.h"

namespace hypro
{

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

	//res.setSet(in.getSet().unite(getSet()));

	//TRACE("hydra.datastructures","After continuous aggregation " << res );

	//if(mHasClocks) {
	//	res.setClockAssignment(in.getClockAssignment().unite(res.getClockAssignment()));
	//	//TRACE("hydra.datastructures","After clock aggregation " << res );
	//}

	res.setTimestamp(mTimestamp.convexHull(in.getTimestamp()));
	return res;
}

template<typename Number, typename Representation, typename ...Rargs>
std::pair<bool,State<Number,Representation,Rargs...>> State<Number,Representation,Rargs...>::intersect(const State<Number,Representation,Rargs...>& in) const {
	//DEBUG("hydra.datastructures","this rep name: " << mSetRepresentationName << " vs " << in.getSetRepresentation());
	//assert(mSetRepresentationName == in.getSetRepresentation());

	State<Number,Representation,Rargs...> res(*this);
	bool empty = true;
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
State<Number,Representation,Rargs...> State<Number,Representation,Rargs...>::applyTimeStep(const matrix_t<Number>& trafoMatrix, const vector_t<Number>& trafoVector, Number timeStepSize ) const {
	State<Number,Representation,Rargs...> res(*this);
	//TRACE("hydra.datastructures","Apply timestep of size " << timeStepSize);
	//res.setSet(mSet.affineTransformation(trafoMatrix,trafoVector));
	res.addTimeToClocks(timeStepSize);
	return res;
}

}
