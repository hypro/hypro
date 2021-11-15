#include "include/hypro/parser/antlr4-flowstar/ParserWrapper.h"

#include "include/hypro/parser/antlr4-flowstar/ErrorListener.h"
#include "include/hypro/parser/antlr4-flowstar/HybridAutomatonLexer.h"
#include "include/hypro/parser/antlr4-flowstar/HybridAutomatonParser.h"
#include "include/hypro/parser/antlr4-flowstar/HyproHAVisitor.h"


namespace hypro {
/*
	void cwd(){
		char cwd[1024];
	   	if (getcwd(cwd, sizeof(cwd)) != NULL)
	       fprintf(stdout, "Current working dir: %s\n", cwd);
	   	else
	       std::cerr << "getcwd() error" << std::endl;
	}
*/
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
			std::cout << "ifs hasn't opened anything" << std::endl;
		}
	}

	std::string replaceConstantsWithValues(TokenStreamRewriter& rewriter, std::map<std::string, std::string> constants){

		for(std::size_t i=0; i < rewriter.getTokenStream()->size(); i++){
			auto it = constants.find(rewriter.getTokenStream()->get(i)->getText());
			if(it != constants.end()){
				rewriter.replace(i, i, constants.at(it->first));
			}
		}
		//std::cout << "======== ALTERED VERSION =========\n" << rewriter.getText() << std::endl;
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
