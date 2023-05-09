/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "CIFLocVisitor.h"

namespace hypro {

    template<typename Number>
    CIFLocVisitor<Number>::CIFLocVisitor(std::vector<std::string> varVec) :
            vars(varVec) {}

    template<typename Number>
    CIFLocVisitor<Number>::~CIFLocVisitor() {}

    template<typename Number>
    antlrcpp::Any CIFLocVisitor<Number>::visitLocations(HybridSystemParser::LocationsContext *ctx) {

        std::vector<Location<Number> *> locSet;

        size_t n = ctx->children.size();
        for (size_t i = 0; i < n; i++) {

            // think about locations without names
            /*for(auto& loc : locSet){
                if(loc->getName() == ctx->children[i]->identifier()->getText()){
                    std::cerr << "Location " << loc->getName() << " has already been parsed." << std::endl;
                }
            }*/

            Location<Number> *loc = visit(ctx->children[i]);
            locSet.push_back(loc);
        }

        for (std::pair<Transition<Number> *, string> ts: transWithTargets) {
            Transition<Number> *tmp = ts.first;
            tmp->setTarget(manager.location(ts.second));
            tmp->getSource()->addTransition(tmp);
            transitionVector.push_back(tmp);
        }


        std::pair<std::vector<Location<Number> *>, std::vector<Transition<Number> *> > result;
        result.first = locSet;
        result.second = transitionVector;
        return result;

    }


    template<typename Number>
    antlrcpp::Any CIFLocVisitor<Number>::visitLocIdElem(HybridSystemParser::LocIdElemContext *ctx) {

        //create location
        Location<Number> *loc = new Location<Number>();
        loc->setName((ctx->identifier())->getText());
        actualLocation = loc;

        //visit Elems to get information about edges, flow matrix and invariants
        visit(ctx->locationElements());

        return loc;
    }


    template<typename Number>
    antlrcpp::Any CIFLocVisitor<Number>::visitLocElem(HybridSystemParser::LocElemContext *ctx) {

        std::string locName = "onlyLonelyLocation";

        //create location
        Location<Number> *loc = new Location<Number>();
        loc->setName(locName);
        actualLocation = loc;

        //visit Elems to get information about edges, flow matrix and invariants
        visit(ctx->locationElements());

        return loc;
    }

    template<typename Number>
    antlrcpp::Any CIFLocVisitor<Number>::visitCoreEdge(HybridSystemParser::CoreEdgeContext *ctx) {

        //get guard and reset
        return visitChildren(ctx);
    }

    template<typename Number>
    antlrcpp::Any CIFLocVisitor<Number>::visitInvExpr(HybridSystemParser::InvExprContext *ctx) {

        CIFExprVisitor<Number> exprVisitor = CIFExprVisitor<Number>(vars);
        std::vector<std::pair<vector_t<Number>, Number>> result = exprVisitor.visit(ctx->expression());
        return result;
    }



    //locationElements


    template<typename Number>
    antlrcpp::Any CIFLocVisitor<Number>::visitLocElemInitialFlag(HybridSystemParser::LocElemInitialFlagContext *ctx) {

        return visitChildren(ctx); //for not generating a warning
    }


    template<typename Number>
    antlrcpp::Any CIFLocVisitor<Number>::visitLocElemEqs(HybridSystemParser::LocElemEqsContext *ctx) {

        //fill flow matrix
        CIFExprVisitor<Number> exprVisitor = CIFExprVisitor<Number>(vars);
        matrix_t<Number> flow = exprVisitor.visit(ctx->equations());

        actualLocation->setFlow(flow);

        return flow;
    }

    template<typename Number>
    antlrcpp::Any CIFLocVisitor<Number>::visitLocElemEdgeTo(HybridSystemParser::LocElemEdgeToContext *ctx) {

        Transition<Number> *trans = new Transition<Number>();
        std::pair<Transition<Number> *, string> result;
        string sourceName = actualLocation->getName();
        trans->setSource(actualLocation);

        visit(ctx->coreEdge());

        result.first = trans;
        result.second = (ctx->identifier())->getText();

        transWithTargets.insert(result);

        return result;
    }

    template<typename Number>
    antlrcpp::Any CIFLocVisitor<Number>::visitLocElemLoop(HybridSystemParser::LocElemLoopContext *ctx) {

        Transition<Number> *trans = new Transition<Number>();
        string sourceName = actualLocation->getName();
        trans->setSource(actualLocation);
        trans->setTarget(actualLocation);

        //visit Children
        visit(ctx->coreEdge());

        actualLocation->addTransition(trans);
        transitionVector.push_back(trans);

        return trans;
    }


