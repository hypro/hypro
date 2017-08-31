#include "State.h"

namespace hypro
{

template<typename Number, typename Representation, typename ...Rargs>
const boost::variant<Representation,Rargs...>& State<Number,Representation,Rargs...>::getSet(std::size_t i) const {
	DEBUG("hypro.datastructures","Attempt to get set at pos " << i << ", mSets.size() = " << mSets.size() << ", mTypes.size() = " << mTypes.size());
	assert(mTypes.size() == mSets.size());
	assert(i < mSets.size());
	assert(checkConsistency());
	return mSets.at(i);
}

template<typename Number, typename Representation, typename ...Rargs>
boost::variant<Representation,Rargs...>& State<Number,Representation,Rargs...>::rGetSet(std::size_t i) {
	DEBUG("hypro.datastructures","Attempt to get set reference at pos " << i << ", mSets.size() = " << mSets.size());
	assert(mTypes.size() == mSets.size());
	assert(checkConsistency());
	return mSets.at(i);
}

template<typename Number, typename Representation, typename ...Rargs>
template<typename R>
void State<Number,Representation,Rargs...>::setSet(const R& s, std::size_t i) {
	DEBUG("hypro.datastructures","Attempt to set set at pos " << i << ", mSets.size() = " << mSets.size());
	assert(mSets.size() == mTypes.size());
	assert(checkConsistency());
	while(i >= mSets.size()) {
		mSets.emplace_back(Representation()); // some default set.
		mTypes.push_back(Representation::type()); // some default set type.
	}
	TRACE("hypro.datastructures","Set set to:" << s);
	mSets[i] = s;
	mTypes[i] = R::type();
	DEBUG("hypro.datastructures","Set set at pos " << i << ", mSets.size() = " << mSets.size());
	assert(mSets.size() > i);
}


template<typename Number, typename Representation, typename ...Rargs>
void State<Number,Representation,Rargs...>::addTimeToClocks(Number t) {
	TRACE("hypro.datastructures","Add timestep of size " << t << " to clocks.");
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

	TRACE("hypro.datastructures","Aggregation of " << res << " and " << in);

	// element-wise union.
	assert(mSets.size() == in.getSets().size());
	assert(checkConsistency());
	for(std::size_t i = 0; i < mSets.size(); ++i) {
		res.setSetDirect( boost::apply_visitor(genericUniteVisitor<repVariant>(), mSets.at(i), in.getSet(i)), i);
	}

	TRACE("hypro.datastructures","After continuous aggregation " << res );
	assert(checkConsistency());
	res.setTimestamp(mTimestamp.convexHull(in.getTimestamp()));
	return res;
}

template<typename Number, typename Representation, typename ...Rargs>
std::pair<bool,State<Number,Representation,Rargs...>> State<Number,Representation,Rargs...>::satisfies(const Condition<Number>& in) const {
	//DEBUG("hypro.datastructures","this rep name: " << mSetRepresentationName << " vs " << in.getSetRepresentation());
	//assert(mSetRepresentationName == in.getSetRepresentation());

	DEBUG("hypro.datastructures","This size: " << mSets.size() << ", condition size: " << in.size());
	assert(in.size() == mSets.size());
	assert(checkConsistency());
	State<Number,Representation,Rargs...> res(*this);
	bool empty = false;

	for(std::size_t i = 0; i < mSets.size(); ++i) {
		auto resultPair = boost::apply_visitor(genericSatisfiesHalfspacesVisitor<repVariant, Number>(in.getMatrix(), in.getVector()), mSets.at(i));
		res.setSetDirect(resultPair.second, i);

		if(!resultPair.first) {
			empty = true;
			break;
		}
	}

	return std::make_pair(!empty, res);
}

template<typename Number, typename Representation, typename ...Rargs>
std::pair<bool,State<Number,Representation,Rargs...>> State<Number,Representation,Rargs...>::partiallySatisfies(const Condition<Number>& in, std::size_t I) const {
	TRACE("hypro.datastructures","Check Condition of size " << in.size() << " against set at pos " << I);
	assert(in.size() == mSets.size());
	assert(checkConsistency());
	State<Number,Representation,Rargs...> res(*this);

	auto resultPair = boost::apply_visitor(genericSatisfiesHalfspacesVisitor<repVariant, Number>(in.getMatrix(), in.getVector()), mSets.at(I));
	res.setSetDirect(resultPair.second, I);

	return std::make_pair(resultPair.first, res);
}


template<typename Number, typename Representation, typename ...Rargs>
State<Number,Representation,Rargs...> State<Number,Representation,Rargs...>::applyTimeStep(const std::vector<std::pair<const matrix_t<Number>&, const vector_t<Number>&>>& flows, Number timeStepSize ) const {
	State<Number,Representation,Rargs...> res(*this);
	TRACE("hypro.datastructures","Apply timestep of size " << timeStepSize);
	//res.setSet(mSet.affineTransformation(trafoMatrix,trafoVector));
	assert(flows.size() == mSets.size());
	assert(checkConsistency());
	for(std::size_t i = 0; i < mSets.size(); ++i) {
		res.setSetDirect(boost::apply_visitor(genericAffineTransformationVisitor<repVariant, Number>(flows.at(i).first, flows.at(i).second), mSets.at(i)), i);
	}
	res.addTimeToClocks(timeStepSize);
	return res;
}

template<typename Number, typename Representation, typename ...Rargs>
State<Number,Representation,Rargs...> State<Number,Representation,Rargs...>::partiallyApplyTimeStep(const ConstraintSet<Number>& flow, Number timeStepSize, std::size_t I ) const {
	State<Number,Representation,Rargs...> res(*this);
	assert(I < mSets.size());
	assert(checkConsistency());
	res.setSetDirect(boost::apply_visitor(genericAffineTransformationVisitor<repVariant, Number>(flow.matrix(), flow.vector()), mSets.at(I)), I);

	res.addTimeToClocks(timeStepSize);
	return res;
}

template<typename Number, typename Representation, typename ...Rargs>
State<Number,Representation,Rargs...> State<Number,Representation,Rargs...>::applyTransformation(const std::vector<ConstraintSet<Number>>& trafos ) const {
	State<Number,Representation,Rargs...> res(*this);
	TRACE("hypro.datastructures","Apply transformation of " << mSets.size() << " sets (" << trafos.size() << " transformations).");
	assert(trafos.size() == mSets.size());
	assert(checkConsistency());
	for(std::size_t i = 0; i < mSets.size(); ++i) {
		res.setSetDirect(boost::apply_visitor(genericAffineTransformationVisitor<repVariant, Number>(trafos.at(i).matrix(), trafos.at(i).vector()), mSets.at(i)), i);
	}
	return res;
}

template<typename Number, typename Representation, typename ...Rargs>
State<Number,Representation,Rargs...> State<Number,Representation,Rargs...>::applyTransformation(const ConstraintSet<Number>& trafo ) const {
	State<Number,Representation,Rargs...> res(*this);
	TRACE("hypro.datastructures","Apply transformation of " << mSets.size() << " sets (" << trafo.size() << " transformations).");
	assert(mSets.size() == 1);
	assert(checkConsistency());
	for(std::size_t i = 0; i < mSets.size(); ++i) {
		res.setSetDirect(boost::apply_visitor(genericAffineTransformationVisitor<repVariant, Number>(trafo.matrix(), trafo.vector()), mSets.at(i)), i);
	}
	return res;
}


template<typename Number, typename Representation, typename ...Rargs>
State<Number,Representation,Rargs...> State<Number,Representation,Rargs...>::partiallyApplyTransformation(const std::vector<ConstraintSet<Number>>& trafos, const std::vector<std::size_t>& sets ) const {
	State<Number,Representation,Rargs...> res(*this);
	assert(trafos.size() == sets.size());
	assert(checkConsistency());
	for(std::size_t i = 0; i < sets.size(); ++i) {
		assert(sets.at(i) < mSets.size());
		res.setSetDirect(boost::apply_visitor(genericAffineTransformationVisitor<repVariant, Number>(trafos.at(i).matrix(), trafos.at(i).vector()), mSets.at(sets.at(i))), sets.at(i));
	}
	return res;
}

template<typename Number, typename Representation, typename ...Rargs>
State<Number,Representation,Rargs...> State<Number,Representation,Rargs...>::partiallyApplyTransformation(const ConstraintSet<Number>& trafo, std::size_t I ) const {
	State<Number,Representation,Rargs...> res(*this);
	assert(I < mSets.size());
	assert(checkConsistency());
	res.setSetDirect(boost::apply_visitor(genericAffineTransformationVisitor<repVariant, Number>(trafo.matrix(), trafo.vector()), mSets.at(I)), I);

	return res;
}


template<typename Number, typename Representation, typename ...Rargs>
State<Number,Representation,Rargs...> State<Number,Representation,Rargs...>::minkowskiSum(const State<Number,Representation,Rargs...>& rhs) const {
	//If only one representation given: avoid boost visitor
	//if(mTypes.size() == 1){
	//	return boost::get<Representation>(mSets.at(0)).minkowskiSum(rhs);
	//}
	//For more representations: use boost visitor
	State<Number,Representation,Rargs...> res(*this);
	assert(mSets.size() == rhs.getSets().size());
	assert(checkConsistency());
	for(std::size_t i=0; i < rhs.getSets().size(); i++){
		res.setSetDirect(boost::apply_visitor(genericMinkowskiSumVisitor<repVariant>(),mSets.at(i), rhs.getSet(i)), i);
	}
	return res;
}

template<typename Number, typename Representation, typename ...Rargs>
State<Number,Representation,Rargs...> State<Number,Representation,Rargs...>::partiallyMinkowskiSum(const State<Number,Representation,Rargs...>& rhs, std::size_t I ) const {
	assert(I < mSets.size());
	assert(I < rhs.getSets().size());
	assert(checkConsistency());
	//If only one representation given: avoid boost visitor
	//if(mTypes.size() == 1){
	//	return boost::get<Representation>(mSets.at(0)).minkowskiSum(rhs);
	//}
	//For more representations avaiable: use boost visitor
	State<Number,Representation,Rargs...> res(*this);
	res.setSetDirect(boost::apply_visitor(genericMinkowskiSumVisitor<repVariant>(),mSets.at(I), rhs.getSet(I)), I);
	return res;
}

template<typename Number, typename Representation, typename ...Rargs>
std::size_t State<Number,Representation,Rargs...>::getDimension(std::size_t I) const {
	assert(I < mSets.size());
	assert(checkConsistency());
	//If only one representation given: avoid boost visitor
	//if(mTypes.size() == 1){
	//	return boost::get<Representation>(mSets.at(0)).dimension();
	//}
	//For more representations avaiable: use boost visitor
	return boost::apply_visitor(genericDimensionVisitor(), mSets.at(I));
}

template<typename Number, typename Representation, typename ...Rargs>
Number State<Number,Representation,Rargs...>::getSupremum(std::size_t I) const {
	assert(I < mSets.size());
	assert(checkConsistency());
	//If only one representation given: avoid boost visitor
	//if(mTypes.size() == 1){
	//	return boost::get<Representation>(mSets.at(0)).supremum();
	//}
	//For more representations avaiable: use boost visitor
	return boost::apply_visitor(genericSupremumVisitor<Number>(),mSets.at(I));
}

template<typename Number, typename Representation, typename ...Rargs>
void State<Number,Representation,Rargs...>::removeRedundancy(){
	//If only one representation given: avoid boost visitor
	//if(mTypes.size() == 1){
	//	return boost::get<Representation>(mSets.at(0)).removeRedundancy();
	//}
	//For more representations avaiable: use boost visitor
	assert(checkConsistency());
	State<Number,Representation,Rargs...> res(*this);
	for(std::size_t i=0; i < mSets.size(); i++){
		res.setSetDirect(boost::apply_visitor(genericReductionVisitor<repVariant,Number>(), mSets.at(i)), i);
	}
}

template<typename Number, typename Representation, typename ...Rargs>
void State<Number,Representation,Rargs...>::partiallyRemoveRedundancy(std::size_t I){
	assert(I < mSets.size());
	assert(checkConsistency());
	//If only one representation given: avoid boost visitor
	//if(mTypes.size() == 1){
	//	return boost::get<Representation>(mSets.at(0)).removeRedundancy();
	//}
	//For more representations avaiable: use boost visitor
	return boost::apply_visitor(genericReductionVisitor<repVariant,Number>(),mSets.at(I), I);
}

template<typename Number, typename Representation, typename ...Rargs>
bool State<Number,Representation,Rargs...>::checkConsistency() const {
	if(mSets.size() != mTypes.size()){
		return false;
	}
	for(std::size_t i=0; i < mSets.size(); i++){
		if(mTypes.at(i) != boost::apply_visitor(genericTypeVisitor(), mSets.at(i))){
			return false;
		}
	}
	return true;
}

template<typename Number, typename Representation, typename ...Rargs>
void State<Number,Representation,Rargs...>::setSetsSave(const std::vector<boost::variant<Representation,Rargs...>>& sets){
	assert(checkConsistency());
	std::cout << "mSets.size(): " << mSets.size() << " mTypes.size(): " << mTypes.size() << " sets.size(): " << sets.size(); 
	for(std::size_t i=0; i < sets.size(); i++){
		setSetType(boost::apply_visitor(genericTypeVisitor(), sets.at(i)), i);
	}
	mSets = sets;
}

} // hypro
