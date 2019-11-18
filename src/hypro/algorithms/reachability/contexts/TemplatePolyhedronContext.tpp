#include "TemplatePolyhedronContext.h"  	

namespace hypro {

	template<typename State>
    vector_t<typename State::NumberType> TemplatePolyhedronContext<State>::gradientOfLinearFct(const vector_t<Number>& linearFct){
        assert(linearFct.rows() == this->mComputationState.getDimension() + 1);
        vector_t<Number> gradient = linearFct;
        gradient(gradient.rows()-1) = 0;
        return gradient;
    }

    template<typename State>
    vector_t<typename State::NumberType> TemplatePolyhedronContext<State>::lieDerivative(const vector_t<Number>& dir){
        assert(dir.rows() == this->mComputationState.getLocation()->getLinearFlow().getFlowMatrix().transpose().rows());
        assert(this->mComputationState.getLocation()->getLinearFlow().getFlowMatrix().transpose().rows() == this->mComputationState.getLocation()->getLinearFlow().getFlowMatrix().transpose().cols());
        return this->mComputationState.getLocation()->getLinearFlow().getFlowMatrix().transpose() * gradientOfLinearFct(dir);
    }

    template<typename State>
    vector_t<typename State::NumberType> TemplatePolyhedronContext<State>::locationInvariantStrengthening(const TemplatePolyhedron<Number>& invTPoly, const vector_t<Number>& initialOffsets){

        std::cout << "TemplatePolyhedronContext::LIS, invTPoly: \n" << invTPoly << "initialOffsets: \n" << initialOffsets << std::endl;
    	assert(!invTPoly.empty());
    	assert(initialOffsets.rows() == invTPoly.vector().rows());

    	unsigned invRows = invTPoly.matrix().rows();
    	unsigned invCols = invTPoly.matrix().cols();
    	assert(invCols == this->mComputationState.getDimension());

        //Used as storage for solution of last iteration, called a(j) in paper
        vector_t<Number> lastStrengthenedInv = vector_t<Number>::Zero(invTPoly.vector().rows()); 
        //Contains the newest relaxed invariant, called a(j+1) in paper
        vector_t<Number> nextStrengthenedInv = invTPoly.vector(); 
        //Fixed scaling factor mü
        Number scalingFactor = 0.5;	

        //Compute pi(j) (certificate of feasibility for a(j+1)) by solving Dj
        //1.Construct A = (H, extended with lambda_j >= 0)^T
        //NOTE: Since A is the same in every iteration, we construct A once the loop 
        matrix_t<Number> A = matrix_t<Number>::Zero(invRows+invCols,invCols);
        A.block(0,0,invRows,invCols) = invTPoly.matrix();
        A.block(invRows,0,invCols,invCols) = -1*matrix_t<Number>::Identity(invCols,invCols);
        A.transposeInPlace();
        std::cout << "TemplatePolyhedronContext::LIS, A is: \n" << A << std::endl;

        //while a(j) != a(j+1)
        while(lastStrengthenedInv != nextStrengthenedInv){

            //Certificate pi(j): Saves the solutions for each Dj
            matrix_t<Number> certificate = matrix_t<Number>::Zero(invRows,invRows);

            //For each row solve Dj
            for(unsigned rowI = 0; rowI < invRows; ++rowI){

	        	//2.Construct b = (mü(H_j) + H_j')^T, extended with zeros to make sure that the optimumValue only contains positive entries.
	        	vector_t<Number> b = vector_t<Number>::Zero(invRows+invCols);
	        	b.block(0,0,invRows,1) = scalingFactor * invTPoly.matrix().row(rowI) + lieDerivative(invTPoly.matrix().row(rowI));
                std::cout << "TemplatePolyhedronContext::LIS, for rowI: " << rowI << " b is: " << b << std::endl;

	        	//3.Set A and b as matrix and vector for mOptimizer
	        	mOptimizer.setMatrix(A);
	        	mOptimizer.setVector(b.transpose());
	        	mOptimizer.setMaximize(false);

	        	//4.Minimize into direction nextStrengthenedInv - Solution is the optimumValue of minimizeA, 
                //but only the first invRows coefficients from that. The rest was only needed to make sure that the optimumValue only contains positive entries.
	        	auto minimizeA = mOptimizer.evaluate(nextStrengthenedInv,true);
	        	#ifndef NDEBUG
	        	assert(minimizeA.errorCode == SOLUTION::FEAS);
	        	assert(minimizeA.optimumValue.rows() == invRows + invCols);
	        	for(int i = 0; i < minimizeA.optimumValue.rows(); ++i){
	        		//make sure all values are greater than 0
	        		assert(minimizeA.optimumValue(i) >= 0);
	        	}
	        	#endif
                std::cout << "TemplatePolyhedronContext::LIS, minimizeA optimumValue is: " << minimizeA.optimumValue.transpose() << std::endl;
	        	//if(minimizeA.errorCode == SOLUTION::FEAS){
	        	//	//usually also add constant part of lie derivative h_j here, but since we only have lie derivatives of linear fcts, there is no constant part
	        	//	minimizeA.supportValue -= scalingFactor * nextStrengthenedInv(rowI); 
	        	//}

                //5.Save into certificate for later construction of L
	        	certificate.row(rowI) = minimizeA.optimumValue.block(0,0,invRows,1).transpose();
                std::cout << "TemplatePolyhedronContext::LIS, certificate is now: \n" << certificate << std::endl;

            }

        	//Build the system L*y = c 
        	//6.Build L_pi(j): Add constraints: init <= y
        	assert(initialOffsets.rows() == invTPoly.vector().rows());
        	matrix_t<Number> L = matrix_t<Number>::Zero(3*invRows,invRows);
        	vector_t<Number> c = vector_t<Number>::Zero(3*invRows);
        	L.block(0,0,invRows,invRows) = std::move(-1*matrix_t<Number>::Identity(invRows,invRows));
        	c.block(0,0,invRows,1) = -1*initialOffsets;
            std::cout << "TemplatePolyhedronContext::LIS, added init <= y to L and c: L: \n" << L << "c: \n" << c << std::endl;

        	//7.Build L_pi(j): Add constraints: y <= inv_j
        	L.block(invRows,0,invRows,invRows) = std::move(matrix_t<Number>::Identity(invRows,invRows));
        	c.block(invRows,0,invRows,1) = invTPoly.vector();
            std::cout << "TemplatePolyhedronContext::LIS, added y <= inv_j to L and c: L: \n" << L << "c: \n" << c << std::endl;
        	
        	//8.Build L_pi(j): Add constraints. Row frozen if value >= inv
        	//If row j frozen, then y = inv_j
        	//If row j not frozen, then Delta_j^T*y - mü*y_j + h_j <= 0 
        	assert(nextStrengthenedInv.rows() == invRows);
        	for(unsigned i = 0; i < nextStrengthenedInv.rows(); ++i){
        		if(nextStrengthenedInv(i) >= invTPoly.vector()(i)){
        			//frozen row - normally, insert y_j = inv_j, but since y_j <= inv_j is already in L, insert y_j >= inv_j aka -y_j <= -inv_j
                    std::cout << "TemplatePolyhedronContext::LIS, frozen row!" << std::endl;
        			vector_t<Number> rowToInsert = vector_t<Number>::Zero(invRows);
        			rowToInsert(i) = -1;
        			L.row(2*invRows+i) = std::move(rowToInsert.transpose());
        			c(2*invRows+i) = -invTPoly.vector()(i);
        		} else {
        			//non frozen row
                    std::cout << "TemplatePolyhedronContext::LIS, non frozen row!" << std::endl;
        			vector_t<Number> rowToInsert = certificate.row(i);
        			rowToInsert(i) -= scalingFactor;
        			L.row(2*invRows+i) = std::move(rowToInsert.transpose());
        		}
        	}
            std::cout << "TemplatePolyhedronContext::LIS, added (non-)frozen rows to L and c: L: \n" << L << "c: \n" << c << std::endl;

        	//9.Minimize L to get nextStrengthenedInv
        	mOptimizer.setMatrix(L);
        	mOptimizer.setVector(c);
        	mOptimizer.setMaximize(false);
        	auto minimizeL = mOptimizer.evaluate(vector_t<Number>::Ones(invRows),true);
        	assert(minimizeL.errorCode == SOLUTION::FEAS);
        	#ifndef NDEBUG
        	for(unsigned i = 0; i < invRows; ++i){
        		assert(initialOffsets(i) <= minimizeL.optimumValue(i) && minimizeL.optimumValue(i) <= invTPoly.vector()(i));
        	}
        	#endif
            std::cout << "TemplatePolyhedronContext::LIS, minimizeL optimumValue is: \n" << minimizeL.optimumValue << std::endl;

        	//10.Set as next strenghtened inv 
        	lastStrengthenedInv = nextStrengthenedInv;
        	nextStrengthenedInv = minimizeL.optimumValue;

            std::cout << "TemplatePolyhedronContext::LIS, lastStrengthenedInv is now: \n" << lastStrengthenedInv << "nextStrengthenedInv is now: \n" << nextStrengthenedInv << std::endl;
		}                 
		return nextStrengthenedInv;
    }


