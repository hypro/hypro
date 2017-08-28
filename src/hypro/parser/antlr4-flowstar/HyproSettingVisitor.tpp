#include "HyproSettingVisitor.h"

namespace hypro {

	////////////// Constructor & Destructor

	template<typename Number>
	HyproSettingVisitor<Number>::HyproSettingVisitor(std::vector<std::string>& varVec) : 
		vars(varVec)
	{ }

	template<typename Number>
	HyproSettingVisitor<Number>::~HyproSettingVisitor() { }

	////////////// Inherited

	template<typename Number>
	antlrcpp::Any HyproSettingVisitor<Number>::visitSetting(HybridAutomatonParser::SettingContext *ctx){

		std::cout << "-- Bin bei visitSetting!" << std::endl;

		//1.Go through all settings, collect data

		//fixed steps
		Number tStep = Number(1);
		if(ctx->fixedsteps().size() > 1){
			std::cerr << "ERROR: fixed step in settings has been defined multiple times." << std::endl;
		} else if(ctx->fixedsteps().size() == 1){
			tStep = visit(ctx->fixedsteps()[0]).antlrcpp::Any::as<Number>();
		} else {
			std::cerr << "ERROR: fixed step size has not been defined" << std::endl;
		}

		//time
		Number tBound = Number(0);
		if(ctx->time().size() > 1){
			std::cerr << "ERROR: time in settings has been defined multiple times." << std::endl;
		} else if(ctx->time().size() == 1){
			tBound = visit(ctx->time()[0]).antlrcpp::Any::as<Number>();
		} else {
			std::cerr << "ERROR: time has not been defined" << std::endl;
		}

		//gnuplot octagon
		std::vector<std::vector<unsigned>> plotDims;
		if(ctx->plotsetting().size() >= 1){
			for(const auto& p : ctx->plotsetting()){
				std::vector<unsigned> plotDimTupel = visit(p);
				plotDims.push_back(plotDimTupel);
			}
		} else {
			std::cerr << "ERROR: gnuplot octagon has not been defined" << std::endl;
		}

		//filename
		std::string name;
		if(ctx->filename().size() > 1){
			std::cerr << "ERROR: filename in settings has been defined multiple times." << std::endl;
		} else if(ctx->filename().size() == 1){
			name = visit(ctx->filename()[0]).antlrcpp::Any::as<std::string>();
		} else {
			std::cerr << "ERROR: filename has not been defined" << std::endl;
		}

		//maxjumps
		int jumps = 0;
		if(ctx->maxjumps().size() > 1){
			std::cerr << "ERROR: max jumps in settings has been defined multiple times." << std::endl;
		} else if(ctx->maxjumps().size() == 1){
			jumps = visit(ctx->maxjumps()[0]);
		} else {
			std::cerr << "ERROR: max jumps has not been defined" << std::endl;
		}

		//remainder
		//identity
		//fixedorders
		//cutoff
		//precision
		//print

		//2.Build ReachabilitySettings and return it.
		std::cout << "-- Building reachability settings" << std::endl;
		ReachabilitySettings<Number> r;
		r.timeStep = tStep;
		r.timeBound = tBound;
		r.plotDimensions = plotDims;
		r.fileName = name;
		r.jumpDepth = jumps;
		return r;
	}

	template<typename Number>
  	antlrcpp::Any HyproSettingVisitor<Number>::visitFixedsteps(HybridAutomatonParser::FixedstepsContext *ctx){

  		std::cout << "-- Bin bei visitFixedsteps!" << std::endl;

  		//Nur Zahlen >0 erlaubt
  		HyproFormulaVisitor<Number> h(vars);
  		Number converted = h.stringToNumber(ctx->NUMBER()->getText());
  		if(converted <= Number(0)){
  			std::cerr << "ERROR: No numbers below or equal 0 are allowed when defining fixed steps." << std::endl;
  		}
  		return converted;
  	}

  	template<typename Number>
  	antlrcpp::Any HyproSettingVisitor<Number>::visitTime(HybridAutomatonParser::TimeContext *ctx){
  		//Alle Zahlen erlaubt
  		HyproFormulaVisitor<Number> h(vars);
  		return h.stringToNumber(ctx->NUMBER()->getText());
  	}

