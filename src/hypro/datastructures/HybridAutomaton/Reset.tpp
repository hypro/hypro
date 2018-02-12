#include "Reset.h"

namespace hypro {
	template<typename Number>
	void Reset<Number>::setVector(const vector_t<Number>& in, std::size_t I) {
		while (mResets.size() < I+1) {
			mResets.push_back(ConstraintSet<Number>());
		}
		mResets[I].rVector() = in;
	}

	template<typename Number>
	void Reset<Number>::setMatrix(const matrix_t<Number>& in, std::size_t I) {
		while (mResets.size() < I+1) {
			mResets.push_back(ConstraintSet<Number>());
		}
		mResets[I].rMatrix() = in;
	}

	template<typename Number>
	template<typename Representation, typename ...Rargs>
	State<Number,Representation, Rargs...> Reset<Number>::applyReset(const State<Number,Representation,Rargs...>& inState) const {
		TRACE("hydra.datastructures","inState #sets: " << inState.getNumberSets() << " and #resets: " << this->size());
		assert(this->empty() || inState.getNumberSets() == this->size());
		if(this->empty()) {
			return inState;
		}
		return inState.applyTransformation(mResets);
	}

	template<typename Number>
	void Reset<Number>::decompose(std::vector<std::vector<size_t>> decomposition){
		if(mResets.size() != 1){
			//already decomposed/empty constraints
			return;
		}
		ConstraintSet<Number> cset = mResets.at(0);
		DEBUG("hypro.datastructures", "Constraint Set before: \n " << cset );

		matrix_t<Number> constraintsOld(cset.matrix());
		vector_t<Number> constantsOld(cset.vector());

		std::vector<ConstraintSet<Number>> newCset;
		// for each set {i,j,..., k} select each constraint that defines over {i,j,k etc.}
		for(auto set : decomposition){
			DEBUG("hypro.datastructures", "decompose constraint for set: {");
			for(auto entry : set){
				DEBUG("hypro.datastructures", "" <<  entry << ", ");
			}
			DEBUG("hypro.datastructures", "}");

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
				DEBUG("hypro.datastructures", "Final decomposed ConstraintSet: \n" << res); 
				newCset.push_back(res);
			}
			else {
				DEBUG("hypro.datastructures", "No constraints for set found.");
				ConstraintSet<Number> res = ConstraintSet<Number>();
				newCset.push_back(res);
			}
		}

		mResets = newCset;
	}
} // namespace
