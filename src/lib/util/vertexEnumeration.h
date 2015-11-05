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
class Dictionary {
private:
	matrix_t<Number> 	mDictionary;
	std::size_t			mF;
	std::size_t			mG;
	std::map<std::size_t, std::size_t> mB;
	std::map<std::size_t, std::size_t> mN;

public:
	Dictionary() = default;
	Dictionary(const Dictionary& rhs);
	Dictionary(const matrix_t<Number>& A, const vector_t<Number>& b);

	const matrix_t<Number>& dictionary() const;
	const std::map<std::size_t, std::size_t>& basis() const;
	const std::map<std::size_t, std::size_t>& cobasis() const;
	Point<Number> vertex() const;

	void search ();

	bool isReverseCrissCrossPivot(std::size_t i, std::size_t j) const;
	bool selectCrissCrossPivot(std::size_t& i, std::size_t& j) const;
	void pivot(std::size_t& i, std::size_t& j);

	void insertRowAtPosition(const std::size_t& originalPos, const std::size_t& insertionPos);
	void insertColAtPosition(const std::size_t& originalPos, const std::size_t& insertionPos);

	inline Dictionary<Number>& operator=(const Dictionary<Number>& rhs);
	inline bool operator==(const Dictionary<Number>& rhs) const;
	inline bool operator!=(const Dictionary<Number>& rhs) const { return !(*this == rhs); };

	void print(bool pretty = false) const;
private:

	void rearrange();
	void increment(std::size_t& i, std::size_t& j) const;
};

template<typename Number>
std::ostream& operator<<(std::ostream& _out, const Dictionary<Number>& _dict) {
	_out << _dict.dictionary() << std::endl;
	_out << "Basis:   " <<_dict.basis() << std::endl;
	_out << "CoBasis: " << _dict.cobasis() << std::endl;
	return _out;
}



} // namespace hypro

#include "vertexEnumeration.tpp"