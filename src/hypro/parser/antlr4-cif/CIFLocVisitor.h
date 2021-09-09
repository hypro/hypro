#pragma once


#include "../../datastructures/HybridAutomaton/Location.h"
#include "../../datastructures/HybridAutomaton/LocationManager.h"
#include "../../../../include/hypro/datastructures/HybridAutomaton/Transition.h"
#include "../../types.h"
#include "CIFExprVisitor.h"
#include "HybridSystemBaseVisitor.h"
#include "HybridSystemVisitor.h"
#include "antlr4-runtime.h"

using namespace antlr4;

namespace hypro {

template<typename Number>
class CIFLocVisitor : public HybridSystemBaseVisitor {

	private:

		//A vector of all variables which are defined
		std::vector<std::string> vars;
		LocationManager<Number>& manager = LocationManager<Number>::getInstance();
		std::set< std::pair<Transition<Number>*,string> > transWithTargets;
		Location<Number>* actualLocation;
		std::vector<Transition<Number>*> transitionVector;


		//antlrcpp::Any visitLoc(HybridSystemParser::LocContext *ctx) override;
		//antlrcpp::Any visitLocId(HybridSystemParser::LocIdContext *ctx) override;
		antlrcpp::Any visitLocElem(HybridSystemParser::LocElemContext *ctx) override;
		antlrcpp::Any visitLocIdElem(HybridSystemParser::LocIdElemContext *ctx) override;

		antlrcpp::Any visitCoreEdge(HybridSystemParser::CoreEdgeContext *ctx) override;

		antlrcpp::Any visitLocElemInitialFlag(HybridSystemParser::LocElemInitialFlagContext *ctx) override;
		antlrcpp::Any visitLocElemEqs(HybridSystemParser::LocElemEqsContext *ctx) override;
		antlrcpp::Any visitLocElemEdgeTo(HybridSystemParser::LocElemEdgeToContext *ctx) override;
		antlrcpp::Any visitLocElemLoop(HybridSystemParser::LocElemLoopContext *ctx) override;

		antlrcpp::Any visitInvariants(HybridSystemParser::InvariantsContext *ctx) override;
		antlrcpp::Any visitInvExpr(HybridSystemParser::InvExprContext *ctx) override;
		antlrcpp::Any visitUpdates(HybridSystemParser::UpdatesContext *ctx) override;
		antlrcpp::Any visitUpdateNonIf(HybridSystemParser::UpdateNonIfContext *ctx) override;

		antlrcpp::Any visitAdressableId(HybridSystemParser::AdressableIdContext *ctx) override;

		//things we can't handle
		antlrcpp::Any visitInvNeeds(HybridSystemParser::InvNeedsContext *ctx) override;
		antlrcpp::Any visitInvNeedsSet(HybridSystemParser::InvNeedsSetContext *ctx) override;
		antlrcpp::Any visitInvDisables(HybridSystemParser::InvDisablesContext *ctx) override;
		antlrcpp::Any visitInvDisablesSet(HybridSystemParser::InvDisablesSetContext *ctx) override;
		antlrcpp::Any visitSupKind(HybridSystemParser::SupKindContext *ctx) override;
		antlrcpp::Any visitUpdateIf(HybridSystemParser::UpdateIfContext *ctx) override;
		//antlrcpp::Any visit***(HybridSystemParser::***Context *ctx) override;

	public:

		CIFLocVisitor(std::vector<std::string> varVec);
		~CIFLocVisitor();

		antlrcpp::Any visitLocations(HybridSystemParser::LocationsContext *ctx) override;

};


} //namespace hypro

#include "CIFLocVisitor.tpp"
