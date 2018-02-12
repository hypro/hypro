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

template<typename Number>
std::string Condition<Number>::getDotRepresentation(const std::vector<std::string>& vars) const {
	std::stringstream o;
	if(mConstraints.size() > 0) {
		const matrix_t<Number>& constraints = mConstraints.begin()->matrix();
		o << "<TR><TD ROWSPAN=\"" << constraints.rows() << "\">";
		for(unsigned i = 0; i < constraints.rows(); ++i) {
			for(unsigned j = 0; j < constraints.cols(); ++j) {
				if(constraints(i,j) != 0) {
					o << constraints(i,j) << "*" << vars[j] << " + ";
				}
			}
			o << " &lt;= " << mConstraints.begin()->vector()(i);
			if(i < constraints.rows() -1)
				o << "<BR/>";
		}
		o << "</TD>";
		o << "</TR>";
	}
	return o.str();
}

template<typename Number>
Condition<Number> combine(
	const Condition<Number>& lhs, const Condition<Number>& rhs,
	const std::vector<std::string> haVar, const std::vector<std::string> lhsVar, const std::vector<std::string> rhsVar) {

	if (lhs.size() == 0 and rhs.size() == 0) {
		return Condition<Number>();
	}

	matrix_t<Number> lhsMatrix = matrix_t<Number>::Zero(0, lhsVar.size());
	matrix_t<Number> rhsMatrix = matrix_t<Number>::Zero(0, rhsVar.size());;
	vector_t<Number> lhsVector = vector_t<Number>::Zero(0);
	vector_t<Number> rhsVector = vector_t<Number>::Zero(0);;

	if (lhs.size() != 0) {
		lhsMatrix = lhs.getMatrix();
		lhsVector = lhs.getVector();
	}
	if (rhs.size() != 0) {
		rhsMatrix = rhs.getMatrix();
		rhsVector = rhs.getVector();
	}

	matrix_t<Number> newMat = combine(lhsMatrix, rhsMatrix, haVar, lhsVar, rhsVar);
	vector_t<Number> newVec = combine(lhsVector, rhsVector);

	/*vector_t<Number>::Zero(lhsInv.getVector().size()+rhsInv.getVector().size());
	newVec.head(lhsInv.getVector().size()) = lhsInv.getVector();
	newVec.tail(rhsInv.getVector().size()) = rhsInv.getVector();*/

	return Condition<Number>(newMat, newVec);
}

void Condition<Number>::decompose(std::vector<std::vector<size_t>> decomposition){
	if(mConstraints.size() != 1){
		//already decomposed/empty constraints
		return;
	}
	ConstraintSet<Number> cset = mConstraints.at(0);
	DEBUG("hypro.datastructures", "Constraint Set before: \n " << cset );

	matrix_t<Number> constraintsOld(cset.matrix());
	vector_t<Number> constantsOld(cset.vector());

	std::vector<ConstraintSet<Number>> newCset;
	// for each set {i,j,..., k} select each constraint that defines over {i,j,k etc.}
	for(auto set : decomposition){
		DEBUG("hypro.datastructures", "decompose constraint for set: {");
		for(auto entry : set){
			DEBUG("hypro.datastructures", ""<<  entry << ", ");
		}
		DEBUG("hypro.datastructures","}");

		// for each row of the constraints check if it contains an entry for one of the variables of the set
		// and add the corresponding rows to a list of indices that are later added to a matrix
		std::vector<int> indicesToAdd;
		for(int i = 0; i < constraintsOld.rows(); i++){
			vector_t<Number> row = constraintsOld.row(i);
			bool containsVar = false;
			for(int j = 0; j < row.rows(); j++){
				if(row(j,0) != 0){
					if(std::find(set.begin(),set.end(), j) != set.end()){
						//set contains variable j, which is also contained in this constraint
						containsVar = true;
					}
				}
			}
			if(containsVar){
				indicesToAdd.push_back(i);
			}
		}

		if(indicesToAdd.size() > 0){
			// create a row matrix with numIndicesToAdd many rows
			matrix_t<Number> rowMat = matrix_t<Number>::Zero(indicesToAdd.size(), constraintsOld.cols());
			for(size_t index = 0; index < rowMat.rows(); index++){
				// copy over preselected rows
				rowMat.row(index) = constraintsOld.row(indicesToAdd[index]);
			}
			// create final matrix that does not contain columns not in this set
			matrix_t<Number> finMat = matrix_t<Number>::Zero(rowMat.rows(), set.size());
			// -1 for constant column
			for(size_t index = 0; index < finMat.cols(); index++){
				finMat.col(index) = rowMat.col(set[index]);
			}
			// create final constant vector
			vector_t<Number> finVec =  vector_t<Number>::Zero(indicesToAdd.size());
			for(size_t index=0; index < finVec.rows(); index++){
				finVec(index) = constantsOld(indicesToAdd[index]);
			}

			ConstraintSet<Number> res(finMat,finVec);
			DEBUG("hypro.datastructures","Final decomposed ConstraintSet: \n" << res); 
			newCset.push_back(res);
		}
		else {
			DEBUG("hypro.datastructures", "No constraints for set found.");
			ConstraintSet<Number> res = ConstraintSet<Number>();
			newCset.push_back(res);
		}
	}

	mConstraints = newCset;
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
