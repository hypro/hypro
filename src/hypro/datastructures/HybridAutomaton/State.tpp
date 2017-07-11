#include "State.h"

namespace hypro
{

template<typename Number>
void State<Number>::addTimeToClocks(Number t) {
	//TRACE("hydra.datastructures","Add timestep of size " << t << " to clocks.");
	if(mHasClocks) {
		matrix_t<Number> identity = matrix_t<Number>::Identity(boost::get<clockSetRepresentation>(mClockAssignment).dimension(), boost::get<clockSetRepresentation>(mClockAssignment).dimension());
		vector_t<Number> clockShift = vector_t<Number>::Ones(boost::get<clockSetRepresentation>(mClockAssignment).dimension());
		clockShift = clockShift * t;
		mClockAssignment = boost::apply_visitor(genericAffineTransformationVisitor<RepresentationVariant>(identity,clockShift), mClockAssignment);
	}
	mTimestamp += t;
}

template<typename Number>
State State<Number>::aggregate(const State& in) const {
	assert(mDiscreteAssignment == in.getDiscreteAssignment());
	assert(mSetRepresentationName == in.getSetRepresentation());
	State res(*this);

	//TRACE("hydra.datastructures","Aggregation of " << res << " and " << in);

	res.setSet(boost::apply_visitor(genericUniteVisitor<RepresentationVariant>(), in.getSet(), getSet()));

	//TRACE("hydra.datastructures","After continuous aggregation " << res );

	if(mHasClocks) {
		res.setClockAssignment(boost::apply_visitor(genericUniteVisitor<RepresentationVariant>(), in.getClockAssignment(), res.getClockAssignment()));
		//TRACE("hydra.datastructures","After clock aggregation " << res );
	}

	res.setTimestamp(mTimestamp.convexHull(in.getTimestamp()));
	return res;
}

template<typename Number>
std::pair<bool,State> State<Number>::intersect(const State& in) const {
	//DEBUG("hydra.datastructures","this rep name: " << mSetRepresentationName << " vs " << in.getSetRepresentation());
	//assert(mSetRepresentationName == in.getSetRepresentation());

	State res(*this);
	bool empty = true;
	std::pair<bool,RepresentationVariant> contPair = boost::apply_visitor(genericSatisfiesHalfspacesVisitor<RepresentationVariant>(boost::get<cPair>(in.getSet()).first, boost::get<cPair>(in.getSet()).second), res.getSet());
	if(contPair.first) {
		empty = false;
		res.setSet(contPair.second);
	}

	// clock sets.
	if(mHasClocks && !empty) {
		std::pair<bool,RepresentationVariant> clockPair = boost::apply_visitor(genericSatisfiesHalfspacesVisitor<RepresentationVariant>(boost::get<cPair>(in.getClockAssignment()).first, boost::get<cPair>(in.getClockAssignment()).second), res.getClockAssignment());
		if(clockPair.first) {
			empty = false;
			res.setClockAssignment(clockPair.second);
		}
	}

	// discrete sets.
	if(mHasDiscreteVariables && !empty) {
		std::pair<bool,RepresentationVariant> discretePair = boost::apply_visitor(genericSatisfiesHalfspacesVisitor<RepresentationVariant>(boost::get<cPair>(in.getDiscreteAssignment()).first, boost::get<cPair>(in.getDiscreteAssignment()).second), res.getDiscreteAssignment());
		if(discretePair.first) {
			empty = false;
			res.setDiscreteAssignment(discretePair.second);
		}
	}

	return std::make_pair(!empty, res);
}

template<typename Number>
State State<Number>::applyTimeStep(const matrix_t<Number>& trafoMatrix, const vector_t<Number>& trafoVector, Number timeStepSize ) const {
	State res(*this);
	//TRACE("hydra.datastructures","Apply timestep of size " << timeStepSize);
	res.setSet(boost::apply_visitor(genericAffineTransformationVisitor<RepresentationVariant>(trafoMatrix,trafoVector), res.getSet()));
	res.addTimeToClocks(timeStepSize);
	return res;
}

}
