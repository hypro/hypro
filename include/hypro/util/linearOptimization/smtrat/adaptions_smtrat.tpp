#pragma once
#include "adaptions_smtrat.h"

namespace hypro {

template <typename Number>
EvaluationResult<Number> smtratOptimizeLinearPostSolve( const vector_t<Number>& _direction, const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relationSymbols, bool maximize, const EvaluationResult<Number>& preSolution ) {
	EvaluationResult<Number> res;
	smtrat::Poly objective = createObjective( _direction );
	//#ifdef RECREATE_SOLVER
	smtrat::SimplexSolver simplex;
	simplex.push();
	std::unordered_map<smtrat::FormulaT, std::size_t> formulaMapping = createFormula( constraints, constants, relationSymbols );
	for ( const auto& constraintPair : formulaMapping ) {
		simplex.inform( constraintPair.first );
		simplex.add( constraintPair.first, false );
	}

	simplex.push();
	// Add a constraint forcing SMT-RAT to improve the solution calculated by glpk (increase precision).
	if ( preSolution.errorCode == SOLUTION::FEAS ) {
		addPreSolution( simplex, preSolution, _direction, objective, maximize );
	} else if ( preSolution.errorCode == SOLUTION::INFEAS ) {
		if ( simplex.check() == smtrat::Answer::UNSAT ) {
			// std::cout << "SMTRAT infeas." << std::endl;
			return preSolution;	 // glpk correctly detected infeasibility.
		}						 // if glpk falsely detected infeasibility, we cope with this case below.
	} else {					 // if glpk already detected unboundedness we return its result.
		return preSolution;
	}

	simplex.addObjective( objective, !maximize );
	smtrat::Answer smtratCheck = simplex.check();

	switch ( smtratCheck ) {
		case smtrat::Answer::SAT: {
			// std::cout << "smtrat: SAT" << std::endl;
			res = extractSolution<Number>( simplex, objective, constraints.cols() );
			break;
		}
		default: {
			// in this case the constraints introduced by the presolution made the problem infeasible
			simplex.pop();
			simplex.addObjective( objective, !maximize );
			// std::cout << "Cleared formula: " << std::endl;
			// std::cout << ((smtrat::FormulaT)simplex.formula()).toString( false, 1, "", true, false, true, true ) << std::endl;
			// std::cout << "(maximize " << objective.toString(false,true) << ")" << std::endl;
			smtratCheck = simplex.check();
			assert( smtratCheck != smtrat::Answer::UNKNOWN );
			if ( smtratCheck == smtrat::Answer::SAT ) {
				res = extractSolution<Number>( simplex, objective, constraints.cols() );
				assert( smtratCheckPoint( constraints, constants, Point<Number>( res.optimumValue ) ) );
			} else {
				assert( smtratCheck == smtrat::Answer::UNSAT );
				res = EvaluationResult<Number>( 0, SOLUTION::INFEAS );
			}
			break;
		}
	}
	return res;
}

template <typename Number>
EvaluationResult<Number> smtratOptimizeLinear( const vector_t<Number>& _direction, const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relationSymbols, bool maximize ) {
	EvaluationResult<Number> res;
	smtrat::Poly objective = createObjective( _direction );
	//#ifdef RECREATE_SOLVER
	smtrat::SimplexSolver simplex;
	simplex.push();
	std::unordered_map<smtrat::FormulaT, std::size_t> formulaMapping = createFormula( constraints, constants, relationSymbols );
	for ( const auto& constraintPair : formulaMapping ) {
		simplex.inform( constraintPair.first );
		simplex.add( constraintPair.first, false );
	}
	// std::cout << "Informed basic constraints defining the object." << std::endl;

	simplex.addObjective( objective, !maximize );

#ifdef DEBUG_MSG
	// std::cout << "(push)" << std::endl;
	// std::cout << ((smtrat::FormulaT)simplex.formula()).toString( false, 1, "", true, false, true, true ) << std::endl;
	// std::cout << "(maximize " << objective.toString(false,true) << ")" << std::endl;
#endif

#ifdef VERIFY_RESULT
	outputToSmtlibFormat( simplex, 0, objective, "Collected_out_" );
#endif

	smtrat::Answer smtratCheck = simplex.check();

#ifdef DEBUG_MSG
	// std::cout << "Done checking." << std::endl;
#endif

	switch ( smtratCheck ) {
		case smtrat::Answer::SAT: {
			// std::cout << "smtrat: SAT" << std::endl;
			res = extractSolution<Number>( simplex, objective, constraints.cols() );
			break;
		}
		default: {
			// the original constraint system is UNSAT. (LRA Module cannot return UNKNOWN, except for inequality constraints (!=)
			assert( smtratCheck == smtrat::Answer::UNSAT );
			// std::cout << "smtrat: UNSAT" << std::endl;
			res = EvaluationResult<Number>( 0, SOLUTION::INFEAS );
			break;
		}
	}
	return res;
}

template <typename Number>
bool smtratCheckConsistency( const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relationSymbols ) {
	//#ifdef RECREATE_SOLVER
	// std::cout << constraints << std::endl << constants << std::endl;
	smtrat::SimplexSolver simplex;
	std::unordered_map<smtrat::FormulaT, std::size_t> formulaMapping = createFormula( constraints, constants, relationSymbols );
	for ( const auto& constraintPair : formulaMapping ) {
		simplex.inform( constraintPair.first );
		simplex.add( constraintPair.first, false );
		// std::cout << constraintPair.first << std::endl;
	}
	smtrat::Answer sol = simplex.check();
	// std::cout << "smtrat says " << sol << std::endl;
	return ( sol == smtrat::Answer::SAT );

	//#else // RECREATE_SOLVER
	/*
		if(!mConsistencyChecked) { // If this setup has already been checked, avoid call.
			//std::cout << "Check: " << std::endl;
			//std::cout << ((smtrat::FormulaT)mSmtratSolver.formula()).toString( false, 1, "", true, false, true, true ) << std::endl;

			smtrat::Answer tmp = mSmtratSolver.check();
			switch (tmp) {
				case smtrat::Answer::UNSAT: {
					mLastConsistencyAnswer = SOLUTION::INFEAS;
					break;
				}
				case smtrat::Answer::SAT: {
					mLastConsistencyAnswer = SOLUTION::FEAS;
					break;
				}
				default:
					mLastConsistencyAnswer = SOLUTION::UNKNOWN;
			}
			mConsistencyChecked = true;
		}
		*/
	//#endif // RECREATE_SOLVER
}

template <typename Number>
bool smtratCheckPoint( const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relationSymbols, const Point<Number>& point ) {
	//#ifdef RECREATE_SOLVER
	smtrat::SimplexSolver simplex;
	std::unordered_map<smtrat::FormulaT, std::size_t> formulaMapping = createFormula( constraints, constants, relationSymbols );
	for ( const auto& constraintPair : formulaMapping ) {
		simplex.inform( constraintPair.first );
		simplex.add( constraintPair.first, false );
	}
	std::unordered_map<smtrat::FormulaT, std::size_t> pointMapping = createFormula( point );
	for ( const auto& constraintPair : pointMapping ) {
		simplex.inform( constraintPair.first );
		simplex.add( constraintPair.first, false );
	}
	// std::cout << "Check: " << std::endl;
	// std::cout << ((smtrat::FormulaT)simplex.formula()).toString( false, 1, "", true, false, true, true ) << std::endl;
	smtrat::Answer sol = simplex.check();
	assert( sol != smtrat::Answer::UNKNOWN );
	return ( sol == smtrat::Answer::SAT );
	//#else // DO NOT RECREATE_SOLVER
	/*
		mSmtratSolver.push();
		std::unordered_map<smtrat::FormulaT, std::size_t> pointMapping = createFormula(_point);
		for(const auto& constraintPair : pointMapping) {
			mSmtratSolver.inform(constraintPair.first);
			mSmtratSolver.add(constraintPair.first, false);
		}
		//std::cout << "Check: " << std::endl;
		//std::cout << ((smtrat::FormulaT)mSmtratSolver.formula()).toString( false, 1, "", true, false, true, true ) << std::endl;
		smtrat::Answer tmp = mSmtratSolver.check();
		mSmtratSolver.pop();
		return (tmp == smtrat::Answer::SAT);
		*/
	//#endif // RECREATE_SOLVER
}

template <typename Number>
std::vector<std::size_t> smtratRedundantConstraints( const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relationSymbols ) {
	std::vector<std::size_t> res;
	//#ifdef RECREATE_SOLVER
	smtrat::SimplexSolver simplex;
	const std::unordered_map<smtrat::FormulaT, std::size_t> formulaMapping = createFormula( constraints, constants, relationSymbols );

	if ( formulaMapping.size() == 1 ) {
		return res;
	}

	if ( unsigned( formulaMapping.size() ) != constraints.rows() ) {
		for ( unsigned cnt = 0; cnt < constraints.rows(); ++cnt ) {
			bool found = false;
			for ( const auto& constraintPair : formulaMapping ) {
				if ( constraintPair.second == cnt ) {
					found = true;
					break;
				}
			}
			if ( !found ) {
				res.push_back( cnt );
			}
			if ( res.size() == ( constraints.rows() - formulaMapping.size() ) )
				break;
		}
	}

	assert( unsigned( formulaMapping.size() + res.size() ) == constraints.rows() );
	for ( const auto& constraintPair : formulaMapping ) {
		simplex.inform( constraintPair.first );
		simplex.add( constraintPair.first, false );
	}

	// first call to check satisfiability
	smtrat::Answer firstCheck = simplex.check();

	switch ( firstCheck ) {
		case smtrat::Answer::UNSAT: {
			return res;
		}
		case smtrat::Answer::SAT: {
			break;
		}
		default: {
			assert( false );
			break;
		}
	}

	std::size_t count = 0;

	std::size_t formulaSize = simplex.formula().size();
	for ( auto formulaIt = simplex.formulaBegin(); count < formulaSize; ++count ) {
		smtrat::FormulaT originalConstraint = ( *formulaIt ).formula();

		smtrat::FormulaT negatedConstraint = smtrat::FormulaT( ( *formulaIt ).formula().constraint().lhs(), negateRelation<Number>( ( *formulaIt ).formula().constraint().relation() ) );
		unsigned currentFormulaSize = simplex.formula().size();
		simplex.inform( negatedConstraint );
		simplex.add( negatedConstraint, false );

		if ( simplex.formula().size() > currentFormulaSize ) {
			formulaIt = simplex.remove( formulaIt );

			smtrat::Answer isRedundant = simplex.check();
			assert( isRedundant != smtrat::Answer::UNKNOWN );
			if ( isRedundant == smtrat::Answer::UNSAT ) {
				assert( formulaMapping.find( originalConstraint ) != formulaMapping.end() );
				assert( unsigned( formulaMapping.at( originalConstraint ) ) < constraints.rows() );
				res.push_back( formulaMapping.at( originalConstraint ) );
			}

			assert( *( --( simplex.formula().end() ) ) == negatedConstraint );
			simplex.remove( --( simplex.formulaEnd() ) );
			simplex.deinform( negatedConstraint );
			simplex.add( originalConstraint, false );
		} else {
			formulaIt++;
		}
	}
	return res;

	//#else // DO NOT RECREATE_SOLVER
	/*
		if(mCurrentFormula.getType() == carl::FormulaType::CONSTRAINT ){ // if there is only one constraint
			return res;
		}

		// first call to check satisfiability
		smtrat::Answer firstCheck;
		if(!mConsistencyChecked) { // If this setup has already been checked, avoid call.
			//std::cout << "Making first check." << std::endl;
			//std::cout << ((smtrat::FormulaT)mSmtratSolver.formula()).toString( false, 1, "", true, false, true, true ) << std::endl;
			firstCheck = mSmtratSolver.check();
			switch (firstCheck) {
				case smtrat::Answer::UNSAT: {
					mLastConsistencyAnswer = SOLUTION::INFEAS;
					// TODO: Return complement of infeasible subset indices.
					return res;
					break;
				}
				case smtrat::Answer::SAT: {
					mLastConsistencyAnswer = SOLUTION::FEAS;
					break;
				}
				default: {
					assert(false);
					break;
				}
			}
			mConsistencyChecked = true;
		}

		if(mLastConsistencyAnswer == SOLUTION::INFEAS){
			return res;
		}

		std::size_t count = 0;
		//std::cout << "Original Formula: " << std::endl;
		//mSmtratSolver.printAssertions();
		std::size_t formulaSize = mSmtratSolver.formula().size();
		for(auto formulaIt = mSmtratSolver.formulaBegin(); count < formulaSize; ) {
			smtrat::FormulaT originalConstraint = (*formulaIt).formula();
			smtrat::FormulaT negatedConstraint = smtrat::FormulaT( (*formulaIt).formula().constraint().lhs(), carl::invertRelation( (*formulaIt).formula().constraint().relation() ) );
			formulaIt = mSmtratSolver.remove(formulaIt);
			mSmtratSolver.inform(negatedConstraint);
			mSmtratSolver.add(negatedConstraint, false);

			//std::cout << "Modified Formula: " << negatedConstraint << std::endl;

			smtrat::Answer isRedundant = mSmtratSolver.check();
			assert(isRedundant != smtrat::Answer::UNKNOWN);
			if(isRedundant == smtrat::Answer::UNSAT)
				res.push_back(mFormulaMapping.at(originalConstraint));

			assert(*(--(mSmtratSolver.formula().end())) == negatedConstraint);
			mSmtratSolver.remove(--(mSmtratSolver.formulaEnd()));
			mSmtratSolver.deinform(negatedConstraint);
			mSmtratSolver.add(originalConstraint, false);
			++count;
		}
		*/
	//#endif // RECREATE_SOLVER
}

template <typename Number>
EvaluationResult<Number> smtratGetInternalPoint( const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relationSymbols ) {
	//#ifdef RECREATE_SOLVER
	EvaluationResult<Number> res;
	smtrat::SimplexSolver simplex;
	std::unordered_map<smtrat::FormulaT, std::size_t> formulaMapping = createFormula( constraints, constants, relationSymbols );
	for ( const auto& constraintPair : formulaMapping ) {
		simplex.inform( constraintPair.first );
		simplex.add( constraintPair.first, false );
	}
	smtrat::Answer sol = simplex.check();
	if ( sol == smtrat::Answer::UNSAT ) {
		res = EvaluationResult<Number>( 0, vector_t<Number>::Zero( 1 ), SOLUTION::INFEAS );
		return res;
	} else {
		res.errorCode = SOLUTION::FEAS;
	}
	smtrat::Model assignment = simplex.model();
	vector_t<Number> point = vector_t<Number>( constraints.cols() );
	for ( unsigned d = 0; d < constraints.cols(); ++d ) {
		// if the variable did not occur in the current call, set to 0.
		if ( assignment.find( hypro::VariablePool::getInstance().carlVarByIndex( d ) ) == assignment.end() ) {
			point( d ) = 0;
		} else {
			assert( assignment.find( hypro::VariablePool::getInstance().carlVarByIndex( d ) ) != assignment.end() );
			assert( assignment.find( hypro::VariablePool::getInstance().carlVarByIndex( d ) )->second.isRational() );
			point( d ) = carl::convert<smtrat::Rational, Number>( assignment.find( VariablePool::getInstance().carlVarByIndex( d ) )->second.asRational() );
		}
	}
	res.optimumValue = point;
	assert( smtratCheckPoint( constraints, constants, Point<Number>( point ) ) );
	return res;

	//#else DO NOT RECREATE SOLVER
	/*
		smtrat::Answer tmp = mSmtratSolver.check();
		switch (tmp) {
			case smtrat::Answer::UNSAT: {
				mLastConsistencyAnswer = SOLUTION::INFEAS;
				mConsistencyChecked = true;
				res.errorCode = SOLUTION::INFEAS;
				return res;
			}
			case smtrat::Answer::SAT: {
				mLastConsistencyAnswer = SOLUTION::FEAS;
				mConsistencyChecked = true;
				smtrat::Model assignment = mSmtratSolver.model();
				vector_t<Number> point;
				for(unsigned d = 0; d < constraints.cols(); ++d){
					// if the variable did not occur in the current call, set to 0.
					if(assignment.find(hypro::VariablePool::getInstance().carlVarByIndex(d)) == assignment.end()){
						point(d) = 0;
					} else {
						assert(assignment.find(hypro::VariablePool::getInstance().carlVarByIndex(d)) != assignment.end());
						assert(assignment.find(hypro::VariablePool::getInstance().carlVarByIndex(d))->second.isRational());
						point(d) = carl::convert<smtrat::Rational, Number>(assignment.find(hypro::VariablePool::getInstance().carlVarByIndex(d))->second.asRational());
					}
				}
				res.optimumValue = point;
				res.errorCode = mLastConsistencyAnswer;
				assert(checkPoint(Point<Number>(res.optimumValue)));
				break;
			}
			default:
				mLastConsistencyAnswer = SOLUTION::UNKNOWN;
		}
		return res;
		*/
	//#endif
}

}  // namespace hypro
