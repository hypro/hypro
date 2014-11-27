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
		std::queue<State> incompleteStates;
		
		// get flow
		for(auto& state : mStates)
		{
			std::string name = state.mName;
			std::string flowname = state.mFlow.mName;
			matrix flow;
			bool incomplete = false;
			if(flowname != "")
			{
				auto pos = matrices.find(flowname);
				if(pos == matrices.end())
				{
					if(!state.mFlow.mMatrix.empty())
					{
						flow = createMatrix(state.mFlow.mMatrix);
						matrices.insert(std::make_pair(flowname, flow));
					}
					else
					{
						incomplete = true;
					}
				}
				else
				{
					assert(state.mFlow.mMatrix.empty());
					flow = (*pos).second;
				}
			}
			else
			{
				flow = createMatrix(state.mFlow.mMatrix);
			}
			
			// get invariant
			std::string invname = state.mInvariant.mName;
			matrix invMatrix;
			if(invname != "")
			{
				auto pos = matrices.find(invname);
				if(pos == matrices.end())
				{
					if(!state.mInvariant.mMatrix.empty())
					{
						invMatrix = createMatrix(state.mInvariant.mMatrix);
						matrices.insert(std::make_pair(invname, flow));
					}
					else
					{
						incomplete = true;
					}
				}
				else
				{
					assert(state.mInvariant.mMatrix.empty());
					invMatrix = (*pos).second;
				}
			}
			else
			{
				invMatrix = createMatrix(state.mFlow.mMatrix);
			}
			
			// Todo: do we always compare with lesseq 0?
			//vector vec = vector();
			//vec = Eigen::DenseBase<typename Derived>::Zero(invMatrix.rows());
			/*
			if(!incomplete)
			{
				Location<double> loc;
				loc.setActivityMat(flow);
				loc.setInvariant(invMatrix, vec, hypro::operator_e::LEQ);
				
				// enlist loc
				locations.insert(std::make_pair(name, loc));
			}
			else
			{
				incompleteStates.push(state);
			}
			 */ 
		}
		
		return result;
	}
	
}
}