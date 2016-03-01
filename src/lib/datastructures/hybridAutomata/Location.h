/*
 * Class that describes one location of a hybrid automaton.
 * File:   location.h
 * Author: stefan & ckugler
 * Created on April 30, 2014, 9:06 AM
 */

#pragma once

namespace hypro {

enum operator_e { EQ, GEQ, LEQ, NEQ, LESS, GREATER };

template <typename Number>
class Transition;

template <typename Number>
class LocationManager;

template <typename Number>
class Location {
	friend LocationManager<Number>;

  public:
	struct Invariant {
		hypro::vector_t<Number> vec;
		hypro::matrix_t<Number> mat;
		hypro::operator_e op;
	};

  protected:
	typedef std::set<Transition<Number>*> transitionSet;

	Location( unsigned _id );
	Location( unsigned _id, const Location& _loc );
	Location( unsigned _id, const hypro::matrix_t<Number> _mat,
			  const transitionSet _trans, const Location<Number>::Invariant _inv );
	Location( unsigned _id, const hypro::matrix_t<Number> _mat,
			  const transitionSet _trans, const Location<Number>::Invariant _inv,
			  const hypro::matrix_t<Number> _extInputMat );

  private:
	/**
	 * Member
	 */
	hypro::matrix_t<Number> mFlow;
	hypro::matrix_t<Number> mExternalInput;
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
	const hypro::matrix_t<Number>& flow() const;
	const Invariant& invariant() const;
	const transitionSet& transitions() const;
	const hypro::matrix_t<Number>& externalInput() const;
	unsigned id() const { return mId; }

	void setFlow( hypro::matrix_t<Number> _mat );
	void setInvariant( struct hypro::Location<Number>::Invariant _inv );
	void setInvariant( hypro::matrix_t<Number> _mat, hypro::vector_t<Number> _vec, hypro::operator_e _op );
	void setLocation( struct locationContent _loc );
	void setTransitions( transitionSet _trans );
	void setExtInputMat( hypro::matrix_t<Number> _mat );

	bool operator<( const Location<Number>& _rhs ) const { return ( mId < _rhs.id() ); }

	friend std::ostream& operator<<( std::ostream& _ostr, const Location<Number>& _l ) {
		_ostr << "location(" << std::endl << "\t Flow = " << _l.mActivityMat << std::endl
			  << "\t Inv = " << _l.mInvariant.mat << std::endl << ")";
		return _ostr;
	}
};
}

#include "Location.tpp"
