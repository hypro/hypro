#pragma once
#include "../../representations/GeometricObject.h"
#include "../../representations/types.h"

namespace hypro {

template<typename T>
class genericUniteVisitor
    : public boost::static_visitor<T>
{
public:

	template<typename A, typename B>
	T operator()(const A& lhs, const B&) const {
		assert(false && "UNION OF DIFFERENT TYPES.");
		return lhs;
	}

	template<typename A>
    T operator()(const A& lhs, const A& rhs) const {
    	//auto tmpHPoly = Converter<Number>::toHPolytope(lhs);
		//TRACE("hydra.datastructures","Union visitor lhs " << tmpHPoly);
		//tmpHPoly = Converter<Number>::toHPolytope(rhs);
		//TRACE("hydra.datastructures","Union visitor rhs " << tmpHPoly);
 		return lhs.unite(rhs);
    }
};

template<typename T>
class genericIntersectVisitor
    : public boost::static_visitor<T>
{
public:
	template<typename A, typename B>
	T operator()(const A& lhs, const B&) const {
		assert(false && "INTERSECTION OF DIFFERENT TYPES.");
		return lhs;
	}

    T operator()(const T& lhs, const T& rhs) const {
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
    T operator()(const B& lhs) const {
 		return lhs.affineTransformation(mat, vec);
    }
};

template<typename T>
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

	template<typename B, typename Number>
    T operator()(const B& lhs) const {
 		switch(toType){
 			case representation_name::box: {
 				return Converter<Number>::toBox(lhs);
 				break;
 			}
 			case representation_name::polytope_h: {
 				return Converter<Number>::toHPolytope(lhs);
 				break;
 			}
 			case representation_name::polytope_v: {
 				return Converter<Number>::toVPolytope(lhs);
 				break;
 			}
 			case representation_name::zonotope: {
 				return Converter<Number>::toZonotope(lhs);
 				break;
 			}
 			case representation_name::support_function: {
 				return Converter<Number>::toSupportFunction(lhs);
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

    T operator()(const T& lhs) const {
    	// Do nothing if not support function.
    	return lhs;
    }

    T operator()(const SupportFunction<Number>& lhs) const {
    	/*
    	Number temp = timeBound/timeStep;
		unsigned long multPerEval = lhs.multiplicationsPerEvaluation();
		unsigned long estimatedNumberOfEvaluations =  (transition->guard().mat.rows() + transition->target()->invariant().mat.rows()) * carl::toInt<carl::uint>(carl::ceil(temp));
		unsigned long estimatedCostWithoutReduction = estimatedNumberOfEvaluations * multPerEval;
		unsigned long hyperplanesForReduction = 2* lhs.dimension() * (lhs.dimension()-1)+ 2* lhs.dimension();
		unsigned long estimatedCostWithReduction = hyperplanesForReduction* multPerEval+ estimatedNumberOfEvaluations * carl::pow(hyperplanesForReduction, 2);
		if (estimatedCostWithReduction < estimatedCostWithoutReduction) {
			*/
    	TRACE("hydra.datastructures", "GenericReduction for SF.");
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
    : public boost::static_visitor<std::pair<bool,T>>
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
    std::pair<bool,T> operator()(const B& lhs) const {
 		return lhs.satisfiesHalfspaces(constraints, constants);
    }
};


class genericCompareVisitor
    : public boost::static_visitor<bool>
{
public:
	template<typename A, typename B>
	bool operator()(const A& lhs, const B&) const {
		return false;
	}

	template<typename T>
    bool operator()(const T& lhs, const T& rhs) const {
 		return (lhs == rhs);
    }
};

} // namespace
