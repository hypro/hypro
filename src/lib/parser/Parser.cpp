#include "Parser.h"

namespace hypro{
namespace parser{
    void MainParser::parseInput(const std::string& pathToInputFile)
    {
		HybridAutomaton<double> resultAutomaton;
		
        std::fstream infile( pathToInputFile );
        if( !infile.good() )
        {
            std::cerr << "Could not open file: " << pathToInputFile << std::endl;
            exit(1); // TODO: Create HyPro-specific Errorcodes
        }
        bool parsingSuccessful = parse( infile, pathToInputFile, resultAutomaton );
        if(!parsingSuccessful)
        {
            std::cerr << "Parse error" << std::endl;
            exit(1);
        }
    }

    bool MainParser::parse(std::istream& in, const std::string& filename, HybridAutomaton<double>& _result)
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
		
        std::cout << "To parse: " << std::string(begin, end) << std::endl;
        
		// create automaton from parsed result.
		_result = std::move(createAutomaton());
		
        return result;
    }

	
	HybridAutomaton<double> MainParser::createAutomaton()
	{
		
		HybridAutomaton<double> result;

		std::map<unsigned, hypro::Location<double>* > locations;
		std::map<unsigned, hypro::Transition<double>* > transitions;
		std::map<std::string, matrix > matrices;
		std::queue<State> incompleteStates;
		std::queue<Transition> incompleteTransitions;
		
		// get flow, first run
		for(const auto& state : mStates)
		{
			Location<double>* loc;
			bool success = createLocFromState(state,loc,matrices,incompleteStates);
			if(success)
			{
				locations.insert(std::make_pair(state.mName, loc));
				result.addLocation(loc);
			}
				
		}
		
		// get transitions, first run
		for(const auto& transition : mTransitions)
		{
			hypro::Transition<double>* tran;
			bool success = createTransition(transition, tran, locations, matrices, incompleteTransitions);
			if(success)
			{
				transitions.insert(std::make_pair(transition.mName, tran));
				result.addTransition(tran);
			}
		}
		
		// process incomplete states
		std::queue<State> secondIncomplete;
		while(!incompleteStates.empty())
		{
			Location<double>* loc = NULL;
			State state = incompleteStates.front();
			bool success = createLocFromState(state,loc,matrices,secondIncomplete);
			if(success)
			{
				locations.insert(std::make_pair(state.mName, loc));
				result.addLocation(loc);
			}
			incompleteStates.pop();
		}
		assert(incompleteStates.empty());
		assert(secondIncomplete.empty());
		
		// process incomplete transitions
		std::queue<Transition> secondIncompleteTransitions;
		while(!incompleteTransitions.empty())
		{
			hypro::Transition<double>* tran = NULL;
			Transition transition = incompleteTransitions.front();
			bool success = createTransition(transition,tran,locations,matrices,secondIncompleteTransitions);
			if(success)
			{
				transitions.insert(std::make_pair(transition.mName,tran));
				result.addTransition(tran);
			}
			incompleteTransitions.pop();
		}
		assert(incompleteTransitions.empty());
		assert(secondIncompleteTransitions.empty());
		
		return std::move(result);
	}
	
}
}