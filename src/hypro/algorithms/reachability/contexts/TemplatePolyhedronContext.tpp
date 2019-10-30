#include "TemplatePolyhedronContext.h"  	

namespace hypro {

/*
    template<typename State>
    void TemplatePolyhedronContext<State>::locationInvariantStrengthening(){
    
        //a(0) = inv

        //while a(j+1) != a(j)

            //Compute pi(j) by solving Dj

            //Compute a(j+1) by solving L_pi(j)

        //Set result as invariant TPoly to use in TPolyFirstSegmentHandler and TPolyTimeEvolutionHandler
    }
*/

    template<typename State>
    TemplatePolyhedron<typename State::NumberType> TemplatePolyhedronContext<State>::createTemplateContent(const TemplatePolyhedron<Number>& tpoly){
        
        //Start with initial set 
        assert(tpoly.matrix().cols() == this->mComputationState.getDimension());
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
            if(TemplatePolyhedron<Number>::Settings::TEMPLATE_SHAPE < TEMPLATE_CONTENT::OCTAGON){
                this->mComputationState.setSet(boost::apply_visitor(genericInternalConversionVisitor<typename State::repVariant, TemplatePolyhedron<Number>>(createTemplateContent(tpoly)), this->mComputationState.getSet(index)),index);     
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
        }        
        //std::cout << "TemplatePolyhedronContext::execBeforeFirstSegment, this->mComputationState after: \n" << this->mComputationState << std::endl;

        //Call Location Invariant Strengthening

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

  	
  	
