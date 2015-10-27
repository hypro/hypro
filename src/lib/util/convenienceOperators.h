

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
}