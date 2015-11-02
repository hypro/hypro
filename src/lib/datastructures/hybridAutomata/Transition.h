/*
 * Class that describes one transition of a hybrid automaton.
 * File:   transition.h
 * Author: stefan & ckugler
 *
 * Created on April 30, 2014, 9:06 AM
 */

#pragma once

#include "Location.h"

namespace hypro {
template <typename Number>
class Transition {
  public:
	struct Guard {
		hypro::vector_t<Number> vec;
		hypro::matrix_t<Number> mat;
		hypro::operator_e op;

		friend std::ostream& operator<<( std::ostream& _ostr, const Guard& _g ) {
			_ostr << _g.mat << " + " << _g.vec << _g.op << "0";
			return _ostr;
		}
	};

	struct Reset {
		hypro::vector_t<Number> translationVec;  // Translation Vector
		hypro::matrix_t<Number> transformMat;  // Transformation Matrix

		friend std::ostream& operator<<( std::ostream& _ostr, const Reset& _a ) {
			_ostr << _a.transformMat << " + " << _a.translationVec;
			return _ostr;
		}
	};

  private:
	/**
	 * Member
	 */
	Location<Number>* mSource;
	Location<Number>* mTarget;
	Guard mGuard;
	Reset mReset;

  public:
	/**
	 * Constructors & Destructor
	 */
	Transition() {}

	Transition( const Transition& _trans )
		: mSource( _trans.source() ), mTarget( _trans.target() ), mGuard( _trans.guard() ), mReset( _trans.reset() ) {}

	Transition( const Location<Number>* _source, const Location<Number>* _target, const struct Guard& _guard,
				const Reset& _reset )
		: mSource( _source ), mTarget( _target ), mGuard( _guard ), mReset( _reset ) {}

	~Transition() {}

	/**
	 * Getter & Setter
	 */
	Location<Number>* source() const { return mSource; }

	Location<Number>* target() const { return mTarget; }

	const Guard& guard() const { return mGuard; }

	const Reset& reset() const { return mReset; }

	void setSource( Location<Number>* _source ) { mSource = _source; }

	void setTarget( Location<Number>* _target ) { mTarget = _target; }

	void setGuard( const struct Guard& _guard ) { mGuard = _guard; }

	void setReset( const struct Reset& _val ) { mReset = _val; }

	friend std::ostream& operator<<( std::ostream& _ostr, const Transition<Number>& _t ) {
		_ostr << "transition(" << std::endl << "\t Source = " << *_t.source() << std::endl
			  << "\t Target = " << *_t.target() << std::endl << "\t Guard = " << _t.guard() << std::endl
			  << "\t Reset = " << _t.reset() << std::endl << ")";
		return _ostr;
	}
};
}
