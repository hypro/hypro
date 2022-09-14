#pragma once

#include "../../types.h"
#include "Transition.h"

#include <deque>
#include <initializer_list>

namespace hypro {

/**
 * @brief      Struct holding a path element, which can be a representative for a time step or a
 * representative for a discrete step.
 * @tparam     Number  The used number type.
 */
template <typename Number, typename tNumber = hypro::tNumber>
struct TPathElement {
	Transition<Number, Location<Number>>* transition = nullptr;					/// Pointer to a transition in case of a discrete step.
	carl::Interval<tNumber> timeInterval = createUnboundedInterval<tNumber>();	/// Time interval holding either the size of the time step or the local time in which the transition for the discrete step was enabled.

	/**
	 * @brief      Constructor for a discrete step element.
	 * @param      t            The transition.
	 * @param[in]  enabledTime  The enabled time.
	 */
	TPathElement( Transition<Number, Location<Number>>* t, const carl::Interval<tNumber>& enabledTime )
		: transition( t )
		, timeInterval( enabledTime ) {}

	/**
	 * @brief      Constructor for a time step.
	 * @param[in]  timeStep  The time step size.
	 */
	TPathElement( const carl::Interval<tNumber>& timeStep )
		: transition( nullptr )
		, timeInterval( timeStep ) {}

	/**
	 * @brief      Determines if the element represents a discrete step.
	 * @return     True if discrete step, False otherwise.
	 */
	bool isDiscreteStep() const {
		return ( transition != nullptr );
	}

	const carl::Interval<tNumber>& getTimestamp() const {
		return timeInterval;
	}

	Transition<Number, Location<Number>>* getTransition() const {
		return transition;
	}

	/**
	 * @brief      Outstream operator.
	 * @param      out       The outstream.
	 * @param[in]  pathElem  The path element.
	 * @return     A reference to the outstream.
	 */
	friend std::ostream& operator<<( std::ostream& out, const TPathElement<Number, tNumber>& pathElem ) {
		carl::Interval<double> tmp( carl::convert<tNumber, double>( pathElem.timeInterval.lower() ), carl::convert<tNumber, double>( pathElem.timeInterval.upper() ) );
		if ( pathElem.isDiscreteStep() ) {
			// out << pathElem.transition->getSource()->getId() << " -> " << pathElem.transition->getTarget()->getId() << " " << tmp;
			out << pathElem.transition->getSource()->hash() << " -> " << pathElem.transition->getTarget()->hash() << " " << tmp;
		} else {
			out << tmp;
		}
		return out;
	}

	/**
	 * @brief      Equality comparison operator.
	 * @param[in]  lhs   The left hand side.
	 * @param[in]  rhs   The right hand side.
	 * @return     True if both elements are equal, False otherwise.
	 */
	friend bool operator==( const TPathElement<Number, tNumber>& lhs, const TPathElement<Number, tNumber>& rhs ) {
		if ( lhs.isDiscreteStep() != rhs.isDiscreteStep() ) {
			return false;
		}

		if ( lhs.isDiscreteStep() ) {
			assert( rhs.isDiscreteStep() );
			return ( lhs.transition == rhs.transition && lhs.timeInterval == rhs.timeInterval );
		}
		assert( !rhs.isDiscreteStep() );
		return ( lhs.timeInterval == rhs.timeInterval );
	}

	/**
	 * @brief      Not-equal operator.
	 * @param[in]  lhs   The left hand side.
	 * @param[in]  rhs   The right hand side.
	 * @return     True if both elements are not equal, False otherwise.
	 */
	friend bool operator!=( const TPathElement<Number, tNumber>& lhs, const TPathElement<Number, tNumber>& rhs ) {
		return !( lhs == rhs );
	}
};

/**
 * @brief      Class to define a path in some hybrid automaton.
 * @tparam     Number  The used number type.
 */
template <typename Number, typename tNumber = Number>
class Path {
  private:
	std::deque<TPathElement<Number, tNumber>> mPath;  // why is this a deque? - shouldn't it be more of a double-linked list?
	// or even better: define this recursively. A path is empty or a subpath
	// Stefan: This is historic :).
	bool chatteringZeno = false;

  public:
	Path(){};
	Path( std::initializer_list<TPathElement<Number, tNumber>> pathElems );
	~Path() {
		while ( !mPath.empty() ) {
			mPath.erase( mPath.begin() );
		}
	};

	void add( const TPathElement<Number, tNumber>& elem );
	void addTransition( Transition<Number, Location<Number>>* t, const carl::Interval<tNumber>& enabledTime );
	void addTimeStep( const carl::Interval<tNumber>& timeStep );
	std::pair<Transition<Number, Location<Number>>*, carl::Interval<tNumber>> getTransitionToJumpDepth( unsigned depth ) const;

	Path& deleteAfterPos( std::size_t cutpos );
	Path& deleteBeforePos( std::size_t cutpos );
	Path& clear();

	static bool sharePrefix( const Path<Number, tNumber>& lhs, const Path<Number, tNumber>& rhs );
	bool sharesPrefix( const Path<Number, tNumber>& rhs ) const;
	Path sharedPrefix( const Path<Number, tNumber>& rhs ) const;
	Path removeSharedPrefix( const Path<Number, tNumber>& rhs ) const;
	bool isEmpty() const { return ( mPath.size() == 0 ); }
	tNumber maximalTimeSpan( typename std::deque<TPathElement<Number, tNumber>>::const_iterator start, typename std::deque<TPathElement<Number, tNumber>>::const_iterator end ) const;

	std::size_t getNumberDiscreteJumps() const;
	std::vector<Transition<Number, Location<Number>>*> getTransitionSequence( typename std::deque<TPathElement<Number, tNumber>>::const_iterator start, typename std::deque<TPathElement<Number, tNumber>>::const_iterator end ) const;
	std::vector<Transition<Number, Location<Number>>*> getTransitionSequence() const { return this->getTransitionSequence( mPath.begin(), mPath.end() ); }
	bool hasChatteringZeno() const;

	// comparison - read as "is longer than"
	bool operator>( const Path<Number, tNumber>& r ) const;
	bool operator>( unsigned r ) const;

	// Iterator
	using TIterator = typename std::deque<TPathElement<Number, tNumber>>::iterator;
	using TIterator_const = typename std::deque<TPathElement<Number, tNumber>>::const_iterator;
	TIterator begin();
	TIterator end();
	TIterator_const begin() const;
	TIterator_const end() const;
	const TPathElement<Number, tNumber>& back() const;
	const TPathElement<Number, tNumber>& front() const;

	// legacy operations - replace them
	std::size_t size() const;
	TPathElement<Number, tNumber> at( std::size_t index ) const;
	void pop_front();
	void push_front( const TPathElement<Number, tNumber>& elem );

	friend std::ostream& operator<<( std::ostream& _out, const Path<Number, tNumber>& path ) {
		if ( !path.isEmpty() ) {
			_out << path.at( 0 );
			for ( std::size_t i = 1; i < path.size(); ++i ) {
				_out << ", " << path.at( i );
			}
		}
		return _out;
	}

	bool operator==( const Path<Number, tNumber>& rhs ) const {
		if ( this->size() != rhs.size() ) {
			return false;
		}
		for ( std::size_t i = 0; i < this->size(); ++i ) {
			if ( this->at( i ) != rhs.at( i ) ) {
				return false;
			}
		}
		return true;
	}

	bool operator!=( const Path<Number, tNumber>& rhs ) const {
		return !( *this == rhs );
	}
};

}  // namespace hypro

#include "Path.tpp"
