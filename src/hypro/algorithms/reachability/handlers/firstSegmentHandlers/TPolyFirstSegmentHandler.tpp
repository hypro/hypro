#pragma once 

#include "TPolyFirstSegmentHandler.h"

namespace hypro {

/*
	template<typename State>
    vector_t<typename State::NumberType> TPolyFirstSegmentHandler<State>::gradientOfLinearFct(const vector_t<Number>& linearFct){
        assert(linearFct.rows() == this->mState->getDimension());
        return linearFct;
        //assert(linearFct.rows() == this->mState->getDimension() + 1);
        //vector_t<Number> gradient = linearFct;
        //gradient(gradient.rows()-1) = 0;
        //return gradient;
    }
*/
    template<typename State>
    vector_t<typename State::NumberType> TPolyFirstSegmentHandler<State>::lieDerivative(const vector_t<Number>& dir){
        assert(dir.rows() == this->getTrafo().transpose().rows());
        assert(this->getTrafo().transpose().rows() == this->getTrafo().transpose().cols());
        //matrix_t<Number> trafoMat

        //TODO: Does our dir need to be of size dimension or dimension+1?

        //return this->getTrafo().transpose() * dir; // only possible since gradient of dir is dir in vector notation
        //return this->getTrafo().transpose() * gradientOfLinearFct(dir);
        //assert(dir.rows() == this->mState->getLocation()->getLinearFlow().getFlowMatrix().transpose().rows());
        //assert(this->mState->getLocation()->getLinearFlow().getFlowMatrix().transpose().rows() == this->mState->getLocation()->getLinearFlow().getFlowMatrix().transpose().cols());
        //return this->mState->getLocation()->getLinearFlow().getFlowMatrix().transpose() * gradientOfLinearFct(dir);
    }

