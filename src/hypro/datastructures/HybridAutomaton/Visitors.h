#pragma once
#include "../../datastructures/Point.h"
#include "../../representations/GeometricObject.h"
#include "../../representations/types.h"
#include "../../types.h"

namespace hypro {

template<typename T>
class genericUniteVisitor
    : public boost::static_visitor<T>
{
public:

	template<typename A, typename B>
	inline T operator()(const A& lhs, const B&) const {
		assert(false && "UNION OF DIFFERENT TYPES.");
		return lhs;
	}

	template<typename A>
    inline T operator()(const A& lhs, const A& rhs) const {
    	//auto tmpHPoly = Converter<Number>::toHPolytope(lhs);
		//TRACE("hydra.datastructures","Union visitor lhs " << tmpHPoly);
		//tmpHPoly = Converter<Number>::toHPolytope(rhs);
		//TRACE("hydra.datastructures","Union visitor rhs " << tmpHPoly);
 		return lhs.unite(rhs);
    }
};

template<typename T>
class genericMinkowskiSumVisitor
    : public boost::static_visitor<T>
{
public:

	template<typename A, typename B>
	inline T operator()(const A& lhs, const B&) const {
		TRACE("hypro.utility","Type lhs: " << A::type() << " and type rhs: " << B::type());
		assert(false && "MinkowskiSum OF DIFFERENT TYPES");
		return lhs;
	}

	template<template<typename,typename,typename> typename A, typename S1, typename S2, typename N, typename C>
	inline T operator()(const A<N,C,S1>& lhs, const A<N,C,S2>& rhs) const {
		A<N,C,S1> tmp{rhs};
		return lhs.minkowskiSum(tmp);
	}

};

template<typename T>
class genericIntersectVisitor
    : public boost::static_visitor<T>
{
public:
	template<typename A, typename B>
	inline T operator()(const A& lhs, const B&) const {
		assert(false && "INTERSECTION OF DIFFERENT TYPES.");
		return lhs;
	}

    inline T operator()(const T& lhs, const T& rhs) const {
 		return lhs.intersect(rhs);
    }
};

template<typename T, typename Number>
class genericAffineTransformationVisitor
    : public boost::static_visitor<T>
{
protected:
	const matrix_t<Number>& mat;
	const vector_t<Number>& vec;

public:
	genericAffineTransformationVisitor() = delete;
	genericAffineTransformationVisitor(const matrix_t<Number>& m, const vector_t<Number>& v) :
		mat(m),
		vec(v)
	{}

	template<typename B>
    inline T operator()(const B& lhs) const {
		auto tmp = lhs.affineTransformation(mat, vec);
		DEBUG("hypro.datastructures","Result of transformation: " << tmp);
 		return lhs.affineTransformation(mat, vec);
    }
};

template<typename T, typename To>
class genericConversionVisitor
    : public boost::static_visitor<T>
{

public:

	template<typename B>
    inline T operator()(const B& lhs) const {
		To tmp;
		convert<typename To::NumberType,typename To::Settings, B>(lhs, tmp);
		return tmp;
    }
};

template<typename T, typename Ext>
class genericInternalConversionVisitor
    : public boost::static_visitor<T>
{
protected:
	Ext mExt;

public:
	genericInternalConversionVisitor() = delete;
	genericInternalConversionVisitor(const Ext& in)
		: mExt(in)
	{}

	template<typename B>
    inline T operator()(const B&) const {
		B tmp;
		convert<typename B::NumberType,typename B::Settings, Ext>(mExt, tmp);
		return tmp;
    }
};

template<typename OutType>
class genericConvertAndGetVisitor
    : public boost::static_visitor<OutType>
{
protected:

public:

	template<typename B>
    inline OutType operator()(const B& in) const {
		OutType tmp;
		convert<typename OutType::NumberType,typename OutType::Settings, B>(in, tmp);
		return tmp;
    }
};

template<typename T, typename Number>
class genericRedundancyVisitor
    : public boost::static_visitor<T>
{
public:

	template<typename A>
    inline T operator()(A lhs) const {
    	lhs.removeRedundancy();
    	return lhs;
    }
};

template<typename T, typename Number>
class genericReductionVisitor
    : public boost::static_visitor<T>
{
public:

	template<typename A>
    inline T operator()(A lhs) const {
    	lhs.reduceRepresentation();
    	return lhs;
    }
};

template<typename T, typename Number>
class genericSatisfiesHalfspacesVisitor
    : public boost::static_visitor<std::pair<CONTAINMENT,T>>
{
protected:
	const matrix_t<Number>& constraints;
	const vector_t<Number>& constants;

public:
	genericSatisfiesHalfspacesVisitor() = delete;
	genericSatisfiesHalfspacesVisitor(const matrix_t<Number>& m, const vector_t<Number>& v) :
		constraints(m),
		constants(v)
	{}

	template<typename B>
    inline std::pair<CONTAINMENT,T> operator()(const B& lhs) const {
 		return lhs.satisfiesHalfspaces(constraints, constants);
    }
};

class genericCompareVisitor
    : public boost::static_visitor<bool>
{
public:
	template<typename A, typename B>
	inline bool operator()(const A&, const B&) const {
		return false;
	}

	template<typename T>
    inline bool operator()(const T& lhs, const T& rhs) const {
 		return (lhs == rhs);
    }
};


class genericOutstreamVisitor
    : public boost::static_visitor<std::ostream&>
{
protected:
	std::ostream& out;
public:
	genericOutstreamVisitor()=delete;
	genericOutstreamVisitor(std::ostream& o) :
		out(o)
	{}

	template<typename T>
    inline std::ostream& operator()(const T& shape) const {
 		return out << shape;
    }
};

class genericDimensionVisitor
	: public boost::static_visitor<std::size_t>
{
public:
	template<typename T>
	inline std::size_t operator()(const T& shape) const {
		return shape.dimension();
	}
};

template<typename T>
class genericSupremumVisitor
	: public boost::static_visitor<T>
{
public:
	template<typename A>
	inline T operator()(const A& shape) const {
		return shape.supremum();
	}
};

class genericTypeVisitor
	: public boost::static_visitor<representation_name>
{
public:
	template<typename A>
	inline representation_name operator()(const A&) const {
		return A::type();
	}
};

template<typename Number>
class genericVerticesVisitor
    : public boost::static_visitor<std::vector<Point<Number>>>
{
public:
	template<typename B>
    inline std::vector<Point<Number>> operator()(const B& lhs) const {
 		return lhs.vertices();
    }
};

template<typename T>
class genericProjectionVisitor
    : public boost::static_visitor<T>
{
protected:
	std::vector<std::size_t> mDimensions;

public:
	genericProjectionVisitor() = delete;
	genericProjectionVisitor(const std::vector<std::size_t>& dim) : mDimensions(dim) {}

	template<typename A>
    inline T operator()(const A& lhs) const {
 		return lhs.project(mDimensions);
    }
};


class genericSetContainsVisitor
    : public boost::static_visitor<bool>
{
public:
	template<typename A, typename B>
	inline bool operator()(const A&, const B&) const {
		std::cout << "Types: " << A::type() << " and " << B::type() << std::endl;
		assert(false && "CONTAINS CHECK OF DIFFERENT TYPES.");
		return false;
	}

	template<typename A>
    inline bool operator()(const A& lhs, const A& rhs) const {
 		return lhs.contains(rhs);
    }
};

template<typename T, typename Number>
class genericIntervalAssignmentVisitor
	: public boost::static_visitor<T>
{
	const std::vector<carl::Interval<Number>>& mAssignments;

	public:
	genericIntervalAssignmentVisitor() = delete;
	genericIntervalAssignmentVisitor(const std::vector<carl::Interval<Number>>& assignments) : mAssignments(assignments) {}

	// TODO: Add SFINAE mechanism to ensure N=Number
	template<typename N, typename C, typename S>
    inline T operator()(const CarlPolytopeT<N,C,S>& lhs) const {
		DEBUG("hypro.datastructures","Interval assignment.");
		assert(mAssignments.size() >= lhs.dimension());
		auto res{lhs};
		for(std::size_t i = 0; i < mAssignments.size(); ++i) {
			// the empty interval is used to encode identity resets.
			if(!mAssignments[i].isEmpty()) {
				assert(VariablePool::getInstance().hasDimension(i));
				TRACE("hypro.datastructures","Assign " << mAssignments[i] << " to variable " << VariablePool::getInstance().carlVarByIndex(i));
				res.eliminateVariable(VariablePool::getInstance().carlVarByIndex(i));
				res.addIntervalConstraints(mAssignments[i], VariablePool::getInstance().carlVarByIndex(i));
			}
		}
		DEBUG("hypro.datastructures","Result: " << res);
 		return res;
    }

	template<typename B>
    inline T operator()(const B& lhs) const {
		DEBUG("hypro.datastructures","INTERVAL ASSIGNMENT NOT IMPLEMENTED FOR THIS TYPE.");
		std::cout << "Inteval assignment not implemented for this type." << std::endl;
 		return lhs;
    }

};

} // namespace
