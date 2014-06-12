#include "Parser.h"

namespace hypro{
namespace parser{
    void HyproParser::parseInput(const std::string& pathToInputFile)
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

    bool HyproParser::parse(std::istream& in, const std::string& filename)
    {
        in.unsetf(std::ios::skipws);
        BaseIteratorType basebegin(in);
        Iterator begin(basebegin);
        Iterator end;
        Skipper skipper;
        Automaton resultAutomaton;
        
        // invoke qi parser
        bool result = qi::phrase_parse(begin, end, main, skipper, resultAutomaton);
        
        std::cout << "Result: " << resultAutomaton << std::endl;
        
        std::cout << "To parse: " << std::string(begin, end) << std::endl;
        
        return result;
    }
}
}