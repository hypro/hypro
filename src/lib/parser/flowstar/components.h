
#pragma once

#define BOOST_SPIRIT_USE_PHOENIX_V3

#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include "boost/variant.hpp"
#include <vector>
#include <queue>

namespace spirit = boost::spirit;
namespace qi = boost::spirit::qi;
namespace px = boost::phoenix;

namespace hypro {
namespace parser {

using namespace boost::fusion;
typedef unsigned locationId;

struct Monomial {
	std::vector<std::string> mVariables;
	//std::vector<unsigned> mExponents;
};

template <typename Number>
struct Term {
	Number mCoefficient;
	Monomial mMonomial;
};

template <typename Number>
struct Polynomial {
	std::vector<Term<Number>> mTerms;
};

template <typename Number>
struct Matrix {
	std::string mName;
	std::vector<std::vector<Number> > mMatrix;
};

template <typename Number>
struct State {
	unsigned mName;
	Matrix<Number> mFlow;
	Matrix<Number> mInvariant;
};

template <typename Number>
struct Transition {
	int mId;
	unsigned mName;
	unsigned mSource;
	unsigned mTarget;
	Matrix<Number> mGuard;
	Matrix<Number> mReset;
};

std::ostream& operator<<( std::ostream& lhs, const Monomial& rhs ) {
	//assert(rhs.mVariables.size() == rhs.mExponents.size());
	if(rhs.mVariables.size() >= 1) {
		for ( std::size_t varId = 0; varId < rhs.mVariables.size()-1; ++varId ) {
			lhs << rhs.mVariables.at(varId);
			//if(rhs.mExponents.at(varId) > 1)
			//	lhs << "^" << rhs.mExponents.at(varId);
			lhs << " * ";
		}
		lhs << rhs.mVariables.at(rhs.mVariables.size()-1);
		//if(rhs.mExponents.at(rhs.mVariables.size()-1) > 1)
	//	lhs << "^" << rhs.mExponents.at(rhs.mVariables.size()-1);
	}
	return lhs;
}

template <typename Number>
std::ostream& operator<<( std::ostream& lhs, const Term<Number>& rhs ) {
	lhs << rhs.mCoefficient << "*" << rhs.mMonomial;
	return lhs;
}

template <typename Number>
std::ostream& operator<<( std::ostream& lhs, const Polynomial<Number>& rhs ) {
	if(rhs.mTerms.size() >= 1) {
		for ( std::size_t termId = 0; termId < rhs.mTerms.size()-1; ++termId ) {
			lhs << "T" << termId << ": " << rhs.mTerms.at(termId) << " + ";
		}
		lhs << "T" << rhs.mTerms.size()-1 << ": " << rhs.mTerms.at(rhs.mTerms.size()-1);
	}
	return lhs;
}

template <typename Number>
std::ostream& operator<<( std::ostream& lhs, const Matrix<Number>& rhs ) {
	lhs << rhs.mName << " [";
	for ( auto& row : rhs.mMatrix ) {
		for ( auto& value : row ) {
			lhs << value << " ";
		}
		lhs << "; ";
	}
	lhs << "]";
	return lhs;
}

template <typename Number>
std::ostream& operator<<( std::ostream& lhs, const State<Number>& rhs ) {
	lhs << "location(" << std::endl << "\t Name = " << rhs.mName << std::endl << "\t Flow = " << rhs.mFlow << std::endl
		<< "\t Inv = " << rhs.mInvariant << std::endl << ")";
	return lhs;
}

template <typename Number>
std::ostream& operator<<( std::ostream& lhs, const Transition<Number>& rhs ) {
	lhs << "Transition( " << rhs.mId << std::endl << "\t Name = " << rhs.mName << std::endl
		<< "\t Source = " << rhs.mSource << std::endl << "\t Target = " << rhs.mTarget << std::endl
		<< "\t Guard = " << rhs.mGuard << std::endl << "\t Reset = " << rhs.mReset << std::endl << ")";
	return lhs;
}

} // namespace
} // namespace

#include "componentsAdapt.h"
