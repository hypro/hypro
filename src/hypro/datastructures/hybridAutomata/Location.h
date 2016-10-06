/*
 * Class that describes one location of a hybrid automaton.
 * File:   location.h
 * Author: stefan & ckugler
 * Created on April 30, 2014, 9:06 AM
 */

#pragma once
#include "../../types.h"
#include <carl/interval/Interval.h>
#include <iostream>

namespace hypro {

template <typename Number>
class Transition;

template <typename Number>
class LocationManager;

template <typename Number>
class Location {
	friend LocationManager<Number>;

  public:
	struct Invariant {
		vector_t<Number> vec;
		matrix_t<Number> mat;

		unsigned discreteOffset;
		std::vector<std::pair<carl::Variable, matrix_t<Number>>> discreteInvariant;
	};

	using transitionSet = std::set<Transition<Number>*>;

  protected:

	Location( unsigned _id );
	Location( unsigned _id, const Location& _loc );
	Location( unsigned _id, const matrix_t<Number>& _mat );
	Location( unsigned _id, const matrix_t<Number>& _mat,
			  const transitionSet& _trans, const Location<Number>::Invariant& _inv );
	Location( unsigned _id, const matrix_t<Number>& _mat,
			  const transitionSet& _trans, const Location<Number>::Invariant& _inv,
			  const matrix_t<Number>& _extInputMat );

  private:
	/**
	 * Member
	 */
	mutable matrix_t<Number> mFlow;
	matrix_t<Number> mExternalInput;
	transitionSet mTransitions;
	Invariant mInvariant;
	unsigned mId;

  public:
	/**
	 * Constructors & Destructor
	 */

	~Location() {}

	/**
	 * Getter & Setter
	 */
	const matrix_t<Number>& flow() const;
	const Invariant& invariant() const;
	const transitionSet& transitions() const;
	const matrix_t<Number>& externalInput() const;
	unsigned id() const { return mId; }

	void setFlow( const matrix_t<Number>& _mat );
	void setInvariant( const struct Location<Number>::Invariant& _inv );
	void setInvariant( const matrix_t<Number>& _mat, const vector_t<Number>& _vec );
	void setLocation( const struct locationContent& _loc );
	void setTransitions( const transitionSet& _trans );
	void addTransition( Transition<Number>* _trans );
	void setExtInputMat( const matrix_t<Number>& _mat );

	inline bool operator<( const Location<Number>& _rhs ) const { return ( mId < _rhs.id() ); }
	inline bool operator==( const Location<Number>& _rhs ) const { return ( mId == _rhs.id() ); }
	inline bool operator!=( const Location<Number>& _rhs ) const { return ( mId != _rhs.id() ); }

	friend std::ostream& operator<<( std::ostream& _ostr, const Location<Number>& _l ) {
		matrix_t<Number> tmp = matrix_t<Number>(_l.invariant().mat.rows(), _l.invariant().mat.cols()+1);
		tmp << _l.invariant().mat,_l.invariant().vec;
		_ostr << "location( id: " << _l.id() << std::endl << "\t Flow: " << std::endl << _l.flow() << std::endl
		<< "\t Inv: " << std::endl << tmp;
		for(const auto& invPair : _l.invariant().discreteInvariant){
			_ostr << invPair.first << " in " << invPair.second << std::endl;
		}
		_ostr << "Transitions: " << std::endl;
		for(auto transitionPtr : _l.transitions()){
			_ostr << transitionPtr->source()->id() << " -> " << transitionPtr->target()->id() << std::endl;
		}
		_ostr << std::endl << ")";
		return _ostr;
	}
};

	template<typename Number>
	struct locPtrComp{
		bool operator()(const Location<Number>* lhs, const Location<Number>* rhs) const {
			return (*lhs < *rhs);
		}
	};


} // namespace hypro

#include "Location.tpp"
