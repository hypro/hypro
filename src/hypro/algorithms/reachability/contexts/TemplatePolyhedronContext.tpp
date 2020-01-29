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
	std::cout << "TemplatePolyhedronContext::lieDerivative, dir with " << dir.rows() << "x" << dir.cols() << ": \n"
			  << dir << std::endl;
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
	//std::cout << "TemplatePolyhedronContext::lieDerivative, derivative with " << derivative.rows() << "x" << derivative.cols() << " is: \n" << derivative << std::endl;
	vector_t<Number> deriv = derivative.block( 0, 0, derivative.rows() - 1, 1 );
	//std::cout << "TemplatePolyhedronContext::lieDerivative, deriv with " << deriv.rows() << "x" << deriv.cols() << " is: \n" << deriv << std::endl;
	std::cout << "TemplatePolyhedronContext::lieDerivative, returning vec: \n"
			  << derivative.block( 0, 0, derivative.rows() - 1, 1 ) << " offset: " << derivative( derivative.rows() - 1 ) << std::endl;
	//auto tmp = std::make_pair(derivative.block(0,0,derivative.rows()-1,1).transpose(), derivative(derivative.rows()-1));
	auto tmp = std::make_pair( deriv, derivative( derivative.rows() - 1 ) );
	//return std::make_pair(derivative.block(0,0,derivative.rows()-1,1).transpose(), derivative(derivative.rows()-1));
	assert( tmp.first.rows() == dir.rows() );
	assert( tmp.first.rows() + 1 == derivative.rows() );
	assert( tmp.first.cols() == 1 );
	return tmp;
}

