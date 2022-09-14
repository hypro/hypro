#include "HyproTransitionVisitor.h"

namespace hypro {

	//////////// Constructor and Destructor

	template<typename Number>
	HyproTransitionVisitor<Number>::HyproTransitionVisitor(std::vector<std::string>& varVec, const std::set<Location<Number>*>& lSet) :
		vars(varVec),
		locSet(lSet)
	{ }

	template<typename Number>
	HyproTransitionVisitor<Number>::~HyproTransitionVisitor() { }

	/////////// Inherited from HybridAutomatonBaseVisitor

	template<typename Number>
	antlrcpp::Any HyproTransitionVisitor<Number>::visitJumps(HybridAutomatonParser::JumpsContext *ctx){

		if(ctx->transition().size() > 0){
			std::set<Transition<Number,Location<Number>>*> trSet;
			//std::set<std::unique_ptr<Transition<Number>>> trSet;
			for(auto tr : ctx->transition()){
				//trSet.insert(visit(tr).antlrcpp::Any::as<Transition<Number>*>());
				//std::unique_ptr<Transition<Number>> t(std::move(visit(tr).template as<std::unique_ptr<Transition<Number>>>()));
				Transition<Number,Location<Number>>* t = visit(tr).template as<Transition<Number,Location<Number>>*>();//.antlrcpp::Any::as<Transition<Number>*>();
				//trSet.insert(t);
				trSet.emplace(t);
				//(t->getSource())->addTransition(t);
			}
			return trSet;
			//return std::move(trSet);
		} else if(ctx->stochastictransition().size() > 0){
			std::set<Transition<Number,Location<Number>>*> trSet;
			for(auto tr : ctx->stochastictransition()){
				std::set<StochasticTransition<Number,Location<Number>> *> tSet = visit(tr).template as<std::set<StochasticTransition<Number,Location<Number>> *>>();
				for(auto t : tSet){
					trSet.emplace(t);
				}
			}
			return trSet;
		} else {
			return std::set<Transition<Number,Location<Number>>*>();
			//return std::move(std::set<std::unique_ptr<Transition<Number>>>());
		}

	}

	template<typename Number>
	antlrcpp::Any HyproTransitionVisitor<Number>::visitTransition(HybridAutomatonParser::TransitionContext *ctx){

		Transition<Number,Location<Number>>* t = new Transition<Number,Location<Number>>();

		//1.Collect start/destination location from visitFromTo
		std::pair<Location<Number>*,Location<Number>*> fromTo = visit(ctx->fromto()).template as<std::pair<Location<Number>*,Location<Number>*>>();
		t->setSource(fromTo.first);
		t->setTarget(fromTo.second);

		//2. Collect Urgency
		if(ctx->urgent().size() > 1){
			std::cout << "WARNING: Please refrain from entering 'urgent' multiple times. One time is sufficient->" << std::endl;
		} else if(ctx->urgent().size() == 1){
			t->setUrgent(true);
		} else {
			t->setUrgent(false);
		}

		//3.Collect Guards
		if(ctx->guard().size() > 1){
			std::cout << "WARNING: Please refrain from entering multiple guard constraints via several guard spaces. Typing one guard space of the form 'guard { constraint1 constraint2 ... }' is sufficient->" << std::endl;
		}
		if(ctx->guard().size() == 1){
			Condition<Number> inv = visit(ctx->guard()[0]).template as<Condition<Number>>();
			t->setGuard(inv);
		}

		//4.Collect Resets
		if(ctx->resetfct().size() > 1){
			std::cout << "WARNING: Please refrain from entering multiple reset allocations via several reset spaces. Typing one reset space of the form 'reset { allocation1 allocation2 ... }' is sufficient->" << std::endl;
		}
		if(ctx->resetfct().size() == 1){
			Reset<Number> reset = visit(ctx->resetfct()[0]).template as<Reset<Number>>();
			t->setReset(reset);
		}

		//5.Collect Aggregation
		if(ctx->aggregation().size() > 1){
			std::cerr << "ERROR: Multiple aggregation types specified for one transition." << std::endl;
			exit(0);
		}
		if(ctx->aggregation().size() == 1){
			Aggregation agg = visit(ctx->aggregation()[0]).template as<Aggregation>();
			t->setAggregation(agg);
		}

		//6. Collect synchronization labels
		if(ctx->labels().size() > 0){
			std::vector<Label> transformed{};
			for(const auto& l : ctx->labels()) {
				auto labels = visit(l).template as<std::vector<hypro::Label>>();
				transformed.insert(transformed.end(),labels.begin(),labels.end());
			}

			t->setLabels(transformed);
		}

		return t;
	}

