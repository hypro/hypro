/*
 * Class that describes a label of an hybrid automaton.
 * @file   Label.h
 * @author Tobias Vogel <tobias.vogel@rwth-aachen.de>
 *
 * @since 	2017-12-03
 */

#pragma once
#include <functional>
#include <iosfwd>
#include <string>

namespace hypro {

class Label {
  private:
	std::string mName = "";

  public:
	Label() = delete;
	Label( const Label& in ) = default;
	Label( Label&& in ) = default;

	explicit Label( const std::string& name )
		: mName( name ){};

	~Label(){};

	Label& operator=( const Label& in ) = default;
	Label& operator=( Label&& in ) = default;

	const std::string& getName() const {
		assert( mName != "" );
		return mName;
	}

	void setName( const std::string& name ) { mName = name; }

	friend bool operator==( const Label& lhs, const Label& rhs ) {
		return lhs.getName() == rhs.getName();
	}

	friend bool operator!=( const Label& lhs, const Label& rhs ) {
		return !( lhs == rhs );
	}

	friend bool operator<( const Label& lhs, const Label& rhs ) {
		return lhs.getName() < rhs.getName();
	}

	friend std::ostream& operator<<( std::ostream& ostr, const Label& l ) {
		ostr << l.getName();
		return ostr;
	}
};

}  // namespace hypro

namespace std {
/**
 * @brief Specialization of std::hash for labels
 * @tparam
 */
template <>
struct hash<hypro::Label> {
	/// Functor for std::hash
	std::size_t operator()( const hypro::Label& l ) const {
		return std::hash<std::string>{}( l.getName() );
	}
};
}  // namespace std
