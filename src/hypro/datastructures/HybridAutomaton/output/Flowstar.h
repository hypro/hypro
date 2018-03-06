#pragma once
#include "../HybridAutomaton.h"
#include "../Condition.h"
#include <iostream>

namespace hypro {

	template<typename Number>
	std::string toFlowstarFormat(const Condition<Number>& in,
								const std::map<Eigen::Index, std::string>& varNameMap,
								const std::string& prefix)
	{
		std::stringstream res;
		if(in.size() > 0) {
			for(Eigen::Index rowI = 0; rowI < in.getMatrix().rows(); ++rowI) {
				res << prefix;
				bool first = true;
				for(Eigen::Index colI = 0; colI < in.getMatrix().cols(); ++colI) {
					if(in.getMatrix()(rowI,colI) > 0) {
						if(!first){
							res << " +";
						} else {
							first = false;
						}
						if(in.getMatrix()(rowI,colI) != 1) {
							res << in.getMatrix()(rowI,colI) << "*";
						}
					} else if(in.getMatrix()(rowI,colI) < 0) {
						res << " " << in.getMatrix()(rowI,colI) << "*";
					}
					if(in.getMatrix()(rowI,colI) != 0 && colI != in.getMatrix().cols() && varNameMap.size() > std::size_t(colI)) {
						res << varNameMap.at(colI);
					}
				}
				res << " <= " << in.getVector()(rowI);
			}
		}
		return res.str();
	}

	template<typename Number>
	std::string toFlowstarFormat(const ConstraintSet<Number>& in,
								const std::map<Eigen::Index, std::string>& varNameMap,
								const std::string& prefix)
	{
		return toFlowstarFormat(Condition<Number>(in.getMatrix(),in.getVector()), varNameMap, prefix);
	}

	template<typename Number>
	std::string toFlowstarFormat(const matrix_t<Number>& in,
								const std::map<Eigen::Index, std::string>& varNameMap,
								const std::string& prefix)
	{
		assert(in.rows() == 1);
		std::stringstream res;
		res << prefix;
		bool first = true;
		for(Eigen::Index colI = 0; colI < in.cols(); ++colI) {
			if(in(0,colI) > 0) {
				if(!first){
					res << " +";
				} else {
					first = false;
				}
				if(in(0,colI) != 1) {
					res << in(0,colI);
				}
			} else if(in(0,colI) < 0) {
				res << " " << in(0,colI);
			}
			if(in(0,colI) != 0 && colI != in.cols()-1 && in(0,colI) != 1) {
				res << "*";
			}
			if(in(0,colI) != 0 && colI != in.cols()-1) {
				res << varNameMap.at(colI);
			}
			// const part
			if(colI == in.cols()-1) {
				if(first){
					res << in(0,colI);
				} else {
					if(in(0,colI) < 0)
						res << in(0,colI);
					else
						res << " + " << in(0,colI);
				}
			}
		}
		return res.str();
	}

	template<typename Number>
	std::string toFlowstarFormat(const Location<Number>* loc,
								const std::map<Eigen::Index, std::string>& varNameMap,
								const std::string& prefix) {
		std::stringstream out;
		// location name
		out << prefix <<loc->getName();
		out << prefix << "{";
		if(varNameMap.size() > 0) {
			assert(varNameMap.size() == std::size_t(loc->getFlow().rows()-1));
			// flow
			out << prefix << "\tpoly ode 1";
			out << prefix << "\t{";
			for(Eigen::Index rowI = 0; rowI < loc->getFlow().rows()-1; ++rowI) {
				std::stringstream tmp;
				tmp << prefix << "\t\t" << varNameMap.at(rowI) << "' = ";
				out << toFlowstarFormat(matrix_t<Number>(loc->getFlow().row(rowI)), varNameMap, tmp.str());
			}
			out << prefix << "\t}";
			// invariant
			out << prefix << "\tinv";
			out << prefix << "\t{";
			std::stringstream invPrefix;
			invPrefix << prefix << "\t\t";
			out << toFlowstarFormat(loc->getInvariant(), varNameMap, invPrefix.str());
			out << prefix << "\t}";
		}
		out << "\n\t\t}";
		return out.str();
	}

