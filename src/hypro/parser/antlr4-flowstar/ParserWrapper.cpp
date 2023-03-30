/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "antlr4-flowstar/ParserWrapper.h"

#include "antlr4-flowstar/ErrorListener.h"
#include "antlr4-flowstar/HybridAutomatonLexer.h"
#include "antlr4-flowstar/HybridAutomatonParser.h"
#include "antlr4-flowstar/HyproHAVisitor.h"


namespace hypro {
	void openFile(const std::string& filename, ANTLRInputStream& input) {

		std::fstream ifs(filename);
		//cwd();

		if(ifs.good()){
			input = ANTLRInputStream(ifs);
		} else {
			std::cerr << "InputStream was bad." << std::endl;
			if(ifs.fail()){
				std::cerr << "Failbit was set" << std::endl;
			}
			if(ifs.eof()){
				std::cerr << "EOFbit was set" << std::endl;
			}
			if(ifs.bad()){
				std::cerr << "Badbit was set" << std::endl;
			}
		}
		if(!ifs.is_open()){
			throw std::logic_error("Input file " + filename +
" could not be opened.");
		}
	}

	std::string replaceConstantsWithValues(TokenStreamRewriter& rewriter, std::map<std::string, std::string> constants){

		for(std::size_t i=0; i < rewriter.getTokenStream()->size(); i++){
			auto it = constants.find(rewriter.getTokenStream()->get(i)->getText());
			if(it != constants.end()){
				rewriter.replace(i, i, constants.at(it->first));
			}
		}
		return rewriter.getText();
	}

	template<>
	std::pair<HybridAutomaton<mpq_class>, ReachabilitySettings> parseFlowstarFile<mpq_class>(const std::string& filename) {

		//Create an ANTLRInputStream
		ANTLRInputStream input;
		openFile(filename,input);

		//Create Error Listener
		ErrorListener* errListener = new ErrorListener();

		//Create a Lexer and feed it with the input
		HybridAutomatonLexer lexer(&input);
		lexer.removeErrorListeners();
		lexer.addErrorListener(errListener);

		//Create an empty TokenStream obj
		CommonTokenStream tokens(&lexer);

		//Fill the TokenStream (and output it for demonstration)
		tokens.fill();

		//Create a parser with error listener
		HybridAutomatonParser parser(&tokens);
		parser.removeErrorListeners();
		parser.addErrorListener(errListener);
		tree::ParseTree* tree = parser.start();

		//Create TokenStreamRewriter, needed for constants if defined
		//Replace constants with their values, then parse again
		if(parser.getConstants().size() > 0){
			TokenStreamRewriter rewriter(&tokens);
			std::string modified = replaceConstantsWithValues(rewriter, parser.getConstants());
			ANTLRInputStream inputMod(modified);
			HybridAutomatonLexer lexerMod(&inputMod);
			lexerMod.removeErrorListeners();
			lexerMod.addErrorListener(errListener);

			//Create an empty TokenStream obj
			CommonTokenStream tokensMod(&lexerMod);

			//Fill the TokenStream
			tokensMod.fill();

			//Create a parser with error listener
			HybridAutomatonParser parserMod(&tokensMod);
			parserMod.removeErrorListeners();
			parserMod.addErrorListener(errListener);
			tree::ParseTree* tree = parserMod.start();

			HyproHAVisitor<mpq_class> visitor;

			//HybridAutomaton<mpq_class> h = (visitor.visit(tree)).antlrcpp::Any::as<HybridAutomaton<mpq_class>>();
			HybridAutomaton<mpq_class> h { std::move((visitor.visit(tree)).antlrcpp::Any::as<HybridAutomaton<mpq_class>>()) };

			delete errListener;

			//return std::tuple<HybridAutomaton<double>&, ReachabilitySettings>(h, visitor.getSettings());
			return std::make_pair(std::move(h), visitor.getSettings());

		} else {

			HyproHAVisitor<mpq_class> visitor;

			//HybridAutomaton<double> h = std::move((visitor.visit(tree)).antlrcpp::Any::as<HybridAutomaton<double>>());
			HybridAutomaton<mpq_class> h { std::move((visitor.visit(tree)).antlrcpp::Any::as<HybridAutomaton<mpq_class>>()) };

			delete errListener;

			//return std::tuple<HybridAutomaton<double>&, ReachabilitySettings>(h, visitor.getSettings());
			return std::make_pair(std::move(h), visitor.getSettings());
		}
	}


	template<>
	std::pair<HybridAutomaton<double>, ReachabilitySettings> parseFlowstarFile<double>(const std::string& filename) {

		//Create an ANTLRInputStream
		ANTLRInputStream input;
		openFile(filename,input);

		//Create Error Listener
		ErrorListener* errListener = new ErrorListener();

		//Create a Lexer and feed it with the input
		HybridAutomatonLexer lexer(&input);
		lexer.removeErrorListeners();
		lexer.addErrorListener(errListener);

		//Create an empty TokenStream obj
		CommonTokenStream tokens(&lexer);

		//Fill the TokenStream (and output it for demonstration)
		tokens.fill();

		//Create a parser with error listener
		HybridAutomatonParser parser(&tokens);
		parser.removeErrorListeners();
		parser.addErrorListener(errListener);
		tree::ParseTree* tree = parser.start();

		//Create TokenStreamRewriter, needed for constants if defined
		//Replace constants with their values, then parse again
		if(parser.getConstants().size() > 0){
			TokenStreamRewriter rewriter(&tokens);
			std::string modified = replaceConstantsWithValues(rewriter, parser.getConstants());
			ANTLRInputStream inputMod(modified);
			HybridAutomatonLexer lexerMod(&inputMod);
			lexerMod.removeErrorListeners();
			lexerMod.addErrorListener(errListener);

			//Create an empty TokenStream obj
			CommonTokenStream tokensMod(&lexerMod);

			//Fill the TokenStream
			tokensMod.fill();

			//Create a parser with error listener
			HybridAutomatonParser parserMod(&tokensMod);
			parserMod.removeErrorListeners();
			parserMod.addErrorListener(errListener);
			tree::ParseTree* tree = parserMod.start();

			HyproHAVisitor<double> visitor;

			HybridAutomaton<double> h { std::move((visitor.visit(tree)).antlrcpp::Any::as<HybridAutomaton<double>>()) };

			delete errListener;

			return std::make_pair(std::move(h), visitor.getSettings());

		} else {

			HyproHAVisitor<double> visitor;

			HybridAutomaton<double> h { std::move((visitor.visit(tree)).antlrcpp::Any::as<HybridAutomaton<double>>()) };

			delete errListener;

			return std::make_pair(std::move(h), visitor.getSettings());
		}
	}

} // namespace
