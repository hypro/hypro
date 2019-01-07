#include "rectangularTimeEvolutionHandler.h"

namespace hypro {
    template<typename State>
	void rectangularTimeEvolutionHandler<State>::handle() {
        if(!mComputed) {
            DEBUG("hydra.worker","Applying timestep to " << mState->getSet(mIndex));
            auto& vpool = hypro::VariablePool::getInstance();
            // get initial state
            CarlPolytope<Number> initial = boost::get<CarlPolytope<Number>>(mState->getSet(mIndex));
            // storage to build elimination query
            std::vector<carl::Variable> variablesToEliminate;
            // add variable for time elapse
            carl::Variable t = vpool.newCarlVariable("t");
            variablesToEliminate.push_back(t);
            // add constraint t >= 0
            initial.addConstraint(ConstraintT<hypro::tNumber>(PolyT<hypro::tNumber>(t), carl::Relation::GEQ));

            // introduce pre-/primed variables and substitute
            for(const auto& v : initial.getVariables()) {
                if(v != t) {
                    // create primed var
                    std::stringstream ss;
                    ss << v.name() << "_pre";
                    std::string s = ss.str();
                    auto newV = vpool.newCarlVariable(s);
                    // substitute to create precondition
                    initial.substituteVariable(v,newV);
                    // store var to eliminate later
                    variablesToEliminate.push_back(newV);
                    // add flow conditions for new variables, we use the variable mapping provided by the flow
                    std::vector<ConstraintT<hypro::tNumber>> flowConstraints = createFlowConstraints<hypro::tNumber,typename State::NumberType>(v,newV, t, mFlow.getFlowIntervalForDimension(v));

                    TRACE("hydra.worker","Use flow constraints: ");
                    #ifdef HYPRO_LOGGING
                    for(const auto& c : flowConstraints) {
                        TRACE("hydra.worker",c);
                    }
                    #endif

                    initial.addConstraints(flowConstraints);
                }
            }

            // create variables to eliminate
            QEQuery quOrder;
            quOrder.push_back(std::make_pair(QuantifierType::EXISTS, variablesToEliminate));
            // allow for some heuristics on how to eliminate
            initial.choseOrder(quOrder);

            // eliminate vars
            initial.eliminateVariables(quOrder);

            //for(auto var : variablesToEliminate) {
            //    initial.eliminateVariable(var);
            //}

            DEBUG("hydra.worker","State set after time elapse: " << initial);

            // update internal state
            mState->setSetDirect(initial,mIndex);
            // set computed flag
            mComputed = true;
            mMarkedForDelete = true;
        }
    }
} // hypro