    template<typename State>
    TemplatePolyhedron<typename State::NumberType> TemplatePolyhedronContext<State>::createTemplateContent(const TemplatePolyhedron<Number>& tpoly){
        
        //Start with initial set 
        assert((unsigned)tpoly.matrix().cols() == this->mComputationState.getDimension());
        std::size_t templateSize = tpoly.matrix().rows();
        matrix_t<Number> extendedMatrix = tpoly.matrix();
        std::cout << "TemplatePolyhedronContext::execBeforeFirstSegment, ONLY_INIT setting" << std::endl;

        //Add invariants if wanted and if there exist some
        if(TemplatePolyhedron<Number>::Settings::TEMPLATE_SHAPE >= TEMPLATE_CONTENT::INIT_INV && this->mComputationState.getLocation()->getInvariant() != Condition<Number>()){
            std::cout << "TemplatePolyhedronContext::execBeforeFirstSegment, INIT_INV setting" << std::endl;
            extendedMatrix.conservativeResize(templateSize + this->mComputationState.getLocation()->getInvariant().getMatrix().rows(), this->mComputationState.getDimension());
            extendedMatrix.block(templateSize,0,this->mComputationState.getLocation()->getInvariant().getMatrix().rows(), this->mComputationState.getDimension()) = this->mComputationState.getLocation()->getInvariant().getMatrix();
            templateSize += this->mComputationState.getLocation()->getInvariant().getMatrix().rows();
        }
        //Add guards if wanted and if there exist some
        if(TemplatePolyhedron<Number>::Settings::TEMPLATE_SHAPE >= TEMPLATE_CONTENT::INIT_INV_GUARD){
            std::cout << "TemplatePolyhedronContext::execBeforeFirstSegment, INIT_INV_GUARD setting" << std::endl;
            for(const auto& transition : this->mComputationState.getLocation()->getTransitions()){
                if(transition->getGuard() != Condition<Number>()){
                    extendedMatrix.conservativeResize(templateSize + transition->getGuard().getMatrix().rows(), this->mComputationState.getDimension());
                    extendedMatrix.block(templateSize,0,transition->getGuard().getMatrix().rows(), this->mComputationState.getDimension()) = transition->getGuard().getMatrix();
                    templateSize += transition->getGuard().getMatrix().rows();           
                }
            }
        }
        //TODO:Add bad states later on
        if(TemplatePolyhedron<Number>::Settings::TEMPLATE_SHAPE >= TEMPLATE_CONTENT::INIT_INV_GUARD_BAD){
            std::cout << "TemplatePolyhedronContext::execBeforeFirstSegment, INIT_INV_GUARD_BAD setting" << std::endl;
            for(const auto& gbadstate : SettingsProvider<State>::getInstance().getHybridAutomaton().getGlobalBadStates()){
                if(gbadstate != Condition<Number>()){
                    extendedMatrix.conservativeResize(templateSize + gbadstate.getMatrix().rows(), this->mComputationState.getDimension());
                    extendedMatrix.block(templateSize,0,gbadstate.getMatrix().rows(), this->mComputationState.getDimension()) = gbadstate.getMatrix();
                    templateSize += gbadstate.getMatrix().rows();   
                }
            }
            auto lbadstate = SettingsProvider<State>::getInstance().getHybridAutomaton().getLocalBadStates().find(this->mComputationState.getLocation());
            if(lbadstate->second != Condition<Number>()){
                extendedMatrix.conservativeResize(templateSize + lbadstate->second.getMatrix().rows(), this->mComputationState.getDimension());
                extendedMatrix.block(templateSize,0,lbadstate->second.getMatrix().rows(), this->mComputationState.getDimension()) = lbadstate->second.getMatrix();
                templateSize += lbadstate->second.getMatrix().rows();   
            }
        }
        //Evaluate tpoly in directions written in extendedMatrix. 
        std::cout << "extendedMatrix: \n" << extendedMatrix << std::endl;
        TemplatePolyhedron<Number> overapprox = tpoly.overapproximate(extendedMatrix);
        overapprox.removeRedundancy();
        std::cout << "overapprox after removeRedundancy: \n" << overapprox << std::endl;
        return overapprox;
    }

