#include "Location.h"

namespace hypro
{

template<typename Number>
Location<Number>::Location(unsigned _id) : mFlows(), mExternalInput(), mTransitions(), mInvariant(), mId(_id)
{}

template<typename Number>
Location<Number>::Location(unsigned _id, const Location<Number>& _loc)
    : mFlows(_loc.getFlows()), mExternalInput(_loc.getExternalInput()), mTransitions(_loc.getTransitions()), mInvariant(_loc.getInvariant()), mId(_id)
{
}

template<typename Number>
Location<Number>::Location(unsigned _id, const matrix_t<Number>& _mat) : mFlows(), mId(_id)
{
	mFlows.push_back(_mat);
}

template<typename Number>
Location<Number>::Location(unsigned _id, const matrix_t<Number>& _mat, const typename Location<Number>::transitionSet& _trans, const Condition<Number>& _inv)
    : mFlows(), mExternalInput(), mTransitions(_trans), mInvariant(_inv), mId(_id)
{
	mFlows.push_back(_mat);
}

template<typename Number>
Location<Number>::Location(unsigned _id, const matrix_t<Number>& _mat, const typename Location<Number>::transitionSet& _trans, const Condition<Number>& _inv,
                   const matrix_t<Number>& _extInputMat)
    : mFlows(), mExternalInput(_extInputMat), mTransitions(_trans), mInvariant(_inv), mId(_id)
{
	mFlows.push_back(_mat);
}

template<typename Number>
void Location<Number>::setFlow(const matrix_t<Number>& mat, std::size_t I) {
	while(I < mFlows.size()) {
		mFlows.push_back(matrix_t<Number>::Identity(mat.rows(),mat.cols()));
	}
	mFlows.push_back(mat);
}

template<typename Number>
void Location<Number>::decompose(std::vector<std::vector<size_t>> decomposition){
	if(mFlows.size() > 1 || mInvariant.size() > 1){
		//already decomposed
		return;
	}
	DEBUG("hypro.datastructures","Flow Matrix before: \n " << mFlows.at(0));
	// decompose flow
	matrix_t<Number> oldFlow(mFlows.at(0));
	std::vector<matrix_t<Number>> newFlows;
	// for each set {i,j,..., k} select the i-th,j-th,...,k-th vector into a new square matrix
	for(auto set : decomposition){
		DEBUG("hypro.datastructures","decompose flow for set: {");
		for(auto entry : set){
			DEBUG("hypro.datastructures", "" << entry << ", ");
		}
		DEBUG("hypro.datastructures","}");
		// +1 row for last-row of affine transformation
		matrix_t<Number> rowMat = matrix_t<Number>::Zero(set.size()+1, oldFlow.cols());
		// -1 because of last-row
		for(size_t index = 0; index < rowMat.rows()-1; index++){
			// select the specific rows into rowMat
			rowMat.row(index) = oldFlow.row(set[index]);
		}
		//copy last row over
		rowMat.row(rowMat.rows()-1) = oldFlow.row(oldFlow.rows()-1);

		// +1 for constant column
		matrix_t<Number> finMat = matrix_t<Number>::Zero(rowMat.rows(), set.size()+1);
		// -1 for constant column
		for(size_t index = 0; index < finMat.cols()-1; index++){
			finMat.col(index) = rowMat.col(set[index]);
		}
		finMat.col(finMat.cols()-1) = rowMat.col(rowMat.cols()-1);
		DEBUG("hypro.datastructures", "Final decomposed Flow: \n" << finMat ); 
		newFlows.push_back(finMat);
	}

	mFlows = newFlows;
	// decompose invariant
	mInvariant.decompose(decomposition);
}

}  // namespace hydra