template <typename State>
vector_t<typename State::NumberType> TemplatePolyhedronContext<State>::locationInvariantStrengthening( const TemplatePolyhedron<Number>& invTPoly, const vector_t<Number>& initialOffsets ) {
	std::cout << "TemplatePolyhedronContext::LIS, invTPoly: \n"
			  << invTPoly << "initialOffsets: \n"
			  << initialOffsets << std::endl;
	assert( !invTPoly.empty() );
	assert( initialOffsets.rows() == invTPoly.vector().rows() );

	unsigned invRows = invTPoly.matrix().rows();
	unsigned invCols = invTPoly.matrix().cols();
	assert( invCols == this->mComputationState.getDimension() );

	//Used as storage for solution of last iteration, called a(j) in paper
	vector_t<Number> lastStrengthenedInv = vector_t<Number>::Zero( invTPoly.vector().rows() );
	//Contains the newest relaxed invariant, called a(j+1) in paper
	vector_t<Number> nextStrengthenedInv = invTPoly.vector();
	//Fixed scaling factor mü
	const Number scalingFactor = 0.7;

	//1. Compute pi(j) (certificate of feasibility for a(j+1)) by solving Dj
	//1.1 Construct A as: first transpose inv matrix, then insert lambda >= 0 constraints
	//NOTE: Since A is the same in every iteration, we construct A once the loop
	//NOTE: We add one row and col for the lie derivate offset later, where we force lambda_{m+1} = 1
	//NOTE: Thus A is of size d+m+1 x m+1
	matrix_t<Number> A = matrix_t<Number>::Zero( invCols + invRows + 1, invRows + 1 );
	A.block( 0, 0, invCols, invRows ) = invTPoly.matrix().transpose();
	A.block( invCols, 0, invRows, invRows ) = -1 * matrix_t<Number>::Identity( invRows, invRows );
	A( invCols + invRows, invRows ) = Number( 1 );
	std::cout << "TemplatePolyhedronContext::LIS, A is: \n"
			  << A << std::endl;

	//Set equality relations for the first d equations
	std::vector<carl::Relation> equalRelations( invCols + invRows + 1, carl::Relation::LEQ );
	for ( unsigned i = 0; i < invCols; ++i ) {
		equalRelations.at( i ) = carl::Relation::EQ;
	}
	//The last for lamdba_{m+1} = 1
	equalRelations[invCols + invRows] = carl::Relation::EQ;

	//while a(j) != a(j+1)
	while ( lastStrengthenedInv != nextStrengthenedInv ) {

		//Certificate pi(j): Saves the solutions for each Dj
		matrix_t<Number> certificate = matrix_t<Number>::Zero( invRows, invRows );

		//Save lie derivate offsets
		vector_t<Number> derivativeOffsets = vector_t<Number>::Zero( invRows );

		//For each (important) row solve Dj
		for ( unsigned rowI = 0; rowI < invRows; ++rowI ) {
			//2.Construct b = (mü(H_j) + H_j')^T, extended with zeros to make sure that the optimumValue only contains non negative entries.
			//NOTE: b is d+m+1 x 1, since there are m lambdas and one row for the being able to calculate with the lie derivate offset
			vector_t<Number> b = vector_t<Number>::Zero( invRows + invCols + 1 );
			assert( b.rows() == A.rows() );
			auto deriv = lieDerivative( invTPoly.matrix().row( rowI ) );
			std::cout << "TemplatePolyhedronContext::LIS, lie derivative of invTPoly matrix row " << rowI << " is: \n"
					  << deriv.first << "with offset " << deriv.second << std::endl;
			b.block( 0, 0, invCols, 1 ) = scalingFactor * vector_t<Number>( invTPoly.matrix().row( rowI ) ) + deriv.first;
			b( invRows + invCols ) = Number( 1 );
			derivativeOffsets( rowI ) = deriv.second;
			std::cout << "TemplatePolyhedronContext::LIS, for rowI: " << rowI << " b is: \n"
					  << b << std::endl;

			//3.Set A and b as matrix and vector for mOptimizer
			mOptimizer.setMatrix( A );
			mOptimizer.setVector( b );
			mOptimizer.setMaximize( false );
			mOptimizer.setRelations( equalRelations );

			//4.Minimize into direction nextStrengthenedInv - Solution is the optimumValue of minimizeA,
			//but only the first invRows coefficients from that. The rest was only needed to make sure that the optimumValue only contains positive entries.
			//vector_t<Number> evalDir = nextStrengthenedInv;
			vector_t<Number> evalDir = vector_t<Number>::Zero( invRows + 1 );
			evalDir.block( 0, 0, invRows, 1 ) = nextStrengthenedInv;
			evalDir( invRows ) = -scalingFactor * evalDir( rowI ) + deriv.second;
			//evalDir(rowI) -= scalingFactor;
			std::cout << "evaldir: " << evalDir << std::endl;
			auto minimizeA = mOptimizer.evaluate( evalDir, true );
			std::cout << "minimizeA: " << minimizeA << std::endl;
#ifndef NDEBUG
			//assert(minimizeA.errorCode == SOLUTION::FEAS);
			assert( minimizeA.optimumValue.rows() == invRows + 1 );
			for ( int i = 0; i < minimizeA.optimumValue.rows(); ++i ) {
				//make sure all values are greater equal than 0
				assert( minimizeA.optimumValue( i ) >= 0 );
			}
#endif
			//std::cout << "TemplatePolyhedronContext::LIS, minimizeA optimumValue is: " << minimizeA.optimumValue.transpose() << std::endl;

			//6.Save into certificate, if condition positive for later construction of L
			//NOTE: -scalingFactor * evalDir(rowI) + deriv.second is already a part of evalDir
			//NOTE: If solution infty, then minimization did not find corner ->
			std::cout << "TemplatePolyhedronContext::LIS, minimizeA dot evaldir is: " << minimizeA.supportValue << std::endl;
			if ( minimizeA.supportValue <= 0 ) {
			//if ( evalDir.dot( minimizeA.optimumValue ) <= 0 ) {
			//if(evalDir(rowI) >= invTPoly.vector()(rowI)){
				vector_t<Number> res = minimizeA.optimumValue.block( 0, 0, invRows, 1 );
				certificate.row( rowI ) = res.transpose();
				//certificate.row(rowI) = minimizeA.optimumValue.transpose();
			}

			std::cout << "TemplatePolyhedronContext::LIS, certificate is now: \n"
					  << certificate << std::endl;
		}

		//Build the system L*y = c
		assert( initialOffsets.rows() == invTPoly.vector().rows() );
		matrix_t<Number> L = matrix_t<Number>::Zero( 3 * invRows, invRows );
		vector_t<Number> c = vector_t<Number>::Zero( 3 * invRows );

		//6.Build L_pi(j): Add constraints: init <= y
		L.block( 0, 0, invRows, invRows ) = std::move( -1 * matrix_t<Number>::Identity( invRows, invRows ) );
		c.block( 0, 0, invRows, 1 ) = -1 * initialOffsets;
		std::cout << "TemplatePolyhedronContext::LIS, added init <= y to L and c: L: \n"
				  << L << "c: \n"
				  << c << std::endl;

		//7.Build L_pi(j): Add constraints: y <= inv_j
		L.block( invRows, 0, invRows, invRows ) = std::move( matrix_t<Number>::Identity( invRows, invRows ) );
		c.block( invRows, 0, invRows, 1 ) = invTPoly.vector();
		std::cout << "TemplatePolyhedronContext::LIS, added y <= inv_j to L and c: L: \n"
				  << L << "c: \n"
				  << c << std::endl;

		//8.Build L_pi(j): Add constraints. Row frozen if value >= inv
		//If row j frozen, then y = inv_j
		//If row j not frozen, then Delta_j^T*y - mü*y_j + h_j <= 0
		assert( nextStrengthenedInv.rows() == invRows );
		for ( unsigned i = 0; i < nextStrengthenedInv.rows(); ++i ) {
			//if(nextStrengthenedInv(i) >= invTPoly.vector()(i)){
			//if(nextStrengthenedInv.dot(certificate.row(i)) - scalingFactor*nextStrengthenedInv(i) + derivativeOffsets(i) > 0){
			if ( certificate.row( i ) == vector_t<Number>::Zero( invRows ).transpose() ) {
				//frozen row - normally, insert y_j = inv_j, but since y_j <= inv_j is already in L, insert y_j >= inv_j aka -y_j <= -inv_j
				std::cout << "TemplatePolyhedronContext::LIS, frozen row!" << std::endl;
				vector_t<Number> rowToInsert = vector_t<Number>::Zero( invRows );
				rowToInsert( i ) = -1;
				L.row( 2 * invRows + i ) = std::move( rowToInsert.transpose() );
				c( 2 * invRows + i ) = -invTPoly.vector()( i );
			} else {
				//non frozen row
				std::cout << "TemplatePolyhedronContext::LIS, non frozen row!" << std::endl;
				vector_t<Number> rowToInsert = certificate.row( i );
				rowToInsert( i ) -= scalingFactor;
				L.row( 2 * invRows + i ) = std::move( rowToInsert.transpose() );
				//c( 2 * invRows + i ) = scalingFactor * rowToInsert( i ) - derivativeOffsets( i );
				c( 2 * invRows + i ) = - derivativeOffsets( i );
			}
		}
		std::cout << "TemplatePolyhedronContext::LIS, added (non-)frozen rows to L and c: L: \n"
				  << L << "c: \n"
				  << c << std::endl;

		//9.Minimize L to get nextStrengthenedInv
		mOptimizer.setMatrix( L );
		mOptimizer.setVector( c );
		mOptimizer.setMaximize( false );
		mOptimizer.setRelations( std::vector<carl::Relation>( 3 * invRows, carl::Relation::LEQ ) );
		auto minimizeL = mOptimizer.evaluate( vector_t<Number>::Ones( invRows ), true );
		//assert( minimizeL.errorCode == SOLUTION::FEAS );
		std::cout << "TemplatePolyhedronContext::LIS, minimizeL is: \n"
				  << minimizeL << std::endl;
#ifndef NDEBUG
		for ( unsigned i = 0; i < invRows; ++i ) {
			assert( initialOffsets( i ) <= minimizeL.optimumValue( i ) && minimizeL.optimumValue( i ) <= invTPoly.vector()( i ) );
		}
#endif
		std::cout << "TemplatePolyhedronContext::LIS, minimizeL optimumValue is: \n"
				  << minimizeL.optimumValue << std::endl;

		//10.Set as next strenghtened inv
		lastStrengthenedInv = nextStrengthenedInv;
		nextStrengthenedInv = minimizeL.optimumValue;

		std::cout << "TemplatePolyhedronContext::LIS, lastStrengthenedInv is now: \n"
				  << lastStrengthenedInv << "nextStrengthenedInv is now: \n"
				  << nextStrengthenedInv << std::endl;
	}
	return nextStrengthenedInv;
}