	template<typename State>
	void TPolyFirstSegmentHandler<State>::handle(){

		//TODO: for each set in mState
		std::cout << "TPolyFirstSegmentHandler::handle, start" << std::endl;
		assert(this->mState->getSetType(this->mIndex) == representation_name::polytope_t);
        auto tpoly = boost::apply_visitor(genericConvertAndGetVisitor<TemplatePolyhedron<typename State::NumberType>>(), this->mState->getSet(this->mIndex));
        vector_t<Number> newVec(tpoly.vector().rows());
		
		//For each row:
		for(int rowI = 0; rowI < tpoly.matrix().rows(); ++rowI){

            std::cout << "TPolyFirstSegmentHandler::handle, rowI = " << rowI << " initialize!" << std::endl;

			//Compute Lie derivative to power of m from initial.matrix().row(i)
            Number factorial = 1;
            vector_t<Number> derivative = tpoly.matrix().row(rowI).transpose(); 
            std::vector<tNumber> polynomCoeffs; //Ordering is from lowest to highest degree
            EvaluationResult<Number> evalRes;
			
			//For first m coefficients in polynom:
			for(int coeffI = 0; (unsigned)coeffI < TemplatePolyhedron<Number>::Settings::DERIVATIVE_ORDER; ++coeffI){ 

                std::cout << "TPolyFirstSegmentHandler::handle, coeffI = " << coeffI << ", factorial = " << factorial << ", derivative = \n" << derivative << std::endl;

				//Special case: first index does not use lie derivative
				if(coeffI != 0){
                    std::cout << "TPolyFirstSegmentHandler::handle, not first index anymore, use derivative!" << std::endl;
					factorial *= coeffI;
					derivative = lieDerivative(derivative);	
				} else {
                    std::cout << "TPolyFirstSegmentHandler::handle, first index do not use derivative!" << std::endl;
                }
				
				//if index < m+1: Solve LP over tpoly to evaluate into derivative direction
				//if index == m+1: Solve LP over TPoly(matrix(),invariants) to evaluate into derivative direction (remainder term only bounded by invariants)
                if((unsigned)coeffI < TemplatePolyhedron<Number>::Settings::DERIVATIVE_ORDER - 1){
                    std::cout << "TPolyFirstSegmentHandler::handle, coeffI < " << TemplatePolyhedron<Number>::Settings::DERIVATIVE_ORDER - 1 << " use tpoly for evaluate!" << std::endl;
                	evalRes = tpoly.evaluate(derivative / factorial, true);
                } else {
                    std::cout << "TPolyFirstSegmentHandler::handle, coeffI == " << TemplatePolyhedron<Number>::Settings::DERIVATIVE_ORDER - 1 << " use invtpoly for evaluate!" << std::endl;
                	TemplatePolyhedron<Number> invTPoly(this->mState->getLocation()->getInvariant().getMatrix(), this->mState->getLocation()->getInvariant().getVector());
                	evalRes = invTPoly.evaluate(derivative / factorial, true);
                }

                //Save resulting value as coeff in polynomCoeffs
                if(evalRes.errorCode == SOLUTION::FEAS){
                    std::cout << "TPolyFirstSegmentHandler::handle, emplace_back polynom coeff: " << evalRes.supportValue << std::endl;
                    polynomCoeffs.emplace_back(carl::convert<Number,tNumber>(evalRes.supportValue));
                } else {
                	std::cout << "TPolyFirstSegmentHandler::handle, What did just happen?? It seems like initial set is not closed or unfeasible." << std::endl;
                }

            }

            //Compute derivative of polynom
            carl::Variable var = carl::freshRealVariable("x");
			carl::UnivariatePolynomial<tNumber> polynom(var, polynomCoeffs);
			carl::UnivariatePolynomial<tNumber> polynomDeriv = carl::derivative(polynom);
            
			//Optimization: Compute Cauchy bound and check if roots lie within [0,delta] to avoid root computation when computing maximum value
			//auto boundNumber = carl::cauchyBound(polynomDeriv);
			//If (-(boundNumber + 1) > 0) || boundNumber + 1 < this->mTimeStep)

            //Get maximum value of polynom in time interval [0,delta] save in new coeff vec
            std::vector<carl::RealAlgebraicNumber<tNumber>> roots = carl::rootfinder::RealRootIsolation<tNumber>(polynomDeriv, carl::Interval<tNumber>(tNumber(0),this->mTimeStep)).get_roots();
            tNumber max(-100000);
            for(const carl::RealAlgebraicNumber<tNumber>& root : roots){
                std::cout << "TPolyFirstSegmentHandler::handle, root is: " << root.value() << " is it between 0 and " << this->mTimeStep << "?" << (0 <= root.value() && root.value() <= this->mTimeStep) << std::endl;
            	if(0 <= root.value() && root.value() <= this->mTimeStep){
            		tNumber valueAtRoot = polynom.evaluate(root.value());
                    std::cout << "TPolyFirstSegmentHandler::handle, value at root is: " << valueAtRoot << " bigger than max = " << max << "? " << (valueAtRoot > max) << std::endl;
            		if(valueAtRoot > max){
            			max = valueAtRoot;
            		}
            	}
            }

            //Get value for 0 and for this->mTimeStep and then somehow compute firstSegment
            if(polynom.evaluate(tNumber(0)) > max){
                std::cout << "TPolyFirstSegmentHandler::handle, polynom at 0 is bigger than max with: " << polynom.evaluate(tNumber(0)) << std::endl;
            	max = polynom.evaluate(tNumber(0));
            }
            if(polynom.evaluate(this->mTimeStep) > max){
                std::cout << "TPolyFirstSegmentHandler::handle, polynom at mTimeStep is bigger than max with: " << polynom.evaluate(this->mTimeStep) << std::endl;
                max = polynom.evaluate(this->mTimeStep);
            }
            
            //Set value in coeff vec
            std::cout << "TPolyFirstSegmentHandler::handle, max is: " << carl::convert<tNumber,Number>(max) << std::endl;
            newVec(rowI) = carl::convert<tNumber,Number>(max);
		}
        
        //Set mComputationState vector to the new coeff vec
		tpoly.setVector(newVec);
		this->mState->setSet(boost::apply_visitor(genericInternalConversionVisitor<typename State::repVariant, TemplatePolyhedron<Number>>(tpoly), this->mState->getSet(this->mIndex)),this->mIndex);
	}

}

