/**
 * The class which represents a box.
 *
 * @file Box.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since   2014-01-16
 * @version 2015-02-27
 */

#pragma once

#include <map>
#include <cassert>
#include <carl/interval/Interval.h>

namespace hypro {

template<typename Number>
class Vertex;

template<typename Number>
class VPolytope;

template<typename Number>
class Box {
private:
	
public:
	typedef std::map<const carl::Variable, carl::Interval<Number> > intervalMap;
	/***************************************************************************
	 * Members
	 **************************************************************************/
protected:
	std::vector<carl::Interval<Number>> mBoundaries;
	
public:
	/***************************************************************************
	 * Constructors
	 **************************************************************************/
	
	/*
	 * Creates a box without any specifications
	 */
	Box() : mBoundaries()
	{}
	
	/*
	 * Creates a copy of a box?
	 * @param orig The box that's gonna be copied
	 */
	Box(const Box& orig) : mBoundaries(orig.boundaries())
	{}
	
	/*
	 * Creates a box by
	 * @param var
	 * @param val
	 */
	Box(const carl::Variable& var, const carl::Interval<Number>& val)
	{
		unsigned pos = hypro::VariablePool::getInstance().dimension(var);
		while(mBoundaries.size() <= pos) {
			mBoundaries.push_back(carl::Interval<Number>::emptyInterval());
		}
		mBoundaries[pos] = val;
	}
	
	/*
	 * Creates a box by
	 * @param intervals
	 */
	Box(const intervalMap& intervals)
	{
		for(auto& pair : intervals) {
			unsigned pos = hypro::VariablePool::getInstance().dimension(pair.first);
			while(mBoundaries.size() <= pos) {
				mBoundaries.push_back(carl::Interval<Number>::emptyInterval());
			}
			mBoundaries[pos] = pair.second;
		}
	}
	
	Box(const std::vector<carl::Interval<Number>>& _intervals) {
		mBoundaries = _intervals;
	}

	Box(const matrix_t<Number>& _matrix, const vector_t<Number>& _constants) : Box(VPolytope<Number>(_matrix,_constants).vertices()) {}
	Box(const std::set<Point<Number>>& _points);
	Box(const std::vector<Point<Number>>& _points);
	Box(const std::set<Vertex<Number>>& _points);
	Box(const std::vector<Vertex<Number>>& _points);


	~Box()
	{
		mBoundaries.clear();
	}
	
	/***************************************************************************
	 * Getters & setters
	 **************************************************************************/
	
	/*
	 * @return
	 */
	std::vector<carl::Interval<Number>>& rBoundaries()
	{
		return mBoundaries;
	}
	
	/*
	 * @return
	 */
	const std::vector<carl::Interval<Number>>& boundaries() const
	{
		return mBoundaries;
	}
	
	/**
	 * Inserts a new boundary for a variable.
	 * @param val Pair of Variable and Interval.
	 * @return True, if a new insertion has happened, else only update of an existing interval.
	 */
	bool insert(const std::pair<const carl::Variable, carl::Interval<Number> >& val)
	{
		unsigned pos = hypro::VariablePool::getInstance().dimension(val.first);
		bool newElement = (mBoundaries.size() <= pos);
		while(mBoundaries.size() <= pos) {
			mBoundaries.push_back(carl::Interval<Number>::emptyInterval());
		}
		mBoundaries[pos] = val.second;
		return newElement;
	}
	
	
	/*
	 *@param var
	 *@param val
	 *@return
	 */
	bool insert(const carl::Variable& var, const carl::Interval<Number>& val)
	{
		unsigned pos = hypro::VariablePool::getInstance().dimension(var);
		bool newElement = (mBoundaries.size() <= pos);
		while(mBoundaries.size() <= pos) {
			mBoundaries.push_back(carl::Interval<Number>::emptyInterval());
		}
		mBoundaries[pos] = val;
		return newElement;
	}
	
	bool insert(unsigned pos, const carl::Interval<Number>& val)
	{
		bool newElement = (mBoundaries.size() <= pos);
		while(mBoundaries.size() <= pos) {
			mBoundaries.push_back(carl::Interval<Number>::emptyInterval());
		}
		mBoundaries[pos] = val;
		return newElement;
	}
		

	/*
	 * Setter method for box boundaries
	 * @param boundaries Defines the new boundaries for the box
	 */
	void insert(const std::vector<carl::Interval<Number>>& boundaries)
	{
		mBoundaries = boundaries;
	}
	
