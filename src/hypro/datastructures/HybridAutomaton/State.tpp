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
	assert(checkConsistency());
}


template<typename Number, typename Representation, typename ...Rargs>
void State<Number,Representation,Rargs...>::addTimeToClocks(tNumber t) {
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

template<typename Number, typename Representation, typename ...Rargs>
State<Number,Representation,Rargs...> State<Number,Representation,Rargs...>::unite(const State<Number,Representation,Rargs...>& in) const {
	State<Number,Representation,Rargs...> res(*this);

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

template<typename Number, typename Representation, typename ...Rargs>
std::pair<CONTAINMENT,State<Number,Representation,Rargs...>> State<Number,Representation,Rargs...>::satisfies(const Condition<Number>& in) const {
	//DEBUG("hypro.datastructures","this rep name: " << mSetRepresentationName << " vs " << in.getSetRepresentation());
	//assert(mSetRepresentationName == in.getSetRepresentation());

	assert(checkConsistency());

	if(in.constraints().empty()) {
		return std::make_pair(CONTAINMENT::FULL,*this);
	}

	DEBUG("hypro.datastructures","This size: " << mSets.size() << ", condition size: " << in.size());
	TRACE("hypro.datastructures","Condition matrix: " << std::endl << in.getMatrix() << std::endl << "Vector: " << std::endl << in.getVector());
	assert(in.size() == mSets.size());

	State<Number,Representation,Rargs...> res(*this);

	CONTAINMENT strictestContainment = CONTAINMENT::FULL;

	for(std::size_t i = 0; i < mSets.size(); ++i) {
		// check each substateset agains its invariant subset
		auto resultPair = boost::apply_visitor(genericSatisfiesHalfspacesVisitor<repVariant, Number>(in.getMatrix(i), in.getVector(i)), mSets.at(i));
		assert(resultPair.first != CONTAINMENT::YES); // assert that we have detailed information on the invariant intersection.

		res.setSetDirect(resultPair.second, i);

		if(resultPair.first == CONTAINMENT::NO) {
			TRACE("hypro.datastructures","State set " << i << "(type " << mTypes.at(i) << ") failed the condition - return empty.");
			strictestContainment = resultPair.first;
			break;
		} else if(resultPair.first == CONTAINMENT::PARTIAL) {
			strictestContainment = CONTAINMENT::PARTIAL;
		}
	}
	return std::make_pair(strictestContainment, res);
}

template<typename Number, typename Representation, typename ...Rargs>
std::pair<CONTAINMENT,State<Number,Representation,Rargs...>> State<Number,Representation,Rargs...>::satisfiesHalfspaces(const matrix_t<Number>& constraints, const vector_t<Number>& constants) const {
	if(constraints.rows() == 0) {
		return std::make_pair(CONTAINMENT::FULL,*this);
	}
	assert(checkConsistency());
	return partiallySatisfies(Condition<Number>(constraints,constants), 0);
}

template<typename Number, typename Representation, typename ...Rargs>
std::pair<CONTAINMENT,State<Number,Representation,Rargs...>> State<Number,Representation,Rargs...>::partiallySatisfies(const Condition<Number>& in, std::size_t I) const {
	TRACE("hypro.datastructures","Check Condition of size " << in.size() << " against set at pos " << I);
	assert(checkConsistency());


	if(in.size() == 0 || in.constraints().empty()) {
		return std::make_pair(CONTAINMENT::FULL,*this);
	}
	assert(in.size() == mSets.size());

	State<Number,Representation,Rargs...> res(*this);
	assert(res.getTimestamp() == this->getTimestamp());

	TRACE("hypro.datastructures","Invoking satisfiesHalfspaces visitor.");
	assert(mSets.size() > I);
	auto resultPair = boost::apply_visitor(genericSatisfiesHalfspacesVisitor<repVariant, Number>(in.getMatrix(I), in.getVector(I)), mSets.at(I));
	TRACE("hypro.datastructures","Done satisfiesHalfspaces visitor, attempt to set result.");
	res.setSetDirect(resultPair.second, I);

	TRACE("hypro.datastructures","Result empty: " << resultPair.first);

	return std::make_pair(resultPair.first, res);
}


template<typename Number, typename Representation, typename ...Rargs>
State<Number,Representation,Rargs...> State<Number,Representation,Rargs...>::applyTimeStep(const std::vector<std::pair<const matrix_t<Number>&, const vector_t<Number>&>>& flows, tNumber timeStepSize ) const {
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
State<Number,Representation,Rargs...> State<Number,Representation,Rargs...>::partiallyApplyTimeStep(const ConstraintSet<Number>& flow, tNumber timeStepSize, std::size_t I ) const {
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
State<Number,Representation,Rargs...> State<Number,Representation,Rargs...>::linearTransformation(const matrix_t<Number>& matrix) const {
	assert(checkConsistency());
	return partiallyApplyTransformation(ConstraintSet<Number>(matrix, vector_t<Number>::Zero(matrix.rows())), 0);
}

template<typename Number, typename Representation, typename ...Rargs>
State<Number,Representation,Rargs...> State<Number,Representation,Rargs...>::affineTransformation(const matrix_t<Number>& matrix, const vector_t<Number>& vector) const {
	assert(checkConsistency());
	return partiallyApplyTransformation(ConstraintSet<Number>(matrix, vector), 0);
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
bool State<Number,Representation,Rargs...>::contains(const State<Number,Representation,Rargs...>& rhs) const {
	assert(checkConsistency());
	assert(rhs.getNumberSets() == this->getNumberSets());
	for(std::size_t i=0; i < this->getNumberSets(); ++i){
		if(!boost::apply_visitor(genericSetContainsVisitor(), this->getSet(i), rhs.getSet(i))) {
			return false;
		}
	}
	return true;
}

template<typename Number, typename Representation, typename ...Rargs>
std::vector<Point<Number>> State<Number,Representation,Rargs...>::vertices(std::size_t I) const {
	assert(checkConsistency());
	return boost::apply_visitor(genericVerticesVisitor<Number>(), mSets.at(I));
}

template<typename Number, typename Representation, typename ...Rargs>
State<Number,Representation,Rargs...> State<Number,Representation,Rargs...>::project(const std::vector<std::size_t>& dimensions, std::size_t I) const {
	State res(*this);
	res.setSetDirect(boost::apply_visitor(genericProjectionVisitor<repVariant>(dimensions), mSets.at(I)));
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
		res.setSetDirect(boost::apply_visitor(genericRedundancyVisitor<repVariant,Number>(), mSets.at(i)), i);
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
	return boost::apply_visitor(genericRedundancyVisitor<repVariant,Number>(),mSets.at(I), I);
}

template<typename Number, typename Representation, typename ...Rargs>
void State<Number,Representation,Rargs...>::reduceRepresentation() {
	assert(checkConsistency());
	for(std::size_t i=0; i < mSets.size(); i++){
		this->setSetDirect(boost::apply_visitor(genericReductionVisitor<repVariant,Number>(), mSets.at(i)), i);
	}
}

template<typename Number, typename Representation, typename ...Rargs>
bool State<Number,Representation,Rargs...>::checkConsistency() const {
	if(mSets.size() != mTypes.size()){
		std::cout << "Inconsistent size!" << std::endl;
		return false;
	}
	for(std::size_t i=0; i < mSets.size(); i++){
		if(mTypes.at(i) != boost::apply_visitor(genericTypeVisitor(), mSets.at(i))){
			std::cout << "Types do not match (expected: " << mTypes.at(i) << ", is: " << boost::apply_visitor(genericTypeVisitor(), mSets.at(i)) << ")" << std::endl;
			return false;
		//} else {
			//std::cout << "Types matched, in mTypes: " << mTypes.at(i) << " actual type in mSets is:" << boost::apply_visitor(genericTypeVisitor(), mSets.at(i)) << std::endl;
		}

	}
	return true;
}

template<typename Number, typename Representation, typename ...Rargs>
void State<Number,Representation,Rargs...>::setSetsSave(const std::vector<boost::variant<Representation,Rargs...>>& sets){
	assert(checkConsistency());
	//std::cout << "mSets.size(): " << mSets.size() << " mTypes.size(): " << mTypes.size() << " sets.size(): " << sets.size() << std::endl;
	for(std::size_t i=0; i < sets.size(); i++){
		setSetType(boost::apply_visitor(genericTypeVisitor(), sets.at(i)), i);
	}
	mSets = sets;
	assert(checkConsistency());
}

template<typename Number, typename Representation, typename ...Rargs>
void State<Number,Representation,Rargs...>::decompose(std::vector<std::vector<size_t>> decomposition){
	if(decomposition.size() == 1 || mSets.size() != 1){
		// no decomposition/already decomposed
	}
	// initial set is a constraint set
	matrix_t<Number> constraintsOld(boost::get<hypro::ConstraintSet<Number>>(mSets.at(0)).matrix());
	vector_t<Number> constantsOld(boost::get<hypro::ConstraintSet<Number>>(mSets.at(0)).vector());
	int i = 0;
	for(auto decomp : decomposition){
		DEBUG("hypro.datastructures", "Trying to project set: \n " << mSets.at(0) << "\n to dimensions: " );
		DEBUG("hypro.datastructures", "{");
		for(auto entry : decomp){
			DEBUG("hypro.datastructures","" <<  entry << ", ");
		}
		DEBUG("hypro.datastructures", "}");

		// for each row of the constraints check if it contains an entry for one of the variables of the set
		// and add the corresponding rows to a list of indices that are later added to the result matrix
		std::vector<int> indicesToAdd;
		for(int i = 0; i < constraintsOld.rows(); i++){
			vector_t<Number> row = constraintsOld.row(i);
			bool containsVar = false;
			for(int j = 0; j < row.rows(); j++){
				if(row(j,0) != 0){
					if(std::find(decomp.begin(),decomp.end(), j) != decomp.end()){
						//set contains variable j, which is also contained in this constraint
						containsVar = true;
						break;
					}
				}
			}
			if(containsVar){
				// this row contains information for one of the variables of this decomposition
				indicesToAdd.push_back(i);
			}
		}

		// we found information for our decomposition
		if(indicesToAdd.size() > 0){
			// create a row matrix with numIndicesToAdd many rows
			matrix_t<Number> rowMat = matrix_t<Number>::Zero(indicesToAdd.size(), constraintsOld.cols());
			for(size_t index = 0; index < rowMat.rows(); index++){
				// copy over preselected rows
				rowMat.row(index) = constraintsOld.row(indicesToAdd[index]);
			}
			// create final matrix that does not contain columns not in this set
			matrix_t<Number> finMat = matrix_t<Number>::Zero(rowMat.rows(), decomp.size());
			// -1 for constant column
			for(size_t index = 0; index < finMat.cols(); index++){
				finMat.col(index) = rowMat.col(decomp[index]);
			}
			// create final constant vector
			vector_t<Number> finVec =  vector_t<Number>::Zero(indicesToAdd.size());
			for(size_t index=0; index < finVec.rows(); index++){
				finVec(index) = constantsOld(indicesToAdd[index]);
			}

			ConstraintSet<Number> res(finMat,finVec);
			DEBUG("hypro.datastructures","Final decomposed ConstraintSet: \n" << res);
			setSetDirect(hypro::Converter<Number>::toConstraintSet(res),i);
			setSetType(hypro::representation_name::constraint_set,i);
		}
		else {
			DEBUG("hypro.datastructures", "No constraints for set found.");
			ConstraintSet<Number> res = ConstraintSet<Number>();
			setSetDirect(hypro::Converter<Number>::toConstraintSet(res),i);
			setSetType(hypro::representation_name::constraint_set,i);
		}
		i++;
	}
	DEBUG("hypro.datastructures", "State after decomposition: "  << *this);
}


template<typename Number, typename Representation, typename ...Rargs>
template<typename To>
void State<Number,Representation,Rargs...>::setAndConvertType( std::size_t I ){
	assert(checkConsistency());
	assert(I < mTypes.size());

	// convert set to type
	mSets[I] = boost::apply_visitor(genericConversionVisitor<repVariant,Number,To>(To::type()), mSets[I]);
	mTypes[I] = To::type();

	assert(checkConsistency());
}

} // hypro
