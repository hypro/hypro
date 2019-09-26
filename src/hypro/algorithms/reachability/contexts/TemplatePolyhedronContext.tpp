#include "TemplatePolyhedronContext.h"  	

namespace hypro {

    //template<typename State>
    //void TemplatePolyhedronContext<State>::execOnStart(){
    //    //Location Invariant Strengthening
    //}

    template<typename State>
    void TemplatePolyhedronContext<State>::execBeforeFirstSegment(){

        //Modify this->mComputationState depending on TPolySettings to either only use
        //1.Initial constraints (are often boxes)
        //2.Initial constraints + location invariants
        //3.Initial constraints + location invariants + flow constraints
        //4.Octagons 

        std::cout << "TemplatePolyhedronContext::execBeforeFirstSegment, this->mComputationState before: \n" << this->mComputationState << std::endl;
        assert(this->mComputationState.getSetType() == representation_name::polytope_t);
        for(std::size_t index = 0; index < this->mComputationState.getNumberSets(); ++index){
            auto tpoly = boost::apply_visitor(genericConvertAndGetVisitor<TemplatePolyhedron<typename State::NumberType>>(), this->mComputationState.getSet(index));
            switch(TemplatePolyhedron<Number>::Settings::TEMPLATE_SHAPE){
                case(TEMPLATE_CONTENT::ONLY_INIT): {
                    //Normally initial constraints are already inside -> nothing to do 
                    std::cout << "TemplatePolyhedronContext::execBeforeFirstSegment, ONLY_INIT setting" << std::endl;
                    break;
                }
                case(TEMPLATE_CONTENT::INIT_INV): {
                    std::cout << "TemplatePolyhedronContext::execBeforeFirstSegment, INIT_INV setting" << std::endl;
                    assert(tpoly.matrix().cols() == this->mComputationState.getDimension());
                    std::pair<matrix_t<Number>,vector_t<Number>> initialPair = std::make_pair(tpoly.matrix(), tpoly.vector());
                    std::pair<matrix_t<Number>,vector_t<Number>> invPair = std::make_pair(this->mComputationState.getLocation()->getInvariant().getMatrix(), this->mComputationState.getLocation()->getInvariant().getVector());
                    std::vector<std::pair<matrix_t<Number>,vector_t<Number>>> constraints = {initialPair,invPair};
                    TemplatePolyhedron<Number> tpolyWithInv(constraints);
                    this->mComputationState.setSet(boost::apply_visitor(genericInternalConversionVisitor<typename State::repVariant, TemplatePolyhedron<Number>>(tpolyWithInv), this->mComputationState.getSet(index)),index);
                    break;
                }
                case(TEMPLATE_CONTENT::INIT_INV_GUARD): {
                    std::cout << "TemplatePolyhedronContext::execBeforeFirstSegment, INIT_INV_GUARD setting" << std::endl;
                    assert(tpoly.matrix().cols() == this->mComputationState.getDimension());
                    std::vector<std::pair<matrix_t<Number>,vector_t<Number>>> constraints;
                    constraints.emplace_back(std::make_pair(tpoly.matrix(), tpoly.vector()));
                    constraints.emplace_back(std::make_pair(this->mComputationState.getLocation()->getInvariant().getMatrix(), this->mComputationState.getLocation()->getInvariant().getVector()));
                    for(const auto& transition : this->mComputationState.getLocation()->getTransitions()){
                        constraints.emplace_back(std::make_pair(transition->getGuard().getMatrix(), transition->getGuard().getVector()));
                    }
                    TemplatePolyhedron<Number> tpolyWithInvGuard(constraints);
                    this->mComputationState.setSet(boost::apply_visitor(genericInternalConversionVisitor<typename State::repVariant, TemplatePolyhedron<Number>>(tpolyWithInvGuard), this->mComputationState.getSet(index)),index);
                    break;
                }
                case(TEMPLATE_CONTENT::OCTAGON): {
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
                    break;
                }
            }
        }        
        std::cout << "TemplatePolyhedronContext::execBeforeFirstSegment, this->mComputationState after: \n" << this->mComputationState << std::endl;
    }

    template<typename State>
    void TemplatePolyhedronContext<State>::firstSegment(){
        std::cout << "TemplatePolyhedronContext::firstSegment" << std::endl;
        if(TemplatePolyhedron<Number>::Settings::USE_ALTERNATIVE_REACH_ALGO){
            for(std::size_t i = 0; i < this->mComputationState.getNumberSets(); i++){
                this->mFirstSegmentHandlers.at(i)->handle();
            }
        } else {
            for(std::size_t i = 0; i < this->mComputationState.getNumberSets(); i++){
                this->mFirstSegmentHandlers.at(i)->ltiFirstSegmentHandler<State>::handle();       
            }
        }
        this->initializeInvariantHandlers();
        this->initializeBadStateHandlers();
    }

    template<typename State>
    void TemplatePolyhedronContext<State>::checkInvariant(){

        //Compute <H,c> intersect <H,inv>

        //If intersection empty stop further computation
    }

    template<typename State>
    void TemplatePolyhedronContext<State>::applyContinuousEvolution(){

        //As setting: only if reachability algo from paper is wished use it, else use lti stuff
        //Check this at compile time if possible

        //For each row:

            //For m+1 coefficients in polynom:

                //Compute Lie derivative to power of m from initial.matrix().row(i)

                //if index < m+1: save resulting value in g

                //if index == m+1: save resulting value in r

            //Compute g_max = initial.evaluate(g)

            //Compute r_max = TPoly(matrix,invariants).evaluate(r)

            //Save g_max + r_max into eval vector

        //Set this->mComputationState vector to the new eval vec

    }

    template<typename State>
    void TemplatePolyhedronContext<State>::intersectBadStates(){
        //Compute <H,c> intersect <H,bad>   
    }

} // namespace hypro

  	
  	
