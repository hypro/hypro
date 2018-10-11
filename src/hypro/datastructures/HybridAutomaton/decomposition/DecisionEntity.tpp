#include "DecisionEntity.h"
namespace hypro
{
	template<typename Number>
	bool DecisionEntity<Number>::isDiscreteSubspace(const Location<Number> &loc, size_t index){
		if(loc.getFlow(index) == matrix_t<Number>::Zero(loc.getFlow(index).rows(), loc.getFlow(index).cols())){
			return true;
		}
		return false;
	}

	template<typename Number>
	bool DecisionEntity<Number>::isTimedSubspace(const Location<Number> &loc, size_t index){
		TRACE("hypro.decisionEntity", "Investigating " << loc.getName());
		// check if flow is of the form
		//	0 ... 0 1
		//  .........
		//	0 ... 0 1
		//  0 ....0 0
		matrix_t<Number> flow = loc.getFlow(index);
		for(int i=0; i < flow.rows()-1; i++){
			matrix_t<Number> expected = matrix_t<Number>::Zero(1, flow.cols());
			expected(0,flow.cols()-1) = Number(1.0);
			if(flow.row(i) != expected){
				TRACE("hypro.decisionEntitiy","Flow row does not match.");
				TRACE("hypro.decisionEntitiy","Is: 		 " << flow.row(i));
				TRACE("hypro.decisionEntitiy","Expected: " << expected);
				return false;
			}
		}
		matrix_t<Number> expectedLastRow = matrix_t<Number>::Zero(1, flow.cols());
		if(flow.row(flow.rows()-1) != expectedLastRow){
			TRACE("hypro.decisionEntitiy","Flow last row does not match.");
			return false;
		}


		// check if the constraints of the invariant set only contain 0s and one entry 1/-1 at most
		if(loc.getInvariant().size() > 0){
			matrix_t<Number> invariant = loc.getInvariant().getMatrix(index);
			for(int i = 0; i < invariant.rows(); i++){
				matrix_t<Number> row = invariant.row(i);
				int counter = 0;
				for(int j = 0; j < row.cols(); j++){
					if(row(0,j) == 1.0 || row(0,j) == -1.0){
						counter++;
					}
					else if(row(0,j) != 0.0){
						//something else
						TRACE("hypro.decisionEntitiy","Invariant row has coefficient not equal to -1,0,1.");
						return false;
					}
				}
				if(counter > 1){
					TRACE("hypro.decisionEntitiy","Invariant row has more than one coefficient equal to -1,1.");
					return false;
				}
			}
		}

		std::set<Transition<Number>*> transitions = loc.getTransitions();
		for(auto transition : transitions){
			TRACE("hypro.decisionEntity", "Investigating " << transition->getSource()->getName() << " -> " << transition->getTarget()->getName());

			// for each transitions check if the constraints of the guard set only only contain 0s and one entry 1/-1 at most

			if(transition->getGuard().size() > 0){
				matrix_t<Number> guard = transition->getGuard().getMatrix(index);
				for(int i = 0; i < guard.rows(); i++){
					matrix_t<Number> row = guard.row(i);
					int counter = 0;
					for(int j = 0; j < row.cols(); j++){
						if(row(0,j) == 1.0 || row(0,j) == -1.0){
							counter++;
						}
						else if(row(0,j) != 0.0){
							//something else
							TRACE("hypro.decisionEntitiy","Guard row has coefficient not equal to -1,0,1.");
							return false;
						}
					}
					if(counter > 1){
						TRACE("hypro.decisionEntitiy","Guard row has more than one coefficient equal to -1,1.");
						return false;
					}
				}
			}


			// check if for each transition the reset function is of the form
			//
			//	0/1	 0  ...  0 | 0
			//	0  0/1 0 ... 0 | 0
			//	..................
			//  0 ...... 0 0/1 | 0
			if(transition->getReset().size() > 0){
				matrix_t<Number> reset = transition->getReset().getMatrix(index);
				for(int i=0; i < reset.rows(); i++){
					matrix_t<Number> expected0 = matrix_t<Number>::Zero(1, reset.cols());
					matrix_t<Number> expected1 = matrix_t<Number>::Zero(1, reset.cols());
					expected1(0,i) = Number(1.0);
					if(!(reset.row(i) == expected0 || reset.row(i) == expected1)){
						TRACE("hypro.decisionEntitiy","Reset matrix rows do not match.");
						return false;
					}
				}
			}

			if(transition->getReset().size() > 0){
				matrix_t<Number> reset = transition->getReset().getVector(index);
				if(reset != matrix_t<Number>::Zero(reset.rows(), 1)){
					TRACE("hypro.decisionEntitiy","Reset vector rows do not reset to zero.");
					return false;
				}
			}


		}
		TRACE("hypro.decisionEntitiy","Is timed.");
		return true;
	}