	template<typename Number>
	std::string toFlowstarFormat(const ReachabilitySettings<Number>& settings,
								 const std::map<Eigen::Index, std::string>& varNameMap,
								 const std::string& prefix) {
		std::stringstream res;

		res << prefix << "settings";
		res << prefix << "{";
		res << prefix << "\tfixed steps " << settings.timeStep;
		res << prefix << "\ttime " << settings.timeBound;
		if(!settings.plotDimensions.empty()) {
			for(const auto& dims : settings.plotDimensions) {
				assert(dims.size() == 2);
				res << prefix << "\tgnuplot octagon " << varNameMap.at(dims[0]) << "," varNameMap.at(dims[1]);
			}
		}

		res << prefix << "\toutput" << settings.fileName;
		res << prefix << "\tmax jumps" << settings.jumpDepth;
		res << prefix << "}";

		return res.str();
	}


	template<typename Number>
	std::string toFlowstarFormat(const HybridAutomaton<Number>& in, const ReachabilitySettings& settings = ReachabilitySettings() ) {
		std::stringstream res;
		std::map<Eigen::Index, std::string> vars;

		res << "hybrid reachability\n{\n";

		if(!in.getLocations().empty()) {
			if( in.dimension() > 0 ) {
				// variables (note: the last dimension is for constants)
				res << "\tstate var x_0";
				vars[0] = "x_0";
				for(std::size_t cnt = 1; cnt < in.dimension(); ++cnt) {
					res << ", x_" << cnt;
					std::stringstream tmp;
					tmp << "x_" << cnt;
					vars[cnt] = tmp.str();
				}
				res << "\n";
			}

			// Todo: add out-commented exemplary settings
			res << toFlowstarFormat(settings,vars,"\n");

			// locations
			res << "\tmodes\n\t{\n";
			for(Location<Number>* locPtr : in.getLocations()) {
				res << toFlowstarFormat(locPtr, vars, "\n\t\t");
			}
			res << "\n\t}\n";

			if(!in.getTransitions().empty()) {
				// transitions
				res << "\tjumps\n\t{";
				for(const auto transPtr : in.getTransitions()) {
					//std::cout << "output transition " << transPtr->getSource()->getName() << " -> " << transPtr->getTarget()->getName() << std::endl;
					res << "\n\t\t" << transPtr->getSource()->getName() << " -> " << transPtr->getTarget()->getName();
					if(transPtr->isUrgent())
						res << "\n\t\turgent";
					res << "\n\t\tguard {";
					res << toFlowstarFormat(transPtr->getGuard(), vars, " ");
					res << " }";
					res << "\n\t\treset {";
					//std::cout << "output reset " << transPtr->getReset().getMatrix() << std::endl;
					for(Eigen::Index rowI = 0; rowI < transPtr->getReset().getMatrix().rows(); ++rowI) {
						std::stringstream tmp;
						tmp << " " << vars[rowI] << "' := ";
						matrix_t<Number> tmpBlock = matrix_t<Number>::Zero(1,transPtr->getReset().getMatrix().cols()+1);
						tmpBlock.block(0,0,1,transPtr->getReset().getMatrix().cols()) = transPtr->getReset().getMatrix().row(rowI);
						tmpBlock(0,transPtr->getReset().getMatrix().cols()) = transPtr->getReset().getVector()(rowI);
						res << toFlowstarFormat(tmpBlock, vars, tmp.str());
					}
					res << " }";
					if(transPtr->getAggregation()) {
						res << "\n\t\tparallelotope aggregation {}";
					}
					res << "\n";
				}
				res << "\n\t}\n";
			}

			// initial states
			res << "\tinit\n\t{";
			for(const auto& s : in.getInitialStates() ) {
				res << "\n\t\t" << s.first->getName();
				res << "\n\t\t{";
				auto tmpConstraintSet = boost::get<ConstraintSet<Number>>(boost::apply_visitor(genericConversionVisitor<typename State_t<Number>::repVariant, Number>(representation_name::constraint_set), s.second.getSet()));
				res << toFlowstarFormat(std::move(Condition<Number>(tmpConstraintSet.matrix(), tmpConstraintSet.vector())), vars, "\n\t\t\t" );
				res << "\n\t\t}";
			}

			res << "\n\t}\n";

			// bad states
			if(in.getLocalBadStates().size() > 0) {
				res << "\n\tunsafe set\n\t{";

				res << "\n\t}\n";
			}


		}

 		res << "}\n";
		return res.str();
	}

}
