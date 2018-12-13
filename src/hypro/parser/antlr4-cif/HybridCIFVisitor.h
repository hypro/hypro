#pragma once


#include "antlr4-runtime.h"
#include "HybridSystemVisitor.h"
#include "HybridSystemBaseVisitor.h"
#include "CIFLocVisitor.h"
#include "../../types.h"
#include "../../datastructures/HybridAutomaton/Location.h"
#include "../../datastructures/HybridAutomaton/LocationManager.h"
/*#include "../../datastructures/HybridAutomaton/HybridAutomaton.h"

#include "../../datastructures/HybridAutomaton/Condition.h"*/

using namespace antlr4;

namespace hypro {

template<typename Number>
class HybridCIFVisitor : public HybridSystemBaseVisitor {

	private:

		//A vector of all variables which are defined
		std::vector<std::string> vars;
		int numberOfLocationsWithoutAName = 0;
		std::vector<Location<Number>*> locSet;
		std::vector<Transition<Number>*> transitionVector;

		antlrcpp::Any visitDiscDecl(HybridSystemParser::DiscDeclContext *ctx) override;
		antlrcpp::Any visitAutomatonBody(HybridSystemParser::AutomatonBodyContext *ctx) override;
		antlrcpp::Any visitStdLibFunction(HybridSystemParser::StdLibFunctionContext *ctx) override;
		antlrcpp::Any visitControllability(HybridSystemParser::ControllabilityContext *ctx) override;
		antlrcpp::Any visitOptControllability(HybridSystemParser::OptControllabilityContext *ctx) override;
		antlrcpp::Any visitEvents(HybridSystemParser::EventsContext *ctx) override;
		antlrcpp::Any visitEdgeEvent(HybridSystemParser::EdgeEventContext *ctx) override;
		antlrcpp::Any visitIoDecls(HybridSystemParser::IoDeclsContext *ctx) override;

	public:

		HybridCIFVisitor();
		~HybridCIFVisitor();

		antlrcpp::Any visitSpecification(HybridSystemParser::SpecificationContext *ctx) override;


};


} //namespace hypro

#include "HybridCIFVisitor.tpp"
