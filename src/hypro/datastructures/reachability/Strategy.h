#pragma once

#include "StrategyNode.h"

#include <vector>

namespace hypro {

namespace detail {
template <typename T>
struct StrategyVariant;
template <typename... Ts>
struct StrategyVariant<boost::variant<Ts...>> {
	using types = boost::variant<StrategyNode<Ts>...>;
};
}  // namespace detail

template <typename State>
using StrategyNodeVariant = typename detail::StrategyVariant<typename State::repVariant>::types;

template <typename StateType>
class Strategy {
	std::vector<StrategyNodeVariant<StateType>> mStrategy;

  public:
	Strategy() = default;
	Strategy( std::initializer_list<StrategyNodeVariant<StateType>> in )
		: mStrategy( in ) {}

	const std::vector<StrategyNodeVariant<StateType>>& getStrategy() const { return mStrategy; }
	void setStrategy( const std::vector<StrategyNodeVariant<StateType>>& s ) { mStrategy = s; }
	void emplace_back( StrategyNodeVariant<StateType>&& n ) { mStrategy.emplace_back( std::move( n ) ); }

	std::size_t size() const { return mStrategy.size(); }
	const StrategyNodeVariant<StateType>& operator[]( std::size_t i ) const { return mStrategy[i]; }

	void advanceToLevel( StateType& state, std::size_t lvl, std::size_t subset = 0 ) const {
		DEBUG( "hypro.datastructures", "Call to set state subset " << subset << " to strategy level " << lvl );
		boost::apply_visitor( detail::strategyConversionVisitor<StateType>( state, subset ), mStrategy[lvl] );
	}

	StrategyParameters getParameters( std::size_t lvl ) const {
		assert( 0 <= lvl && lvl < mStrategy.size() );
		return boost::apply_visitor( detail::getParametersVisitor(), mStrategy[lvl] );
	}

	void removeNode( std::size_t lvl ) {
		if ( mStrategy.size() > 0 ) {
			assert( 0 <= lvl && lvl < mStrategy.size() );
			auto it = mStrategy.begin();
			mStrategy.erase( it + lvl );
		}
	}

#ifdef HYPRO_LOGGING
	friend std::ostream& operator<<( std::ostream& ostr, const Strategy<StateType>& strat ) {
		std::cout << "Current strategy is: \n";
		for ( std::size_t i = 0; i < strat.getStrategy().size(); ++i ) {
			ostr << "Node " << i << ": " << strat.getParameters( i ) << std::endl;
		}
#else
	friend std::ostream& operator<<( std::ostream& ostr, const Strategy<StateType>& /*strat*/ ) {
#endif
		return ostr;
	}
};

}  // namespace hypro
