/*
 * HyproSettingVisitor.h
 *
 * Collects information from given settings
 * in order to build a HybridAutomaton.
 *
 * @author Phillip Tse
 * @date 17.8.2017
 */

#pragma once

#include "../../types.h"
#include "HybridAutomatonLexer.h"
#include "HybridAutomatonParser.h"
#include "HybridAutomatonBaseVisitor.h"
#include "HyproFormulaVisitor.h"
#include "../../datastructures/reachability/Settings.h"
#include <math.h>

using namespace antlr4;

namespace hypro {

template<typename Number>
class HyproHAVisitor;

template<typename Number>
class HyproSettingVisitor : HybridAutomatonBaseVisitor {

	friend class HyproHAVisitor<Number>;

	private:

		//A vector of all variables that are defined
		std::vector<std::string>& vars;

        //Inherited
        antlrcpp::Any visitFixedsteps(HybridAutomatonParser::FixedstepsContext *ctx) override;
        antlrcpp::Any visitTime(HybridAutomatonParser::TimeContext *ctx) override;
        antlrcpp::Any visitPlotsetting(HybridAutomatonParser::PlotsettingContext *ctx) override;
        antlrcpp::Any visitFilename(HybridAutomatonParser::FilenameContext *ctx) override;
        antlrcpp::Any visitMaxjumps(HybridAutomatonParser::MaxjumpsContext *ctx) override;
/*          
        antlrcpp::Any visitPrint(HybridAutomatonParser::PrintContext *ctx) override;
        antlrcpp::Any visitRemainder(HybridAutomatonParser::RemainderContext *ctx) override;
        antlrcpp::Any visitIdentity(HybridAutomatonParser::IdentityContext *ctx) override;
        antlrcpp::Any visitFixedorders(HybridAutomatonParser::FixedordersContext *ctx) override;
        antlrcpp::Any visitCutoff(HybridAutomatonParser::CutoffContext *ctx) override;
        antlrcpp::Any visitPrecision(HybridAutomatonParser::PrecisionContext *ctx) override;
*/

	public:

        //Constructor & Destructor
        HyproSettingVisitor(std::vector<std::string>& varVec);
        ~HyproSettingVisitor();

		//Inherited - stays public so we can access it for testing/debugging
		antlrcpp::Any visitSetting(HybridAutomatonParser::SettingContext *ctx) override;

};

} //namespace hypro

#include "HyproSettingVisitor.tpp"