	template<typename Number>
	antlrcpp::Any HyproTransitionVisitor<Number>::visitFromto(HybridAutomatonParser::FromtoContext *ctx){

		//0.Syntax check - are both given names really location names?
		//1.While doing syntax check, also fill fromTo (defined below) so we can return it.
		bool foundLeft = false;
		bool foundRight = false;
		std::pair<Location<Number>*,Location<Number>*> fromTo;
		for(const auto& loc : locSet){
			if(loc->getName() == ctx->VARIABLE()[0]->getText()){
				foundLeft = true;
				fromTo.first = loc;
			}
			if(loc->getName() == ctx->VARIABLE()[1]->getText()){
				foundRight = true;
				fromTo.second = loc;
			}
		}
		if(!foundLeft || !foundRight){
			std::cerr << "ERROR: Location names in a jump do not exist." << std::endl;
			exit(0);
		}

		//1.Return pair of location pointers to both given location names
		return fromTo;
	}

	template<typename Number>
	antlrcpp::Any HyproTransitionVisitor<Number>::visitGuard(HybridAutomatonParser::GuardContext *ctx){

		//1.Call HyproFormulaVisitor and get pair of matrix and vector if constrset exists
		if(ctx->constrset() != NULL){
			HyproFormulaVisitor<Number> visitor(vars);
			std::pair<matrix_t<Number>,vector_t<Number>> result = visitor.visit(ctx->constrset()).template as<std::pair<matrix_t<Number>,vector_t<Number>>>();
			Condition<Number> inv;
			inv.setMatrix(result.first);
			inv.setVector(result.second);
			return inv;
		}
		//Return empty condition as 0xn matrix because we have zero contraints over n variables.
		return Condition<Number>(ConstraintSetT<Number>{   matrix_t<Number>::Zero(0, vars.size()), vector_t<Number>::Zero(0)    });

	}

	template<typename Number>
	antlrcpp::Any HyproTransitionVisitor<Number>::visitLabels(HybridAutomatonParser::LabelsContext *ctx) {
		// TODO
		std::vector<hypro::Label> labels{};
		for(const auto& l : ctx->VARIABLE() ) {
			labels.emplace_back(hypro::Label(l->getText()));
		}
		return labels;
	}

	template<typename Number>
	antlrcpp::Any HyproTransitionVisitor<Number>::visitAllocation(HybridAutomatonParser::AllocationContext *ctx){

		//0.Syntax Check - Check if left side is a var with '
		bool found = false;
		unsigned placeInto = 0;
		for(unsigned i=0; i < vars.size(); i++){
			if((vars[i] + "'") == ctx->VARIABLE()->getText()){
				found = true;
				placeInto = i;
			}
		}
		if(!found){
			std::cerr << "An allocation in the reset part has a not defined variable." << std::endl;
			exit(0);
		}

		std::variant<vector_t<Number>, carl::Interval<Number>> alloc;

		//assert(ctx-polynom() == NULL || ctx->interval() == NULL);
		//1.Call HyproFormulaVisitor::visitPolynom()
		if(ctx->polynom() != NULL){
			HyproFormulaVisitor<Number> visitor(vars);
			vector_t<Number> tmp = visitor.visit(ctx->polynom()).template as<vector_t<Number>>();
			alloc = tmp;
		}
		//NOTE: Intervals are parsed but not handled yet
		if(ctx->interval() != NULL){
			HyproFormulaVisitor<Number> visitor(vars);
			carl::Interval<Number> tmp = visitor.visit(ctx->interval()).template as<carl::Interval<Number>>();
			alloc = tmp;
		}

		//3.Return Vector of coefficents and place in matrix
		return std::make_pair(alloc,placeInto);
	}