    template<typename Number>
    antlrcpp::Any CIFLocVisitor<Number>::visitInvariants(HybridSystemParser::InvariantsContext *ctx) {

        size_t numberOfInvariantVectors = ctx->children.size();

        std::vector<std::vector<std::pair<vector_t<Number>, Number>>> allInvariantVectors;
        allInvariantVectors.resize(numberOfInvariantVectors);
        int numberOfInvariants = 0;

        for (size_t i = 0; i < numberOfInvariantVectors; i++) {
            std::vector<std::pair<vector_t<Number>, Number>> tmp = visit(ctx->children[i]);
            allInvariantVectors[i] = tmp;
            numberOfInvariants = numberOfInvariants + tmp.size();
        }

        matrix_t<Number> resultMatrix = matrix_t<Number>::Zero(numberOfInvariants, vars.size());
        vector_t<Number> resultVector = vector_t<Number>::Zero(numberOfInvariants);

        unsigned int actualRow = 0;
        for (unsigned int i = 0; i < numberOfInvariantVectors; i++) {

            std::vector<std::pair<vector_t<Number>, Number>> invariant = allInvariantVectors[i];

            for (unsigned int j = 0; invariant.size(); j++) {
                resultMatrix.row(actualRow + j) = invariant[j].first;
                resultVector[actualRow + j] = invariant[j].second;
            }

            actualRow = actualRow + invariant.size();

        }

        Condition<Number> inv;
        inv.setMatrix(resultMatrix);
        inv.setVector(resultVector);
        actualLocation->setInvariant(inv); //TODO its possible to set more than one time "invariants" => add not set

        return inv;

    }

    template<typename Number>
    antlrcpp::Any CIFLocVisitor<Number>::visitUpdates(HybridSystemParser::UpdatesContext *ctx) {

        /*matrix_t<Number> result = matrix_t<Number>::Zero(vars.size()+1, vars.size()+1);

        size_t n = ctx->children.size();
        for (size_t i = 0; i < n-1; i++) {
            std::pair<string,vector_t<Number>> tmp = visit(ctx->children[i]);
            result.row(varToInt[tmp.first]) = tmp.second;
        }

        Result<Number> inv;
        inv.setMatrix(resultMatrix);
        inv.setVector(resultVector);
        actualLocation->setInvariant(inv); //TODO its possible to set more than one time "invariants" => add not set

        return inv;*/

        return visitChildren(ctx); //for not generating a warning

    }

    template<typename Number>
    antlrcpp::Any CIFLocVisitor<Number>::visitUpdateNonIf(HybridSystemParser::UpdateNonIfContext *ctx) {

        CIFExprVisitor<Number> exprVisitor = CIFExprVisitor<Number>(vars);
        std::vector<std::pair<vector_t<Number>, Number>> expr = exprVisitor.visit(ctx->expression());

        std::pair<string, vector_t<Number> > result;
        string name = visit(ctx->adressable());
        result.first = name;
        result.second = expr[0].first;

        return result;

    }


    template<typename Number>
    antlrcpp::Any CIFLocVisitor<Number>::visitAdressableId(HybridSystemParser::AdressableIdContext *ctx) {
        string result = ctx->getText();
        return result;
    }


    //things we can't handle


    template<typename Number>
    antlrcpp::Any CIFLocVisitor<Number>::visitInvNeeds(HybridSystemParser::InvNeedsContext *ctx) {
        std::cerr << "Could not interpret /handle events (keyword needs)  yet." << std::endl;
        exit(1);
        return visitChildren(ctx); //for not generating a warning
    }

    template<typename Number>
    antlrcpp::Any CIFLocVisitor<Number>::visitInvNeedsSet(HybridSystemParser::InvNeedsSetContext *ctx) {
        std::cerr << "Could not interpret /handle events (keyword needs) yet." << std::endl;
        exit(1);
        return visitChildren(ctx); //for not generating a warning
    }

    template<typename Number>
    antlrcpp::Any CIFLocVisitor<Number>::visitInvDisables(HybridSystemParser::InvDisablesContext *ctx) {
        std::cerr << "Could not interpret /handle events (keyword disables) yet." << std::endl;
        exit(1);
        return visitChildren(ctx); //for not generating a warning
    }

    template<typename Number>
    antlrcpp::Any CIFLocVisitor<Number>::visitInvDisablesSet(HybridSystemParser::InvDisablesSetContext *ctx) {
        std::cerr << "Could not interpret /handle events (keyword diables) yet." << std::endl;
        exit(1);
        return visitChildren(ctx); //for not generating a warning
    }

    template<typename Number>
    antlrcpp::Any CIFLocVisitor<Number>::visitSupKind(HybridSystemParser::SupKindContext *ctx) {
        std::cerr << "Could not interpret /handle supervisors yet." << std::endl;
        exit(1);
        return visitChildren(ctx); //for not generating a warning
    }

    template<typename Number>
    antlrcpp::Any CIFLocVisitor<Number>::visitUpdateIf(HybridSystemParser::UpdateIfContext *ctx) {
        std::cerr << "Could not interpret if expressions in updates yet." << std::endl;
        exit(1);
        return visitChildren(ctx); //for not generating a warning
    }

/*
	template<typename Number>
	antlrcpp::Any CIFLocVisitor<Number>::visit***(HybridSystemParser::***Context *ctx){
		std::cerr << "Could not interpret /handle *** yet." << std::endl;
		exit( 1 );
		return visitChildren(ctx); //for not generating a warning
	}
*/
}
