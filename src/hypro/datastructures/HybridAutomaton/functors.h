/**
 * File holding different functors encapsulating required state set representation methods
 */

#pragma once

namespace hypro {

	struct union_functor {
		template<typename T>
		T operator()(const T& lhs, const T& rhs) {
			return lhs.unite(rhs);
		}
	};

	template<typename Number>
	struct affineTransformation_functor {
		matrix_t<Number> m;
		vector_t<Number> v;

		affineTransformation_functor(const matrix_t<Number>& mat, const vector_t<Number>& vec)
			:m(mat)
			,v(vec)
		{}

		template<typename T>
		T operator()(const T& lhs) {
			return lhs.affineTransformation(m,v);
		}
	};

	/**
	 * @brief      Lazy satisfiesHalfspaces functor, which has a state. As soon as the first call to this evaluates to the empty set,
	 * 			   all other calls to this instance evaluate in zero time.
	 *
	 * @tparam     Number  The used number type.
	 */
	template<typename Number>
	struct satisfiesHalfspaces_functor {
		matrix_t<Number> m;
		vector_t<Number> v;

		satisfiesHalfspaces_functor(const matrix_t<Number>& mat, const vector_t<Number>& vec)
			: m(mat)
			, v(vec)
		{}

		template<typename T>
		std::pair<bool,T> operator()(const T& lhs) {
			return lhs.satisfiesHalfspaces(m,v);
		}
	};

} // namespace hypro
