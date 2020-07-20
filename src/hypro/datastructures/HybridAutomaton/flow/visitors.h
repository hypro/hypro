#pragma once
#include <variant>

namespace hypro {

struct flowHashVisitor {
	template <typename F>
	inline std::size_t operator()( const F& flow ) const {
		return std::hash<F>()( flow );
	}
};

struct flowDimensionVisitor {
	template <typename F>
	inline std::size_t operator()( const F& flow ) const {
		return flow.dimension();
	}
};

struct flowTypeVisitor {
	template <typename F>
	inline DynamicType operator()( const F& flow ) const {
		return flow.type();
	}
};

struct flowDynamicsTypeVisitor {
	template <typename F>
	inline DynamicType operator()( const F& flow ) const {
		return flow.getDynamicsType();
	}
};

struct flowIsTimedVisitor {
	template <typename F>
	inline bool operator()( const F& flow ) const {
		return flow.isTimed();
	}
};

struct flowIsDiscreteVisitor {
	template <typename F>
	inline bool operator()( const F& flow ) const {
		return flow.isDiscrete();
	}
};

}  // namespace hypro