	template<typename Number>
	antlrcpp::Any HyproTransitionVisitor<Number>::visitResetfct(HybridAutomatonParser::ResetfctContext *ctx){
		//0.Check if there are not too much resets
		if(ctx->allocation().size() > vars.size()){
			std::cerr << "ERROR: Too many resets for this amount of variables. Only one reset per transition per variable allowed." << std::endl;
			exit(0);
		}

		//1.Iteratively call visit(allocation) to get a values for the row of resetMatrix and a value for resetVector
		using allocVariant = std::variant<vector_t<Number>, carl::Interval<Number>>;

		matrix_t<Number> resetMatrix = matrix_t<Number>::Identity(vars.size(), vars.size());
		vector_t<Number> resetVector = vector_t<Number>::Zero(vars.size());
                std::vector<carl::Interval<Number>> intervalResets = std::vector<carl::Interval<Number>>(vars.size(), createEmptyInterval<Number>());
		std::size_t affineAssignmentCnt = 0;
		std::size_t intervalAssignmentCnt = 0;
		for(unsigned i=0; i < ctx->allocation().size(); i++){
			std::pair<allocVariant,unsigned> valuesNPos = visit(ctx->allocation()[i]).template as<std::pair<allocVariant,unsigned>>();
			if(valuesNPos.first.index() == 0) {
				auto assignment = std::get<vector_t<Number>>(valuesNPos.first);
				if(static_cast<unsigned>(assignment.rows()) != vars.size()+1){
					std::cerr << "ERROR: Visiting Allocation brought forth vec of size: " << assignment.rows() << " but we need: " << vars.size() << std::endl;
					exit(0);
				}
				auto rowNumber = assignment.rows();
				//1.2.Find out into which row according to vars we have to place the row
				resetMatrix.row(valuesNPos.second) = assignment.head(vars.size());
				resetVector(valuesNPos.second) = assignment(rowNumber-1);
                                intervalResets[valuesNPos.second] = createEmptyInterval<Number>();
				++affineAssignmentCnt;
			} else {
				assert(valuesNPos.first.index() == 1);
				//resetMatrix.row(valuesNPos.second) = vector_t<Number>::Zero(vars.size());
				//resetVector(valuesNPos.second) = 0;
				intervalResets[valuesNPos.second] = std::get<carl::Interval<Number>>(valuesNPos.first);
				++intervalAssignmentCnt;
			}
		}

		//2. decompose reset matrix according to interval assignments
		Reset<Number> res;
		res.setMatrix(resetMatrix, 0);
		res.setVector(resetVector, 0);
		res.setIntervals(intervalResets,0);

		//3.return a Reset
		return res;
	}

	template<typename Number>
	antlrcpp::Any HyproTransitionVisitor<Number>::visitAggregation(HybridAutomatonParser::AggregationContext *ctx){
		if(ctx->PARALLELOTOPE() != NULL){
			return Aggregation::aggregation;
		} else if(ctx->BOX() != NULL || ctx->INTERVALAGG() != NULL){
			return Aggregation::aggregation;
		} else {
			return Aggregation::none;
		}
	}

	template<typename Number>
	antlrcpp::Any HyproTransitionVisitor<Number>::visitStochastictransition(HybridAutomatonParser::StochastictransitionContext *ctx){
		std::set<StochasticTransition<Number,Location<Number>>*> trSet;

		if (ctx->probtransition().size() > 0) {
			for (auto tr : ctx->probtransition()) {
				StochasticTransition<Number,Location<Number>>* t = visit(tr).template as<StochasticTransition<Number,Location<Number>>*>();
				trSet.emplace(t);
			}
		}

		// 1. Collect start location from visitProbfrom
		StochasticLocation<Number>* probFrom = visit(ctx->probfrom()).template as<StochasticLocation<Number>*>();
		for (auto t : trSet) {
			t->setSource(probFrom);
		}

		// 2. Collect Urgency
		if(ctx->urgent().size() > 1){
			std::cout << "WARNING: Please refrain from entering 'urgent' multiple times. One time is sufficient->" << std::endl;
		} else if(ctx->urgent().size() == 1){
			for (auto t : trSet) {
				t->setUrgent(true);
			}
		} else {
			for (auto t : trSet) {
				t->setUrgent(false);
			}
		}

		// 3. Collect Guards
		if(ctx->guard().size() > 1){
			std::cout << "WARNING: Please refrain from entering multiple guard constraints via several guard spaces. Typing one guard space of the form 'guard { constraint1 constraint2 ... }' is sufficient->" << std::endl;
		}
		if(ctx->guard().size() == 1){
			Condition<Number> inv = visit(ctx->guard()[0]).template as<Condition<Number>>();
			for (auto t : trSet) {
				t->setGuard(inv);
			}
		}

		// 6. Collect synchronization labels
		if(ctx->labels().size() > 0){
			std::vector<Label> transformed{};
			for(const auto& l : ctx->labels()) {
				auto labels = visit(l).template as<std::vector<hypro::Label>>();
				transformed.insert(transformed.end(),labels.begin(),labels.end());
			}

			for (auto t : trSet) {
				t->setLabels(transformed);
			}
		}
		
		return trSet;
	}