  	template<typename Number>
  	antlrcpp::Any HyproSettingVisitor<Number>::visitPlotsetting(HybridAutomatonParser::PlotsettingContext *ctx){

  		std::cout << "-- Bin bei visitPlotsetting!" << std::endl;

  		//0.Syntax Check - only declared variables?
  		bool found = false;
  		for(const auto& maybeVar : ctx->VARIABLE()){
  			std::string culprit = maybeVar->getText();
  			for(const auto& var : vars){
  				if(var == maybeVar->getText()){
  					found = true;
  				}
  			}
  			if(!found){
  				std::cerr << "ERROR: variable " << culprit << " in gnuplot octagon has not been defined in state var." << std::endl;
  			}
  		}

  		//1.Count how often variables occur and throw error if a variable is mentioned more than one time
  		std::vector<unsigned> varCount;
  		for(unsigned i=0; i < vars.size(); i++){
  			varCount.push_back(0);
  		}
  		std::size_t startIndex = ctx->start->getStartIndex();
  		std::size_t endIndex = ctx->stop->getStopIndex();
  		misc::Interval inter(startIndex, endIndex);
  		CharStream* input = ctx->start->getInputStream();
  		std::string text = input->getText(inter);
  		for(unsigned i=0; i < vars.size(); i++){
  			unsigned pos = text.find(vars[i]);
  			if(pos != std::string::npos){
  				varCount[i]++;
  				text = text.erase(pos, vars[i].size());
  			}
  		}
  		for(unsigned i=0; i < varCount.size(); i++){
  			if(varCount[i] > 1){
  				std::cerr << "ERROR: Variable " << vars[i] << "has been mentioned multiple times in gnuplot octagon. Please mention every variable at most one time." << std::endl;
  			}
  		}

  		//2.Find variable indices, push their indices into a vector of unsigned
  		std::vector<unsigned> res;
  		for(const auto& maybeVar : ctx->VARIABLE()){
  			for(unsigned i=0; i < vars.size(); i++){
  				if(maybeVar->getText() == vars[i]){
  					res.push_back(i);
  				}
  			}
  		}
  		return res;
  	}

  	template<typename Number>
  	antlrcpp::Any HyproSettingVisitor<Number>::visitFilename(HybridAutomatonParser::FilenameContext *ctx){
  		std::cout << "-- Bin bei visitFilename!" << std::endl;
  		return ctx->VARIABLE()->getText();
  	}

  	template<typename Number>
  	antlrcpp::Any HyproSettingVisitor<Number>::visitMaxjumps(HybridAutomatonParser::MaxjumpsContext *ctx){
  		std::cout << "-- Bin bei visitMaxjumps!" << std::endl;
  		//Only integers allowed
  		std::string numAsText = ctx->NUMBER()->getText();
  		std::cout << "---- num before: " << numAsText << std::endl;
  		unsigned pos = numAsText.find(".");
		if(pos != std::string::npos){
			numAsText = std::string(numAsText, 0, pos);
		}
		std::cout << "---- num after: " << numAsText << std::endl;
		return std::stoi(numAsText);
  	}
/*
  	template<typename Number>
  	antlrcpp::Any HyproSettingVisitor<Number>::visitPrint(HybridAutomatonParser::PrintContext *ctx){

  	}

  	template<typename Number>
  	antlrcpp::Any HyproSettingVisitor<Number>::visitRemainder(HybridAutomatonParser::RemainderContext *ctx){

  	}

  	template<typename Number>
  	antlrcpp::Any HyproSettingVisitor<Number>::visitIdentity(HybridAutomatonParser::IdentityContext *ctx){

  	}

  	template<typename Number>
  	antlrcpp::Any HyproSettingVisitor<Number>::visitFixedorders(HybridAutomatonParser::FixedordersContext *ctx){

  	}

  	template<typename Number>
  	antlrcpp::Any HyproSettingVisitor<Number>::visitCutoff(HybridAutomatonParser::CutoffContext *ctx){

  	}

  	template<typename Number>
  	antlrcpp::Any HyproSettingVisitor<Number>::visitPrecision(HybridAutomatonParser::PrecisionContext *ctx){

  	}
*/
}
