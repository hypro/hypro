/* This file contains helper functions.
 * @file   helper.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	2014-11-27
 * @version	2014-11-27
 */

#pragma once

namespace hypro {
namespace parser {

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
		std::string flowname = _state.mFlow.mName;
		matrix flow;
		bool incomplete = false;
		if(flowname != "")
		{
			auto pos = _matrices.find(flowname);
			if(pos == _matrices.end())
			{
				if(!_state.mFlow.mMatrix.empty())
				{
					flow = createMatrix(_state.mFlow.mMatrix);
					_matrices.insert(std::make_pair(flowname, flow));
				}
				else
				{
					incomplete = true;
				}
			}
			else
			{
				assert(_state.mFlow.mMatrix.empty());
				flow = (*pos).second;
			}
		}
		else
		{
			flow = createMatrix(_state.mFlow.mMatrix);
		}

		// get invariant
		std::string invname = _state.mInvariant.mName;
		matrix invMatrix;
		if(invname != "")
		{
			auto pos = _matrices.find(invname);
			if(pos == _matrices.end())
			{
				if(!_state.mInvariant.mMatrix.empty())
				{
					invMatrix = createMatrix(_state.mInvariant.mMatrix);
					_matrices.insert(std::make_pair(invname, flow));
				}
				else
				{
					incomplete = true;
				}
			}
			else
			{
				assert(_state.mInvariant.mMatrix.empty());
				invMatrix = (*pos).second;
			}
		}
		else
		{
			invMatrix = createMatrix(_state.mFlow.mMatrix);
		}

		// Todo: do we always compare with lesseq 0?
		hypro::vector_t<double> vec = hypro::vector_t<double>(invMatrix.rows());
		for(unsigned i = 0; i<invMatrix.rows(); ++i)
			vec(i) = double(0);

		if(!incomplete)
		{
			_loc.setActivityMat(flow);
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