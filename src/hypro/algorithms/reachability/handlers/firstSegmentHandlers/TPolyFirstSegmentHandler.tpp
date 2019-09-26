#pragma once 

#include "TPolyFirstSegmentHandler.h"

namespace hypro {

	template<typename State>
    vector_t<typename State::NumberType> TPolyFirstSegmentHandler<State>::gradientOfLinearFct(const vector_t<Number>& linearFct){
        assert(linearFct.rows() == mState->getDimension() + 1);
        vector_t<Number> gradient = linearFct;
        gradient(gradient.rows()-1) = 0;
        return gradient;
    }

    template<typename State>
    vector_t<typename State::NumberType> TPolyFirstSegmentHandler<State>::lieDerivative(const vector_t<Number>& dir){
        return mState->getLocation()->getLinearFlow().getFlowMatrix().transpose() * gradientOfLinearFct(dir);
    }

    //template<typename State>
    //vector_t<Number> TPolyFirstSegmentHandler<State>::lieDerivativeNthPower(const vector_t<Number>& dir, const unsigned power){
    //    auto flow = mState->getLocation()->getLinearFlow();
    //    vector_t<Number> deriv = dir;
    //    for(unsigned counter = 0; counter < power; ++counter){
    //    	deriv = flow.transpose() * gradientOfLinearFct(deriv);
    //    }
    //    return deriv;
    //}

	template<typename State>
	void TPolyFirstSegmentHandler<State>::handle(){

		//TODO: for each set in mState
		std::cout << "TPolyFirstSegmentHandler::handle, start" << std::endl;
		assert(mState->getSetType() == representation_name::polytope_t);
        auto tpoly = boost::apply_visitor(genericConvertAndGetVisitor<TemplatePolyhedron<typename State::NumberType>>(), mState->getSet());
        vector_t<Number> newVec(tpoly.vector().rows());
		
		//For each row:
		for(int rowI = 0; rowI < tpoly.matrix().rows(); ++rowI){

			//Compute Lie derivative to power of m from initial.matrix().row(i)
            Number factorial = 1;
            vector_t<Number> derivative = tpoly.matrix().row(rowI); 
			std::vector<Number> polynomCoeffs; //Ordering is from lowest to highest degree
            EvaluationResult<Number> evalRes;
			
			//For first m coefficients in polynom:
			for(int coeffI = 0; (unsigned)coeffI < TemplatePolyhedron<Number>::Settings::DERIVATIVE_ORDER; ++coeffI){ 

				//Special case: first index does not use lie derivative
				if(coeffI != 0){
					factorial *= coeffI;
					derivative = lieDerivative(derivative);	
				}
				
				//if index < m+1: Solve LP over tpoly to evaluate into derivative direction
				//if index == m+1: Solve LP over TPoly(matrix(),invariants) to evaluate into derivative direction (remainder term only bounded by invariants)
                if((unsigned)coeffI < TemplatePolyhedron<Number>::Settings::DERIVATIVE_ORDER - 1){
                	evalRes = tpoly.evaluate(derivative / factorial, true);
                } else {
                	TemplatePolyhedron<Number> invTPoly(mState->getLocation()->getInvariant().getMatrix(), mState->getLocation()->getInvariant().getVector());
                	evalRes = invTPoly.evaluate(derivative / factorial, true);
                }

                //Save resulting value as coeff in polynomCoeffs
                if(evalRes.errorCode == SOLUTION::FEAS){
                	polynomCoeffs.emplace_back(evalRes.supportValue);
                } else {
                	std::cout << "TPolyFirstSegmentHandler::handle, What did just happen?? It seems like initial set is not closed or unfeasible." << std::endl;
                }

            }

            //Compute derivative of polynom
            carl::Variable var = carl::freshRealVariable("x");
			carl::UnivariatePolynomial<Number> polynom(var, polynomCoeffs);
			carl::UnivariatePolynomial<Number> polynomDeriv = carl::derivative(polynom);

			//Optimization: Compute Cauchy bound and check if roots lie within [0,delta] to avoid root computation when computing maximum value
			//auto boundNumber = carl::cauchyBound(polynomDeriv);
			//If (-(boundNumber + 1) > 0) || boundNumber + 1 < mTimeStep)

            //Get maximum value of polynom in time interval [0,delta] save in new coeff vec
            //std::vector<carl::RealAlgebraicNumber<tNumber>> roots = carl::rootfinder::realRoots(polynomDeriv, carl::Interval<tNumber>(0,mTimeStep));
            //std::vector<carl::RealAlgebraicNumber<Number>> roots = carl::rootfinder::realRoots<Number,Number>(polynomDeriv, carl::Interval<Number>(Number(0),carl::convert<tNumber,Number>(mTimeStep)));
            ////auto roots = carl::rootfinder::realRoots<Number,Number>(polynomDeriv, carl::Interval<Number>(Number(0),carl::convert<tNumber,Number>(mTimeStep)));
            Number max(-100000);
            //for(const carl::RealAlgebraicNumber<Number>& root : roots){
            //	//if(0 <= root.value() && root.value() <= mTimeStep){
            //	if(0 <= root.value() && root.value() <= carl::convert<tNumber,Number>(mTimeStep)){
            //		Number valueAtRoot = polynom.evaluate(carl::convert<tNumber,Number>(root.value()));
            //		if(valueAtRoot > max){
            //			max = valueAtRoot;
            //		}
            //	}
            //}

            //Get value for 0 and for mTimeStep and then somehow compute firstSegment
            if(polynom.evaluate(0) > max){
            	max = polynom.evaluate(0);
            }
            if(polynom.evaluate(carl::convert<tNumber,Number>(mTimeStep)) > max){
            	max = polynom.evaluate(carl::convert<tNumber,Number>(mTimeStep));
            }

            //Set value in coeff vec
            newVec(rowI) = max;

		}
        
        //Set mComputationState vector to the new coeff vec
		tpoly.setVector(newVec);
		mState->setSet(boost::apply_visitor(genericInternalConversionVisitor<typename State::repVariant, TemplatePolyhedron<Number>>(tpoly), mState->getSet(mIndex)),mIndex);
	}

}

