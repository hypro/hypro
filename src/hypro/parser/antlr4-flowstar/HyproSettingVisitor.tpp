#include "HyproSettingVisitor.h"

namespace hypro {

	////////////// Constructor & Destructor

	template<typename Number>
	HyproSettingVisitor<Number>::HyproSettingVisitor(std::vector<std::string> varVec) : 
		vars(varVec),
		plotDims()
	{ }

	template<typename Number>
	HyproSettingVisitor<Number>::~HyproSettingVisitor() { }

	////////////// Helping Functions

	template<typename Number>
	Number HyproSettingVisitor<Number>::toIntValue(Number& num){
		int converted = dynamic_cast<int>(num);
		return Number(converted);
	}

	////////////// Inherited

	template<typename Number>
	antlrcpp::Any HyproSettingVisitor<Number>::visitSetting(HybridAutomatonParser::SettingContext *ctx){

		std::cout << "-- Bin bei visitSetting!" << std::endl;

		//1.Go through all settings, collect data

		//fixed steps
		Number tStep = Number(1);
		if(ctx->fixedstep().size() > 1){
			std::cerr << "ERROR: fixed step in settings has been defined multiple times." << std::endl;
		} else if(ctx->fixedstep().size() == 1){
			tStep = visit(ctx->fixedstep());	
		} else {
			std::cerr << "ERROR: fixed step size has not been defined" << std::endl;
		}

		//time
		Number tBound = Number(0);
		if(ctx->time().size() > 1){
			std::cerr << "ERROR: time in settings has been defined multiple times." << std::endl;
		} else if(ctx->time().size() == 1){
			tBound = visit(ctx->time());	
		} else {
			std::cerr << "ERROR: time has not been defined" << std::endl;
		}

		//gnuplot octagon
		std::vector<std::vector<unsigned>> plotDims;
		if(ctx->plotsetting().size() >= 1){
			for(auto p : ctx->plotsetting()){
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
			name = visit(ctx->fileName());
		} else {
			std::cerr << "ERROR: filename has not been defined" << std::endl;
		}

		//maxjumps
		size_t jumps = 0;
		if(ctx->maxjumps().size() > 1){
			std::cerr << "ERROR: max jumps in settings has been defined multiple times." << std::endl;
		} else if(ctx->maxjumps().size() == 1){
			jumps = visit(ctx->maxjumps());		
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
		ReachabilitySettings r;
		r.timeStep = tStep;
		r.timeBound = tBound;
		r.plotDimensions = plotDims;
		r.fileName = name;
		r.jumpDepth = jumps;
		return r;
	}

	template<typename Number>
  	antlrcpp::Any HyproSettingVisitor<Number>::visitFixedsteps(HybridAutomatonParser::FixedstepsContext *ctx){

  		//Nur Zahlen >0 erlaubt
  		HyproFormulaVisitor<Number> h;
  		Number converted = h.stringToNumber(ctx->NUMBER()->getText());
  		if(converted <= Number(0)){
  			std::cerr << "ERROR: No numbers below or equal 0 are allowed when defining fixed steps." << std::endl;
  		}
  		return converted;
  	}

  	template<typename Number>
  	antlrcpp::Any HyproSettingVisitor<Number>::visitTime(HybridAutomatonParser::TimeContext *ctx){
  		//Alle Zahlen erlaubt
  		HyproFormulaVisitor<Number> h;
  		return h.stringToNumber(ctx->NUMBER()->getText());
  	}

  	template<typename Number>
  	antlrcpp::Any HyproSettingVisitor<Number>::visitPlotsetting(HybridAutomatonParser::PlotsettingContext *ctx){
  		
  		//TODO: schließe doppelte Variablen aus -> mitzählen wie oft variablen vorkommen

  		//0.Syntax Check - only declared variables?

  		//1.Find variable indices, push their indices into a vector of unsigned
  		
  	}

  	template<typename Number>
  	antlrcpp::Any HyproSettingVisitor<Number>::visitFilename(HybridAutomatonParser::FilenameContext *ctx){
  		return ctx->VARIABLE()->getText();
  	}

  	template<typename Number>
  	antlrcpp::Any HyproSettingVisitor<Number>::visitMaxjumps(HybridAutomatonParser::MaxjumpsContext *ctx){
  		
  		//Alle Zahlen erlaubt
  		HyproFormulaVisitor<Number> h;
  		Number num = h.stringToNumber(ctx->NUMBER()->getText());
  		return toIntValue(num);
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