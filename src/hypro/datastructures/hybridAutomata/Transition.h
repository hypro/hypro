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

enum Aggregation {none,boxAgg,parallelotopeAgg};

template <typename Number>
class Transition {
  public:
	struct Guard {
		vector_t<Number> vec;
		matrix_t<Number> mat;

		unsigned discreteOffset;
		std::vector<std::pair<carl::Variable, matrix_t<Number>>> discreteGuard;

		void addArtificialDimension() {
			matrix_t<Number> newConstraints = matrix_t<Number>::Zero(mat.rows(), mat.cols()+1);
			newConstraints.block(0,0,mat.rows(), mat.cols()) = mat;
			mat = newConstraints;
		}

		friend std::ostream& operator<<( std::ostream& _ostr, const Guard& _g ) {
			_ostr << _g.mat << " + " << std::endl << _g.vec << std::endl;
			for(const auto& discretePair : _g.discreteGuard) {
				_ostr << "guard dim " << discretePair.first << ": " << discretePair.second << std::endl;
			}
			return _ostr;
		}
	};

	struct Reset {
		vector_t<Number> vec;  // Translation Vector
		matrix_t<Number> mat;  // Transformation Matrix

		unsigned discreteOffset;
		vector_t<Number> discreteVec;  // Translation Vector
		matrix_t<Number> discreteMat;  // Transformation Matrix

		void addArtificialDimension() {
			matrix_t<Number> newConstraints = matrix_t<Number>::Zero(mat.rows()+1, mat.cols()+1);
			newConstraints.block(0,0,mat.rows(), mat.cols()) = mat;
			// The artificial dimension is not changed upon reset.
			newConstraints(mat.rows(), mat.cols()) = 1;
			vector_t<Number> newConstants = vector_t<Number>::Zero(vec.rows()+1);
			newConstants.block(0,0,vec.rows(),1) = vec;
			mat = newConstraints;
			vec = newConstants;
		}

		friend std::ostream& operator<<( std::ostream& _ostr, const Reset& _a ) {
			_ostr << _a.mat << " + " << std::endl << _a.vec << std::endl;
			_ostr << "Discrete Reset:" << _a.discreteMat << " + " << _a.discreteVec << std::endl;
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
	std::vector<unsigned> mDiscreteDimensions;
	Aggregation mAggregationSetting;
	bool mTimeTriggered;
	Number mTriggerTime;

  public:
	/**
	 * Constructors & Destructor
	 */
	Transition()
		: mSource( nullptr )
		, mTarget( nullptr )
		, mGuard()
		, mReset()
		, mAggregationSetting(Aggregation::none)
		, mTimeTriggered( false )
		, mTriggerTime( -1 )
	{}

	Transition( const Transition& _trans )
		: mSource( _trans.source() )
		, mTarget( _trans.target() )
		, mGuard( _trans.guard() )
		, mReset( _trans.reset() )
		, mAggregationSetting( _trans.aggregation() )
		, mTimeTriggered( _trans.triggerTime() >= 0 )
		, mTriggerTime( _trans.triggerTime() )
	{}

	Transition( Location<Number>* _source, Location<Number>* _target )
		: mSource( _source )
		, mTarget( _target )
		, mGuard()
		, mReset()
		, mAggregationSetting(Aggregation::none)
		, mTimeTriggered( false )
		, mTriggerTime( -1 )
	{}

	Transition( Location<Number>* _source, Location<Number>* _target, const struct Guard& _guard,
				const Reset& _reset )
		: mSource( _source )
		, mTarget( _target )
		, mGuard( _guard )
		, mReset( _reset )
		, mAggregationSetting(Aggregation::none)
		, mTimeTriggered( false )
		, mTriggerTime( -1 )
	{}

	~Transition() {}

	/**
	 * Getter & Setter
	 */
	Location<Number>* source() const { return mSource; }
	Location<Number>* target() const { return mTarget; }
	const Guard& guard() const { return mGuard; }
	const Reset& reset() const { return mReset; }
	const Aggregation& aggregation() const { return mAggregationSetting; }
	bool isTimeTriggered() const { return mTimeTriggered; }
	Number triggerTime() const { return mTriggerTime; }

	void setSource( Location<Number>* _source ) { mSource = _source; }
	void setTarget( Location<Number>* _target ) { mTarget = _target; }
	void setGuard( const struct Guard& _guard ) { mGuard = _guard; }
	void setReset( const struct Reset& _val ) { mReset = _val; }
	void setAggregation( const Aggregation& _aggregation ) { mAggregationSetting = _aggregation; }
	void setTriggerTime( const Number& _triggerTime ) { mTriggerTime = _triggerTime; mTimeTriggered = mTriggerTime >= 0; }

	void addArtificialDimension() {
		mGuard.addArtificialDimension();
		mReset.addArtificialDimension();
	}

	friend std::ostream& operator<<( std::ostream& _ostr, const Transition<Number>& _t ) {
		_ostr << "transition(" << std::endl << "\t Source = " << _t.source()->id() << std::endl
			  << "\t Target = " << _t.target()->id() << std::endl << "\t Guard = " << _t.guard() << std::endl
			  << "\t Reset = " << _t.reset() << std::endl << ")";
		return _ostr;
	}
};
} // namespace hypro