template <typename State>
template <typename Setting>
TemplatePolyhedronT<typename State::NumberType, hypro::Converter<typename State::NumberType>, Setting> TemplatePolyhedronContext<State>::createTemplateContent( const TemplatePolyhedronT<Number, hypro::Converter<Number>, Setting>& tpoly ) {
	//TemplatePolyhedron<typename State::NumberType> TemplatePolyhedronContext<State>::createTemplateContent(const TemplatePolyhedron<Number>& tpoly){

	//Start with initial set
	assert( (unsigned)tpoly.matrix().cols() == this->mComputationState.getDimension() );
	std::size_t templateSize = tpoly.matrix().rows();
	matrix_t<Number> extendedMatrix = tpoly.matrix();
	std::cout << "TemplatePolyhedronContext::execBeforeFirstSegment, ONLY_INIT setting" << std::endl;

	//Add invariants if wanted and if there exist some
	if ( Setting::TEMPLATE_SHAPE >= TEMPLATE_CONTENT::INIT_INV && this->mComputationState.getLocation()->getInvariant() != Condition<Number>() ) {
		std::cout << "TemplatePolyhedronContext::execBeforeFirstSegment, INIT_INV setting" << std::endl;
		extendedMatrix.conservativeResize( templateSize + this->mComputationState.getLocation()->getInvariant().getMatrix().rows(), this->mComputationState.getDimension() );
		extendedMatrix.block( templateSize, 0, this->mComputationState.getLocation()->getInvariant().getMatrix().rows(), this->mComputationState.getDimension() ) = this->mComputationState.getLocation()->getInvariant().getMatrix();
		templateSize += this->mComputationState.getLocation()->getInvariant().getMatrix().rows();
	}
	//Add guards if wanted and if there exist some
	if ( Setting::TEMPLATE_SHAPE >= TEMPLATE_CONTENT::INIT_INV_GUARD ) {
		std::cout << "TemplatePolyhedronContext::execBeforeFirstSegment, INIT_INV_GUARD setting" << std::endl;
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
		std::cout << "TemplatePolyhedronContext::execBeforeFirstSegment, INIT_INV_GUARD_BAD setting" << std::endl;
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
	overapprox.reduceRepresentation();
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
		std::cout << "TemplatePolyhedronContext::isPositiveInvariant, tpoly.vector(i) = " << tpoly.vector()( i ) << " != " << invVector( i ) << std::endl;

		//Avoid test if value is equal to invariant value
		if ( tpoly.vector()( i ) != invVector( i ) ) {
			//Add constraint "row i >= vector_i" to get equality "row_i == vector_i" since "row_i <= vector_i" is already in template
			extendedMatrix.row( tpoly.matrix().rows() ) = -tpoly.matrix().row( i );
			extendedVector( tpoly.vector().rows() ) = -tpoly.vector()( i );

			//Add constraint "lie derivative of row_i > 0"
			extendedMatrix.row( tpoly.matrix().rows() + 1 ) = -lieDerivative( tpoly.matrix().row( i ) ).first.transpose();

			//If unfeasible, then not a positive invariant
			mOptimizer.setMatrix( extendedMatrix );
			mOptimizer.setVector( extendedVector );
			mOptimizer.setMaximize( true );
			std::cout << "TemplatePolyhedronContext::isPositiveInvariant, extendedMatrix: \n"
					  << extendedMatrix << " extendedVector: \n"
					  << extendedVector << std::endl;
			if ( !mOptimizer.checkConsistency() ) {
				return false;
			}
		}
	}

	return true;
}

