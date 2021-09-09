/*
 * RootGrowNode.h
 *
 * An abstract class representing a node in a tree where a new node is set above the root,
 * thus making the tree grow at its root.
 * Each node knows and owns its children and has a weak_ptr to itself.
 * Every type of operation and leaf must inherit from this base class, since only then
 * this unifying base class can be used for calculations.
 *
 * @author Stefan Schupp
 * @author Phillip Tse
 */

#pragma once

#include "../../types.h"
#include "../../util/linearOptimization/EvaluationResult.h"
#include "../types.h"
#include "LinTrafoParameters.h"

#include <cassert>
#include <functional>
#include <ios>
#include <iosfwd>
#include <memory>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>

namespace hypro {

// Type of nodes. Needed to fast determine which node subclass is actually calling a function.
enum SFNEW_TYPE { NODE = 0,
				  LEAF,
				  TRAFO,
				  SCALEOP,
				  PROJECTOP,
				  SUMOP,
				  INTERSECTOP,
				  UNIONOP,
				  INTERSECTHSPACEOP };

// Abstract class encapsulating all needed data to build a RootGrowNode. Only needed for Settings conversion
struct RGNData {
	RGNData() {}
	virtual ~RGNData() {}
};

}  // namespace hypro

#include "IntersectHalfspaceOp.h"
#include "IntersectOp.h"
#include "Leaf.h"
#include "ProjectOp.h"
#include "ScaleOp.h"
#include "SumOp.h"
#include "TrafoOp.h"
#include "UnionOp.h"
namespace hypro {

////// RootGrowNode

template <typename Number, typename Converter, typename Setting>
class RootGrowNode {
  public:
	using PointerVec = std::vector<std::shared_ptr<RootGrowNode<Number, Converter, Setting>>>;

  protected:
	////// Members

	SFNEW_TYPE mType = NODE;			  // NONE since RootGrowNode should later be an abstract class
	unsigned originCount = 0;			  // Least amount of children needed to function properly
	PointerVec mChildren = PointerVec();  // vector of all current children
	std::size_t mDimension = 0;			  // The dimension of the operations and representations
	mutable SETSTATE mEmptyState = SETSTATE::UNKNOWN;

  public:
	////// Constructors

	RootGrowNode() {}
	virtual ~RootGrowNode() {}

	////// Getters and Setters

	virtual SFNEW_TYPE getType() const { return mType; }
	virtual unsigned getOriginCount() const { return originCount; }
	virtual PointerVec getChildren() const { return mChildren; }
	virtual PointerVec& rGetChildren() { return mChildren; }
	virtual std::size_t getDimension() const { return mDimension; }
	virtual SETSTATE isEmpty() const { return mEmptyState; }

	// Gets the data from a node subclass that has no extra templates (and is therefore not the Leaf class)
	virtual RGNData* getData() const = 0;

	// Gets the construction data from the Leaf class only.
	// Needed in Settings conversion to avoid casting RGNData to LeafData.
	// Doing this would undermine the guarantee of a reinterpret_cast to be able to cast back to the
	// original type as long as its underlying bit pattern is not changed.
	virtual LeafData getLeafData() const { return LeafData(); }

	virtual void setDimension( const std::size_t d ) { mDimension = d; }

	////// Modifiers

	void addToChildren( const std::shared_ptr<RootGrowNode>& rhs ) { mChildren.push_back( rhs ); }
	void clearChildren() { mChildren.clear(); }

	////// Displaying

	virtual void print( std::ostream& ostr ) const {
		ostr << "RootGrowNode address: " << this << " own type: " << this->getType() << " children types(address): [";
		for ( const auto& c : this->getChildren() ) {
			ostr << c->getType() << "(" << &( *c ) << ")"
				 << ",";
		}
		ostr << "]" << std::endl;
		for ( const auto& c : this->getChildren() ) {
			ostr << *c;
		}
	}

	friend std::ostream& operator<<( std::ostream& ostr, const RootGrowNode& r ) {
		r.print( ostr );
		return ostr;
	}

	////// Traversal

	// The needed functions for evaluate. Virtual s.t. they can be implemented in the Operation/Leaf classes
	// Three functions are needed: transform, compute and aggregate.
	// - transform will be called by every node: Needed parameters are modified via transform
	// - compute will be called once by every leaf node: Compute computes the result in the leaf noeds from the given parameters and returns it
	// - aggregate will be called once by every non leaf node: Given the results of its child nodes, a non leaf node A processes these to results to one from A
	//
	// Order of calling:
	// 1) From top to bottom, all nodes call transform
	// 2) When arriving at the lowest level, leaf nodes first call transform, then call compute
	// 3) From bottom to top, all non leaf nodes call aggregate
	//
	// NOTE: 	All functions used as the transform must have the signature A name(A param)
	//			All functions used as the compute must have the signature B name(A param)
	//			All functions used as the aggregate must have the signature B name(std::vector<B> param)

	// For everyone - transform
	virtual matrix_t<Number> transform( const matrix_t<Number>& param ) const = 0;

