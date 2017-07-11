#include "lib/datastructures/HybridAutomaton/Reset.h"

namespace hydra {

	State Reset::applyReset(const State& inState) const {
		//TRACE("hydra.datastructures","Apply reset on " << inState);
		State res(inState);
		if(hasContinuousReset) {
			//TRACE("hydra.datastructures","Apply continuous reset");
			//TRACE("hydra.datastructures","Continuous reset matrix: " << continuousMat);
			//TRACE("hydra.datastructures","Continuous reset vector: " << continuousVec);
			res.setSet(boost::apply_visitor(genericAffineTransformationVisitor<RepresentationVariant>(continuousMat,continuousVec), inState.getSet()));
		}

		if(hasDiscreteReset){
			//TRACE("hydra.datastructures","Apply discrete reset");
			//TRACE("hydra.datastructures","Discrete reset matrix: " << discreteMat);
			//TRACE("hydra.datastructures","Discrete reset vector: " << discreteVec);
			res.setDiscreteAssignment(boost::apply_visitor(genericAffineTransformationVisitor<RepresentationVariant>(discreteMat,discreteVec), inState.getDiscreteAssignment()));
			//res.setDiscreteAssignment(inState.getDiscreteAssignment().affineTransformation(discreteMat,discreteVec));
		}
		if(hasClockReset){
			//TRACE("hydra.datastructures","Apply clock reset");
			//TRACE("hydra.datastructures","Clock reset matrix: " << clockMat);
			//TRACE("hydra.datastructures","Clock reset vector: " << clockVec);
			res.setClockAssignment(boost::apply_visitor(genericAffineTransformationVisitor<RepresentationVariant>(clockMat,clockVec), inState.getClockAssignment()));
			//res.setClockAssignment(inState.getClockAssignment().affineTransformation(clockMat,clockVec));
		}

		assert(hasContinuousReset || inState.getSet() == res.getSet());
		assert(hasDiscreteReset || inState.getDiscreteAssignment() == res.getDiscreteAssignment());
		assert(hasClockReset || inState.getClockAssignment() == res.getClockAssignment());

		return res;
	}

	State Reset::applyDiscreteReset(const State& inState) const {
		State res(inState);
		if(hasDiscreteReset){
			//TRACE("hydra.datastructures","Apply discrete reset");
			//TRACE("hydra.datastructures","Discrete reset matrix: " << discreteMat);
			//TRACE("hydra.datastructures","Discrete reset vector: " << discreteVec);
			res.setDiscreteAssignment(boost::apply_visitor(genericAffineTransformationVisitor<RepresentationVariant>(discreteMat,discreteVec), inState.getDiscreteAssignment()));
			//res.setDiscreteAssignment(inState.getDiscreteAssignment().affineTransformation(discreteMat,discreteVec));
		}
		return res;
	}

} // namespace
