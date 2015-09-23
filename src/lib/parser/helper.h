/* This file contains helper functions.
 * @file   helper.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	2014-11-27
 * @version	2014-11-27
 */

#include "utils.h"

#pragma once

namespace hypro {
namespace parser {

template <typename Number>
static std::pair<matrix_t<Number>, bool> insertMatrix( const std::vector<std::vector<Number>>& _rawMatrix,
													   const std::string& _name,
													   std::map<std::string, matrix_t<Number>>& _matrices ) {
	if ( _name != "" )  // non-anonymous (named) matrix_t<Number>
	{
		auto pos = _matrices.find( _name );
		if ( pos == _matrices.end() )  // create new named matrix_t<Number>
		{
			if ( !_rawMatrix.empty() ) {
				matrix_t<Number> result = createMatrix( _rawMatrix );
				_matrices.insert( std::make_pair( _name, result ) );
				return std::make_pair( result, false );
			} else  // the matrix_t<Number> is not given -> we wait after parsing if it is defined in the following
					// locations
			{
				matrix_t<Number> result;
				return std::make_pair( result, true );
			}
		} else  // the matrix_t<Number> has already been defined - it cannot be overridden
		{
			return std::make_pair( ( *pos ).second, false );
		}
	}

	// anonymous matrix_t<Number> - create once
	matrix_t<Number> result = createMatrix( _rawMatrix );
	return std::make_pair( result, false );
}

/**
 * Converts a parsed state struct to a location object for hybrid automata
 * @param _state The parsed state.
 * @return
 */
template <typename Number>
static bool createLocFromState( const State<Number>& _state, Location<Number>* const _loc,
								std::map<std::string, matrix_t<Number>>& _matrices,
								std::queue<State<Number>>& _incompletes ) {
	bool incomplete = false;
	std::string flowname = _state.mFlow.mName;
	matrix_t<Number> flow;
	std::pair<matrix_t<Number>, bool> res = insertMatrix( _state.mFlow.mMatrix, flowname, _matrices );
	bool incompleteFlow = res.second;
	if ( !incompleteFlow ) flow = res.first;

	// get invariant
	std::string invname = _state.mInvariant.mName;
	bool invariant = ( !_state.mInvariant.mMatrix.empty() || invname != "" );
	matrix_t<Number> invMatrix;
	bool incompleteInvariant = false;
	if ( invariant ) {
		res = insertMatrix( _state.mInvariant.mMatrix, invname, _matrices );
		incompleteInvariant = res.second;
		if ( !incompleteInvariant ) invMatrix = res.first;
	}

	// Todo: do we always compare with lesseq 0?
	hypro::vector_t<Number> vec = hypro::vector_t<Number>( invMatrix.rows() );
	for ( unsigned i = 0; i < invMatrix.rows(); ++i ) vec( i ) = Number( 0 );

	incomplete = incompleteFlow || incompleteInvariant;
	if ( !incomplete ) {
		_loc->setActivityMat( flow );
		_loc->setActivityVec( vec );
		if ( invariant ) _loc->setInvariant( invMatrix, vec, hypro::operator_e::LEQ );

		return true;
	} else {
		_incompletes.push( _state );
		return false;
	}
}

template <typename Number>
static bool createTransition( const hypro::parser::Transition<Number>& _transition, hypro::Transition<Number>* _tran,
							  const std::map<unsigned, Location<Number>*>& _locations,
							  std::map<std::string, matrix_t<Number>>& _matrices,
							  std::queue<Transition<Number>>& _incompletes ) {
	bool incomplete = false;

	auto sourceLocIt = _locations.find( _transition.mSource );
	auto targetLocIt = _locations.find( _transition.mTarget );
	if ( sourceLocIt == _locations.end() || targetLocIt == _locations.end() ) incomplete = true;

	std::pair<matrix_t<Number>, bool> res;

	bool incompleteGuard = false;
	bool hasGuard = ( !_transition.mGuard.mMatrix.empty() || _transition.mGuard.mName != "" );
	matrix_t<Number> guard;
	if ( hasGuard ) {
		res = insertMatrix( _transition.mGuard.mMatrix, _transition.mGuard.mName, _matrices );
		incompleteGuard = res.second;
		if ( !incompleteGuard ) guard = res.first;
	}

	bool incompleteReset = false;
	bool hasReset = ( !_transition.mReset.mMatrix.empty() || _transition.mReset.mName != "" );
	matrix_t<Number> reset;
	if ( hasReset ) {
		res = insertMatrix( _transition.mReset.mMatrix, _transition.mReset.mName, _matrices );
		incompleteReset = res.second;
		if ( !incompleteReset ) reset = res.first;
	}

	// Todo: do we always compare with lesseq 0?
	hypro::vector_t<Number> vecGuard = hypro::vector_t<Number>( guard.rows() );
	for ( unsigned i = 0; i < guard.rows(); ++i ) vecGuard( i ) = Number( 0 );
	hypro::vector_t<Number> vecReset = hypro::vector_t<Number>( reset.rows() );
	for ( unsigned i = 0; i < reset.rows(); ++i ) vecReset( i ) = Number( 0 );

	incomplete = incomplete || incompleteGuard || incompleteReset;

	if ( !incomplete ) {
		_tran->setStartLoc( sourceLocIt->second );
		_tran->setTargetLoc( targetLocIt->second );

		struct hypro::Transition<Number>::guard tmpGuard;
		tmpGuard.mat = guard;
		tmpGuard.op = hypro::operator_e::LEQ;
		tmpGuard.vec = vecGuard;

		struct hypro::Transition<Number>::assignment tmpReset;
		tmpReset.transformMat = reset;
		tmpReset.translationVec = vecReset;

		_tran->setGuard( tmpGuard );
		_tran->setAssignment( tmpReset );

		return true;
	} else {
		_incompletes.push( _transition );
		return false;
	}
}

}  // namespace
}  // namespace