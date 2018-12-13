#include "rectangularTimeEvolutionHandler.h"

namespace hypro {
    template<typename State>
	void rectangularTimeEvolutionHandler<State>::handle() {
        if(!mComputed) {
            TRACE("hydra.worker","Applying timestep to " << mState->getSet(mIndex));
            auto& vpool = hypro::VariablePool::getInstance();
            // get initial state
            CarlPolytope<Number> initial = boost::get<CarlPolytopeT<Number>>(mState->getSet(mIndex));
            // storage to build elimination query
            std::vector<carl::Variable> variablesToEliminate;
            // add variable for time elapse
            carl::Variable t = vpool.newCarlVariable("t");
            variablesToEliminate.push_back(t);

            // introduce pre-/primed variables and substitute
            for(const auto& v : initial.getVariables()) {
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
                initial.addConstraints(createFlowConstraints(v,newV, t, mFlow.getFlowIntervalForDimension(v)));
            }

            // create variables to eliminate
            QEQuery quOrder;
            quOrder.push_back(std::make_pair(QuantifierType::EXISTS, variablesToEliminate));
            // allow for some heuristics on how to eliminate
            initial.choseOrder(quOrder);

            // eliminate vars
            initial.eliminateVariables(quOrder);

            // update internal state
            mState->setSetDirect(initial,mIndex);
            // set computed flag
            mComputed = true;
        }
    }
} // hypro
