/**
 * This file holds some general purpose convenience operators.
 * @file operators.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * 
 * @since	2015-06-16
 * @version	2015-06-16
 */
 
namespace hypro {
	template<typename T>
	std::ostream& operator<<(std::ostream& out, const std::vector<T>& lhs) {
		out << "( ";
		for(const auto item : lhs)
			out << item << " ";
		out << ")" << std::endl;
		return out;
	}
} // namespace