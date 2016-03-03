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

enum Aggregation {none,box,parallelotope};

template <typename Number>
class Transition {
  public:
	struct Guard {
		hypro::vector_t<Number> vec;
		hypro::matrix_t<Number> mat;

		friend std::ostream& operator<<( std::ostream& _ostr, const Guard& _g ) {
			_ostr << _g.mat << " + " << std::endl << _g.vec;
			return _ostr;
		}
	};

	struct Reset {
		hypro::vector_t<Number> vec;  // Translation Vector
		hypro::matrix_t<Number> mat;  // Transformation Matrix

		friend std::ostream& operator<<( std::ostream& _ostr, const Reset& _a ) {
			_ostr << _a.mat << " + " << std::endl << _a.vec;
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
	Aggregation mAggregationSetting;

  public:
	/**
	 * Constructors & Destructor
	 */
	Transition() {}

	Transition( const Transition& _trans )
		: mSource( _trans.source() ), mTarget( _trans.target() ), mGuard( _trans.guard() ), mReset( _trans.reset() ), mAggregationSetting( _trans.aggregation() ) {}

	Transition( Location<Number>* _source, Location<Number>* _target )
		: mSource( _source ), mTarget( _target ), mGuard(), mReset(), mAggregationSetting(Aggregation::none) {}

	Transition( Location<Number>* _source, Location<Number>* _target, const struct Guard& _guard,
				const Reset& _reset )
		: mSource( _source ), mTarget( _target ), mGuard( _guard ), mReset( _reset ), mAggregationSetting(Aggregation::none) {}

	~Transition() {}

	/**
	 * Getter & Setter
	 */
	Location<Number>* source() const { return mSource; }

	Location<Number>* target() const { return mTarget; }

	const Guard& guard() const { return mGuard; }

	const Reset& reset() const { return mReset; }

	const Aggregation& aggregation() const { return mAggregationSetting; }

	void setSource( Location<Number>* _source ) { mSource = _source; }

	void setTarget( Location<Number>* _target ) { mTarget = _target; }

	void setGuard( const struct Guard& _guard ) { mGuard = _guard; }

	void setReset( const struct Reset& _val ) { mReset = _val; }

	void setAggregation( const Aggregation& _aggregation ) { mAggregationSetting = _aggregation; }

	friend std::ostream& operator<<( std::ostream& _ostr, const Transition<Number>& _t ) {
		_ostr << "transition(" << std::endl << "\t Source = " << _t.source()->id() << std::endl
			  << "\t Target = " << _t.target()->id() << std::endl << "\t Guard = " << _t.guard() << std::endl
			  << "\t Reset = " << _t.reset() << std::endl << ")";
		return _ostr;
	}
};
}
