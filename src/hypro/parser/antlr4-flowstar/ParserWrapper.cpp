#include "ParserWrapper.h"


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
/*
	template<>
	boost::tuple<HybridAutomaton<mpq_class, State_t<mpq_class,mpq_class>>, ReachabilitySettings<mpq_class>> parseFlowstarFile<mpq_class>(const std::string& filename) {

		//Create an AnTLRInputStream
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

		//Create a parser
		HybridAutomatonParser parser(&tokens);
		parser.removeErrorListeners();
		parser.addErrorListener(errListener);
		tree::ParseTree* tree = parser.start();

		//Create TokenStreamRewriter, needed for constants if defined
		//std::cout << "Size of constant map: " << parser.getConstants().size() << std::endl;
		//for(auto entry : parser.getConstants()){
		//	std::cout << "Constant name: " << entry.first << " constant value " << entry.second << std::endl;
		//}

		if(parser.getConstants().size() > 0){
			TokenStreamRewriter rewriter(&tokens);
			std::string modified = replaceConstantsWithValues(rewriter, parser.getConstants());
			ANTLRInputStream inputMod(modified);
			HybridAutomatonLexer lexerMod(&inputMod);
			lexerMod.removeErrorListeners();
			lexerMod.addErrorListener(errListener);

			//Create an empty TokenStream obj
			CommonTokenStream tokensMod(&lexerMod);

			//Fill the TokenStream (and output it for demonstration)
			tokensMod.fill();

			//Create a parser
			HybridAutomatonParser parserMod(&tokensMod);
			parserMod.removeErrorListeners();
			parserMod.addErrorListener(errListener);
			tree::ParseTree* tree = parserMod.start();

			HyproHAVisitor<mpq_class> visitor;

			HybridAutomaton<mpq_class, State_t<mpq_class,mpq_class>> h = (visitor.visit(tree)).antlrcpp::Any::as<HybridAutomaton<mpq_class, State_t<mpq_class,mpq_class>>>();

			delete errListener;

			return boost::tuple<HybridAutomaton<mpq_class, State_t<mpq_class,mpq_class>>&, ReachabilitySettings<mpq_class>>(h, visitor.getSettings());

		} else {

			HyproHAVisitor<mpq_class> visitor;

			HybridAutomaton<mpq_class, State_t<mpq_class,mpq_class>> h = (visitor.visit(tree)).antlrcpp::Any::as<HybridAutomaton<mpq_class, State_t<mpq_class,mpq_class>>>();

			delete errListener;

			return boost::tuple<HybridAutomaton<mpq_class, State_t<mpq_class,mpq_class>>&, ReachabilitySettings<mpq_class>>(h, visitor.getSettings());
		}
	}
*/
	template<>
	//boost::tuple<HybridAutomaton<double,State_t<double,double>>, ReachabilitySettings<double>> parseFlowstarFile<double>(const std::string& filename) {
	std::pair<HybridAutomaton<double,State_t<double,double>>, ReachabilitySettings<double>> parseFlowstarFile<double>(const std::string& filename) {

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

		//Create a parser
		HybridAutomatonParser parser(&tokens);
		parser.removeErrorListeners();
		parser.addErrorListener(errListener);
		tree::ParseTree* tree = parser.start();

		//std::cout << "Size of constant map: " << parser.getConstants().size() << std::endl;
		//for(auto entry : parser.getConstants()){
		//	std::cout << "Constant name: " << entry.first << " constant value " << entry.second << std::endl;
		//}

		//Create TokenStreamRewriter, needed for constants if defined
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

			//Create a parser
			HybridAutomatonParser parserMod(&tokensMod);
			parserMod.removeErrorListeners();
			parserMod.addErrorListener(errListener);
			tree::ParseTree* tree = parserMod.start();

			HyproHAVisitor<double> visitor;

			HybridAutomaton<double, State_t<double,double>> h = (visitor.visit(tree)).antlrcpp::Any::as<HybridAutomaton<double, State_t<double,double>>>();

			delete errListener;

			//return boost::tuple<HybridAutomaton<double, State_t<double,double>>&, ReachabilitySettings<double>>(h, visitor.getSettings());
			return std::make_pair(std::move(h), visitor.getSettings());

		} else {

			HyproHAVisitor<double> visitor;

			HybridAutomaton<double, State_t<double,double>> h { std::move((visitor.visit(tree)).antlrcpp::Any::as<HybridAutomaton<double, State_t<double,double>>>()) };
			//HybridAutomaton<double, State_t<double,double>> h = std::move((visitor.visit(tree)).antlrcpp::Any::as<HybridAutomaton<double, State_t<double,double>>>());

			delete errListener;

			std::cout << "========== PARSERWRAPPER =============" << std::endl;
			std::cout << "Parsed HybridAutomaton Transitions:\n";
			for(const auto t : h.getTransitions()){
				std::cout << *t << std::endl;
			}
			std::cout << "Parsed HybridAutomaton Locations:\n";
			for(const auto l : h.getLocations()){
				std::cout << *l << std::endl;
			}
			//return boost::tuple<HybridAutomaton<double, State_t<double,double>>&, ReachabilitySettings<double>>(h, visitor.getSettings());
			return std::make_pair(std::move(h), visitor.getSettings());
		}
	}

} // namespace
