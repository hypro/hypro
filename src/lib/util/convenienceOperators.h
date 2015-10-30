

namespace hypro {

	template<typename T>
	bool operator ==(const std::vector<T>& lhs, const std::vector<T>& rhs) {
		std::cout << "Ping." << std::endl;
		if(lhs.size() != rhs.size())
			return false;

		for(std::size_t i = 0; i < lhs.size(); ++i)
			if(lhs.at(i) != rhs.at(i))
				return false;

		return true;
	}

	template<typename T>
	std::ostream& operator <<(std::ostream& _out, const std::set<T>& _set) {
		if(!_set.empty()) {
			_out << *_set.begin();
			for(auto setIt = ++_set.begin(); setIt != _set.end(); ++setIt)
				_out << ", " << *setIt;
		}

		return _out;
	}

	template<typename T>
	std::ostream& operator <<(std::ostream& _out, const std::vector<T>& _vec) {
		if(!_vec.empty()) {
			_out << *_vec.begin();
			for(auto vecIt = ++_vec.begin(); vecIt != _vec.end(); ++vecIt)
				_out << ", " << *vecIt;
		}

		return _out;
	}
}