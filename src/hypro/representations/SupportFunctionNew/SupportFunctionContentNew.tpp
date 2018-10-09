#include "SupportFunctionContentNew.h"

namespace hypro {

	template<typename Number>
	std::vector<EvaluationResult<Number>> SupportFunctionContentNew<Number>::evaluate(const matrix_t<Number>& directions) {
		
		//Define lambda functions that will call the functions transform, compute and aggregate dependent on the current node type
		std::function<Parameters<matrix_t<Number>>(RootGrowNode<Number>*, Parameters<matrix_t<Number>>)> trans = 
			[](RootGrowNode<Number>* n, Parameters<matrix_t<Number>> param) -> Parameters<matrix_t<Number>> { 
				std::cout << "calling trans\n";
				return Parameters<matrix_t<Number>>(n->transform(std::get<0>(param.args))); 
			};

		std::function<std::vector<EvaluationResult<Number>>(RootGrowNode<Number>*, Parameters<matrix_t<Number>>)> comp = 
			[](RootGrowNode<Number>* n, Parameters<matrix_t<Number>> dir) -> std::vector<EvaluationResult<Number>> { 
				std::cout << "calling comp\n";
				return n->compute(std::get<0>(dir.args)); 
			};

		std::function<std::vector<EvaluationResult<Number>>(RootGrowNode<Number>*, std::vector<std::vector<EvaluationResult<Number>>>, Parameters<matrix_t<Number>>)> agg = 
			[](RootGrowNode<Number>* n, std::vector<std::vector<EvaluationResult<Number>>> resultStackBack, Parameters<matrix_t<Number>> currentParam) -> std::vector<EvaluationResult<Number>> { 
				std::cout << "calling agg\n";
				return n->aggregate(resultStackBack, std::get<0>(currentParam.args)); 
			};

		//Check if the functions are invocable (if not, something went wrong)
		std::cout << "trans invocable? " << std::is_invocable_r<Parameters<matrix_t<Number>>, decltype(trans), RootGrowNode<Number>*, Parameters<matrix_t<Number>>>::value << std::endl;
		std::cout << "comp invocable? " << std::is_invocable_r<std::vector<EvaluationResult<Number>>, decltype(comp), RootGrowNode<Number>*, Parameters<matrix_t<Number>>>::value << std::endl;
		std::cout << "agg invocable? " << std::is_invocable_r<std::vector<EvaluationResult<Number>>, decltype(agg), RootGrowNode<Number>*, std::vector<std::vector<EvaluationResult<Number>>>, Parameters<matrix_t<Number>>>::value << std::endl;

		//Traverse the underlying RootGrowTree with the three functions and given directions as initial parameters.
		return RootGrowTree<Number>::traverse(trans, comp, agg, Parameters<matrix_t<Number>>(directions));
	}



} //namespace hypro