    template<typename State>
    void TemplatePolyhedronContext<State>::execBeforeFirstSegment(){

        //Modify this->mComputationState depending on TPolySettings to either only use
        //1.Initial constraints (are often boxes)
        //2.Initial constraints + location invariants
        //3.Initial constraints + location invariants + flow constraints
        //4.Initial constraints + location invariants + flow constraints + all relevant bad states constraints
        //5.Octagons 

        //std::cout << "TemplatePolyhedronContext::execBeforeFirstSegment, this->mComputationState before: \n" << this->mComputationState << std::endl;
        assert(this->mComputationState.getSetType() == representation_name::polytope_t);
        for(std::size_t index = 0; index < this->mComputationState.getNumberSets(); ++index){
            auto tpoly = boost::apply_visitor(genericConvertAndGetVisitor<TemplatePolyhedron<typename State::NumberType>>(), this->mComputationState.getSet(index));
            if(TemplatePolyhedron<Number>::Settings::TEMPLATE_SHAPE != TEMPLATE_CONTENT::OCTAGON){
            	tpoly = createTemplateContent(tpoly);
                this->mComputationState.setSet(boost::apply_visitor(genericInternalConversionVisitor<typename State::repVariant, TemplatePolyhedron<Number>>(tpoly), this->mComputationState.getSet(index)),index);     
            } else {
                std::cout << "TemplatePolyhedronContext::execBeforeFirstSegment, OCTAGON setting" << std::endl;
                TemplatePolyhedron<Number> octagon(this->mComputationState.getDimension(), 8);
                auto evalInOctagonDirs = tpoly.multiEvaluate(octagon.matrix());
                vector_t<Number> evalRes(evalInOctagonDirs.size());
                for(int i = 0; i < evalRes.rows(); ++i){
                    assert(evalInOctagonDirs[i].errorCode == SOLUTION::FEAS);
                    evalRes(i) = evalInOctagonDirs[i].supportValue;
                }
                octagon.setVector(evalRes);
                this->mComputationState.setSet(boost::apply_visitor(genericInternalConversionVisitor<typename State::repVariant, TemplatePolyhedron<Number>>(octagon), this->mComputationState.getSet(index)),index);
            }
            //Call Location Invariant Strengthening on current invariants
	        if(TemplatePolyhedron<Number>::Settings::TEMPLATE_SHAPE >= TEMPLATE_CONTENT::INIT_INV 
	       	   && this->mComputationState.getLocation()->getInvariant().getVector().rows() >= this->mComputationState.getDimension() + 1){
	        	TemplatePolyhedron<Number> invTPoly(this->mComputationState.getLocation()->getInvariant().getMatrix(), this->mComputationState.getLocation()->getInvariant().getVector());
	        	invTPoly = invTPoly.overapproximate(tpoly.matrix());
                //mRelaxedInvariant = vector_t<Number>::Zero(invTPoly.matrix().rows());
	        	mRelaxedInvariant = locationInvariantStrengthening(invTPoly, tpoly.vector());
                std::cout << "TemplatePolyhedronContext::execBeforeFirstSegment: mRelaxedInvariant is: " << mRelaxedInvariant << std::endl;
                exit(0);
	        	//TOOOOOOOOODOOOOOOOOO: What to do with that?
	        	//Set result as invariant TPoly to use in TPolyFirstSegmentHandler and TPolyTimeEvolutionHandler
	        }
        }        
        //std::cout << "TemplatePolyhedronContext::execBeforeFirstSegment, this->mComputationState after: \n" << this->mComputationState << std::endl;        

        //Do the stuff ltiContext would to 
        this->LTIContext<State>::execBeforeFirstSegment();
    }

