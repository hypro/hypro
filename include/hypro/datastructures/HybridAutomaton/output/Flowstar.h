/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once
#include "../../reachability/Settings.h"
#include "../Condition.h"
#include "../HybridAutomaton.h"

#include <iosfwd>

namespace hypro {

template <typename Number>
std::string toFlowstarFormat( const matrix_t<Number>& in,
							  const std::map<Eigen::Index, std::string>& varNameMap,
							  const std::string& prefix ) {
	assert( in.rows() == 1 );
	std::stringstream res;
	res << std::fixed << prefix;
	bool first = true;
	for ( Eigen::Index colI = 0; colI < in.cols(); ++colI ) {
		// const part
		if ( colI == in.cols() - 1 ) {
			if ( first ) {
				res << in( 0, colI );
			} else {
				if ( in( 0, colI ) < 0 )
					res << in( 0, colI );
				else
					res << " + " << in( 0, colI );
			}
		} else {
			if ( in( 0, colI ) > 0 ) {
				if ( !first ) {
					res << " +";
				} else {
					first = false;
				}
				if ( in( 0, colI ) != 1 ) {
					res << in( 0, colI );
				}
			} else if ( in( 0, colI ) < 0 ) {
				res << " " << in( 0, colI );
				if ( first ) {
					first = false;
				}
			}
			if ( in( 0, colI ) != 0 && in( 0, colI ) != 1 ) {
				res << "*";
				res << varNameMap.at( colI );
			}
		}
	}
	res << std::scientific;
	return res.str();
}

template <typename Number>
std::string toFlowstarFormat( const Condition<Number>& in,
							  const std::map<Eigen::Index, std::string>& varNameMap,
							  const std::string& prefix ) {
	std::stringstream res;
	if ( in.size() > 0 ) {
		res << std::fixed;
		for ( Eigen::Index rowI = 0; rowI < in.getMatrix().rows(); ++rowI ) {
			res << prefix;
			bool first = true;
			for ( Eigen::Index colI = 0; colI < in.getMatrix().cols(); ++colI ) {
				if ( in.getMatrix()( rowI, colI ) > 0 ) {
					if ( !first ) {
						res << " +";
					} else {
						first = false;
					}
					if ( in.getMatrix()( rowI, colI ) != 1 ) {
						res << in.getMatrix()( rowI, colI ) << "*";
					}
				} else if ( in.getMatrix()( rowI, colI ) < 0 ) {
					if ( first ) {
						first = false;
					}
					res << " " << in.getMatrix()( rowI, colI ) << "*";
				}
				if ( in.getMatrix()( rowI, colI ) != 0 && colI != in.getMatrix().cols() && varNameMap.size() > std::size_t( colI ) ) {
					res << varNameMap.at( colI );
				}
			}
			// if first is still true, this was a zero-row, which should be skipped
			if ( !first ) {
				res << " <= " << in.getVector()( rowI );
			}
		}
		res << std::scientific;
	}
	return res.str();
}

template <typename Number>
std::string toFlowstarFormat( const ConstraintSetT<Number>& in,
							  const std::map<Eigen::Index, std::string>& varNameMap,
							  const std::string& prefix ) {
	return toFlowstarFormat( Condition<Number>( in.matrix(), in.vector() ), varNameMap, prefix );
}

template <typename Number>
std::string toFlowstarFormat( const flowVariant<Number>& f,
							  const std::map<Eigen::Index, std::string>& varNameMap,
							  const std::string& prefix ) {
	std::stringstream out;
	switch ( getFlowType( f ) ) {
		case DynamicType::timed:
		case DynamicType::discrete:
		case DynamicType::linear: {
			matrix_t<Number> flow = std::get<linearFlow<Number>>( f ).getFlowMatrix();
			for ( Eigen::Index rowI = 0; rowI < flow.rows() - 1; ++rowI ) {
				std::stringstream tmp;
				tmp << prefix << "\t\t" << varNameMap.at( rowI ) << "' = ";
				out << toFlowstarFormat( matrix_t<Number>( flow.row( rowI ) ), varNameMap, tmp.str() );
			}
			break;
		}
		case DynamicType::affine: {
			matrix_t<Number> flow = std::get<affineFlow<Number>>( f ).getFlowMatrix();
			vector_t<Number> constPart = std::get<affineFlow<Number>>( f ).getTranslation();
			for ( Eigen::Index rowI = 0; rowI < flow.rows(); ++rowI ) {
				std::stringstream tmp;
				tmp << prefix << "\t\t" << varNameMap.at( rowI ) << "' = ";
				matrix_t<Number> tmpMatrix = matrix_t<Number>( 1, flow.cols() + 1 );
				tmpMatrix << flow.row( rowI ), constPart( rowI );
				out << toFlowstarFormat( tmpMatrix, varNameMap, tmp.str() );
			}
			break;
		}
		case DynamicType::rectangular: {
			auto flow = std::get<rectangularFlow<Number>>( f ).getFlowIntervals();
			for ( const auto& vFlowPair : flow ) {
				out << prefix << "\t\t" << vFlowPair.first << "' in " << vFlowPair.second;
			}
			break;
		}
		case DynamicType::singular: {
			throw NotImplemented( "Output of singular dynamics not yet implemented." );
			break;
		}
		case DynamicType::mixed: {
			throw NotImplemented( "Output of mixed dynamics not yet implemented." );
			break;
		}
		default:
			throw std::logic_error( "Cannot output dynamics of type 'undefined'." );
	}
	return out.str();
}

template <typename Number>
std::string toFlowstarFormat( const Location<Number>* loc,
							  const std::map<Eigen::Index, std::string>& varNameMap,
							  const std::string& prefix ) {
	std::stringstream out;
	// location name
	out << prefix << loc->getName();
	out << prefix << "{";
	if ( varNameMap.size() > 0 ) {
		assert( varNameMap.size() == std::size_t( loc->dimension() ) );
		// flow
		out << prefix << "\tpoly ode 1";
		out << prefix << "\t{";
		out << toFlowstarFormat<Number>( *( loc->getFlows().begin() ), varNameMap, prefix );
		out << prefix << "\t}";
		// invariant
		out << prefix << "\tinv";
		out << prefix << "\t{";
		std::stringstream invPrefix;
		invPrefix << prefix << "\t\t";
		out << toFlowstarFormat( loc->getInvariant(), varNameMap, invPrefix.str() );
		out << prefix << "\t}";
	}
	out << "\n\t\t}";
	return out.str();
}

std::string toFlowstarFormat( const ReachabilitySettings& settings,
							  const std::map<Eigen::Index, std::string>& varNameMap,
							  const std::string& prefix );

template <typename Number>
std::string toFlowstarFormat( const HybridAutomaton<Number>& in, const ReachabilitySettings& settings = ReachabilitySettings() ) {
	std::stringstream res;
	std::map<Eigen::Index, std::string> vars;
	for ( std::size_t i = 0; i < in.getVariables().size(); ++i ) {
		vars[i] = in.getVariables()[i];
	}

	res << "hybrid reachability\n{\n";

	if ( !in.getLocations().empty() ) {
		if ( in.dimension() > 0 ) {
			// variables (note: the last dimension is for constants)
			res << "\tstate var ";
			if ( !vars.count( 0 ) ) {
				vars[0] = "x_0";
			}
			res << vars[0];
			for ( std::size_t cnt = 1; cnt < in.dimension(); ++cnt ) {
				if ( !vars.count( cnt ) ) {
					vars[cnt] = "x_" + std::to_string( cnt );
				}
				res << ", " << vars[cnt];
			}
			res << "\n";
		}

		// Todo: add out-commented exemplary settings
		res << toFlowstarFormat( settings, vars, "\n" );

		// locations
		res << "\tmodes\n\t{\n";
		for ( auto& locPtr : in.getLocations() ) {
			res << toFlowstarFormat( locPtr, vars, "\n\t\t" );
		}
		res << "\n\t}\n";

		// transitions
		res << "\tjumps\n\t{";
		if ( !in.getTransitions().empty() ) {
			for ( const auto transPtr : in.getTransitions() ) {
				res << "\n\t\t" << transPtr->getSource()->getName() << " -> " << transPtr->getTarget()->getName();
				if ( transPtr->isUrgent() )
					res << "\n\t\turgent";
				res << "\n\t\tguard {";
				res << toFlowstarFormat( transPtr->getGuard(), vars, " " );
				res << " }";
				res << "\n\t\treset {";
				if ( !transPtr->getReset().empty() ) {
					for ( Eigen::Index rowI = 0; rowI < transPtr->getReset().getMatrix().rows(); ++rowI ) {
						if ( !transPtr->getReset().isIdentity( rowI ) ) {
							std::stringstream tmp;
							tmp << " " << vars[rowI] << "' := ";
							matrix_t<Number> tmpBlock = matrix_t<Number>::Zero( 1, transPtr->getReset().getMatrix().cols() + 1 );
							tmpBlock.block( 0, 0, 1, transPtr->getReset().getMatrix().cols() ) = transPtr->getReset().getMatrix().row( rowI );
							tmpBlock( 0, transPtr->getReset().getMatrix().cols() ) = transPtr->getReset().getVector()( rowI );
							res << toFlowstarFormat( tmpBlock, vars, tmp.str() );
						}
					}
				}
				res << " }";
				if ( !transPtr->getLabels().empty() ) {
					res << "\n\t\tlabel { ";
					bool first = true;
					for ( const auto& label : transPtr->getLabels() ) {
						if ( first ) {
							res << label;
							first = false;
						} else {
							res << ", " << label;
						}
					}
					res << " }";
				}
				if ( transPtr->getAggregation() ) {
					res << "\n\t\tparallelotope aggregation {}";
				}
				res << "\n";
			}
		}
		res << "\n\t}\n";

		// initial states
		res << "\tinit\n\t{";
		for ( const auto& s : in.getInitialStates() ) {
			res << "\n\t\t" << s.first->getName();
			res << "\n\t\t{";
			auto tmpConstraintSet = s.second;
			res << toFlowstarFormat( tmpConstraintSet, vars, "\n\t\t\t" );
			res << "\n\t\t}";
		}

		res << "\n\t}\n";

		// bad states
		if ( in.getLocalBadStates().size() > 0 || in.getGlobalBadStates().size() > 0 ) {
			res << "\n\tunsafe set\n\t{";
			for ( const auto& [loc, cond] : in.getLocalBadStates() ) {
				res << "\n\t\t" << loc->getName() << "{";
				res << toFlowstarFormat( cond, vars, "\n\t\t\t" );
				res << "\n\t\t}";
			}
			for ( const auto& cond : in.getGlobalBadStates() ) {
				res << toFlowstarFormat( cond, vars, "\n\t\t" );
			}
			res << "\n\t}\n";
		}
	}

	res << "}\n";
	return res.str();
}

}  // namespace hypro