	/*
	 * Checks if the box has the same dimension as the variable.
	 * @param var
	 * @return
	 */
	bool hasDimension(const carl::Variable& var) const
	{
		return hypro::VariablePool::getInstance().hasDimension(var) && unsigned(hypro::VariablePool::getInstance().dimension(var)) < mBoundaries.size();
	}
			
	/**
	 * Checks if the box has the same dimensions as this box.
	 * The number of dimensions has to be equal as well as the actual
	 * variables used for those dimensions.
	 * 
	 * @param p
	 * @return True, if all dimension variables are equal
	 */
	bool haveSameDimensions(const Box<Number>& b) const
	{
		if (dimension() != b.dimension())
		{
			return false;
		}
		return true;
	}
	
	carl::Interval<Number> interval(const carl::Variable& var) const;
	carl::Interval<Number>& rInterval(const carl::Variable& var);
	
	carl::Interval<Number> at (unsigned _index) const {
		if(_index > mBoundaries.size())
			return carl::Interval<Number>::emptyInterval();
		
		return mBoundaries[_index];
	}
	
	/*
	 * @return
	 */
	bool isEmpty() const
	{
		if(mBoundaries.size() == 0)
			return true;
		for(auto interval : mBoundaries)
		{
			if(interval.isEmpty())
			{
				return true;
			}
		}
		return false;
	}

	/*
	 * @return
	 */
	Point<Number> max() const
	{
		vector_t<Number> coordinates = vector_t<Number>(mBoundaries.size());
		for(unsigned i = 0; i < mBoundaries.size(); ++i)
		{
			coordinates(i) = mBoundaries[i].upper();
		}
		return Point<Number>(coordinates);
	}
		
	/*
	 * @return
	 */
	Point<Number> min() const
	{
		vector_t<Number> coordinates = vector_t<Number>(mBoundaries.size());
		for(unsigned i = 0; i < mBoundaries.size(); ++i)
		{
			coordinates(i) = mBoundaries[i].lower();
		}
		return Point<Number>(coordinates);
	}
	
	Number supremum() const;

	std::vector<Point<Number>> vertices() const;

	/**
	 * Checks if two boxes are equal
	 * @param b1 Contains the first box
	 * @param b2 Contains the second box
	 * @return true, if they are equal.
	 */
	friend bool operator==(const Box<Number> & b1, const Box<Number> & b2)
	{
		if(b1.dimension() != b2.dimension()) return false;
		for (unsigned i = 0; i < b1.boundaries().size(); ++i)
		{
			if (b1.at(i) != b2.at(i)) return false;
		}
		return true;
	}

	/**
	 * @param b1
	 * @param b2
	 * @return true. if they are not equal
	 */
	friend bool operator!=(const Box<Number> & b1, const Box<Number> & b2)
	{
		return !(b1 == b2);
	}

	/*
	 *@param rhs
	 *@return
	 */
	Box<Number>& operator= (const Box<Number>& rhs) 
	{ 
		if (*this != rhs)
		{
			this->mBoundaries.clear();
			mBoundaries = rhs.boundaries();
		} 
		return *this;
	}

	/**
	 *
	 * @param ostr
	 * @param b
	 * @return
	 */
	friend std::ostream & operator<< (std::ostream& ostr, const Box<Number>& b)
	{
		ostr << "{";		
		for (unsigned i = 0; i < b.dimension(); ++i) {
			if (i != 0) {
				ostr << ";";
			}
			ostr << " " << b.at(i);
		}		
		ostr << " }";
		return ostr;
	}
	
	const carl::Interval<Number>& operator[](unsigned i) const{
		return mBoundaries[i];
	}
	
	carl::Interval<Number>& operator[](unsigned i) {
		return mBoundaries[i];
	}
		
		
	/***************************************************************************
	 * General interface
	 **************************************************************************/
	
	unsigned int dimension() const
	{
		return mBoundaries.size();
	}
	
	Box<Number> linearTransformation(const matrix_t<Number>& A, const vector_t<Number>& b = vector_t<Number>()) const;
	Box<Number> minkowskiSum(const Box<Number>& rhs) const;
	Box<Number> intersect(const Box<Number>& rhs) const;
	bool contains(const Point<Number>& point) const;
	bool contains(const Box<Number>& box) const;
	Box<Number> unite(const Box<Number>& rhs) const;
	
	void clear();
};

}
#include "Box.tpp"
