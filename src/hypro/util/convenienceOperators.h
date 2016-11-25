#pragma once

#include "../types.h"
#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <vector>

namespace hypro {
	/*
	template<typename T>
	bool operator ==(const std::vector<T>& lhs, const std::vector<T>& rhs) {
		std::cout << "Ping." << std::endl;
		if(lhs.size() != rhs.size()){
			return false;
		}

		for(std::size_t i = 0; i < lhs.size(); ++i){
			if(lhs.at(i) != rhs.at(i)){
				return false;
			}
		}

		return true;
	}
	*/

	template<typename T>
	std::ostream& operator <<(std::ostream& _out, const std::set<T>& _set) {
		if(!_set.empty()) {
			_out << *_set.begin();
			for(auto setIt = ++_set.begin(); setIt != _set.end(); ++setIt){
				_out << ", " << *setIt;
			}
		}

		return _out;
	}

	template<typename T>
	std::ostream& operator <<(std::ostream& _out, const std::vector<T>& _vector) {
		if(!_vector.empty()) {
			_out << *_vector.begin();
			for(auto vectorIt = ++_vector.begin(); vectorIt != _vector.end(); ++vectorIt){
				_out << ", " << *vectorIt;
			}
		}

		return _out;
	}

	template<typename T>
	std::ostream& operator <<(std::ostream& _out, const std::pair<T,T>& _pair) {
		_out << _pair.first << ", " << _pair.second;

		return _out;
	}

	template<typename Key, typename T>
	std::ostream& operator <<(std::ostream& _out, const std::map<Key,T>& _map) {
		if(!_map.empty()) {
			_out << _map.begin()->first << " -> " << _map.begin()->second;
			for(auto mapIt = ++_map.begin(); mapIt != _map.end(); ++mapIt){
				_out << ", " << mapIt->first << " -> " << mapIt->second;
			}
		}

		return _out;
	}

	template<typename T>
	struct typeName {
		std::string get() {
			return "unknown";
		}
	};

	template<>
	struct typeName<double> {
		std::string get() {
			return "double";
		}
	};

	template<>
	struct typeName<mpq_class> {
		std::string get() {
			return "mpq_class";
		}
	};

} // namespace hypro
