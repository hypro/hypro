
namespace hypro {

	template<typename Number>
	struct State {
		unsigned locationId;
		hypro::vector_t<Number> constraints;
		hypro::matrix_t<Number> constrants;
		std::map<carl::Variable, carl::Interval<Number>> discreteConstraints;
	};
} // namespace