	// For leaves - compute
	virtual std::vector<EvaluationResult<Number>> compute( const matrix_t<Number>& param, bool useExact ) const = 0;

	// For operations - aggregate
	// NOTE: Double vector structure - Outer vector for every child node, inner vector for every evaluation direction
	virtual std::vector<EvaluationResult<Number>> aggregate( std::vector<std::vector<EvaluationResult<Number>>>& resultStackBack, const matrix_t<Number>& currentParam ) const = 0;

	////// Functions for SupportFunctionNew

	virtual bool empty() const {
		assert( false && "This should only be called by Leaf\n" );
		return false;
	}
	virtual bool empty( const std::vector<bool>& ) const {
		assert( false && "This should only be called by operations\n" );
		return false;
	}
	virtual Point<Number> supremumPoint() const {
		assert( false && "supremumPoint() should only be called by Leaf\n" );
		return Point<Number>();
	}
	virtual Point<Number> supremumPoint( std::vector<Point<Number>>& ) const {
		assert( false && "supremumPoint(vector) should only be called by operations\n" );
		return Point<Number>();
	}

	virtual vector_t<Number> reverseOp( const vector_t<Number>& point ) const { return point; }	 // only needed for unary operations
	virtual bool contains( const vector_t<Number>& ) const {
		assert( false && "contains(p) should only be called by Leaf\n" );
		return true;
	}
	virtual bool contains( const std::vector<bool>&, const vector_t<Number>& ) const {
		assert( "contains(v,p) should only be called by operations\n" );
		return false;
	}

