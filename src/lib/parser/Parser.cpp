#include "Parser.h"

namespace hypro{
namespace parser{
    void MainParser::parseInput(const std::string& pathToInputFile)
    {
        std::fstream infile( pathToInputFile );
        if( !infile.good() )
        {
            std::cerr << "Could not open file: " << pathToInputFile << std::endl;
            exit(1); // TODO: Create HyPro-specific Errorcodes
        }
        bool parsingSuccessful = parse( infile, pathToInputFile );
        if(!parsingSuccessful)
        {
            std::cerr << "Parse error" << std::endl;
            exit(1);
        }
    }

    bool MainParser::parse(std::istream& in, const std::string& filename)
    {
        in.unsetf(std::ios::skipws);
        BaseIteratorType basebegin(in);
        Iterator begin(basebegin);
        Iterator end;
        Skipper skipper;
        
        std::cout << "To parse: " << std::string(begin, end) << std::endl;
        // invoke qi parser
        bool result = qi::phrase_parse(begin, end, main, skipper);
        
        std::cout << "Result: Done" << std::endl;
		
		for(auto& state : mStates)
		{
			std::cout << state << std::endl;
		}
        
        std::cout << "To parse: " << std::string(begin, end) << std::endl;
        
		// create automaton from parsed result.
		
        return result;
    }
	
	HybridAutomaton<double> MainParser::createAutomaton()
	{
		HybridAutomaton<double> result;
		
		std::map<std::string, Location<double> > locations;
		std::map<std::string, matrix > matrices;
		
		for(auto& state : mStates)
		{
			matrix flow = createMatrix(state.mFlow.mMatrix);
			std::string name = state.mFlow.mName;
			if(name != "")
			{
				bool inserted = matrices.insert(std::make_pair(name, flow)).second;
				assert(inserted);
			}
		}
		
		return result;
	}
}
}