	template<typename Number>
	antlrcpp::Any HyproTransitionVisitor<Number>::visitProbtransition(HybridAutomatonParser::ProbtransitionContext *ctx) {

		StochasticTransition<Number,Location<Number>>* t = new StochasticTransition<Number,Location<Number>>();

		// 1. Collect probability and destination location from visitProbTo
		std::pair<Number,StochasticLocation<Number>*> probTo = visit(ctx->probto()).template as<std::pair<Number,StochasticLocation<Number>*>>();
		t->setTransitionWeight(probTo.first);
		t->setTarget(probTo.second);
		
		// 4. Collect Resets
		if(ctx->resetfct().size() > 1){
			std::cout << "WARNING: Please refrain from entering multiple reset allocations via several reset spaces. Typing one reset space of the form 'reset { allocation1 allocation2 ... }' is sufficient->" << std::endl;
		}
		if(ctx->resetfct().size() == 1){
			Reset<Number> reset = visit(ctx->resetfct()[0]).template as<Reset<Number>>();
			t->setReset(reset);
		}

		// 5. Collect Aggregation
		if(ctx->aggregation().size() > 1){
			std::cerr << "ERROR: Multiple aggregation types specified for one transition." << std::endl;
			exit(0);
		}
		if(ctx->aggregation().size() == 1){
			Aggregation agg = visit(ctx->aggregation()[0]).template as<Aggregation>();
			t->setAggregation(agg);
		}
		return t;
	}

	template<typename Number>
	antlrcpp::Any HyproTransitionVisitor<Number>::visitProbfrom(HybridAutomatonParser::ProbfromContext *ctx) {

		// 0. Syntax check - is the given name really a location name?
		// 1. While doing syntax check, also fill from (defined below) so we can return it.
		bool found = false;
		StochasticLocation<Number>* from;
		for(const auto& loc : locSet){
			if(loc->getName() == ctx->VARIABLE()->getText()){
				found = true;
				from = dynamic_cast<StochasticLocation<Number>*>( loc );
			}
		}
		if(!found){
			std::cerr << "ERROR: Location source in a probabilistic jump does not exist." << std::endl;
			exit(0);
		}

		// 2. Return location pointer to given location name
		return from;
	}

	template<typename Number>
	antlrcpp::Any HyproTransitionVisitor<Number>::visitProbto(HybridAutomatonParser::ProbtoContext *ctx) {

		// 0. Syntax check - is the given name really a location name?
		// 1. While doing syntax check, also fill from (defined below) so we can return it.
		bool found = false;
		std::pair<Number,StochasticLocation<Number>*> to;
		for(const auto& loc : locSet){
			if(loc->getName() == ctx->VARIABLE()->getText()){
				found = true;
				to.second = dynamic_cast<StochasticLocation<Number>*>( loc );
				break;
			}
		}
		if(!found){
			std::cerr << "ERROR: Location source in a probabilistic jump does not exist." << std::endl;
			exit(0);
		}

		std::string weightString = ctx->NUMBER()[0].getText();
		// from HyproFormularVisitor::stringToNumber
		double weightInFloat = boost::lexical_cast<double>(weightString);
		Number weight = Number(weightInFloat);
		to.first = weight;
		

		// 2. Return pair of probability and location pointer to given location name
		return to;
	}
}
