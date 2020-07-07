#pragma once
#include "../../representations/ConstraintSet/ConstraintSet.h"
#include "../../representations/types.h"
#include "../../types.h"
#include "decomposition/Decomposition.h"

#include <iosfwd>
#include <variant>

namespace hypro {

template <typename Number>
class Condition {
  private:
	std::vector<ConstraintSetT<Number>> mConstraints;  /// holds the constraints specifying the condition
	mutable std::vector<TRIBOOL> mConditionIsBox;	   /// cache to check whether constraints are axis-aligned
	mutable std::size_t mHash = 0;					   /// cache for the hash value
  public:
	Condition() = default;
	Condition( const matrix_t<Number>& mat, const vector_t<Number>& vec )
		: mConstraints( { ConstraintSetT<Number>( mat, vec ) } )
		, mConditionIsBox( { TRIBOOL::NSET } )
		, mHash( 0 ) {}
	explicit Condition( const ConstraintSetT<Number>& constraints )
		: mConstraints( { constraints } )
		, mConditionIsBox( { TRIBOOL::NSET } )
		, mHash( 0 ) {}
	explicit Condition( const std::vector<std::variant<ConstraintSetT<Number>>>& sets );
	Condition( const Condition& orig ) = default;
	Condition( Condition&& orig ) = default;
	Condition& operator=( const Condition& orig ) = default;
	Condition& operator=( Condition&& orig ) = default;
	~Condition() {}

	// Access
	std::size_t size() const { return mConstraints.size(); }
	bool empty() const { return mConstraints.empty(); }

	const matrix_t<Number>& getMatrix( std::size_t I = 0 ) const {
		assert( mConstraints.size() > I );
		return mConstraints.at( I ).matrix();
	}
	const vector_t<Number>& getVector( std::size_t I = 0 ) const {
		assert( mConstraints.size() > I );
		return mConstraints.at( I ).vector();
	}

	bool isAxisAligned() const;
	bool isAxisAligned( std::size_t i ) const;

	void setMatrix( const matrix_t<Number>& m, std::size_t I = 0 );
	void setVector( const vector_t<Number>& v, std::size_t I = 0 );

	const std::vector<ConstraintSetT<Number>>& constraints() const { return mConstraints; }

	std::size_t hash() const;

	std::string getDotRepresentation( const std::vector<std::string>& vars ) const;

	/**
    * decomposes constraint set of this condition
    */
	void decompose( const Decomposition& decomposition );

	// helper methods
	//template<typename Representation, typename ...Rargs>
	//std::pair<bool,State<Number,Representation, Rargs...>> isSatisfiedBy(const State<Number,Representation, Rargs...>& inState) const;

	friend bool operator==( const Condition& lhs, const Condition& rhs ) {
		if ( lhs.size() != rhs.size() ) {
			return false;
		}

		for ( std::size_t i = 0; i < lhs.size(); ++i ) {
			if ( ( lhs.getVector( i ) != rhs.getVector( i ) ) || ( lhs.getMatrix( i ) != rhs.getMatrix( i ) ) ) {
				return false;
			}
		}
		return true;
	}

	friend bool operator!=( const Condition& lhs, const Condition& rhs ) {
		return !( lhs == rhs );
	}

#ifdef HYPRO_LOGGING
	friend std::ostream& operator<<( std::ostream& out, const Condition& in ) {
		std::size_t i = 0;
		for ( const auto& pair : in.constraints() ) {
			out << "Constraint " << i << ": " << pair.matrix() << " constants: " << pair.vector() << std::endl;
			++i;
		}
#else
	friend std::ostream& operator<<( std::ostream& out, const Condition& ) {
#endif
		return out;
	}

  private:
	void checkAxisAligned( std::size_t i ) const;
};

template <typename Number>
Condition<Number> combine(
	  const Condition<Number>& lhs, const Condition<Number>& rhs,
	  const std::vector<std::string> haVar, const std::vector<std::string> lhsVar, const std::vector<std::string> rhsVar );

}  // namespace hypro

namespace std {

template <typename Number>
struct hash<hypro::Condition<Number>> {
	std::size_t operator()( const hypro::Condition<Number>& cond ) const {
		std::size_t seed = 0;
		for ( auto conSet : cond.constraints() ) {
			carl::hash_add( seed, std::hash<hypro::matrix_t<Number>>()( conSet.matrix() ) );
			carl::hash_add( seed, std::hash<hypro::vector_t<Number>>()( conSet.vector() ) );
		}
		return seed;
	}
};

}  // namespace std

#include "Condition.tpp"
