#pragma once
#include "../../datastructures/Halfspace.h"
#include <carl/interval/Interval.h>
#include <carl/interval/IntervalEvaluation.h>

namespace hypro {

	/**
	 * @brief      Performs intersection of a vector of intervals with a halfspace.
	 * @details    The idea is to use ICP-style contractions to obtain the resulting box.
	 * As we know the constraint (the halfspace) is linear, we only need to perform one contraction per dimension and the order does not matter.
	 * @param      intervals  The intervals as a vector (call by reference).
	 * @param[in]  hsp        The halfspace
	 *
	 * @tparam     Number     The used number type.
	 *
	 * @return     True, if one of the resulting intervals is empty, False otherwise.
	 */
	template<typename Number>
	bool icpIntersectHalfspace(std::vector<carl::Interval<Number>>& intervals, const Halfspace<Number>& hsp) {
		assert(Eigen::Index(intervals.size()) == hsp.normal().rows());

		// contraction variable cVar, other variables (for that run) oVar.
		for(Eigen::Index cVar = 0; cVar < hsp.normal().rows(); ++cVar) {
			if(hsp.normal()(cVar) != 0) {
				// initialize with constant part.
				carl::Interval<Number> newIntv = Number(-1) * carl::Interval<Number>(hsp.offset(),carl::BoundType::INFTY,hsp.offset(),carl::BoundType::WEAK);
				// update interval using interval arithmetic (ICP-style: propagation).
				for(Eigen::Index oVar = 0; oVar < hsp.normal().rows(); ++oVar) {
					if(cVar != oVar && hsp.normal()(oVar) != 0) {
						newIntv += hsp.normal()(oVar)*intervals[oVar];
					}
				}
				newIntv /= Number(-hsp.normal()(cVar));

				intervals[cVar] = intervals[cVar].intersect(newIntv);
				if(intervals[cVar].isEmpty()) {
					return true;
				}
			}

		}
		return false;

		/*
		carl::MultivariatePolynomial<Number> hspNormal;
		std::map<carl::Variable, carl::Interval<Number>> intervalMap;
		std::vector<carl::Variable> posVector; // maps hypro dimension to carl::Variable

		for(Eigen::Index pos = 0; pos < hsp.normal().rows(); ++pos) {
			carl::Variable tmp = carl::freshVariable(carl::VariableType::VT_REAL);
			intervalMap[tmp] = intervals.at(pos);
			if(hsp.normal()(pos) != 0){
				hspNormal.addTerm(carl::Term<Number>(hsp.normal()(pos),tmp,1));
			}
			posVector.push_back(tmp);
		}

		carl::Variable constant = carl::freshVariable(carl::VariableType::VT_REAL);
		hspNormal.addTerm(carl::Term<Number>(Number(-1),constant,1));
		intervalMap[constant] = carl::Interval<Number>(hsp.offset(),carl::BoundType::INFTY,hsp.offset(),carl::BoundType::WEAK);

		std::cout << "Resulting Polynomial: " << hspNormal << std::endl;

		// contraction
		for(unsigned i = 0; i < hspNormal.size(); ++i){
			if(hspNormal[i].coeff() != 0) {
				std::cout << "Solved for " << hspNormal[i].monomial()->getSingleVariable();
				carl::MultivariatePolynomial<Number> t = (hspNormal - hspNormal[i]) / Number(-hspNormal[i].coeff());
				std::cout << ": " << t << std::endl;
				carl::Interval<Number> newIntv = carl::IntervalEvaluation::evaluate(t,intervalMap);
				std::cout << "New interval: " << newIntv << std::endl;
				assert(hspNormal[i].monomial()->isLinear());
				auto tmp = intervalMap[hspNormal[i].monomial()->getSingleVariable()].intersect(newIntv);
				std::cout << "After intersection: " << tmp << std::endl;
				intervalMap[hspNormal[i].monomial()->getSingleVariable()] = tmp;
			}
		}

		// creation of result vector
		std::vector<carl::Interval<Number>> res;
		for(Eigen::Index i = 0; i < hsp.normal().rows(); ++i) {
			res.emplace_back(intervalMap[posVector[i]]);
		}

		return res;
		*/
	}

} // namespace hypro
