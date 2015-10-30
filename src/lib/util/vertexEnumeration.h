/**
 * This file holds the vertex enumeration algorithm presented by Avis and Fukuda.
 * @file vertexEnumeration.h
 *
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	2015-10-29
 * @version	2015-10-30
 */

#pragma once

#include "../config.h"
#include "../datastructures/Point.h"

namespace hypro {

template<typename Number>
struct Dictionary {
	matrix_t<Number> 	mDictionary;
	std::size_t			mF;
	std::size_t			mG;
	std::vector<std::size_t> mB;
	std::vector<std::size_t> mN;

	Dictionary (const matrix_t<Number>& A, const vector_t<Number>& b) :
		mDictionary(),
		mF(A.rows()+A.cols()),
		mG(A.rows()+A.cols()+1)
	{
		matrix_t<Number> t = matrix_t<Number>(A.rows(), A.cols() + 1);
		t << b,-A;
		// rearrange to make the last d equations linear independent.
		rearrange();

		// solve the last d equations
		std::size_t dimension = A.cols();
		// Assumption: The last d equations of A are linear independent

		auto bottom = t.bottomRows(dimension);
		auto top = t.topRows(A.rows()-dimension);

		auto varBlock = bottom.rightCols(dimension);
		auto constPart = bottom.leftCols(1);

		matrix_t<Number> tmp = matrix_t<Number>(varBlock);

		matrix_t<Number> a(tmp.rows(), 2*dimension+1);
		a << tmp, -constPart, matrix_t<Number>::Identity(dimension,dimension);

		//normalize rows for each variable and forward insertion
		for(unsigned rowIndex = 0; rowIndex < a.rows()-1; ++rowIndex)
		{
			a.row(rowIndex) = a.row(rowIndex)/a(rowIndex,rowIndex);
			a.row(rowIndex+1) = a.row(rowIndex+1) - (a.row(rowIndex)*a(rowIndex+1, rowIndex));
		}

		// backward insertion
		for(unsigned rowIndex = a.rows()-1; rowIndex > 0; --rowIndex)
		{
			if(a(rowIndex,rowIndex) != 1)
			{
				a.row(rowIndex) = a.row(rowIndex) / a(rowIndex,rowIndex);
			}
			a.row(rowIndex-1) = a.row(rowIndex-1) - (a.row(rowIndex)*a(rowIndex-1, rowIndex));
		}

		auto substitutionBlock = a.rightCols(dimension+1);

		std::cout << substitutionBlock << std::endl;

		mDictionary = matrix_t<Number>(A.rows()-dimension + 1, dimension + 1);

		for(unsigned rI = 0; rI < top.rows(); ++rI)
		{
			mDictionary(rI,0) = top(rI,0);

			for(unsigned dI = 1; dI < top.cols(); ++dI)
			{
				mDictionary.row(rI) = mDictionary.row(rI) + (top(rI,dI) * substitutionBlock.row(dI-1));
			}
		}

		// Augment dictionary by a row of -1s
		//mDictionary.conservativeResize(mDictionary.rows()+1,Eigen::NoChange_t());

		matrix_t<Number> allOnes = matrix_t<Number>::Constant(1,mDictionary.cols(), Number(-1));
		allOnes(0) = Number(0);
		mDictionary.row(mDictionary.rows()-1) = allOnes;

		//std::cout << "Optimal dictionary: " << mDictionary << std::endl;
		for(std::size_t index = 1; index < mDictionary.rows(); ++index)
			mB.push_back(index);
		mB.push_back(mF);

		mN.push_back(mG);
		for(std::size_t index = mDictionary.rows() ; index < A.rows() + dimension - 1 ; ++index)
			mN.push_back(index);

		std::cout << "B: " << mB << std::endl;
		std::cout << "N: " << mN << std::endl;
		std::cout << "F: " << mF << std::endl;
		std::cout << "G: " << mG << std::endl;
	}

	const matrix_t<Number>& content() const {
		return mDictionary;
	}

	Point<Number> vertex() const {

	}

	void search () {
		std::size_t i,j;
		i = 2;
		j = 1;
	}

	void pivotBland();
	void pivotBlandReverse();
	void pivotCrissCross();
	void pivotCrissCrossReverse();

	void pivot(std::size_t r, std::size_t s) {
		assert(r != mF && s != mG);

		unsigned rPos = 0;
		while(r != mB[rPos]) ++rPos;

		unsigned sPos = 0;
		while(s != mN[sPos]) ++sPos;

		std::cout << "sPos: " << sPos << std::endl;
		std::cout << "rPos: " << rPos << std::endl;

		// update other cells
		for(unsigned colIndex = 0; colIndex < mDictionary.cols(); ++colIndex) {
			for(unsigned rowIndex = 0; rowIndex < mDictionary.rows(); ++rowIndex) {
				if(colIndex != sPos && rowIndex != rPos)
					mDictionary(rowIndex, colIndex) = mDictionary(rowIndex, colIndex) - ( mDictionary(rowIndex, sPos)* mDictionary(rPos, colIndex) ) / mDictionary(rPos, sPos);
			}
		}

		// update row
		for(unsigned colIndex = 0; colIndex < mDictionary.cols(); ++colIndex) {
			if(colIndex != sPos)
				mDictionary(rPos, colIndex) = - mDictionary(rPos, colIndex) / mDictionary(rPos, sPos);
		}

		// update col
		for(unsigned rowIndex = 0; rowIndex < mDictionary.rows(); ++rowIndex) {
			if(rowIndex != rPos)
				mDictionary(rowIndex,sPos) = mDictionary(rowIndex, sPos) / mDictionary(rPos, sPos);
		}

		mDictionary(rPos, sPos) = Number(1) / mDictionary(rPos, sPos);
	}

private:
	void rearrange() {
	}

	void increment(std::size_t& i, std::size_t& j) {
		++j;

	}
};

template<typename Number>
std::ostream& operator<<(std::ostream& _out, const Dictionary<Number>& _dict) {
	_out << _dict.content();
	return _out;
}



} // namespace hypro