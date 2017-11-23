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
		assert(false && "MinkowskiSum OF DIFFERENT TYPES.");
		return lhs;
	}

	template<typename A>
    inline T operator()(const A& lhs, const A& rhs) const {
    	//auto tmpHPoly = Converter<Number>::toHPolytope(lhs);
		//TRACE("hydra.datastructures","Union visitor lhs " << tmpHPoly);
		//tmpHPoly = Converter<Number>::toHPolytope(rhs);
		//TRACE("hydra.datastructures","Union visitor rhs " << tmpHPoly);
 		return lhs.minkowskiSum(rhs);
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
 		return lhs.affineTransformation(mat, vec);
    }
};

template<typename T, typename Number>
class genericConversionVisitor
    : public boost::static_visitor<T>
{
protected:
	representation_name toType;

public:
	genericConversionVisitor() = delete;
	genericConversionVisitor(representation_name to) :
		toType(to)
	{}

	template<typename B>
    inline T operator()(const B& lhs) const {
 		switch(toType){
 			case representation_name::box: {
 				Box<Number> tmp = Converter<Number>::toBox(lhs);
 				return tmp;
 				break;
 			}
 			case representation_name::polytope_h: {
 				HPolytope<Number> tmp = Converter<Number>::toHPolytope(lhs);
 				return tmp;
 				break;
 			}
 			case representation_name::polytope_v: {
 				VPolytope<Number> tmp = Converter<Number>::toVPolytope(lhs);
 				return tmp;
 				break;
 			}
 			case representation_name::zonotope: {
 				Zonotope<Number> tmp = Converter<Number>::toZonotope(lhs);
 				return tmp;
 				break;
 			}
 			case representation_name::support_function: {
 				SupportFunction<Number> tmp = Converter<Number>::toSupportFunction(lhs);
 				return tmp;
 				break;
 			}
 			case representation_name::ppl_polytope: {
 				assert(false && "CONVERSION TO PPL POLYTOPE NOT YET IMPLEMENTED.");
 				break;
 			}
 			case representation_name::constraint_set:
 				assert(false && "CANNOT CONVERT TO TYPE ConstraintSet<Number>.");
 			case representation_name::taylor_model:
 				assert(false && "CANNOT CONVERT TO TYPE TAYLOR MODEL.");
 		}
 		assert(false && "SHOULD NEVER REACH THIS");
 		return T();
    }
};

template<typename T, typename Number>
class genericReductionVisitor
    : public boost::static_visitor<T>
{
public:

	template<typename A>
    inline T operator()(A lhs) const {
    	//Use removeRedundancy if not supportfunction
    	lhs.removeRedundancy();
    	return lhs;
    }

    inline T operator()(const SupportFunction<Number>& lhs) const {
    	/*
    	Number temp = timeBound/timeStep;
		unsigned long multPerEval = lhs.multiplicationsPerEvaluation();
		unsigned long estimatedNumberOfEvaluations =  (transition->guard().mat.rows() + transition->target()->invariant().mat.rows()) * carl::toInt<carl::uint>(carl::ceil(temp));
		unsigned long estimatedCostWithoutReduction = estimatedNumberOfEvaluations * multPerEval;
		unsigned long hyperplanesForReduction = 2* lhs.dimension() * (lhs.dimension()-1)+ 2* lhs.dimension();
		unsigned long estimatedCostWithReduction = hyperplanesForReduction* multPerEval+ estimatedNumberOfEvaluations * carl::pow(hyperplanesForReduction, 2);
		if (estimatedCostWithReduction < estimatedCostWithoutReduction) {
			*/
    	TRACE("hypro.datastructures", "GenericReduction for SF.");
		auto tmpHPoly = Converter<Number>::toHPolytope(lhs);
		//std::vector<unsigned> projDims;
		//projDims.push_back(0);
		//projDims.push_back(3);
		//TRACE("hydra.datastructures","Reduction visitor created set " << tmpHPoly.project(projDims));
		SupportFunction<Number> newSet(tmpHPoly.matrix(), tmpHPoly.vector());
		return newSet;
		//}
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

} // namespace