    template<typename State>
    void TemplatePolyhedronContext<State>::firstSegment(){
        //std::cout << "TemplatePolyhedronContext::firstSegment" << std::endl;
        if(TemplatePolyhedron<Number>::Settings::USE_ALTERNATIVE_REACH_ALGO){
            for(std::size_t i = 0; i < this->mComputationState.getNumberSets(); i++){
                std::cout << "TemplatePolyhedronContext::firstSegment, use USE_ALTERNATIVE_REACH_ALGO!" << std::endl;
                this->mFirstSegmentHandlers.at(i)->handle();
            }
        } else {
            for(std::size_t i = 0; i < this->mComputationState.getNumberSets(); i++){
                std::cout << "TemplatePolyhedronContext::firstSegment, use standard reach algo!" << std::endl;
                static_cast<ltiFirstSegmentHandler<State>*>(this->mFirstSegmentHandlers.at(i))->handle();
            }
        }
        //Do the stuff ltiContext would to 
        this->initializeInvariantHandlers();
        this->initializeBadStateHandlers();
    }

    template<typename State>
    void TemplatePolyhedronContext<State>::applyContinuousEvolution(){
        //std::cout << "TemplatePolyhedronContext::applyContinuousEvolution" << std::endl;
        if(TemplatePolyhedron<Number>::Settings::USE_ALTERNATIVE_REACH_ALGO){
            for(std::size_t i = 0; i < this->mComputationState.getNumberSets(); i++){
                //std::cout << "TemplatePolyhedronContext::applyContinuousEvolution, use USE_ALTERNATIVE_REACH_ALGO!" << std::endl;
                this->mContinuousEvolutionHandlers.at(i)->handle();
            }
        } else {
            for(std::size_t i = 0; i < this->mComputationState.getNumberSets(); i++){
                //std::cout << "TemplatePolyhedronContext::applyContinuousEvolution, use standard reach algo!" << std::endl;
                static_cast<ltiTimeEvolutionHandler<State>*>(this->mContinuousEvolutionHandlers.at(i))->handle();
            }
        }
        //Do the stuff ltiContext would to 
        this->mComputationState.setTimestamp(this->mComputationState.getTimestamp()+this->mStrategy.getParameters(this->mTask->btInfo.btLevel).timeStep);
        for(auto it = this->mContinuousEvolutionHandlers.begin(); it != this->mContinuousEvolutionHandlers.end(); ){
            if((*it)->getMarkedForDelete()) {
                delete *it;
                it = this->mContinuousEvolutionHandlers.erase(it);
            } else {
                ++it;
            }
        }
    }

} // namespace hypro

  	
  	
