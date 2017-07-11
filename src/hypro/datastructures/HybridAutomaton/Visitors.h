#pragma once
#include "lib/datastructures/ReachTree/types.h"

namespace hydra {

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
    	//auto tmpHPoly = hypro::Converter<Number>::toHPolytope(lhs);
		//TRACE("hydra.datastructures","Union visitor lhs " << tmpHPoly);
		//tmpHPoly = hypro::Converter<Number>::toHPolytope(rhs);
		//TRACE("hydra.datastructures","Union visitor rhs " << tmpHPoly);
 		return lhs.unite(rhs);
    }

    T operator()(const cPair& lhs, const cPair&) const {
    	assert(false && "UNION OF CPAIRS.");
    	return lhs;
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

    T operator()(const cPair& lhs, const cPair&) const {
    	assert(false && "INTERSECTION OF CPAIRS.");
    	return lhs;
    }
};

template<typename T>
class genericAffineTransformationVisitor
    : public boost::static_visitor<T>
{
protected:
	const hypro::matrix_t<Number>& mat;
	const hypro::vector_t<Number>& vec;

public:
	genericAffineTransformationVisitor() = delete;
	genericAffineTransformationVisitor(const hypro::matrix_t<Number>& m, const hypro::vector_t<Number>& v) :
		mat(m),
		vec(v)
	{}

	template<typename B>
    T operator()(const B& lhs) const {
 		return lhs.affineTransformation(mat, vec);
    }

    T operator()(const cPair& lhs) const {
    	assert(false && "AFFINE TRANSFORMATION OF CPAIRS.");
    	return lhs;
    }
};

template<typename T>
class genericConversionVisitor
    : public boost::static_visitor<T>
{
protected:
	hypro::representation_name toType;

public:
	genericConversionVisitor() = delete;
	genericConversionVisitor(hypro::representation_name to) :
		toType(to)
	{}

	template<typename B>
    T operator()(const B& lhs) const {
 		switch(toType){
 			case hypro::representation_name::box: {
 				return hypro::Converter<Number>::toBox(lhs);
 				break;
 			}
 			case hypro::representation_name::polytope_h: {
 				return hypro::Converter<Number>::toHPolytope(lhs);
 				break;
 			}
 			case hypro::representation_name::polytope_v: {
 				return hypro::Converter<Number>::toVPolytope(lhs);
 				break;
 			}
 			case hypro::representation_name::zonotope: {
 				return hypro::Converter<Number>::toZonotope(lhs);
 				break;
 			}
 			case hypro::representation_name::support_function: {
 				return hypro::Converter<Number>::toSupportFunction(lhs);
 				break;
 			}
 			case hypro::representation_name::ppl_polytope: {
 				assert(false && "CONVERSION TO PPL POLYTOPE NOT YET IMPLEMENTED.");
 				break;
 			}
 			case hypro::representation_name::cpair:
 				assert(false && "CANNOT CONVERT TO TYPE CPAIR.");
 			case hypro::representation_name::taylor_model:
 				assert(false && "CANNOT CONVERT TO TYPE TAYLOR MODEL.");
 		}
 		assert(false && "SHOULD NEVER REACH THIS");
 		return T();
    }

    T operator()(const cPair& lhs) const {
    	assert(false && "CONVERSION OF CPAIRS.");
    	return lhs;
    }
};

template<typename T>
class genericReductionVisitor
    : public boost::static_visitor<T>
{
public:

    T operator()(const T& lhs) const {
    	// Do nothing if not support function.
    	return lhs;
    }

    T operator()(const hypro::SupportFunction<Number>& lhs) const {
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
		auto tmpHPoly = hypro::Converter<Number>::toHPolytope(lhs);
		//std::vector<unsigned> projDims;
		//projDims.push_back(0);
		//projDims.push_back(3);
		//TRACE("hydra.datastructures","Reduction visitor created set " << tmpHPoly.project(projDims));
		hypro::SupportFunction<Number> newSet(tmpHPoly.matrix(), tmpHPoly.vector());
		return newSet;
		//}
    }
};

template<typename T>
class genericSatisfiesHalfspacesVisitor
    : public boost::static_visitor<std::pair<bool,T>>
{
protected:
	const hypro::matrix_t<Number>& constraints;
	const hypro::vector_t<Number>& constants;

public:
	genericSatisfiesHalfspacesVisitor() = delete;
	genericSatisfiesHalfspacesVisitor(const hypro::matrix_t<Number>& m, const hypro::vector_t<Number>& v) :
		constraints(m),
		constants(v)
	{}

	template<typename B>
    std::pair<bool,T> operator()(const B& lhs) const {
 		return lhs.satisfiesHalfspaces(constraints, constants);
    }

    std::pair<bool,T> operator()(const cPair& lhs) const {
    	assert(false && "Satisfies halfspaces for CPAIRS.");
    	return std::make_pair(false,lhs);
    }
};

} // namespace