	virtual std::vector<std::size_t> intersectDims( const std::vector<std::vector<std::size_t>>& dims ) const { return dims.front(); }
};
////// Settings conversion

// Converts the setting of only the given RootGrowNode to the given setting and returns a shared pointer to a newly allocated RootGrowNode of the same type.
// Does not convert its children and does not maintain its connection to its children. This is done in the SupportFunctionNew settings converter.
template <typename Number, typename Converter, typename Setting, typename SettingRhs, carl::DisableIf<std::is_same<Setting, SettingRhs>> = carl::dummy>
std::shared_ptr<RootGrowNode<Number, Converter, Setting>> convertSettings( const RootGrowNode<Number, Converter, SettingRhs>* in ) {
	assert( in != nullptr );
	std::shared_ptr<RootGrowNode<Number, Converter, Setting>> clone;
	RGNData* tmpPtr = in->getData();

	switch ( in->getType() ) {
		case SFNEW_TYPE::TRAFO: {
			TrafoData<Number, SettingRhs>* dataWithSettingRhs = dynamic_cast<TrafoData<Number, SettingRhs>*>( tmpPtr );
			assert( dataWithSettingRhs != nullptr );
			TrafoData<Number, Setting> dataTr( *dataWithSettingRhs );
			std::shared_ptr<TrafoOp<Number, Converter, Setting>> trafo = std::make_shared<TrafoOp<Number, Converter, Setting>>( dataTr );
			clone = std::static_pointer_cast<RootGrowNode<Number, Converter, Setting>>( trafo );
			delete tmpPtr;
			break;
		}
		case SFNEW_TYPE::INTERSECTOP: {
			std::shared_ptr<IntersectOp<Number, Converter, Setting>> sum = std::make_shared<IntersectOp<Number, Converter, Setting>>( *tmpPtr );
			clone = std::static_pointer_cast<RootGrowNode<Number, Converter, Setting>>( sum );
			delete tmpPtr;
			break;
		}
		case SFNEW_TYPE::PROJECTOP: {
			std::shared_ptr<ProjectOp<Number, Converter, Setting>> project = std::make_shared<ProjectOp<Number, Converter, Setting>>( *( dynamic_cast<ProjectData*>( tmpPtr ) ) );
			clone = std::static_pointer_cast<RootGrowNode<Number, Converter, Setting>>( project );
			delete tmpPtr;
			break;
		}
		case SFNEW_TYPE::SCALEOP: {
			std::shared_ptr<ScaleOp<Number, Converter, Setting>> scale = std::make_shared<ScaleOp<Number, Converter, Setting>>( *( dynamic_cast<ScaleData<Number>*>( tmpPtr ) ) );
			clone = std::static_pointer_cast<RootGrowNode<Number, Converter, Setting>>( scale );
			delete tmpPtr;
			break;
		}
		case SFNEW_TYPE::SUMOP: {
			std::shared_ptr<SumOp<Number, Converter, Setting>> sum = std::make_shared<SumOp<Number, Converter, Setting>>( *tmpPtr );
			clone = std::static_pointer_cast<RootGrowNode<Number, Converter, Setting>>( sum );
			delete tmpPtr;
			break;
		}
		case SFNEW_TYPE::UNIONOP: {
			std::shared_ptr<UnionOp<Number, Converter, Setting>> unio = std::make_shared<UnionOp<Number, Converter, Setting>>( *tmpPtr );
			clone = std::static_pointer_cast<RootGrowNode<Number, Converter, Setting>>( unio );
			delete tmpPtr;
			break;
		}
		case SFNEW_TYPE::INTERSECTHSPACEOP: {
			using IntersectHalfspaceOP = IntersectHalfspaceOp<Number, Converter, Setting>;
			std::shared_ptr<IntersectHalfspaceOP> interhspace = std::make_shared<IntersectHalfspaceOP>( *( dynamic_cast<IntersectHalfspaceData<Number>*>( tmpPtr ) ) );
			clone = std::static_pointer_cast<RootGrowNode<Number, Converter, Setting>>( interhspace );
			delete tmpPtr;
			break;
		}

		case SFNEW_TYPE::LEAF: {
			// It's going to be ugly as hell but it seems necessary
			using N = Number;
			using C = Converter;
			using S = Setting;

			delete tmpPtr;
			LeafData dataLe = in->getLeafData();

			switch ( dataLe.typeOfRep ) {
				case representation_name::box: {
					std::shared_ptr<Leaf<N, C, S, typename C::Box>> leafPtr = std::make_shared<Leaf<N, C, S, typename C::Box>>( dataLe );
					clone = std::static_pointer_cast<RootGrowNode<N, C, S>>( leafPtr );
					break;
				}
				case representation_name::carl_polytope: {
					std::shared_ptr<Leaf<N, C, S, typename C::CarlPolytope>> leafPtr = std::make_shared<Leaf<N, C, S, typename C::CarlPolytope>>( dataLe );
					clone = std::static_pointer_cast<RootGrowNode<N, C, S>>( leafPtr );
					break;
				}
				case representation_name::polytope_h: {
					using HPolyWithOptimizerCaching = HPolytopeT<N, C, HPolytopeOptimizerCaching>;
					std::shared_ptr<Leaf<N, C, S, HPolyWithOptimizerCaching>> leafPtr = std::make_shared<Leaf<N, C, S, HPolyWithOptimizerCaching>>( dataLe );
					clone = std::static_pointer_cast<RootGrowNode<N, C, S>>( leafPtr );
					break;
				}
				case representation_name::polytope_v: {
					std::shared_ptr<Leaf<N, C, S, typename C::VPolytope>> leafPtr = std::make_shared<Leaf<N, C, S, typename C::VPolytope>>( dataLe );
					clone = std::static_pointer_cast<RootGrowNode<N, C, S>>( leafPtr );
					break;
				}
#ifdef HYPRO_USE_PPL
				case representation_name::ppl_polytope: {
					std::shared_ptr<Leaf<N, C, S, typename C::Polytope>> leafPtr = std::make_shared<Leaf<N, C, S, typename C::Polytope>>( dataLe );
					clone = std::static_pointer_cast<RootGrowNode<N, C, S>>( leafPtr );
					break;
				}
#endif
				case representation_name::zonotope: {
					std::shared_ptr<Leaf<N, C, S, typename C::Zonotope>> leafPtr = std::make_shared<Leaf<N, C, S, typename C::Zonotope>>( dataLe );
					clone = std::static_pointer_cast<RootGrowNode<N, C, S>>( leafPtr );
					break;
				}
				case representation_name::difference_bounds: {
					std::shared_ptr<Leaf<N, C, S, typename C::DifferenceBounds>> leafPtr = std::make_shared<Leaf<N, C, S, typename C::DifferenceBounds>>( dataLe );
					clone = std::static_pointer_cast<RootGrowNode<N, C, S>>( leafPtr );
					break;
				}
				case representation_name::constraint_set: {
					// std::shared_ptr<Leaf<N,C,S,typename C::ConstraintSet>> leafPtr = std::make_shared<Leaf<N,C,S,typename C::ConstraintSet>>(dataLe);
					// clone = std::static_pointer_cast<RootGrowNode<N,C,S>>(leafPtr);
					break;
				}
				case representation_name::support_function: {
					// std::shared_ptr<Leaf<N,C,S,SupportFunctionT<N,C,S>>> leafPtr = std::make_shared<Leaf<N,C,S,SupportFunctionT<N,C,S>>>(dataLe);
					// clone = std::static_pointer_cast<RootGrowNode<N,C,S>>(leafPtr);
					break;
				}
				case representation_name::taylor_model: {
					// std::shared_ptr<Leaf<N,C,S,TaylorModelT<N,C,S>>> leafPtr = std::make_shared<Leaf<N,C,S,TaylorModelT<N,C,S>>>(dataLe);
					// clone = std::static_pointer_cast<RootGrowNode<N,C,S>>(leafPtr);
					break;
				}
				case representation_name::SFN: {
					// std::shared_ptr<Leaf<N,C,S,SupportFunctionNewT<N,C,S>>> leafPtr = std::make_shared<Leaf<N,C,S,SupportFunctionNewT<N,C,S>>>(dataLe);
					// clone = std::static_pointer_cast<RootGrowNode<N,C,S>>(leafPtr);
					break;
				}
				case representation_name::UNDEF:
				default:
					assert( "leaf has no defined representation" && false );
					return clone;
			}
			break;
		}
		case SFNEW_TYPE::NODE:
		default:
			assert( "Node was of no defined type" && false );
			return clone;
	}
	return clone;
}

}  // namespace hypro
