#pragma once

#include "../types.h"

#include <iosfwd>
#include <map>
#include <set>
#include <utility>
#include <vector>

namespace hypro {

/// enum-to-int conversion
template <typename Enumeration>
auto as_integer( Enumeration const value )
	  -> typename std::underlying_type<Enumeration>::type {
	return static_cast<typename std::underlying_type<Enumeration>::type>( value );
}

/// enum outstream operator
template <typename Enumeration, carl::EnableIf<std::is_enum<Enumeration>> = carl::dummy>
std::ostream& operator<<( std::ostream& out, Enumeration in ) {
	out << as_integer( in );
	return out;
}

/// set-outstream operator (element-wise)
template <typename T>
std::ostream& operator<<( std::ostream& _out, const std::set<T>& _set ) {
	if ( !_set.empty() ) {
		_out << *_set.begin();
		for ( auto setIt = ++_set.begin(); setIt != _set.end(); ++setIt ) {
			_out << ", " << *setIt;
		}
	}

	return _out;
}

/// vector-outstream operator (element-wise)
template <typename T>
std::ostream& operator<<( std::ostream& _out, const std::vector<T>& _vector ) {
	if ( !_vector.empty() ) {
		_out << *_vector.begin();
		for ( auto vectorIt = ++_vector.begin(); vectorIt != _vector.end(); ++vectorIt ) {
			_out << ", " << *vectorIt;
		}
	}

	return _out;
}

/// pair-outstream operator (element-wise)
template <typename T>
std::ostream& operator<<( std::ostream& _out, const std::pair<T, T>& _pair ) {
	_out << _pair.first << ", " << _pair.second;

	return _out;
}

/// map-outstream operator (element-wise)
template <typename Key, typename T>
std::ostream& operator<<( std::ostream& _out, const std::map<Key, T>& _map ) {
	if ( !_map.empty() ) {
		_out << _map.begin()->first << " -> " << _map.begin()->second;
		for ( auto mapIt = ++_map.begin(); mapIt != _map.end(); ++mapIt ) {
			_out << ", " << mapIt->first << " -> " << mapIt->second;
		}
	}

	return _out;
}

/// default case typename to string
template <typename T>
struct typeName {
	std::string get() {
		return "unknown";
	}
};
/// typename to string: double
template <>
struct typeName<double> {
	std::string get() {
		return "double";
	}
};
/// typename to string: mpq_class
template <>
struct typeName<mpq_class> {
	std::string get() {
		return "mpq_class";
	}
};

}  // namespace hypro
