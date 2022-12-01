/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created by Stefan Schupp <stefan.schupp@tuwien.ac.at> on 29.11.22.
 */

#ifndef HYPRO_SPACEEX_H
#define HYPRO_SPACEEX_H

#include <hypro/flags.h>

#ifdef HYPRO_ENABLE_SPACEEX_OUTPUT

#include "../../../util/exceptions.h"
#include "../../reachability/Settings.h"
#include "../Condition.h"
#include "../HybridAutomaton.h"

#include <iosfwd>
#include <tinyxml2.h>

namespace hypro {

template <typename Number>
std::string toSpaceExFormat( const matrix_t<Number>& matrix,
							 const std::map<Eigen::Index, std::string>& varNameMap,
							 const std::string& prefix ) {
	assert( matrix.rows() == 1 );
	std::stringstream res;
	res << std::fixed << prefix;
	bool first = true;
	for ( Eigen::Index colI = 0; colI < matrix.cols(); ++colI ) {
		// const part
		if ( colI == matrix.cols() - 1 ) {
			if ( first ) {
				res << matrix( 0, colI );
			} else {
				if ( matrix( 0, colI ) < 0 ) {
					res << matrix( 0, colI );
				} else if ( matrix( 0, colI ) > 0 ) {
					res << " + " << matrix( 0, colI );
				}
			}
		} else {
			if ( matrix( 0, colI ) > 0 ) {
				if ( !first ) {
					res << " +";
				} else {
					first = false;
				}
				if ( matrix( 0, colI ) != 1 ) {
					res << matrix( 0, colI );
				}
			} else if ( matrix( 0, colI ) < 0 ) {
				res << " " << matrix( 0, colI );
				if ( first ) {
					first = false;
				}
			}
			if ( matrix( 0, colI ) != 0 ) {
				if ( matrix( 0, colI ) != 1 ) {
					res << "*";
				}
				res << varNameMap.at( colI );
			}
		}
	}
	res << std::scientific;
	return res.str();
}

template <typename Number>
std::string toSpaceExFormat( const Condition<Number>& condition,
							 const std::map<Eigen::Index, std::string>& varNameMap ) {
	std::stringstream res;
	if ( condition.size() > 0 ) {
		res << std::fixed;
		for ( Eigen::Index rowI = 0; rowI < condition.getMatrix().rows(); ++rowI ) {
			bool first = true;
			for ( Eigen::Index colI = 0; colI < condition.getMatrix().cols(); ++colI ) {
				if ( condition.getMatrix()( rowI, colI ) > 0 ) {
					if ( !first ) {
						res << " +";
					} else {
						first = false;
					}
					if ( condition.getMatrix()( rowI, colI ) != 1 ) {
						res << condition.getMatrix()( rowI, colI ) << "*";
					}
				} else if ( condition.getMatrix()( rowI, colI ) < 0 ) {
					if ( first ) {
						first = false;
					}
					res << " " << condition.getMatrix()( rowI, colI ) << "*";
				}
				if ( condition.getMatrix()( rowI, colI ) != 0 && colI != condition.getMatrix().cols() && varNameMap.size() > static_cast<std::size_t>( colI ) ) {
					res << varNameMap.at( colI );
				}
			}
			// if first is still true, this was a zero-row, which should be skipped
			if ( !first ) {
				res << " <= " << condition.getVector()( rowI );
			}
			bool lastRow = ( rowI == condition.getMatrix().rows() - 1 );
			if ( !lastRow ) {
				res << " &";
			}
		}
		res << std::scientific;
	}
	return res.str();
}

template <typename Number>
std::string toSpaceExFormat( const ConstraintSetT<Number>& constraints,
							 const std::map<Eigen::Index, std::string>& varNameMap ) {
	return toSpaceExFormat( Condition<Number>( constraints.matrix(), constraints.vector() ), varNameMap );
}

template <typename Number>
std::string toSpaceExFormat( const flowVariant<Number>& flowVariant,
							 const std::map<Eigen::Index, std::string>& varNameMap ) {
	std::stringstream out;
	switch ( getFlowType( flowVariant ) ) {
		case DynamicType::timed:
		case DynamicType::discrete:
		case DynamicType::linear: {
			matrix_t<Number> flow = std::get<linearFlow<Number>>( flowVariant ).getFlowMatrix();
			for ( Eigen::Index rowI = 0; rowI < flow.rows() - 1; ++rowI ) {
				std::stringstream tmp;
				tmp << varNameMap.at( rowI ) << "' == ";
				out << toSpaceExFormat( matrix_t<Number>( flow.row( rowI ) ), varNameMap, tmp.str() );
				bool lastRow = ( rowI == flow.rows() - 2 );
				if ( !lastRow ) {
					out << " &\n";
				}
			}
			break;
		}
		case DynamicType::affine: {
			matrix_t<Number> flow = std::get<affineFlow<Number>>( flowVariant ).getFlowMatrix();
			vector_t<Number> constPart = std::get<affineFlow<Number>>( flowVariant ).getTranslation();
			for ( Eigen::Index rowI = 0; rowI < flow.rows(); ++rowI ) {
				std::stringstream tmp;
				tmp << varNameMap.at( rowI ) << "' == ";
				matrix_t<Number> tmpMatrix = matrix_t<Number>( 1, flow.cols() + 1 );
				tmpMatrix << flow.row( rowI ), constPart( rowI );
				out << toSpaceExFormat( tmpMatrix, varNameMap, tmp.str() );
				bool lastRow = ( rowI == flow.rows() - 1 );
				if ( !lastRow ) {
					out << " &\n";
				}
			}
			break;
		}
		case DynamicType::rectangular: {
			throw NotImplemented();
			break;
		}
		default:
			throw std::logic_error( "Dynamic type not recognized" );
			break;
	}
	return out.str();
}

template <typename Number>
void toSpaceExFormat( const Location<Number>* loc,
					  const std::map<Eigen::Index, std::string>& varNameMap,
					  std::size_t identifier,
					  tinyxml2::XMLElement* const parent ) {
	using tinyxml2::XMLElement;
	XMLElement* location = parent->InsertNewChildElement( "location" );
	location->SetAttribute( "id", identifier );
	location->SetAttribute( "name", loc->getName().c_str() );

	if ( !varNameMap.empty() ) {
		assert( varNameMap.size() == std::size_t( loc->dimension() ) );
		// invariant
		XMLElement* invariant = location->InsertNewChildElement( "invariant" );
		invariant->SetText( toSpaceExFormat( loc->getInvariant(), varNameMap ).c_str() );
		// flow
		XMLElement* flow = location->InsertNewChildElement( "flow" );
		flow->SetText( toSpaceExFormat( *( loc->getFlows().begin() ), varNameMap ).c_str() );
	}
}

std::string toSpaceExFormat( const ReachabilitySettings& settings,
							 const std::map<Eigen::Index, std::string>& varNameMap,
							 const std::string& prefix );

template <typename Number>
std::pair<std::string, std::string> toSpaceExFormat( const HybridAutomaton<Number>& automaton, const ReachabilitySettings& settings = ReachabilitySettings() ) {
	using tinyxml2::XMLDocument;
	using tinyxml2::XMLElement;
	using tinyxml2::XMLPrinter;

	XMLDocument doc;
	XMLElement* spaceex = doc.NewElement( "sspaceex" );
	spaceex->SetAttribute( "math", "SpaceEx" );
	doc.InsertFirstChild( spaceex );

	std::map<Eigen::Index, std::string> vars;
	for ( std::size_t i = 0; i < automaton.getVariables().size(); ++i ) {
		vars.emplace( i, automaton.getVariables()[i] );
	}

	// plant component
	XMLElement* plantElement = spaceex->InsertNewChildElement( "component" );
	plantElement->SetAttribute( "id", "plant_component_template" );
	for ( const auto& [_, name] : vars ) {
		XMLElement* param = plantElement->InsertNewChildElement( "param" );
		param->SetAttribute( "d1", 1 );
		param->SetAttribute( "d2", 1 );
		param->SetAttribute( "dynamics", "any" );
		param->SetAttribute( "local", "false" );
		param->SetAttribute( "name", name.c_str() );
		param->SetAttribute( "type", "real" );
	}
	// locations
	std::size_t locationIdentifier{ 0 };
	std::map<std::string, std::size_t> locationIdNameMap;
	for ( auto locPtr : automaton.getLocations() ) {
		locationIdNameMap.emplace( locPtr->getName(), locationIdentifier );
		toSpaceExFormat( locPtr, vars, locationIdentifier++, plantElement );
	}
	// transitions
	for ( auto locPtr : automaton.getLocations() ) {
		std::size_t sourceId = locationIdNameMap[locPtr->getName()];
		for ( const auto& transitionPtr : locPtr->getTransitions() ) {
			XMLElement* transition = plantElement->InsertNewChildElement( "transition" );
			transition->SetAttribute( "source", sourceId );
			transition->SetAttribute( "target", locationIdNameMap[transitionPtr->getTarget()->getName()] );
			if ( !transitionPtr->getGuard().isTrue() ) {
				XMLElement* guard = transition->InsertNewChildElement( "guard" );
				guard->SetText( toSpaceExFormat( transitionPtr->getGuard(), vars ).c_str() );
			}
			if ( !transitionPtr->getReset().isIdentity() ) {
				XMLElement* reset = transition->InsertNewChildElement( "assignment" );
				std::stringstream tmp;
				matrix_t<Number> constraintMatrix = transitionPtr->getReset().getMatrix();
				vector_t<Number> constraintVector = transitionPtr->getReset().getVector();
				for ( Eigen::Index rowI = 0; rowI < constraintMatrix.rows(); ++rowI ) {
					tmp << vars.at( rowI ) << "' == ";
					matrix_t<Number> tmpMatrix = matrix_t<Number>( 1, constraintMatrix.cols() + 1 );
					tmpMatrix << constraintMatrix.row( rowI ), constraintVector( rowI );
					tmp << toSpaceExFormat( tmpMatrix, vars, "" );
					bool lastRow = ( rowI == constraintMatrix.rows() - 1 );
					if ( !lastRow ) {
						tmp << " &\n";
					}
				}
				reset->SetText( tmp.str().c_str() );
			}
		}
	}

	// system component
	XMLElement* systemElement = spaceex->InsertNewChildElement( "component" );
	systemElement->SetAttribute( "id", "system" );
	for ( const auto& [_, name] : vars ) {
		XMLElement* param = systemElement->InsertNewChildElement( "param" );
		param->SetAttribute( "controlled", true );
		param->SetAttribute( "d1", 1 );
		param->SetAttribute( "d2", 1 );
		param->SetAttribute( "dynamics", "any" );
		param->SetAttribute( "local", "false" );
		param->SetAttribute( "name", name.c_str() );
		param->SetAttribute( "type", "real" );
	}
	XMLElement* binding = systemElement->InsertNewChildElement( "bind" );
	binding->SetAttribute( "as", "plant" );
	binding->SetAttribute( "component", "plant_component_template" );
	for ( const auto& [_, name] : vars ) {
		XMLElement* map = binding->InsertNewChildElement( "map" );
		map->SetAttribute( "key", name.c_str() );
		map->InsertNewText( name.c_str() );
	}

	// TODO print to string

	XMLPrinter printer;
	doc.Print( &printer );
	const std::string automatonXml = printer.CStr();

	std::string settingsString;
	std::string initialSetString;
	std::string badStateString;

	for ( const auto& [location, initialCondition] : automaton.getInitialStates() ) {
		initialSetString += "loc(plant_component_template) == " + location->getName();
		initialSetString += toSpaceExFormat( initialCondition, vars );
	}
	for ( const auto& [location, unsafeCondition] : automaton.getLocalBadStates() ) {
		badStateString += "loc(plant_component_template) == " + location->getName();
		badStateString += toSpaceExFormat( unsafeCondition, vars );
	}

	settingsString += "system = system\n";
	settingsString += "initially = \"" + initialSetString + "\"\n";
	settingsString += "forbidden = \"" + badStateString + "\"\n";
	settingsString +=
		  "\
scenario = stc\n\
directions = oct\n\
set-aggregation = \"none\"\n\
sampling-time = " +
		  std::to_string( carl::convert<tNumber, double>( settings.timeStep ) ) +
		  "\n\
flowpipe-tolerance = 0.01\n\
flowpipe-tolerance-rel = 0\n\
simu-init-sampling-points = 0\n\
time-horizon = " +
		  std::to_string( carl::convert<tNumber, double>( settings.timeBound ) ) +
		  "\n\
iter-max = -1\n\
output-variables = \"x0,x1\"\n\
output-format = GEN\n\
verbosity = m\n\
output-error = 0\n\
rel-err = 1.0E-12\n\
abs-err = 1.0E-15\n";
	return std::make_pair( automatonXml, settingsString );
}

}  // namespace hypro

#endif

#endif	// HYPRO_SPACEEX_H
