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
	
	
	static std::pair<matrix, bool> insertMatrix(const std::vector<std::vector<double>>& _rawMatrix, const std::string& _name, std::map<std::string, matrix>& _matrices)
	{
		std::cout << "Name: " << _name << std::endl;
		if(_name != "") // non-anonymous (named) matrix
		{
			auto pos = _matrices.find(_name);
			if(pos == _matrices.end()) // create new named matrix
			{
				if(!_rawMatrix.empty())
				{
					matrix result = createMatrix(_rawMatrix);
					_matrices.insert(std::make_pair(_name, result));
					std::cout << "added matrix " << _name << " to pool." << std::endl;
					return std::make_pair(result,false);
				}
				else // the matrix is not given -> we wait after parsing if it is defined in the following locations
				{
					matrix result;
					return std::make_pair(result,true);
				}
			}
			else // the matrix has already been defined - make sure it is not overridden
			{
				assert(_rawMatrix.empty());
				std::cout << "Insert already named matrix " << _name << std::endl;
				return std::make_pair((*pos).second, false);
			}
		}
		
		// anonymous matrix - create once
		std::cout << "anonymous matrix" << std::endl;
		matrix result = createMatrix(_rawMatrix);
		return std::make_pair(result,false);
	}

	/**
	 * Converts a parsed state struct to a location object for hybrid automata
     * @param _state The parsed state.
     * @return
     */
	static bool createLocFromState(
			const State& _state, 
			Location<double>& _loc,
			std::map<std::string, matrix>& _matrices, 
			std::queue<State>& _incompletes)
	{
		bool incomplete;
		std::string flowname = _state.mFlow.mName;
		matrix flow;
		std::pair<matrix, bool> res = insertMatrix(_state.mFlow.mMatrix, flowname, _matrices);
		incomplete = res.second;
		if(!incomplete)
			flow = res.first;
		
		// get invariant
		std::string invname = _state.mInvariant.mName;
		bool invariant = (!_state.mInvariant.mMatrix.empty() || invname != "");
		matrix invMatrix;
		if(invariant)
		{
			res = insertMatrix(_state.mInvariant.mMatrix, invname, _matrices);
			incomplete = res.second;
			if(!incomplete)
				invMatrix = res.first;
		}

		// Todo: do we always compare with lesseq 0?
		hypro::vector_t<double> vec = hypro::vector_t<double>(invMatrix.rows());
		for(unsigned i = 0; i<invMatrix.rows(); ++i)
			vec(i) = double(0);

		if(!incomplete)
		{
			_loc.setActivityMat(flow);
			_loc.setActivityVec(vec);
			if(invariant)
				_loc.setInvariant(invMatrix, vec, hypro::operator_e::LEQ);

			std::cout << _loc << std::endl;
			return true;
		}
		else
		{
			_incompletes.push(_state);
			return false;
		}
		
	}
	
} // namespace
} // namespace