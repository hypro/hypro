#pragma once 

#include "TPolyFirstSegmentHandler.h"

namespace hypro {


	template<typename State>
    vector_t<typename State::NumberType> TPolyFirstSegmentHandler<State>::gradientOfLinearFct(const vector_t<Number>& linearFct){
        assert(linearFct.rows() == this->mState->getDimension() + 1);
        vector_t<Number> gradient = linearFct;
        gradient(gradient.rows()-1) = 0;
        return gradient;
    }

    template<typename State>
    vector_t<typename State::NumberType> TPolyFirstSegmentHandler<State>::lieDerivative(const vector_t<Number>& dir){
        assert(dir.rows() == this->mState->getLocation()->getLinearFlow().getFlowMatrix().transpose().rows());
        assert(this->mState->getLocation()->getLinearFlow().getFlowMatrix().transpose().rows() == this->mState->getLocation()->getLinearFlow().getFlowMatrix().transpose().cols());
        return this->mState->getLocation()->getLinearFlow().getFlowMatrix().transpose() * gradientOfLinearFct(dir);
    }

	template<typename State>
	void TPolyFirstSegmentHandler<State>::handle(){

		assert(this->mState->getSetType(this->mIndex) == representation_name::polytope_t);
        auto tpoly = boost::apply_visitor(genericConvertAndGetVisitor<TemplatePolyhedron<typename State::NumberType>>(), this->mState->getSet(this->mIndex));
        vector_t<Number> newVec(tpoly.vector().rows());
		
		//For each row:
		for(int rowI = 0; rowI < tpoly.matrix().rows(); ++rowI){

			//Compute Lie derivative to power of m from initial.matrix().row(i)
            Number factorial = 1;
            vector_t<Number> derivative(tpoly.matrix().cols()+1);
            derivative.block(0,0,tpoly.matrix().cols(),1) = tpoly.matrix().row(rowI).transpose();
            derivative(derivative.rows()-1) = 0;
            //vector_t<Number> derivative = vector_t<Number>(tpoly.matrix().row(rowI).transpose()); 
            std::vector<tNumber> polynomCoeffs; //Ordering is from lowest to highest degree
            polynomCoeffs.emplace_back(tpoly.vector()(rowI));
            EvaluationResult<Number> evalRes;
			
			//For first m coefficients in polynom:
			//for(int coeffI = 1; (unsigned)coeffI < TemplatePolyhedron<Number>::Settings::DERIVATIVE_ORDER; ++coeffI){ 
            for(int coeffI = 1; coeffI < tpoly.matrix().rows() + 1; ++coeffI){

				//Special case: first index does not use lie derivative
				factorial *= coeffI;
				derivative = lieDerivative(derivative);	
                vector_t<Number> derivVarCoeffs(derivative.rows()-1);
                derivVarCoeffs = derivative.block(0,0,derivVarCoeffs.rows(),1);

				//if index < m+1: Solve LP over tpoly to evaluate into derivative direction
				//if index == m+1: Solve LP over TPoly(matrix(),invariants) to evaluate into derivative direction (remainder term only bounded by invariants)
                //if((unsigned)coeffI < TemplatePolyhedron<Number>::Settings::DERIVATIVE_ORDER - 1){
                if(coeffI < tpoly.matrix().rows()){
                    if(derivVarCoeffs == vector_t<Number>::Zero(derivVarCoeffs.rows())){
                        evalRes = EvaluationResult<Number>(derivative(derivative.rows()-1), SOLUTION::FEAS);
                        //polynomCoeffs.emplace_back(carl::convert<Number,tNumber>(derivative(derivative.rows()-1)) / factorial);
                        //break;
                    } else {
                        evalRes = tpoly.evaluate(derivative / factorial, true);    
                    }
                } else {
                    //NOTE: How to treat remainder? Normally, use tpoly.matrix() as matrix, and use giant coeffs where bounds do not exist but evaluating then does not make any sense.
                    //If using the invariant matrix we either get the same or better results.
                	TemplatePolyhedron<Number> invTPoly(this->mState->getLocation()->getInvariant().getMatrix(), this->mState->getLocation()->getInvariant().getVector());
                	evalRes = invTPoly.evaluate(derivVarCoeffs / factorial, true);
                }

                //Save resulting value as coeff in polynomCoeffs
                if(evalRes.errorCode == SOLUTION::FEAS){
                    polynomCoeffs.emplace_back(carl::convert<Number,tNumber>(evalRes.supportValue));
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
            tNumber max(-1e100);
            for(const carl::RealAlgebraicNumber<tNumber>& root : roots){
            	if(0 <= root.value() && root.value() <= this->mTimeStep){
            		tNumber valueAtRoot = polynom.evaluate(root.value());
            		if(valueAtRoot > max){
            			max = valueAtRoot;
            		}
            	}
            }

            //Get value for 0 and for this->mTimeStep and then somehow compute firstSegment
            if(polynom.evaluate(tNumber(0)) > max){
            	max = polynom.evaluate(tNumber(0));
            }
            if(polynom.evaluate(this->mTimeStep) > max){
                max = polynom.evaluate(this->mTimeStep);
            }
            
            //Set value in coeff vec
            newVec(rowI) = carl::convert<tNumber,Number>(max);
		}
        
        //Set mComputationState vector to the new coeff vec
		tpoly.setVector(newVec);
		this->mState->setSet(boost::apply_visitor(genericInternalConversionVisitor<typename State::repVariant, TemplatePolyhedron<Number>>(tpoly), this->mState->getSet(this->mIndex)),this->mIndex);
	}

}

