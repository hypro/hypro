#include "Parser.h"

namespace hypro{
namespace parser{
	
	template<typename Number, typename Representation>
    HybridAutomaton<Number,Representation> MainParser<Number,Representation>::parseInput(const std::string& pathToInputFile)
    {
		HybridAutomaton<Number,Representation> resultAutomaton;
		
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
		
		std::cout << resultAutomaton << std::endl;
		
		return resultAutomaton;
    }

	template<typename Number, typename Representation>
    bool MainParser<Number,Representation>::parse(std::istream& in, const std::string& filename, HybridAutomaton<Number,Representation>& _result)
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
		//_result = std::move(createAutomaton());
		_result = createAutomaton();
		
        return result;
    }

	
	template<typename Number,typename Representation>
	HybridAutomaton<Number,Representation> MainParser<Number,Representation>::createAutomaton()
	{
		
		HybridAutomaton<Number,Representation> result;

		std::map<unsigned, hypro::Location<Number>* > locations;
		std::map<unsigned, hypro::Transition<Number>* > transitions;
		std::map<std::string, matrix<Number> > matrices;
		std::queue<State<Number>> incompleteStates;
		std::queue<Transition<Number>> incompleteTransitions;
		
		// set initial location - TODO
		std::cout << __func__ << " Initial: " << mInitial << std::endl;
		
		// get flow, first run
		for(const auto& state : mStates)
		{
			Location<Number>* loc = new Location<Number>();
			bool success = createLocFromState(state,loc,matrices,incompleteStates);
			if(success)
			{
				locations.insert(std::make_pair(state.mName, loc));
				result.addLocation(loc);
			}
			else
			{
				delete loc;
			}
		}
		
		// get transitions, first run
		for(const auto& transition : mTransitions)
		{
			hypro::Transition<Number>* tran = new hypro::Transition<Number>();
			bool success = createTransition(transition, tran, locations, matrices, incompleteTransitions);
			if(success)
			{
				transitions.insert(std::make_pair(transition.mName, tran));
				result.addTransition(tran);
			}
			else
			{
				delete tran;
			}
		}
		
		// process incomplete states
		std::queue<State<Number>> secondIncomplete;
		while(!incompleteStates.empty())
		{
			Location<Number>* loc = new Location<Number>();
			State<Number> state = incompleteStates.front();
			bool success = createLocFromState(state,loc,matrices,secondIncomplete);
			if(success)
			{
				locations.insert(std::make_pair(state.mName, loc));
				result.addLocation(loc);
			}
			else
			{
				delete loc;
			}
			incompleteStates.pop();
		}
		assert(incompleteStates.empty());
		assert(secondIncomplete.empty());
		
		// process incomplete transitions
		std::queue<Transition<Number>> secondIncompleteTransitions;
		while(!incompleteTransitions.empty())
		{
			hypro::Transition<Number>* tran = new hypro::Transition<Number>();
			Transition<Number> transition = incompleteTransitions.front();
			bool success = createTransition(transition,tran,locations,matrices,secondIncompleteTransitions);
			if(success)
			{
				transitions.insert(std::make_pair(transition.mName,tran));
				result.addTransition(tran);
			}
			else
			{
				delete tran;
			}
			incompleteTransitions.pop();
		}
		assert(incompleteTransitions.empty());
		assert(secondIncompleteTransitions.empty());
		
		//return std::move(result);
		return result;
	}
	
}
}
