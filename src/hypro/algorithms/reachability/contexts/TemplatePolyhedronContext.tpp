#include "TemplatePolyhedronContext.h"

namespace hypro {

template <typename State>
vector_t<typename State::NumberType> TemplatePolyhedronContext<State>::gradientOfLinearFct( const vector_t<Number>& linearFct ) {
	assert( (unsigned)linearFct.rows() == this->mComputationState.getDimension() + 1 );
	vector_t<Number> gradient = linearFct;
	gradient( gradient.rows() - 1 ) = 0;
	return gradient;
}

template <typename State>
std::pair<vector_t<typename State::NumberType>, typename State::NumberType> TemplatePolyhedronContext<State>::lieDerivative( const vector_t<Number>& dir ) {
	//std::cout << "TemplatePolyhedronContext::lieDerivative, dir with " << dir.rows() << "x" << dir.cols() << ": \n" << dir << std::endl;
	assert( dir.cols() == 1 );
	assert( this->mComputationState.getLocation()->getLinearFlow().getFlowMatrix().transpose().rows() == this->mComputationState.getLocation()->getLinearFlow().getFlowMatrix().transpose().cols() );
	//Extend dir by one dimension
	vector_t<Number> derivative = vector_t<Number>::Zero( dir.rows() + 1 );
	derivative.block( 0, 0, dir.rows(), 1 ) = dir;
	derivative( derivative.rows() - 1 ) = 0;
	assert( derivative.rows() == this->mComputationState.getLocation()->getLinearFlow().getFlowMatrix().transpose().rows() );
	//Compute lie derivative
	derivative = this->mComputationState.getLocation()->getLinearFlow().getFlowMatrix().transpose() * gradientOfLinearFct( derivative );
	//Separate vector and dimensionless offset
	vector_t<Number> deriv = derivative.block( 0, 0, derivative.rows() - 1, 1 );
	auto tmp = std::make_pair( deriv, derivative( derivative.rows() - 1 ) );
	assert( tmp.first.rows() == dir.rows() );
	assert( tmp.first.rows() + 1 == derivative.rows() );
	assert( tmp.first.cols() == 1 );
	return tmp;
}

template <typename State>
std::pair<vector_t<typename State::NumberType>, typename State::NumberType> TemplatePolyhedronContext<State>::lieDerivativeExtended( const vector_t<Number>& dir ) {
	//std::cout << "TemplatePolyhedronContext::lieDerivative, dir with " << dir.rows() << "x" << dir.cols() << ": \n" << dir << std::endl;
	assert( dir.cols() == 1 );
	assert( this->mComputationState.getLocation()->getLinearFlow().getFlowMatrix().transpose().rows() == this->mComputationState.getLocation()->getLinearFlow().getFlowMatrix().transpose().cols() );
	assert( this->mComputationState.getLocation()->getLinearFlow().getFlowMatrix().transpose().rows() == dir.rows() );
	//Compute lie derivative
	vector_t<Number> derivative = this->mComputationState.getLocation()->getLinearFlow().getFlowMatrix().transpose() * gradientOfLinearFct( dir );
	//std::cout << "flow: \n" << this->mComputationState.getLocation()->getLinearFlow().getFlowMatrix().transpose() << "dir: \n" << dir << " derivative: \n" << derivative << std::endl;
	vector_t<Number> deriv = derivative.block( 0, 0, derivative.rows() - 1, 1 );
	//std::cout << "TemplatePolyhedronContext::lieDerivative, deriv with " << deriv.rows() << "x" << deriv.cols() << " is: \n" << deriv << std::endl;
	//std::cout << "TemplatePolyhedronContext::lieDerivative, returning vec: \n" << derivative.block( 0, 0, derivative.rows() - 1, 1 ) << " offset: " << derivative( derivative.rows() - 1 ) << std::endl;
	//auto tmp = std::make_pair(derivative.block(0,0,derivative.rows()-1,1).transpose(), derivative(derivative.rows()-1));
	auto tmp = std::make_pair( deriv, derivative( derivative.rows() - 1 ) );
	//return std::make_pair(derivative.block(0,0,derivative.rows()-1,1).transpose(), derivative(derivative.rows()-1));
	assert( tmp.first.rows() + 1 == derivative.rows() );
	assert( tmp.first.cols() == 1 );
	return tmp;
}

template <typename State>
vector_t<typename State::NumberType> TemplatePolyhedronContext<State>::locationInvariantStrengthening( const TemplatePolyhedron<Number>& invTPoly, const vector_t<Number>& initialOffsets ) {
	//std::cout << "TemplatePolyhedronContext::LIS" << std::endl;
	//std::cout << "TemplatePolyhedronContext::LIS, invTPoly: \n"
	//		  << invTPoly << "initialOffsets: \n"
	//		  << initialOffsets << std::endl;
	COUNT( "Location Invariant Strengthening" );
#ifndef NDEBUG
	assert( !invTPoly.empty() );
	assert( initialOffsets.rows() == invTPoly.vector().rows() );
	for ( int i = 0; i < initialOffsets.rows(); ++i ) {
		assert( initialOffsets( i ) <= invTPoly.vector()( i ) );
	}
#endif

	unsigned invRows = invTPoly.matrix().rows();
	unsigned invCols = invTPoly.matrix().cols();
	assert( invCols == this->mComputationState.getDimension() );

	//Used as storage for solution of last iteration, called a(j) in paper
	vector_t<Number> lastStrengthenedInv = vector_t<Number>::Zero( invTPoly.vector().rows() );
	//Contains the newest relaxed invariant, called a(j+1) in paper
	vector_t<Number> nextStrengthenedInv = invTPoly.vector();
	//Contains the relaxed invariant with the smallest sum of coefficients
	vector_t<Number> smallestInv = invTPoly.vector();
	//Contains all strengthened invariant computed, needed for cycle detection
	std::vector<vector_t<Number>> allInvs;
	//Counts the number of iterations to stop when we reached 10 iterations
	int counter = 0;

	//////// POLICY EVALUATION

	//1. Compute pi(j) (certificate of relaxed invariance for a(j+1)) by solving Dj : max evalDir*x subject to Ax <= b && lambda >= 0
	//Construct A as: first transpose inv matrix, then insert lambda >= 0 constraints
	//NOTE: Since A is the same in every iteration, we construct A once the loop
	//NOTE: We add one row and col for the lie derivate offset later, where we force lambda_{m+1} = 1
	//NOTE: Thus A is of size d+m+1 x m+1
	matrix_t<Number> A = matrix_t<Number>::Zero( invCols + invRows + 1, invRows + 1 );
	A.block( 0, 0, invCols, invRows ) = invTPoly.matrix().transpose();
	A.block( invCols, 0, invRows, invRows ) = -1 * matrix_t<Number>::Identity( invRows, invRows );
	A( invCols + invRows, invRows ) = Number( 1 );

	//std::cout << "TemplatePolyhedronContext::LIS, A is: \n" << A << std::endl;

	//Set equality relations for the first d equations
	std::vector<carl::Relation> equalRelations( invCols + invRows + 1, carl::Relation::LEQ );
	for ( unsigned i = 0; i < invCols; ++i ) {
		equalRelations.at( i ) = carl::Relation::EQ;
	}
	//The last for lamdba_{m+1} = 1
	equalRelations[invCols + invRows] = carl::Relation::EQ;

	//while a(j) != a(j+1)
	while ( lastStrengthenedInv != nextStrengthenedInv ) {
		counter++;

		//Certificate pi(j): Saves the solutions for each Dj
		matrix_t<Number> certificate = matrix_t<Number>::Zero( invRows, invRows );

		//Save lie derivate offsets
		vector_t<Number> derivativeOffsets = vector_t<Number>::Zero( invRows );

		//For each (important) row solve Dj
		for ( unsigned rowI = 0; rowI < invRows; ++rowI ) {
			//2.Construct b = (mScaling * current template row + lie derivative of current row)^T = (mü(H_j) + H_j')^T,
			//extended with zeros to make sure that the optimumValue only contains non negative entries.
			//NOTE: b is of dimension d+m+1, since there are m lambdas and one extra row for being able to calculate with the lie derivate offset
			vector_t<Number> b = vector_t<Number>::Zero( invRows + invCols + 1 );
			assert( b.rows() == A.rows() );
			auto deriv = lieDerivative( invTPoly.matrix().row( rowI ) );
			b.block( 0, 0, invCols, 1 ) = mScaling * vector_t<Number>( invTPoly.matrix().row( rowI ) ) + deriv.first;
			b( invRows + invCols ) = Number( 1 );
			derivativeOffsets( rowI ) = deriv.second;

			//std::cout << "TemplatePolyhedronContext::LIS, for rowI: " << rowI << " b is: \n" << b << std::endl;

			//3.Set A and b as matrix and vector for mOptimizer
			mOptimizer.setMatrix( A );
			mOptimizer.setVector( b );
			mOptimizer.setMaximize( false );
			mOptimizer.setRelations( equalRelations );

			//4.Minimize into direction nextStrengthenedInv - Solution is the optimumValue of minimizeA, but only the first invRows coefficients from that.
			//The rest was only needed to make sure that the optimumValue only contains positive entries.
			vector_t<Number> evalDir = vector_t<Number>::Zero( invRows + 1 );
			evalDir.block( 0, 0, invRows, 1 ) = nextStrengthenedInv;
			evalDir( invRows ) = -mScaling * evalDir( rowI ) + deriv.second;
			auto minimizeA = mOptimizer.evaluate( evalDir, std::is_same_v<Number, mpq_class> );

#ifndef NDEBUG
			assert( minimizeA.errorCode == SOLUTION::FEAS );
			assert( minimizeA.optimumValue.rows() == invRows + 1 );
			for ( int i = 0; i < minimizeA.optimumValue.rows(); ++i ) {
				//make sure all values are greater equal than 0
				assert( minimizeA.optimumValue( i ) >= 0 );
			}
#endif

			//std::cout << "TemplatePolyhedronContext::LIS, evaldir: " << evalDir << std::endl;
			//std::cout << "TemplatePolyhedronContext::LIS, minimizeA: " << minimizeA << std::endl;

			//6.Save into certificate, if support value <= 0, since then row is non-frozen and invariant therefore changeable
			//NOTE: -mScaling * evalDir(rowI) + deriv.second is already a part of evalDir
			if ( minimizeA.supportValue <= 0 ) {
				vector_t<Number> res = minimizeA.optimumValue.block( 0, 0, invRows, 1 );
				certificate.row( rowI ) = res.transpose();
			}

			//Numerical corrections
			if ( TemplatePolyhedron<Number>::Settings::USE_NUMERICAL_CORRECTIONS ) {
				if ( certificate.row( rowI ) == vector_t<Number>::Zero( certificate.cols() ).transpose() ) {
					//Usually when the condition above holds, it also holds nextStrengthenedInv(rowI) == invTPoly.vector()(rowI),
					//but because of numerical issues it can be unequal. In that case correct to the upper case.
					if ( nextStrengthenedInv( rowI ) < invTPoly.vector()( rowI ) ) {
						//numeric error correction
						COUNT( "Correction Insert Certificate Row" );
						vector_t<Number> correction = minimizeA.optimumValue.block( 0, 0, invRows, 1 );
						certificate.row( rowI ) = correction.transpose();
					}
				} else {
					if ( nextStrengthenedInv.dot( certificate.row( rowI ) ) - mScaling * nextStrengthenedInv( rowI ) + deriv.second > 0 ) {
						//numeric error correction - as the value is actually zero or less, we need to set back to row to a zero row.
						COUNT( "Correction Remove Certificate Row" );
						vector_t<Number> correction = vector_t<Number>::Zero( invRows );
						certificate.row( rowI ) = correction.transpose();
					}
				}
			}

			//NOTE: this would usually hold, but because of numerical issues this is not always the case
			//#ifndef NDEBUG
			//if(certificate.row(rowI) == vector_t<Number>::Zero(certificate.cols()).transpose()){
			//	assert(nextStrengthenedInv(rowI) == invTPoly.vector()(rowI));
			//} else {
			//	assert(nextStrengthenedInv.dot(certificate.row(rowI)) - mScaling*nextStrengthenedInv(rowI) + deriv.second <= 0);
			//}
			//#endif
		}

		//std::cout << "TemplatePolyhedronContext::LIS, certificate is now: \n" << certificate << std::endl;

		//////// POLICY IMPROVEMENT

		//Build the system L*y = c with which we get better invariant bounds
		assert( initialOffsets.rows() == invTPoly.vector().rows() );
		matrix_t<Number> L = matrix_t<Number>::Zero( 3 * invRows, invRows );
		vector_t<Number> c = vector_t<Number>::Zero( 3 * invRows );

		//6.Build L_pi(j): Add constraints: init <= y
		L.block( 0, 0, invRows, invRows ) = std::move( -1 * matrix_t<Number>::Identity( invRows, invRows ) );
		c.block( 0, 0, invRows, 1 ) = -1 * initialOffsets;
		//std::cout << "TemplatePolyhedronContext::LIS, added init <= y to L and c: L: \n" << L << "c: \n" << c << std::endl;

		//7.Build L_pi(j): Add constraints: y <= inv_j
		L.block( invRows, 0, invRows, invRows ) = std::move( matrix_t<Number>::Identity( invRows, invRows ) );
		c.block( invRows, 0, invRows, 1 ) = invTPoly.vector();
		//std::cout << "TemplatePolyhedronContext::LIS, added y <= inv_j to L and c: L: \n" << L << "c: \n" << c << std::endl;

		//8.Build L_pi(j): Add constraints. Row frozen if value >= inv
		//If row j frozen, then y = inv_j
		//If row j not frozen, then Delta_j^T*y - mü*y_j + h_j <= 0
		assert( nextStrengthenedInv.rows() == invRows );
		for ( unsigned i = 0; i < nextStrengthenedInv.rows(); ++i ) {
			if ( certificate.row( i ) == vector_t<Number>::Zero( invRows ).transpose() ) {
				//frozen row - normally, insert y_j = inv_j, but since y_j <= inv_j is already in L, insert y_j >= inv_j aka -y_j <= -inv_j
				vector_t<Number> rowToInsert = vector_t<Number>::Zero( invRows );
				rowToInsert( i ) = -1;
				L.row( 2 * invRows + i ) = std::move( rowToInsert.transpose() );
				c( 2 * invRows + i ) = -invTPoly.vector()( i );
			} else {
				//non frozen row
				vector_t<Number> rowToInsert = certificate.row( i );
				rowToInsert( i ) -= mScaling;
				L.row( 2 * invRows + i ) = std::move( rowToInsert.transpose() );
				c( 2 * invRows + i ) = -derivativeOffsets( i );
			}
		}
		//std::cout << "TemplatePolyhedronContext::LIS, added (non-)frozen rows to L and c: L: \n" << L << "c: \n" << c << std::endl;

		//9.Minimize L to get nextStrengthenedInv
		mOptimizer.setMatrix( L );
		mOptimizer.setVector( c );
		mOptimizer.setMaximize( false );
		mOptimizer.setRelations( std::vector<carl::Relation>( 3 * invRows, carl::Relation::LEQ ) );
		auto minimizeL = mOptimizer.evaluate( vector_t<Number>::Ones( invRows ), std::is_same_v<Number, mpq_class> );
		if ( minimizeL.errorCode == SOLUTION::INFEAS ) {
			//If next solution infeasible, return currently saved solution
			//TODO: find out why infeas return even occurs
			COUNT( "Infeas return" );
			return nextStrengthenedInv;
		}
		assert( minimizeL.errorCode == SOLUTION::FEAS );

		//NOTE: normally, this would hold, too, but sadly there are numerical effects again
		//#ifndef NDEBUG
		//for ( unsigned i = 0; i < invRows; ++i ) {
		//	std::cout << i << std::endl;
		//	assert( initialOffsets( i ) <= minimizeL.optimumValue( i ) );
		//	assert( minimizeL.optimumValue( i ) <= invTPoly.vector()( i ) );
		//}
		//#endif

		//std::cout << "TemplatePolyhedronContext::LIS, minimizeL optimumValue is: \n" << minimizeL.optimumValue << std::endl;

		//10.Set as next strenghtened inv
		lastStrengthenedInv = nextStrengthenedInv;
		nextStrengthenedInv = minimizeL.optimumValue;

		//Wrong fixed point escape: save inv with smallest coefficient
		if ( nextStrengthenedInv.sum() < smallestInv.sum() ) {
			smallestInv = nextStrengthenedInv;
		}

		//std::cout << "TemplatePolyhedronContext::LIS, lastStrengthenedInv is now: \n" << lastStrengthenedInv << "nextStrengthenedInv is now: \n" << nextStrengthenedInv << std::endl;
		//std::cout << "TemplatePolyhedronContext::LIS, nextStrengthenedInv: \n" << nextStrengthenedInv << std::endl;
		//std::cout << "TemplatePolyhedronContext::LIS, counter: " << counter << std::endl;

		//Cycle Detection
		bool cycleDetected = false;
		for ( const auto& inv : allInvs ) {
			if ( nextStrengthenedInv.isApprox( inv ) ) {
				COUNT( "Cycle Detection Return" );
				cycleDetected = true;
				break;
			}
		}
		if ( cycleDetected ) {
			break;
		} else {
			allInvs.push_back( nextStrengthenedInv );
		}

		//Stop after 10 iterations to stop cycles of size greater 10
		if ( counter >= 10 ) {
			COUNT( "Counter max return" );
			break;
		}
	}

	//Return strengthened invariant with smallest sum
	if ( nextStrengthenedInv.sum() < smallestInv.sum() ) {
		return nextStrengthenedInv;
	} else {
		return smallestInv;
	}
}

template <typename State>
template <typename Setting>
TemplatePolyhedronT<typename State::NumberType, hypro::Converter<typename State::NumberType>, Setting> TemplatePolyhedronContext<State>::createTemplateContent( const TemplatePolyhedronT<Number, hypro::Converter<Number>, Setting>& tpoly ) {
	//TemplatePolyhedron<typename State::NumberType> TemplatePolyhedronContext<State>::createTemplateContent(const TemplatePolyhedron<Number>& tpoly){

	assert( (unsigned)tpoly.matrix().cols() == this->mComputationState.getDimension() );

	if ( Setting::TEMPLATE_SHAPE == TEMPLATE_CONTENT::OCTAGON ) {
		//std::cout << "TemplatePolyhedronContext::execBeforeFirstSegment, OCTAGON setting" << std::endl;
		return tpoly.overapproximate( createMatrix( computeTemplate<Number>( this->mComputationState.getDimension(), 8 ) ) );
	}

	if ( Setting::TEMPLATE_SHAPE == TEMPLATE_CONTENT::ONLY_INIT ) {
		//std::cout << "TemplatePolyhedronContext::execBeforeFirstSegment, ONLY_INIT setting" << std::endl;
		return tpoly;
	}

	//Start with initial set
	assert( Setting::TEMPLATE_SHAPE != TEMPLATE_CONTENT::OCTAGON );
	std::size_t templateSize = tpoly.matrix().rows();
	matrix_t<Number> extendedMatrix = tpoly.matrix();

	//Add invariants if wanted and if there exist some
	if ( Setting::TEMPLATE_SHAPE >= TEMPLATE_CONTENT::INIT_INV && this->mComputationState.getLocation()->getInvariant() != Condition<Number>() ) {
		//std::cout << "TemplatePolyhedronContext::execBeforeFirstSegment, INIT_INV setting" << std::endl;
		extendedMatrix.conservativeResize( templateSize + this->mComputationState.getLocation()->getInvariant().getMatrix().rows(), this->mComputationState.getDimension() );
		extendedMatrix.block( templateSize, 0, this->mComputationState.getLocation()->getInvariant().getMatrix().rows(), this->mComputationState.getDimension() ) = this->mComputationState.getLocation()->getInvariant().getMatrix();
		templateSize += this->mComputationState.getLocation()->getInvariant().getMatrix().rows();
	}
	//Add guards if wanted and if there exist some
	if ( Setting::TEMPLATE_SHAPE >= TEMPLATE_CONTENT::INIT_INV_GUARD ) {
		//std::cout << "TemplatePolyhedronContext::execBeforeFirstSegment, INIT_INV_GUARD setting" << std::endl;
		for ( const auto& transition : this->mComputationState.getLocation()->getTransitions() ) {
			if ( transition->getGuard() != Condition<Number>() ) {
				extendedMatrix.conservativeResize( templateSize + transition->getGuard().getMatrix().rows(), this->mComputationState.getDimension() );
				extendedMatrix.block( templateSize, 0, transition->getGuard().getMatrix().rows(), this->mComputationState.getDimension() ) = transition->getGuard().getMatrix();
				templateSize += transition->getGuard().getMatrix().rows();
			}
		}
	}
	//Add bad states later on
	if ( Setting::TEMPLATE_SHAPE >= TEMPLATE_CONTENT::INIT_INV_GUARD_BAD ) {
		//std::cout << "TemplatePolyhedronContext::execBeforeFirstSegment, INIT_INV_GUARD_BAD setting" << std::endl;
		for ( const auto& gbadstate : SettingsProvider<State>::getInstance().getHybridAutomaton().getGlobalBadStates() ) {
			if ( gbadstate != Condition<Number>() ) {
				extendedMatrix.conservativeResize( templateSize + gbadstate.getMatrix().rows(), this->mComputationState.getDimension() );
				extendedMatrix.block( templateSize, 0, gbadstate.getMatrix().rows(), this->mComputationState.getDimension() ) = gbadstate.getMatrix();
				templateSize += gbadstate.getMatrix().rows();
			}
		}
		auto lbadstate = SettingsProvider<State>::getInstance().getHybridAutomaton().getLocalBadStates().find( this->mComputationState.getLocation() );
		if ( lbadstate->second != Condition<Number>() ) {
			extendedMatrix.conservativeResize( templateSize + lbadstate->second.getMatrix().rows(), this->mComputationState.getDimension() );
			extendedMatrix.block( templateSize, 0, lbadstate->second.getMatrix().rows(), this->mComputationState.getDimension() ) = lbadstate->second.getMatrix();
			templateSize += lbadstate->second.getMatrix().rows();
		}
	}
	//Evaluate tpoly in directions written in extendedMatrix.
	TemplatePolyhedronT<Number, hypro::Converter<Number>, Setting> overapprox = tpoly.overapproximate( extendedMatrix );
	std::cout << "TPC::createTemplateContent, after overapprox: \n"
			  << overapprox.matrix() << " and: \n"
			  << overapprox.vector() << std::endl;
	overapprox.reduceRepresentation();
	std::cout << "TPC::createTemplateContent, after reduc: \n"
			  << overapprox.matrix() << " and: \n"
			  << overapprox.vector() << std::endl;
	return overapprox;
}

template <typename State>
bool TemplatePolyhedronContext<State>::isPositiveInvariant( const TemplatePolyhedron<Number>& tpoly, const vector_t<Number>& invVector ) {
#ifndef NDEBUG
	//All offset values must be below or equal to invariant offset values
	assert( tpoly.matrix().rows() == invVector.rows() );
	assert( tpoly.vector().rows() == invVector.rows() );
	for ( int i = 0; i < invVector.rows(); ++i ) {
		assert( tpoly.vector()( i ) <= invVector( i ) );
	}
#endif

	//Template matrix and vector extended by two constraints to test if current constraint is a positive invariant.
	matrix_t<Number> extendedMatrix = matrix_t<Number>::Zero( tpoly.matrix().rows() + 2, tpoly.matrix().cols() );
	extendedMatrix.block( 0, 0, tpoly.matrix().rows(), tpoly.matrix().cols() ) = tpoly.matrix();
	vector_t<Number> extendedVector = vector_t<Number>::Zero( tpoly.vector().rows() + 2 );
	extendedVector.block( 0, 0, tpoly.vector().rows(), 1 ) = tpoly.vector();

	for ( int i = 0; i < tpoly.matrix().rows(); ++i ) {
		//std::cout << "TemplatePolyhedronContext::isPositiveInvariant, tpoly.vector(i) = " << tpoly.vector()( i ) << " != " << invVector( i ) << std::endl;

		//Avoid test if value is equal to invariant value
		if ( tpoly.vector()( i ) != invVector( i ) ) {
			//Add constraint "row i >= vector_i" to get equality "row_i == vector_i" since "row_i <= vector_i" is already in template
			extendedMatrix.row( tpoly.matrix().rows() ) = -tpoly.matrix().row( i );
			extendedVector( tpoly.vector().rows() ) = -tpoly.vector()( i );

			//Add constraint "lie derivative of row_i > 0"
			//NOTE: this is equivalent to "-(lie derivative) < 0 " <=> "-(lie derivative only terms with variables) < lie derivate offset"
			auto deriv = lieDerivative( tpoly.matrix().row( i ) );
			extendedMatrix.row( tpoly.matrix().rows() + 1 ) = -deriv.first.transpose();
			extendedVector( tpoly.vector().rows() + 1 ) = deriv.second;
			//extendedMatrix.row( tpoly.matrix().rows() + 1 ) = -lieDerivative( tpoly.matrix().row( i ) ).first.transpose();

			//If unfeasible, then not a positive invariant
			mOptimizer.setMatrix( extendedMatrix );
			mOptimizer.setVector( extendedVector );
			mOptimizer.setMaximize( true );
			//std::cout << "TemplatePolyhedronContext::isPositiveInvariant, extendedMatrix: \n" << extendedMatrix << " extendedVector: \n" << extendedVector << std::endl;
			if ( !mOptimizer.checkConsistency() ) {
				return false;
			}
		}
	}

	return true;
}

template <typename State>
bool TemplatePolyhedronContext<State>::isRelaxedInvariant( const TemplatePolyhedron<Number>& tpoly, const vector_t<Number>& invVector ) {
#ifndef NDEBUG
	//All offset values must be below or equal to invariant offset values
	assert( tpoly.matrix().rows() == invVector.rows() );
	assert( tpoly.vector().rows() == invVector.rows() );
	for ( int i = 0; i < invVector.rows(); ++i ) {
		assert( tpoly.vector()( i ) <= invVector( i ) );
	}
#endif

	//Template matrix and vector extended by two constraints to test if current constraint is a positive invariant.
	matrix_t<Number> extendedMatrix = matrix_t<Number>::Zero( tpoly.matrix().rows() + 1, tpoly.matrix().cols() );
	extendedMatrix.block( 0, 0, tpoly.matrix().rows(), tpoly.matrix().cols() ) = tpoly.matrix();
	vector_t<Number> extendedVector = vector_t<Number>::Zero( tpoly.vector().rows() + 1 );
	extendedVector.block( 0, 0, tpoly.vector().rows(), 1 ) = tpoly.vector();

	for ( int i = 0; i < tpoly.matrix().rows(); ++i ) {
		//std::cout << "TemplatePolyhedronContext::isRelaxedInvariant, tpoly.vector(i) = " << tpoly.vector()( i ) << " != " << invVector( i ) << std::endl;

		//Avoid test if value is equal to invariant value
		if ( tpoly.vector()( i ) < invVector( i ) ) {
			//Compute Lie(H_i*x - d_i)
			vector_t<Number> tmp = vector_t<Number>::Zero( tpoly.matrix().cols() + 1 );
			tmp.block( 0, 0, tpoly.matrix().cols(), 1 ) = tpoly.matrix().row( i ).transpose();
			tmp( tpoly.matrix().cols() ) = -tpoly.vector()( i );
			auto deriv = lieDerivativeExtended( tmp );

			extendedMatrix.row( tpoly.matrix().rows() ) = deriv.first + mScaling * tpoly.matrix().row( i ).transpose();
			extendedVector( tpoly.vector().rows() ) = -deriv.second + mScaling * tpoly.vector()( i );

			//If unfeasible, then not a positive invariant
			mOptimizer.setMatrix( extendedMatrix );
			mOptimizer.setVector( extendedVector );
			mOptimizer.setMaximize( true );
			//std::cout << "TemplatePolyhedronContext::isRelaxedInvariant, extendedMatrix: \n" << extendedMatrix << " extendedVector: \n" << extendedVector << std::endl;
			if ( !mOptimizer.checkConsistency() ) {
				return false;
			}
		}
	}

	return true;
}

template <typename State>
void TemplatePolyhedronContext<State>::execBeforeFirstSegment() {
	//std::cout << "TemplatePolyhedronContext::execBeforeFirstSegment, this->mComputationState before: \n" << this->mComputationState << std::endl;
	//std::cout << "TemplatePolyhedronContext::execBeforeFirstSegment, loc: " << this->mComputationState.getLocation()->getName() << std::endl;
	assert( this->mComputationState.getSetType() == representation_name::polytope_t );
	for ( std::size_t index = 0; index < this->mComputationState.getNumberSets(); ++index ) {
		//TODO: Somehow get tpoly without overriding settings
		//auto tpolySetting = std::visit(genericSettingVisitor<decltype(this->mComputationState.getSet(index))>(), this->mComputationState.getSet(index));
		//using TPolyType = TemplatePolyhedron<typename State::NumberType, hypro::Converter<Number>, decltype(tpolySetting)>
		//auto tpoly = std::visit(genericConvertAndGetVisitor<TPolyType>(), this->mComputationState.getSet(index));
		auto tpoly = std::visit( genericConvertAndGetVisitor<TemplatePolyhedron<Number>>(), this->mComputationState.getSet( index ) );
		tpoly = createTemplateContent( tpoly );
		this->mComputationState.setSet( std::visit( genericInternalConversionVisitor<typename State::repVariant, TemplatePolyhedron<Number>>( tpoly ), this->mComputationState.getSet( index ) ), index );
		this->mTask->treeNode->rGetRefinements().at( this->mTask->btInfo.btLevel ).initialSet = this->mComputationState;

		//Call Location Invariant Strengthening on current invariants
		if ( tpoly.getSettings().USE_LOCATION_INVARIANT_STRENGTHENING && !this->mComputationState.getLocation()->getInvariant().empty() ) {
			//Overapproximate invariant with tpoly directions and save them
			TemplatePolyhedron<Number> invTPoly( this->mComputationState.getLocation()->getInvariant().getMatrix(), this->mComputationState.getLocation()->getInvariant().getVector() );
			invTPoly = invTPoly.overapproximate( tpoly.matrix() );
			mOverapproxedInvariant = invTPoly.vector();
			//Get strengthened invariant
			mStrengthenedInvariant = locationInvariantStrengthening( invTPoly, tpoly.vector() );
			this->mComputationState.rGetLocation()->setInvariant( Condition<Number>( invTPoly.matrix(), *mStrengthenedInvariant ) );
		}
	}
	//std::cout << "TemplatePolyhedronContext::execBeforeFirstSegment, this->mComputationState after: \n" << this->mComputationState << std::endl;

	//Do the stuff ltiContext would to
	this->LTIContext<State>::execBeforeFirstSegment();
}

template <typename State>
void TemplatePolyhedronContext<State>::firstSegment() {
	//std::cout << "TemplatePolyhedronContext::firstSegment" << std::endl;
	if ( TemplatePolyhedron<Number>::Settings::USE_ALTERNATIVE_REACH_ALGO ) {
		for ( std::size_t i = 0; i < this->mComputationState.getNumberSets(); i++ ) {
			//std::cout << "TemplatePolyhedronContext::firstSegment, use USE_ALTERNATIVE_REACH_ALGO!" << std::endl;
			if ( mStrengthenedInvariant ) {
				static_cast<TPolyFirstSegmentHandler<State>*>( this->mFirstSegmentHandlers.at( i ) )->setInvariant( *mStrengthenedInvariant );
			}
			static_cast<TPolyFirstSegmentHandler<State>*>( this->mFirstSegmentHandlers.at( i ) )->handle();
		}
	} else {
		this->mComputationState = ltiFirstSegmentHandler<State>()( this->mComputationState, SettingsProvider<State>::getInstance().getTimeStepSize() );
		//for ( std::size_t i = 0; i < this->mComputationState.getNumberSets(); i++ ) {
		//	//std::cout << "TemplatePolyhedronContext::firstSegment, use standard reach algo!" << std::endl;
		//	//static_cast<ltiFirstSegmentHandler<State>*>( this->mFirstSegmentHandlers.at( i ) )->ltiFirstSegmentHandler<State>::handle();
		//}
	}
	//Do the stuff ltiContext would do
	this->initializeInvariantHandlers();
	this->initializeBadStateHandlers();
}

template <typename State>
void TemplatePolyhedronContext<State>::applyContinuousEvolution() {
	//std::cout << "TemplatePolyhedronContext::applyContinuousEvolution" << std::endl;
	if ( TemplatePolyhedron<Number>::Settings::USE_ALTERNATIVE_REACH_ALGO ) {
		for ( std::size_t i = 0; i < this->mComputationState.getNumberSets(); i++ ) {
			//std::cout << "TemplatePolyhedronContext::applyContinuousEvolution, use USE_ALTERNATIVE_REACH_ALGO!" << std::endl;
			if ( mStrengthenedInvariant ) {
				static_cast<TPolyTimeEvolutionHandler<State>*>( this->mContinuousEvolutionHandlers.at( i ) )->setInvariant( *mStrengthenedInvariant );
			}
			static_cast<TPolyTimeEvolutionHandler<State>*>( this->mContinuousEvolutionHandlers.at( i ) )->handle();
		}
	} else {
		for ( std::size_t i = 0; i < this->mComputationState.getNumberSets(); i++ ) {
			//std::cout << "TemplatePolyhedronContext::applyContinuousEvolution, use standard reach algo!" << std::endl;
			static_cast<TPolyTimeEvolutionHandler<State>*>( this->mContinuousEvolutionHandlers.at( i ) )->handle();
			//static_cast<ltiTimeEvolutionHandler<State>*>( this->mContinuousEvolutionHandlers.at( i ) )->ltiTimeEvolutionHandler<State>::handle();
		}
	}
	//Do the stuff ltiContext would do
	this->mComputationState.setTimestamp( this->mComputationState.getTimestamp() + this->mStrategy.getParameters( this->mTask->btInfo.btLevel ).timeStep );
	for ( auto it = this->mContinuousEvolutionHandlers.begin(); it != this->mContinuousEvolutionHandlers.end(); ) {
		if ( ( *it )->getMarkedForDelete() ) {
			delete *it;
			it = this->mContinuousEvolutionHandlers.erase( it );
		} else {
			++it;
		}
	}
}

template <typename State>
void TemplatePolyhedronContext<State>::execBeforeProcessDiscreteBehavior() {
	for ( std::size_t i = 0; i < this->mComputationState.getNumberSets(); i++ ) {
		if ( mOverapproxedInvariant ) {
			//Restore the overapproximated invariant of the location, or else computation is continued with a specialized invariant
			auto tpoly = std::visit( genericConvertAndGetVisitor<TemplatePolyhedron<Number>>(), this->mComputationState.getSet( i ) );
			this->mComputationState.rGetLocation()->setInvariant( Condition<Number>( tpoly.matrix(), *mOverapproxedInvariant ) );
		}
	}
	this->LTIContext<State>::execBeforeProcessDiscreteBehavior();
}

}  // namespace hypro