template <typename State>
void TemplatePolyhedronContext<State>::execBeforeFirstSegment() {
	//Modify this->mComputationState depending on TPolySettings to either only use
	//1.Initial constraints (are often boxes)
	//2.Initial constraints + location invariants
	//3.Initial constraints + location invariants + flow constraints
	//4.Initial constraints + location invariants + flow constraints + all relevant bad states constraints
	//5.Octagons

	//std::cout << "TemplatePolyhedronContext::execBeforeFirstSegment, this->mComputationState before: \n" << this->mComputationState << std::endl;
	assert( this->mComputationState.getSetType() == representation_name::polytope_t );
	for ( std::size_t index = 0; index < this->mComputationState.getNumberSets(); ++index ) {
		//TODO: Somehow get tpoly without overriding settings
		//auto tpolySetting = std::visit(genericSettingVisitor<decltype(this->mComputationState.getSet(index))>(), this->mComputationState.getSet(index));
		//using TPolyType = TemplatePolyhedron<typename State::NumberType, hypro::Converter<Number>, decltype(tpolySetting)>
		//auto tpoly = std::visit(genericConvertAndGetVisitor<TPolyType>(), this->mComputationState.getSet(index));
		auto tpoly = std::visit( genericConvertAndGetVisitor<TemplatePolyhedron<Number>>(), this->mComputationState.getSet( index ) );
		if ( tpoly.getSettings().TEMPLATE_SHAPE != TEMPLATE_CONTENT::OCTAGON ) {
			tpoly = createTemplateContent( tpoly );
			this->mComputationState.setSet( std::visit( genericInternalConversionVisitor<typename State::repVariant, TemplatePolyhedron<Number>>( tpoly ), this->mComputationState.getSet( index ) ), index );
		} else {
			std::cout << "TemplatePolyhedronContext::execBeforeFirstSegment, OCTAGON setting" << std::endl;
			TemplatePolyhedron<Number> octagon( this->mComputationState.getDimension(), 8 );
			auto evalInOctagonDirs = tpoly.multiEvaluate( octagon.matrix() );
			vector_t<Number> evalRes( evalInOctagonDirs.size() );
			for ( int i = 0; i < evalRes.rows(); ++i ) {
				assert( evalInOctagonDirs[i].errorCode == SOLUTION::FEAS );
				evalRes( i ) = evalInOctagonDirs[i].supportValue;
			}
			octagon.setVector( evalRes );
			this->mComputationState.setSet( std::visit( genericInternalConversionVisitor<typename State::repVariant, TemplatePolyhedron<Number>>( octagon ), this->mComputationState.getSet( index ) ), index );
		}

		//Call Location Invariant Strengthening on current invariants
		if ( tpoly.getSettings().USE_LOCATION_INVARIANT_STRENGTHENING 
			&& tpoly.getSettings().TEMPLATE_SHAPE >= TEMPLATE_CONTENT::INIT_INV 
			&& this->mComputationState.getLocation()->getInvariant().size() >= this->mComputationState.getDimension() + 1) {
			std::cout << "TemplatePolyhedronContext::execBeforeFirstSegment, check for locationInvariantStrengthening" << std::endl;
			TemplatePolyhedron<Number> invTPoly( this->mComputationState.getLocation()->getInvariant().getMatrix(), this->mComputationState.getLocation()->getInvariant().getVector() );
			std::cout << "TemplatePolyhedronContext::execBeforeFirstSegment, invTPoly before overapprox: " << invTPoly << std::endl;
			if ( invTPoly.isBounded() && !invTPoly.empty() ) {
				std::cout << "TemplatePolyhedronContext::execBeforeFirstSegment, invTPoly was bounded!" << std::endl;
				invTPoly = invTPoly.overapproximate( tpoly.matrix() );
				std::cout << "TemplatePolyhedronContext::execBeforeFirstSegment, overapproximate inv with tpoly dirs: " << invTPoly << std::endl;
				//auto tmp = isPositiveInvariant(tpoly, invTPoly.vector());
				//std::cout << "TemplatePolyhedronContext::execBeforeFirstSegment, is tpoly positive invariant? " << tmp << std::endl;
				//if(tmp){
				if ( isPositiveInvariant( tpoly, invTPoly.vector() ) ) {
					std::cout << "TemplatePolyhedronContext::execBeforeFirstSegment, use locationInvariantStrengthening" << std::endl;
					//mRelaxedInvariant = vector_t<Number>::Zero(invTPoly.matrix().rows());
					mRelaxedInvariant = locationInvariantStrengthening( invTPoly, tpoly.vector() );
					std::cout << "TemplatePolyhedronContext::execBeforeFirstSegment, mRelaxedInvariant is: " << mRelaxedInvariant << std::endl;
					std::cout << "TemplatePolyhedronContext::execBeforeFirstSegment, end beforehand" << std::endl;
				} else {
					mRelaxedInvariant = invTPoly.vector();
				}
			} else {
				//mRelaxedInvariant = vector_t<Number>::Zero(invTPoly.vector().rows());
				//default to dimension size such that FSHandler can compare to that
				//mRelaxedInvariant = vector_t<Number>::Zero(invTPoly.matrix().cols());
				//default to tpoly matrix rows size such that FSHandler can compare to that
				mRelaxedInvariant = vector_t<Number>::Zero( tpoly.matrix().rows() );
			}
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
			std::cout << "TemplatePolyhedronContext::firstSegment, use USE_ALTERNATIVE_REACH_ALGO!" << std::endl;
			//this->mFirstSegmentHandlers.at(i)->handle();
			static_cast<TPolyFirstSegmentHandler<State>*>( this->mFirstSegmentHandlers.at( i ) )->setInvariant( mRelaxedInvariant );
			static_cast<TPolyFirstSegmentHandler<State>*>( this->mFirstSegmentHandlers.at( i ) )->handle();
		}
	} else {
		for ( std::size_t i = 0; i < this->mComputationState.getNumberSets(); i++ ) {
			std::cout << "TemplatePolyhedronContext::firstSegment, use standard reach algo!" << std::endl;
			static_cast<ltiFirstSegmentHandler<State>*>( this->mFirstSegmentHandlers.at( i ) )->ltiFirstSegmentHandler<State>::handle();
			//this->mFirstSegmentHandlers.at(i)->ltiFirstSegmentHandler<State>::handle();
		}
	}
	//Do the stuff ltiContext would to
	this->initializeInvariantHandlers();
	this->initializeBadStateHandlers();
}

