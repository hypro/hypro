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

#ifdef HYPRO_USE_TINYXML

#include "../../../util/exceptions.h"
#include "../../reachability/Settings.h"
#include "../Condition.h"
#include "../HybridAutomaton.h"

#include <iosfwd>
#include <tinyxml2.h>

namespace hypro {

template <typename Number>
std::string toSpaceExFormat( const matrix_t<Number>& in,
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
std::string toSpaceExFormat( const Condition<Number>& in,
							 const std::map<Eigen::Index, std::string>& varNameMap ) {
	std::stringstream res;
	if ( in.size() > 0 ) {
		res << std::fixed;
		for ( Eigen::Index rowI = 0; rowI < in.getMatrix().rows(); ++rowI ) {
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
			bool lastRow = ( rowI == in.getMatrix().rows() - 1 );
			if ( !lastRow ) {
				res << " &";
			}
		}
		res << std::scientific;
	}
	return res.str();
}

template <typename Number>
std::string toSpaceExFormat( const ConstraintSetT<Number>& in,
							 const std::map<Eigen::Index, std::string>& varNameMap ) {
	return toSpaceExFormat( Condition<Number>( in.matrix(), in.vector() ), varNameMap );
}

template <typename Number>
std::string toSpaceExFormat( const flowVariant<Number>& f,
							 const std::map<Eigen::Index, std::string>& varNameMap,
							 tinyxml2::XMLElement* const parent ) {
	std::stringstream out;
	switch ( getFlowType( f ) ) {
		case DynamicType::timed:
		case DynamicType::discrete:
		case DynamicType::linear: {
			matrix_t<Number> flow = std::get<linearFlow<Number>>( f ).getFlowMatrix();
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
			matrix_t<Number> flow = std::get<affineFlow<Number>>( f ).getFlowMatrix();
			vector_t<Number> constPart = std::get<affineFlow<Number>>( f ).getTranslation();
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
		}
	}
	return out.str();
}

template <typename Number>
void toSpaceExFormat( const Location<Number>* loc,
					  const std::map<Eigen::Index, std::string>& varNameMap,
					  std::size_t id,
					  tinyxml2::XMLElement* const parent ) {
	using namespace tinyxml2;
	XMLElement* location = parent->InsertNewChildElement( "location" );
	location->SetAttribute( "id", id );
	location->SetAttribute( "name", loc->getName().c_str() );

	if ( varNameMap.size() > 0 ) {
		assert( varNameMap.size() == std::size_t( loc->dimension() ) );
		// invariant
		XMLElement* invariant = location->InsertNewChildElement( "invariant" );
		invariant->SetText( toSpaceExFormat( loc->getInvariant(), varNameMap ).c_str() );
		// flow
		XMLElement* flow = location->InsertNewChildElement( "flow" );
		flow->SetText( toSpaceExFormat( *( loc->getFlows().begin() ), varNameMap, flow ).c_str() );
	}
}

std::string toSpaceExFormat( const ReachabilitySettings& settings,
							 const std::map<Eigen::Index, std::string>& varNameMap,
							 const std::string& prefix );

template <typename Number>
std::string toSpaceExFormat( const HybridAutomaton<Number>& in, const ReachabilitySettings& settings = ReachabilitySettings() ) {
	using namespace tinyxml2;
	XMLDocument doc;
	XMLElement* spaceex = doc.NewElement( "sspaceex" );
	spaceex->SetAttribute( "math", "SpaceEx" );
	doc.InsertFirstChild( spaceex );

	std::map<Eigen::Index, std::string> vars;
	for ( std::size_t i = 0; i < in.getVariables().size(); ++i ) {
		vars[i] = in.getVariables()[i];
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
	std::size_t id{ 0 };
	std::map<std::string, std::size_t> locationIdNameMap;
	for ( auto locPtr : in.getLocations() ) {
		locationIdNameMap[locPtr->getName()] = id;
		toSpaceExFormat( locPtr, vars, id++, plantElement );
	}
	// transitions
	for ( auto locPtr : in.getLocations() ) {
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
				matrix_t<Number> A = transitionPtr->getReset().getMatrix();
				vector_t<Number> b = transitionPtr->getReset().getVector();
				for ( Eigen::Index rowI = 0; rowI < A.rows(); ++rowI ) {
					tmp << vars.at( rowI ) << "' == ";
					matrix_t<Number> tmpMatrix = matrix_t<Number>( 1, A.cols() + 1 );
					tmpMatrix << A.row( rowI ), b( rowI );
					tmp << toSpaceExFormat( tmpMatrix, vars, "" );
					bool lastRow = ( rowI == A.rows() - 1 );
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
	std::string res = printer.CStr();
	std::cout << "Printed document: " << res << std::endl;
	return res;
}

}  // namespace hypro

#endif

#endif	// HYPRO_SPACEEX_H
