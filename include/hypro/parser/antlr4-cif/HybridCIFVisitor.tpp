#include "HybridCIFVisitor.h"

namespace hypro {

	template<typename Number>
	HybridCIFVisitor<Number>::HybridCIFVisitor() :
		vars()
	{ }

	template<typename Number>
	HybridCIFVisitor<Number>::~HybridCIFVisitor(){ }

	/*Beginning*/
	template<typename Number>
	antlrcpp::Any HybridCIFVisitor<Number>::visitSpecification(HybridSystemParser::SpecificationContext *ctx){

		return visitChildren(ctx);
	}


	/*catch all variables*/
	template<typename Number>
	antlrcpp::Any HybridCIFVisitor<Number>::visitDiscDecl(HybridSystemParser::DiscDeclContext *ctx){
		//first only catch which variables are there
		//IMPORTANT: initial values are set also here.
		std::string varName = (ctx->identifier())->getText();
		vars.push_back(varName);
		return varName;
	}


	template<typename Number>
	antlrcpp::Any HybridCIFVisitor<Number>::visitAutomatonBody(HybridSystemParser::AutomatonBodyContext *ctx){

		//optional: initial values, variable declarations, multiple not-so-far handable options like synchronisation etc.
		visit(ctx->optAutDecls());

		/*
		std::cout << "Vars are:" << std::endl;
		for (auto i = vars.begin(); i != vars.end(); ++i)
    			std::cout << *i << ' ';
		std::cout << std::endl;
		*/

		//locations, also containing edge information
		CIFLocVisitor<Number> locVisitor = CIFLocVisitor<Number>(vars);
		std::pair< std::vector<Location<Number>*>, std::vector<Transition<Number>*> > result = locVisitor.visit(ctx->locations());
		locSet = result.first;
		transitionVector = result.second;


		//IO Delcarations
		visit(ctx->optIoDecls());

		return true;
	}


//All things, we can't handle yet

	template<typename Number>
	antlrcpp::Any HybridCIFVisitor<Number>::visitStdLibFunction(HybridSystemParser::StdLibFunctionContext *ctx){
		std::cerr << "Could not handle std lib functions yet." << std::endl;
		exit( 1 );
		return visitChildren(ctx); //for not generating a warning
	}

	template<typename Number>
	antlrcpp::Any HybridCIFVisitor<Number>::visitControllability(HybridSystemParser::ControllabilityContext *ctx){
		std::cerr << "Could not handle controllability yet." << std::endl;
		exit( 1 );
		return visitChildren(ctx); //for not generating a warning
	}

	template<typename Number>
	antlrcpp::Any HybridCIFVisitor<Number>::visitOptControllability(HybridSystemParser::OptControllabilityContext *ctx){
		std::cerr << "Could not handle controllability yet." << std::endl;
		exit( 1 );
		return visitChildren(ctx); //for not generating a warning
	}

	template<typename Number>
	antlrcpp::Any HybridCIFVisitor<Number>::visitEvents(HybridSystemParser::EventsContext *ctx){
		std::cerr << "Could not handle events yet." << std::endl;
		exit( 1 );
		return visitChildren(ctx); //for not generating a warning
	}

	template<typename Number>
	antlrcpp::Any HybridCIFVisitor<Number>::visitEdgeEvent(HybridSystemParser::EdgeEventContext *ctx){
		std::cerr << "Could not handle events yet." << std::endl;
		exit( 1 );
		return visitChildren(ctx); //for not generating a warning
	}

	//IMPORTANT: maybe information for settings
	template<typename Number>
	antlrcpp::Any HybridCIFVisitor<Number>::visitIoDecls(HybridSystemParser::IoDeclsContext *ctx){
		std::cerr << "Could not handle IO manegement or SVG output within the model yet." << std::endl;
		exit( 1 );
		return visitChildren(ctx); //for not generating a warning
	}
/*
	template<typename Number>
	antlrcpp::Any HybridCIFVisitor<Number>::visit***(HybridSystemParser::***Context *ctx){
		std::cerr << "Could not interpret /handle *** yet." << std::endl;
		exit( 1 );
		return visitChildren(ctx); //for not generating a warning
	}
*/
}
