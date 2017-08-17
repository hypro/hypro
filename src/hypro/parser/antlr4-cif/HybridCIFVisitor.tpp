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
		std::cout << "Beginning" << std::endl;
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
	antlrcpp::Any HybridCIFVisitor<Number>::visitCoreEdge(HybridSystemParser::CoreEdgeContext *ctx){
		std::cout << "-- Visit CoreEdge" << std::endl;
		std::cout << "optEdgeUpdate" << (ctx->optEdgeUpdate())->getText() << std::endl;
		return visitChildren(ctx);
	}


	template<typename Number>
	antlrcpp::Any HybridCIFVisitor<Number>::visitLocations(HybridSystemParser::LocationsContext *ctx){
		
		std::set<Location<Number>*> locSet;
		size_t n = ctx->children.size();
		for (size_t i = 0; i < n; i++) {

			// think about locations without names
			/*for(auto& loc : locSet){
				if(loc->getName() == ctx->children[i]->identifier()->getText()){
					std::cerr << "Location " << loc->getName() << " has already been parsed." << std::endl;
				}
			}*/

			Location<Number>* loc = visit(ctx->children[i]);
			locSet.insert(loc);
		}
		std::cout << "There are " << locSet.size() << " locations." << std::endl;
		return locSet;

	}
	

	template<typename Number>
	antlrcpp::Any HybridCIFVisitor<Number>::visitLocIdElem(HybridSystemParser::LocIdElemContext *ctx){
		std::cout << "-- Visit Location " << (ctx->identifier())->getText() << std::endl;
		
		//visit Elems to get information about edges, flow matrix and invariants 
		LocationManager<Number>& manager = LocationManager<Number>::getInstance();
		visit(ctx->locationElements());

		//only a dummy location
		Location<Number>* loc =	manager.create();	

		return loc;
	}

	template<typename Number>
	antlrcpp::Any HybridCIFVisitor<Number>::visitLocElem(HybridSystemParser::LocElemContext *ctx){
		
		numberOfLocationsWithoutAName++;
		std::string locName = "location" + std::to_string(numberOfLocationsWithoutAName);
		std::cout << "-- Visit Location " << locName << std::endl;
		
		//visit Elems to get information about edges, flow matrix and invariants 
		LocationManager<Number>& manager = LocationManager<Number>::getInstance();
		visit(ctx->locationElements());

		//only a dummy location
		Location<Number>* loc =	manager.create();	

		return loc;
	}


	template<typename Number>
	antlrcpp::Any HybridCIFVisitor<Number>::visitAutomatonBody(HybridSystemParser::AutomatonBodyContext *ctx){
		std::cout << "-- Visit optAutDecls" << std::endl;

		//optional: initial values, variable declarations, multiple not-so-far handable options like synchronisation etc.
		visit(ctx->optAutDecls());

		std::cout << "Vars are:" << std::endl;
		for (auto i = vars.begin(); i != vars.end(); ++i)
    			std::cout << *i << ' ';
		std::cout << std::endl;

		

		std::cout << "-- Visit Locations" << std::endl;
		//locations also containing edge information
		visit(ctx->locations());
		
		//std::cout << "There are " << locSet.size() << " locations" << std::endl;

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
