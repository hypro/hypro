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

	template<>
	boost::tuple<HybridAutomaton<mpq_class>, ReachabilitySettings<mpq_class>> parseFlowstarFile<mpq_class>(const std::string& filename) {

		//Create an AnTLRInputStream
		ANTLRInputStream input;
		openFile(filename,input);

		//Create Error Listener
		hypro::ErrorListener* errListener = new hypro::ErrorListener();

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

		//Create TokenStreamRewriter, needed for constants if defined
		if(parser.getConstants().size() > 0){
			TokenStreamRewriter rewriter(&tokens);	
		}

		tree::ParseTree* tree = parser.start();

		hypro::HyproHAVisitor<mpq_class> visitor;

		hypro::HybridAutomaton<mpq_class> h = (visitor.visit(tree)).antlrcpp::Any::as<hypro::HybridAutomaton<mpq_class>>();

		delete errListener;

		return boost::tuple<HybridAutomaton<mpq_class>&, ReachabilitySettings<mpq_class>>(h, visitor.getSettings());
	}

	template<>
	boost::tuple<HybridAutomaton<double>, ReachabilitySettings<double>> parseFlowstarFile<double>(const std::string& filename) {
	
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

		hypro::HyproHAVisitor<double> visitor;

		hypro::HybridAutomaton<double> h = (visitor.visit(tree)).antlrcpp::Any::as<hypro::HybridAutomaton<double>>();

		delete errListener;

		return boost::tuple<HybridAutomaton<double>, ReachabilitySettings<double>>(h, visitor.getSettings());
	}

} // namespace
