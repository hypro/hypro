#include "Reset.h"

namespace hypro {

	template<typename Number>
	Reset<Number>::Reset(const matrix_t<Number>& mat, const vector_t<Number>& vec) {
		assert(mat.rows() == mat.cols());
		mResets.emplace_back(mat,vec);
	}

	template<typename Number>
	void Reset<Number>::setVector(const vector_t<Number>& in, std::size_t I) {
		while (mResets.size() < I+1) {
			mResets.push_back(ConstraintSet<Number>());
		}
		mResets[I].rVector() = in;
	}

	template<typename Number>
	void Reset<Number>::setMatrix(const matrix_t<Number>& in, std::size_t I) {
		assert(in.rows() == in.cols());
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
	bool Reset<Number>::isIdentity() const {
		for(const auto& cset : mResets) {
			if( cset.matrix() != matrix_t<Number>::Identity(cset.matrix().rows(),cset.matrix().rows())
				|| cset.vector() != vector_t<Number>::Zero(cset.vector().rows()) ) {
				return false;
			}
		}
		return true;
	}

	template<typename Number>
	Reset<Number> combine(
		const Reset<Number>& lhs, const Reset<Number>& rhs,
		const std::vector<std::string> haVar, const std::vector<std::string> lhsVar, const std::vector<std::string> rhsVar) {

		matrix_t<Number> newMat;
		vector_t<Number> newVec;

		if(lhs.size() == 0 && rhs.size() != 0) {
			//std::cout << "take rhs" << std::endl;
			newMat = combine(matrix_t<Number>(0,0), rhs.getMatrix(), haVar, lhsVar, rhsVar);
			newVec = combine(vector_t<Number>(0), rhs.getVector());
		} else if(lhs.size() != 0 && rhs.size() == 0) {
			//std::cout << "take lhs" << std::endl;
			newMat = combine(lhs.getMatrix(), matrix_t<Number>(0,0), haVar, lhsVar, rhsVar);
			newVec = combine(lhs.getVector(), vector_t<Number>(0));
		} else if(lhs.size() == 0 && rhs.size() == 0) {
			//std::cout << "both empty" << std::endl;
			return Reset<Number>();
		} else {
			assert(lhs.size() != 0);
			assert(rhs.size() != 0);
			//std::cout << "Default." << std::endl;
			//std::cout << "Combine: " << lhs.getMatrix() << " and " << rhs.getMatrix() << std::endl;
			//std::cout << "LhsVAR:";
			//for(const auto& v : lhsVar) std::cout << v << " ";
			//std::cout << std::endl;
			//std::cout << "RhsVAR:";
			//for(const auto& v : rhsVar) std::cout << v << " ";
			//std::cout << std::endl;

			// Todo: This is a corrected, yet ineffective method. Improve!
			newMat = matrix_t<Number>::Zero(haVar.size(), haVar.size());
			newVec = vector_t<Number>::Zero(haVar.size());
			std::size_t lhsIR = 0, lhsIC = 0, rhsIR = 0, rhsIC = 0;
			bool admissible = true; // flag used to denote a non-admissible flow, i.e. shared variables with different flow.
			// iterate over all rows
			for( std::size_t rowI = 0; rowI != haVar.size(); ++rowI ) {
				//std::cout << "Consider composed row " << rowI << " for var " << haVar[rowI] << std::endl;
				//std::cout << "lhsIR: " << lhsIR << std::endl;
				//std::cout << "rhsIR: " << rhsIR << std::endl;
				//std::cout << "Now left hand side." << std::endl;
				if(lhsIR < lhsVar.size() && lhsVar[lhsIR] == haVar[rowI]) {
					newVec(rowI) = lhs.getVector()(lhsIR);
					// iterate over all columns
					lhsIC = 0;
					for( std::size_t colI = 0; colI != haVar.size(); ++colI) {
						//std::cout << "Consider composed col " << colI << " for var " << haVar[colI] << std::endl;
						//std::cout << "lhsIC: " << lhsIC << std::endl;
						//std::cout << "rhsIC: " << rhsIC << std::endl;
						assert(lhsIC < lhsVar.size());
						if(lhsVar[lhsIC] == haVar[colI]) {
							//std::cout << "rowI " << rowI << ", colI " << colI << ", lhsIR " << lhsIR << ", lhsIC " << lhsIC << std::endl;
							newMat(rowI,colI) = lhs.getMatrix()(lhsIR,lhsIC);
							++lhsIC;
							if(lhsIC == lhsVar.size()) {
								break;
							}
						}
					}
					++lhsIR;
				}
				//std::cout << "lhsIR: " << lhsIR << std::endl;
				//std::cout << "intermediate result: " << newMat << std::endl;
				//std::cout << "Now right hand side." << std::endl;
				if(rhsIR < rhsVar.size() && rhsVar[rhsIR] == haVar[rowI]) {
					newVec(rowI) = rhs.getVector()(rhsIR);
					// iterate over all columns
					rhsIC = 0;
					for( std::size_t colI = 0; colI != haVar.size(); ++colI) {
						//std::cout << "Consider composed col " << colI << " for var " << haVar[colI] << std::endl;
						//std::cout << "lhsIC: " << lhsIC << std::endl;
						//std::cout << "rhsIC: " << rhsIC << std::endl;
						if(rhsVar[rhsIC] == haVar[colI]) {
							// TODO: the check is not entirely correct, since the flow can be non-admissible but set to 0 in lhs and something != 0 in rhs.
							if(newMat(rowI,colI) != 0 && rhs.getMatrix()(rhsIR,rhsIC) != newMat(rowI,colI)) {
								//std::cout << "Attention, try to set " << rowI << "," << colI << " to " << rhs.getMatrix()(rhsIR,rhsIC) << " which already is set to " << newMat(rowI,colI);
								admissible = false;
								break;
							}
							newMat(rowI,colI) = rhs.getMatrix()(rhsIR,rhsIC);
							++rhsIC;
							if(rhsIC == rhsVar.size()) {
								break;
							}
						}
					}
					++rhsIR;
				}
				//std::cout << "rhsIR: " << rhsIR << std::endl;
				if(!admissible)
					break;
			}
			assert(admissible);
			// newMat = combine(lhs.getMatrix(), rhs.getMatrix(), haVar, lhsVar, rhsVar);
			// newVec = combine(lhs.getVector(), rhs.getVector());
		}

		Reset<Number> re;
		re.setMatrix(newMat);
		re.setVector(newVec);

		return re;
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
		// select constrains i,j,k into new constraint vector
		for(auto set : decomposition){
			DEBUG("hypro.datastructures", "decompose constraint for set: {");
			for(auto entry : set){
				DEBUG("hypro.datastructures", "" <<  entry << ", ");
			}
			DEBUG("hypro.datastructures", "}");

			// for each row of the constraints check if it contains an entry for one of the variables of the set
			// and add the corresponding rows to a list of indices that are later added to a matrix
			std::vector<size_t> indicesToAdd;
			for(auto entry : set){
				indicesToAdd.push_back(entry);
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
				// add identity constraints
				ConstraintSet<Number> res = ConstraintSet<Number>();
				newCset.push_back(res);
			}
		}

		mResets = newCset;
	}
} // namespace