	template<typename Number>
	bool DecisionEntity<Number>::isTimedLocation(const Location<Number> &loc){
		bool isTimed = true;
		TRACE("hypro.decisionEntity", "Investigating " << loc.getName());
		// check if flow is of the form
		//	0 ... 0 1
		//  .........
		//	0 ... 0 1
		//  0 ....0 0
		if(isTimed){
			for(size_t i = 0; i < loc.getNumberFlow();i++){
				matrix_t<Number> flow = loc.getFlow(i);
				for(int i=0; i < flow.rows()-1; i++){
					matrix_t<Number> expected = matrix_t<Number>::Zero(1, flow.cols());
					expected(0,flow.cols()-1) = Number(1.0);
					if(flow.row(i) != expected){
						isTimed = false;
					}
				}
				matrix_t<Number> expectedLastRow = matrix_t<Number>::Zero(1, flow.cols());
				if(flow.row(flow.rows()-1) != expectedLastRow){
					isTimed = false;
				}

				if(!isTimed){
					break;
				}
			}
		}

		// check if the constraints of the invariant set only contain 0s and one entry 1/-1 at most
		if(isTimed){
			for(size_t i=0; i< loc.getInvariant().size(); i++){
				matrix_t<Number> invariant = loc.getInvariant().getMatrix(i);
				for(int i = 0; i < invariant.rows(); i++){
					matrix_t<Number> row = invariant.row(i);
					int counter = 0;
					for(int j = 0; j < row.cols(); j++){
						if(row(0,j) == 1.0 || row(0,j) == -1.0){
							counter++;
						}
						else if(row(0,j) != 0.0){
							//something else
							isTimed=false;
						}
					}
					if(counter > 1){
						isTimed = false;
					}
				}

				if(!isTimed){
					break;
				}
			}
		}

		std::set<Transition<Number>*> transitions = loc.getTransitions();
		for(auto transition : transitions){
			TRACE("hypro.decisionEntity", "Investigating " << transition->getSource()->getName() << " -> " << transition->getTarget()->getName());

			// for each transitions check if the constraints of the guard set only only contain 0s and one entry 1/-1 at most
			if(isTimed){
				for(size_t i=0; i< transition->getGuard().size(); i++){
					matrix_t<Number> guard = transition->getGuard().getMatrix(i);
					for(int i = 0; i < guard.rows(); i++){
						matrix_t<Number> row = guard.row(i);
						int counter = 0;
						for(int j = 0; j < row.cols(); j++){
							if(row(0,j) == 1.0 || row(0,j) == -1.0){
								counter++;
							}
							else if(row(0,j) != 0.0){
								//something else
								isTimed=false;
							}
						}
						if(counter > 1){
							isTimed = false;
						}
					}

					if(!isTimed){
						break;
					}
				}
			}

			// check if for each transition the reset function is of the form
			//
			//	0/1	 0  ...  0 | 0
			//	0  0/1 0 ... 0 | 0
			//	..................
			//  0 ...... 0 0/1 | 0
			if(isTimed){
				for(size_t i=0; i< transition->getReset().size(); i++){
					matrix_t<Number> reset = transition->getReset().getMatrix(i);
					for(int i=0; i < reset.rows(); i++){
						matrix_t<Number> expected0 = matrix_t<Number>::Zero(1, reset.cols());
						matrix_t<Number> expected1 = matrix_t<Number>::Zero(1, reset.cols());
						expected1(0,i) = Number(1.0);
						if(!(reset.row(i) == expected0 || reset.row(i) == expected1)){
							isTimed = false;
						}
					}

					if(!isTimed){
						break;
					}
				}
			}


			if (isTimed){
				for(size_t i=0; i< transition->getReset().size(); i++){
					matrix_t<Number> reset = transition->getReset().getVector(i);
					if(reset != matrix_t<Number>::Zero(reset.rows(), 1)){
						isTimed = false;
					}


					if(!isTimed){
						break;
					}
				}
			}

		}

		return isTimed;
	}

	template<typename Number>
	bool DecisionEntity<Number>::isTimedAutomaton(const HybridAutomaton<Number> &ha){
		std::set<Location<Number>*> locations = ha.getLocations();
		bool isTimed = true;

		for(auto location : locations){
			isTimed &= isTimedLocation(*location);
			if(!isTimed){
				break;
			}
		}
		return isTimed;
	}

	template<typename Number>
	bool DecisionEntity<Number>::checkDecomposed(const HybridAutomaton<Number> &automaton){
		typename HybridAutomaton<Number>::locationStateMap initialStates = automaton.getInitialStates();
		for (auto stateMapIt = initialStates.begin(); stateMapIt != initialStates.end(); ++stateMapIt) {
			if(stateMapIt->second.getNumberSets() > 1){
				return true;
			}
		}
		return false;
	}


