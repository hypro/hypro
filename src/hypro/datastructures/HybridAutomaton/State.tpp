#include "State.h"

namespace hypro
{

template<typename Number, typename tNumber, typename Representation, typename ...Rargs>
const boost::variant<Representation,Rargs...>& State<Number,tNumber,Representation,Rargs...>::getSet(std::size_t i) const {
	DEBUG("hypro.datastructures","Attempt to get set at pos " << i << ", mSets.size() = " << mSets.size() << ", mTypes.size() = " << mTypes.size());
	assert(mTypes.size() == mSets.size());
	assert(i < mSets.size());
	assert(checkConsistency());
	return mSets.at(i);
}

template<typename Number, typename tNumber, typename Representation, typename ...Rargs>
boost::variant<Representation,Rargs...>& State<Number,tNumber,Representation,Rargs...>::rGetSet(std::size_t i) {
	DEBUG("hypro.datastructures","Attempt to get set reference at pos " << i << ", mSets.size() = " << mSets.size());
	assert(mTypes.size() == mSets.size());
	assert(checkConsistency());
	return mSets.at(i);
}

template<typename Number, typename tNumber, typename Representation, typename ...Rargs>
template<typename R>
void State<Number,tNumber,Representation,Rargs...>::setSet(const R& s, std::size_t i) {
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
	assert(checkConsistency());
}


template<typename Number, typename tNumber, typename Representation, typename ...Rargs>
void State<Number,tNumber,Representation,Rargs...>::addTimeToClocks(tNumber t) {
	TRACE("hypro.datastructures","Add timestep of size " << t << " to clocks.");
	//if(mHasClocks) {
	//	matrix_t<Number> identity = matrix_t<Number>::Identity(mClockAssignment.dimension(), mClockAssignment.dimension());
	//	vector_t<Number> clockShift = vector_t<Number>::Ones(mClockAssignment.dimension());
	//	clockShift = clockShift * t;
	//	mClockAssignment = mClockAssignment.affineTransformation(identity,clockShift);
	//}
	assert(checkConsistency());
	mTimestamp += t;
}

template<typename Number, typename tNumber, typename Representation, typename ...Rargs>
State<Number,tNumber,Representation,Rargs...> State<Number,tNumber,Representation,Rargs...>::unite(const State<Number,tNumber,Representation,Rargs...>& in) const {
	State<Number,tNumber,Representation,Rargs...> res(*this);

	TRACE("hypro.datastructures","Union with " << mSets.size() << " sets.");

	// element-wise union.
	assert(mSets.size() == in.getSets().size());
	assert(checkConsistency());
	for(std::size_t i = 0; i < mSets.size(); ++i) {
		TRACE("hypro.datastructures","Apply unite vistor for set " << i);
		res.setSetDirect( boost::apply_visitor(genericUniteVisitor<repVariant>(), mSets.at(i), in.getSet(i)), i);
	}

	TRACE("hypro.datastructures","Done union.");

	res.setTimestamp(mTimestamp.convexHull(in.getTimestamp()));
	return res;
}

template<typename Number, typename tNumber, typename Representation, typename ...Rargs>
std::pair<CONTAINMENT,State<Number,tNumber,Representation,Rargs...>> State<Number,tNumber,Representation,Rargs...>::satisfies(const Condition<Number>& in) const {
	//DEBUG("hypro.datastructures","this rep name: " << mSetRepresentationName << " vs " << in.getSetRepresentation());
	//assert(mSetRepresentationName == in.getSetRepresentation());

	assert(checkConsistency());

	if(in.constraints().empty()) {
		return std::make_pair(CONTAINMENT::FULL,*this);
	}

	DEBUG("hypro.datastructures","This size: " << mSets.size() << ", condition size: " << in.size());
	TRACE("hypro.datastructures","Condition matrix: " << std::endl << in.getMatrix() << std::endl << "Vector: " << std::endl << in.getVector());
	assert(in.size() == mSets.size());

	State<Number,tNumber,Representation,Rargs...> res(*this);

	CONTAINMENT strictestContainment = CONTAINMENT::FULL;

	for(std::size_t i = 0; i < mSets.size(); ++i) {
		auto resultPair = boost::apply_visitor(genericSatisfiesHalfspacesVisitor<repVariant, Number>(in.getMatrix(), in.getVector()), mSets.at(i));
		assert(resultPair.first != CONTAINMENT::YES); // assert that we have detailed information on the invariant intersection.

		res.setSetDirect(resultPair.second, i);

		if(!resultPair.first) {
			TRACE("hypro.datastructures","State set " << i << "(type " << mTypes.at(i) << ") failed the condition - return empty.");
			strictestContainment = resultPair.first;
			break;
		} else if(resultPair.first == CONTAINMENT::PARTIAL) {
			strictestContainment = CONTAINMENT::PARTIAL;
		}
	}
	return std::make_pair(strictestContainment, res);
}

template<typename Number, typename tNumber, typename Representation, typename ...Rargs>
std::pair<CONTAINMENT,State<Number,tNumber,Representation,Rargs...>> State<Number,tNumber,Representation,Rargs...>::satisfiesHalfspaces(const matrix_t<Number>& constraints, const vector_t<Number>& constants) const {
	if(constraints.rows() == 0) {
		return std::make_pair(CONTAINMENT::FULL,*this);
	}
	assert(checkConsistency());
	return partiallySatisfies(Condition<Number>(constraints,constants), 0);
}

template<typename Number, typename tNumber, typename Representation, typename ...Rargs>
std::pair<CONTAINMENT,State<Number,tNumber,Representation,Rargs...>> State<Number,tNumber,Representation,Rargs...>::partiallySatisfies(const Condition<Number>& in, std::size_t I) const {
	TRACE("hypro.datastructures","Check Condition of size " << in.size() << " against set at pos " << I);
	assert(checkConsistency());

	if(in.size() == 0 || in.constraints().empty()) {
		return std::make_pair(CONTAINMENT::FULL,*this);
	}
	assert(in.size() == mSets.size());

	State<Number,tNumber,Representation,Rargs...> res(*this);
	assert(res.getTimestamp() == this->getTimestamp());

	auto resultPair = boost::apply_visitor(genericSatisfiesHalfspacesVisitor<repVariant, Number>(in.getMatrix(), in.getVector()), mSets.at(I));
	res.setSetDirect(resultPair.second, I);

	TRACE("hypro.datastructures","Result empty: " << resultPair.first);

	return std::make_pair(resultPair.first, res);
}


template<typename Number, typename tNumber, typename Representation, typename ...Rargs>
State<Number,tNumber,Representation,Rargs...> State<Number,tNumber,Representation,Rargs...>::applyTimeStep(const std::vector<std::pair<const matrix_t<Number>&, const vector_t<Number>&>>& flows, tNumber timeStepSize ) const {
	State<Number,tNumber,Representation,Rargs...> res(*this);
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

template<typename Number, typename tNumber, typename Representation, typename ...Rargs>
State<Number,tNumber,Representation,Rargs...> State<Number,tNumber,Representation,Rargs...>::partiallyApplyTimeStep(const ConstraintSet<Number>& flow, tNumber timeStepSize, std::size_t I ) const {
	State<Number,tNumber,Representation,Rargs...> res(*this);
	assert(I < mSets.size());
	assert(checkConsistency());
	res.setSetDirect(boost::apply_visitor(genericAffineTransformationVisitor<repVariant, Number>(flow.matrix(), flow.vector()), mSets.at(I)), I);

	res.addTimeToClocks(timeStepSize);
	return res;
}

template<typename Number, typename tNumber, typename Representation, typename ...Rargs>
State<Number,tNumber,Representation,Rargs...> State<Number,tNumber,Representation,Rargs...>::applyTransformation(const std::vector<ConstraintSet<Number>>& trafos ) const {
	State<Number,tNumber,Representation,Rargs...> res(*this);
	TRACE("hypro.datastructures","Apply transformation of " << mSets.size() << " sets (" << trafos.size() << " transformations).");
	assert(trafos.size() == mSets.size());
	assert(checkConsistency());
	for(std::size_t i = 0; i < mSets.size(); ++i) {
		res.setSetDirect(boost::apply_visitor(genericAffineTransformationVisitor<repVariant, Number>(trafos.at(i).matrix(), trafos.at(i).vector()), mSets.at(i)), i);
	}
	return res;
}

template<typename Number, typename tNumber, typename Representation, typename ...Rargs>
State<Number,tNumber,Representation,Rargs...> State<Number,tNumber,Representation,Rargs...>::applyTransformation(const ConstraintSet<Number>& trafo ) const {
	State<Number,tNumber,Representation,Rargs...> res(*this);
	TRACE("hypro.datastructures","Apply transformation of " << mSets.size() << " sets (" << trafo.size() << " transformations).");
	assert(mSets.size() == 1);
	assert(checkConsistency());
	for(std::size_t i = 0; i < mSets.size(); ++i) {
		res.setSetDirect(boost::apply_visitor(genericAffineTransformationVisitor<repVariant, Number>(trafo.matrix(), trafo.vector()), mSets.at(i)), i);
	}
	return res;
}

template<typename Number, typename tNumber, typename Representation, typename ...Rargs>
State<Number,tNumber,Representation,Rargs...> State<Number,tNumber,Representation,Rargs...>::linearTransformation(const matrix_t<Number>& matrix) const {
	assert(checkConsistency());
	return partiallyApplyTransformation(ConstraintSet<Number>(matrix, vector_t<Number>::Zero(matrix.rows())), 0);
}

template<typename Number, typename tNumber, typename Representation, typename ...Rargs>
State<Number,tNumber,Representation,Rargs...> State<Number,tNumber,Representation,Rargs...>::affineTransformation(const matrix_t<Number>& matrix, const vector_t<Number>& vector) const {
	assert(checkConsistency());
	return partiallyApplyTransformation(ConstraintSet<Number>(matrix, vector), 0);
}


template<typename Number, typename tNumber, typename Representation, typename ...Rargs>
State<Number,tNumber,Representation,Rargs...> State<Number,tNumber,Representation,Rargs...>::partiallyApplyTransformation(const std::vector<ConstraintSet<Number>>& trafos, const std::vector<std::size_t>& sets ) const {
	State<Number,tNumber,Representation,Rargs...> res(*this);
	assert(trafos.size() == sets.size());
	assert(checkConsistency());
	for(std::size_t i = 0; i < sets.size(); ++i) {
		assert(sets.at(i) < mSets.size());
		res.setSetDirect(boost::apply_visitor(genericAffineTransformationVisitor<repVariant, Number>(trafos.at(i).matrix(), trafos.at(i).vector()), mSets.at(sets.at(i))), sets.at(i));
	}
	return res;
}

template<typename Number, typename tNumber, typename Representation, typename ...Rargs>
State<Number,tNumber,Representation,Rargs...> State<Number,tNumber,Representation,Rargs...>::partiallyApplyTransformation(const ConstraintSet<Number>& trafo, std::size_t I ) const {
	State<Number,tNumber,Representation,Rargs...> res(*this);
	assert(I < mSets.size());
	assert(checkConsistency());
	res.setSetDirect(boost::apply_visitor(genericAffineTransformationVisitor<repVariant, Number>(trafo.matrix(), trafo.vector()), mSets.at(I)), I);

	return res;
}


template<typename Number, typename tNumber, typename Representation, typename ...Rargs>
State<Number,tNumber,Representation,Rargs...> State<Number,tNumber,Representation,Rargs...>::minkowskiSum(const State<Number,tNumber,Representation,Rargs...>& rhs) const {
	//If only one representation given: avoid boost visitor
	//if(mTypes.size() == 1){
	//	return boost::get<Representation>(mSets.at(0)).minkowskiSum(rhs);
	//}
	//For more representations: use boost visitor
	State<Number,tNumber,Representation,Rargs...> res(*this);
	assert(mSets.size() == rhs.getSets().size());
	assert(checkConsistency());
	for(std::size_t i=0; i < rhs.getSets().size(); i++){
		res.setSetDirect(boost::apply_visitor(genericMinkowskiSumVisitor<repVariant>(),mSets.at(i), rhs.getSet(i)), i);
	}
	return res;
}

template<typename Number, typename tNumber, typename Representation, typename ...Rargs>
State<Number,tNumber,Representation,Rargs...> State<Number,tNumber,Representation,Rargs...>::partiallyMinkowskiSum(const State<Number,tNumber,Representation,Rargs...>& rhs, std::size_t I ) const {
	assert(I < mSets.size());
	assert(I < rhs.getSets().size());
	assert(checkConsistency());
	//If only one representation given: avoid boost visitor
	//if(mTypes.size() == 1){
	//	return boost::get<Representation>(mSets.at(0)).minkowskiSum(rhs);
	//}
	//For more representations avaiable: use boost visitor
	State<Number,tNumber,Representation,Rargs...> res(*this);
	res.setSetDirect(boost::apply_visitor(genericMinkowskiSumVisitor<repVariant>(),mSets.at(I), rhs.getSet(I)), I);
	return res;
}

template<typename Number, typename tNumber, typename Representation, typename ...Rargs>
bool State<Number,tNumber,Representation,Rargs...>::contains(const State<Number,tNumber,Representation,Rargs...>& rhs) const {
	assert(checkConsistency());
	assert(rhs.getNumberSets() == this->getNumberSets());
	for(std::size_t i=0; i < this->getNumberSets(); ++i){
		auto tmp = boost::apply_visitor(hypro::genericConversionVisitor<boost::variant<Representation,Rargs...>, Number>(mTypes.at(i)), rhs.getSet(i));
		if(!boost::apply_visitor(genericSetContainsVisitor(), this->getSet(i), tmp)) {
			return false;
		}
	}
	return true;
}

template<typename Number, typename tNumber, typename Representation, typename ...Rargs>
std::vector<Point<Number>> State<Number,tNumber,Representation,Rargs...>::vertices(std::size_t I) const {
	assert(checkConsistency());
	return boost::apply_visitor(genericVerticesVisitor<Number>(), mSets.at(I));
}

template<typename Number, typename tNumber, typename Representation, typename ...Rargs>
State<Number,tNumber,Representation,Rargs...> State<Number,tNumber,Representation,Rargs...>::project(const std::vector<std::size_t>& dimensions, std::size_t I) const {
	State res(*this);
	res.setSetDirect(boost::apply_visitor(genericProjectionVisitor<repVariant>(dimensions), mSets.at(I)));
	return res;
}

template<typename Number, typename tNumber, typename Representation, typename ...Rargs>
std::size_t State<Number,tNumber,Representation,Rargs...>::getDimension(std::size_t I) const {
	assert(I < mSets.size());
	assert(checkConsistency());
	//If only one representation given: avoid boost visitor
	//if(mTypes.size() == 1){
	//	return boost::get<Representation>(mSets.at(0)).dimension();
	//}
	//For more representations avaiable: use boost visitor
	return boost::apply_visitor(genericDimensionVisitor(), mSets.at(I));
}

template<typename Number, typename tNumber, typename Representation, typename ...Rargs>
Number State<Number,tNumber,Representation,Rargs...>::getSupremum(std::size_t I) const {
	assert(I < mSets.size());
	assert(checkConsistency());
	//If only one representation given: avoid boost visitor
	//if(mTypes.size() == 1){
	//	return boost::get<Representation>(mSets.at(0)).supremum();
	//}
	//For more representations avaiable: use boost visitor
	return boost::apply_visitor(genericSupremumVisitor<Number>(),mSets.at(I));
}

template<typename Number, typename tNumber, typename Representation, typename ...Rargs>
void State<Number,tNumber,Representation,Rargs...>::removeRedundancy(){
	//If only one representation given: avoid boost visitor
	//if(mTypes.size() == 1){
	//	return boost::get<Representation>(mSets.at(0)).removeRedundancy();
	//}
	//For more representations avaiable: use boost visitor
	assert(checkConsistency());
	State<Number,tNumber,Representation,Rargs...> res(*this);
	for(std::size_t i=0; i < mSets.size(); i++){
		res.setSetDirect(boost::apply_visitor(genericReductionVisitor<repVariant,Number>(), mSets.at(i)), i);
	}
}

template<typename Number, typename tNumber, typename Representation, typename ...Rargs>
void State<Number,tNumber,Representation,Rargs...>::partiallyRemoveRedundancy(std::size_t I){
	assert(I < mSets.size());
	assert(checkConsistency());
	//If only one representation given: avoid boost visitor
	//if(mTypes.size() == 1){
	//	return boost::get<Representation>(mSets.at(0)).removeRedundancy();
	//}
	//For more representations avaiable: use boost visitor
	return boost::apply_visitor(genericReductionVisitor<repVariant,Number>(),mSets.at(I), I);
}

template<typename Number, typename tNumber, typename Representation, typename ...Rargs>
bool State<Number,tNumber,Representation,Rargs...>::checkConsistency() const {
	if(mSets.size() != mTypes.size()){
		std::cout << "Inconsistent size!" << std::endl;
		return false;
	}
	for(std::size_t i=0; i < mSets.size(); i++){
		if(mTypes.at(i) != boost::apply_visitor(genericTypeVisitor(), mSets.at(i))){
			std::cout << "Types do not match (expected: " << mTypes.at(i) << ", is: " << boost::apply_visitor(genericTypeVisitor(), mSets.at(i)) << ")" << std::endl;
			return false;
		}
	}
	return true;
}

template<typename Number, typename tNumber, typename Representation, typename ...Rargs>
void State<Number,tNumber,Representation,Rargs...>::setSetsSave(const std::vector<boost::variant<Representation,Rargs...>>& sets){
	assert(checkConsistency());
	//std::cout << "mSets.size(): " << mSets.size() << " mTypes.size(): " << mTypes.size() << " sets.size(): " << sets.size() << std::endl;
	for(std::size_t i=0; i < sets.size(); i++){
		setSetType(boost::apply_visitor(genericTypeVisitor(), sets.at(i)), i);
	}
	mSets = sets;
	assert(checkConsistency());
}

template<typename Number, typename tNumber, typename Representation, typename ...Rargs>
void State<Number,tNumber,Representation,Rargs...>::setAndConvertType( representation_name to, std::size_t I ){
	assert(checkConsistency());
	assert(I < mTypes.size());
	// skip, if type is already correct.
	if(mTypes[I] == to) return;

	// convert set to type
	mSets[I] = boost::apply_visitor(genericConversionVisitor<repVariant,Number>(to), mSets[I]);
	mTypes[I] = to;

	assert(checkConsistency());
}

} // hypro
