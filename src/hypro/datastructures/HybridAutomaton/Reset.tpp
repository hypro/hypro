#include "Reset.h"

namespace hypro {

	template<typename Number>
	template<typename Representation>
	State<Number,Representation> Reset<Number>::applyReset(const State<Number,Representation>& inState) const {
		//TRACE("hydra.datastructures","Apply reset on " << inState);
		State<Number,Representation> res(inState);
		if(hasContinuousReset) {
			//TRACE("hydra.datastructures","Apply continuous reset");
			//TRACE("hydra.datastructures","Continuous reset matrix: " << continuousMat);
			//TRACE("hydra.datastructures","Continuous reset vector: " << continuousVec);
			res.setSet(inState.getSet().affineTransformation(continuousMat,continuousVec));
		}

		if(hasDiscreteReset){
			//TRACE("hydra.datastructures","Apply discrete reset");
			//TRACE("hydra.datastructures","Discrete reset matrix: " << discreteMat);
			//TRACE("hydra.datastructures","Discrete reset vector: " << discreteVec);
			res.setDiscreteAssignment(inState.getDiscreteAssignment().affineTransformation(discreteMat,discreteVec));
			//res.setDiscreteAssignment(inState.getDiscreteAssignment().affineTransformation(discreteMat,discreteVec));
		}
		if(hasClockReset){
			//TRACE("hydra.datastructures","Apply clock reset");
			//TRACE("hydra.datastructures","Clock reset matrix: " << clockMat);
			//TRACE("hydra.datastructures","Clock reset vector: " << clockVec);
			res.setClockAssignment(inState.getClockAssignment().affineTransformation(clockMat,clockVec));
			//res.setClockAssignment(inState.getClockAssignment().affineTransformation(clockMat,clockVec));
		}

		assert(hasContinuousReset || inState.getSet() == res.getSet());
		assert(hasDiscreteReset || inState.getDiscreteAssignment() == res.getDiscreteAssignment());
		assert(hasClockReset || inState.getClockAssignment() == res.getClockAssignment());

		return res;
	}

	template<typename Number>
	template<typename Representation>
	State<Number,Representation> Reset<Number>::applyDiscreteReset(const State<Number,Representation>& inState) const {
		State<Number,Representation> res(inState);
		if(hasDiscreteReset){
			//TRACE("hydra.datastructures","Apply discrete reset");
			//TRACE("hydra.datastructures","Discrete reset matrix: " << discreteMat);
			//TRACE("hydra.datastructures","Discrete reset vector: " << discreteVec);
			res.setDiscreteAssignment(inState.getDiscreteAssignment().affineTransformation(discreteMat,discreteVec));
			//res.setDiscreteAssignment(inState.getDiscreteAssignment().affineTransformation(discreteMat,discreteVec));
		}
		return res;
	}

} // namespace