template <typename State>
void TemplatePolyhedronContext<State>::applyContinuousEvolution() {
	//std::cout << "TemplatePolyhedronContext::applyContinuousEvolution" << std::endl;
	if ( TemplatePolyhedron<Number>::Settings::USE_ALTERNATIVE_REACH_ALGO ) {
		for ( std::size_t i = 0; i < this->mComputationState.getNumberSets(); i++ ) {
			//std::cout << "TemplatePolyhedronContext::applyContinuousEvolution, use USE_ALTERNATIVE_REACH_ALGO!" << std::endl;
			//this->mContinuousEvolutionHandlers.at(i)->handle();
			static_cast<TPolyTimeEvolutionHandler<State>*>( this->mContinuousEvolutionHandlers.at( i ) )->setInvariant( mRelaxedInvariant );
			static_cast<TPolyTimeEvolutionHandler<State>*>( this->mContinuousEvolutionHandlers.at( i ) )->handle();
		}
	} else {
		for ( std::size_t i = 0; i < this->mComputationState.getNumberSets(); i++ ) {
			//std::cout << "TemplatePolyhedronContext::applyContinuousEvolution, use standard reach algo!" << std::endl;
			static_cast<ltiTimeEvolutionHandler<State>*>( this->mContinuousEvolutionHandlers.at( i ) )->ltiTimeEvolutionHandler<State>::handle();
			//this->mContinuousEvolutionHandlers.at(i)->ltiTimeEvolutionHandler<State>::handle();
		}
	}
	//Do the stuff ltiContext would to
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

}  // namespace hypro
