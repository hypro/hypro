#pragma once
#include <boost/variant.hpp>

namespace hypro {

struct flowHashVisitor : public boost::static_visitor<std::size_t> {
	template <typename F>
	inline std::size_t operator()( const F& flow ) const {
		return std::hash<F>()( flow );
	}
};

struct flowDimensionVisitor : public boost::static_visitor<std::size_t> {
	template <typename F>
	inline std::size_t operator()( const F& flow ) const {
		return flow.dimension();
	}
};

struct flowTypeVisitor : public boost::static_visitor<DynamicType> {
	template <typename F>
	inline DynamicType operator()( const F& flow ) const {
		return flow.type();
	}
};

struct flowIsTimedVisitor : public boost::static_visitor<bool> {
	template <typename F>
	inline bool operator()( const F& flow ) const {
		return flow.isTimed();
	}
};

struct flowIsDiscreteVisitor : public boost::static_visitor<bool> {
	template <typename F>
	inline bool operator()( const F& flow ) const {
		return flow.isDiscrete();
	}
};

}  // namespace hypro