    template<typename Number>
	void DecisionEntity<Number>::addEdgesForAffineTrafo(matrix_t<Number> affineTrafo,boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>& graph){
		matrix_t<Number>tmp(affineTrafo);
		// we do not consider the constant part of the trafo
    	tmp.conservativeResize(tmp.rows()-1, tmp.cols()-1);

    	for(size_t i = 0; i < tmp.rows(); i++){
			for(size_t j = 0; j < tmp.cols(); j++){
				if(tmp(i,j) != 0){
					boost::add_edge(i,j,graph);
				}
			}
		}
    }

    template<typename Number>
	void DecisionEntity<Number>::addEdgesForLinTrafo(matrix_t<Number> linTrafo,boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>& graph){
    	for(size_t i = 0; i < linTrafo.rows(); i++){
			for(size_t j = 0; j < linTrafo.cols(); j++){
				if(linTrafo(i,j) != 0){
					boost::add_edge(i,j,graph);
				}
			}
		}
    }

    template<typename Number>
	void DecisionEntity<Number>::addEdgesForCondition(Condition<Number> condition,boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>& graph){
    	if(!(condition.size() > 0)){
    		//empty condition (e.g. location with no invariant) --> do nothing
    		return;
    	}
    	matrix_t<Number> tmp(condition.getMatrix());

    	for(size_t i = 0; i < tmp.rows(); i++){
			//pairwise comparison of the row entries
			for(size_t j = 0; j < tmp.cols();j++){
				for(size_t k = 0; k < tmp.cols(); k++){

					//Example:
					// row i: 0,0,2,0,0,-4
					//            j      k
					// => j and k are dependent
					if(tmp(i,j) != 0 && tmp(i,k) != 0){
						boost::add_edge(j,k,graph);
					}
				}
			}
		}
    }

	template<typename Number>
	void DecisionEntity<Number>::printDecomposition(const Decomposition& decomposition){
		int i = 0;
		for(auto bucket : decomposition){
			std::cout << "Decomposition " << i << ": " <<std::endl;
			TRACE("hypro.decisionEntity", "Decomposition " << i << ":");
			for(auto var : bucket){
				std::cout << "Var " << var << std::endl;
				TRACE("hypro.decisionEntity", "Var " << var);
			}
			i++;
		}
	}


	template<typename Number>
	Decomposition  DecisionEntity<Number>::getSubspaceDecomposition(const HybridAutomaton<Number> &automaton){
		if(checkDecomposed(automaton)){
			// return empty decomposition
			return Decomposition();
		}
		typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;
		Graph G(automaton.dimension()-1);

		//check flow and invariant of locations
		std::set<Location<Number>*> locations = automaton.getLocations();
		for(auto loc : locations){
			addEdgesForAffineTrafo(loc->getFlow(), G);
			addEdgesForCondition(loc->getInvariant(),G);
		}

		//check reset and guards of transitions
		std::set<Transition<Number>*> transitions = automaton.getTransitions();
		for(auto transition : transitions){

			addEdgesForLinTrafo(transition->getReset().getMatrix(), G);
			addEdgesForCondition(transition->getGuard(),G);
		}

		//check local bad states
		const std::map<const Location<Number>*, Condition<Number>> localBadstates = automaton.getLocalBadStates();
		for(auto it = localBadstates.begin(); it != localBadstates.end(); ++it){
			addEdgesForCondition(it->second, G);
		}
		//check global bad states
		std::vector<Condition<Number>> globalBadStateConditions = automaton.getGlobalBadStates();
		for(auto condition : globalBadStateConditions){
			addEdgesForCondition(condition, G);
		}

		std::vector<int> component(num_vertices(G));
		int num = boost::connected_components(G, &component[0]);
		// components now holds an array. It has one entry for each variable specifying its component
		// we parse this to a vector of vectors. each vector contains the variable indices for one component
		// and can consequently can be given to project.
		Decomposition res;
		res.mDecomposition = std::vector<std::vector<size_t>>(num);
		std::vector<size_t>::size_type i;
		for(i = 0; i != component.size(); i++){
			res.mDecomposition[component[i]].push_back(i);
		}
		return res;
	}

	template<typename Number>
	std::pair<HybridAutomaton<Number>, Decomposition> DecisionEntity<Number>::decomposeAutomaton(HybridAutomaton<Number> &automaton){
		Decomposition decomposition = getSubspaceDecomposition(automaton);
		printDecomposition(decomposition);
		//SettingsProvider<Number>::getInstance().setSubspaceDecomposition(decomposition);
		if(decomposition.size() <= 1){
			// decomposing failed/was already done(0-case) or decomposition is all variables (1 case)
			return automaton;
		}
		printDecomposition(decomposition);
		TRACE("hypro.decisionEntity", "Automaton before decomposition: " << automaton);
		automaton.decompose(decomposition);
		TRACE("hypro.decisionEntity", "Automaton after decomposition: " << automaton);
		return std::make_pair(automaton,decomposition);
	}

} // hypro
